#define button                                PIND0_bit
#define charge_pin                            PORTD4_bit
#define discharge_pin                         PORTD6_bit

#define start_timer                           TCCR0=0x2;
#define stop_timer                            TCCR0=0x0;

#define comp_sig                              ACO_bit


unsigned long CNT=0;


sbit LCD_RS at PORTB0_bit;
sbit LCD_EN at PORTB1_bit;
sbit LCD_D4 at PORTB2_bit;
sbit LCD_D5 at PORTB3_bit;
sbit LCD_D6 at PORTB4_bit;
sbit LCD_D7 at PORTB5_bit;

sbit LCD_RS_Direction at DDB0_bit;
sbit LCD_EN_Direction at DDB1_bit;
sbit LCD_D4_Direction at DDB2_bit;
sbit LCD_D5_Direction at DDB3_bit;
sbit LCD_D6_Direction at DDB4_bit;
sbit LCD_D7_Direction at DDB5_bit;


bit OF;
unsigned char C[] = "00.000 uF";
unsigned int tmr_cnt=0;
unsigned int T_value=0;


void setup();
void display(unsigned int value);


void timerISR()
org IVT_ADDR_TIMER0_OVF
{
    TCNT0=tmr_cnt;
    CNT+=1;
    if(CNT>9999)
    {
                OF=1;
    }
}


void main()
{
     setup();
     while(1)
     {
             if(button)
             {
                       delay_ms(100);
                       while(button);
                       CNT=0;
                       OF=0;
                       ACSR=0x80; 
                       DDD6_bit=1; 
                       discharge_pin=0; 
                       charge_pin=0;
                       Lcd_Cmd(_LCD_CLEAR);
                       Lcd_Out(1,4,"Checking!");
                       delay_ms(1000);
                       Lcd_Cmd(_LCD_CLEAR);
                       Lcd_Out(1,5,"Reading");
                       Lcd_Out(2,3,"Please wait!");
                       ACSR=0x00;
                       DDD6_bit=0;
                       charge_pin=1;
                       TCNT0=tmr_cnt;
                       start_timer
                       
                       while(!comp_sig)
                       {
                                       if(OF)
                                       {
                                     
                                             break;
                                       }
                       }
                       stop_timer
                       T_value=(TCNT0-tmr_cnt);
                       charge_pin=0;
                       Lcd_Cmd(_LCD_CLEAR);
                       
                       if(OF)
                       {
                            Lcd_Cmd(_Lcd_Clear);
                            Lcd_Out(1, 3, "Out of Range!");
                            OF=0;
                       }
                       else
                       {
                            Display(CNT*10);
                       }
                       
             }
      }
}


void setup()
{
   PORTB=0x00;
   DDRB=0x01;
   PORTC=0x00;
   DDRC=0x00;
   PORTD=0x00;
   DDRD=0x08;

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

   ASSR=0x00;
   TCCR2=0x00;
   TCNT2=0x00;
   OCR2=0x00;

   MCUCR=0x00;
   TIMSK=0x01;

   ACSR=0x00;
   SFIOR=0x00;

   asm sei;

   stop_timer
   tmr_cnt=108;
   Lcd_Init();
   Lcd_Cmd(_LCD_CLEAR);
   Lcd_Cmd(_LCD_CURSOR_OFF);
   
   lcd_out(1,6,"Ready!");
}


void display(unsigned int value)
{
     unsigned char text[15];
     C[0] = ((value/10000) + 48);
     C[1] = (((value/1000)%10) + 48);
     C[3] = (((value/100)%10) + 48);
     C[4] = (((value/10)%10) + 48);
     C[5] = (((T_Value*10)/153) + 48);
     Lcd_Cmd(_Lcd_Clear);
     Lcd_Out(1, 5, C);
}

