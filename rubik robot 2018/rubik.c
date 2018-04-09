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
#define quatrotate 50 // ((360/1.8)/4)
#define mot_delay 4
#define servoretract 500
#define halfrotate 100
#define scan_delay 500
#define fosc 16000000

int i,j,k,l;
int lclaw,fclaw,bclaw,rclaw;
int fvertical,lvertical,bvertical,rvertical;

void frontclaw(int pos){
	if(pos == 1){
		PORTB |= 1<<PINB0;
		fclaw =1;
	}
	else if(pos == 0){
		PORTB &=~(1<<PINB0);
		fclaw =0;
	}
}

void leftclaw(int pos){
	if(pos == 1){
		PORTB |= 1<<PINB1;
		lclaw =1;
	}
	else if(pos == 0){
		PORTB &=~(1<<PINB1);
		lclaw =0;
	}
}

void backclaw(int pos){
	if(pos == 1){
		PORTB |= 1<<PINB2;
		bclaw =1;
	}
	else if(pos == 0){
		PORTB &=~(1<<PINB2);
		bclaw =0;
	}
}

void rightclaw(int pos){
	if(pos == 1){
		PORTB |= 1<<PINB3;
		rclaw =1;
	}
	else if(pos == 0){
		PORTB &=~(1<<PINB3);
		rclaw =0;
	}
}
void setup(){
	DDRA = 0xFF;
	DDRB = 0xFF;
//	DDRD |= 1<< PIND7;
	DDRD = 0b11111110;
	PORTA = 0x00;
	PORTB = 0x00;


	//SERIAL INTERFACE SETUP
//	UBRRH = 0x00;   //FOR 9600 BAUD RATE
//	UBRRL = 103		//FOR 9600 BAUD RATE
	UBRRH = 1; 		//FOR 2400 BAUD RATE
	UBRRL = 160;  	//FOR 2400 BAUD RATE
//	UBRRH = 0; 		//FOR 250000 BAUD RATE
//	UBRRL = 3;  	//FOR 250000 BAUD RATE


	UCSRB = 0x18; // enable transmitter and reciever
	UCSRC = 0x86; // set as 8 bit data, no parity bit and 1 stop bit.
	lvertical =1;
	fvertical =1;
	rvertical =1;
	bvertical =1;
	lclaw=0;
	fclaw=0;
	bclaw=0;
	rclaw=0;
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
	 * 'P' -> clockwise (FOR X & Y MOTORS ONLY)
	 * 'Q' -> anticlockwise (FOR X & Y MOTORS ONLY)
	 * 'R' -> HALF TURN (FOR X & Y MOTORS ONLY)
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
	else if ( dir == 'P'){
			PORTA |= (1<<PINA3);
			PORTA &= ~(1<<PINA7);
			for(i=0;i<(quatrotate*2);i++){
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
	else if ( dir == 'Q'){
			PORTA |= (1<<PINA7);
			PORTA &= ~(1<<PINA3);
			for(i=0;i<(quatrotate*2);i++){
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
	else if ( dir == 'R'){
			PORTA |= (1<<PINA3);
			PORTA &= ~(1<<PINA7);
			for(i=0;i<(quatrotate*2);i++){
				PORTA ^= 1<<PINA2 ;
				PORTA ^= 1<<PINA6 ;
				_delay_ms(mot_delay);
			}
		}
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

	else if ( dir == 'P'){
			PORTA |= (1<<PINA1);
			PORTA &= ~(1<<PINA5);
			for(i=0;i<(halfrotate);i++){
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
	else if ( dir == 'Q'){
			PORTA |= (1<<PINA5);
			PORTA &= ~(1<<PINA1);
			for(i=0;i<(halfrotate);i++){
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
	else if ( dir == 'R'){
			PORTA |= (1<<PINA1);
			PORTA &= ~(1<<PINA5);
			for(i=0;i<(halfrotate);i++){
				PORTA ^= 1<<PINA0 ;
				PORTA ^= 1<<PINA4 ;
				_delay_ms(mot_delay);
			}
		}
}
}

void sendchar_uart(unsigned char data)
{
  while ((UCSRA & 0x20) == 0x00);  // Wait until the transmit buffer is empty
  UDR = data; // As soon as the buffer is empty, put the data in UDR
}

unsigned char getchar_uart(void)
{
  unsigned char data;
  while ((UCSRA & 0x80) == 0x00); // Wait for till the data arrives data
  data=UDR;	// Read the data from UDR, as soon as the data arrives
  return data;
}

void straightfront(){
	if(!fvertical){
		frontclaw(0);
		_delay_ms(servoretract);
		motor('F','C');
		frontclaw(1);
		_delay_ms(servoretract);
	}
}

void straightleft(){
	if(!lvertical){
		leftclaw(0);
		_delay_ms(servoretract);
		motor('L','C');
		leftclaw(1);
		_delay_ms(servoretract);
	}
}

void straightright(){
	if(!rvertical){
		rightclaw(0);
		_delay_ms(servoretract);
		motor('R','C');
		rightclaw(1);
		_delay_ms(servoretract);
	}
}

void straightback(){
	if(!bvertical){
		backclaw(0);
		_delay_ms(servoretract);
		motor('B','C');
		backclaw(1);
		_delay_ms(servoretract);
	}
}

void move_generator(char input[]){
	int x;
	for(x=0;x<strlen(input);x++){
			if(input[x] == 'F'){
				if(!lvertical){
					if(!bvertical){
						backclaw(0);
						_delay_ms(servoretract);
						motor('B','C');
						backclaw(1);
					}
					frontclaw(0);
					leftclaw(0);
					_delay_ms(servoretract);
					motor('L','C');
					leftclaw(1);
					frontclaw(1);
				}
				if(!rvertical){
					if(!bvertical){
						backclaw(0);
						_delay_ms(servoretract);
						motor('B','C');
						backclaw(1);
					}
					frontclaw(0);
					rightclaw(0);
					_delay_ms(servoretract);
					motor('R','C');
					rightclaw(1);
					frontclaw(1);
				}
				_delay_ms(servoretract);
//				if(input[x+1] == 'C'){
//					motor('F','C');
//					x+=1;
//				}
//				else if(input[x+1] == 'A'){
//					motor('F','A');
//					x+=1;
//				}
//				else if(input[x+1] == 'H'){
//					motor('F','H');
//					x+=1;
//				}

				motor('F',input[x+1]);
			}

			else if (input[x] == 'L'){
				if(!fvertical){
					if(!rvertical){
						rightclaw(0);
						_delay_ms(servoretract);
						motor('R','C');
						rightclaw(1);
					}
					leftclaw(0);
					frontclaw(0);
					_delay_ms(servoretract);
					motor('F','C');
					leftclaw(1);
					frontclaw(1);
				}
				if(!bvertical){
					if(!rvertical){
						rightclaw(0);
						_delay_ms(servoretract);
						motor('R','C');
						rightclaw(1);
					}
					leftclaw(0);
					backclaw(0);
					_delay_ms(servoretract);
					motor('B','C');
					leftclaw(1);
					backclaw(1);
				}
				_delay_ms(servoretract);
//				if(input[x+1] == 'C'){
//					motor('L','C');
//					x+=1;
//				}
//				else if(input[x+1] == 'A'){
//					motor('L','A');
//					x+=1;
//				}
//				else if(input[x+1] == 'H'){
//					motor('L','H');
//					x+=1;
//				}
				motor('L',input[x+1]);
			}
			else if (input[x] == 'R'){
				if(!fvertical){
					if(lvertical){
						leftclaw(0);
						_delay_ms(servoretract);
						motor('L','C');
						leftclaw(1);
					}
					rightclaw(0);
					frontclaw(0);
					_delay_ms(servoretract);
					motor('F','C');
					rightclaw(1);
					frontclaw(1);
				}
				if(!bvertical){
					if(lvertical){
						leftclaw(0);
						_delay_ms(servoretract);
						motor('L','C');
						leftclaw(1);
					}
					rightclaw(0);
					backclaw(0);
					_delay_ms(servoretract);
					motor('B','C');
					rightclaw(1);
					backclaw(1);
				}
				_delay_ms(servoretract);
				/*
				if(input[x+1] == 'C'){
					motor('R','C');
				}
				else if(input[x+1] == 'A'){
					motor('R','A');
				}
				else if(input[x+1] == 'H'){
					motor('R','H');
				}
				*/
				motor('R',input[x+1]);
			}
			else if(input[x] == 'B'){
				if(!lvertical){
					if(!fvertical){
						frontclaw(0);
						_delay_ms(servoretract);
						motor('F','C');
						frontclaw(1);
					}
					backclaw(0);
					leftclaw(0);
					_delay_ms(servoretract);
					motor('L','C');
					leftclaw(1);
					backclaw(1);
				}
				if(!rvertical){
					if(!fvertical){
						frontclaw(0);
						_delay_ms(servoretract);
						motor('F','C');
						frontclaw(1);
					}
					backclaw(0);
					rightclaw(0);
					_delay_ms(servoretract);
					motor('R','C');
					rightclaw(1);
					backclaw(1);
				}
				_delay_ms(servoretract);
//				if(input[x+1] == 'C'){
//					motor('B','C');
//					x+=1;
//				}
//				else if(input[x+1] == 'A'){
//					motor('B','A');
//					x+=1;
//				}
//				else if(input[x+1] == 'H'){
//					motor('B','H');
//					x+=1;
//				}
				motor('B',input[x+1]);
			}
			else if (input[x] == 'X'){
				if(!fvertical && (!bvertical)){
					frontclaw(0);
					backclaw(0);
					_delay_ms(servoretract/2);
					motor('Y','C');
				}
				else if(!fvertical){
					frontclaw(0);
					_delay_ms(servoretract/2);
					motor('F','C');
				}
//				else{
//					backclaw(0);
//					_delay_ms(servoretract/2);
//					motor('B','C');
//				}
				else if (!bvertical){
					backclaw(0);
					_delay_ms(servoretract/2);
					motor('B','C');
				}
				_delay_ms(servoretract);
				leftclaw(1);
				rightclaw(1);
				_delay_ms(servoretract);
				motor('X',input[x+1]);
				backclaw(1);
				frontclaw(1);
			}
			else if (input[x] == 'Y'){
				if(!lvertical && (!rvertical)){
					leftclaw(0);
					rightclaw(0);
					_delay_ms(servoretract/2);
					motor('X','C');
								}
				else if(!rvertical){
					rightclaw(0);
					_delay_ms(servoretract/2);
					motor('R','C');
				}
//				else{
//					leftclaw(0);
//					_delay_ms(servoretract/2);
//					motor('L','C');
//				}
				else if (!lvertical){
					leftclaw(0);
					_delay_ms(servoretract/2);
					motor('L','C');
				}
				_delay_ms(servoretract);
				frontclaw(1);
				backclaw(1);
				_delay_ms(servoretract);
				motor('Y',input[x+1]);
				rightclaw(1);
				leftclaw(1);
			}
	}
}

void sendstring_uart(char v[])
{
	unsigned int i;
	for(i=0;i<strlen(v);i++)
	{
		sendchar_uart((unsigned char) v[i]);
		_delay_ms(2);
	}
}

void enable_stepper(){
	PORTD &= ~(1<<PIND7);
}

void disable_stepper(){
	PORTD |= 1<<PIND7;
}

void reset(){
	wdt_enable(WDTO_15MS);
	  while(1) {
	  }
}

void scan_cube(){
//	//scanU
//	_delay_ms(scan_delay);
//	move_generator("XA");
//	//scanF
//	_delay_ms(scan_delay);
//	move_generator("YC");
//	//scanL
//	_delay_ms(scan_delay);
//	move_generator("YC");
//	//scanB
//	_delay_ms(scan_delay);
//	move_generator("YC");
//	//scanR
//	_delay_ms(scan_delay);
//	move_generator("YC");
//	_delay_ms(scan_delay);
//	move_generator("XA");
//	//scanD
//	_delay_ms(scan_delay);
//	move_generator("XH");

	// scanning order -> FRBLDU

	//scanF
	//sendchar_uart('z');

	//scanR
	if(getchar_uart()=='n'){
	move_generator("YA");
	sendchar_uart('d');
	}

	//scanB
	if(getchar_uart()=='n'){
		move_generator("YA");
		sendchar_uart('z');
	}

	//scanL
	if(getchar_uart()=='n'){
		move_generator("YA");
		sendchar_uart('z');
	}

	//scanD
	if(getchar_uart()=='n'){
		move_generator("YA");
		move_generator("XA");
		sendchar_uart('z');
	}

	//scanU
	if(getchar_uart()=='n'){
		move_generator("XH");
		sendchar_uart('z');
	}

}

int main(){

	setup();
	disable_stepper();
	int cnt,num;
	unsigned char first;
//	unsigned char c;
	char inp_str[150],chr;
	// wait here for some input from robot
	for(num=0;num<150;num++){
		inp_str[num] = '\0';
	}
	while(1){
		first = getchar_uart();
		if(first == 's'){
			enable_stepper();
			scan_cube();
			disable_stepper();
			sendstring_uart("b");
			_delay_ms(50);
		}
		else{
			inp_str[0] = first;
			cnt=1;
			do{
				chr = (char)getchar_uart();
				inp_str[cnt] = chr;
				cnt++;
			}while(inp_str[cnt-1] != 'e');
//			_delay_ms(5);
//			sendstring_uart("string received ");
//			_delay_ms(5);
//			sendstring_uart(inp_str);
			enable_stepper();
			move_generator(inp_str);
			disable_stepper();
			sendstring_uart("d");
			reset();
		}
	}

return 0;
}
