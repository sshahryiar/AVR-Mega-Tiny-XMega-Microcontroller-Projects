#define RX      PIND0_bit

#define RLA1    PORTD1_bit
#define RLA2    PORTD2_bit
#define RLA3    PORTD3_bit
#define RLA4    PORTD4_bit
#define LED     PORTD5_bit

#define sync    0x09
#define error   0x06


void setup();
unsigned char receive_data();
signed long decode_data();


void main() 
{
     signed int rcv = 0;
     
     setup();
     
     while(1)
     {
        rcv = decode_data();

        if(rcv == 0x04)
        {
            RLA1 ^= 1;
        }
        if(rcv == 0x06)
        {
            RLA2 ^= 1;
        }
        if(rcv == 0x09)
        {
            RLA3 ^= 1;
        }
        if(rcv == 0x10)
        {
            RLA4 ^= 1;
        }
     }
}


void setup()
{
    CLKPR = 0x80;
    CLKPR = 0x00;
    PORTB = 0x00;
    DDRB = 0x00;
    PORTC = 0x00;
    DDRC = 0x00;
    PORTD = 0x00;
    DDRD = 0x3E;
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
    delay_ms(600);
}


unsigned char receive_data()
{
    unsigned char t = 0;

    while(!RX);
    LED = 0;
    while(RX)
    {
        t++;
        delay_us(10);
        LED = 1;
    };
    LED = 0;

    if((t > 25) && (t < 75))
    {
        return sync;
    }
    else if((t > 175) && (t < 225))
    {
        return 1;
    }
    else if((t > 75) && (t < 125))
    {
        return 0;
    }
    else
    {
        return error;
    }
}


signed long decode_data()
{
    unsigned char d = 0;
    unsigned char s = 0;
    unsigned long value = 0;
    unsigned char v1 = 0;
    unsigned char v2 = 0;

    while(receive_data() != sync);

    d = receive_data();
    while(d == sync)
    {
         d = receive_data();
    };

    while(s < 15)
    {
        switch(d)
        {
            case 1:
            {
                value |= 1;
                break;
            }
            case 0:
            {
                break;
            }
            case sync:
            case error:
            {
                return -1;
            }
        }
        s++;
        value <<= 1;
        d = receive_data();
    }

    v1 = (value >> 8);
    v2 = (value & 0x00FF);
    delay_ms(4);

    if((v1 & 0xAA) == v2)
    {
        return v1;
    }
    else
    {
        return -1;
    }
}