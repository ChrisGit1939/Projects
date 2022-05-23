/*
 * centralka_lampek_na_spi.c
 *
 * Created: 2018-11-02 18:55:38
 *  Author: ppp
 */ 


#define F_CPU 1000000UL
#include <avr/io.h>


#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>

#define clk_spi (1<<PB0)                           // 6 linijek to definicja sygn wyjœciowego do lampki
#define dane_spi (1<<PB1)

#define clk_spi_on PORTB |= clk_spi
#define clk_spi_off PORTB &= ~clk_spi

#define dane_spi_on PORTB |= dane_spi
#define dane_spi_off PORTB &= ~dane_spi

#define data PD1
#define clk PD0
#define cs PD3
#define dc PD2
#define lcd_light PD4
#define lcd_status PD5    // pin odpowiadaj¹cy za zasilanie na LCD

#define data_1 (PORTD |= (1<<data))
#define data_0 (PORTD &= ~(1<<data))

#define clk_1 (PORTD |= (1<<clk))
#define clk_0 (PORTD &= ~(1<<clk))

#define cs_1 (PORTD |= (1<<cs))      // nieaktywny
#define cs_0 (PORTD &= ~(1<<cs))      // aktywny

#define dc_1 (PORTD |= (1<<dc))       // wyswietlanie
#define dc_0 (PORTD &= ~(1<<dc))     // sterowanie

#define lcd_on (PORTD |=(1<<lcd_status))  //lcd w³¹czony
#define lcd_off (PORTD &= ~(1<<lcd_status))  // lcd wy³¹czony

#define lcd_light_on (PORTD |= (1<<lcd_light) )   // w³¹czanie  œwiat³a na LCD
#define lcd_light_off (PORTD &= ~(1<<lcd_light))   // wy³¹czanie œwiat³a na LCD




#define enter_push (!(PIND & (1<<PD7)))   //klawisz wciœniêty
#define enter_stop (PIND & (1<<PD7))      // klawisz zwolniony

#define esc_push (!(PIND & (1<<PD6)))
#define esc_stop (PIND & (1<<PD6))

#define enc_push (!(PINC & (1<<PC3)))
#define enc_stop (PINC & (1<<PC3))




uint32_t czas;    // zmienna globalna odmierzaj¹ca czas
unsigned char ilosc_odbiornikow; // zmienna globalna w której zawarta jest iloœæ odbiorników SPI


void ADC_init (void)
{
	ADMUX = (1<<REFS0);	// napiêcie referencyjne = napiêcie zasilania


	ADCSRA = (1<<ADEN)      // w³¹czamy przetwornik
	|(1<<ADPS0)
	|(1<<ADPS1)
	|(1<<ADPS2);             // preskaler 1/128
}

void TIMER2_SETUP (void)
{
	TCCR2 |= ((1 << CS22) | (1 << CS20)); //Ustawia timer2 z preskalerem
	ASSR |= (1 << AS2);        // praca asynchroniczna
	TIMSK |= (1 << TOIE2);             // odblokowanie przerwañ z przepelnienia
	while (ASSR & (1 << OCR2UB));  // Wait for registers to update
	sei();                 // pozwolenie na globalne przerwania
};



void send_lcd_data (unsigned char dana)
{
	cs_1;
	clk_0;
	dc_1;
	data_0;
	unsigned char cyfra;
	unsigned char h;     // bit nr 7
	unsigned char g;
	unsigned char f;
	unsigned char e;
	unsigned char d;
	unsigned char c;
	unsigned char b;
	unsigned char a;	// bit nr 0



	cyfra=dana;
	a=cyfra%2;
	dana=dana>>1;

	cyfra=dana;
	b=cyfra%2;
	dana=dana>>1;

	cyfra=dana;
	c=cyfra%2;
	dana=dana>>1;

	cyfra=dana;
	d=cyfra%2;
	dana=dana>>1;

	cyfra=dana;
	e=cyfra%2;
	dana=dana>>1;

	cyfra=dana;
	f=cyfra%2;
	dana=dana>>1;

	cyfra=dana;
	g=cyfra%2;
	dana=dana>>1;

	cyfra=dana;
	h=cyfra%2;

	cs_0;
	dc_1;
	if(h==1) data_1; else data_0;
	clk_1;

	clk_0;

	if(g==1) data_1; else data_0;
	clk_1;

	clk_0;

	if(f==1) data_1; else data_0;
	clk_1;

	clk_0;

	if(e==1) data_1; else data_0;
	clk_1;

	clk_0;

	if(d==1) data_1; else data_0;
	clk_1;

	clk_0;

	if(c==1) data_1; else data_0;
	clk_1;

	clk_0;

	if(b==1) data_1; else data_0;
	clk_1;

	clk_0;

	if(a==1) data_1; else data_0;
	clk_1;
	clk_0;

	cs_1;
	clk_0;
	dc_1;
	data_0;

};

void send_lcd_command(unsigned char dana)
{
	cs_1;
	clk_0;
	dc_0;
	data_0;
	unsigned char cyfra;
	unsigned char h;     // bit nr 7
	unsigned char g;
	unsigned char f;
	unsigned char e;
	unsigned char d;
	unsigned char c;
	unsigned char b;
	unsigned char a;	// bit nr 0

	cyfra=dana;
	a=cyfra%2;
	dana=dana>>1;

	cyfra=dana;
	b=cyfra%2;
	dana=dana>>1;

	cyfra=dana;
	c=cyfra%2;
	dana=dana>>1;

	cyfra=dana;
	d=cyfra%2;
	dana=dana>>1;

	cyfra=dana;
	e=cyfra%2;
	dana=dana>>1;

	cyfra=dana;
	f=cyfra%2;
	dana=dana>>1;

	cyfra=dana;
	g=cyfra%2;
	dana=dana>>1;

	cyfra=dana;
	h=cyfra%2;

	cs_0;
	dc_0;
	if(h==1) data_1;
	else data_0;
	clk_1;

	clk_0;

	if(g==1) data_1;
	else data_0;
	clk_1;

	clk_0;

	if(f==1) data_1;
	else data_0;
	clk_1;

	clk_0;

	if(e==1) data_1;
	else data_0;
	clk_1;

	clk_0;

	if(d==1) data_1;
	else data_0;
	clk_1;

	clk_0;

	if(c==1) data_1;
	else data_0;
	clk_1;

	clk_0;

	if(b==1) data_1;
	else data_0;
	clk_1;

	clk_0;

	if(a==1) data_1;
	else data_0;
	clk_1;

	clk_0;

	cs_1;
	clk_0;
	dc_0;
	data_0;
};

void send_lcd_picture(unsigned char x, unsigned char y, unsigned char szerokosc, unsigned char wysokosc, unsigned char tablica[])
{                     // wspó³rzêdna x  wspó³rzêdna y   szerokosc obrazka w pix        wysokosc obrazka w pix        bajt danych
	unsigned char adres_x;
	unsigned char adres_y;
	unsigned char szer;
	unsigned char koniec_szer;
	unsigned int element;
	unsigned int koniec;      //ostatni bajt obrazka

	element=0;

	koniec_szer=x+szerokosc;
	wysokosc=wysokosc/8;

	szer=x;


	koniec=wysokosc*szerokosc;


	adres_x=0x80;             // sta³a wartoœæ któr¹ LCD interpretuje jako adres
	adres_y=0x40;             // jak wy¿ej
	adres_x=adres_x+x;
	adres_y=adres_y+y;

	send_lcd_command(adres_x);
	send_lcd_command(adres_y);

	while(1)
	{

		send_lcd_data(tablica[element]);
		element++;
		szer++;
		if(element==koniec) break;
		if(szer==koniec_szer) {szer=x; adres_y++; send_lcd_command(adres_x); send_lcd_command(adres_y); };

		
	}


	
}

void godzina(unsigned char wspolrzedna_x, unsigned char wspolrzedna_y, unsigned char znaki[])   // cyfry
{
	unsigned char zegarek[] = { 0x38,0x57,0x83,0x82,0xde,0x92,0x83,0x57,0x38 };
	
	unsigned char js;
	unsigned char ds;
	unsigned char jm;
	unsigned char dm;
	unsigned char jg;
	unsigned char dg;
	unsigned char s;
	unsigned char m;
	unsigned char g;
	unsigned short reszta;
	uint32_t pomocnicza;
	js=0;
	ds=0;
	jm=0;
	dm=0;
	jg=0;
	dg=0;
	s=0;
	m=0;
	g=0;
	reszta=0;
	pomocnicza=czas;          // nie wolno zmieniaæ wartoœci czas


	reszta=pomocnicza%3600;
	pomocnicza=pomocnicza-reszta;  // aby wyliczyæ iloœæ godzin jako liczba ca³kowita odejmujemy reszte
	g=pomocnicza/3600;    // wyliczamy wartoœæ godzin

	pomocnicza=reszta;    // przekazujemy wartoœæ która zawiera minuty i sekundy

	reszta=pomocnicza%60;    // reszta to iloœæ sekund
	pomocnicza=pomocnicza-reszta;
	m=pomocnicza/60;      // iloœæ minut

	s=reszta;             // sekundy


	reszta=g%10;
	g=g-reszta;
	dg=g/10;
	jg=reszta;

	reszta=m%10;
	m=m-reszta;
	dm=m/10;
	jm=reszta;

	reszta=s%10;
	s=s-reszta;
	ds=s/10;
	js=reszta;

	dg=dg*6;
	jg=jg*6;
	dm=dm*6;
	jm=jm*6;
	ds=ds*6;
	js=js*6;



	send_lcd_picture(wspolrzedna_x, wspolrzedna_y, 9, 8, zegarek);


	pomocnicza=0;         // pomocnicza bêdzie robiæ za licznik przesy³anych bajtów

	while(pomocnicza<6){send_lcd_data(znaki[dg]);pomocnicza++;dg++;}



	pomocnicza=0;         // pomocnicza bêdzie robiæ za licznik przesy³anych bajtów

	while(pomocnicza<6){send_lcd_data(znaki[jg]);pomocnicza++;jg++;}


	pomocnicza=0;         // pomocnicza bêdzie robiæ za licznik przesy³anych bajtów

	send_lcd_data(0x00);    // spacja
	send_lcd_data(0x28);   //dwukropek


	while(pomocnicza<6){send_lcd_data(znaki[dm]);pomocnicza++;dm++;}


	pomocnicza=0;         // pomocnicza bêdzie robiæ za licznik przesy³anych bajtów

	while(pomocnicza<6){send_lcd_data(znaki[jm]);pomocnicza++;jm++;}

	send_lcd_data(0x00);    // spacja
	send_lcd_data(0x28);   //dwukropek


	pomocnicza=0;         // pomocnicza bêdzie robiæ za licznik przesy³anych bajtów

	while(pomocnicza<6){send_lcd_data(znaki[ds]);pomocnicza++;ds++;}


	pomocnicza=0;         // pomocnicza bêdzie robiæ za licznik przesy³anych bajtów

	while(pomocnicza<6){send_lcd_data(znaki[js]); pomocnicza++; js++;}
}

void pomiar_swiatla(unsigned char wspolrzedna_x, unsigned char wspolrzedna_y, unsigned char znaki[])
{
	unsigned char procent[] = {0x00,0x86,0x66,0x10,0xcc,0xc2};
	unsigned char swiatlo[] = {0x00,0x12,0x08,0xc2,0x36,0x06,0xf6,0x06,0x36,0xc2,0x08,0x12};	// obrazek œwiat³o

	unsigned short pomiar_a;
	unsigned short pomiar_b;
	unsigned short pomiar_c;
	unsigned short pomiar;
	unsigned char reszta;
	unsigned char s;
	unsigned char d;
	unsigned char j;

	ADMUX = 0x46;            //  w³¹czamy ADC6 na którym jest fotorezystor
	ADCSRA |= (1<<ADSC); //ADSC: uruchomienie pojedynczej konwersji
	while(ADCSRA & (1<<ADSC)); //czeka na zakoñczenie konwersji
	pomiar=ADC;

	ADCSRA |= (1<<ADSC); //ADSC: uruchomienie pojedynczej konwersji
	while(ADCSRA & (1<<ADSC)); //czeka na zakoñczenie konwersji
	pomiar_a=ADC;

	ADCSRA |= (1<<ADSC); //ADSC: uruchomienie pojedynczej konwersji
	while(ADCSRA & (1<<ADSC)); //czeka na zakoñczenie konwersji
	pomiar_b=ADC;

	ADCSRA |= (1<<ADSC); //ADSC: uruchomienie pojedynczej konwersji
	while(ADCSRA & (1<<ADSC)); //czeka na zakoñczenie konwersji
	pomiar_c=ADC;

	pomiar=pomiar + pomiar_a + pomiar_b + pomiar_c; // wykonujemy 4 pomiary i wyliczamy œredni¹
	reszta=pomiar%4;
	pomiar=pomiar-reszta;
	pomiar=pomiar/4;

	if(pomiar>1000) pomiar=1000;
	reszta=pomiar%10;
	pomiar=pomiar-reszta;
	pomiar=pomiar/10;
	reszta=pomiar%100;
	pomiar=pomiar-reszta;
	s=pomiar/100;
	pomiar=reszta;
	reszta=pomiar%10;
	pomiar=pomiar-reszta;
	d=pomiar/10;
	j=reszta;

	s=s*6;     // mno¿enie pozwala wyœwietliæ cyfrê z ci¹gu zbioru tablicy zaw. cyfry
	d=d*6;     // cyfra jest ukryta w tablicy. wynik mno¿enia to numer elementu
	j=j*6;     // od którego ma siê rozpocz¹æ przesy³anie obrazka symbolizj¹cego cyfrê. cyfra to 6 kolejnych znaków

	send_lcd_picture(wspolrzedna_x, wspolrzedna_y, 12, 8, swiatlo);

	reszta=0;       // reszta bêdzie teraz robiæ za licznik pêtli
	while(reszta<6){send_lcd_data(znaki[s]);if(s==0)break; reszta++;s++; }//  wyswietlamy setki jeœli jest jakaœ setka
	reszta=0;
	while(reszta<6){send_lcd_data(znaki[d]);reszta++;d++;}    // wyswietlamy dziesiatki
	reszta=0;
	while(reszta<6){send_lcd_data(znaki[j]);reszta++;j++;}     // wyswietlamy jednosci
	reszta=0;
	while(reszta<6){send_lcd_data(procent[reszta]);reszta++;} // wyœwietlamy znak %
	reszta=0;
	while(reszta<5){if(s==1)break; send_lcd_data(0x00);reszta++;}  //dodajemy kilka pustych miejsc aby wykasowaæ
	// piksele które zosta³y gdy pomiar wyniós³ 100% przez co wyraz by³ d³u¿szy
}
void pomiar_baterii(unsigned char wspolrzedna_x, unsigned char wspolrzedna_y, unsigned char znaki[])
{
	unsigned char bateria[] =
	{
		0x00,0xfc,0x86,0xb6,0x86,0xfc
	};
	
	unsigned char litera_V[] =
	{
		0x00,0x06,0x38,0xc0,0x38,0x06
		
	};
	
	unsigned char procent[] = {0x00,0x86,0x66,0x10,0xcc,0xc2};
	
	unsigned short pomiar;
	unsigned char reszta;
	unsigned char s;
	unsigned char d;
	unsigned char j;
	unsigned short pomocnicza;
	
	reszta=0;
	s=0;
	d=0;
	j=0;
	
	send_lcd_picture(wspolrzedna_x, wspolrzedna_y, 6, 8, bateria);  // wyœwietlamy ikonke baterii

	ADMUX = 0x42;            //  w³¹czamy ADC2
	ADCSRA |= (1<<ADSC); //ADSC: uruchomienie pojedynczej konwersji
	while(ADCSRA & (1<<ADSC)); //czeka na zakoñczenie konwersji
	pomiar=ADC;
	
	pomocnicza=pomiar;                  // z wartoœci ADC obliczamy % na³adowania baterii
	if(pomocnicza<660) pomocnicza=660;
	if(pomocnicza>810) pomocnicza=810;
	pomocnicza=pomocnicza-660;
	pomocnicza=pomocnicza*10;
	reszta=pomocnicza%15;
	pomocnicza=pomocnicza-reszta;
	pomocnicza=pomocnicza/15;
	
	reszta=pomocnicza%100;         // obliczanie setek
	pomocnicza=pomocnicza-reszta;
	s=pomocnicza/100;
	
	pomocnicza=reszta;
	
	reszta=pomocnicza%10;        // obliczanie dziesi¹tek i jednoœci
	pomocnicza=pomocnicza-reszta;
	d=pomocnicza/10;
	
	j=reszta;
	
	pomocnicza=0;         //  bêdzie robiæ za licznik przesy³anych bajtów
	
	s=s*6;
	
	while(pomocnicza<6){if(s==0) break; send_lcd_data(znaki[s]);pomocnicza++;s++;}  // wyœwietlamy setki jeœli s¹
	
	pomocnicza=0;         //  bêdzie robiæ za licznik przesy³anych bajtów
	
	d=d*6;
	while(pomocnicza<6){send_lcd_data(znaki[d]);pomocnicza++;d++;}  // wyœwietlamy dziesi¹tki
	
	pomocnicza=0;         //  bêdzie robiæ za licznik przesy³anych bajtów
	
	j=j*6;
	while(pomocnicza<6){send_lcd_data(znaki[j]);pomocnicza++;j++;}  // wyœwietlamy jednoœci
	
	
	pomocnicza=0;         //  bêdzie robiæ za licznik przesy³anych bajtów
	
	
	while(pomocnicza<6){send_lcd_data(procent[pomocnicza]);pomocnicza++;}  // wyœwietlamy %
	
	send_lcd_data(0x00);  // kilka spacji
	send_lcd_data(0x00);
	send_lcd_data(0x00);
	send_lcd_data(0x00);
	send_lcd_data(0x00);
	
	pomocnicza=pomiar;
	
	pomocnicza=pomocnicza-13;   // ma³a kalibracja pomiaru :)
	
	reszta=pomocnicza%2;            // obliczamy to co wska¿e woltomierz
	pomocnicza=pomocnicza-reszta;
	pomocnicza=pomocnicza/2;
	
	reszta=pomocnicza%100;         // obliczanie setek
	pomocnicza=pomocnicza-reszta;
	s=pomocnicza/100;
	
	pomocnicza=reszta;
	
	reszta=pomocnicza%10;        // obliczanie dziesi¹tek i jednoœci
	pomocnicza=pomocnicza-reszta;
	d=pomocnicza/10;
	
	j=reszta;
	
	pomocnicza=0;         //  bêdzie robiæ za licznik przesy³anych bajtów
	
	s=s*6;
	while(pomocnicza<6){send_lcd_data(znaki[s]);pomocnicza++;s++;}  // wyœwietlamy setki
	
	pomocnicza=0;         //  bêdzie robiæ za licznik przesy³anych bajtów
	
	send_lcd_data(0x00);     // coœ w rodzaju przecinka :)
	send_lcd_data(0x80);
	
	d=d*6;
	while(pomocnicza<6){send_lcd_data(znaki[d]);pomocnicza++;d++;}  // wyœwietlamy dziesi¹tki
	
	pomocnicza=0;         //  bêdzie robiæ za licznik przesy³anych bajtów
	
	j=j*6;
	while(pomocnicza<6){send_lcd_data(znaki[j]);pomocnicza++;j++;}  // wyœwietlamy jednoœci
	
	
	pomocnicza=0;         //  bêdzie robiæ za licznik przesy³anych bajtów
	
	
	while(pomocnicza<6){send_lcd_data(litera_V[pomocnicza]);pomocnicza++;}  // wyœwietlamy litere V
	
	send_lcd_data(0x00);  // kilka spacji
	send_lcd_data(0x00);
	send_lcd_data(0x00);
	send_lcd_data(0x00);
	send_lcd_data(0x00);  // kilka spacji
	send_lcd_data(0x00);

	
}
void pomiar_temp(unsigned char wspolrzedna_x, unsigned char wspolrzedna_y, unsigned char znaki[])
{
	unsigned char st_C[] =                           // symbol stopni Celcjusza
	{
		0x00,0x06,0x06,0x00,0x7c,0x82,0x82,0x44
	};
	
	
	
	unsigned char termometr[] =
	{
		0x00,0x80,0xfe,0xaa,0x00,
	};
	unsigned short pomocnicza;
	unsigned short pomiar;
	unsigned char temp;
	unsigned char skladnik;
	unsigned short suma;
	unsigned char dt;
	unsigned char jt;
	
	
	temp=0;
	skladnik=0;
	suma=0;
	
	
	ADMUX = 0x47;            //  w³¹czamy ADC7 na którym jest ntc
	ADCSRA |= (1<<ADSC); //ADSC: uruchomienie pojedynczej konwersji
	while(ADCSRA & (1<<ADSC)); //czeka na zakoñczenie konwersji
	pomiar=ADC;
	
	pomocnicza=pomiar;
	
	send_lcd_picture(wspolrzedna_x, wspolrzedna_y, 5, 8, termometr);
	
	if(pomocnicza<436)          // wyœwietla obraz" <0 st C
	{
		send_lcd_data(0x00);
		send_lcd_data(0x10);
		send_lcd_data(0x28);
		send_lcd_data(0x44);
		send_lcd_data(0x82);
		send_lcd_data(0x00);
		send_lcd_data(0x7c);
		send_lcd_data(0x82);
		send_lcd_data(0x82);
		send_lcd_data(0x7c);
		send_lcd_data(0x00);
		send_lcd_data(0x06);
		send_lcd_data(0x06);
		send_lcd_data(0x00);
		send_lcd_data(0x7c);
		send_lcd_data(0x82);
		send_lcd_data(0x82);
		send_lcd_data(0x44);
		send_lcd_data(0x00);
		send_lcd_data(0x00);
		send_lcd_data(0x00);
		
		
	};
	
	
	
	while(pomocnicza>=436)
	{
		pomiar=pomiar-436;
		
		while(pomiar>suma)                         // obliczanie temperatury od 0-70 st C
		{
			if(temp>0) skladnik=15;
			if(temp>10) skladnik=12;
			if(temp>20) skladnik=9;
			if(temp>30) skladnik=7;
			if(temp>40) skladnik=5;
			if(temp>50) skladnik=4;
			if(temp>60) skladnik=3;
			temp++;
			suma=suma+skladnik;
		}
		
		jt=temp%10;
		temp=temp-jt;
		
		dt=temp/10;
		
		temp=0;         // temp bêdzie robiæ za licznik przesy³anych bajtów
		
		dt=dt*6;
		while(temp<6){send_lcd_data(znaki[dt]);temp++;dt++;}
		
		temp=0;
		jt=jt*6;
		while(temp<6){send_lcd_data(znaki[jt]);temp++;jt++;}
		
		temp=0;
		while(temp<8){send_lcd_data(st_C[temp]);temp++;}     // na koñcu znak st C
		
		send_lcd_data(0x00);
		send_lcd_data(0x00);   // dwie spacje
		break;
	}
	
	
}


void lcd_clear(void)
{
	unsigned int a;
	a=0;
	send_lcd_command(0x80);       //ustalamy adres x
	send_lcd_command(0x40);	      //ustalamy adres y

	while(a<505)
	{
		a++;
		send_lcd_data(0x00);

		
	}

}

void lcd_init (void)
{
	send_lcd_command(0x21);

	send_lcd_command(0xc8);
	
	send_lcd_command(0x06);        //wpó³czynnik temp
	
	send_lcd_command(0x11);        // bias
	
	send_lcd_command(0x20);
	
	send_lcd_command(0x08);
	send_lcd_command(0x09);       // piksele w³¹czone
	
	send_lcd_command(0x0C);       // normalne wyœwietlanie niezanegowane
	send_lcd_command(0xc0);       // kontrast minimum wartoœæ 0x80
	
}

void lcd_day_night (void)          // funkcja w³¹cza podœwietlenie w nocy. u¿ywa ADC6 i PD4
{
	ADMUX = 0x46;            //  w³¹czamy ADC6 na którym jest fotorezystor
	ADCSRA |= (1<<ADSC); //ADSC: uruchomienie pojedynczej konwersji
	while(ADCSRA & (1<<ADSC)); //czeka na zakoñczenie konwersji
	if(ADC>370) {send_lcd_command(0x0C); lcd_light_off;}  // obraz normalny œwiat³o wyl¹czone
	if(ADC<310) {send_lcd_command(0x0C); lcd_light_on;}  // obraz normalny œwiat³o wl¹czone
	if(ADC<130) {send_lcd_command(0x0D); lcd_light_on;}	  // obraz zanegowany œwiat³o w³¹czone
}

ISR(TIMER2_OVF_vect)     // przerwanie asynchroniczne z przepe³nienia
{
	czas++;
	if(czas>86399) czas=0;

}

void setup_adress(unsigned char x, unsigned char y)
{
unsigned char adres_x;
unsigned char adres_y;	

adres_x=0x80;             // sta³a wartoœæ któr¹ LCD interpretuje jako adres
adres_y=0x40;             // jak wy¿ej
adres_x=adres_x+x;
adres_y=adres_y+y;

send_lcd_command(adres_x);
send_lcd_command(adres_y);
}
void send_lcd_letter(unsigned char dlugosc_litery, unsigned char litera[])    // funkcja wysy³a do LCD znaki jeden po drugim. Adres na lcd ustalamy w innej funkcji
{                     // wspó³rzêdna x  wspó³rzêdna y   szerokosc obrazka w pix        wysokosc obrazka w pix        bajt danych

unsigned char element;
dlugosc_litery-=1;         // elementy tablic liczymy od 0 wiêc musimy odj¹æ 1  



element=0;

while(1)	
{
send_lcd_data(litera[element]);
element+=1;
if(element==dlugosc_litery) break;	
}	


		
}

void wyslij_bajt(unsigned char bajt)
{
	clk_spi_off;
	dane_spi_off;
	unsigned char a;
	unsigned char b;
	unsigned char c;
	unsigned char d;
	unsigned char e;
	unsigned char f;
	unsigned char g;
	unsigned char h;
	
	
	a=bajt % 2;
	bajt>>=1;
	
	b=bajt % 2;
	bajt>>=1;
	
	c=bajt % 2;
	bajt>>=1;
	
	d=bajt % 2;
	bajt>>=1;
	
	e=bajt % 2;
	bajt>>=1;
	
	f=bajt % 2;
	bajt>>=1;
	
	g=bajt % 2;
	bajt>>=1;
	
	h=bajt % 2;
	
	
	
	if(a==1) dane_spi_on;
	else dane_spi_off;
	_delay_us(120);
	clk_spi_on;
	_delay_us(240);
	clk_spi_off;
	_delay_us(120);
	
	
	if(b==1) dane_spi_on;
	else dane_spi_off;
	_delay_us(120);
	clk_spi_on;
	_delay_us(240);
	clk_spi_off;
	_delay_us(120);
	
	
	if(c==1) dane_spi_on;
	else dane_spi_off;
	_delay_us(120);
	clk_spi_on;
	_delay_us(240);
	clk_spi_off;
	_delay_us(120);
	
	
	if(d==1) dane_spi_on;
	else dane_spi_off;
	_delay_us(120);
	clk_spi_on;
	_delay_us(240);
	clk_spi_off;
	_delay_us(120);
	
	
	if(e==1) dane_spi_on;
	else dane_spi_off;
	_delay_us(120);
	clk_spi_on;
	_delay_us(240);
	clk_spi_off;
	_delay_us(120);
	
	
	if(f==1) dane_spi_on;
	else dane_spi_off;
	_delay_us(120);
	clk_spi_on;
	_delay_us(240);
	clk_spi_off;
	_delay_us(120);
	
	
	if(g==1) dane_spi_on;
	else dane_spi_off;
	_delay_us(120);
	clk_spi_on;
	_delay_us(240);
	clk_spi_off;
	_delay_us(120);
	
	
	if(h==1) dane_spi_on;
	else dane_spi_off;
	_delay_us(120);
	clk_spi_on;
	_delay_us(240);
	clk_spi_off;
	_delay_us(120);
	
	
}

int main(void)
{
	
	
	unsigned char cyfry[] =
	{
		0x00,0x7c,0x82,0x82,0x82,0x7c,   //-0
		0x00,0x08,0x04,0xfe,0x00,0x00,   //-1
		0x00,0x84,0xc2,0xa2,0x92,0x8c,   //-2
		0x00,0x44,0x82,0x92,0x92,0x6c,  // -3
		0x00,0x30,0x28,0x24,0x22,0xfe,  // -4
		0x00,0x5e,0x92,0x92,0x92,0x62,   //-5
		0x00,0x7c,0x92,0x92,0x92,0x64,   //-6
		0x00,0x02,0xc2,0x32,0x0a,0x06,   //-7
		0x00,0x6c,0x92,0x92,0x92,0x6c,   //-8
		0x00,0x4c,0x92,0x92,0x92,0x7c,  // -9
	};
	unsigned char kulka [] =
	{
		0x3c,0x7e,0x7e,0x3c

	};
    unsigned char czysc_kulke [] =
	{
		0x00, 0x00, 0x00, 0x00
	};
	unsigned char kursor[] =
	{
		0x03,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x03
	};
	unsigned char czysc_kursor[] =
	{
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	};
    unsigned char fala [] =
    {
	0x10,0x00,0x28,0x10,0x44,0x38,0x82,0x7c
    };
	unsigned char litera_a []=
{
0x00,0x80,0xc0,0xba,0x26,0xb8,0xc0,0x80	
};
    unsigned char litera_b []=
{
0x00,0x82,0xfe,0x92,0x92,0x92,0x6c	
};

unsigned char litera_c []=
{
0x00,
0x7c,0x82,0x82,0x82,0x44	
};

unsigned char litera_d []=
{
0x00,0x82,0xfe,0x82,0x82,0x44,0x38	
};

unsigned char litera_e []=
{
0x00,0x82,0xfe,0x92,
0xba,0xc6	
};

unsigned char litera_f []=
{
0x00,0x82,0xfe,0x92,0x3a,0x06	
};

unsigned char litera_g []=
{
0x00,0x7c,0x82,0x82,0xa2,0x66,0x20	
};

unsigned char litera_h []=
{
0x00,
0x82,0xfe,0x92,0x10,0x92,0xfe,0x82	
};

unsigned char litera_i []=
{
0x00,0x82,0x82,0xfe,0x82,0x82	
};

unsigned char litera_j []=
{
0x00,0x60,0x82,
0x82,0x7e,0x02	
};

unsigned char litera_k []=
{
0x00,0x82,0xfe,0x92,0x10,0x2a,0xc6,0x82	
};

unsigned char litera_l []=
{
0x00,0x82,0xfe,0x82,
0x80,0xe0	
};

unsigned char litera_m []=
{
0x00,0x82,0xfe,0x8e,0x10,0x8e,0xfe,0x82	
};

unsigned char litera_n []=
{
0x00,0x82,0xfe,0x8e,0x30,0xc2,
0xfe,0x02	
};

unsigned char litera_o []=
{
0x00,0x7c,0x82,0x82,0x82,0x7c	
};

unsigned char litera_p []=
{
0x00,0x82,0xfe,0xa2,0x22,0x1c	
};

unsigned char litera_r []=
{
0x00,0x82,
0xfe,0xa2,0x22,0x5c,0x80	
};

unsigned char litera_s []=
{
0x00,0xcc,0x92,0x92,0x94,0x66	
};

unsigned char litera_t []=
{
0x00,0x06,0x82,0xfe,0x82,
0x06	
};

unsigned char litera_u []=
{
0x00,0x02,0x7e,0x82,0x80,0x82,0x7e	
};

unsigned char litera_w []=
{
0x00,0x02,0x7e,0x82,0x78,0x82,0x7e,0x02	
};

unsigned char litera_y []=
{

0x00,0x02,0x06,0x8a,0xf0,0x8a,0x06,0x02	
};

unsigned char litera_z []=
{
0x00,0xc6,0xa2,0x92,0x8a,0xc6, 0x00	
};
	
	
	DDRC=0x00;              // same wejsca
	PORTC=0x38;            // pull na wejœcia: PC3, PC4 i PC5 (enkoer)
	DDRD=0x3F;              // PD7 i PD6 to wejœcia reszta to wyjœcia
	PORTD=0xC0;            // PULL na PD7 i PD6
	ADC_init();
	TIMER2_SETUP();
	unsigned char encoder;          // zmienna do obs³ugi enkodera
	encoder=1;
	
	while(1)
	{
		lcd_on;
		_delay_ms(100);
		lcd_init();
		lcd_day_night();
		lcd_clear();
		
		while(1)         // ekran g³ówny
		{ ekran_glowny:
			while(esc_push){_delay_ms(33); lcd_clear();}        // czekamy na zwolnienie przycisku
			
			lcd_day_night();
			godzina(0, 0, cyfry);  // dwie pierwsze wartosci to wspolrzedne trzecia wartosc to wyswietlane znaki
			pomiar_swiatla(0, 1, cyfry);
			pomiar_temp(0, 2, cyfry);
			pomiar_baterii(0, 3, cyfry);
			
			
			
			if enc_push {_delay_ms(1); lcd_clear(); break;};
			if enter_push {_delay_ms(1); lcd_clear(); break;};
		}                                                           // koniec ekranu g³ównego
		
		while(1)    // menu g³ówne
		{
			menu:
			lcd_day_night();
			encoder=1;
			
			while(enc_push)
			_delay_ms(1);
			while(enter_push)
			_delay_ms(1);
			while(esc_push);
			_delay_ms(33);
			
			
			setup_adress(6, 0);            // ustawiamy adres na lcd pzed napisaniem 
			send_lcd_letter(8, litera_c);
			send_lcd_letter(8, litera_z);
			send_lcd_letter(8, litera_a);
			send_lcd_letter(8, litera_s);   // napis CZAS z³o¿ony z liter
			
			setup_adress(6, 1);
			send_lcd_letter(8, litera_s);
			send_lcd_letter(8, litera_p);
			send_lcd_letter(8, litera_i);
			send_lcd_picture(25, 1, 8, 8, fala);
			
			setup_adress(6, 2);
			send_lcd_letter(8, litera_b);
			send_lcd_letter(8, litera_a);
			send_lcd_letter(8, litera_t);
			send_lcd_letter(8, litera_e);
			send_lcd_letter(8, litera_r);
			send_lcd_letter(8, litera_i);
			send_lcd_letter(8, litera_a);
			
			setup_adress(0, 3);
			send_lcd_letter(8, litera_a);
			send_lcd_letter(8, litera_b);
			send_lcd_letter(8, litera_c);
			send_lcd_letter(8, litera_d);
			send_lcd_letter(8, litera_e);
			send_lcd_letter(8, litera_f);
			send_lcd_letter(8, litera_g);
			send_lcd_letter(8, litera_h);
			send_lcd_letter(8, litera_i);
			send_lcd_letter(8, litera_j);
			setup_adress(0, 4);
			send_lcd_letter(8, litera_k);
			send_lcd_letter(8, litera_l);
			send_lcd_letter(8, litera_m);
			send_lcd_letter(8, litera_n);
			send_lcd_letter(8, litera_o);
			send_lcd_letter(8, litera_p);
			send_lcd_letter(8, litera_r);
			send_lcd_letter(8, litera_s);
			send_lcd_letter(8, litera_t);
			send_lcd_letter(8, litera_u);
			setup_adress(0, 5);
			send_lcd_letter(8, litera_w);
			send_lcd_letter(8, litera_y);
			send_lcd_letter(8, litera_z);
			
			
			
			
			while(PINC &0x30)         // enkoder musi byæ wyzerowany
			{
				lcd_day_night();
				while(!(PINC &0x10))      // obs³uga enkodera
				{
					encoder--;
					while(!(PINC &0x10))
					while(!(PINC &0x30))
					while(!(PINC &0x20));
					
				}
				
				while(!(PINC &0x20))
				{
					encoder++;
					while(!(PINC &0x20))
					while(!(PINC &0x30))
					while(!(PINC &0x10));
					
				}	         // koniec obs³ugi enkodera
				
				if(encoder>3) encoder=1;
				if(encoder<1) encoder=3;
				switch(encoder)
				{
					case 1: {send_lcd_picture(1, 0, 4, 8, kulka); send_lcd_picture(1, 1, 4, 8, czysc_kulke); send_lcd_picture(1, 2, 4, 8, czysc_kulke);};
					break;
					case 2: {send_lcd_picture(1, 1, 4, 8, kulka); send_lcd_picture(1, 2, 4, 8, czysc_kulke); send_lcd_picture(1, 0, 4, 8, czysc_kulke);};
					break;
					case 3: {send_lcd_picture(1, 2, 4, 8, kulka); send_lcd_picture(1, 1, 4, 8, czysc_kulke); send_lcd_picture(1, 0, 4, 8, czysc_kulke); };
					break;
					
				}
				
				if(enc_push)
				{
					_delay_ms(10);
					lcd_clear();
					switch(encoder)
					{
						case 1: goto menu_czasu;
						break;
						case 2: goto menu_sterowania;
						break;
					}
				}
				
				if(enter_push)
				{
					_delay_ms(10);
					lcd_clear();
					switch(encoder)
					{
						case 1: goto menu_czasu;
						break;
						case 2: goto menu_sterowania;
						break;
					}
					
				}
				
				
				
				
				
				if (esc_push) {_delay_ms(33); lcd_clear(); goto ekran_glowny;};
			}
			
			
			
			
		}         //koniec menu g³ównego
		
		
		while(1)  // MENU CZASU
		{
			menu_czasu:
			lcd_day_night();
			encoder=1;
			while(enc_push)
			_delay_ms(1);
			while(enter_push)
			_delay_ms(1);
			while(esc_push);
			_delay_ms(33);
			
			
			
			
			
			
			
			setup_adress(0, 0);
			send_lcd_letter(8, litera_u);
			send_lcd_letter(7, litera_s);
			send_lcd_letter(7, litera_t);
			send_lcd_letter(8, litera_a);
			send_lcd_letter(8, litera_w);
			send_lcd_data(0x00);
			send_lcd_data(0x00);
			send_lcd_data(0x00);
			send_lcd_letter(7, litera_g);
			send_lcd_letter(7, litera_o);
			send_lcd_letter(8, litera_d);
			send_lcd_letter(7, litera_z);
			send_lcd_letter(7, litera_i);
			send_lcd_letter(8, litera_n);
			send_lcd_letter(8, litera_e);
			
			unsigned char k; // pomocnicza przy polo¿eniu kursora
			k=1;
			
			
			while(1)
			{
				godzina(15, 2, cyfry);
				if(k==1)
				
				{
					send_lcd_picture(25, 3, 11, 8, kursor);
					send_lcd_picture(39, 3, 11, 8, czysc_kursor);
				}
				
				if(k==2)
				{
					send_lcd_picture(39, 3, 11, 8, kursor);
					send_lcd_picture(25, 3, 11, 8, czysc_kursor);
				}
				
				if(k>2) k=1;
				
				if(enc_push){_delay_ms(100); k++; while(enc_push); _delay_ms(100);};
				if(enter_push){_delay_ms(100); k++; while(enter_push); _delay_ms(100);};
				
				while(!(PINC &0x10))      // obs³uga enkodera
				{
					if(k==1) czas+=3600;
					if(k==2) czas+=60;
					while(!(PINC &0x10))
					while(!(PINC &0x30))
					while(!(PINC &0x20));
					
					
				}
				
				while(!(PINC &0x20))
				{
					if(k==1) czas-=3600;
					if(k==2) czas-=60;
					while(!(PINC &0x20))
					while(!(PINC &0x30))
					while(!(PINC &0x10));
					
					
				}	         // koniec obs³ugi enkodera
				if(czas>86399) czas=86399;
				if(esc_push) {_delay_ms(10); lcd_clear(); goto menu;}
			}
			
			
			}        // KONIEC MENU CZASU
			
			while(1)    //menu sterowania
			{
			menu_sterowania:
			
			
			lcd_day_night();
			encoder=1;
			while(enc_push)
			_delay_ms(1);
			while(enter_push)
			_delay_ms(1);
			while(esc_push);
			_delay_ms(33);
			setup_adress(26, 0);
			send_lcd_letter(8, litera_s);
			send_lcd_letter(8, litera_p);
			send_lcd_letter(8, litera_i);
			send_lcd_picture(48, 0, 8, 8, fala);
			
			setup_adress(5, 1);
			send_lcd_letter(8, litera_s);
			send_lcd_letter(8, litera_t);
			send_lcd_letter(8, litera_e);
			send_lcd_letter(8, litera_r);
			send_lcd_letter(8, litera_o);
			send_lcd_letter(8, litera_w);
			send_lcd_letter(8, litera_a);
			send_lcd_letter(8, litera_n);
			send_lcd_letter(8, litera_i);
			send_lcd_letter(8, litera_e);
			send_lcd_data(0x00);  // spacja
			send_lcd_data(0x28);  // dwukropek
			
			setup_adress(6, 3);
			send_lcd_letter(8, litera_m);
			send_lcd_letter(8, litera_a);
			send_lcd_letter(8, litera_n);
			send_lcd_letter(8, litera_u);
			send_lcd_letter(8, litera_a);
			send_lcd_letter(8, litera_l);
			send_lcd_letter(8, litera_n);
			send_lcd_letter(8, litera_e);
			
			setup_adress(6, 4);
			send_lcd_letter(8, litera_a);
			send_lcd_letter(8, litera_u);
			send_lcd_letter(7, litera_t);
			send_lcd_letter(8, litera_o);
			
			
			unsigned char cze;
			cze=0;
			unsigned char zie;
			zie=0;
			unsigned char nie;
			nie=0;
			
			
			
				 _delay_ms(999);
				 wyslij_bajt(0);
				 _delay_ms(10);
				 wyslij_bajt(1);
				 _delay_ms(999);
		while(1)	
		{
		cze=0;
		zie=0;	 
		nie=0;	
		wyslij_bajt(1);
		wyslij_bajt(cze);
		wyslij_bajt(zie);
		wyslij_bajt(nie);
		
		while(1)
		{
		while(cze<255)
		{
		cze+=5;
		
		
		if(esc_push) {_delay_ms(10); lcd_clear(); goto menu;}
		wyslij_bajt(1);
		wyslij_bajt(cze);
		wyslij_bajt(zie);
		wyslij_bajt(nie);	
		}
		
		while(cze>0)
		{
		cze-=5;
		
		
		if(esc_push) {_delay_ms(10); lcd_clear(); goto menu;}
		wyslij_bajt(1);
		wyslij_bajt(cze);
		wyslij_bajt(zie);
		wyslij_bajt(nie);	
		}
			
		}
		
		
		
		}
			
			
			
			
			
			
			if(esc_push) {_delay_ms(10); lcd_clear(); goto menu;}	
			} // koniec menu sterowania
		
		
	}       // koniec programu g³ównego
	
	
	
}       // koniec main