#define LED       PORTB6_bit

sbit LCD_RS at PORTB0_bit;
sbit LCD_EN at PORTB1_bit;
sbit LCD_D4 at PORTB2_bit;
sbit LCD_D5 at PORTB3_bit;
sbit LCD_D6 at PORTB4_bit;
sbit LCD_D7 at PORTB5_bit;

sbit LCD_RS_Direction at DDB0_bit;
sbit LCD_EN_Direction at DDB1_bit;
sbit LCD_D4_Direction at DDB2_bit;
sbit LCD_D5_Direction at DDB3_bit;
sbit LCD_D6_Direction at DDB4_bit;
sbit LCD_D7_Direction at DDB5_bit;


void setup();
void UART_Flush();
unsigned char UART_Receive();
void gets(unsigned char *buffer);
void UART_Transmit(unsigned char value);
void putc(unsigned char *ch);


void main() 
{
     unsigned char i = 0;
     unsigned char pwm = 0x00;
     unsigned char buf[5] = {0x20, 0x20, 0x20, 0x20, 0x20};
     
     setup();
     
     while(1)
     {
            LED = 1;
            UART_Transmit('S');
            
            gets(buf);
            delay_ms(10);
            for(i = 1; i < 4; i++)
            {
               lcd_chr(2, (i + 2), buf[i]);
               buf[i] -= 48;
            }
            
            pwm = ((buf[1] * 100) + (buf[2] * 10) + buf[3]);
            OCR0B = pwm;
            
            LED = 0;
            delay_ms(490);
     };
}


void setup()
{
    CLKPR=0x80;
    CLKPR = 0x00;
    PORTA = 0x00;
    DDRA = 0x00;
    PORTB = 0x00;
    DDRB = 0x7F;
    PORTD = 0x00;
    DDRD = 0x20;
    TCCR0A = 0x23;
    TCCR0B = 0x01;
    TCNT0  =0x00;
    OCR0A = 0x00;
    OCR0B = 0x00;
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
    GIMSK = 0x00;
    MCUCR = 0x00;
    TIMSK = 0x00;
    USICR = 0x00;
    UCSRA = 0x00;
    UCSRB = 0x18;
    UCSRC = 0x06;
    UBRRH = 0x00;
    UBRRL = 0x33;
    ACSR = 0x80;
    DIDR = 0x00;
    
    UART_Flush();
    
    Lcd_Init();
    Lcd_Cmd(_LCD_CLEAR);
    Lcd_Cmd(_LCD_CURSOR_OFF);
    Lcd_Out(1, 1, "MaxSONAR");
    Lcd_Out(2, 7, "In");
}


void UART_Flush()
{
     unsigned char i = 0;
     while(RXC_bit == 1)
     i = UDR;
}


unsigned char UART_Receive()
{
    while(RXC_bit == 0);
    return UDR;
}


void gets(unsigned char *buffer)
{
    unsigned char tmp = 0;
    
    do
    {
        tmp = UART_Receive();
        *buffer++ = tmp;
    }while(tmp != 0x0D);
}


void UART_Transmit(unsigned char value)
{
    while(UDRE_bit == 0);
    UDR = value;
}


void putc(unsigned char *ch)
{
     while(*ch)
     {
          UART_Transmit(*ch++);
     };
}