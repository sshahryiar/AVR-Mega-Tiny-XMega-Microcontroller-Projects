#include "lcd_print.c"


#define REDE                                    PORTD2_bit

#define DIR_RX                                  0
#define DIR_TX                                  1

#define TX_buffer_length                        10
#define RX_buffer_length                        10
#define fixed_no_of_bytes_to_read               5


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


const unsigned char degree_symbol[8] = {0x06, 0x09, 0x09, 0x06, 0x00, 0x00, 0x00, 0x00};


unsigned char cnt = 0;
volatile unsigned char RX_buffer[RX_buffer_length];


void setup(void);
void load_degree_symbol(unsigned char y_pos, unsigned char x_pos);
void flush_RX_buffer(void);
void send_read_command(void);
unsigned int make_word(unsigned char HB, unsigned char LB);
void get_HB_LB(unsigned int value, unsigned char *HB, unsigned char *LB);
unsigned int MODBUS_RTU_CRC16(unsigned char *data_input, unsigned char data_length);


void UART1_Interrupt()
iv IVT_ADDR_USART_RXC
ics ICS_AUTO
{
    RX_buffer[cnt++] = UDR;
    RXC_bit = 0;
}



void main(void)
{
     unsigned char temp_HB = 0;
     unsigned char temp_LB = 0;

     unsigned int value = 0;
     unsigned int check1 = 0;
     unsigned int check2 = 0;

     setup();

     flush_RX_buffer();

     while(1)
     {
         send_read_command();
         
         check1 = make_word(RX_buffer[8], RX_buffer[7]);
         check2 = MODBUS_RTU_CRC16(RX_buffer, 7);
         
         if(check1 == check2)
         {
             value = make_word(RX_buffer[3], RX_buffer[4]);
             print_F(12, 1, (value / 10.0), 1);

             value = make_word(RX_buffer[5], RX_buffer[6]);
             print_F(12, 2, (value / 10.0), 1);
         }
         
         else
         {
             lcd_out(1, 13, "--.-");
             lcd_out(2, 13, "--.-");
         }

         delay_ms(400);
     };
}


void setup(void)
{
    PORTA = 0x00;
    DDRA = 0x00;
    PORTB = 0x0F;
    DDRB = 0xF0;
    PORTC = 0x00;
    DDRC = 0x00;
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

    Lcd_Out(1, 1, "Temp/ C:");
    load_degree_symbol(1, 6);
    Lcd_Out(2, 1, "R.H / %:");
    
    delay_ms(100);
}


void load_degree_symbol(unsigned char y_pos, unsigned char x_pos)
{
    unsigned char s = 0;
    
    Lcd_Cmd(64);
    
    for (s = 0; s < 8; s++)
    {
        Lcd_Chr_CP(degree_symbol[s]);
    }
    
    Lcd_Cmd(_LCD_RETURN_HOME);
    Lcd_Chr(y_pos, x_pos, 0);
}


void flush_RX_buffer(void)
{
    signed char i = (RX_buffer_length - 1);

    while(i > -1)
    {
        RX_buffer[i] = 0x00;
        i--;
    };
}


void send_read_command(void)
{
    unsigned char i = 0;
    
    volatile unsigned char TX_buffer[TX_buffer_length] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x02, 0xC4, 0x0B};

    REDE = DIR_TX;

    for(i = 0; i < TX_buffer_length; i++)
    {
        UART_Write(TX_buffer[i]);
    }

    cnt = 0;
    REDE = DIR_RX;

    delay_ms(600);
}


unsigned int make_word(unsigned char HB, unsigned char LB)
{
    unsigned int tmp = 0;

    tmp = HB;
    tmp <<= 8;
    tmp |= LB;

    return tmp;
}


void get_HB_LB(unsigned int value, unsigned char *HB, unsigned char *LB)
{
    *LB = (value & 0x00FF);
    *HB = ((value & 0xFF00) >> 8);
}


unsigned int MODBUS_RTU_CRC16(unsigned char *data_input, unsigned char data_length)
{
    unsigned char n = 8;
    unsigned char s = 0;
    unsigned int CRC_word = 0xFFFF;

    for(s = 0; s < data_length; s++)
    {
      CRC_word ^= ((unsigned int)data_input[s]);

      n = 8;
      while(n > 0)
      {
        if((CRC_word & 0x0001) == 0)
        {
          CRC_word >>= 1;
        }

        else
        {
          CRC_word >>= 1;
          CRC_word ^= 0xA001;
        }

        n--;
      }
    }

    return CRC_word;
}