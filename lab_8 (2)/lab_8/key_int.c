#include <at89c5131.h>
#include "lcd.h"
#include <stdio.h>
#include <math.h>
#include <string.h>

code unsigned char display_msg1[] = "SA(LOW)";
code unsigned char display_msg2[] = "RE";
code unsigned char display_msg3[] = "GA";
code unsigned char display_msg4[] = "MA";
code unsigned char display_msg5[] = "PA";
code unsigned char display_msg6[] = "DHA";
code unsigned char display_msg7[] = "NI";
code unsigned char display_msg8[] = "SA(HIGH)";
code unsigned char display_msg9[] = "SILENCE";
int entered_pass= 0 ;
sbit tone=P0^0;
int count_freq;
int a;
char b;
char k;

struct Out1{
	int freq;
	char out[3];
} Output;

char keypad[4][4] = { '1', '2', '3', 'A',
											'4', '5', '6', 'B',
											'7', '8', '9', 'C',
											'*', '0', '#', 'D'};
char display[9][9]={"SA(LOW)","RE","GA","MA","PA","DHA","NI","SA(HIGH)","SILENCE"};

///int count_dur;

unsigned char colloc, rowloc;
														
void Output_func(char k)
{
	//k = keypad[rowloc][colloc];
	switch(k)
	{
		case '1':
			Output.freq = 240;
			strcpy(Output.out, "Sa");
			break;
		
		case '2':
			Output.freq = 270;
			strcpy(Output.out, "Re");
			break;
		
		case '3':
			Output.freq = 300;
			strcpy(Output.out, "Ga");
			break;
		
		case '4':
			Output.freq = 320;
			strcpy(Output.out, "Ma");
			break;
		
		case '5':
			Output.freq = 360;
			strcpy(Output.out, "Pa");
			break;
		
		case '6':
			Output.freq = 400;
			strcpy(Output.out, "Dha");
			break;
		
		case '7':
			Output.freq = 450;
			strcpy(Output.out, "Ni");
			break;
		
		case '8':
			Output.freq = 480;
			strcpy(Output.out, "Sa");
			break;
		
		case '9':
			Output.freq = 0;
			strcpy(Output.out, "Sil");
			break;
		
		default:
			Output.freq = 0;
			strcpy(Output.out, "#$%");
	}
	
	lcd_init();
	lcd_cmd(0x80);
	lcd_write_string(Output.out);
	
	
}
void value(int freq)
{
	
	count_freq = (int) (- (1000000/(freq)));
	TL0 = count_freq&0xFF;
	TH0 = (count_freq>>8)&0xFF;
	
	TR0= 1;
}
void tone_note () interrupt 1
{ 
	tone = ~tone;
	TL0 = count_freq&0xFF;
	TH0 = (count_freq>>8)&0xFF;
	TR0 = 1;
}
void begin(int freq)
{
	TMOD = 0x01; //mode 1 timer 0 and timer 1
	ET0 = 1; //activate interrupts for timer 0 and timer 1
	EA = 1;  //activate global interrupts
	value(freq);
}
void music(){
	
	begin(Output.freq);
}

void main (void)
{
	lcd_init();	
	lcd_cmd(0x80);													//Move cursor to first line
	msdelay(4);
	lcd_write_string(display_msg1);
	P3 = 0x0F;
	while(1)
	{
		do
		{
			P3 = 0x0F;
			colloc = P3;
			colloc &= 0x0F;
		}while(colloc != 0x0F);
	do
		
	{	
		msdelay(20);
		colloc = P3;
		colloc &= 0x0F;
	}while(colloc == 0x0F);
	
	while(1)
	{
		P3 = 0xEF;
		colloc = P3;
		colloc &= 0x0F;
		if (colloc != 0x0F)
		{
			rowloc = 0;
			break;
		}
		P3 = 0xDF;
		colloc = P3;
		colloc &= 0x0F;
		if (colloc != 0x0F)
		{
			rowloc = 1;
			break;
		}
		P3 = 0xBF;
		colloc = P3;
		colloc &= 0x0F;
		if (colloc != 0x0F)
		{
			rowloc = 2;
			break;
		}
		P3 = 0x7F;
		colloc = P3;
		colloc &= 0x0F;
		rowloc = 3;
		break;
	}
	
	if (colloc == 0x0E)
	{entered_pass = keypad[rowloc][3];
		k = entered_pass;
		a= b-1;													
		Output_func(k);
		music();
		}
	else if (colloc == 0x0D)
	{entered_pass = keypad[rowloc][2];
		k = entered_pass;
		a= b-1;													
		Output_func(k);
		music();
	}
	else if (colloc == 0x0B)
	{entered_pass = keypad[rowloc][1];
		k = entered_pass;
		a= b-1;												
		msdelay(4);
		Output_func(k);
		music();
	}
	else
	{entered_pass = keypad[rowloc][0];
		k = entered_pass;
		a= b-1;												
		Output_func(k);
		music();
	}
	}
}

