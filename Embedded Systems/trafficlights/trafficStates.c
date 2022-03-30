#include <avr/io.h>
#include <util/delay.h>
#include "trafficStates.h"


//  definitions for all LEDs and button
#define PEDG (1<<2)
#define PEDR (1<<3)
#define RED (1<<3)
#define YELLOW (1<<4)
#define GREEN (1<<5)
#define BUTTON (1<<0)

//  delay times for Pedstrian Safety
double delay_red_to_green = 3.5;
double delay_green_to_red = 2.0;

//  custom time and message
char* red_msg = "DONT PASS!\0";
int red_time = 20;
int yellow_time = 3;
char* green_msg = "PASS NOW!\0";
int green_time = 35;


char pedRedState(char* ped){
    
    //  Pedestrian Red State initialization
    *ped = 0;
    PORTB |= RED;
    
    //  changes PED light from red to green, also checks button
    double time = 0;
    while(time != delay_red_to_green * 20){
        if(*ped == 0 && ((PINC & BUTTON) == 0)) *ped = 1;
        _delay_ms(50);
        ++time;
    }
    PORTD &= ~(PEDR);
    PORTD |= PEDG;
    
    //  Pedestrian Red State button check and countdown
    time = 0;
    while(time != (red_time - delay_red_to_green - delay_green_to_red) * 20){
        if(*ped == 0 && ((PINC & BUTTON) == 0)) *ped = 1;
        if(time >= 270){
            PIND = PEDG;
            _delay_ms(100);
        }
        _delay_ms(50);
        ++time;
    }
    
    time = 0;
    PORTD &= ~(PEDG);
    PIND = PEDR;
    //  changes PED light from green to red, also checks button
    while(time != delay_green_to_red * 20){
        if(*ped == 0 && ((PINC & BUTTON) == 0)) *ped = 1;
        _delay_ms(50);
        ++time;
    }
    PINB = (RED);
    return 'g';
}


char redState(char* ped){
    
    //  Red State initialization
    *ped = 0;
    PORTB |= RED;
    PORTD &= ~(PEDG);
    PORTD |= PEDR;
    //lcd_stringout(red_msg);
    
    //  Red State button check and countdown
    int time = 0;
    while(time != red_time * 20){
        if(*ped == 0 && ((PINC & BUTTON) == 0)) *ped = 1;
        _delay_ms(50);
        ++time;
    }
    
    PINB = RED;
    return 'g';
}


char greenState(char* ped){
    
    //  Green State initialization
    //lcd_stringout(green_msg);
    PINB = GREEN;
    
    //  Green State button check and countdown
    int time = 0;
    while(time != green_time * 20){
        if(*ped == 0 && ((PINC & BUTTON) == 0)) *ped = 1;
        _delay_ms(50);
        ++time;
    }
    
    PINB = GREEN;
    return 'y';
}


char yellowState(char* ped){

    //  Yellow State initialization
    //lcd_stringout(yellow_msg);
    PINB = YELLOW;
    
    //  Yellow State countdown
    int time = 0;
    while(time != yellow_time * 20){
        _delay_ms(50);
        ++time;
    }
    
    PINB = YELLOW;
    return 'r';
}


