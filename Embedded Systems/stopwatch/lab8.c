/********************************************
 *
 *  Name: Eric Chen
 *  Email: echen606@usc.edu
 *  Section: 30799
 *  Assignment: Lab 8 - Digital Stopwatch
 *
 ********************************************/

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include <avr/interrupt.h>

#include "lcd.h"
#include "adc.h"

enum state {start,stop};
enum buttons {nothing, up, down};

volatile unsigned tenths = 0;
unsigned int front = 0;
char state = stop;
char b_state = nothing;

//  sets the timer module, uses 256 to slow down the clock speed
void init_timer1(unsigned short m){
    TCCR1B |= (1 << WGM12);
    TIMSK1 |= (1 << OCIE1A);
    OCR1A = m;
    TCCR1B |= (1 << CS12);
}

void reset(){ // calls when the program starts so user needs to hit start button to start
              // reset also is used when first stop then lap is pushed
    
    lcd_moveto(0,0);
    lcd_stringout(" 0.0");
    
    front = 0;
    tenths = 0;
    b_state = nothing;
    
    while(1){   //  until the start is pushed nothing happens
        unsigned char result = adc_sample(0);
        if(41 <= result && result <= 61){
            while(41 <= result && result <= 61) {
                result = adc_sample(0);
            }
            break;
        }
    }
    state = start;
    sei();
}

int main()
{
    
    // Initialize the LCD
    lcd_init();

    // Initialize the ADC
    adc_init();
    
    // Initialize the timer
    init_timer1(6250);
    
    char buffer[5];
    
    // Write a spash screen to the LCD
    lcd_moveto(0, 2);
    lcd_stringout("EE109 Lab 8");
    lcd_moveto(1, 3);
    lcd_stringout("Eric Chen");
    _delay_ms(1000);
    lcd_clear();
    
    reset();
    
    while (1) {         // Loop forever
        
        //  formatting the time
        if(tenths == 10){
            ++front;
            tenths  = 0;
        }
        if(front == 60) front = 0;
        
        //  updating the lcd based on time
        if(front < 10) snprintf(buffer, 5, " %d.%d", front,tenths);
        else snprintf(buffer, 5, "%d.%d", front,tenths );
        if(state == start){ //  if off the timer screen won't be updating but internally the time can still update
            lcd_moveto(0,0);
            lcd_stringout(buffer);
        }
        
        unsigned char result = adc_sample(0);
        if(41 <= result && result <= 61){
            while(41 <= result && result <= 61) { //    debouncing button
                result = adc_sample(0);
            }
            if(b_state == down){ //    if lap is pressed, lcd can now update
                state = start;
                b_state = nothing;
            }
            else if(b_state == nothing){ //  if the state is nothing then stop is pressed
                state = stop;
                cli();
                b_state = up;
            }
            else if(b_state == up){ //  if the state is stop then start is pressed
                state = start;
                sei();
                b_state = nothing;
            }
        }
       else if(92 <= result && result <= 112){
           while(92 <= result && result <= 112){ //     debouncing button
                result = adc_sample(0);
           }
           if(b_state == up){ //    if stop is pressed then reset is pressed
               reset();
           }
           else if(b_state == nothing){ //  if nothing is pressed then lap is pressed, internal timer not stopped, but lcd cant update
                state = stop;
                b_state = down;
           }
           else if(b_state == down){ // if lap is pressed, lcd can now update
               state = start;
               b_state = nothing;
           }
       }
    }
    return 0;   /* never reached */
}

    

ISR(TIMER1_COMPA_vect){
    ++tenths;
}
