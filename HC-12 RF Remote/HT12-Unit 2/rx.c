#define set       PORTD6_bit
#define LED       PORTD7_bit

#define bt1       PIND2_bit
#define bt2       PIND3_bit
#define bt3       PIND4_bit
#define bt4       PIND5_bit

#define str_len   11


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


void setup();
void check_RF();
void set_RF();
unsigned char inc_dec(unsigned char x_pos, unsigned char y_pos, signed long value, unsigned char max, unsigned char min);
void show_modem_data(unsigned char ch[], unsigned char start_char, unsigned char stop_char);


void main() 
{
   unsigned char rcv = 0;
   
   setup();
   check_RF();
   
   while(1)
   {

            if(bt1 == 1)
            {
                while(bt1 == 1);
                lcd_chr(1, 13, '1');
                UART_write_text("1");
            }
            if(bt2 == 1)
            {
                while(bt2 == 1);
                lcd_chr(1, 13, '2');
                UART_write_text("2");
            }
            if(bt3 == 1)
            {
                while(bt3 == 1);
                lcd_chr(1, 13, '3');
                UART_write_text("3");
            }
            if(bt4 == 1)
            {
                while(bt4 == 1);
                delay_ms(600);
                set_RF();
            }


            if(UART1_Data_Ready() == 1)
            {
                rcv = UART_Read();

                if((rcv >= 32) && (rcv <= 126))
                {
                        lcd_chr(2, 13, rcv);
                }
            }
   };
}


void setup()
{
      PORTB = 0x00;
      DDRB = 0x00;
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
      TIMSK = 0x00;
      UCSRB = 0x00;
      ACSR = 0x80;
      SFIOR = 0x00;
      ADCSRA = 0x00;
      SPCR = 0x00;
      TWCR = 0x00;
      Lcd_Init();
      Lcd_Cmd(_LCD_CLEAR);
      Lcd_Cmd(_LCD_CURSOR_OFF);
      UART1_Init_Advanced(9600, _UART_NOPARITY, _UART_ONE_STOPBIT);
      delay_ms(600);
}


void check_RF()
{
     bit stat;
     signed char cmp = 0;
     unsigned char rx_data[str_len];

     stat = 0;
     set = 1;
     delay_ms(10);
     set = 0;
     delay_ms(400);
     
     while(stat == 0)
     {
         memset(rx_data, 0x00, sizeof(rx_data));
         lcd_out(1, 3, "Checking RF.");
         lcd_out(2, 5, "AT =");
         delay_ms(600);
         LED = 1;
         UART_write_text("AT\r\n");
         UART_Read_Text(rx_data, "\r", 6);
         cmp = strcmp("OK", rx_data);
         if(cmp == 0)
         {
             LED = 1;
             lcd_out(2, 10, "OK.");
             delay_ms(900);
             stat = 1;
         }
         else
         {
             LED = 0;
             lcd_out(2, 10, "ERR");
             delay_ms(900);
             lcd_out(2, 9, "     ");
             stat = 0;
         }
     }
     LED = 0;
     
     memset(rx_data, 0x00, sizeof(rx_data));
     Lcd_Cmd(_LCD_CLEAR);
     lcd_out(1, 1, "RF S/W Version:");
     UART_write_text("AT+V\r");
     UART_Read_Text(rx_data, "\r", str_len);
     show_modem_data(rx_data, 'H', '\r');
     delay_ms(2000);

     memset(rx_data, 0x00, sizeof(rx_data));
     Lcd_Cmd(_LCD_CLEAR);
     lcd_out(1, 1, "Baud Rate:");
     UART_write_text("AT+RB\r");
     UART_Read_Text(rx_data, "\r", str_len);
     show_modem_data(rx_data, 'B', '\r');
     delay_ms(2000);

     memset(rx_data, 0x00, sizeof(rx_data));
     Lcd_Cmd(_LCD_CLEAR);
     lcd_out(1, 1, "Channel:");
     UART_write_text("AT+RC\r");
     UART_Read_Text(rx_data, "\r", str_len);
     show_modem_data(rx_data, 'C', '\r');
     delay_ms(2000);

     memset(rx_data, 0x00, sizeof(rx_data));
     Lcd_Cmd(_LCD_CLEAR);
     lcd_out(1, 1, "TX Power:");
     UART_write_text("AT+RP\r");
     UART_Read_Text(rx_data, "\r", str_len);
     show_modem_data(rx_data, 'P', '\r');
     delay_ms(2000);

     memset(rx_data, 0x00, sizeof(rx_data));
     Lcd_Cmd(_LCD_CLEAR);
     lcd_out(1, 1, "TX-RX Mode:");
     UART_write_text("AT+RF\r");
     UART_Read_Text(rx_data, "\r", str_len);
     show_modem_data(rx_data, 'F', '\r');
     delay_ms(2000);
     
     Lcd_Cmd(_LCD_CLEAR);
     set = 1;
     delay_ms(200);
     
     lcd_out(1, 4, "CMD Sent:");
     lcd_out(2, 4, "CMD Rcv.:");
}


void set_RF()
{
      unsigned char tmp = 0;

      Lcd_Cmd(_LCD_CLEAR);
      lcd_out(1, 5, "Setup RF");

      LED = 1;
      set = 0;
      delay_ms(600);

      Lcd_Cmd(_LCD_CLEAR);
      lcd_out(1, 1, "Load Defaults?");
      lcd_out(2, 1, "Y = 1  N = 0");
      tmp = inc_dec(13, 2, tmp, 1, 0);
      if(tmp == 1)
      {
        UART_write_text("AT+DEFAULT\r\n");
      }
      else
      {
          delay_ms(600);
          tmp = 3;
          Lcd_Cmd(_LCD_CLEAR);
          lcd_out(1, 1, "Set TX-RX Mode:");
          tmp = inc_dec(1, 2, tmp, 3, 1);
          if((tmp < 1) || (tmp > 3))
          {
            tmp = 3;
          }
          UART_write_text("AT+FU");
          UART_write((tmp + 48));
          UART_write_text("\r\n");
          delay_ms(600);

          tmp = 8;
          Lcd_Cmd(_LCD_CLEAR);
          lcd_out(1, 1, "Set TX Power:");
          tmp = inc_dec(1, 2, tmp, 8, 1);
          if((tmp < 1) || (tmp > 8))
          {
            tmp = 8;
          }
          UART_write_text("AT+P");
          UART_write((tmp + 48));
          UART_write_text("\r\n");
          delay_ms(600);

          Lcd_Cmd(_LCD_CLEAR);
          lcd_out(1, 1, "Set Channel:");
          tmp = inc_dec(1, 2, tmp, 127, 1);
          if((tmp < 1) || (tmp > 127))
          {
            tmp = 1;
          }
          if((tmp >= 1) && (tmp <= 9))
          {
              UART_write_text("AT+FU00");
              UART_write((tmp + 48));
              UART_write_text("\r\n");
          }
          if((tmp >= 10) && (tmp <= 99))
          {
              UART_write_text("AT+FU0");
              UART_write(((tmp / 10) + 48));
              UART_write(((tmp % 10) + 48));
              UART_write_text("\r\n");
          }
          if((tmp >= 100) && (tmp <= 127))
          {
              UART_write_text("AT+FU");
              UART_write(((tmp / 100) + 48));
              UART_write((((tmp / 10) % 10) + 48));
              UART_write(((tmp % 10) + 48));
              UART_write_text("\r\n");
          }
          delay_ms(600);
      }

      Lcd_Cmd(_LCD_CLEAR);
      LED = 0;
      set = 1;
      delay_ms(400);
      
      check_RF();
}


unsigned char inc_dec(unsigned char x_pos, unsigned char y_pos, signed long value, unsigned char max, unsigned char min)
{
    unsigned char txt[9];
    
    while(1)
    {
        ByteToStr((unsigned char)value, txt);
        lcd_out(y_pos, x_pos, txt);

        if(bt2)
        {
            delay_ms(40);
            value++;
        }

        if(value > max)
        {
            lcd_out(y_pos, x_pos, "    ");
            value = min;
        }

        if(bt3)
        {
            delay_ms(40);
            value--;
        }

        if(value < min)
        {
            lcd_out(y_pos, x_pos, "    ");
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


void show_modem_data(unsigned char ch[], unsigned char start_char, unsigned char stop_char)
{
     bit done;
     unsigned char i = 0;
     unsigned char p = 0;
     
     done = 0;

     do
     {
        if((ch[i] == start_char) && (done == 0))
        {
            p = i;
            done = 1;
        }
        i++;
     }while(ch[i] != stop_char);

     i = p;
     do
     {
        if((ch[i] >= 32) && (ch[i] <= 126))
        {
            lcd_chr(2, ((i - p) + 1), (ch[i]));
            lcd_out(2, ((i - p) + 2), "      ");
        }
        i++;
     }while(ch[i] != stop_char);
}