/********************************************
 *
 *  Name: Eric Chen
 *  Email: echen606@usc.edu
 *  Section: 30799
 *  Assignment: Lab 6 - Analog-to-digital conversion
 *
 ********************************************/

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

#include "lcd.h"
#include "adc.h"

void rand_init(void);

int main(void)
{

    // Initialize the LCD
    lcd_init();

    // Initialize the ADC
    adc_init();

    // Initialize the random number function
    rand_init();

    // Write splash screen
    lcd_moveto(0, 2);
    lcd_stringout("EE109 Lab6");
    lcd_moveto(1, 3);
    lcd_stringout("Eric Chen");
    _delay_ms(500);
    lcd_clear();
    lcd_moveto(0,0);

    // Find a random initial position of the 'X'
    int position = rand() % 16;
    lcd_moveto(0, position);

    // Display the 'X' on the screen
    lcd_writedata('X');
    
    //  Sets the carat position
    int c_position = rand() % 16;
    lcd_moveto(1, c_position);
    
    // Display the '^' on the screen
    lcd_writedata('^');
    
    //  the counter for when the player wins
    int count = 0;
    

    while (1) {         // Loop forever
        unsigned char result = adc_sample(0);
        unsigned char c_result = adc_sample(3);
	
        // Check for button pressed
        if(result != 255){

            // If pressed, move 'X' to new position
            if(150 <= result && result <= 160){
                if(position){
                    position -= 1;
                    lcd_moveto(0, position+1);
                    lcd_writedata(' ');
                    lcd_moveto(0, position);
                    lcd_writedata('X');
                    _delay_ms(300);
                }
            }
            else if(0 <= result && result <= 10){
                if(position < 15){
                    position += 1;
                    lcd_moveto(0, position-1);
                    lcd_writedata(' ');
                    lcd_moveto(0, position);
                    lcd_writedata('X');
                    _delay_ms(300);
                }
            }
        }
        
        // Do a conversion of potentiometer input
        int c_prev = c_position;
        c_position = c_result / 16;
        if(c_position != c_prev){
            
            // Move '^' to new position
            lcd_moveto(1, c_prev);
            lcd_writedata(' ');
            lcd_moveto(1, c_position);
            lcd_writedata('^');
        }
        
        _delay_ms(10);
        
	// Check if '^' is aligned with 'X'
        if(c_position == position){
            if(count == 200){
                while(1){
                    lcd_moveto(0,0);
                    lcd_stringout("YOU WIN!!!");
                }
            }
            ++count;
        }
        else{
            count = 0;
        }

    }

    return 0;   /* never reached */
}

void rand_init()
{
    int seed = 0;
    unsigned char i, j, x;

    // Build a 15-bit number from the LSBs of an ADC
    // conversion of the channels 1-5, 3 times each
    for (i = 0; i < 3; i++) {
	for (j = 1; j < 6; j++) {
	    x = adc_sample(j);
	    x &= 1;	// Get the LSB of the result
	    seed = (seed << 1) + x; // Build up the 15-bit result
	}
    }
    srand(seed);	// Seed the rand function
}
