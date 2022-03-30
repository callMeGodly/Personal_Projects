/********************************************
*
*  Name: Eric Chen
*  Email: echen606@usc.edu
*  Section: 30799
*  Assignment: Lab 4 - Up/Down counter on LCD display
*
********************************************/

#include <avr/io.h>
#include <util/delay.h>

#include "lcd.h"

enum states { UP, DOWN };

int main(void) {

    // Setup DDR and PORT bits for the 2 input buttons as necessary
    
    //Ensures the two buttons are being seen as inputs
    DDRC &= ~(0X14);
    
    //Ensures the internal pull up resistors are being used
    PORTC |= 0X14;

    // Initialize the LCD
    lcd_init();


    // Use a state machine approach to organize your code
    //   - Declare and initialize a variable to track what state you
    //     are in by assigning the values UP or DOWN to that variable.

    // initialize counter, the state, timer to do parallel work
    char count = '0';
    char state = UP;
    char timer = 0;
    
    
    while (1) {  // Loop forever
        
        //  adds up the timer, when the timer hits 15 then the led displays
        //  needs this so the button can get checked in 50ms.
        timer++;
        
        //  checks what state the machine is in
        //  if PC2 is pressed, state turns UP
        //  if PC4 is pressed, state turns DOWN
        if(!(PINC & (1 << 2))){
            state = UP;
        }
        else if(!(PINC & (1 << 4))){
            state = DOWN;
        }
        
        //  Sets the cursor to always the first row first column
        //  Writes the data to the LCD display
        lcd_moveto(0,0);
        lcd_writedata(count);
        
        //  If the state is UP and its time to increment
        //  increment the counter and wrap if at one more than 9
        if(state == UP && timer == 15){
            count++;
            if(count == '9' + 1){
                count = '0';
            }
            
            //resets the timer to count again
            timer = 0;
        }
        else if(state == DOWN && timer == 15){ // If the state is DOWN and its time to decrement
                                               // decrement the counter and wrap if one less than 0
            count--;
            if(count == '0' - 1){
                count = '9';
            }
            
            //resets the timer to count again
            timer = 0;
        }
        
        //  gives a delay so numbers won't be flying
        //  and gives time to press a different button
        _delay_ms(50);
         

    }

    return 0;   /* never reached */
}

