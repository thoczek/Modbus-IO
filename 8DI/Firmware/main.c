/*
 * main.c
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

volatile char Bufor_wej[255], Bufor_wyj[255], MBAP[6];
volatile uint8_t numer_znaku_wej=0, numer_znaku_wyj=0, odbior=0, nadawanie=0,delay=0,cmd_ack=0;
volatile char FrameError=0, DataOverrun=0, ParityError=0;
volatile uint8_t ADRES_KARTY[2];

uint8_t check_crc(char buffer[],uint8_t byte_no);
uint16_t crc_calc(char buffer[],uint8_t byte_no);

int main ( void )
{
	//-----------------------------------------------------
	//Ustawienie konfiguracji portów
	//---------------------------------------------------------------------
	//Wejcia
	//---------------------------------------------------------------------
	DDRB &= ~(_BV(0) | _BV(1) | _BV(2) | _BV(3));
	DDRC &= ~(_BV(0) | _BV(1) | _BV(2) | _BV(3));
	//---------------------------------------------------------------------
	//Wyjscia
	//---------------------------------------------------------------------
	//DDRC |= _BV(0) | _BV(1) | _BV(2) | _BV(3);
	//PORTC &= ~(_BV(0) | _BV(1) | _BV(2) | _BV(3));
	//PORTC &= ~_BV(3);
	//PORTC |= _BV(0);
	//---------------------------------------------------------------------
	//Sterowanie nadajnikiem RS485
	//---------------------------------------------------------------------
	DDRD |= _BV(2);
	PORTD &= ~_BV(2);
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
	uint8_t tmp=0;
	for (;;) // Loop forever
	{
		wdt_reset();
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
					Bufor_wyj[0]='8';
					Bufor_wyj[1]='D';
					Bufor_wyj[2]='I';
					Bufor_wyj[3]='_';
					Bufor_wyj[4]='M';
					Bufor_wyj[5]='O';
					Bufor_wyj[6]='D';
					Bufor_wyj[7]='B';
					Bufor_wyj[8]='U';
					Bufor_wyj[9]='S';
					Bufor_wyj[10]=' ';
					Bufor_wyj[11]='V';
					Bufor_wyj[12]='3';
					Bufor_wyj[13]='.';
					Bufor_wyj[14]='0';
					Bufor_wyj[15]='\n';
					numer_znaku_wyj=16;
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
					wdt_reset();
//					for(uint8_t i=0;i<numer_znaku_wej;i++)
//					{
//						Bufor_wyj[i]=Bufor_wej[i];
//					}
//					numer_znaku_wyj=numer_znaku_wej;
//					nadawanie=1;
				}

				if((tcp_mode=='1' || check_crc(Bufor_wej, numer_znaku_wej)==1) && !nadawanie)
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
					//Wywolanie rozkazu Read Input Status (FC=02)
					//---------------------------------------------------------------------
					if(Bufor_wej[0]==ADRES_KARTY[0]		//Adres karty
							&& Bufor_wej[1]==0x02		//Kod funkcji
							&& Bufor_wej[2]==0x00		//Adres HB
							&& Bufor_wej[3]<=0x07		//Adres LB
							&& Bufor_wej[4]==0x00		//Dlugosc HB
							&& Bufor_wej[5]<=0x08		//Dlugosc LB
							)
					{
						wdt_reset();
						cmd_ack=1;
						Bufor_wyj[0]=ADRES_KARTY[0];			//Adres karty
						Bufor_wyj[1]=0x02;						//Kod funkcji
						Bufor_wyj[2]=0x01;						//Liczba rejestrów

						tmp=0;
						for(int i=0;i<Bufor_wej[5];i++)
						{
							if(i+Bufor_wej[3]==0x07)
							{
								if(PINC & _BV(0)) tmp &= ~_BV(i);
								else tmp |= _BV(i);
							}

							if(i+Bufor_wej[3]==0x06)
							{
								if(PINC & _BV(1)) tmp &= ~_BV(i);
								else tmp |= _BV(i);
							}

							if(i+Bufor_wej[3]==0x05)
							{
								if(PINC & _BV(2)) tmp &= ~_BV(i);
								else tmp |= _BV(i);
							}

							if(i+Bufor_wej[3]==0x04)
							{
								if(PINC & _BV(3)) tmp &= ~_BV(i);
								else tmp |= _BV(i);
							}

							if(i+Bufor_wej[3]==0x03)
							{
								if(PINB & _BV(3)) tmp &= ~_BV(i);
								else tmp |= _BV(i);
							}

							else if(i+Bufor_wej[3]==0x02)
							{
								if(PINB & _BV(2)) tmp&= ~_BV(i);
								else tmp|= _BV(i);
							}

							else if(i+Bufor_wej[3]==0x01)
							{
								if(PINB & _BV(1)) tmp&= ~_BV(i);
								else tmp|= _BV(i);
							}

							else if(i+Bufor_wej[3]==0x00)
							{
								if(PINB & _BV(0)) tmp&= ~_BV(i);
								else tmp|= _BV(i);
							}
						}
						Bufor_wyj[3]=tmp;
						numer_znaku_wyj=4;
						MBAP[5]=numer_znaku_wyj;
						if(tcp_mode=='0')
						{
							crc=0;
							crc=crc_calc(Bufor_wyj, 4);
							Bufor_wyj[4]=(uint8_t)crc;			//CRC HB
							Bufor_wyj[5]=(uint8_t)(crc >> 8);	//CRC LB
							numer_znaku_wyj=6;
						}
						nadawanie=1;
					}
					//---------------------------------------------------------------------
					//Wywolanie rozkazu Read Input Registers (FC=04)
					//---------------------------------------------------------------------
					else if(Bufor_wej[0]==ADRES_KARTY[0]//Adres karty
							&& Bufor_wej[1]==0x04		//Kod funkcji
							&& Bufor_wej[2]==0x00		//Adres HB
							&& Bufor_wej[3]==0x00		//Adres LB
							&& Bufor_wej[4]==0x00		//Dlugosc HB
							&& Bufor_wej[5]==0x01		//Dlugosc LB
							)
					{
						wdt_reset();
						cmd_ack=1;
						Bufor_wyj[0]=ADRES_KARTY[0];			//Adres karty
						Bufor_wyj[1]=0x04;						//Kod funkcji
						Bufor_wyj[2]=0x02;						//Liczba rejestrów
						Bufor_wyj[3]=0x00;						//Rejestr HB
						Bufor_wyj[4]=0x00;						//Rejestr LB

						if(PINC & _BV(0)) Bufor_wyj[4]&= ~_BV(7);
						else Bufor_wyj[4]|= _BV(7);

						if(PINC & _BV(1)) Bufor_wyj[4]&= ~_BV(6);
						else Bufor_wyj[4]|= _BV(6);

						if(PINC & _BV(2)) Bufor_wyj[4]&= ~_BV(5);
						else Bufor_wyj[4]|= _BV(5);

						if(PINC & _BV(3)) Bufor_wyj[4]&= ~_BV(4);
						else Bufor_wyj[4]|= _BV(4);



						if(PINB & _BV(3)) Bufor_wyj[4]&= ~_BV(3);
						else Bufor_wyj[4]|= _BV(3);

						if(PINB & _BV(2)) Bufor_wyj[4]&= ~_BV(2);
						else Bufor_wyj[4]|= _BV(2);

						if(PINB & _BV(1)) Bufor_wyj[4]&= ~_BV(1);
						else Bufor_wyj[4]|= _BV(1);

						if(PINB & _BV(0)) Bufor_wyj[4]&= ~_BV(0);
						else Bufor_wyj[4]|= _BV(0);

						numer_znaku_wyj=5;
						MBAP[5]=numer_znaku_wyj;

						if(tcp_mode=='0')
						{
							crc=0;
							crc=crc_calc(Bufor_wyj, 5);
							Bufor_wyj[5]=(uint8_t)crc;			//CRC HB
							Bufor_wyj[6]=(uint8_t)(crc >> 8);	//CRC LB
							numer_znaku_wyj=7;
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
		else if(TCNT2 >= delay && (ParityError==1 |FrameError==1 | DataOverrun==1 ))
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
		if(numer_znaku_wej<100)
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

