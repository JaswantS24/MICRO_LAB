#include <at89c5131.h>
sbit mybit=	P1^5;
sbit out = P0^7;
unsigned char m;

void T1(void) interrupt 3
{
	mybit=~mybit;
	m=m+1;
	TL1 = 0xB0;
	TH1 = 0x3C;
}

void T0(void) interrupt 1
{
	out=~out;
	
	while(m<20){
	TL0 = 0xB9;
	TH0 = 0xEF;
	}
	while(m<50 && m>19){
		TL0 = 0x89;
		TH0 = 0xF1;
	}
	while(m<90 && m>49){
		TL0 = 0xFB;
		TH0 = 0xF2;
	}
	while(m<110 && m>89){
		TL0 = 0xCB;
	  TH0 = 0xF3;
	}
	while(m<150 && m>109){
	  TL0 = 0x26;
	  TH0 = 0xF5;
	}
	while(m<180 && m>149){
	  TL0 = 0x3C;
	  TH0 = 0xF6;
	}
	while(m<220 && m>179){
	  TL0 = 0x52;
	  TH0 = 0xF7;
	}
		while(m<240 && m>219){
	  TL0 = 0xDD;
	  TH0 = 0xF7;
		}			
}

void main(void){
	while(m<20){
		TMOD = 0x11;
		TL0 = 0xB9;
		TH0 = 0xEF;
		TL1 = 0xB0;
		TH1 = 0x3C;
		ET0 = 1; //activate interrupts for both timers
		ET1 = 1;
		EA = 1;  //activate global interrupts
		TR1 = 1;
		TR0 = 1; 	
}
	while(m<50 && m>19){
		TMOD = 0x11;
		TL0 = 0x89;
		TH0 = 0xF1;
		TL1 = 0xB0;
		TH1 = 0x3C;
		ET0 = 1; //activate interrupts for both timers
		ET1 = 1;
		EA = 1;  //activate global interrupts
		TR1 = 1;
		TR0 = 1; 
	}
	
	while(m<90 && m>49){
		TMOD = 0x11;
		TL0 = 0xFB;
		TH0 = 0xF2;
		TL1 = 0xB0;
		TH1 = 0x3C;
		ET0 = 1; //activate interrupts for both timers
		ET1 = 1;
		EA = 1;  //activate global interrupts
		TR1 = 1;
		TR0 = 1; 
	}
	
	while(m<110 && m>89){
		TMOD = 0x11;
	  TL0 = 0xCB;
	  TH0 = 0xF3;
		TL1 = 0xB0;
		TH1 = 0x3C;
		ET0 = 1; //activate interrupts for both timers
		ET1 = 1;
		EA = 1;  //activate global interrupts
		TR1 = 1;
		TR0 = 1; 
	}
	
	while(m<150 && m>109){
		TMOD = 0x11;
	  TL0 = 0x26;
	  TH0 = 0xF5;
		TL1 = 0xB0;
		TH1 = 0x3C;
		ET0 = 1; //activate interrupts for both timers
		ET1 = 1;
		EA = 1;  //activate global interrupts
		TR1 = 1;
		TR0 = 1; 
	}
	
	while(m<180 && m>149){
		TMOD = 0x11;
	  TL0 = 0x3C;
	  TH0 = 0xF6;
		TL1 = 0xB0;
		TH1 = 0x3C;
		ET0 = 1; //activate interrupts for both timers
		ET1 = 1;
		EA = 1;  //activate global interrupts
		TR1 = 1;
		TR0 = 1; 
	}
	
	while(m<220 && m>179){
		TMOD = 0x11;
	  TL0 = 0x52;
	  TH0 = 0xF7;
		TL1 = 0xB0;
		TH1 = 0x3C;
		ET0 = 1; //activate interrupts for both timers
		ET1 = 1;
		EA = 1;  //activate global interrupts
		TR1 = 1;
		TR0 = 1; 
	}
	
	while(m<240 && m>219){
		TMOD = 0x11;
	  TL0 = 0xDD;
	  TH0 = 0xF7;
		TL1 = 0xB0;
		TH1 = 0x3C;
		ET0 = 1; //activate interrupts for both timers
		ET1 = 1;
		EA = 1;  //activate global interrupts
		TR1 = 1;
		TR0 = 1; 
	}
		
}



