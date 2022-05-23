/*
 * program.c
 *
 * Created: 2019-06-30 09:17:00
 *  Author: ppp
 */ 


#include <avr/io.h>
#define F_CPU 1200000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/wdt.h>             // watchdog

unsigned char a;      //pomocnicza przy rozjaœnianiu i œciemnianiu

void PWM_setup (void)
{
	TCCR0B |= (1 << CS01) | (0 << CS00);      // preskaler
	TCCR0A |= (1 << WGM01) | (1 << WGM00);    // fast pwm
	TCCR0A |= ((1 << COM0B1) | (1 << COM0B0));        // inwersja obu kana³ów
	TCCR0A |= ((1 << COM0A1) | (1 << COM0A0));
	OCR0A=255;
	OCR0B=255;
	
}



void adc_setup (void)
{
	// Set the ADC input to PB2/ADC1
	ADMUX |= (1 << MUX0);
	
	

	// Set the prescaler  & enable ADC
	ADCSRA |= (1 << ADPS1) | (0 << ADPS0) | (1 << ADEN);
}

int pomiar_fotorezystora (void)
{
	
	ADMUX=0x01;    // zmiana wejscia na adc1
	
	_delay_us(100);
	// Start the conversion
	ADCSRA |= (1 << ADSC);
	
	// Wait for it to finish
	while (ADCSRA & (1 << ADSC));
	
	return ADC;
	
}

int pomiar_potencjometru (void)
{
	
	ADMUX=0x02;     //zmiana wejscia na adc2
	
	_delay_us(100);
	// Start the conversion
	ADCSRA |= (1 << ADSC);
	
	// Wait for it to finish
	while (ADCSRA & (1 << ADSC));
	
	return ADC;
	if(ADC>1000) ADC=1000;
	if(ADC<20) ADC=20;
	
}

void rozjasnianie (void)
{

while (1)
{
	_delay_ms(10);
	if(OCR0A<=255) a=1;
	if(OCR0A<=250) a=2;
	if(OCR0A<=240) a=3;
	if(OCR0A<=225) a=4;
	if(OCR0A<=201) a=5;
	if(OCR0A<=171) a=6;
	if(OCR0A<=129) a=8;
	if(OCR0A<=65) a=5;
	if(OCR0A<=10) a=1;

	OCR0A=OCR0A-a;
	if(OCR0A==0) break;
}
	
}

void sciemnianie (void)
{
	while (1)
	{
	_delay_ms(12);
	if(OCR0A>=0) a=12;
	if(OCR0A>=96) a=7;
	if(OCR0A>=145) a=6;
	if(OCR0A>=181) a=5;
	if(OCR0A>=206) a=4;
	if(OCR0A>=222) a=3;
	if(OCR0A>=240) a=2;
	if(OCR0A>=250) a=1;

	OCR0A=OCR0A+a;
	if(OCR0A==255) break;	
	}
}



int main(void)
{

DDRB |= (1<<PB3) | (1<<PB1) | (1<<PB0);
PORTB=0x00;
PWM_setup();
adc_setup();

PORTB |= (1<<PB3);
OCR0B=100;
OCR0A=255;


unsigned int swiatlo;
swiatlo=0;

unsigned int regulacja;
regulacja=0;



unsigned char opoznienie;
opoznienie=0;	

unsigned int prog_zciemniania;
prog_zciemniania=0;

unsigned char roznica;     // roznica miedzy pogiem zciemniania a swiatlem
roznica=0;

wdt_enable(WDTO_4S );      // watchdog on
	
	 
 while(1)
{
wdt_reset();
swiatlo=pomiar_fotorezystora();
regulacja=pomiar_potencjometru();

opoznienie=0;

while(1)
{
	wdt_reset();
	_delay_ms(899);
	OCR0A=255;
	swiatlo=pomiar_fotorezystora();
	regulacja=pomiar_potencjometru();
	
	if(swiatlo<regulacja) opoznienie++;
	if(swiatlo>regulacja) opoznienie=0;
	if(opoznienie>7) break;
}

while(1) // procedura rozjaœniania
{
	wdt_reset();
	opoznienie=0;
	rozjasnianie();
	break;
}

while(1)            // pomiar œwiat³a po zaœwieceniu siê paska na wyjœciu czujnika
{
	wdt_reset();
	_delay_ms(1999);
	OCR0A=0;
	 prog_zciemniania=pomiar_fotorezystora();

	
	prog_zciemniania=prog_zciemniania+20;
	
	break;
}
while(1)                  // gdy jest ciemno i pasek swieci
{
wdt_reset();	
_delay_ms(899);
swiatlo=pomiar_fotorezystora();
regulacja=pomiar_potencjometru();
if(swiatlo<prog_zciemniania) {roznica=prog_zciemniania-swiatlo; if(roznica>10) prog_zciemniania--;}         // reakcja na spadek jasnosci
if(swiatlo<prog_zciemniania) {roznica=prog_zciemniania-swiatlo; if(roznica>50) prog_zciemniania-=40;}       //
if(swiatlo<prog_zciemniania) {roznica=prog_zciemniania-swiatlo; if(roznica>100) prog_zciemniania-=90;}      //
if(swiatlo<prog_zciemniania) {roznica=prog_zciemniania-swiatlo; if(roznica>200) prog_zciemniania-=190;}     //

if(prog_zciemniania<regulacja) {prog_zciemniania=regulacja; prog_zciemniania=prog_zciemniania+5;}	

if(swiatlo>prog_zciemniania) opoznienie++;
if(swiatlo<prog_zciemniania) opoznienie=0;
if(opoznienie>7) break;	
}

while(1) // procedura sciemniania
{
wdt_reset();
opoznienie=0;
sciemnianie();
break;

}

	   
	  
   }
   
   

}