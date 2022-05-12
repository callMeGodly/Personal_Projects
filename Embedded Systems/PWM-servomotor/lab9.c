/********************************************
 *
 *  Name: Eric Chen
 *  Email: echen606@usc.edu
 *  Section: 30799 Wednesday 12:30pm
 *  Assignment: Lab 9 - PWM
 *
 ********************************************/

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>

#include "lcd.h"

//  global variables for the ISR to use
volatile unsigned char new_state, old_state;
volatile unsigned char changed = 0;  // Flag for state change
volatile unsigned char count = 128;        // Count to display
volatile unsigned char a, b;
volatile unsigned int width = 3000;


void timer1_init(void){
    TCCR1B |= (1 << WGM13 | 1 << WGM12);
    TCCR1A |= (1 << WGM11 | 1 << WGM10);
    TCCR1A |= (1 << COM1B1);
    OCR1B = 3000; // the starting value for OCR1B when the pulse width is 1.5ms
    OCR1A = 40000; // the pulse period
    TCCR1B |= (1 << CS11);
}

void timer2_init(void)
{
    TCCR2A |= (0b11 << WGM00);  // Fast PWM mode, modulus = 256
    TCCR2A |= (0b10 << COM0A0); // Turn D11 on at 0x00 and off at OCR2A
    OCR2A = 128;                // Initial pulse duty cycle of 50%
    TCCR2B |= (0b101 << CS20);  // Prescaler = 1024 for 16ms period
}

int main() {

    // All lcd functions and calls are disabled for the motor
    // The code is commented out because a splash is required on the online checksheet
    // initiates the lcd
    //lcd_init();

    // Write a spash screen to the LCD
    // lcd_moveto(0, 2);
    // lcd_stringout("EE109 Lab 8");
    // lcd_moveto(1, 3);
    // lcd_stringout("Eric Chen");
    // _delay_ms(1000);
    // lcd_clear();

    // initiates all the timers
    timer1_init();
    timer2_init();

    // sets PB3 port to output for the LED
    DDRB |= (1 << PB3);

    // sets PB2 port to output for the servo motor
    DDRB |= (1 << PB2);

    //  initializes the rotary encoder turns on the pull up resistors
    PORTC |= (1 << PC4) | (1 << PC5);

    //  sets up the ISR
    PCICR |= (1 << PCIE1);
    PCMSK1 |= ((1 << PCINT9) | (1 << PCINT13));
    sei();

    unsigned char start_state = PINC;
    
    //LSB
    a = start_state & (1 << PC5);
    
    //MSB
    b = start_state & (1 << PC1);
    
    if (!b && !a)
	old_state = 0;
    else if (!b && a)
	old_state = 1;
    else if (b && !a)
	old_state = 3;
    else
	old_state = 2;

    new_state = old_state;

    // For each state, examine the two input bits to see if state
    // has changed, and if so set "new_state" to the new state,
    // and adjust the count value.

    while(1){
        if(changed){
            changed = 0;
            OCR2A = count;
            OCR1B = width;
        }
    }

}

ISR(PCINT1_vect){
    // Read the input bits and determine A and B.
    unsigned char state = PINC;
    
    //LSB
    a = state & (1 << PC5);
    
    //MSB
    b = state & (1 << PC4);

    if (old_state == 0) {

        // Handle A and B inputs for state 0
        if (!b && a){
            new_state = 1;
            if(count <= 250) count += 5; //  for LED count
            else count = 255;

            if(width <= 4500) width += 100; //  for TIMER OCR1B width
            else width = 4500;
        }
        else if (b && !a){
            new_state = 3;
            if(count >= 5) count -= 5; //  for LED count
            else count = 0;

            if(width >= 1500) width -= 100; //  for TIMER OCR1B width
            else width = 1500;
        }

    }
    else if (old_state == 1) {

        // Handle A and B inputs for state 1
        if (b && a){
            new_state = 2;
            if(count <= 250) count += 5; //  for LED count
            else count = 255;

            if(width <= 4500) width += 100; //  for TIMER OCR1B width
            else width = 4500;
        }
        else if (!b && !a){
            new_state = 0;
            if(count >= 5) count -= 5; //  for LED count
            else count = 0;

            if(width >= 1500) width -= 100; //  for TIMER OCR1B width
            else width = 1500;
        }
    }
    else if (old_state == 2) {

        // Handle A and B inputs for state 2
        if (b && !a){
            new_state = 3;
            if(count <= 250) count += 5; //  for LED count
            else count = 255;

            if(width <= 4500) width += 100; //  for TIMER OCR1B width
            else width = 4500;
        }
        else if (!b && a){
            new_state = 1;
            if(count >= 5) count -= 5;
            else count = 0;

            if(width >= 1500) width -= 100; //  for TIMER OCR1B width
            else width = 1500;
        }

    }
    else {   // old_state = 3

        // Handle A and B inputs for state 3
        if (!b && !a){
            new_state = 0;
            if(count <= 250) count += 5; //  for LED count
            else count = 255;

            if(width <= 4500) width += 100; //  for TIMER OCR1B width
            else width = 4500;
        }
        else if (b && a){
            new_state = 2;
            if(count >= 5) count -= 5; //  for LED count
            else count = 0;

            if(width >= 1500) width -= 100; //  for TIMER OCR1B width
            else width = 1500;
        }
    }

    // If state changed, update the value of old_state,
    // and set a flag that the state has changed.
    if (new_state != old_state) {
        changed = 1;
        old_state = new_state;
    }
}



