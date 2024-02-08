// Jack Berkowitz
// Lab 3, Mechatronics
// 2/5/24 


#include <avr/io.h>
#include <avr/interrupt.h>

void wait(volatile int);


int main(void)
{
	DDRD = 0b00000000; //data register, all Port D pins set as inputs (includes PD2 & PD3 set as input for interrupts)
	DDRC = 0b00111111; //data register, pins PCO-PC5 set as output for LEDs
	DDRB = 0b00000110; //data register, pins PB1 & PB2 set as output for LEDs
	PORTC = 0b00111111; //setting output of PORTC high to turn off LEDs (assuming wired as active low)
	PORTB = 0b00000110; //setting output of PORTB high to turn off LEDs (assuming wired as active low)
	
	
	//Set Up Interrupts
	EICRA = 0b00001010; //Trigger INT0 & INT1 on Falling Edge
	EIMSK = 0b00000011; //Enable INTO & INT1
	sei(); //Enable Global Interrupt
	
	
	while(1)
	{
		
		PORTC = PORTC & 0b11111110; //Turn on LED, PCO
		wait(200);
		PORTC = PORTC | 0b00000001; //Turn off LED, PC0
		
		PORTC = PORTC & 0b11111101; //Turn on LED, PC1
		wait(200);
		PORTC = PORTC | 0b00000010; //Turn off LED, PC1
		
		PORTC = PORTC & 0b11111011; //Turn on LED, PC2
		wait(200);
		PORTC = PORTC | 0b00000100; //Turn off LED, PC2
		
		PORTC = PORTC & 0b11110111; //Turn on LED, PC3
		wait(200);
		PORTC = PORTC | 0b00001000; //Turn off LED, PC3
		
		PORTC = PORTC & 0b11101111; //Turn on LED, PC4
		wait(200);
		PORTC = PORTC | 0b00010000; //Turn off LED, PC4
		
		PORTC = PORTC & 0b11011111; //Turn on LED, PC5
		wait(200);
		PORTC = PORTC | 0b00100000; //Turn off LED, PC5
		
	}
}	
		
//ISR, INT0
ISR(INT0_vect) //entered if Switch 0 is turned on
{
	int flag = 0;
	wait(50); //switch debounce
	
	if(flag == 0)
	{
		if(PINC & 0b11111011) //seeing if is LED 2 on
		{
			PORTB = PORTB & 0b11111101; //Turn on LED 6, PB1
			wait(200);
			
			flag++;
			
			PORTC = PORTC | 0b00000100; //Turn off LED, PC2
			wait(200);
			
			while(1)
			{
				PORTC = PORTC & 0b11110111; //Turn on LED, PC3
				wait(200);
				PORTC = PORTC | 0b00001000; //Turn off LED, PC3
		
				PORTC = PORTC & 0b11101111; //Turn on LED, PC4
				wait(200);
				PORTC = PORTC | 0b00010000; //Turn off LED, PC4
		
				PORTC = PORTC & 0b11011111; //Turn on LED, PC5
				wait(200);
				PORTC = PORTC | 0b00100000; //Turn off LED, PC5
			}	
		}
	}
	
	EIFR = 0b00000001;	//clear the INT0 flag	
}

//ISR, INT1
ISR(INT1_vect) //entered if Switch 1 is turned on
{
	wait(50); //switch debounce
	
	if(PINB & 0b11111101) //seeing if LED 6 is on
	{
			
		if(PINC & 0b11011111) //seeing if LED 5 is on
		{
				
			PORTB = PORTB & 0b11111011; //Turn on LED 7, PB2
			wait(3000);
			PORTB = PORTB | 0b00000100; //Turn off LED 7, PB2
			PORTC = PORTC | 0b00000001; //Turn off LED, PC0
			PORTC = PORTC | 0b00000010; //Turn off LED, PC1
			PORTC = PORTC | 0b00000100; //Turn off LED, PC2
			PORTC = PORTC | 0b00001000; //Turn off LED, PC3
			PORTC = PORTC | 0b00010000; //Turn off LED, PC4
			PORTC = PORTC | 0b00100000; //Turn off LED, PC5
			PORTB = PORTB | 0b00000010; //Turn off LED 6, PB1
				
		}
	}
	
	EIFR = 0b00000010;	//Clear the INT1 flag
}

void wait(volatile int multiple)
{
	while(multiple > 0)
	{
		TCCR0A = 0x00;
		TCNT0 = 0;
		TCCR0B = 0b00000011;
		while(TCNT0 < 0xFA);
		TCCR0B = 0x00;
		multiple--;
	}
}
		
	

		
