const unsigned char dot_disp[0x06] = {0x1F, 0x1E, 0x1D, 0x1B, 0x17, 0x0F};
const unsigned char bar_disp[0x06] = {0x1F, 0x1E, 0x1C, 0x18, 0x10, 0x00};


void setup();
unsigned int adc_avg();


void main() 
{
     bit disp;
     unsigned char tmp = 0x00;
     unsigned int v = 0x0000;
     
     setup();
     
     while(1)
     {
             v = adc_avg();
             v >>= 5;
             tmp = v;
             tmp >>= 1;
             
             DDB0_bit = 0;
             PORTB0_bit = 1;
             
             if(PINB0_bit == 0)
             {
                while(PINB0_bit == 0);
                disp = ~disp;
             }
             
             DDB0_bit = 1;

             switch(disp)
             {
                 case 1:
                 {
                     PORTB = bar_disp[tmp];
                     break;
                 }
                 default:
                 {
                     PORTB = dot_disp[tmp];
                     break;
                 }
             }
             delay_ms(40);

             if((v % 2) != 0)
             {
                   PORTB = 0x1F;
                   delay_ms(60);
             }
     };
}


void setup()
{
    CLKPR = 0x80;
    CLKPR = 0x00;
    PORTB = 0x00;
    DDRB = 0x1F;
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
    PORTB = 0x1F;
    adc_init();
}


unsigned int adc_avg()
{
    unsigned char s = 64;
    signed int tmp = 0x0000;
    unsigned int avg = 0x0000;
    
    while(s--)
    {
        tmp = (adc_read(0) - 511);
        if(tmp < 0)
        {
           tmp = -tmp;
        }
        
        avg += tmp;
        delay_us(10);
    }
    
    avg >>= 6;
    
    return avg;
}