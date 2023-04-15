#include "DS1202.c"


#define up                      1
#define down                    2
#define left                    3
#define right                   4
#define none                    0

#define up_button               !PINA0_bit
#define down_button             !PINA1_bit
#define right_button            !PINA2_bit
#define left_button             !PINA3_bit


sbit LCD_RS at PORTC2_bit;
sbit LCD_EN at PORTC3_bit;
sbit LCD_D4 at PORTC4_bit;
sbit LCD_D5 at PORTC5_bit;
sbit LCD_D6 at PORTC6_bit;
sbit LCD_D7 at PORTC7_bit;

sbit LCD_RS_Direction at DDC2_bit;
sbit LCD_EN_Direction at DDC3_bit;
sbit LCD_D4_Direction at DDC4_bit;
sbit LCD_D5_Direction at DDC5_bit;
sbit LCD_D6_Direction at DDC6_bit;
sbit LCD_D7_Direction at DDC7_bit;


void setup(void);
void LCD_print_value(unsigned char x_pos, unsigned char y_pos, unsigned char value);
void dow_disp(unsigned char dow);
void display_time(void);
void setup_RTC(void);
unsigned char get_buttons(void);
unsigned char set_value(unsigned char x_pos, unsigned char y_pos, signed char value, unsigned char max, unsigned char min, unsigned char type);


void main(void)
{
     setup();
     
     while(1)
     {
        if(get_buttons() == left)
        {
            while(get_buttons() == left);
            setup_RTC();
        }
        else
        {
            DS1202_get_time_and_date();
            display_time();
        }
     };
}


void setup(void)
{
    PORTA = 0x00;
    DDRA = 0x00;
    PORTB = 0x00;
    DDRB = 0x00;
    PORTC = 0x00;
    DDRC = 0xFE;
    PORTD = 0x00;
    DDRD = 0x00;
    PORTE = 0x00;
    DDRE = 0x00;
    TCCR0 = 0x00;
    TCNT0 = 0x00;
    OCR0 = 0x00;
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
    GICR = 0x00;
    MCUCR = 0x00;
    EMCUCR = 0x00;
    GIFR = 0x00;
    TIMSK = 0x00;
    UCSRB = 0x00;
    ACSR = 0x80;
    SPCR = 0x00;

    DS1202_init();

    Lcd_Init();
    Lcd_Cmd(_LCD_CLEAR);
    Lcd_Cmd(_LCD_CURSOR_OFF);
    delay_ms(10);
}


void LCD_print_value(unsigned char x_pos, unsigned char y_pos, unsigned char value)
{
    Lcd_Chr(y_pos, x_pos, ((value / 10) + 0x30));
    Lcd_Chr(y_pos, (x_pos + 1), ((value % 10) + 0x30));
}


void dow_disp(unsigned char dow)
{
    switch(dow)
    {
      case 1:
      {
      	Lcd_Out(2, 3, "SUN");
      	break;
      }
      case 2:
      {
      	Lcd_Out(2, 3, "MON");
      	break;
      }
      case 3:
      {
      	Lcd_Out(2, 3, "TUE");
      	break;
      }
      case 4:
      {
      	Lcd_Out(2, 3, "WED");
      	break;
      }
      case 5:
      {
      	Lcd_Out(2, 3, "THR");
      	break;
      }
      case 6:
      {
      	Lcd_Out(2, 3, "FRI");
      	break;
      }
      case 7:
      {
      	Lcd_Out(2, 3, "SAT");
      	break;
      }
      default:
      {
      	Lcd_Out(2, 3, "   ");
      	break;
      }
    }
}


void display_time(void)
{
    LCD_print_value(5, 1, time.hour);
    Lcd_Out(1, 7, ":");
    LCD_print_value(8, 1, time.min);
    Lcd_Out(1, 10, ":");
    LCD_print_value(11, 1, time.sec);
    
    dow_disp(time.dow);
    
    LCD_print_value(7, 2, time.date);
    Lcd_Out(2, 9, "/");
    LCD_print_value(10, 2, time.month);
    Lcd_Out(2, 12, "/");
    LCD_print_value(13, 2, time.year);
    
    delay_ms(400);
}


void setup_RTC(void)
{
    unsigned char temp1 =  0x00;
    unsigned char temp2 =  0x00;
    unsigned char temp3 =  0x00;
    unsigned char temp4 =  0x00;

    temp1 = set_value(5, 1, time.hour, 23, 0, 1);
    delay_ms(200);
    temp2 = set_value(8, 1, time.min, 59, 0, 1);
    delay_ms(200);
    temp3 = set_value(11, 1, time.sec, 59, 0, 1);
    delay_ms(200);

    DS1202_set_time(temp1, temp2, temp3);

    temp4 = set_value(3, 2, time.dow, 7, 1, 0);
    delay_ms(200);
    temp1 = set_value(7, 2, time.date, 31, 1, 1);
    delay_ms(200);
    temp2 = set_value(10, 2, time.month, 12, 1, 1);
    delay_ms(200);
    temp3 = set_value(13, 2, time.year, 99, 0, 1);
    delay_ms(200);

    DS1202_set_date(temp1, temp2, temp3, temp4);
}


unsigned char get_buttons(void)
{
    if(left_button)
    {
        return left;
    }
    else if(right_button)
    {
        return right;
    }
    else if(up_button)
    {
        return up;
    }
    else if(down_button)
    {
        return down;
    }
    else
    {
        return none;
    }
}


unsigned char set_value(unsigned char x_pos, unsigned char y_pos, signed char value, unsigned char max, unsigned char min, unsigned char type)
{
    bit tgl;
    
    while(1)
    {
        tgl = ~tgl;
        delay_ms(90);

        if(get_buttons() == up)
        {
            value++;
        }

        if(value > max)
        {
            value = min;
        }
        
        if(get_buttons() == down)
        {
            value--;
        }

        if(value < min)
        {
            value = max;
        }

        switch(type)
        {
          case 1:
          {
            switch(tgl)
  	    {
                case 1:
  	        {
                    LCD_print_value(x_pos, y_pos, value);
  		    break;
                }

      	        default:
      	        {
      	            Lcd_Out(y_pos, x_pos, "  ");
      	            break;
                }
             }
                break;
          }
          default:
          {
              switch(tgl)
              {
                  case 1:
                  {
                      dow_disp(value);
                      break;
                  }
                  default:
                  {
                      dow_disp(0);
                      break;
                  }
              }
              break;
          }
        }

        if((get_buttons() == right) && (tgl))
        {
           return value;
        }
    };
}