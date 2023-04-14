#define    on_off_sw   PIND0_bit
#define    dir_sw      PIND1_bit
#define    inc_sw      PIND2_bit
#define    dec_sw      PIND3_bit

#define enable_pin     PORTD4_bit


void main()
{
     register signed int t=100;
     signed short s=0;
     
     const unsigned char POS[4]=
     {
         0b00010101,
         0b00101001,
         0b01001010,
         0b10000110
     };
     
     bit on_off_flag;
     bit dir_flag;
     
     on_off_flag=0;
     dir_flag=0;
     
     CLKPR=0x80;
     CLKPR=0x00;
     PORTA=0x00;
     DDRA=0x00;
     DDRB=0xFF;
     DDRD=0x10;
     PORTB=0x00;
     PORTD=0x00;
     ACSR=0x80;
     DIDR=0x00;
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
     delay_ms(500);
     
     while(1)
     {
             if(on_off_sw)
             {
                       delay_ms(20);
                       PORTB=0x00;
                       while(on_off_sw);
                       on_off_flag^=1;
             }
             
             else
             {
                       if(on_off_flag)
                       {
                                 enable_pin=1;
                                 
                                 if(inc_sw)
                                 {
                                        delay_ms(20);
                                        PORTB=0x00;
                                        while(inc_sw);
                                        if(t<0)
                                        {
                                               t=0;
                                        }
                                        else
                                        {
                                               t--;
                                        }
                                 }
                                 
                                 else if(dec_sw)
                                 {
                                        delay_ms(20);
                                        PORTB=0x00;
                                        while(dec_sw);
                                        if(t>10000)
                                        {
                                               t=10000;
                                        }
                                        else
                                        {
                                               t++;
                                        }
                                 }
                                 
                                 else if(dir_sw)
                                 {
                                        delay_ms(20);
                                        PORTB=0x00;
                                        while(dir_sw);
                                        dir_flag=~dir_flag;
                                 }
                                 
                                 else
                                 {
                                        if(dir_flag)
                                        {
                                               PORTB=POS[s];
                                               s++;
                                               if(s>3)
                                               {
                                                   s=0;
                                               }
                                        }
                                        
                                        else
                                        {
                                               PORTB=POS[s];
                                               s--;
                                               if(s<0)
                                               {
                                                   s=3;
                                               }
                                        }
                                        
                                        vdelay_ms(t);
                                 }
                       }
                       
                       else
                       {
                                 enable_pin=0;
                                 PORTB=0x00;
                       }
             }
     };
}


