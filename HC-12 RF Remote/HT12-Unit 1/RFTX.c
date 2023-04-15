#include <16F886.h>  


#device *= 16
                         
                                                                                               
#fuses NOWDT, NOLVP, HS, NOWRT, BROWNOUT, NODEBUG, CPD 
#fuses FCMEN, NOIESO, NOWRT, PUT, MCLR, BORV40, PROTECT 

                                                                                                     
#use delay (clock = 10MHz)                                      
#use rs232(baud = 9600, uart1, stop = 1, bits = 8, parity = N, timeout = 100)                
                                   
                                                             
#include <lcd420.c>                
                                                                                             
                                                             
#define bt1               input(pin_C0)                              
#define bt2               input(pin_C1)
#define bt3               input(pin_C2)         
#define bt4               input(pin_C3)                               
                                               
#define set               pin_C5                
#define LED               pin_C4                                    
                                     
#define str_len           16    
                                        
#define dly               2000
#define kbd_dly           30
                        
                                  
unsigned char str[str_len];        
                                     
                    
void setup();                                  
void check_RF(); 
void set_RF();
unsigned char inc_dec(unsigned char x_pos, unsigned char y_pos, signed long value, unsigned char max, unsigned char min);           
void read_and_display_output(unsigned char start_char, unsigned char stop_char);         
                                                                                 
                 
void main()                                     
{                                     
      unsigned char rcv = 0;
      
      setup();
      check_RF();    
      
      while(TRUE)              
      {                      
            if(bt4)                  
            {         
                while(bt4);      
                delay_ms(600);    
                set_RF();     
            }                                                 
            
            lcd_gotoxy(4, 1);           
    		lcd_putc("CMD Sent:");
    		lcd_gotoxy(4, 2);           
    		lcd_putc("CMD Rcv.:");  
             
            if(bt1)
            {
                while(bt1);   
                lcd_gotoxy(13, 1);
                lcd_putc('1');
                putc('1');         
            }     
            if(bt2)
            {
                while(bt2);   
                lcd_gotoxy(13, 1);
                lcd_putc('2');
                putc('2');         
            } 
            if(bt3)       
            {       
                while(bt3);   
                lcd_gotoxy(13, 1);
                lcd_putc('3');
                putc('3');                               
            } 
            
            if(kbhit())
            {                      
                rcv = getc(); 
                
                if((rcv >= 32) && (rcv <= 126))
            	{   
                	lcd_gotoxy(13, 2);     
                	printf(lcd_putc, "%c", rcv);   
            	}
            }                                          
      };                                
}                                                                      
                             
                                    
void setup()                              
{                                                        
      memset(str, 0x00, sizeof(str));       
      disable_interrupts(global);
      setup_WDT(WDT_off);                             
      setup_comparator(NC_NC_NC_NC);          
      setup_ADC(ADC_off);           
      setup_ADC_ports(no_analogs);                   
      setup_SPI(SPI_disabled | SPI_SS_disabled);    
      setup_CCP1(CCP_off);                 
      setup_CCP2(CCP_off);
      setup_timer_0(T0_internal); 
      setup_timer_1(T1_disabled); 
      setup_timer_2(T2_disabled, 255, 1);
      set_timer0(0);  
      set_timer1(0);
      set_timer2(0);
      lcd_init();
      lcd_putc("\f");    
}                        

                              
void check_RF()            
{                                    
      short chk = FALSE;  
                                     
      output_high(set);
      delay_ms(40);      
      output_low(set);
      delay_ms(400); 
                         
      do       
      {                                     
        lcd_putc("\f");
        lcd_gotoxy(3, 1);                 
        lcd_putc("Checking RF.");     
        lcd_gotoxy(5, 2);                             
        lcd_putc("AT = ");                      
        puts("AT\r");  
        
        if(getc() == 'O')                               
        {                            
                output_high(LED);                           
                lcd_gotoxy(10, 2);  
                lcd_putc("OK.");         
                delay_ms(600);                                
                chk = TRUE;                       
        }                                               
        else                                                                                                  
        {                                   
                output_low(LED);                     
                lcd_gotoxy(10, 2);   
                lcd_putc("ERR");       
                delay_ms(600);  
                chk = FALSE;                   
        }                                               
      }while(chk == FALSE);   
      
      delay_ms(dly);
      output_low(LED);    
      
      lcd_putc("\f");
      lcd_gotoxy(1, 1);                 
      lcd_putc("RF S/W Version:");     
      lcd_gotoxy(1, 2);                      
      printf("AT+V\r");         
      read_and_display_output('H', '\r');     
      delay_ms(dly);  
      
      lcd_putc("\f");                
      lcd_gotoxy(1, 1);                                        
      lcd_putc("Baud Rate:");                                                                     
      lcd_gotoxy(1, 2);                      
      printf("AT+RB\r");                                             
      read_and_display_output('B', '\r');           
      delay_ms(dly);    
                                                                      
      lcd_putc("\f");                
      lcd_gotoxy(1, 1);                                        
      lcd_putc("Channel:");                                                                     
      lcd_gotoxy(1, 2);                      
      printf("AT+RC\r");                                             
      read_and_display_output('C', '\r');
      delay_ms(dly); 
      
      lcd_putc("\f");                
      lcd_gotoxy(1, 1);                                        
      lcd_putc("TX Power:");                                                                     
      lcd_gotoxy(1, 2);                      
      printf("AT+RP\r");                                             
      read_and_display_output('P', '\r');           
      delay_ms(dly); 
      
      lcd_putc("\f");                
      lcd_gotoxy(1, 1);                                        
      lcd_putc("TX-RX Mode:");                                                                     
      lcd_gotoxy(1, 2);                      
      printf("AT+RF\r");                                             
      read_and_display_output('F', '\r');           
      delay_ms(dly);      
      
      output_high(set); 
      delay_ms(400);  
      lcd_putc("\f");        
}   


void set_RF()
{  
      unsigned char tmp = 0; 
                     
      lcd_putc("\f");
      lcd_gotoxy(5, 1);
      lcd_putc("Setup RF");              
      
      output_high(LED);
      output_low(set);                     
      delay_ms(600);
      
      lcd_putc("\f");
      lcd_gotoxy(1, 1);
      lcd_putc("Load Defaults?");  
      lcd_gotoxy(1, 2);
      lcd_putc("Y = 1  N = 0");                      
      tmp = inc_dec(13, 2, tmp, 1, 0); 
      if(tmp == 1)
      {
        printf("AT+DEFAULT\r\n");    
      }                                  
      else
      {                                
          delay_ms(600);
          tmp = 3; 
          lcd_putc("\f");
          lcd_gotoxy(1, 1); 
          lcd_putc("Set TX-RX Mode:");               
          tmp = inc_dec(1, 2, tmp, 3, 1);  
          if((tmp < 1) || (tmp > 3))   
          {                      
            tmp = 3;                 
          }          
          printf("AT+FU%u\r\n", tmp);
          delay_ms(600); 
          
          tmp = 8;
          lcd_putc("\f");
          lcd_gotoxy(1, 1);
          lcd_putc("Set TX Power:");               
          tmp = inc_dec(1, 2, tmp, 8, 1);
          if((tmp < 1) || (tmp > 8))   
          {                  
            tmp = 8;
          }                      
          printf("AT+P%u\r\n", tmp); 
          delay_ms(600); 
                                   
          lcd_putc("\f");
          lcd_gotoxy(1, 1);
          lcd_putc("Set Channel:");               
          tmp = inc_dec(1, 2, tmp, 127, 1);
          if((tmp < 1) || (tmp > 127))
          {                                               
            tmp = 1;
          }  
          printf("AT+C%03u\r\n", tmp);  
          delay_ms(600); 
      }
      
      output_low(LED);
      output_high(set);                     
      delay_ms(400); 
                                            
      check_RF();
}                                          
                              
                   
unsigned char inc_dec(unsigned char x_pos, unsigned char y_pos, signed long value, unsigned char max, unsigned char min)
{                                 
    while(TRUE)
    {
        lcd_gotoxy(x_pos, y_pos);
        printf(lcd_putc, "%u ", (unsigned char)value);
                               
        if(bt2)
        {                  
            delay_ms(kbd_dly);      
            value++;
        }   
        
        if(value > max)
        {
            lcd_gotoxy(x_pos, y_pos);
            lcd_putc("    ");           
            value = min;
        } 
        
        if(bt3)
        {
            delay_ms(kbd_dly);
            value--;
        } 
        
        if(value < min)
        {
            lcd_gotoxy(x_pos, y_pos);
            lcd_putc("    ");  
            value = max;
        }
            
        if(bt1)
        {
            return (max + 1);  
        }
            
        if(bt4)
        {
            return value; 
        }   
    }; 
}                                           
                                       
                                         
void read_and_display_output(unsigned char start_char, unsigned char stop_char) 
{                                                           
     short done = FALSE;  
     unsigned char p = 0;
     unsigned char i = 0;
                        
     memset(str, 0x00, sizeof(str)); 
     
     do
     {       
            str[i] = getc();    
            if((str[i] == start_char) && (done == FALSE))     
            {
                p = i;
                done = TRUE;
            }   
            i++;         
     }while(str[i] != stop_char); 
              
     i = p;                  
     do
     {                                    
            if((str[i] >= 32) && (str[i] <= 126))
            {                                                     
                lcd_gotoxy((1 + (i - p)), 2);                      
                printf(lcd_putc, "%c ", str[i]);            
            }     
            i++;         
     }while(str[i] != stop_char);   
}                                            
                                                     
