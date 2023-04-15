#define GATE                            PORTD2_bit
#define CLK                             PORTD3_bit
#define D                               PORTD4_bit
#define C                               PORTD5_bit
#define B                               PORTD6_bit
#define A                               PORTD7_bit

#define SW                              PIND0_bit

#define top_seg                         4
#define bot_seg                         0

#define HIGH                            1
#define LOW                             0


unsigned char num[0x0A] = {0xED, 0x21, 0x8F, 0xAB, 0x63, 0xEA, 0xEE, 0xA1, 0xEF, 0xEB};
unsigned char data_values[0x09] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};


unsigned char SW_in = 0;
unsigned char n = 0;


void setup();
void write_74164(unsigned char value);
void write_74145(unsigned char channel);
void show_LEDs(unsigned char LED1_state, unsigned char LED2_state, unsigned char LED3_state, unsigned char LED4_state);
void show_numbers(signed int value, unsigned char pos);


void Timer_1_ISR()
iv IVT_ADDR_TIMER1_OVF
ics ICS_AUTO
{
    TCNT1H = 0xFD;
    TCNT1L = 0xE8;

    write_74164(data_values[n]);
    write_74145(n);

    n++;
    if(n > 9)
    {
        n = 0;
    }
}


void main()
{
     unsigned int i = 0;
     unsigned int j = 9999;

     setup();

     while(1)
     {
          switch(SW_in)
           {
               case 1:
               {
                   show_LEDs(1, 0, 0, 0);
                   break;
               }
               case 2:
               {
                   show_LEDs(0, 1, 0, 0);
                   break;
               }
               case 3:
               {
                   show_LEDs(0, 0, 1, 0);
                   break;
               }
               case 4:
               {
                   show_LEDs(0, 0, 0, 1);
                   break;
               }
           }

           SW_in = 0;

           i++;
           j--;
           if(i > 9999)
           {
               i = 0;
               j = 9999;
           }

           show_numbers(i, bot_seg);
           show_numbers(j, top_seg);
           
           delay_ms(600);
           show_LEDs(0, 0, 0, 0);
     };
}


void setup()
{
    PORTA = 0x00;
    DDRA = 0x00;
    PORTB = 0x00;
    DDRB = 0x00;
    PORTC = 0x00;
    DDRC = 0x00;
    PORTD = 0x00;
    DDRD = 0xFC;
    TCCR0 = 0x00;
    TCNT0 = 0x00;
    OCR0 = 0x00;
    TCCR1A = 0x00;
    TCCR1B = 0x03;
    TCNT1H = 0xFD;
    TCNT1L = 0xE8;
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
    TIMSK = 0x04;
    UCSRB = 0x00;
    ACSR = 0x80;
    SFIOR = 0x00;
    ADCSRA = 0x00;
    SPCR = 0x00;
    TWCR = 0x00;
    SREG_I_bit = 1;
}


void write_74164(unsigned char value)
{
    unsigned char s = 0x08;

    while(s > 0)
    {
        if((value & 0x80) != 0x00)
        {
            GATE = HIGH;
        }
        else
        {
            GATE = LOW;
        }

        CLK = HIGH;
        CLK = LOW;

        value <<= 1;
        s--;
    }
}


void write_74145(unsigned char channel)
{
    PORTD &= 0x0F;

    switch(channel)
    {
        case 0:
        {
            delay_ms(1);
            if(SW == LOW)
            {
                SW_in = 1;
            }
            break;
        }

        case 1:
        {
            PORTD |= 0x80;
            break;
        }

        case 2:
        {
            PORTD |= 0x40;
            break;
        }

        case 3:
        {
            PORTD |= 0xC0;
            break;
        }

        case 4:
        {
            PORTD |= 0x20;
            break;
        }

        case 5:
        {
            PORTD |= 0xA0;
            break;
        }

        case 6:
        {
            PORTD |= 0x60;
            break;
        }

        case 7:
        {
            PORTD |= 0xE0;
            delay_ms(1);
            if(SW == LOW)
            {
                SW_in = 2;
            }
            break;
        }

        case 8:
        {
            PORTD |= 0x10;
            delay_ms(1);
            if(SW == LOW)
            {
                SW_in = 3;
            }
            break;
        }

        case 9:
        {
            PORTD |= 0x90;
            delay_ms(1);
            if(SW == LOW)
            {
                SW_in = 4;
            }
            break;
        }
    }
}


void show_LEDs(unsigned char LED1_state, unsigned char LED2_state, unsigned char LED3_state, unsigned char LED4_state)
{
    switch(LED1_state)
    {
        case HIGH:
        {
           data_values[8] |= 0x80;
           break;
        }
        case LOW:
        {
           data_values[8] &= 0x7F;
           break;
        }
    }

    switch(LED2_state)
    {
        case HIGH:
        {
           data_values[8] |= 0x40;
           break;
        }
        case LOW:
        {
           data_values[8] &= 0xBF;
           break;
        }
    }

    switch(LED3_state)
    {
        case HIGH:
        {
           data_values[8] |= 0x08;
           break;
        }
        case LOW:
        {
           data_values[8] &= 0xF7;
           break;
        }
    }

    switch(LED4_state)
    {
        case HIGH:
        {
           data_values[8] |= 0x02;
           break;
        }
        case LOW:
        {
           data_values[8] &= 0xFD;
           break;
        }
    }
}


void show_numbers(signed int value, unsigned char pos)
{
    unsigned char ch = 0x00;

    if((value >= 0) && (value <= 9))
    {
        ch = (value % 10);
        data_values[(0 + pos)] = num[ch];
        data_values[(1 + pos)] = 0x00;
        data_values[(2 + pos)] = 0x00;
        data_values[(3 + pos)] = 0x00;
    }
    else if((value > 9) && (value <= 99))
    {
        ch = (value % 10);
        data_values[(0 + pos)] = num[ch];
        ch = ((value / 10) % 10);
        data_values[(1 + pos)] = num[ch];
        data_values[(2 + pos)] = 0x00;
        data_values[(3 + pos)] = 0x00;
    }
    else if((value > 99) && (value <= 999))
    {
        ch = (value % 10);
        data_values[(0 + pos)] = num[ch];
        ch = ((value / 10) % 10);
        data_values[(1 + pos)] = num[ch];
        ch = ((value / 100) % 10);
        data_values[(2 + pos)] = num[ch];
        data_values[(3 + pos)] = 0x00;
    }
    else if((value > 999) && (value <= 9999))
    {
        ch = (value % 10);
        data_values[(0 + pos)] = num[ch];
        ch = ((value / 10) % 10);
        data_values[(1 + pos)] = num[ch];
        ch = ((value / 100) % 10);
        data_values[(2 + pos)] = num[ch];
        ch = (value / 1000);
        data_values[(3 + pos)] = num[ch];
    }
}