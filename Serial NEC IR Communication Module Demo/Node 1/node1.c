#include "DHT11.c"


#define BT1                                     !PINB0_bit
#define BT2                                     !PINB1_bit
#define BT3                                     !PINB2_bit
#define BT4                                     !PINB3_bit

#define LED1                                    PORTC0_bit
#define LED2                                    PORTC1_bit
#define LED3                                    PORTC2_bit
#define LED4                                    PORTC3_bit

#define preamble                                0xA1
#define transmission                            0xF1

#define sync                                    0x66

#define sync_byte                               0
#define data_byte_1                             1
#define data_byte_2                             2

#define RX_buffer_length                        3


sbit LCD_RS at PORTD6_bit;
sbit LCD_EN at PORTD4_bit;
sbit LCD_D4 at PORTB4_bit;
sbit LCD_D5 at PORTB5_bit;
sbit LCD_D6 at PORTB6_bit;
sbit LCD_D7 at PORTB7_bit;

sbit LCD_RS_Direction at DDD6_bit;
sbit LCD_EN_Direction at DDD4_bit;
sbit LCD_D4_Direction at DDB4_bit;
sbit LCD_D5_Direction at DDB5_bit;
sbit LCD_D6_Direction at DDB6_bit;
sbit LCD_D7_Direction at DDB7_bit;


unsigned char cnt = 0;

unsigned char UART_RX_buffer[RX_buffer_length] = {0x00, 0x00, 0x00};
const unsigned char symbol[8] = {0x06, 0x09, 0x09, 0x06, 0x00, 0x00, 0x00, 0x00};


void setup(void);
void load_symbol(unsigned char pos_row, unsigned char pos_char);
void lcd_str(unsigned char x_pos, unsigned char y_pos, char *ch);
void print_C(unsigned char x_pos, unsigned char y_pos, signed int value);
void UART_send_data(unsigned char a, unsigned char b, unsigned char c);


void UART1_Interrupt()
iv IVT_ADDR_USART_RXC
ics ICS_AUTO
{
    UART_RX_buffer[cnt++] = UDR;
    RXC_bit = 0;
}


void main(void)
{
     unsigned char s = 0;
     unsigned char DS_T = 0;
     unsigned char state = 0;
     unsigned char LED_states = 0x00;
     unsigned char DHT_T = 0xFF;
     unsigned char DHT_RH = 0x00;

     setup();

     Lcd_Out(1, 3, "IR Comms. Node 1");
     Lcd_Out(2, 1, "DHT11 Tmp/ C:");
     Lcd_Out(3, 1, "DHT11 R.H/ %:");
     Lcd_Out(4, 1, "DS18B20 T/ C:");

     load_symbol(2, 11);
     load_symbol(4, 11);

     while(1)
     {
        state = get_data();

        switch(state)
        {
           case 1:
           {
           }

           case 2:
           {
           }

           case 3:
           {
              Lcd_Out(2, 17, "---");
              Lcd_Out(3, 17, "---");
              UART_send_data(0xFF, 0xFF, 0xFF);
              break;
           }

           default:
           {
              DHT_RH = values[0];
              DHT_T = values[2];

              print_C(17, 2, DHT_T);
              print_C(17, 3, DHT_RH);
              
              UART_send_data(sync, DHT_T, DHT_RH);
              break;
           }
        }

        if(UART_RX_buffer[sync_byte] == 0x99)
        {
           LED_states = (UART_RX_buffer[data_byte_1] & 0x0F);
           DS_T = UART_RX_buffer[data_byte_2];

           if((DS_T <= 99) && (DS_T >= 0))
           {
              print_C(17, 4, DS_T);
           }
           else
           {
              Lcd_Out(4, 17, "---");
           }

           PORTC = (0x0F & LED_states);
           cnt = 0;
        }
        else
        {
            cnt = 0;
            for(s = 0; s < RX_buffer_length; s++)
            {
                UART_RX_buffer[s] = 0x00;
            }
        }

        delay_ms(1100);
     };
}


void setup(void)
{
    PORTA = 0x00;
    DDRA = 0x00;
    PORTB = 0x0F;
    DDRB = 0xF0;
    PORTC = 0x00;
    DDRC = 0x0F;
    PORTD = 0x00;
    DDRD = 0x76;
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
    ASSR = 0x00;
    TCCR2 = 0x00;
    TCNT2 = 0x00;
    OCR2 = 0x00;
    MCUCR = 0x00;
    MCUCSR = 0x00;
    TIMSK = 0x00;
    UCSRA = 0x00;
    UCSRB = 0x18;
    UCSRC = 0x86;
    UBRRH = 0x00;
    UBRRL = 0x0C;
    ACSR = 0x80;
    SFIOR = 0x00;
    ADCSRA = 0x00;
    SPCR = 0x00;
    TWCR = 0x00;

    Lcd_Init();
    Lcd_Cmd(_LCD_CLEAR);
    Lcd_Cmd(_LCD_CURSOR_OFF);
    UART1_Init_Advanced(9600, _UART_NOPARITY, _UART_ONE_STOPBIT);
    RXCIE_bit = 1;
    TXCIE_bit = 0;
    TXEN_bit = 1;
    SREG_I_bit = 1;
    delay_ms(100);
}


void load_symbol(unsigned char pos_row, unsigned char pos_char)
{
    unsigned char s = 0x00;

    Lcd_Cmd(0x40);

    for (s = 0x00; s < 0x08; s++)
    {
        Lcd_Chr_CP(symbol[s]);
    }

    Lcd_Cmd(_LCD_RETURN_HOME);
    Lcd_Chr(pos_row, pos_char, 0);
}


void lcd_str(unsigned char x_pos, unsigned char y_pos, char *ch)
{
    do
    {
        Lcd_Chr(y_pos, x_pos++, *ch++);
    }while(*ch != '\0');
}


void print_C(unsigned char x_pos, unsigned char y_pos, signed int value)
{
     unsigned char ch[5] = {0x20, 0x20, 0x20, 0x20, '\0'};

     if(value < 0x00)
     {
        ch[0] = 0x2D;
        value = -value;
     }
     else
     {
        ch[0] = 0x20;
     }

     if((value > 99) && (value <= 999))
     {
         ch[1] = ((value / 100) + 0x30);
         ch[2] = (((value % 100) / 10) + 0x30);
         ch[3] = ((value % 10) + 0x30);
     }
     else if((value > 9) && (value <= 99))
     {
         ch[1] = (((value % 100) / 10) + 0x30);
         ch[2] = ((value % 10) + 0x30);
         ch[3] = 0x20;
     }
     else if((value >= 0) && (value <= 9))
     {
         ch[1] = ((value % 10) + 0x30);
         ch[2] = 0x20;
         ch[3] = 0x20;
     }

     lcd_str(x_pos, y_pos, ch);
}


void UART_send_data(unsigned char a, unsigned char b, unsigned char c)
{
   SREG_I_bit = 0;
   UART1_Write(preamble);
   UART1_Write(transmission);
   UART1_Write(a);
   UART1_Write(b);
   UART1_Write(c);
   delay_ms(90);
   SREG_I_bit = 1;
}