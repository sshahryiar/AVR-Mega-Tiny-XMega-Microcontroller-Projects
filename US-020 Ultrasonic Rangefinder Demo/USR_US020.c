#define trigger_pin             PORTD3_bit
#define echo_pin                PIND2_bit


#define high                    1
#define low                     0


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


void setup();
void lcd_print_value(unsigned char x_pos, unsigned char y_pos, unsigned int value);
void send_sonar_burst();


void main()
{
     unsigned long timeout = 0;
     unsigned long range = 0;
     unsigned int pulse_width = 0;

     setup();
     lcd_out(1, 1, "P.Width/uS:");
     lcd_out(2, 1, "Range / mm:");

     while(1)
     {
            range = 0;
            pulse_width = 0;

            send_sonar_burst();
            timeout = 0;
            while((echo_pin == low) && (timeout < 100000))
            {
                timeout++;
                delay_us(1);
            };
            timeout = 0;
            while((echo_pin == high) && (timeout < 60000))
            {
                delay_us(1);
                pulse_width += 4;
                timeout++;
            };

            range = (pulse_width * 0.34);
            range >>= 1;

            lcd_print_value(12, 1, pulse_width);
            lcd_print_value(12, 2, range);
            delay_ms(1000);
     };
}


void setup()
{
    PORTA = 0x00;
    DDRA = 0xF0;
    PORTB = 0x00;
    DDRB = 0x00;
    PORTC = 0x00;
    DDRC = 0xF0;
    PORTD = 0x00;
    DDRD = 0x08;
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
    GICR = 0x00;
    GIFR = 0x00;
    MCUCR = 0x00;
    EMCUCR = 0x00;
    TIMSK = 0x00;
    UCSRB = 0x00;
    ACSR = 0x80;
    SPCR = 0x00;

    Lcd_Init();
    Lcd_Cmd(_LCD_CLEAR);
    Lcd_Cmd(_LCD_CURSOR_OFF);
    Delay_ms(600);
}


void lcd_print_value(unsigned char x_pos, unsigned char y_pos, unsigned int value)
{
    unsigned char ch = 0x00;

    if(value > 9999)
    {
        ch = ((value / 10000) + 0x30);
        lcd_chr(y_pos, x_pos, ch);
        ch = (((value % 10000)/ 1000) + 0x30);
        lcd_chr_cp(ch);
        ch = (((value % 1000) / 100) + 0x30);
        lcd_chr_cp(ch);
        ch = (((value % 100) / 10) + 0x30);
        lcd_chr_cp(ch);
        ch = ((value % 10) + 0x30);
        lcd_chr_cp(ch);
    }

    else if((value > 999) && (value <= 9999))
    {
        ch = 0x20;
        lcd_chr(y_pos, x_pos, ch);
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
        lcd_chr(y_pos, x_pos, ch);
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
        lcd_chr(y_pos, x_pos, ch);
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
        lcd_chr(y_pos, x_pos, ch);
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


void send_sonar_burst()
{
     trigger_pin = high;
     delay_us(20);
     trigger_pin = low;
}