#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "project.h"
#include "serial.h"

#define FOSC 16000000
#define BAUD 9600
#define MYUBRR (FOSC/16/BAUD-1)

void serial_init(){
    
    UCSR0B |= ((1 << TXEN0) | (1 << RXEN0)); // Enable RX and TX
    UCSR0C = (3 << UCSZ00); // Async., no parity,
                            // 1 stop bit, 8 data bits

    UBRR0 = MYUBRR;
}

// helper function for transmitting tx
void tx_helper(short int c){
    
    char to_send[7];
    if(c >= 0) snprintf(to_send, 7, "@+%d#", c);
    else snprintf(to_send, 7, "@%d#", c);
    int i = 0;
    while(to_send[i] != '\0'){
        tx_char(to_send[i]);
        ++i;
    }
}

void tx_char(char ch){
    
    // wait for transmitter data register empty
    while((UCSR0A & (1<<UDRE0)) == 0){}
    UDR0 = ch;
}

ISR(USART_RX_vect){ // interrupt for RX receiving data
    char something = UDR0;
    if(begin){
        if((placement == 0) && (something == '+' || something == '-')){ // checks if sign is the first
            receive_buffer[placement] = something;
            ++placement;
        }
        else if((something == '#') && (placement >= 1)){ // if placement less than 1 then no temperature no terminating affect
            is_complete = 1;
            begin = 0;
        }
        else if(placement >= 1 && placement < 4){ // numbers can only be between placements 1 and 4
            int test = something - '0'; // uses ascii inequality to check if sent character is 0-9 or null
            if(test >= 0 && test < 10){
                receive_buffer[placement] = something;
                ++placement;
            }
            else{
                begin = 0;
            }
        }
        else{
            begin = 0;
        }
    }
    else if(something == '@'){
        begin = 1;
        for(int i = 0; i < 4; ++i){ // resets the buffer to all null character
            receive_buffer[i] = '\0';
        }
        placement = 0;
    }
}