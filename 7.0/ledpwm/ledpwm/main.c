 #define F_CPU 1000000
 #include <avr/io.h>
 #include <stdlib.h>
 #include <avr/interrupt.h>
 #include <util/delay.h>

 int main(void)
	{
	DDRD |= 0xFF;
	TCCR1A |= 1<<COM1A1 | 1<<WGM11; 
	TCCR1B |= 1<<WGM12 | 1<<WGM13 | 1<<CS10;
	ICR1 = 9999;
	sei();
	ADMUX |= 1<<ADLAR;
	ADMUX |= 1<<REFS0;
	ADCSRA |= 1<<ADIE;
	ADCSRA |= 1<<ADEN;
	ADMUX |= 1<<MUX0;
	ADCSRA |= 1<< ADSC;
	while (1)
		{
			
		}
	return 0;
	}

ISR (ADC_vect)
	{
		OCR1A = 10000/256*ADCH;
		ADCSRA |=1<<ADSC;
	}




