#include "MCP3008.c"


sbit LCD_RS at PORTC6_bit;
sbit LCD_EN at PORTC7_bit;
sbit LCD_D4 at PORTA4_bit;
sbit LCD_D5 at PORTA5_bit;
sbit LCD_D6 at PORTA6_bit;
sbit LCD_D7 at PORTA7_bit;

sbit LCD_RS_Direction at DDC6_bit;
sbit LCD_EN_Direction at DDC7_bit;
sbit LCD_D4_Direction at DDA4_bit;
sbit LCD_D5_Direction at DDA5_bit;
sbit LCD_D6_Direction at DDA6_bit;
sbit LCD_D7_Direction at DDA7_bit;


void setup(void);
void lcd_print_value(unsigned char x_pos, unsigned char y_pos, signed int value);


void main(void)
{
     signed int T_value = 0x00000;
     
     setup();
     
     Lcd_Out(1, 1, "CH0:");
     Lcd_Out(2, 1, "CH1:");
     Lcd_Out(3, 1, "CH2:");
     Lcd_Out(4, 1, "CH3:");
     Lcd_Out(1, 12, "CH4:");
     Lcd_Out(2, 12, "CH5:");
     Lcd_Out(3, 12, "CH6:");
     Lcd_Out(4, 12, "CH7:");

     while(1)
     {
         T_value = MCP3008_read(MCP3008_S_CH0, MCP3008_SINGLE_MODE);
         lcd_print_value(5, 1, (T_value >> 1));
         
         T_value = MCP3008_read(MCP3008_S_CH1, MCP3008_SINGLE_MODE);
         lcd_print_value(5, 2, (T_value >> 1));
         
         T_value = MCP3008_read(MCP3008_S_CH2, MCP3008_SINGLE_MODE);
         lcd_print_value(5, 3, (T_value >> 1));

         T_value = MCP3008_read(MCP3008_S_CH3, MCP3008_SINGLE_MODE);
         lcd_print_value(5, 4, (T_value >> 1));
         
         T_value = MCP3008_read(MCP3008_S_CH4, MCP3008_SINGLE_MODE);
         lcd_print_value(16, 1, (T_value >> 1));

         T_value = MCP3008_read(MCP3008_S_CH5, MCP3008_SINGLE_MODE);
         lcd_print_value(16, 2, (T_value >> 1));

         T_value = MCP3008_read(MCP3008_S_CH6, MCP3008_SINGLE_MODE);
         lcd_print_value(16, 3, (T_value >> 1));

         T_value = MCP3008_read(MCP3008_S_CH7, MCP3008_SINGLE_MODE);
         lcd_print_value(16, 4, (T_value >> 1));
         
         delay_ms(100);
     };
}


void setup(void)
{
    PORTA = 0x00;
    DDRA = 0xF0;
    PORTB = 0x00;
    DDRB = 0x00;
    PORTC = 0x00;
    DDRC = 0xE0;
    PORTD = 0x00;
    DDRD = 0x00;
    PORTE = 0x00;
    DDRE = 0x00;
    TCCR0 = 0x00;
    TCNT0 = 0x00;
    OCR0 = 0x00;
    TCCR1A = 0x00;
    TCCR1B = 0x00;
    TCNT1H = 0x00;
    TCNT1L = 0x00;
    ICR1H = 0x00;
    ICR1L = 0x00;
    OCR1AH = 0x00;
    OCR1AL = 0x00;
    OCR1BH = 0x00;
    OCR1BL = 0x00;
    MCUCR = 0x00;
    EMCUCR = 0x00;
    TIMSK = 0x00;
    UCSRB = 0x00;
    ACSR = 0x80;
    SPCR = 0x00;
    SPSR = 0x00;

    Lcd_Init();
    Lcd_Cmd(_LCD_CLEAR);
    Lcd_Cmd(_LCD_CURSOR_OFF);
    
    MCP3008_init();
    
    Delay_ms(10);
}


void lcd_print_value(unsigned char x_pos, unsigned char y_pos, signed int value)
{
    unsigned char ch[6] = {0x20, 0x20, 0x20, 0x20, 0x20, '\0'};

    if(value < 0)
    {
        ch[0] = 0x2D;
        value = -value;
    }
    else
    {
        ch[0] = 0x20;
    }

    if((value > 999) && (value <= 9999))
    {
        ch[1] = (((value % 10000)/ 1000) + 0x30);
        ch[2] = (((value % 1000) / 100) + 0x30);
        ch[3] = (((value % 100) / 10) + 0x30);
        ch[4] = ((value % 10) + 0x30);
    }
    else if((value > 99) && (value <= 999))
    {
        ch[1] = 0x20;
        ch[2] = (((value % 1000) / 100) + 0x30);
        ch[3] = (((value % 100) / 10) + 0x30);
        ch[4] = ((value % 10) + 0x30);
    }
    else if((value > 9) && (value <= 99))
    {
        ch[1] = 0x20;
        ch[2] = 0x20;
        ch[3] = (((value % 100) / 10) + 0x30);
        ch[4] = ((value % 10) + 0x30);
    }
    else
    {
        ch[1] = 0x20;
        ch[2] = 0x20;
        ch[3] = 0x20;
        ch[4] = ((value % 10) + 0x30);
    }

    lcd_out(y_pos, x_pos, ch);
}