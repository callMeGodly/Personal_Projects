/********************************************
*
*  Name: Eric Chen
*  Email: echen606@usc.edu
*  Lab section: 30799
*  Assignment: Lab 3 - Arduino Input and Output
*
********************************************/

#include <avr/io.h>
#include <util/delay.h>

#define DOT_LENGTH  250        /* Define the length of a "dot" time in msec */
#define DASH_DELAY 3

void dot(void);
void dash(void);
void makeOutput(char);
char checkInput(char);

int main(void)
{

    // Initialize appropriate DDR registers
    DDRD |= (1 << 3);
    DDRB = 0x00;
	
    // Initialize the LED output to 0
    PORTD = 0x00;
    
	
    // Enable the pull-up resistors for the 
    // 3 button inputs
    PORTB = (7 << 3);
	

    // Loop forever
    while (1) {                 
    
	//  Use if statements and the checkInput()
	//  function to determine if a button
	//  is being pressed and then output
	//  the correct dot/dash sequence by
	//  calling the dot(), dash(), and 
	//  using appropriate delay functions
        
        //for U
        if(checkInput(3)){
            dot();
            dot();
            dash();
            _delay_ms(DASH_DELAY * DOT_LENGTH);
        }
        //for S
        else if(checkInput(4)){
            dot();
            dot();
            dot();
            _delay_ms(DASH_DELAY * DOT_LENGTH);
        }
        //for C
        else if(checkInput(5)){
            dash();
            dot();
            dash();
            dot();
            _delay_ms(DASH_DELAY * DOT_LENGTH);
        }
    }

    return 0;   /* never reached */
}

/*
  dot() - Makes the output LED blink a "dot".

  Write code to generate a dot by using the makeOutput function
  to turn the output ON and OFF with appropriate delays.
  Be sure you don't forget to also delay an
  appropriate time after you turn the output off
*/
void dot()
{
    //turns on then delay
    makeOutput(1);
    _delay_ms(DOT_LENGTH);
    //turns off then delay
    makeOutput(0);
    _delay_ms(DOT_LENGTH);
}

/*
  dash() - Makes the output LED blink a "dash".

  Write code to generate a dash by using the makeOutput function
  to turn the output ON and OFF with appropriate delays.
  Be sure you don't forget to also delay
  appropriate time after you turn the output off
*/
void dash()
{
    //turns on then delay
    makeOutput(1);
    _delay_ms(DASH_DELAY * DOT_LENGTH);
    //turns off then delay
    makeOutput(0);
    _delay_ms(DOT_LENGTH);
}

/*
  makeOutput() - Changes the output bit to either a zero 
  or one, based on the input argument "value".
  
  If the argument is zero, turn the output OFF,
  otherwise turn the output ON. 
  
  Do not use any delays here.  Just use bit-wise operations
  to make the appropriate PORT bit turn on or off.
*/
void makeOutput(char value)
{
    //turns the led on if value is given as 1
    if(value) PORTD |= (1 << 2);
    //turns the led off by changing only bit 2 in PORTD
    else PORTD &= ~(1 << 2);

}

/*
  checkInput(bit) - Checks the state of the input bit specified by the
  "bit" argument (0-7), and returns either 0 or 1 depending on its state.
  
  Write code to use the appropriate group's PIN register and determine if  
  the specified bit (which is passed as the argument) of that group is
  pressed or not.  Think carefully about what bit value means "pressed"
  when connected to a pushbutton.
 */
char checkInput(char bit)
{
    //since button pressed is logic 0, we need to check if such
    //pin in PINB is 0
    if((PINB & (1 << bit)) == 0x00) return 1;
    else return 0;
}
