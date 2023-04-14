#define BT1       PINB0_bit
#define BT2       PINB1_bit
#define BT3       PINB2_bit
#define BT4       PINB3_bit

#define TX        PORTB4_bit


void setup();
void send_one();
void send_zero();
void send_data(unsigned char value);


void main()
{
     setup();

     while(1)
     {
             if(BT1)
             {
                 while(BT1);
                 send_data(4);
             }
             if(BT2)
             {
                 while(BT2);
                 send_data(6);
             }
             if(BT3)
             {
                 while(BT3);
                 send_data(9);
             }
             if(BT4)
             {
                 while(BT4);
                 send_data(16);
             }
     };
}


void setup()
{
    CLKPR = 0x80;
    CLKPR = 0x00;
    PORTB = 0x00;
    DDRB = 0x10;
    TCCR0A = 0x00;
    TCCR0B = 0x00;
    TCNT0 = 0x00;
    OCR0A = 0x00;
    OCR0B = 0x00;
    GIMSK = 0x00;
    MCUCR = 0x00;
    TIMSK0 = 0x00;
    ACSR = 0x80;
    ADCSRB = 0x00;
    DIDR0 = 0x00;
    ADCSRA = 0x00;
}


void send_data(unsigned char value)
{
     unsigned char s = 0;
     unsigned char crc = 0;

     crc = (value & 0xAA);
     
     for(s = 0; s < 20; s++)
     {
           TX = 1;
           delay_us(500);
           TX = 0;
           delay_us(500);
     }
     delay_us(100);
     
     for(s = 0; s < 8; s++)
     {
           TX = 1;
           if(value & 0x80)
           {
               delay_ms(2);
           }
           else
           {
               delay_ms(1);
           }
           TX = 0;
           delay_ms(1);
           value <<= 1;
     }

     for(s = 0; s < 8; s++)
     {
           TX = 1;
           if(crc & 0x80)
           {
               delay_ms(2);
           }
           else
           {
               delay_ms(1);
           }
           TX = 0;
           delay_ms(1);
           crc <<= 1;
     }
}