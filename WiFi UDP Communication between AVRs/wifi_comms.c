#define SET                !PINB3_bit
#define INC                !PINB2_bit
#define DEC                !PINB1_bit
#define ESC                !PINB0_bit

#define RDY                PIND3_bit

#define RST                PORTD2_bit

#define str_len            60
#define key_delay          90

#define STA                1
#define AP                 0


sbit LCD_RS at PORTD6_bit;
sbit LCD_EN at PORTD4_bit;
sbit LCD_D4 at PORTB4_bit;
sbit LCD_D5 at PORTB5_bit;
sbit LCD_D6 at PORTB6_bit;
sbit LCD_D7 at PORTB7_bit;

sbit LCD_RS_Direction at DDD6_bit;
sbit LCD_EN_Direction at DDD4_bit;
sbit LCD_D4_Direction at DDB4_bit;
sbit LCD_D5_Direction at DDB5_bit;
sbit LCD_D6_Direction at DDB6_bit;
sbit LCD_D7_Direction at DDB7_bit;


unsigned char buffer[str_len];


void setup();
void(* resetFunc)() = 0;
void flush_buffer();
void check_wifi();
void show_wifi_infos();
void show_wifi_data(unsigned char ch[], unsigned char limit, signed char offset);
unsigned char disp_char(unsigned char value, unsigned char value_max, unsigned char value_min, unsigned char x_pos, unsigned char y_pos, unsigned char rcv);
signed int inc_dec(signed int value, signed int value_max, signed int value_min, unsigned char x_pos, unsigned char y_pos);
void display_and_write_uart(unsigned char value, unsigned char x_pos, unsigned char y_pos, unsigned char digits, unsigned char point);
void set_SSID_or_key(unsigned char x_pos, unsigned char y_pos, unsigned char digits);
void setup_wifi();
void data_tx_rx();


void main() 
{
    unsigned int i = 0;
    
    setup();

    check_wifi();
    show_wifi_infos();

    while(1)
    {
            switch(i)
            {
                case 1:
                {
                     setup_wifi();
                     i = 0;
                     break;
                }
                default:
                {
                     data_tx_rx();
                     if(ESC)
                     {
                         i = 1;
                     }
                     break;
                }
            }
    };
}


void setup()
{
    PORTA = 0x00;
    DDRA = 0x00;
    PORTB = 0x0F;
    DDRB = 0xF0;
    PORTC = 0x00;
    DDRC = 0x00;
    PORTD = 0x00;
    DDRD = 0x76;
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
    ASSR = 0x00;
    TCCR2 = 0x00;
    TCNT2 = 0x00;
    OCR2 = 0x00;
    MCUCR = 0x00;
    MCUCSR = 0x00;
    TIMSK = 0x00;
    UCSRA = 0x00;
    UCSRB = 0x18;
    UCSRC = 0x86;
    UBRRH = 0x00;
    UBRRL = 0x0C;
    ACSR = 0x80;
    SFIOR = 0x00;
    ADCSRA = 0x00;
    SPCR = 0x00;
    TWCR = 0x00;
    
    Lcd_Init();
    Lcd_Cmd(_LCD_CLEAR);
    Lcd_Cmd(_LCD_CURSOR_OFF);
    UART1_Init_Advanced(57600, _UART_NOPARITY, _UART_ONE_STOPBIT);
    delay_ms(100);
}


void flush_buffer()
{
    signed char i = 59;

    while(i > -1)
    {
        buffer[i] = 0x00;
        i--;
    };
}


void check_wifi()
{
     bit chk;
     unsigned char cmp;
     unsigned char i = 0;

     chk = 0;
     cmp = 1;

     Lcd_Cmd(_LCD_CLEAR);
     lcd_out(1, 7, "WiFi-232");
     lcd_out(2, 6, "Initiating");
     RST = 1;
     while(RDY != 0);
     delay_ms(600);
     lcd_out(2, 4, "              ");
     while(chk == 0)
     {
         flush_buffer();
         lcd_out(3, 1, "Checking WiFi Device");
         UART_write_text("+++");
         delay_ms(400);
         UART_write_text("a");
         UART_Read_Text(buffer, "\r", 6);
         cmp = strcmp("a+ok", buffer);

         if(cmp == 0)
         {
             chk = 1;
             lcd_out(4, 3, "WiFi Device Okay");
             delay_ms(2000);
         }
         else
         {
             chk = 0;
             lcd_out(4, 2, "WiFi Device Error!");
             i++;
             if(i == 3)
             {
                  Lcd_Cmd(_LCD_CLEAR);
                  lcd_out(2, 3, "Unable to detect");
                  lcd_out(3, 5, "WiFi device!");
                  while(1);
             }
             delay_ms(2000);
         }
     };
     
     flush_buffer();
}


void show_wifi_infos()
{
     unsigned char rx_data[str_len];

     Lcd_Cmd(_LCD_CLEAR);
     lcd_out(1, 1, "Version:");
     memset(rx_data, 0x00, sizeof(rx_data));
     UART_write_text("AT+VER\r");
     UART_Read_Text(rx_data, "\r\n\r\n", str_len);
     show_wifi_data(rx_data, 36, -14);
     delay_ms(2000);
     Lcd_Cmd(_LCD_CLEAR);
     Uart_Write_Text("AT+ENTM\r");
     delay_ms(100);

}


void show_wifi_data(unsigned char ch[], unsigned char limit, signed char offset)
{
     unsigned char i = 0;

     for(i = 0; i < limit; i++)
     {
        if((ch[i] >= 32) && (ch[i] <= 127))
        {
             lcd_chr(2, (i + offset), ch[i]);
             delay_ms(120);
        }
     }
}


unsigned char disp_char(unsigned char value, unsigned char value_max, unsigned char value_min, unsigned char x_pos, unsigned char y_pos, unsigned char rcv)
{
     static unsigned char RX_data;
     
     while(1)
     {
         if(INC)
         {
             delay_ms(key_delay);
             value++;
         }
         if(value > value_max)
         {
             value = value_min;
         }

         if(DEC)
         {
             delay_ms(key_delay);
             value--;
         }
         if(value < value_min)
         {
             value = value_max;
         }

         lcd_chr(y_pos, x_pos, value);
         
         if(rcv)
         {
              if(UART_Data_Ready())
              {
                 RX_data = Uart_Read();
                 if((RX_data >= 32) && (RX_data <= 126))
                 {
                     lcd_chr(2, 1, RX_data);
                 }
              }
         }

         if(SET)
         {
             while(SET);
             Uart_Write(value);
             delay_ms(key_delay);
             return value;
         }
         
         if(ESC)
         {
             delay_ms(key_delay);
             break;
         }
     }
}


signed int inc_dec(signed int value, signed int value_max, signed int value_min, unsigned char x_pos, unsigned char y_pos)
{
     while(1)
     {
         if(INC)
         {
             value++;
         }
         if(value > value_max)
         {
             value = value_min;
         }

         if(DEC)
         {
             value--;
         }
         if(value < value_min)
         {
             value = value_max;
         }

         lcd_out(y_pos, x_pos, " ");
         lcd_chr(y_pos, x_pos, (value + 0x30));
         delay_ms(key_delay);

         if(SET)
         {
             delay_ms(key_delay);
             while(SET);
             return value;
         }
     }
}


void display_and_write_uart(unsigned char value, unsigned char x_pos, unsigned char y_pos, unsigned char digits, unsigned char point)
{
     unsigned char c = 0;
     
     for(c = 0; c < digits; c++)
     {
        value = inc_dec(value, 9, 0, (x_pos + c), y_pos);
        Uart_Write(value + 0x30);
     }
     
     switch(point)
     {
         case 1:
         {
            lcd_out(y_pos, (x_pos + digits), ".");
            Uart_Write('.');
            break;
         }
         default:
         {
            break;
         }
     }
}


void set_SSID_or_key(unsigned char x_pos, unsigned char y_pos, unsigned char digits)
{
     unsigned char c = 0;
     unsigned char value = 0;
     
     for(c = 0; c < digits; c++)
     {
        value = disp_char(value, 127, 32, (c + x_pos), y_pos, 0);
     }
}


void setup_wifi()
{
     bit mode;
     
     unsigned char v = 0;
     
     lcd_cmd(_LCD_CLEAR);
     lcd_out(1, 6, "WiFi Setup");

     lcd_out(2, 1, "1 = STA  0 = AP");
     mode = inc_dec(mode, STA, AP, 20, 2);

     lcd_out(3, 1, "LAN:");
     Uart_Write_Text("AT+LANN=");

     display_and_write_uart(v, 6, 3, 3, 1);
     display_and_write_uart(v, 10, 3, 3, 1);
     display_and_write_uart(v, 14, 3, 3, 1);
     display_and_write_uart(v, 18, 3, 3, 0);

     lcd_out(4, 1, "SUB:");
     Uart_Write(',');

     display_and_write_uart(v, 6, 4, 3, 1);
     display_and_write_uart(v, 10, 4, 3, 1);
     display_and_write_uart(v, 14, 4, 3, 1);
     display_and_write_uart(v, 18, 4, 3, 0);
     Uart_Write('\r');
     delay_ms(1000);

     Lcd_Cmd(_LCD_CLEAR);
     lcd_out(1, 6, "WiFi Setup");

     lcd_out(2, 1, "Port ID:");
     Uart_Write_Text("AT+NETP=UDP,SERVER,");
     delay_ms(40);
     display_and_write_uart(v, 17, 2, 4, 0);
     lcd_out(3, 1, "Server Address:");
     Uart_Write(',');
     delay_ms(40);
     display_and_write_uart(v, 1, 4, 3, 1);
     display_and_write_uart(v, 5, 4, 3, 1);
     display_and_write_uart(v, 9, 4, 3, 1);
     display_and_write_uart(v, 13, 4, 3, 0);
     Uart_Write('\r');
     delay_ms(100);

     Lcd_Cmd(_LCD_CLEAR);
     lcd_out(1, 6, "WiFi Setup");

     switch(mode)
     {
         case STA:
         {
             lcd_out(2, 1, "SSID:");
             Uart_Write_Text("AT+WSSSID=");
             delay_ms(40);
             set_SSID_or_key(7, 2, 4);
             Uart_Write('\r');
             delay_ms(100);

             lcd_out(3, 1, "WiFi STA Password:");
             Uart_Write_Text("AT+WSKEY=WPAPSK,AES,");
             set_SSID_or_key(1, 4, 8);
             delay_ms(10);
             Uart_Write('\r');
             delay_ms(100);
             
             Uart_Write_Text("AT+WMODE=STA\r");
             break;
         }
         case AP:
         {
             lcd_out(2, 1, "SSID:");
             Uart_Write_Text("AT+WAP=11BGN,");
             delay_ms(40);
             set_SSID_or_key(7, 2, 4);
             Uart_Write_Text(",AUTO\r");
             delay_ms(100);

             lcd_out(3, 1, "WiFi AP Password:");
             Uart_Write_Text("AT+WAKEY=WPAPSK,AES,");
             set_SSID_or_key(1, 4, 8);
             delay_ms(10);
             Uart_Write('\r');
             delay_ms(100);
             
             Uart_Write_Text("AT+WMODE=AP\r");
             break;
         }
     }
     delay_ms(100);

     Uart_Write_Text("AT+TMODE=Through\r");
     delay_ms(100);
     Uart_Write_Text("AT+ENTM\r");
     delay_ms(100);
     Uart_Write_Text("AT+Z\r");
     delay_ms(900);
     while(RDY != 0);
     Lcd_Cmd(_LCD_CLEAR);
}


void data_tx_rx()
{
    static unsigned char TX_data;

    lcd_out(1, 1, "RX Data:");
    lcd_out(3, 1, "TX Data:");

    TX_data = disp_char(TX_data, 126, 32, 1, 4, 1);
}