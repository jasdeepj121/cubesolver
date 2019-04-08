/*
 * rubik.c
 *
 *  Created on: Mar 3, 2018
 *      Author: Jasdeep
 */

#include<avr/io.h>
#include<util/delay.h>
#include<string.h>
#include<avr/wdt.h>
#define quatrotate 48
//#define mot_delay 2.2
#define mot_delay 3
//#define servoretract 120
#define servoretract 400

#define halfrotate 96
#define scan_delay 500
#define LED_ON  PORTD|=1<<PIN6
#define LED_OFF PORTD&=~(1<<PIN6)
#define fosc 16000000

//int i,j,k,l;
unsigned char i;
//int lclaw,fclaw,bclaw,rclaw;
unsigned char clawl,clawb,clawf,clawr,clawd;
//int fvertical,lvertical,bvertical,rvertical;
unsigned char fvertical,lvertical,bvertical,rvertical;
//claw('R','');
void claw(unsigned char face,unsigned char pos){
//	1 -> c
//	0 -> o
	if(face == 'F'){
		if(pos == 'c'){
				PORTB |= 1<<PINB0;
				clawf = 1;
			}
		else {
			PORTB &=~(1<<PINB0);
			clawf = 0;
		}
	}
	else if(face == 'B'){
		if(pos == 'c'){
			PORTB |= 1<<PINB2;
			clawb = 1;
		}
		else{
			PORTB &=~(1<<PINB2);
			clawb = 0;
		}
	}
	else if(face == 'R'){
		if(pos == 'c'){
			PORTB |= 1<<PINB3;
			clawr = 1;
		}
		else{
			PORTB &=~(1<<PINB3);
			clawr = 0;
		}
	}
	else if(face == 'L'){
		if(pos == 'c'){
				PORTB |= 1<<PINB1;
				clawl = 1;
			}
			else {
				PORTB &=~(1<<PINB1);
				clawl = 0;
			}
	}
	else if(face == 'D'){
		if(pos == 'c'){
			PORTB |= 1<<PINB4;
			clawd = 1;
			}
		else {
			PORTB &=~(1<<PINB4);
			clawd = 0;
			}
	}


}

void setup(){
	DDRA = 0xFF;
	DDRB = 0xFF;
	DDRD = 0b11111110;
	PORTA = 0x00;
	PORTB = 0x00;
	PORTD = 0x00;

	//SERIAL INTERFACE SETUP
	UBRRH = 0x00;   //FOR 9600 BAUD RATE
	UBRRL = 103;		//FOR 9600 BAUD RATE
//	UBRRH = 1; 		//FOR 2400 BAUD RATE
//	UBRRL = 160;  	//FOR 2400 BAUD RATE
	UCSRB = 0x18; // enable transmitter and reciever
	UCSRC = 0x86; // set as 8 bit data, no parity bit and 1 stop bit.
	lvertical=1;
	fvertical=1;
	rvertical=1;
	bvertical=1;
//	lclaw=0;
//	fclaw=0;
//	bclaw=0;
//	rclaw=0;
	clawl=0;
	clawb=0;
	clawf=0;
	clawr=0;
	clawd=1;
	claw('F','o');
	claw('R','o');
	claw('B','o');
	claw('L','o');
	_delay_ms(servoretract);
	claw('D','c');
	_delay_ms(servoretract);
}

void motor(unsigned char mot,unsigned char dir){
	/* STEPPER MOTOR CONTROL PINS
	 * PA0 -> F STEP
	 * PA1 -> F DIR
	 * PA2 -> L STEP
	 * PA3 -> L DIR
	 * PA4 -> B STEP
	 * PA5 -> B DIR
	 * PA6 -> R STEP
	 * PA7 -> R DIR
	 */

	/*SIMULTANEOUS MOVEMENT
	 * X -> LEFT & RIGHT  MOTORS ( DIRECTION ACCORDING TO 'L' FACE)
	 * Y -> FRONT & BACK  MOTORS ( DIRECTION ACCORDING TO 'F' FACE)
	 */

	/* DIRECTION CONTROL
	 * 'C' -> clockwise
	 * 'A' -> anticlockwise
	 * 'H' -> half turn (180 degrees)
	 * 'P' -> clockwise(inverted rotation) (FOR X & Y MOTORS ONLY)
	 * 'Q' -> anticlockwise(inverted rotation) (FOR X & Y MOTORS ONLY)
	 * 'R' -> HALF TURN(inverted rotation) (FOR X & Y MOTORS ONLY)
	 */

if( mot == 'F'){
	if( dir == 'C'){
		PORTA |= (1<<PINA1);
		for(i=0;i<quatrotate;i++){
			PORTA ^= 1<<PINA0 ;
			_delay_ms(mot_delay);
		}
		if(fvertical)
			fvertical = 0;
		else
			fvertical = 1;
	}
	else if ( dir == 'A'){
		PORTA &= ~(1<<PINA1);
		for(i=0;i<quatrotate;i++){
			PORTA ^= 1<<PINA0 ;
			_delay_ms(mot_delay);
		}
		if(fvertical)
			fvertical = 0;
		else
			fvertical = 1;
	}
	else if ( dir == 'H'){
		for(i=0;i<halfrotate;i++){
			PORTA ^= 1<<PINA0 ;
			_delay_ms(mot_delay);
		}
	}
}

else if( mot == 'L'){
	if( dir == 'C'){
		PORTA |= (1<<PINA3);
		for(i=0;i<quatrotate;i++){
			PORTA ^= 1<<PINA2 ;
			_delay_ms(mot_delay);
		}
		if(lvertical)
			lvertical = 0;
		else
			lvertical = 1;
	}
	else if ( dir == 'A'){
		PORTA &= ~(1<<PINA3);
		for(i=0;i<quatrotate;i++){
			PORTA ^= 1<<PINA2 ;
			_delay_ms(mot_delay);
		}
		if(lvertical)
			lvertical = 0;
		else
			lvertical = 1;
	}
	else if ( dir == 'H'){
		for(i=0;i<(halfrotate);i++){
			PORTA ^= 1<<PINA2 ;
			_delay_ms(mot_delay);
		}
	}
}

else if( mot == 'B'){
	if( dir == 'C'){
		PORTA |= (1<<PINA5);
		for(i=0;i<quatrotate;i++){
			PORTA ^= 1<<PINA4 ;
			_delay_ms(mot_delay);
		}
		if(bvertical)
			bvertical = 0;
		else
			bvertical = 1;
	}
	else if ( dir == 'A'){
		PORTA &= ~(1<<PINA5);
		for(i=0;i<quatrotate;i++){
			PORTA ^= 1<<PINA4 ;
			_delay_ms(mot_delay);
		}
		if(bvertical)
			bvertical = 0;
		else
			bvertical = 1;
	}
	else if ( dir == 'H'){
		for(i=0;i<(halfrotate);i++){
			PORTA ^= 1<<PINA4 ;
			_delay_ms(mot_delay);
		}
	}
}

else if( mot == 'R'){
	if( dir == 'C'){
		PORTA |= (1<<PINA7);
		for(i=0;i<quatrotate;i++){
			PORTA ^= 1<<PINA6 ;
			_delay_ms(mot_delay);
		}
		if(rvertical)
			rvertical = 0;
		else
			rvertical = 1;
	}
	else if ( dir == 'A'){
		PORTA &= ~(1<<PINA7);
		for(i=0;i<quatrotate;i++){
			PORTA ^= 1<<PINA6 ;
			_delay_ms(mot_delay);
		}
		if(rvertical)
			rvertical = 0;
		else
			rvertical = 1;
	}
	else if ( dir == 'H'){
		for(i=0;i<(halfrotate);i++){
			PORTA ^= 1<<PINA6 ;
			_delay_ms(mot_delay);
		}
	}
}

else if( mot == 'X'){
	if( dir == 'C'){
		PORTA |= (1<<PINA3);
		PORTA &= ~(1<<PINA7);
		for(i=0;i<quatrotate;i++){
			PORTA ^= 1<<PINA2 ;
			PORTA ^= 1<<PINA6 ;
			_delay_ms(mot_delay);
		}
		if(rvertical)
			rvertical = 0;
		else
			rvertical = 1;

		if(lvertical)
			lvertical = 0;
		else
			lvertical = 1;
	}
	else if ( dir == 'A'){
		PORTA |= (1<<PINA7);
		PORTA &= ~(1<<PINA3);
		for(i=0;i<quatrotate;i++){
			PORTA ^= 1<<PINA2 ;
			PORTA ^= 1<<PINA6 ;
			_delay_ms(mot_delay);
		}
		if(rvertical)
			rvertical = 0;
		else
			rvertical = 1;
		if(lvertical)
			lvertical = 0;
		else
			lvertical = 1;
	}
	else if ( dir == 'H'){
		PORTA |= (1<<PINA3);
		PORTA &= ~(1<<PINA7);
		for(i=0;i<(halfrotate);i++){
			PORTA ^= 1<<PINA2 ;
			PORTA ^= 1<<PINA6 ;
			_delay_ms(mot_delay);
		}
	}
//	else if ( dir == 'P'){
//			PORTA |= (1<<PINA3);
//			PORTA &= ~(1<<PINA7);
//			for(i=0;i<(quatrotate);i++){
//				PORTA ^= 1<<PINA2 ;
//				PORTA ^= 1<<PINA6 ;
//				_delay_ms(mot_delay);
//			}
//			if(rvertical)
//				rvertical = 0;
//			else
//				rvertical = 1;
//			if(lvertical)
//				lvertical = 0;
//			else
//				lvertical = 1;
//		}
//	else if ( dir == 'Q'){
//			PORTA |= (1<<PINA7);
//			PORTA &= ~(1<<PINA3);
//			for(i=0;i<(quatrotate);i++){
//				PORTA ^= 1<<PINA2 ;
//				PORTA ^= 1<<PINA6 ;
//				_delay_ms(mot_delay);
//			}
//			if(rvertical)
//				rvertical = 0;
//			else
//				rvertical = 1;
//			if(lvertical)
//				lvertical = 0;
//			else
//				lvertical = 1;
//		}
//	else if ( dir == 'R'){
//			PORTA |= (1<<PINA3);
//			PORTA &= ~(1<<PINA7);
//			for(i=0;i<(halfrotate);i++){
//				PORTA ^= 1<<PINA2 ;
//				PORTA ^= 1<<PINA6 ;
//				_delay_ms(mot_delay);
//			}
//		}
}

else if( mot == 'Y'){
	if( dir == 'C'){
		PORTA |= (1<<PINA1);
		PORTA &= ~(1<<PINA5);
		for(i=0;i<quatrotate;i++){
			PORTA ^= 1<<PINA0 ;
			PORTA ^= 1<<PINA4 ;
			_delay_ms(mot_delay);
		}

		if(fvertical)
			fvertical = 0;
		else
			fvertical = 1;
		if(bvertical)
			bvertical = 0;
		else
			bvertical = 1;
	}
	else if ( dir == 'A'){
			PORTA |= (1<<PINA5);
			PORTA &= ~(1<<PINA1);
			for(i=0;i<quatrotate;i++){
				PORTA ^= 1<<PINA0 ;
				PORTA ^= 1<<PINA4 ;
				_delay_ms(mot_delay);
			}
			if(fvertical)
				fvertical = 0;
			else
				fvertical = 1;
			if(bvertical)
				bvertical = 0;
			else
				bvertical = 1;
		}
	else if ( dir == 'H'){
		PORTA |= (1<<PINA1);
		PORTA &= ~(1<<PINA5);
		for(i=0;i<(halfrotate);i++){
			PORTA ^= 1<<PINA0 ;
			PORTA ^= 1<<PINA4 ;
			_delay_ms(mot_delay);
		}
	}

//	else if ( dir == 'P'){
//			PORTA |= (1<<PINA1);
//			PORTA &= ~(1<<PINA5);
//			for(i=0;i<(quatrotate);i++){
//				PORTA ^= 1<<PINA0 ;
//				PORTA ^= 1<<PINA4 ;
//				_delay_ms(mot_delay);
//			}
//			if(fvertical)
//				fvertical = 0;
//			else
//				fvertical = 1;
//			if(bvertical)
//				bvertical = 0;
//			else
//				bvertical = 1;
//		}
//	else if ( dir == 'Q'){
//			PORTA |= (1<<PINA5);
//			PORTA &= ~(1<<PINA1);
//			for(i=0;i<(quatrotate);i++){
//				PORTA ^= 1<<PINA0 ;
//				PORTA ^= 1<<PINA4 ;
//				_delay_ms(mot_delay);
//			}
//			if(fvertical)
//				fvertical = 0;
//			else
//				fvertical = 1;
//			if(bvertical)
//				bvertical = 0;
//			else
//				bvertical = 1;
//		}
//	else if ( dir == 'R'){
//			PORTA |= (1<<PINA1);
//			PORTA &= ~(1<<PINA5);
//			for(i=0;i<(halfrotate);i++){
//				PORTA ^= 1<<PINA0 ;
//				PORTA ^= 1<<PINA4 ;
//				_delay_ms(mot_delay);
//			}
//		}
}
}

void sendchar_uart(char data)
{
  while ((UCSRA & 0x20) == 0x00);  // Wait until the transmit buffer is empty
  UDR = (unsigned char)data; // As soon as the buffer is empty, put the data in UDR
}

unsigned char getchar_uart(void)
{
  unsigned char data;
  while ((UCSRA & 0x80) == 0x00); // Wait for till the data arrives data
  data=UDR;	// Read the data from UDR, as soon as the data arrives
  return data;
}

//void straightfront(){
//	if(!fvertical){
//		frontclaw(0);
//		_delay_ms(servoretract);
//		motor('F','C');
//		frontclaw(1);
//		_delay_ms(servoretract);
//	}
//}
//
//void straightleft(){
//	if(!lvertical){
//		leftclaw(0);
//		_delay_ms(servoretract);
//		motor('L','C');
//		leftclaw(1);
//		_delay_ms(servoretract);
//	}
//}
//
//void straightright(){
//	if(!rvertical){
//		rightclaw(0);
//		_delay_ms(servoretract);
//		motor('R','C');
//		rightclaw(1);
//		_delay_ms(servoretract);
//	}
//}
//
//void straightback(){
//	if(!bvertical){
//		backclaw(0);
//		_delay_ms(servoretract);
//		motor('B','C');
//		backclaw(1);
//		_delay_ms(servoretract);
//	}
//}

void move_generator(char input[]){
	unsigned char x;
	for(x=0;x<strlen(input);x++){
			if(input[x] == 'F'){
				if(!lvertical && (!rvertical)){
					if(!bvertical){
						//backclaw(0);
						claw('B','o');
						_delay_ms(servoretract);
						motor('B','C');
						//backclaw(1);
						claw('B','c');
					}
					//leftclaw(0);
					claw('L','o');
//					rightclaw(0);
					claw('R','o');
					_delay_ms(servoretract);
					motor('X','H');
//					leftclaw(1);
					claw('L','c');
//					rightclaw(1);
					claw('R','c');

				}
				if(!lvertical){
					if(!bvertical){
						//backclaw(0);
						claw('B','o');
						_delay_ms(servoretract);
						motor('B','C');
						//backclaw(1);
						claw('B','c');
					}
//					frontclaw(0);
					claw('F','o');
//					leftclaw(0);
					claw('L','o');
					_delay_ms(servoretract);
					motor('L','C');
//					leftclaw(1);
					claw('L','c');
//					frontclaw(1);
					claw('F','c');
				}
				if(!rvertical){
					if(!bvertical){
						//backclaw(0);
						claw('B','o');
						_delay_ms(servoretract);
						motor('B','C');
						//backclaw(1);
						claw('B','c');
					}
//					frontclaw(0);
					claw('F','o');
//					rightclaw(0);
					claw('R','o');
					_delay_ms(servoretract);
					motor('R','C');
//					rightclaw(1);
					claw('R','c');
//					frontclaw(1);
					claw('F','c');
				}
				_delay_ms(servoretract);
				motor('F',input[x+1]);
			}

			else if (input[x] == 'L'){
				if(!fvertical && (!bvertical)){
					if(!rvertical){
//						rightclaw(0);
						claw('R','o');
						_delay_ms(servoretract);
						motor('R','C');
//						rightclaw(1);
						claw('R','c');
					}
					//backclaw(0);
					claw('B','o');
//					frontclaw(0);
					claw('F','o');
					_delay_ms(servoretract);
					motor('Y','H');
					//backclaw(1);
					claw('B','c');
//					frontclaw(1);
					claw('F','c');
					}
				if(!fvertical){
					if(!rvertical){
//						rightclaw(0);
						claw('R','o');
						_delay_ms(servoretract);
						motor('R','C');
//						rightclaw(1);
						claw('R','c');
					}
//					leftclaw(0);
					claw('L','o');
//					frontclaw(0);
					claw('F','o');
					_delay_ms(servoretract);
					motor('F','C');
//					leftclaw(1);
					claw('L','c');
//					frontclaw(1);
					claw('F','c');
				}
				if(!bvertical){
					if(!rvertical){
//						rightclaw(0);
						claw('R','o');
						_delay_ms(servoretract);
						motor('R','C');
//						rightclaw(1);
						claw('R','c');
					}
//					leftclaw(0);
					claw('L','o');
					//backclaw(0);
					claw('B','o');
					_delay_ms(servoretract);
					motor('B','C');
//					leftclaw(1);
					claw('L','c');
					//backclaw(1);
					claw('B','c');
				}
				_delay_ms(servoretract);
				motor('L',input[x+1]);
			}
			else if (input[x] == 'R'){
				if(!fvertical && (!bvertical)){
					if(!lvertical){
//						leftclaw(0);
						claw('L','o');
						_delay_ms(servoretract);
						motor('L','C');
//						leftclaw(1);
						claw('L','c');
					}
					//backclaw(0);
					claw('B','o');
//					frontclaw(0);
					claw('F','o');
					_delay_ms(servoretract);
					motor('Y','H');
					//backclaw(1);
					claw('B','c');
//					frontclaw(1);
					claw('F','c');
					}
				if(!fvertical){
					if(lvertical){
//						leftclaw(0);
						claw('L','o');
						_delay_ms(servoretract);
						motor('L','C');
//						leftclaw(1);
						claw('L','c');
					}
//					rightclaw(0);
					claw('R','o');
//					frontclaw(0);
					claw('F','o');
					_delay_ms(servoretract);
					motor('F','C');
//					rightclaw(1);
					claw('R','c');
//					frontclaw(1);
					claw('F','c');
				}
				if(!bvertical){
					if(lvertical){
//						leftclaw(0);
						claw('L','o');
						_delay_ms(servoretract);
						motor('L','C');
//						leftclaw(1);
						claw('L','c');
					}
//					rightclaw(0);
					claw('R','o');
					//backclaw(0);
					claw('B','o');
					_delay_ms(servoretract);
					motor('B','C');
//					rightclaw(1);
					claw('R','c');
					//backclaw(1);
					claw('B','c');
				}
				_delay_ms(servoretract);
				motor('R',input[x+1]);
			}
			else if(input[x] == 'B'){
				if(!lvertical && (!rvertical)){
					if(!fvertical){
//						frontclaw(0);
						claw('F','o');
						_delay_ms(servoretract);
						motor('F','C');
//						frontclaw(1);
						claw('F','c');
					}
//					leftclaw(0);
					claw('L','o');
//					rightclaw(0);
					claw('R','o');
					_delay_ms(servoretract);
					motor('X','H');
//					leftclaw(1);
					claw('L','c');
//					rightclaw(1);
					claw('R','c');
					}
				if(!lvertical){
					if(!fvertical){
//						frontclaw(0);
						claw('F','o');
						_delay_ms(servoretract);
						motor('F','C');
//						frontclaw(1);
						claw('F','c');
					}
					//backclaw(0);
					claw('B','o');
//					leftclaw(0);
					claw('L','o');
					_delay_ms(servoretract);
					motor('L','C');
//					leftclaw(1);
					claw('L','c');
					//backclaw(1);
					claw('B','c');
				}
				if(!rvertical){
					if(!fvertical){
//						frontclaw(0);
						claw('F','o');
						_delay_ms(servoretract);
						motor('F','C');
//						frontclaw(1);
						claw('F','c');
					}
					//backclaw(0);
					claw('B','o');
//					rightclaw(0);
					claw('R','o');
					_delay_ms(servoretract);
					motor('R','C');
//					rightclaw(1);
					claw('R','c');
					//backclaw(1);
					claw('B','c');
				}
				_delay_ms(servoretract);
				motor('B',input[x+1]);
			}
			else if (input[x] == 'X'){
				if(!lvertical && !rvertical && !clawl && !clawr){
					motor('X','A');
				}
				else if(!lvertical && !clawl){
//					claw('L','o');
//					_delay_ms(servoretract);
					motor('L','A');
				}
				else if(!rvertical && !clawr){
//					claw('R','o');
//					_delay_ms(servoretract);
					motor('R','A');
				}
				claw('L','c');
				claw('R','c');
				_delay_ms(servoretract);
				claw('F','o');
				claw('B','o');
				_delay_ms(servoretract);

				if(!fvertical && (!bvertical)){
//					frontclaw(0);
					claw('F','o');
					//backclaw(0);
					claw('B','o');
					_delay_ms(servoretract);
					motor('Y','C');
				}
				else if(!fvertical){
//					frontclaw(0);
					claw('F','o');
					_delay_ms(servoretract);
					motor('F','C');
				}
				else if (!bvertical){
					//backclaw(0);
					claw('B','o');
					_delay_ms(servoretract);
					motor('B','C');
				}
				_delay_ms(servoretract);
//				leftclaw(1);
				claw('L','c');
//				rightclaw(1);
				claw('R','c');
				_delay_ms(servoretract);
				motor('X',input[x+1]);
				//backclaw(1);
//				claw('B','c');
//				frontclaw(1);
//				claw('F','c');
			}
			else if (input[x] == 'Y'){
				if(!fvertical && !bvertical && !clawf && !clawb){
//					claw('F','o');
//					claw('B','o');
//					_delay_ms(servoretract);
					motor('X','A');
				}
				else if(!lvertical && !clawl){
//					claw('L','o');
//					_delay_ms(servoretract);
					motor('L','A');
				}
				else if(!rvertical && !clawr){
//					claw('R','o');
//					_delay_ms(servoretract);
					motor('R','A');
				}
				claw('F','c');
				claw('B','c');
				_delay_ms(servoretract);
				claw('R','o');
				claw('L','o');
				_delay_ms(servoretract);
				if(!lvertical && (!rvertical)){
//					leftclaw(0);
					claw('L','o');
//					rightclaw(0);
					claw('R','o');
					_delay_ms(servoretract);
					motor('X','C');
								}
				else if(!rvertical){
//					rightclaw(0);
					claw('R','o');
					_delay_ms(servoretract);
					motor('R','C');
				}
				else if (!lvertical){
//					leftclaw(0);
					claw('L','o');
					_delay_ms(servoretract);
					motor('L','C');
				}
				_delay_ms(servoretract);
//				frontclaw(1);
				claw('F','c');
				//backclaw(1);
				claw('B','c');
				_delay_ms(servoretract);
				motor('Y',input[x+1]);
//				rightclaw(1);
//				claw('R','c');
//				leftclaw(1);
//				claw('L','c');
			}
	}
}

void enable_stepper(){
	PORTD &= ~(1<<PIND7);
	_delay_ms(10);
}

void disable_stepper(){
	_delay_ms(10);
	PORTD |= 1<<PIND7;
}

void reset(){
	wdt_enable(WDTO_15MS);
	  while(1) {
	  }
}

void scan_cube(){
	LED_ON ;
	_delay_ms(500);
	claw('R','o');
	claw('L','o');
	_delay_ms(servoretract);

	_delay_ms(50);
	if(getchar_uart()=='n'){
		PORTD |= 1<<PIN6; // TURN LED ON
		sendchar_uart('z');
		//scanB
	}

	if(getchar_uart()=='n'){
		move_generator("YA");
		sendchar_uart('z');
		//scanL
	}

	if(getchar_uart()=='n'){
		move_generator("YA");
		sendchar_uart('z');
		//scanF
	}

	if(getchar_uart()=='n'){
		move_generator("YA");
		sendchar_uart('z');
		//scanR
	}

	if(getchar_uart()=='n'){

//		claw('F','o');
//		claw('B','o');
//		claw('R','c');
//		claw('L','c');
//		_delay_ms(servoretract);
		move_generator("XC");
		sendchar_uart('z');
		//scanU
	}

	if(getchar_uart()=='n'){
		move_generator("XH");
		sendchar_uart('z');
		//scanD
	}

	if(getchar_uart()=='n'){
		move_generator("XC");
//		claw('F','c');
//		claw('B','c');
//		claw('R','o');
//		claw('L','o');
//		_delay_ms(servoretract);
		move_generator("YC");
		sendchar_uart('z');
		PORTD &= ~(1<<PIN6); //TURN LED OFF
	}

//	claw('F','c');
//	claw('B','c');
//	claw('R','c');
//	claw('L','c');
//	_delay_ms(servoretract);
	LED_OFF;
}

int main(){

	setup();
	disable_stepper();
	int cnt;
	unsigned char first;
//	unsigned char c;
	char inp_str[100],chr;
	while(1){
		for(cnt=0;cnt<100;cnt++)
			inp_str[cnt] = '\0';
		first = getchar_uart();
		if(first == 's'){
			claw('F','c');
			claw('B','c');
			claw('R','c');
			claw('L','c');
			_delay_ms(servoretract);
			claw('D','o');
			_delay_ms(servoretract);
			enable_stepper();
			scan_cube();
			disable_stepper();
			sendchar_uart('b');
			_delay_ms(50);
		}
		else{
			inp_str[0] = first;
			cnt=1;
			do{
				chr = (char)getchar_uart();
				inp_str[cnt] = chr;
				cnt++;
			}while(inp_str[cnt-1] != 'e' && cnt < 100);
			enable_stepper();

			claw('F','c');
			claw('B','c');
			claw('R','c');
			claw('L','c');
			_delay_ms(servoretract);
			claw('D','o');
			_delay_ms(servoretract);
			move_generator(inp_str);
			disable_stepper();
			sendchar_uart('d');
			claw('D','c');
			_delay_ms(servoretract);
			claw('F','o');
			claw('R','o');
			claw('B','o');
			claw('L','o');
			reset();
		}
	}

return 0;
}
