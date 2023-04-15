#include "lcd_keypad_shield.h"
#include "lcd_print.c"
#include "MCP2515.c"
#include "DS18B20.c"


void setup(void);


void main(void)
{
    signed int t = 0;

    setup();

    CAN_TX_msg.id = 117;
    CAN_TX_msg.ext_id = 0;
    CAN_TX_msg.rtr = 0;
    CAN_TX_msg.length = 1;

    Lcd_Out(1, 1, "N");
    Lcd_Out(1, 8, "T/ C");
    print_symbol(10, 1, 0);

    Lcd_Out(2, 1, "N");
    Lcd_Out(2, 8, "T/ C");
    print_symbol(10, 2, 0);

    while(1)
    {
        t = DS18B20_get_temp();

        CAN_TX_msg.data_byte[0] = t;
        MCP2515_message_TX();

        print_C(3, 1, CAN_TX_msg.id);
        print_C(13, 1, t);


        if(MCP2515_check_for_incoming_message())
        {
            MCP2515_message_RX();

            print_C(3, 2, CAN_RX_msg.id);
            print_C(13, 2, CAN_RX_msg.data_byte[0]);
        }

        delay_ms(600);
    };
}


void setup(void)
{
    CLKPR = 0x80;
    CLKPR = 0x00;
    PORTB = 0x00;
    DDRB = 0x00;
    PORTC = 0x30;
    DDRC = 0x00;
    PORTD = 0x00;
    DDRD = 0x00;
    TCCR0A = 0x00;
    TCCR0B = 0x00;
    TCNT0 = 0x00;
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
    ASSR = 0x00;
    TCCR2A = 0x00;
    TCCR2B = 0x00;
    TCNT2 = 0x00;
    OCR2A = 0x00;
    OCR2B = 0x00;
    EICRA = 0x00;
    EIMSK = 0x00;
    PCICR = 0x00;
    TIMSK0 = 0x00;
    TIMSK1 = 0x00;
    TIMSK2 = 0x00;
    UCSR0B = 0x00;
    ACSR = 0x80;
    ADCSRB = 0x00;
    DIDR1 = 0x00;
    ADCSRA = 0x00;
    SPCR = 0x00;
    TWCR = 0x00;

    Lcd_Init();
    Lcd_Cmd(_LCD_CLEAR);
    Lcd_Cmd(_LCD_CURSOR_OFF);

    MCP2515_init();
    load_custom_symbol();

    PORTB2_bit = HIGH;
}