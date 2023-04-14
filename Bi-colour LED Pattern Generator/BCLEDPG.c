#define color_toggler           PORTB0_bit
#define change_pattern          PINB1_bit
#define max                     16


void setup();
void all_off();
void simple_toggle_pattern();
void alternating_colour();
void knight_rider_1();
void knight_rider_2();
void knight_rider_3();
void knight_rider_4();
void knight_rider_5();
void knight_rider_6();
void knight_rider_7();
void knight_rider_8();
void illusion1();
void illusion2();
void police_lights1();
void police_lights2();
void police_lights3();
void effect();


void main() 
{
     unsigned short s=0;
     setup();
     while(1)
     {

             if(change_pattern)
             {
                               delay_ms(10);
                               all_off();
                               while(change_pattern);
                               s++;
             }
             if(s>max)
             {
                      s=0;
             }
             switch(s)
             {
                    case 1:
                    {
                         simple_toggle_pattern();
                         break;
                    }
                    case 2:
                    {
                         alternating_colour();
                         break;
                    }
                    case 3:
                    {
                         knight_rider_1();
                         break;
                    }
                    case 4:
                    {
                         knight_rider_2();
                         break;
                    }
                    case 5:
                    {
                         knight_rider_3();
                         break;
                    }
                    case 6:
                    {
                         knight_rider_4();
                         break;
                    }
                    case 7:
                    {
                         knight_rider_5();
                         break;
                    }
                    case 8:
                    {
                         knight_rider_6();
                         break;
                    }
                    case 9:
                    {
                         knight_rider_7();
                         break;
                    }
                    case 10:
                    {
                         knight_rider_8();
                         break;
                    }
                    case 11:
                    {
                         illusion1();
                         break;
                    }
                    case 12:
                    {
                         illusion2();
                         break;
                    }
                    case 13:
                    {
                         police_lights1();
                         break;
                    }
                    case 14:
                    {
                         police_lights2();
                         break;
                    }
                    case 15:
                    {
                         police_lights3();
                         break;
                    }
                    case 16:
                    {
                         effect();
                         break;
                    }
                    default:
                    {
                            all_off();
                            break;
                    }
             }
     };
}


void setup()
{
      CLKPR=0x80;
      CLKPR=0x00;
      DDRA=0x00;
      DDRB=0x01;
      DDRD=0x1F;
      PORTA=0x00;
      PORTB=0x00;
      PORTD=0x00;
      TCCR0A=0x00;
      TCCR0B=0x00;
      TCNT0=0x00;
      OCR0A=0x00;
      OCR0B=0x00;
      TCCR1A=0x00;
      TCCR1B=0x00;
      TCNT1H=0x00;
      TCNT1L=0x00;
      ICR1H=0x00;
      ICR1L=0x00;
      OCR1AH=0x00;
      OCR1AL=0x00;
      OCR1BH=0x00;
      OCR1BL=0x00;
      GIMSK=0x00;
      MCUCR=0x00;
      TIMSK=0x00;
      USICR=0x00;
      UCSRB=0x00;
      ACSR=0x80;
      DIDR=0x00;
}


void all_off()
{
     PORTD=0x00;
     color_toggler=0;
}


void simple_toggle_pattern()
{
     PORTD=0x1F;
     color_toggler=1;
     delay_ms(300);
     PORTD=0x00;
     color_toggler=1;
     delay_ms(300);
     
     PORTD=0x00;
     color_toggler=0;
     delay_ms(300);
     PORTD=0x1F;
     color_toggler=0;
     delay_ms(300);
}


void alternating_colour()
{
     PORTD=0x1F;
     color_toggler=0;
     delay_ms(150);
     PORTD=0x00;
     color_toggler=1;
     delay_ms(150);
}


void knight_rider_1()
{
      unsigned short n=1;
      color_toggler=1;
      while(n<16)
      {
                  PORTD=n;
                  delay_ms(200);
                  n<<=1;
      }
      n=16;
      while(n>=1)
      {
                  PORTD=n;
                  delay_ms(200);
                  n>>=1;
      }
}


void knight_rider_2()
{
      unsigned short n=1;
      color_toggler=1;
      while(n<16)
      {
                  PORTD=~n;
                  delay_ms(200);
                  n<<=1;
      }
      n=16;
      while(n>=1)
      {
                  PORTD=~n;
                  delay_ms(200);
                  n>>=1;
      }
}


void knight_rider_3()
{
      unsigned short n=1;
      color_toggler=0;
      while(n<16)
      {
                  PORTD=~n;
                  delay_ms(200);
                  n<<=1;
      }
      n=16;
      while(n>=1)
      {
                  PORTD=~n;
                  delay_ms(200);
                  n>>=1;
      }
}


void knight_rider_4()
{
      unsigned short n=1;
      color_toggler=0;
      while(n<16)
      {
                  PORTD=n;
                  delay_ms(200);
                  n<<=1;
      }
      n=16;
      while(n>=1)
      {
                  PORTD=n;
                  delay_ms(200);
                  n>>=1;
      }
}


void knight_rider_5()
{
      unsigned short n=1;
      while(n<16)
      {
                  PORTD=n;
                  color_toggler=1;
                  delay_ms(50);
                  PORTD=~n;
                  color_toggler=0;
                  delay_ms(150);
                  n<<=1;
      }
      n=16;
      while(n>=1)
      {
                  PORTD=n;
                  color_toggler=1;
                  delay_ms(50);
                  PORTD=~n;
                  color_toggler=0;
                  delay_ms(150);
                  n>>=1;
      }
}


void knight_rider_6()
{
     unsigned short n=1;
      while(n<16)
      {
                  PORTD=n;
                  color_toggler=0;
                  delay_ms(50);
                  PORTD=~n;
                  color_toggler=1;
                  delay_ms(150);
                  n<<=1;
      }
      n=16;
      while(n>=1)
      {
                  PORTD=n;
                  color_toggler=0;
                  delay_ms(50);
                  PORTD=~n;
                  color_toggler=1;
                  delay_ms(150);
                  n>>=1;
      }
}


void knight_rider_7()
{
      unsigned short n=1;
      color_toggler=0;
      while(n<16)
      {
                  PORTD=n;
                  delay_ms(150);
                  n<<=1;
      }
      n=16;
      color_toggler=1;
      while(n>=1)
      {
                  PORTD=~n;
                  delay_ms(150);
                  n>>=1;
      }
}


void knight_rider_8()
{
     knight_rider_2();
     knight_rider_4();
}


void illusion1()
{
     PORTD=0x55;
     color_toggler=0;
     delay_ms(100);
     PORTD=0xAA;
     color_toggler=1;
     delay_ms(100);
}


void illusion2()
{
     PORTD=0x55;
     color_toggler=0;
     delay_ms(50);
     PORTD=0x55;
     color_toggler=1;
     delay_ms(50);
}


void police_lights1()
{
     color_toggler=0;
     PORTD=0x1B;
     delay_ms(100);
     color_toggler=1;
     PORTD=0x04;
     delay_ms(100);
}


void police_lights2()
{
     unsigned short n=0;
     for(n=0;n<3;n++)
     {
                     color_toggler=1;
                     PORTD=0x04;
                     delay_ms(60);
                     color_toggler=0;
                     PORTD=0x00;
                     delay_ms(40);
     }
     delay_ms(100);
     for(n=0;n<3;n++)
     {
                     color_toggler=0;
                     PORTD=0x1B;
                     delay_ms(60);
                     color_toggler=1;
                     PORTD=0xFF;
                     delay_ms(40);
     }
     delay_ms(100);
}


void police_lights3()
{
     color_toggler=0;
     PORTD=0x11;
     delay_ms(120);
     color_toggler=1;
     PORTD=0x15;
     delay_ms(120);
}


void effect()
{
     unsigned char n=0;
     for(n=0;n<32;n++)
     {
           PORTD=n;
           color_toggler=~color_toggler;
           delay_ms(90);
     }
}