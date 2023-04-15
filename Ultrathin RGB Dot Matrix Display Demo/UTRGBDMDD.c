#include "msg.c"


#define Row_A              PORTB0_bit
#define Row_B              PORTB1_bit
#define Row_C              PORTB2_bit
#define Row_D              PORTB3_bit
#define R_ch               PORTB4_bit
#define G_ch               PORTB5_bit
#define B_ch               PORTB6_bit
#define OE                 PORTB7_bit
#define STB                PORTD6_bit
#define CLK                PORTD7_bit


unsigned char shift = 0;
unsigned int dly = 0;
unsigned char i = 0;
unsigned char row = 0;

bit RF;
bit GF;
bit BF;
bit RB;
bit GB;
bit BB;


void setup();
void scan_rows(unsigned char p);
void send_data(unsigned char value);
void latch_data();


void main()
{
     unsigned char col = 0x00;
     
     setup();

     while(1)
     {
              for(shift = 0; shift < 15; shift++)
              {
                 if(shift == 12)
                 {
                     dly = 400;
                 }
                 else
                 {
                     dly = 90;
                 }
                 while(dly > 0)
                 {
                      for(row = 0; row < 16; row++)
                      {
                            for (i = 0; i < 2; i++)
                            {
                                send_data((disp[((i + shift) * 32) + (row << 1)]));
                                send_data((disp[((i + shift) * 32) + (row << 1) + 1]));
                            }

                            latch_data();
                      }
                      dly--;
                 }
              }
              
              col++;
              switch(col)
              {
                  case 1:
                  {
                       RF = 1;
                       GF = 0;
                       BF = 0;
                       RB = 0;
                       GB = 0;
                       BB = 1;
                       break;
                  }
                  case 2:
                  {
                       RF = 1;
                       GF = 0;
                       BF = 0;
                       RB = 0;
                       GB = 1;
                       BB = 0;
                       break;
                  }
                  case 3:
                  {
                       RF = 0;
                       GF = 0;
                       BF = 0;
                       RB = 1;
                       GB = 0;
                       BB = 0;
                       break;
                  }
                  case 4:
                  {
                       RF = 0;
                       GF = 1;
                       BF = 0;
                       RB = 1;
                       GB = 0;
                       BB = 0;
                       break;
                  }
                  case 5:
                  {
                       RF = 0;
                       GF = 1;
                       BF = 0;
                       RB = 0;
                       GB = 0;
                       BB = 1;
                       break;
                  }
                  case 6:
                  {
                       RF = 0;
                       GF = 0;
                       BF = 0;
                       RB = 0;
                       GB = 1;
                       BB = 0;
                       break;
                  }
                  case 7:
                  {
                       RF = 0;
                       GF = 0;
                       BF = 1;
                       RB = 1;
                       GB = 0;
                       BB = 0;
                       break;
                  }
                  case 8:
                  {
                       RF = 0;
                       GF = 0;
                       BF = 1;
                       RB = 0;
                       GB = 1;
                       BB = 0;
                       break;
                  }
                  case 8:
                  {
                       RF = 0;
                       GF = 0;
                       BF = 0;
                       RB = 0;
                       GB = 0;
                       BB = 1;
                       break;
                  }
                  case 9:
                  {
                       RF = 0;
                       GF = 0;
                       BF = 0;
                       RB = 1;
                       GB = 1;
                       BB = 1;
                       break;
                  }
                  case 10:
                  {
                       RF = 1;
                       GF = 1;
                       BF = 0;
                       RB = 0;
                       GB = 0;
                       BB = 0;
                       break;
                  }
                  case 10:
                  {
                       RF = 0;
                       GF = 0;
                       BF = 0;
                       RB = 0;
                       GB = 1;
                       BB = 1;
                       break;
                  }
                  case 10:
                  {
                       RF = 1;
                       GF = 0;
                       BF = 1;
                       RB = 0;
                       GB = 1;
                       BB = 0;
                       break;
                  }
                  default:
                  {
                       col = 1;
                       break;
                  }
              }
     };
}


void setup()
{
    RF = 0;
    GF = 0;
    BF = 1;
    RB = 0;
    GB = 1;
    BB = 1;

    PORTB = 0x00;
    DDRB = 0xFF;
    PORTC = 0x00;
    DDRC = 0x00;
    PORTD = 0x00;
    DDRD = 0xC0;
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
    MCUCSR = 0x00;
    TIMSK = 0x00;
    UCSRB = 0x00;
    ACSR = 0x80;
    SFIOR = 0x00;
    ADCSRA = 0x00;
    SPCR = 0x00;
    TWCR = 0x00;
}


void scan_rows(unsigned char p)
{
     Row_A = (p & 0x01);
     Row_B = ((p & 0x02) >> 1);
     Row_C = ((p & 0x04) >> 2);
     Row_D = ((p & 0x08) >> 3);
}


void send_data(unsigned char value)
{
    unsigned char s = 0x08;

    while(s > 0)
    {
        if((value & 0x80) != 0)
        {
            R_ch = RF;
            G_ch = GF;
            B_ch = BF;
        }
        else
        {
            R_ch = RB;
            G_ch = GB;
            B_ch = BB;
        }
        
        CLK = 1;
        value <<= 1;
        s--;
        CLK = 0;
    }
}


void latch_data()
{
    OE = 1;
    scan_rows(row);
    STB = 0;
    STB = 1;
    delay_us(200);
    OE = 0;
    delay_us(200);
}