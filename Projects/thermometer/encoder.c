#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include "encoder.h"
#include "project.h"

void encoder_init(){
    // sets up the rotary encoder
    unsigned char start_state = PIND;
    changed = 0;
    
    //LSB
    b = start_state & (1 << PD3);
    
    //MSB
    a = start_state & (1 << PD2);
    
    if (!b && !a)
	old_state = 0;
    else if (!b && a)
	old_state = 1;
    else if (b && !a)
	old_state = 3;
    else
	old_state = 2;

    new_state = old_state;
}

ISR(PCINT2_vect){ // Rotary Encoder ISR
    // Read the input bits and determine A and B.
    unsigned char state = PIND;
    
    //LSB
    a = state & (1 << PD3);
    
    //MSB
    b = state & (1 << PD2);

    if (old_state == 0) {

        // Handle A and B inputs for state 0
        if (!b && a){
            new_state = 1;
            if(threshold < 90) threshold += 1; //   increase temperature threshold

        }
        else if (b && !a){
            new_state = 3;
            if(threshold > 50) threshold -= 1; //  decrease temperature threshold
        }

    }
    else if (old_state == 1) {

        // Handle A and B inputs for state 1
        if (b && a){
            new_state = 2;
            if(threshold < 90) threshold += 1; //   increase temperature threshold
        }
        else if (!b && !a){
            new_state = 0;
            if(threshold > 50) threshold -= 1; //  decrease temperature threshold
        }
    }
    else if (old_state == 2) {

        // Handle A and B inputs for state 2
        if (b && !a){
            new_state = 3;
            if(threshold < 90) threshold += 1; //   increase temperature threshold
        }
        else if (!b && a){
            new_state = 1;
            if(threshold > 50) threshold -= 1; //  decrease temperature threshold
        }

    }
    else {   // old_state = 3

        // Handle A and B inputs for state 3
        if (!b && !a){
            new_state = 0;
            if(threshold < 90) threshold += 1; //   increase temperature threshold
        }
        else if (b && a){
            new_state = 2;
            if(threshold > 50) threshold -= 1; //  decrease temperature threshold
        }
    }

    // If state changed, update the value of old_state,
    // and set a flag that the state has changed.
    if (new_state != old_state) {
        changed = 1;
        eeprom_update_byte((void *) 100, threshold);
        old_state = new_state;
    }
}