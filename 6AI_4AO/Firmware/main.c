/* * main.c
 *
 *  Created on: 17 maj 2014
 *      Author: Ted
 */
//#include <stdio.h>
//#include <stddef.h>
//#include <stdbool.h>
#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include <util/delay.h> // _delay_ms(500);
#include <util/atomic.h>
#include <avr/eeprom.h>
#include <avr/wdt.h>
#include <util/crc16.h>

uint8_t EEMEM EPROM_ECHO='1';
uint8_t EEMEM EPROM_PARITY='0';
uint8_t EEMEM EPROM_STOPBITS='2';
uint8_t EEMEM EPROM_ADRES_KARTY[2];
uint32_t EEMEM EPROM_BAUD=9600;
uint8_t EEMEM EPROM_TCP_MODE=0x00;

volatile char Bufor_wej[255], Bufor_wyj[255], MBAP[6], AnalogInputs[12],AnalogOutputs[8];
volatile uint8_t numer_znaku_wej=0, numer_znaku_wyj=0, odbior=0, nadawanie=0,delay=0,cmd_ack=0,adc_number=0;
volatile char FrameError=0, DataOverrun=0, ParityError=0;
volatile uint8_t ADRES_KARTY[2];
volatile uint16_t PWMCycles=0;

uint8_t check_crc(char buffer[],uint8_t byte_no);
uint16_t crc_calc(char buffer[],uint8_t byte_no);

int main ( void )
{
	//-----------------------------------------------------
	//Ustawienie konfiguracji portów
	//---------------------------------------------------------------------
	//Wejcia
	//---------------------------------------------------------------------
	//DDRB &= ~(_BV(0) | _BV(1) | _BV(2) | _BV(3));
	DDRC &= ~(_BV(0) | _BV(1) | _BV(2) | _BV(3));

	//---------------------------------------------------------------------
	//Wyjscia
	//---------------------------------------------------------------------
	//DDRC |= _BV(0) | _BV(1) | _BV(2) | _BV(3);
	//PORTC &= ~(_BV(0) | _BV(1) | _BV(2) | _BV(3));
	DDRB |= _BV(1) | _BV(2) | _BV(3) | _BV(4);
	PORTB &= ~(_BV(1) | _BV(2) | _BV(3) | _BV(4));
	//---------------------------------------------------------------------
	//Sterowanie nadajnikiem RS485
	//---------------------------------------------------------------------
	DDRD |= _BV(2);
	PORTD &= ~_BV(2);
	//---------------------------------------------------------------------
	//Ustawienie ADC
	//---------------------------------------------------------------------
	ADMUX &= ~( _BV(7) | _BV(6) );
	//		   ADEN     ADPS0	  ADPS2	   ADSC
	ADCSRA |= _BV(7) | _BV(0) | _BV(2) | _BV(6);
	//---------------------------------------------------------------------
	//Ustawienie timera 0 PWM
	//---------------------------------------------------------------------
	TCCR0 = _BV(1) ; //CS01  //_BV(1)
	TIMSK |= _BV(0); //TOIE0 //_BV(0)
	TCNT0=241;
	//---------------------------------------------------------------------
	//odczyt zapisanego w EEPROM znacznika echo
	//---------------------------------------------------------------------
	uint8_t e_echo;
	eeprom_read_block(&e_echo , &EPROM_ECHO , 1);
	if(e_echo != '0' && e_echo != '1')
	{
		e_echo='1';
	}
	//---------------------------------------------------------------------
	//odczyt zapisanego w EEPROM znacznika tcp_mode
	//---------------------------------------------------------------------
	uint8_t e_tcp_mode='1', tcp_mode='1';
	eeprom_read_block(&e_tcp_mode , &EPROM_TCP_MODE , 1);
	if(e_tcp_mode != '0' && e_tcp_mode != '1')
	{
		e_tcp_mode='0';
	}
	//---------------------------------------------------------------------
	tcp_mode = e_tcp_mode;
	//---------------------------------------------------------------------
	//odczyt zapisanej w EEPROM prêdkosci komunikacji
	//---------------------------------------------------------------------
	uint32_t e_baud;
	eeprom_read_block(&e_baud, &EPROM_BAUD, 4);
	if( e_baud != 2400 && e_baud != 4800 && e_baud != 9600 && e_baud != 19200 && e_baud != 38400 && e_baud != 57600) // && e_baud != 115200 && e_baud != 230400)
	{
		e_baud = 9600;
	}
	//---------------------------------------------------------------------
	//Ustawienie wartoci preskalera
	//---------------------------------------------------------------------
	unsigned long BAUD_PRESCALE;
	UCSRA |= (1 << U2X);
	BAUD_PRESCALE = (((F_CPU / (e_baud * 8ul))) - 1);
	UBRRH = (BAUD_PRESCALE >> 8);
	UBRRL = BAUD_PRESCALE;
	//---------------------------------------------------------------------
	//Konfiguracja timera 2
	//---------------------------------------------------------------------
	if(e_baud==2400)
		delay = 199;
	else if(e_baud==4800)
		delay = 100;
	else if(e_baud==9600)
		delay = 50;
	else if(e_baud>=19200)
		delay = 25;
	else
		delay = 25;
	//---------------------------------------------------------------------
	//odczyt zapisanego w EEPROM adresu karty
	//---------------------------------------------------------------------
	uint8_t e_addr[2];
	eeprom_read_block(&e_addr , &EPROM_ADRES_KARTY , 2);
	//-----------------------------------------------------
	//Ustawienie adresu karty
	//---------------------------------------------------------------------
	ADRES_KARTY[0]=e_addr[0];
	ADRES_KARTY[1]=e_addr[1];
	//---------------------------------------------------------------------
	//odczyt zapisanego w EEPROM znacznika parzystoci transmisji
	//---------------------------------------------------------------------
	uint8_t e_parity;
	eeprom_read_block(&e_parity , &EPROM_PARITY , 1);
	if(e_parity!='0' && e_parity != '1' && e_parity !='2')
	{
		e_parity='0';
	}
	//---------------------------------------------------------------------
	//odczyt zapisanej w EEPROM iloci stopbitow
	//---------------------------------------------------------------------
	uint8_t e_stopbits;
	eeprom_read_block(&e_stopbits , &EPROM_STOPBITS , 1);
	if(e_stopbits != '1' && e_stopbits != '2')
	{
		e_stopbits='2';
	}
	//---------------------------------------------------------------------
	// Wpisanie odczytanej konfiguracji z EEPROM do rejestrów
	//---------------------------------------------------------------------
	char transm_param=0;
	transm_param=(1 << URSEL ) | (1 << UCSZ0 ) | (1 << UCSZ1 ) | (1 << USBS );//_BV(7)|_BV(2)|_BV(1);

	if(e_stopbits=='1')
	{
		transm_param &=~(1 << USBS);
	}
	else if(e_stopbits=='2')
	{
		transm_param |= (1 << USBS);
	}
	//---------------------------------------------------------------------
	if(e_parity=='0')
	{
		transm_param &= ~(1 << UPM0);
		transm_param &= ~(1 << UPM1);
	}
	else if(e_parity=='1')
	{
		transm_param |= (1 << UPM0);
		transm_param |= (1 << UPM1);
	}
	else if(e_parity=='2')
	{
		transm_param &= ~(1 << UPM0);
		transm_param |= (1 << UPM1);
	};
	UCSRC = transm_param;
	UCSRB = (1 << RXEN ) | (1 << TXEN ); // Turn on the transmission and reception circuitry
	UCSRB |= (1 << RXCIE )| (1 << TXCIE ); // Enable the USART Recieve/Transmit Complete interrupt ( USART_RXC )
	//-----------------------------------------------------
	sei() ; // Enable the Global Interrupt Enable flag so that interrupts can be processed
	//---------------------------------------------------------------------
	//Aktywacja watchdoga
	//---------------------------------------------------------------------
	wdt_enable(WDTO_2S);
	//---------------------------------------------------------------------
	odbior=0;
	uint16_t crc = 0;
	//uint8_t tmp8=0;
	//uint16_t tmp16 = 0;
	for (;;) // Loop forever
	{
		wdt_reset();
		//Odczyt wejœæ analogowych
		//---------------------------------------------------------------------
		ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
		{
			if(!(ADCSRA & _BV(6)))
			//if(!bit_is_set(ADCSRA , 6))
			{
				if (adc_number==0)
				{
					AnalogInputs[1] = ADCL;
					AnalogInputs[0] = ADCH;
					adc_number++;
					ADMUX |= _BV(0);
					ADCSRA |= _BV(6);
				}
				else if(adc_number==1)
				{
					AnalogInputs[3] = ADCL;
					AnalogInputs[2] = ADCH;
					adc_number++;
					ADMUX &= ~_BV(0);
					ADMUX |= _BV(1);
					ADCSRA |= _BV(6);
				}
				else if(adc_number==2)
				{
					AnalogInputs[5] =ADCL;
					AnalogInputs[4] =ADCH;
					adc_number++;
					ADMUX|= _BV(0);
					ADCSRA |= _BV(6);
				}
				else if(adc_number==3)
				{
					AnalogInputs[7] =ADCL ;
					AnalogInputs[6] =ADCH ;
					adc_number++;
					ADMUX&= ~_BV(0);
					ADMUX&= ~_BV(1);
					ADMUX|= _BV(2);
					ADCSRA |= _BV(6);
				}
				else if(adc_number==4)
				{
					AnalogInputs[9] =ADCL;
					AnalogInputs[8] =ADCH;
					adc_number++;
					ADMUX|= _BV(0);
					ADCSRA |= _BV(6);
				}
				else
				{
					AnalogInputs[11] =ADCL;
					AnalogInputs[10] =ADCH;
					adc_number=0;
					ADMUX&= ~_BV(0);
					ADMUX&= ~_BV(2);
					ADCSRA |= _BV(6);
				}
			}
		}
		//---------------------------------------------------------------------
		cmd_ack=0;
		if(TCNT2 >= delay && ParityError==0 && FrameError==0 && DataOverrun==0)
		{
			TCCR2 &= ~((1 << CS22) | (1 << CS21)| (1 << CS20));
			TCNT2=0;
			ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
			{

				//---------------------------------------------------------------------
				//Zwrocenie rodzaju karty na zapytanie #"ADRES_KARTY"_ECHO
				//---------------------------------------------------------------------
				if(Bufor_wej[0]=='#' &&
							Bufor_wej[1]==ADRES_KARTY[0] &&	//Adres karty
							Bufor_wej[2]=='_' &&
							Bufor_wej[3]=='E' &&
							Bufor_wej[4]=='C' &&
							Bufor_wej[5]=='H' &&
							Bufor_wej[6]=='O')
				{
					wdt_reset();
					Bufor_wyj[0]='4';
					Bufor_wyj[1]='D';
					Bufor_wyj[2]='I';
					Bufor_wyj[3]='4';
					Bufor_wyj[4]='R';
					Bufor_wyj[5]='O';
					Bufor_wyj[6]='_';
					Bufor_wyj[7]='M';
					Bufor_wyj[8]='O';
					Bufor_wyj[9]='D';
					Bufor_wyj[10]='B';
					Bufor_wyj[11]='U';
					Bufor_wyj[12]='S';
					Bufor_wyj[13]=' ';
					Bufor_wyj[14]='V';
					Bufor_wyj[15]='3';
					Bufor_wyj[16]='.';
					Bufor_wyj[17]='0';
					Bufor_wyj[18]='\n';
					numer_znaku_wyj=19;
					nadawanie=1;
				}
				//---------------------------------------------------------------------
				//Reset karty
				//---------------------------------------------------------------------
				else if(Bufor_wej[0]=='#' &&
							Bufor_wej[1]==ADRES_KARTY[0] &&	//Adres karty
							Bufor_wej[2]=='_' &&
							Bufor_wej[3]=='L' &&
							Bufor_wej[4]=='O' &&
							Bufor_wej[5]=='O' &&
							Bufor_wej[6]=='P')
					{
						while(1){}
					}
				//---------------------------------------------------------------------
				// KONGIFURACJA KARTY
				//---------------------------------------------------------------------
				//Ustawienie adresu karty @CONF_ADDR "ADRES_KARTY"
				//---------------------------------------------------------------------
				else if(Bufor_wej[0]=='@' &&
						Bufor_wej[1]=='C' &&
						Bufor_wej[2]=='O' &&
						Bufor_wej[3]=='N' &&
						Bufor_wej[4]=='F' &&
						Bufor_wej[5]=='_' &&
						Bufor_wej[6]=='A' &&
						Bufor_wej[7]=='D' &&
						Bufor_wej[8]=='D' &&
						Bufor_wej[9]=='R' )
				{
					wdt_reset();
					if(Bufor_wej[11]<=247)
					{
						e_addr[0]=Bufor_wej[11];
						eeprom_update_block (&e_addr , &EPROM_ADRES_KARTY , 1);
					}

					Bufor_wyj[0]='A';
					Bufor_wyj[1]='C';
					Bufor_wyj[2]='K';
					Bufor_wyj[3]='\n';
					numer_znaku_wyj=4;
					nadawanie=1;
				}
				//---------------------------------------------------------------------
				//Ustawienie prêdkoci tranmisji @CONF_BAUD "LICZBA(1-6)"
				//---------------------------------------------------------------------
				else if(Bufor_wej[0]=='@' &&
						Bufor_wej[1]=='C' &&
						Bufor_wej[2]=='O' &&
						Bufor_wej[3]=='N' &&
						Bufor_wej[4]=='F' &&
						Bufor_wej[5]=='_' &&
						Bufor_wej[6]=='B' &&
						Bufor_wej[7]=='A' &&
						Bufor_wej[8]=='U' &&
						Bufor_wej[9]=='D' )
				{
					wdt_reset();
					if(Bufor_wej[11]!=' ')
					{
						if(Bufor_wej[11]=='1')
						{e_baud=2400;}
						else if(Bufor_wej[11]=='2')
						{e_baud=4800;}
						else if(Bufor_wej[11]=='3')
						{e_baud=9600;}
						else if(Bufor_wej[11]=='4')
						{e_baud=19200;}
						else if(Bufor_wej[11]=='5')
						{e_baud=38400;}
						else if(Bufor_wej[11]=='6')
						{e_baud=57600;}

						eeprom_update_block (&e_baud , &EPROM_BAUD , 4);

						Bufor_wyj[0]='A';
						Bufor_wyj[1]='C';
						Bufor_wyj[2]='K';
						Bufor_wyj[3]='\n';
						numer_znaku_wyj=4;
						nadawanie=1;
					}
				}
				//---------------------------------------------------------------------
				//Ustawienie liczby bitów stopu dla transmisji @CONF_STOPBITS "LICZBA(1,2)"
				//---------------------------------------------------------------------
				else if(Bufor_wej[0]=='@' &&
						Bufor_wej[1]=='C' &&
						Bufor_wej[2]=='O' &&
						Bufor_wej[3]=='N' &&
						Bufor_wej[4]=='F' &&
						Bufor_wej[5]=='_' &&
						Bufor_wej[6]=='S' &&
						Bufor_wej[7]=='T' &&
						Bufor_wej[8]=='O' &&
						Bufor_wej[9]=='P' &&
						Bufor_wej[10]=='B' &&
						Bufor_wej[11]=='I' &&
						Bufor_wej[12]=='T' &&
						Bufor_wej[13]=='S')
				{
					wdt_reset();
					if(Bufor_wej[15]!=' ')
					{
						if(Bufor_wej[15]=='1')
						{e_stopbits='1';}
						else if(Bufor_wej[15]=='2')
						{e_stopbits='2';}

						eeprom_update_block (&e_stopbits , &EPROM_STOPBITS , 1);

						Bufor_wyj[0]='A';
						Bufor_wyj[1]='C';
						Bufor_wyj[2]='K';
						Bufor_wyj[3]='\n';
						numer_znaku_wyj=4;
						nadawanie=1;
					}
				}
				//---------------------------------------------------------------------
				//Ustawienie przystoci dla transmisji @CONF_PARITY(0,1,2)
				//---------------------------------------------------------------------
				else if(Bufor_wej[0]=='@' &&
						Bufor_wej[1]=='C' &&
						Bufor_wej[2]=='O' &&
						Bufor_wej[3]=='N' &&
						Bufor_wej[4]=='F' &&
						Bufor_wej[5]=='_' &&
						Bufor_wej[6]=='P' &&
						Bufor_wej[7]=='A' &&
						Bufor_wej[8]=='R' &&
						Bufor_wej[9]=='I' &&
						Bufor_wej[10]=='T' &&
						Bufor_wej[11]=='Y')
				{
					wdt_reset();
					if(Bufor_wej[13]!=' ')
					{
						if(Bufor_wej[13]=='0')
						{e_parity='0';}
						else if(Bufor_wej[13]=='1')
						{e_parity='1';}
						else if(Bufor_wej[13]=='2')
						{e_parity='2';}
						eeprom_update_block (&e_parity , &EPROM_PARITY , 1);

						Bufor_wyj[0]='A';
						Bufor_wyj[1]='C';
						Bufor_wyj[2]='K';
						Bufor_wyj[3]='\n';
						numer_znaku_wyj=4;
						nadawanie=1;

					}
				}
				//=====================================================================
				//&e_tcp_mode , &EPROM_TCP_MODE
				//---------------------------------------------------------------------
				else if(Bufor_wej[0]=='@' &&
						Bufor_wej[1]=='C' &&
						Bufor_wej[2]=='O' &&
						Bufor_wej[3]=='N' &&
						Bufor_wej[4]=='F' &&
						Bufor_wej[5]=='_' &&
						Bufor_wej[6]=='T' &&
						Bufor_wej[7]=='C' &&
						Bufor_wej[8]=='P' &&
						Bufor_wej[9]=='_' &&
						Bufor_wej[10]=='M' &&
						Bufor_wej[11]=='O' &&
						Bufor_wej[12]=='D' &&
						Bufor_wej[13]=='E')
				{
					wdt_reset();
					if(Bufor_wej[15]!=' ')
					{
						if(Bufor_wej[15]=='0')
						{e_tcp_mode='0';}
						else if(Bufor_wej[15]=='1')
						{e_tcp_mode='1';}

						eeprom_update_block (&e_tcp_mode , &EPROM_TCP_MODE , 1);

						Bufor_wyj[0]='A';
						Bufor_wyj[1]='C';
						Bufor_wyj[2]='K';
						Bufor_wyj[3]='\n';
						numer_znaku_wyj=4;
						nadawanie=1;

					}
				}
				//---------------------------------------------------------------------
				//Wyswietlenie konfiguracji modu³u @CONF
				//---------------------------------------------------------------------
				else if(Bufor_wej[0]=='@' &&
						Bufor_wej[1]=='C' &&
						Bufor_wej[2]=='O' &&
						Bufor_wej[3]=='N' &&
						Bufor_wej[4]=='F' &&
						Bufor_wej[5]=='D')
				{
					wdt_reset();
					Bufor_wyj[0]='S';
					Bufor_wyj[1]='T';
					Bufor_wyj[2]='O';
					Bufor_wyj[3]='P';
					Bufor_wyj[4]=' ';
					Bufor_wyj[5]='B';
					Bufor_wyj[6]='I';
					Bufor_wyj[7]='T';
					Bufor_wyj[8]='S';
					Bufor_wyj[9]='=';
					Bufor_wyj[10]=e_stopbits;
					Bufor_wyj[11]='\n';
					Bufor_wyj[12]='P';
					Bufor_wyj[13]='A';
					Bufor_wyj[14]='R';
					Bufor_wyj[15]='I';
					Bufor_wyj[16]='T';
					Bufor_wyj[17]='Y';
					Bufor_wyj[18]='=';
					Bufor_wyj[19]=e_parity;
					Bufor_wyj[20]='\n';
					Bufor_wyj[21]='E';
					Bufor_wyj[22]='C';
					Bufor_wyj[23]='H';
					Bufor_wyj[24]='O';
					Bufor_wyj[25]='=';
					Bufor_wyj[26]=e_echo;
					Bufor_wyj[27]='\n';
					Bufor_wyj[28]='T';
					Bufor_wyj[29]='C';
					Bufor_wyj[30]='P';
					Bufor_wyj[31]='_';
					Bufor_wyj[32]='M';
					Bufor_wyj[33]='O';
					Bufor_wyj[34]='D';
					Bufor_wyj[35]='E';
					Bufor_wyj[36]='=';
					Bufor_wyj[37]=e_tcp_mode;
					Bufor_wyj[38]='\n';
					numer_znaku_wyj=39;
					nadawanie=1;
				}
				else
				{
//					wdt_reset();
//					cmd_ack=1;
//					for(uint8_t i=0;i<numer_znaku_wej;i++)
//					{
//						Bufor_wyj[i]=Bufor_wej[i];
//					}
//					numer_znaku_wyj=numer_znaku_wej;
//					nadawanie=1;
				}

				if((tcp_mode=='1' || check_crc(Bufor_wej, numer_znaku_wej)==1 ) && !nadawanie)
				{
					if(tcp_mode=='1')
					{
						MBAP[0]=Bufor_wej[0];
						MBAP[1]=Bufor_wej[1];
						MBAP[2]=Bufor_wej[2];
						MBAP[3]=Bufor_wej[3];
						MBAP[4]=Bufor_wej[4];
						MBAP[5]=Bufor_wej[5];

						for(int i=0; i<numer_znaku_wej;i++)
						{
							Bufor_wej[i]=Bufor_wej[i+6];
							Bufor_wej[i+6]=0x00;
						}
						numer_znaku_wej=numer_znaku_wej-6;
					}
					//---------------------------------------------------------------------
					//Wywolanie rozkazu Read Input Registers (FC=04)
					//---------------------------------------------------------------------
					else if(Bufor_wej[0]==ADRES_KARTY[0]//Adres karty
							&& Bufor_wej[1]==0x04		//Kod funkcji
							&& Bufor_wej[2]==0x00		//Adres HB
							&& (Bufor_wej[3]>=0x00 &&	//Adres LB
								Bufor_wej[3]<=0x05)
							&& Bufor_wej[4]==0x00		//Dlugosc HB
							&& (Bufor_wej[5]>=0x01 &&	//Dlugosc LB
								Bufor_wej[5]<=0x06)
							)
					{
						wdt_reset();
						cmd_ack=1;
						Bufor_wyj[0]=ADRES_KARTY[0];			//Adres karty
						Bufor_wyj[1]=0x04;						//Kod funkcji
						Bufor_wyj[2]=(Bufor_wej[5]*2);			//Liczba rejestrów
						//Bufor_wyj[3]=0x00;						//Rejestr HB
						//Bufor_wyj[4]=0x00;						//Rejestr LB

						for(uint8_t i=(uint8_t)Bufor_wej[3];i<(uint8_t)Bufor_wej[5]+(uint8_t)Bufor_wej[3]; i++)
						//for(uint8_t i=0;i<2; i++)
						{
							if(i<=5)
							{
								Bufor_wyj[3+2*i-2*Bufor_wej[3]]=AnalogInputs[0+2*i];
								Bufor_wyj[4+2*i-2*Bufor_wej[3]]=AnalogInputs[1+2*i];
							}
							else
							{
								Bufor_wyj[3+2*i-2*Bufor_wej[3]]=0x00;
								Bufor_wyj[4+2*i-2*Bufor_wej[3]]=0x00;
							}
						}


						numer_znaku_wyj=3+2*(uint8_t)Bufor_wej[5];

						MBAP[5]=numer_znaku_wyj;

						if(tcp_mode=='0')
						{
							crc=0;
							crc=crc_calc(Bufor_wyj, numer_znaku_wyj);
							Bufor_wyj[numer_znaku_wyj]=(uint8_t)crc;			//CRC HB
							Bufor_wyj[numer_znaku_wyj+1]=(uint8_t)(crc >> 8);	//CRC LB
							numer_znaku_wyj=numer_znaku_wyj+2;
						}
						nadawanie=1;
					}

					//---------------------------------------------------------------------
					//Wywo³anie rozkazu Read Holding Registers (FC=03)
					//---------------------------------------------------------------------
					else if(Bufor_wej[0]==ADRES_KARTY[0]		//Adres karty
							&& Bufor_wej[1]==0x03				//Kod funkcji
							&& Bufor_wej[2]==0x00				//Adres HB
							&& (Bufor_wej[3]>=0x00 &&			//Adres LB
								Bufor_wej[3]<=0x03 )
							&& Bufor_wej[4]==0x00				//Dlugosc HB
							&& (Bufor_wej[5]>=0x01 &&			//Dlugosc LB
								Bufor_wej[5]<=0x04 )
							)
					{
						wdt_reset();
						cmd_ack=1;
						Bufor_wyj[0]=ADRES_KARTY[0];			//Adres karty
						Bufor_wyj[1]=0x03;						//Kod funkcji
						Bufor_wyj[2]=Bufor_wej[5]*2;			//Liczba rejestrów
						//Bufor_wyj[3]=0x00;						//Rejestr HB
						//Bufor_wyj[4]=0x00;						//Rejestr LB

						for(uint8_t i=(uint8_t)Bufor_wej[3];i<(uint8_t)Bufor_wej[5]+(uint8_t)Bufor_wej[3]; i++)
						{
							if(i<4)
							{
								Bufor_wyj[3+2*i-2*Bufor_wej[3]]=AnalogOutputs[0+2*i];
								Bufor_wyj[4+2*i-2*Bufor_wej[3]]=AnalogOutputs[1+2*i];
							}
							else
							{
								Bufor_wyj[3+2*i-2*Bufor_wej[3]]=0x00;
								Bufor_wyj[4+2*i-2*Bufor_wej[3]]=0x00;
							}
						}
						numer_znaku_wyj=3+2*(uint8_t)Bufor_wej[5];

						MBAP[5]=numer_znaku_wyj;

						if(tcp_mode=='0')
						{
							crc=0;
							crc=crc_calc(Bufor_wyj, numer_znaku_wyj);
							Bufor_wyj[numer_znaku_wyj]=(uint8_t)crc;			//CRC HB
							Bufor_wyj[numer_znaku_wyj+1]=(uint8_t)(crc >> 8);	//CRC LB
							numer_znaku_wyj=numer_znaku_wyj+2;
						}
						nadawanie=1;
					}
					//---------------------------------------------------------------------
					//Wywo³anie rozkazu Write Holding Register (FC=06)
					//---------------------------------------------------------------------
					else if(Bufor_wej[0]==ADRES_KARTY[0]		//Adres karty
							&& Bufor_wej[1]==0x06				//Kod funkcji
							&& Bufor_wej[2]==0x00				//Adres HB
							&& (Bufor_wej[3]>=0x00	&&			//Adres LB
								Bufor_wej[3]<=0x03)
							//&& Bufor_wej[4]==0x00				//Wartosc HB
							//&& Bufor_wej[5]==0x00				//Wartosc LB
							)
					{
						wdt_reset();
						cmd_ack=1;
						Bufor_wyj[0]=ADRES_KARTY[0];			//Adres karty
						Bufor_wyj[1]=0x06;						//Kod funkcji
						Bufor_wyj[2]=0x00;						//Adres HB
						Bufor_wyj[3]=Bufor_wej[3];				//Adres LB
						//Bufor_wyj[4]=0x00;					//Rejestr HB
						//Bufor_wyj[5]=0x00;					//Rejestr LB

						//-----------------------------------------------
						//Zapis wartoci
						//-----------------------------------------------
						AnalogOutputs[2*Bufor_wej[3]]=Bufor_wej[4];
						AnalogOutputs[2*Bufor_wej[3]+1]=Bufor_wej[5];
						//-----------------------------------------------
						//Odczyt zapisanych wartosci
						//-----------------------------------------------
						Bufor_wyj[4]=AnalogOutputs[2*Bufor_wej[3]];
						Bufor_wyj[5]=AnalogOutputs[2*Bufor_wej[3]+1];

						numer_znaku_wyj=6;
						MBAP[5]=numer_znaku_wyj;

						if(tcp_mode=='0')
						{
							crc=0;
							crc=crc_calc(Bufor_wyj, 6);
							Bufor_wyj[6]=(uint8_t)crc;			//CRC HB
							Bufor_wyj[7]=(uint8_t)(crc >> 8);	//CRC LB
							numer_znaku_wyj=8;
						}
						nadawanie=1;
					}
					else
					{
						wdt_reset();
//						cmd_ack=1;
//						for(uint8_t i=0;i<numer_znaku_wej;i++)
//						{
//							Bufor_wyj[i]=Bufor_wej[i];
//						}
//						numer_znaku_wyj=numer_znaku_wej;
//						nadawanie=1;
					}
				}
				odbior=0;
				for(uint8_t i=0;i<numer_znaku_wej;i++)
				{
					Bufor_wej[i]=0x00;
				}
				numer_znaku_wej=0;
				//---------------------------------------------------------------------
				//Nadanie odpowiedzi
				//---------------------------------------------------------------------
				if(nadawanie)
				{
					wdt_reset();
					ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
					{
						if(tcp_mode=='1'&& cmd_ack==1)
						{
							for(int i=numer_znaku_wyj-1; i>=0 ;i--)
							{
								Bufor_wyj[i+6]=Bufor_wyj[i];
							}
							numer_znaku_wyj=numer_znaku_wyj+6;
							for(int i=0; i<6;i++)
							{
								Bufor_wyj[i]=MBAP[i];
							}
						}
						PORTD |= _BV(2);
						_delay_ms(1);
						if(numer_znaku_wyj>0)
						{
							while(!(UCSRA & _BV(UDRE))); //oczekiwanie na dostêpnosc buforu
							UDR=Bufor_wyj[0];
							for(int i=0;i<numer_znaku_wyj;i++)
							{
								Bufor_wyj[i]=Bufor_wyj[i+1];
							}
							Bufor_wyj[numer_znaku_wyj]=0x00;
							numer_znaku_wyj--;
							nadawanie=0;
						}
					}
				}
			}
		}
		else if(TCNT2 >= delay && (ParityError==1 ||FrameError==1 || DataOverrun==1 ))
		{
			odbior=0;
			for(uint8_t i=0;i<numer_znaku_wej;i++)
			{
				Bufor_wej[i]=0x00;
			}
			numer_znaku_wej=0;
			ParityError=0;
			FrameError=0;
			DataOverrun=0;
		}
	}
}
//---------------------------------------------------------
//Odbiór danych
//---------------------------------------------------------
ISR ( USART_RXC_vect )
{
	if(odbior==0)
	{
		wdt_reset();
		//---------------------------------------------------------------------
		//Odczyt bledow transmisji
		//---------------------------------------------------------------------
		if(UCSRA & _BV(4))//FE)
		{
			FrameError=1;
		}
		if(UCSRA & _BV(3))//DOR)
		{
			DataOverrun=1;
		}
		if(UCSRA & _BV(2))//PE==1)
		{
			ParityError=1;
		}
		//---------------------------------------------------------------------
		//Odczyt bufora wejciowego
		//---------------------------------------------------------------------
		char tmp;
		tmp=UDR;
		if(numer_znaku_wej<255)
		{
			Bufor_wej[numer_znaku_wej]=tmp;
			numer_znaku_wej++;
		}
		TCCR2 |= (1 << CS22) | (1 << CS20); 			// Wlaczenie Timera2
		TCNT2 = 0;										// Reset wartosci licznika
	}
}
//---------------------------------------------------------
// Wysylanie danych
//---------------------------------------------------------
ISR ( USART_TXC_vect )
{
	wdt_reset();
	PORTD |= _BV(2);
	_delay_ms(1);
	if(numer_znaku_wyj>0)
	{
		while(!(UCSRA & _BV(UDRE))); //oczekiwanie na dostêpnosc buforu
		UDR=Bufor_wyj[0];
		for(int i=0;i<numer_znaku_wyj;i++)
		{
			Bufor_wyj[i]=Bufor_wyj[i+1];
		}
		Bufor_wyj[numer_znaku_wyj]=0x00;
		numer_znaku_wyj--;
	}
	else
	{
		PORTD &= ~_BV(2);
		_delay_ms(1);
	}
}
//---------------------------------------------------------
// Przepe³nienie timera 0 PWM
//---------------------------------------------------------
ISR(TIMER0_OVF_vect)
{
	TCNT0=TCNT0+236;//236

	if (PWMCycles<255)
	{
		PWMCycles++;
	}
	else
	{
		PWMCycles=0;
		PORTB |= _BV(1);
		PORTB |= _BV(2);
		PORTB |= _BV(3);
		PORTB |= _BV(4);
	}
	if(PWMCycles >= (((uint8_t)AnalogOutputs[0]<<8)|(AnalogOutputs[1])))
	{
		PORTB &= ~_BV(1);
	}
	if(PWMCycles >= (((uint8_t)AnalogOutputs[2]<<8)|(AnalogOutputs[3])))
	{
		PORTB &= ~_BV(2);
	}
	if(PWMCycles >= (((uint8_t)AnalogOutputs[4]<<8)|(AnalogOutputs[5])))
	{
		PORTB &= ~_BV(3);
	}
	if(PWMCycles >= (((uint8_t)AnalogOutputs[6]<<8)|(AnalogOutputs[7])))
	{
		PORTB &= ~_BV(4);
	}
}
//---------------------------------------------------------
// Sprawdzenie CRC
//---------------------------------------------------------
uint8_t check_crc(char buffer[],uint8_t byte_no)
{
	uint16_t crc=0xffff;
	for(uint8_t i=0;i<(byte_no-2);i++)
	{
		wdt_reset();
		crc = _crc16_update (crc, (uint8_t)buffer[i]);
	}

	if (buffer[byte_no-1]==(uint8_t)(crc >> 8) &&  buffer[byte_no-2] == (uint8_t)crc )
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
//---------------------------------------------------------
// Obliczenie CRC
//---------------------------------------------------------
uint16_t crc_calc(char buffer[],uint8_t byte_no)
{
	uint16_t crc=0xffff;
	for(uint8_t i=0;i<(byte_no);i++)
	{
		wdt_reset();
		crc = _crc16_update (crc, (uint8_t)buffer[i]);
	}
	return crc;
}

