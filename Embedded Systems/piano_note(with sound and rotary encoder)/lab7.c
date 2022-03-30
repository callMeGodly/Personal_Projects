/********************************************
 *
 *  Name: Eric Chen
 *  Email: echen606@usc.edu
 *  Section: 30799 Wednesday 12:30pm
 *  Assignment: Lab 7 - Rotary Encoder
 *
 ********************************************/

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>

#include "lcd.h"

void variable_delay_us(int);
void play_note(unsigned short);

// Frequencies for natural notes from middle C (C4)
// up one octave to C5.
unsigned short frequency[8] =
    { 262, 294, 330, 349, 392, 440, 494, 523 };

//  global variables for the ISR to use
volatile unsigned char new_state, old_state;
volatile unsigned char changed = 0;  // Flag for state change
volatile int count = 0;        // Count to display
volatile unsigned char a, b;

int main(void) {

    // Initialize DDR and PORT registers and LCD
    lcd_init();
    
    //  initialize the buzzers output port
    DDRB |= (1 << PB4);
    
    //  initializes the rotary encoder turns on the pull up resistors
    PORTC |= (1 << PC1) | (1 << PC5);

    // Write a spash screen to the LCD
    lcd_moveto(0, 2);
    lcd_stringout("EE109 Lab 7");
    lcd_moveto(1, 3);
    lcd_stringout("Eric Chen");
    _delay_ms(1000);
    lcd_clear();
    
    //  sets up the ISR
    PCICR |= (1 << PCIE1);
    PCMSK1 |= ((1 << PCINT9) | (1 << PCINT13));
    sei();
    
    
    // Read the A and B inputs to determine the intial state.
    // In the state number, B is the MSB and A is the LSB.
    // Warning: Do NOT read A and B separately.  You should read BOTH inputs
    // at the same time, then determine the A and B values from that value.
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
    
    char buffer[15];
    snprintf(buffer, 15, "%d", count);
    lcd_stringout(buffer);
    lcd_moveto(0,0);

    while (1) {                 // Loop forever

        if (changed) { // Did state change?
	    changed = 0;        // Reset changed flag

	    // Output count to LCD
            char buffer[15];
            snprintf(buffer, 15, "%d        ", count);
            lcd_stringout(buffer);
            lcd_moveto(0,0);
            // Do we play a note?
            if ((count % 8) == 0) {
            // Determine which note (0-7) to play
                int note;
                if(count < 0){
                    note = -((count % 64) / 8);
                }
                else{
                    note = (count % 64) / 8;
                }
            // Find the frequency of the note
                unsigned short to_play = frequency[note];
            // Call play_note and pass it the frequency
                play_note(to_play);
            }
        }
    }
}

/*
  Play a tone at the frequency specified for one second
*/
void play_note(unsigned short freq)
{
    unsigned long period;

    period = 1000000 / freq;      // Period of note in microseconds

    while (freq--) {
	// Make PB4 high
        PORTB |= (1 << PB4);

	// Use variable_delay_us to delay for half the period
        variable_delay_us(period/2);
        
	// Make PB4 low
        PINB &= (1 << PB4);
        
	// Delay for half the period again
        variable_delay_us(period/2);
    }
}

/*
    variable_delay_us - Delay a variable number of microseconds
*/
void variable_delay_us(int delay)
{
    int i = (delay + 5) / 10;

    while (i--)
        _delay_us(10);
}

ISR(PCINT1_vect){
    // Read the input bits and determine A and B.
    unsigned char state = PINC;
    
    //LSB
    a = state & (1 << PC5);
    
    //MSB
    b = state & (1 << PC1);
    
    // For each state, examine the two input bits to see if state
    // has changed, and if so set "new_state" to the new state,
    // and adjust the count value.

    if (old_state == 0) {

        // Handle A and B inputs for state 0
        if (!b && a){
            new_state = 1;
            ++count;
        }
        else if (b && !a){
            new_state = 3;
            --count;
        }

    }
    else if (old_state == 1) {

        // Handle A and B inputs for state 1
        if (b && a){
            new_state = 2;
            ++count;
        }
        else if (!b && !a){
            new_state = 0;
            --count;
        }
    }
    else if (old_state == 2) {

        // Handle A and B inputs for state 2
        if (b && !a){
            new_state = 3;
            ++count;
        }
        else if (!b && a){
            new_state = 1;
            --count;
        }

    }
    else {   // old_state = 3

        // Handle A and B inputs for state 3
        if (!b && !a){
            new_state = 0;
            ++count;
        }
        else if (b && a){
            new_state = 2;
            --count;
        }
    }

    // If state changed, update the value of old_state,
    // and set a flag that the state has changed.
    if (new_state != old_state) {
        changed = 1;
        old_state = new_state;
    }
}
