#include "XPT2046.c"


#define scale_value                                   (VDD_in_mV / ADC_count_max)
#define RL                                            100.0
#define LDR_Constant                                  500000.0
#define B                                             3950.0
#define RT                                            10000.0
#define _25C_in_K                                     298.0


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


const unsigned char symbol[8] = {0x06, 0x09, 0x09, 0x06, 0x00, 0x00, 0x00, 0x00};


void setup();
void load_fixed_items();
void load_symbol(unsigned char pos_row, unsigned char pos_char);
void lcd_print_i_value(unsigned char x_pos, unsigned char y_pos, signed long value);


void main()
{
     float light = 0;
     float temp = 0;
     float R_inf = 0;

     unsigned int ain0 = 0x0000;
     unsigned int ain1 = 0x0000;
     unsigned int ain2 = 0x0000;
     unsigned int ain3 = 0x0000;

     setup();
     load_fixed_items();

     R_inf = (B / _25C_in_K);
     R_inf *= -1;
     R_inf = exp(R_inf);
     R_inf *= RT;

     while(1)
     {
         ain0 = XPT2046_read_ADC(ch0, (ADC_res_12 | single_ended_ADC | power_down_between_conversions_IRQ_enabled));

         lcd_print_i_value(4, 1, ain0);
         lcd_print_i_value(16, 1, (ain0 * scale_value));

         ain1 = XPT2046_read_ADC(ch1, (ADC_res_12 | single_ended_ADC | power_down_between_conversions_IRQ_enabled));

         lcd_print_i_value(4, 2, ain1);

         temp = ain1;
         temp = (ADC_count_max / temp);
         temp -= 1.0;
         temp *= RT;
         temp /= R_inf;
         temp = log(temp);
         temp = (B / temp);
         temp -= 273.0;

         lcd_print_i_value(16, 2, ((signed long)temp));


         ain2 = XPT2046_read_ADC(ch2, (ADC_res_12 | single_ended_ADC | power_down_between_conversions_IRQ_enabled));

         lcd_print_i_value(4, 3, ain2);

         light = ain2;
         light = (ADC_count_max / light);
         light -= 1.0;
         light *= RL;
         light = (LDR_Constant / light);

         lcd_print_i_value(16, 3, light);

         ain3 = XPT2046_read_ADC(ch3, (ADC_res_12 | single_ended_ADC | power_down_between_conversions_IRQ_enabled));

         lcd_print_i_value(4, 4, ain3);
         lcd_print_i_value(16, 4, (ain3 * scale_value));

         delay_ms(600);
     }
}


void setup()
{
    PORTA = 0x00;
    DDRA = 0xF0;
    PORTB = 0x00;
    DDRB = 0x00;
    PORTC = 0x00;
    DDRC = 0xE0;
    PORTD = 0x80;
    DDRD = 0x70;
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
    
    XPT2046_init();
    
    Lcd_Init();
    Lcd_Cmd(_LCD_CLEAR);
    Lcd_Cmd(_LCD_CURSOR_OFF);

    delay_ms(100);
}


void load_fixed_items()
{
    lcd_out(1, 1, "A0");
    lcd_out(2, 1, "A1");
    lcd_out(3, 1, "A2");
    lcd_out(4, 1, "A3");

    lcd_out(1, 10, "VR/mV");
    lcd_out(2, 10, "Tc/ C");
    lcd_out(3, 10, "LD/Lx");
    lcd_out(4, 10, "Vi/mV");
    load_symbol(2, 13);
}


void load_symbol(unsigned char pos_row, unsigned char pos_char)
{
    unsigned char i = 0x00;

    Lcd_Cmd(64);

    for (i = 0; i <= 7; i++)
    {
        Lcd_Chr_CP(symbol[i]);
    }

    Lcd_Cmd(_LCD_RETURN_HOME);
    Lcd_Chr(pos_row, pos_char, 0);
}


void lcd_print_i_value(unsigned char x_pos, unsigned char y_pos, signed long value)
{
    unsigned char ch = 0x00;

    if(value < 0)
    {
        value = -value;
        lcd_out(y_pos, x_pos, "-");
    }
    else
    {
        lcd_out(y_pos, x_pos, " ");
    }

    if((value > 999) && (value <= 9999))
    {
        ch = (((value % 10000)/ 1000) + 0x30);
        lcd_chr_cp(ch);
        ch = (((value % 1000) / 100) + 0x30);
        lcd_chr_cp(ch);
        ch = (((value % 100) / 10) + 0x30);
        lcd_chr_cp(ch);
        ch = ((value % 10) + 0x30);
        lcd_chr_cp(ch);
    }
    else if((value > 99) && (value <= 999))
    {
        ch = 0x20;
        lcd_chr_cp(ch);
        ch = (((value % 1000) / 100) + 0x30);
        lcd_chr_cp(ch);
        ch = (((value % 100) / 10) + 0x30);
        lcd_chr_cp(ch);
        ch = ((value % 10) + 0x30);
        lcd_chr_cp(ch);
    }
    else if((value > 9) && (value <= 99))
    {
        ch = 0x20;
        lcd_chr_cp(ch);
        ch = 0x20;
        lcd_chr_cp(ch);
        ch = (((value % 100) / 10) + 0x30);
        lcd_chr_cp(ch);
        ch = ((value % 10) + 0x30);
        lcd_chr_cp(ch);
    }
    else
    {
        ch = 0x20;
        lcd_chr_cp(ch);
        ch = 0x20;
        lcd_chr_cp(ch);
        ch = 0x20;
        lcd_chr_cp(ch);
        ch = ((value % 10) + 0x30);
        lcd_chr_cp(ch);
    }
}