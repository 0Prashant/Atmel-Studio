/*
 * lcd.c
 *
 * Created: 6/2/2017 7:31:04 AM
 * Author : sansii
 */ 

#include <avr/io.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>


#define databus PORTB
#define databus_dd DDRB
#define lcd_control PORTD
#define lcd_control_data DDRB
#define rs 0
#define rw 1
#define en 2
void check_busy(void); //check lcd weather it is busy or not it will read data or not
void  enable_lcd(void);//make lcd on and off it flashes the lcd condition
void set_cmd(unsigned char cmd);
void  set_ch(char ch);
void set_strings(char *c);
void set_num(char num);
void initilize(void);


int main(void)
{initilize();
 char a[5]="sansi";  /* Replace with your application code */
 
	   
	   set_strings("sansii");
	
_delay_ms(1000);
		
		
      	  	  
  }
  
    while (1) 
    {
	
		
    }
}


void check_busy(void)
{
	DDRB = 0x00;
	lcd_control |= 1<<rw;
	lcd_control &= ~(1<<rs);
	while(databus >= 0x80)
	{
		enable_lcd();
	}
	DDRB = 0xff;
	
	
}
void  enable_lcd(void)
{
	lcd_control |= 1<<en;
	asm volatile ("nop");
	asm volatile ("nop");
	lcd_control &= ~(1<<en);
	
}
void set_cmd(unsigned char cmd)
{   check_busy();
	databus = cmd;
	lcd_control &= ~((1<<rs) | (1<<rw));
	enable_lcd();
	databus = 0;
	
	
	
}
void  set_ch(char ch)
{  check_busy();
	databus = ch;
	lcd_control &= ~(1<<rw);
	lcd_control |= (1<<rs);
	enable_lcd();
	databus = 0;
}
void set_strings(char *c)
{   while(*c>0)
	{
		set_ch(*c++);
	}
}
void set_num(char num)
{
	char n[5];
	itoa(num,n,10);
	set_strings(n);
}
void initilize()
{
	DDRD |= 1<<rw | 1 << rs | 1<< en;
	_delay_ms(15);
	set_cmd(0x01);//clear screen
	_delay_ms(2);
	set_cmd(0x38);
	_delay_us(50);
	set_cmd(0b00001110);
	_delay_us(50 );
	
}