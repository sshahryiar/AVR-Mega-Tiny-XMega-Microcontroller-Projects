#include "8255.c"


void setup();


void main()
{
    unsigned char data_value = 0x00;

    setup();

    while(1)
    {
        data_value = read_8255(PORT_A);
        write_8255(PORT_C, ~data_value);
    };
}


void setup()
{
    CLKPR = 0x80;
    CLKPR = 0x00;
    PORTA = 0x00;
    DDRA = 0x00;
    PORTB = 0x00;
    DDRB = 0x00;
    PORTD = 0x00;
    DDRD = 0x1F;
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
    GIMSK = 0x00;
    MCUCR = 0x00;
    TIMSK = 0x00;
    USICR = 0x00;
    UCSRB = 0x00;
    ACSR = 0x80;
    DIDR = 0x00;
    _8255_init();
    delay_ms(100);
}