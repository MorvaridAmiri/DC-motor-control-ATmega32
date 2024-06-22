/*
 * code.c
 *
 * Created: 1403/04/02 10:02:43 ق.ظ
 * Author : ALFA
 */ 

#include <avr/io.h>
#include <util/delay.h>
#define ADC_VREF_TYPE ((0<<REFS1) | (0<<REFS0) | (1<<ADLAR))

unsigned char read_adc(unsigned char adc_input)
{
	// Set the ADC input channel
	ADMUX = (adc_input | ADC_VREF_TYPE);

	// Delay for 10 microseconds to allow the ADC to stabilize
	_delay_us(10);

	// Start the ADC conversion
	ADCSRA |= (1 << ADSC);

	// Wait for the conversion to complete
	while ((ADCSRA & (1 << ADIF)) == 0);

	// Clear the ADIF flag
	ADCSRA |= (1 << ADIF);

	// Return the 8-bit ADC result
	return ADCH;
}



int main(void)
{
	DDRA=0X00;
	PORTA=0X00;
	DDRB=0X00;
	PORTB=0X00;
	DDRC=0X03;
	PORTC=0X00;
	DDRD=0X80;
	PORTD=0X00;
	
	ASSR &= ~(1 << AS2);
	TCCR2=0X62;
	TCNT2=0x00;
	OCR2=0x00;
	ADMUX=ADC_VREF_TYPE;
	;
	
	ADCSRA=0X81;
	SFIOR=(0<<ADTS2) | (0<<ADTS1) | (0<<ADTS0);

	OCR2=0;


	while (1)
	{
		OCR2=read_adc(0);
		
		if ((PINB & (1 << PINB0)) == 0)
		{
			PORTC &= ~(1 << PORTC0);
			PORTC |= (1 << PORTC1);
		}
		if ((PINB & (1 << PINB1)) == 0)
		{
			PORTC &= ~(1 << 0);
			PORTC &= ~(1 << 1);
		}



	}
}

