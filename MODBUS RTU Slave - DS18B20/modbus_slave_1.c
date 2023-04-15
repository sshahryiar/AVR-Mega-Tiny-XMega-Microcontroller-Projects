#include "DS18B20.c"
#include "lcd_print.c"
#include "misc.c"
#include "MODBUS.c"


#define BT1                                     PINB0_bit
#define BT2                                     PINB1_bit
#define BT3                                     PINB2_bit
#define BT4                                     PINB3_bit

#define LED1                                    PORTC0_bit
#define LED2                                    PORTC1_bit
#define LED3                                    PORTC2_bit
#define LED4                                    PORTC3_bit


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


void setup(void);


void main(void)
{
     unsigned char i = 0;
     
     setup();

     flush_TX_buffer();
     flush_RX_buffer();
     
     Lcd_Out(1, 1, "MODBUS Slave ID:");
     Lcd_Out(2, 1, "Coils:");
     Lcd_Out(2, 12, "IPs:");
     Lcd_Out(3, 1, "I Reg:");
     Lcd_Out(4, 1, "H Reg:");

     print_C(17, 1, own_ID);

     while(1)
     {
         MODBUS_receive_task();

         LED1 = coils[0];
         LED2 = coils[1];
         LED3 = coils[2];
         LED4 = coils[3];
         
         discrete_inputs[0] = ~BT1;
         discrete_inputs[1] = ~BT2;
         discrete_inputs[2] = ~BT3;
         discrete_inputs[3] = ~BT4;
         
         input_registers[0] = get_temp();
         input_registers[1] = (input_registers[0] + 273);
         
         for(i = 0; i < 4; i++)
         {
             Lcd_Chr(2, (7 + i), (48 + coils[i]));
             Lcd_Chr(2, (16 + i), (48 + discrete_inputs[i]));
         }

         print_I(8, 3, input_registers[0]);
         print_I(15, 3, input_registers[1]);
         
         print_I(8, 4, holding_registers[0]);
         print_I(15, 4, holding_registers[1]);
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
    DIR_RX;
    delay_ms(100);
}
