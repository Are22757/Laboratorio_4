/*
 * Slave1_I2C.c
 *
 * Created: 1/08/2024 17:46:40
 * Author : luisa
 */ 

#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <util/delay.h>

#include "I2C/I2C.h"

#define SlaveAddress 0x30

uint8_t buffer = 0;




int main(void)
{
   DDRD |= (1<<DDD5);
   PORTD &= ~(1<<PORTD5);
   
   I2C_Slave_Init(SlaveAddress);
   sei();
	
    while (1) 
    {
		if(buffer == 'R'){
			PORTD |= (1<<PORTD5);
			_delay_ms(1000);
			buffer = 0;
			PORTD &= ~(1<<PORTD5);  
		}
		
			
    }
}

ISR(TWI_vect){
	uint8_t estado; 
	estado = TWSR & 0xF8; 
	switch(estado){
	case 0x60:
	case 0x70:
		TWCR |= (1<<TWINT);
		break;
	case 0x80:
	case 0x90:
		buffer = TWDR; 
		TWCR |= (1<< TWINT); //Se limpia la bandera
		break;
	 default: //Se libera el bus de cualquier error
	TWCR |= (1<<TWINT)|(1<<TWSTO);	
	}
}
