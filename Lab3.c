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
		wait(200);
		
		PORTC = PORTC & 0b11111101; //Turn on LED, PC1
		wait(200);
		PORTC = PORTC | 0b00000010; //Turn off LED, PC1
		wait(200);
		
		PORTC = PORTC & 0b11111011; //Turn on LED, PC2
		wait(200);
		PORTC = PORTC | 0b00000100; //Turn off LED, PC2
		wait(200);
		
		PORTC = PORTC & 0b11110111; //Turn on LED, PC3
		wait(200);
		PORTC = PORTC | 0b00001000; //Turn off LED, PC3
		wait(200);
		
		PORTC = PORTC & 0b11101111; //Turn on LED, PC4
		wait(200);
		PORTC = PORTC | 0b00010000; //Turn off LED, PC4
		wait(200);
		
		PORTC = PORTC & 0b11011111; //Turn on LED, PC5
		wait(200);
		PORTC = PORTC | 0b00100000; //Turn off LED, PC5
		wait(200);
		
	}
}	
		
//ISR, INT0
ISR(INT0_vect)
{
	//if button is pushed for 1st time, enter a new while loop (so while loop in here)
	int flag = 0;
	
	if(flag ==0)
	{
		PORTB = PORTB & 0b11111101; //Turn on LED 6, PB1
		wait(200);
		
		if(PINC & 0b00000100) //seeing if is LED 2 on
		{
			flag++;
			while(1)
			{
				PORTC = PORTC & 0b11110111; //Turn on LED, PC3
				wait(200);
				PORTC = PORTC | 0b00001000; //Turn off LED, PC3
				wait(200);
		
				PORTC = PORTC & 0b11101111; //Turn on LED, PC4
				wait(200);
				PORTC = PORTC | 0b00010000; //Turn off LED, PC4
				wait(200);
		
				PORTC = PORTC & 0b11011111; //Turn on LED, PC5
				wait(200);
				PORTC = PORTC | 0b00100000; //Turn off LED, PC5
				wait(200);
			}
			
		}
	}		
	
	while()
	//manipulate flags to get buttons to work and not work at different times
}

//ISR, INT1
ISR(INT1_vect)
{
	int flag2 = 0;
	
	if(flag2 == 0) //is this the 1st time switch has been pressed
	{
		
		if(PINB & 0b00000010) //seeing if LED 6 is on
		{
			
			if(PINC & 0b00100000) //seeing if LED 5 is on
			{
				flag2++;
				
				PORTB = PORTB & 0b11111011; //Turn on LED 7, PB2
				wait(3000);
				PORTB = PORTB | 0b00000100; //Turn off LED 7, PB2
				PORTC = PORTC | 0b00000001; //Turn off LED, PC0
				PORTC = PORTC | 0b00000010; //Turn off LED, PC1
				PORTC = PORTC | 0b00000100; //Turn off LED, PC2
				PORTC = PORTC | 0b00001000; //Turn off LED, PC3
				PORTC = PORTC | 0b00010000; //Turn off LED, PC4
				PORTC = PORTC | 0b00100000; //Turn off LED, PC5
				PORTB = PORTB \ 0b00000010; //Turn off LED 6, PB1
				
				flag = 0;
				flag2 = 0;
			
			}
		}
	}

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
		
	

		
