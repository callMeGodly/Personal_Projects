/********************************************
*
*  Name: Eric Chen
*  Email: echen606@usc.edu
*  Section: 30799
*  Assignment: Lab 5 - Combination Lock
*
********************************************/

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#include "lcd.h"

enum states { S0, S1, S2, S3, S4, S5 };

int main(void) {

    /* Call lcd_init to set up the LCD */
    lcd_init();

    /* Call lcd_stringout to print out your name */
    lcd_stringout("Eric Chen");

    /* Use snprintf to create a string with your birthdate */
    char buffer[17];
    int month = 5;
    int day = 6;
    int year = 2002;
    snprintf(buffer, 17, "%02d/%02d/%d", month, day, year);

    /* Use lcd_moveto to start at an appropriate column 
       in the bottom row to appear centered */
    lcd_moveto(1,2);

    /* Use lcd_stringout to print the birthdate string */
    lcd_stringout(buffer);
    
    /* Delay 1 second */
    _delay_ms(1000);
    
    //resets the LED for second task
    lcd_init();
    
    //Ensures the two buttons are being seen as inputs
    DDRC &= ~(0X14);
    
    //Ensures the internal pull up resistors are being used
    PORTC |= 0X14;
    
    //sets the initial state and buffer to display state
    char state = S0;
    int count = 0;
    char buff[17];
    
    // sets the timer if not pressed goes back to initial state
    int time = 0;
    
    // helper function to debounce a button press
    char pcPressed()
    {
        char pressed = (PINC & 0x14);
        // if B button is pressed, debounce then send it
        if(((pressed & (1<<4)) == 0) && ((pressed & (1<<2)) != 0)){
            _delay_ms(5);
            while( (PINC & 0x10) == 0 ) { }
            _delay_ms(5);
            return 'B';
        }
        // if A button is pressed, debounce then send it
        else if(((pressed & (1<<2)) == 0) && ((pressed & (1<<4)) != 0)){
            _delay_ms(5);
            while( (PINC & 0x04) == 0 ) { }
            _delay_ms(5);
            return 'A';
        }
        else return 0;
    }
    
    while(1)
    {
        
        // used for debugging to see if presses give correct states
        snprintf(buff, 17, "State: S%d", count);
        lcd_moveto(0,0);
        lcd_stringout(buff);
        
        // controls the LED to display whether the lock is solved
        if(state == S5){
            lcd_moveto(1,0);
            lcd_stringout("Status: Unlocked");
        }
        else{
            lcd_moveto(1,0);
            lcd_stringout("Status:   Locked");
        }
        
        // need to implement a onetime button input checker
        char press = pcPressed();
        while(!press){
            press = pcPressed();
            
            // if idle for 3 seconds, reset to initial state
            // the the time times the delay might not end up to be 3000ms
            // but using a stop watch this is the correct number of increments
            // this may be due to other delays in processing code above
            if(time == 48){ // time == 60 represents 3 secs in code but 48 is the actual count 3 seconds go by
                state = S0;
                count = 0;
                break;
            }
            
            // adds the time and delays in 50 increments
            ++time;
            _delay_ms(50);
        }
        
        // conditions for S0
        if(state == S0){
            if(press == 'B'){
                ++count;
                state = S1;
                time = 0;
            }
            else{ // stays at state S0 when A is pressed
                time = 0;
            }
        }
        // conditions for S1
        else if(state == S1){
            if(press == 'A'){
                ++count;
                state = S2;
                time = 0;
            }
            else{ // stays at state S1 when B is pressed
                state = S1;
                count = 1;
                time = 0;
            }
        }
        // conditions for S2
        else if(state == S2){
            if(press == 'B'){
                ++count;
                state = S3;
                time = 0;
            }
            else{ // returns to state S0 when A is pressed
                state = S0;
                count = 0;
                time = 0;
            }
        }
        // conditions for S3
        else if(state == S3){
            if(press == 'B'){
                ++count;
                state = S4;
                time = 0;
            }
            else{ // returns to state S2 when A is pressed
                state = S2;
                count = 2;
                time = 0;
            }
        }
        // conditions for S4
        else if(state == S4){
            if(press == 'A'){
                ++count;
                state = S5;
                time = 0;
            }
            else{ // returns to state S1 when B is pressed
                state = S1;
                count = 1;
                time = 0;
            }
        }
        // conditions for S5
        else if(state == S5){
            if(press){ // if any button is presssed it resets to 0
                state = S1;
                count = 1;
                time = 0;
            }
        }
    }

    return 0;   /* never reached */
}
