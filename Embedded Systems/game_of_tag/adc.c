#include <avr/io.h>

#include "adc.h"


void adc_init(void)
{
    // Initialize the ADC
    ADMUX &= ~(1 << REFS1);
    ADMUX |= (1 << REFS0);
    ADMUX |= (1 << ADLAR);
    ADCSRA |= (1 << ADPS2);
    ADCSRA |= (1 << ADPS1);
    ADCSRA |= (1 << ADPS0);
    ADCSRA |= (1 << ADEN);

}

unsigned char adc_sample(unsigned char channel)
{
    // Set ADC input mux bits to 'channel' value
    ADMUX &= ~(0x0f);
    ADMUX |= channel;
    
    // Convert an analog input and return the 8-bit result
    
    ADCSRA |= (1 << ADSC);
    while((ADCSRA & (1 << ADSC)) != 0){
        
    }
    
    return ADCH;
}
