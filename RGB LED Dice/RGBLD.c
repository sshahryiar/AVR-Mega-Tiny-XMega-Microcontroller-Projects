#define IN        PINA4_bit

#define R_ch      PORTB2_bit
#define G_ch      PORTA7_bit
#define B_ch      PORTA6_bit

#define A         PORTA0_bit
#define B         PORTA1_bit
#define C         PORTA2_bit
#define D         PORTA3_bit


void setup();
void switch_LEDS(unsigned char val);


void main() 
{
     unsigned char value = 0x00;
     
     setup();
     
     while(1)
     {
             if(!IN)
             {
                 value++;
                 if(value > 6)
                 {
                     value = 1;
                 }
                 if(value < 1)
                 {
                     value = 6;
                 }
             }
             else
             {
                 switch_LEDS(value);
             }
     };
}


void setup()
{
    CLKPR = 0x80;
    CLKPR = 0x00;
    PORTA = 0x30;
    DDRA = 0xCF;
    PORTB = 0x00;
    DDRB = 0x04;
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
    MCUCR = 0x00;
    GIMSK = 0x00;
    TIMSK0 = 0x00;
    TIMSK1 = 0x00;
    USICR = 0x00;
    ACSR = 0x80;
    ADCSRB = 0x00;
    DIDR0 = 0x00;
    ADCSRA = 0x00;
}


void switch_LEDS(unsigned char val)
{
     switch(val)
     {
         case 1:
         {
             A = 0;
             B = 0;
             C = 0;
             D = 1;
             
             R_ch = 1;
             G_ch = 1;
             B_ch = 0;
             break;
         }
         case 2:
         {
             A = 1;
             B = 0;
             C = 0;
             D = 0;
             
             R_ch = 1;
             G_ch = 0;
             B_ch = 0;
             break;
         }
         case 3:
         {
             A = 0;
             B = 1;
             C = 0;
             D = 1;
             
             R_ch = 0;
             G_ch = 1;
             B_ch = 0;
             break;
         }
         case 4:
         {
             A = 1;
             B = 1;
             C = 0;
             D = 0;
             
             R_ch = 0;
             G_ch = 0;
             B_ch = 1;
             break;
         }
         case 5:
         {
             A = 1;
             B = 1;
             C = 0;
             D = 1;
             
             R_ch = 1;
             G_ch = 0;
             B_ch = 1;
             break;
         }
         case 6:
         {
             A = 1;
             B = 1;
             C = 1;
             D = 0;
             
             R_ch = 0;
             G_ch = 1;
             B_ch = 1;
             break;
         }
         default:
         {
             A = 0;
             B = 0;
             C = 0;
             D = 0;
             
             R_ch = 0;
             G_ch = 0;
             B_ch = 0;
             break;
         }
     }
}