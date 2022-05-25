/********************************************
 *
 *  Name: Eric Chen
 *  Email: echen606@usc.edu
 *  Section: 30799 Wednesday 12:30pm
 *  Assignment: Project - Thermometer
 *
 ********************************************/

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>

#include "lcd.h"
#include "ds18b20.h"
#include "encoder.h"
#include "project.h"
#include "serial.h"

// for Rotary Encoder
unsigned char new_state, old_state;
unsigned char a, b;
unsigned char changed;

// for LED
unsigned int threshold = 75;   // Threshold for the temperature, default at 75 but eeprom will overide eventually, used to debug when I want flash memory off

// for Buzzer
volatile unsigned short int buzzer_phase = 0; // for buzzer length
volatile unsigned char buzzed = 0; // buzzed dont buzz until returns to a different state then goes back to hot

// for temperature states
volatile unsigned char state; // remembers which state the temperature is in

// for buttons
volatile char receiving = local;

// for RX
short int remote_fahrenheit = 0;
char receive_buffer[5];
char begin = 0;
int placement = 0;
char is_complete = 0;

// function prototypes
void timer0_init(void);
void timer1_init(void);
void timer2_init(void);
void write_state(void);
void thermometer_init(void);

int main() {

    // configures all the inits and pins
    thermometer_init();

    // Write a spash screen to the LCD
    lcd_moveto(0, 2);
    lcd_stringout("EE109 Project");
    lcd_moveto(1, 3);
    lcd_stringout("Eric Chen");
    _delay_ms(1000);
    lcd_clear();

    //  draws background for LCD
    lcd_moveto(0,0);
    lcd_stringout("Local: ");
    lcd_moveto(1,0);
    lcd_stringout("Remote: ");

    //  initializes the starting temperature
    unsigned char t[2];
    char buffer [10];
    short int celsius = 0;
    short int to_divide = 18;
    short int fahrenheit = 0;
    ds_convert();

    // initalizes the threshold and first temperature conversion
    lcd_moveto(0,14);
    snprintf(buffer, 10, "%d",threshold);
    lcd_stringout(buffer);

    while(1){

        if(state != warm) TCCR1B &= ~((1 << CS12)|(1 << CS11)|(1 << CS10));

        if(is_complete){
            lcd_moveto(1, 9);
            sscanf(receive_buffer, "%hd", &remote_fahrenheit);
            lcd_moveto(1, 8);
            snprintf(buffer, 10, "%hd", remote_fahrenheit);
            lcd_stringout(buffer);
            is_complete = 0;
            begin = 0;
        }

        if (ds_temp(t)){ // for updating threshold
            celsius = 0;
            celsius |= ((0x07 & t[1]) << 8);
            celsius |= (t[0]);
            fahrenheit = ((celsius * to_divide) / 16) + 320;
            snprintf(buffer, 10, "%d.%d",fahrenheit/10, fahrenheit%10);
            lcd_moveto(0,7);
            lcd_stringout(buffer);
            ds_convert();
        }

        // uses helper function to transmit tx
        tx_helper(fahrenheit/10);

        // button chooses what temperature the servo abides to
        if(receiving == local){
            OCR2A = (fahrenheit/10-40)*-4/10+36;
            lcd_moveto(1,12);
            lcd_writedata('L');
        }
        else if(receiving == remote){
            OCR2A = (remote_fahrenheit-40)*-4/10+36;
            lcd_moveto(1,12);
            lcd_writedata('R');
        }
        

        if((fahrenheit/10) >= threshold){ // stay red
            state = hot;
            PORTB &= ~(1<<PB5);
            PORTB |= (1<<PB4);
        }
        else if((fahrenheit/10)+3 >= threshold){ // blinking 0.5s
            buzzed = 0;
            state = warm;
            TCCR1B |= (1 << CS12);
            PORTB &= ~(1<<PB5);
        }
        else{ // stay green
            buzzed = 0;
            state = cool;
            PORTB &= ~(1<<PB4);
            PORTB |= (1<<PB5);
        }

        // updates LCD whether currently its cool warm or hot
        write_state();

        if(changed){ // for the threshold
            changed = 0; // Reset changed flag
            lcd_moveto(0,14);
            snprintf(buffer, 10, "%d",threshold);
            lcd_stringout(buffer);
        }
    }
}

ISR(PCINT1_vect){ // pin change interrupt for local and remote buttons
    unsigned char local_state = PINC & (1<<PC1);
    unsigned char remote_state = PINC & (1<<PC2);
    if(!local_state && receiving != local){ // cant go from local to local again
        receiving = local;
    }
    else if(!remote_state && receiving != remote){ // cant go from remote to remote again
        receiving = remote;
    }
}

ISR(TIMER0_COMPA_vect){ // buzzes the buzzer for 0.5s

    if(buzzer_phase == 175){ // instead of running low right after high in play_note, only one each counter cycles, hence there should be 349/2 phases
        buzzed = 1;
        buzzer_phase = 0;
    }
    else if(!buzzed && (state == hot)){
        PINC |= (1<<PC5);
        buzzer_phase++;
    }
}

ISR(TIMER1_COMPA_vect){ // blinks the LED 0.5s
    PINB |= (1<<PB4);
}

void timer0_init(void) // timer for the buzzer
{
    TCCR0B |= (1 << WGM02);
    TIMSK0 |= (1 << OCIE0A);
    OCR0A = 45; // this value came from the conversion to microseconds in the original variable delay function
                // (500000/349/2 + 5)/10 * 0.00001 * 16000000/256 = 45            
    TCCR0B |= (1 << CS02);  
}

void timer1_init(void){ // timer for the led
    TCCR1B |= (1 << WGM12);
    TIMSK1 |= (1 << OCIE1A);
    OCR1A = 31250;
    TCCR1B |= (1 << CS12);
}

void timer2_init(void){ // timer for the servo
    TCCR2A |= (0b11 << WGM00);
    TCCR2A |= (0b10 << COM0A0);
    TCCR2B |= (0b111 << CS20);  // Prescaler = 1024 for 16ms period
}

void write_state(void){
    lcd_moveto(1,15);
    if(state == hot) lcd_writedata('H');
    else if(state == warm) lcd_writedata('W');
    else lcd_writedata('C');
}

void thermometer_init(void){
        // sets up the LCD
    lcd_init();

    // sets up the rotary encoder
    encoder_init();

    if(ds_init() == 0){ // set ups the thermometer
        lcd_stringout("failed");
        while(1){}
    }

    // sets up serial
    serial_init();

    //  sets up the ISR
    PCICR |= ((1<<PCIE1)|(1 << PCIE2)); // for ports D and C
    PCMSK1 |= ((1<<PCINT9) | (1<<PCINT10)); // for PC1 and PC2
    PCMSK2 |= ((1 << PCINT18) | (1 << PCINT19)); // for PD2 and PD3
    UCSR0B |= (1 << RXCIE0); // for RX
    sei();

    // sets up the timers
    timer0_init(); // timer for 0.5s buzzer
    timer1_init(); // timer for 0.5s using 1024 prescalar
    timer2_init(); // timer for pwm of the servo

    //  initialize the buzzers output port
    DDRC |= (1 << PC5);

    // sets PB3 port to output for the servo motor
    DDRB |= (1 << PB3);

    // initialize the ports for led red and green
    DDRB |= ((1<<PB4) | (1<<PB5));

    //  initializes the rotary encoder turns on the pull up resistors
    DDRD &= ~(1 << PD3) | (1 << PD2);
    PORTD |= (1 << PD3) | (1 << PD2);

    //  initializes the buttons for local and remote
    DDRC &= ~(1 << PC1) | (1 << PC2);
    PORTC |= (1 << PC1); // pull up for local buttong
    PORTC |= (1 << PC2); // pull up for remote button

    DDRC |= (1 << PC4);
    PORTC &= ~(1 << PC4);

    // make sure value is in a valid threshold value
    if(eeprom_read_byte((void *) 100) >= 50 && eeprom_read_byte((void *) 100) <= 90){
        threshold = eeprom_read_byte((void *) 100);
    }
    else{
        eeprom_update_byte((void *) 100, 0x32);
        threshold = eeprom_read_byte((void *) 100);
    }
}