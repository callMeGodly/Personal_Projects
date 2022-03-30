#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include "trafficStates.h"

//  USE FOR ARDUINO UNO MINI LIMITED

//  BITS for different LEDS sets
#define LEDS ((1<<3) | (1<<4) | (1<<5)) //  PORTB
#define PED ((1<<2) | (1<<3)) //    PORTD


//  initial state
char state = 'r';
char isPed = 0;

int main(void) {
    
    //  sets B3 - B5 and D2 - D3 as outputs
    DDRB |= (LEDS);
    DDRD |= (PED);
    
    //  pull up resistor for ped button at C0
    PORTC |= (1 << 0);
    
    //  turns on RED light and PEDGreen Light to start sequence
    PORTB |= (1 << 3);
    PORTD |= (1 << 2);

    while(1){
        
        if(state == 'r'){   //  red light info
            if(isPed == 0) state = redState(&isPed);
            else state = pedRedState(&isPed);
        }
        else if(state == 'g'){    //  green light info
            state = greenState(&isPed);
        }
        else if(state == 'y'){   //  yellow light info
            state = yellowState();
        }
    }

    return 0;   /* never reached */
}
