#define RESET              PORTD2_bit
#define MODE               PORTD3_bit

#define SET                !PINB0_bit
#define INC                !PINB1_bit
#define DEC                !PINB2_bit
#define ESC                !PINB3_bit

#define com_mode           0
#define at_mode            1


sbit LCD_RS at PORTD6_bit;
sbit LCD_EN at PORTD4_bit;
sbit LCD_D4 at PORTB4_bit;
sbit LCD_D5 at PORTB5_bit;
sbit LCD_D6 at PORTB6_bit;
sbit LCD_D7 at PORTB7_bit;

sbit LCD_RS_Direction at DDD7_bit;
sbit LCD_EN_Direction at DDD5_bit;
sbit LCD_D4_Direction at DDB4_bit;
sbit LCD_D5_Direction at DDB5_bit;
sbit LCD_D6_Direction at DDB6_bit;
sbit LCD_D7_Direction at DDB7_bit;


unsigned char buffer[100];
unsigned char name[6];
unsigned char pass[4];
unsigned char symbol_pos[9];
unsigned char comma_pos[16];
unsigned char tmp[40];

bit checked;
unsigned char device_count = 0;


void setup();
void(* resetFunc)() = 0;
void flush_buffer();
void flush_tmp_buffer();
void check_BT();
void basic_BT_info();
void main_menu();
void tasks();
unsigned char disp_char(unsigned char value, unsigned char value_max, unsigned char value_min, unsigned char x_pos, unsigned char y_pos);
signed char inc_dec(signed char value, signed char value_max, signed char value_min, unsigned char x_pos, unsigned char y_pos);
void show_BT_data(unsigned char ch[], unsigned char start_char, unsigned char stop_char, unsigned char x_pos, unsigned char y_pos);
unsigned char search_char(unsigned char start_pos, unsigned char stop_pos, unsigned char search_ch);
void find_symbols(unsigned char start_pos, unsigned char stop_pos, unsigned char symbol1, unsigned char symbol2);
void replace_symbols(unsigned char start_pos, unsigned char stop_pos, unsigned char symbol);
void show_BT_addresses(unsigned char start, unsigned char stop, unsigned char y_pos);
void write_BT_address(unsigned char start, unsigned char stop);
void show_BT_names(unsigned char start, unsigned char stop, unsigned char y_pos);
void link_BT(unsigned char start, unsigned char stop);
void clear_screen();


void main()
{
     unsigned char i = 0;

     setup();
     check_BT();
     basic_BT_info();

     while(1)
     {
         tasks();
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
    DDRD = 0x7E;
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
    UBRRL = 0x33;

    Lcd_Init();
    Lcd_Cmd(_LCD_CLEAR);
    Lcd_Cmd(_LCD_CURSOR_OFF);
    UART1_Init_Advanced(9600, _UART_NOPARITY, _UART_ONE_STOPBIT);
    flush_buffer();
    delay_ms(100);
}


void flush_buffer()
{
    signed char i = 99;

    while(i > -1)
    {
        buffer[i] = 0x00;
        i--;
    };
}


void flush_tmp_buffer()
{
    signed char i = 39;

    while(i > -1)
    {
        tmp[i] = 0x00;
        i--;
    };
}


void check_BT()
{
     bit chk;
     bit cmp;
     char i = 0;

     chk = 0;
     cmp = 0;

     Lcd_Cmd(_LCD_CLEAR);
     lcd_out(1, 4, "HC05 Bluetooth");
     lcd_out(2, 4, "Initiating....");

     delay_ms(900);
     RESET = 0;
     delay_ms(900);
     RESET = 1;
     MODE = com_mode;
     delay_ms(900);
     MODE = at_mode;

     lcd_out(2, 4, "              ");
     lcd_out(3, 2, "Checking BT Device");

     while(chk == 0)
     {
         UART_write_text("AT\r\n");
         UART_Read_Text(buffer, "\r", 6);
         cmp = strcmp("OK", buffer);

         if(cmp == 0)
         {
             chk = 1;
             lcd_out(4, 4, "BT Device Okay");
             delay_ms(2000);
         }
         else
         {
             chk = 0;
             lcd_out(4, 3, "BT Device Error!");
             i++;
             if(i == 3)
             {
                  Lcd_Cmd(_LCD_CLEAR);
                  lcd_out(2, 3, "Unable to detect");
                  lcd_out(2, 3, "Bluetooth device..");
                  while(1);
             }
             delay_ms(4000);
         }
     };
}


void basic_BT_info()
{
     Lcd_Cmd(_LCD_CLEAR);

     flush_buffer();
     lcd_out(1, 1, "Name:");
     UART_write_text("AT+NAME?\r\n");
     UART_Read_Text(buffer, "OK", 20);
     show_BT_data(buffer, ':', '\r', 6, 1);
     delay_ms(200);

     flush_buffer();
     lcd_out(2, 1, "Code:");
     UART_write_text("AT+PSWD?\r\n");
     UART_Read_Text(buffer, "OK", 20);
     show_BT_data(buffer, ':', '\r', 6, 2);
     delay_ms(200);

     flush_buffer();
     lcd_out(3, 1, "Addr:");
     UART_write_text("AT+ADDR?\r\n");
     UART_Read_Text(buffer, "OK", 40);
     show_BT_data(buffer, ':', '\r', 6, 3);
     delay_ms(200);

     flush_buffer();
     lcd_out(4, 1, "Ver.:");
     UART_write_text("AT+VERSION?\r\n");
     UART_Read_Text(buffer, "OK", 40);
     show_BT_data(buffer, ':', '\r', 6, 4);
     delay_ms(4000);
}


void main_menu()
{
     Lcd_Cmd(_LCD_CLEAR);

     lcd_out(1, 1, "1. Set BT Parameters");
     lcd_out(2, 1, "2. Search & Connect");
     lcd_out(3, 1, "3. Send/Receive Data");
     lcd_out(4, 1, "Selection:");
     
     MODE = at_mode;
}


void tasks()
{
     unsigned char i = 0;
     unsigned char ch = 0;
     signed char n = 0;

     main_menu();
     i = inc_dec(i, 3, 1, 12, 4);
     delay_ms(600);

     Lcd_Cmd(_LCD_CLEAR);

     switch(i)
     {
         case 1:
         {
             lcd_out(1, 2, "Set BT Parameters");
             lcd_out(2, 1, "Name:");
             lcd_out(3, 1, "Code:");
             lcd_out(4, 1, "Role:");

             while(1)
             {
                     UART_Write_text("AT+NAME=");
                     for(n = 0; n < 6; n++)
                     {
                         name[n] = disp_char(ch, 127, 32, (7 + n), 2);
                         UART_Write(name[n]);
                     }
                     UART_Write_text("\r\n");
                     delay_ms(600);

                     UART_Write_text("AT+PSWD=");
                     for(n = 0; n < 4; n++)
                     {
                         pass[n] = disp_char(ch, 57, 48, (7 + n), 3);
                         UART_Write(pass[n]);

                     }
                     UART_Write_text("\r\n");
                     delay_ms(600);

                     n = 48;
                     while(!SET)
                     {
                         if(INC)
                         {
                             n = 49;
                         }
                         if(DEC)
                         {
                             n = 48;
                         }

                         if(n == 48)
                         {
                             lcd_out(4, 6, "BT Slave ");
                         }
                         else
                         {
                             lcd_out(4, 6, "BT Master");
                         }
                     }
                     UART_Write_text("AT+ROLE=");
                     UART_Write(n);
                     UART_Write_text("\r\n");
                     delay_ms(100);
                     UART_Write_text("AT+RESET\r\n");
                     RESET = 0;
                     delay_ms(900);
                     resetFunc();
                     break;
             }
             break;
         }
         case 2:
         {
             flush_buffer();
             UART_Write_text("AT+ROLE?\r\n");
             UART_Read_Text(buffer, "OK", 12);

             ch = search_char(0, 12, '1');

             if(ch == 1)
             {
                 checked = 0;
                 device_count = 0;
                 
                 lcd_out(2, 5, "Searching...");

                 UART_Write_text("AT+RMAAD\r\n");
                 delay_ms(100);
                 UART_Write_text("AT+CMODE=0\r\n");
                 delay_ms(100);
                 UART_Write_text("AT+INQM=0,3,9\r\n");
                 delay_ms(100);
                 UART_Write_text("AT+INIT\r\n");
                 delay_ms(100);
                 flush_buffer();
                 UART_Write_text("AT+INQ\r\n");

                 while(uart_read() != '+');
                 UART_Read_Text(buffer, "OK", 98);

                 find_symbols(0, 98, ':', ',');
                 Lcd_Cmd(_LCD_CLEAR);
                 
                 if(device_count == 1)
                 {
                     lcd_out(1, 1, "1.");

                     show_BT_addresses(0, 0, 1);
                 }

                 else if(device_count == 2)
                 {
                     lcd_out(1, 1, "1.");
                     lcd_out(2, 1, "2.");

                     show_BT_addresses(0, 0, 1);
                     show_BT_addresses(3, 2, 2);
                 }
                 else
                 {
                     lcd_out(1, 1, "1.");
                     lcd_out(2, 1, "2.");
                     lcd_out(3, 1, "3.");

                     show_BT_addresses(0, 0, 1);
                     show_BT_addresses(3, 2, 2);
                     show_BT_addresses(6, 4, 3);
                 }

                 lcd_out(4, 1, "Selection:");

                 replace_symbols(0, 98, ':');
                 UART_Write_text("AT+INQC\r\n");
                 delay_ms(6000);

                 find_symbols(0, 98, ':', ',');

                 clear_screen();
                 if(device_count == 1)
                 {
                     show_BT_names(0, 3, 1);
                 }

                 else if(device_count == 2)
                 {
                     show_BT_names(0, 3, 1);
                     show_BT_names(5, 8, 2);
                 }
                 else
                 {
                     show_BT_names(0, 3, 1);
                     show_BT_names(5, 8, 2);
                     show_BT_names(10, 13, 3);
                 }

                 n = inc_dec(n, 3, 1, 12, 4);

                 switch(n)
                 {
                     case 1:
                     {
                         link_BT(0, 3);
                         break;
                     }
                     case 2:
                     {
                         link_BT(5, 8);
                         break;
                     }
                     case 3:
                     {
                         link_BT(10, 13);
                         break;
                     }
                 }
             }
             else
             {
                 lcd_out(2, 1, "Device set as slave.");
                 delay_ms(4000);
             }
             
             i = 3;
         }
         case 3:
         {
             n = 0;
             MODE = com_mode;
             Lcd_Cmd(_LCD_CLEAR);
             lcd_out(2, 4, "Connecting....");
             delay_ms(9000);
             
             Lcd_Cmd(_LCD_CLEAR);
             lcd_out(1, 1, "RX Data:");
             lcd_out(3, 1, "TX Data:");

             while((!ESC))
             {
                if(INC)
                {
                    n++;
                    delay_ms(90);
                }

                if(n > 127)
                {
                   n = 32;
                }

                if(DEC)
                {
                    n--;
                    delay_ms(90);
                }

                if(n < 32)
                {
                   n = 127;
                }

                if(SET)
                {
                    while(SET);
                    UART_write(n);
                }

                ch = UART_read();
                if((ch >= 32) && (ch <= 126))
                {
                    lcd_chr(2, 1, ch);
                }
                lcd_chr(4, 1, n);
             }
             
             UART_write_text("AT+DISC\r\n");
             delay_ms(200);
             
             RESET = 0;
             delay_ms(900);
             RESET = 1;
             
             Lcd_Cmd(_LCD_CLEAR);
             lcd_out(2, 3, "Disconnected....");
             delay_ms(4000);

             i = 0;
             break;
         }
     }
}


unsigned char disp_char(unsigned char value, unsigned char value_max, unsigned char value_min, unsigned char x_pos, unsigned char y_pos)
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

         lcd_chr(y_pos, x_pos, value);
         delay_ms(90);

         if(SET)
         {
             delay_ms(90);
             return value;
         }
         if(ESC)
         {
             delay_ms(90);
             return 0;
         }
     }
}


signed char inc_dec(signed char value, signed char value_max, signed char value_min, unsigned char x_pos, unsigned char y_pos)
{
     char txt[6];

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

         ByteToStr((unsigned char)value, txt);
         lcd_out(y_pos, x_pos, "   ");
         lcd_out(y_pos, x_pos, txt);
         delay_ms(90);

         if(SET)
         {
             delay_ms(90);
             return value;
         }
         if(ESC)
         {
             delay_ms(90);
             return -1;
         }
     }
}


void show_BT_data(unsigned char ch[], unsigned char start_char, unsigned char stop_char, unsigned char x_pos, unsigned char y_pos)
{
     bit done;
     unsigned char i = 0;
     unsigned char p = 0;

     done = 0;

     do
     {
        if((ch[i] == start_char) && (done == 0))
        {
            p = (i + 1);
            done = 1;
        }
        i++;
     }while(ch[i] != stop_char);

     i = p;
     do
     {
        if((ch[i] >= 32) && (ch[i] <= 126))
        {
            lcd_chr(y_pos, ((i - p) + x_pos + 1), (ch[i]));
            lcd_out(y_pos, ((i - p) + x_pos + 2), " ");
        }
        i++;
     }while(ch[i] != stop_char);
}


unsigned char search_char(unsigned char start_pos, unsigned char stop_pos, unsigned char search_ch)
{
     unsigned char i = 0;

     for(i = start_pos; i <= stop_pos; i++)
     {
         if(buffer[i] == search_ch)
         {
             return 1;
         }
     }

     return 0;
}


void find_symbols(unsigned char start_pos, unsigned char stop_pos, unsigned char symbol1, unsigned char symbol2)
{
     unsigned char i = 0;
     unsigned char j = 0;
     unsigned char k = 0;

     for(i = start_pos; i <= stop_pos; i++)
     {
         if(buffer[i] == symbol1)
         {
             symbol_pos[j] = i;

             if(checked == 0)
             {
                 if((j >= 0) && (j < 3))
                 {
                     device_count = 1;
                 }
                 else if((j >= 3) && (j < 6))
                 {
                     device_count = 2;
                 }
                 else if((j >= 6) && (j < 9))
                 {
                     device_count = 3;
                 }
             }

             j++;
         }
         if(buffer[i] == symbol2)
         {
             comma_pos[k] = i;
             k++;
         }
     }

     checked = 1;
}


void replace_symbols(unsigned char start_pos, unsigned char stop_pos, unsigned char symbol)
{
     unsigned char i = 0;

     for(i = start_pos; i <= stop_pos; i++)
     {
         if(buffer[i] == symbol)
         {
             buffer[i] = ',';
         }
     }
}


void show_BT_addresses(unsigned char start, unsigned char stop, unsigned char y_pos)
{
    unsigned char i = 0;
    unsigned char n = 4;

    for(i = (symbol_pos[start] + 1); i < comma_pos[stop]; i++)
    {
        if((buffer[i] >= 32) && (buffer[i] <= 126))
        {
            lcd_chr(y_pos, n, buffer[i]);
            n++;
        }
    }
}


void write_BT_address(unsigned char start, unsigned char stop)
{
    unsigned char i = 0;
    unsigned char n = 4;

    for(i = (comma_pos[start] + 1); i < comma_pos[stop]; i++)
    {
        if((buffer[i] >= 32) && (buffer[i] <= 126))
        {
            UART_Write(buffer[i]);
        }
    }
}


void show_BT_names(unsigned char start, unsigned char stop, unsigned char y_pos)
{
    flush_tmp_buffer();
    UART_write_text("AT+RNAME?");
    write_BT_address(start, stop);
    UART_write_text("\r\n");
    while(uart_read() != '+');
    UART_Read_Text(tmp, "OK", 40);
    show_BT_data(tmp, ':', '\r', 3, y_pos);
    delay_ms(100);
}


void link_BT(unsigned char start, unsigned char stop)
{
    UART_write_text("AT+PAIR=");
    write_BT_address(start, stop);
    UART_write_text(",30\r\n");
    delay_ms(100);

    UART_write_text("AT+BIND=");
    write_BT_address(start, stop);
    UART_write_text("\r\n");
    delay_ms(100);

    UART_write_text("AT+CMODE=1\r\n");
    delay_ms(100);

    UART_write_text("AT+LINK=");
    write_BT_address(start, stop);
    UART_write_text("\r\n");
    delay_ms(100);
}


void clear_screen()
{
    unsigned char i = 0;
    unsigned char j = 3;

    while(j > 0)
    {
        i = 20;
        while(i > 3)
        {
            lcd_out(j, i, " ");
            i--;
        };
        j--;
    }
}