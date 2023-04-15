#include "DHT11.c"
#include "TM1622.c"


void setup(void);  
void LCD_print_value(unsigned char pos, unsigned char value);


void main(void)
{
    unsigned char DHT_state = 0x00;
    
    setup();
    TM1622_write_str(0, "DHT11 DEMO\r");
    delay_ms(2000);
    TM1622_write_str(0, "TM1622 COG\r");
    delay_ms(2000);

    while(1)
    {
        TM1622_clear_display();
        DHT_state = DHT11_get_data();

        switch(DHT_state)
        {
              case DHT11_sensor_error_state:
              {
                  TM1622_write_str(0, "DHT Error!\r");
                  break;
              }
              case DHT11_no_sensor_state:
              {
                 TM1622_write_str(0, "No Sensor!\r");
                 break;
              }
              case DHT11_checksum_error_state:
              {
                 TM1622_write_str(0, "Comm Error\r");
                 break;
              }
              default:
              {
                 LCD_print_value(1, values[0]);
                 TM1622_write_char(3, '%');
                 LCD_print_value(5, values[2]);
                 TM1622_print_custom_char(7, 0);
                 TM1622_write_char(8, 'C');
                 break;
              }
        }
        
        delay_ms(1000);

    };
}


void setup(void)
{
    PORTB = 0x00;
    DDRB = 0x00;
    PORTC = 0x00;
    DDRC = 0x00;
    PORTD = 0x00;
    DDRD = 0x00;
    TCCR0 = 0x00;
    TCNT0 = 0x00;
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
    TIMSK = 0x00;
    UCSRB = 0x00;
    ACSR = 0x80;
    SFIOR = 0x00;
    ADCSRA = 0x00;
    SPCR = 0x00;
    TWCR = 0x00;
    TM162x_init();
    DHT11_init();
}


void LCD_print_value(unsigned char pos, unsigned char value)
{
    char chr = 0x00;
    
    chr = ((value / 10) + 0x30);
    TM1622_write_char(pos, chr);
    chr = ((value % 10) + 0x30);
    TM1622_write_char((pos + 1), chr);
}