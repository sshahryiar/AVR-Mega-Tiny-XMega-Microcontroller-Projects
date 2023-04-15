#define DHT_out_pin             PORTD2_bit
#define DHT_in_pin              PIND2_bit
#define DHT_pin_dir             DDD2_bit

#define input                   0
#define output                  1

#define low                     0
#define high                    1

#define timeout                 200
#define response_max            180
#define response_min            145
#define logic_high_max          140
#define logic_high_min          100
#define logic_low_max           95
#define logic_low_min           60
#define hold_time               18

#define number_of_pulses        42

#define no_error                -117
#define CRC_error               -118
#define sync_error              -119
#define sensor_error            -120


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


const unsigned char symbol[0x08] = {0x00, 0x06, 0x09, 0x09, 0x06, 0x00, 0x00, 0x00};

unsigned char times[number_of_pulses];

unsigned char frame = 0x00;

bit received;

void setup();
void load_symbol(unsigned char pos_row, unsigned char pos_char);
void request_data();
void clear_frames();
signed char get_data(signed char *p1, signed char *p2);
signed char decode_data(unsigned char start_pos, unsigned char end_pos);
signed char calculate_dew_point(float p1, float p2);


void get_pulse() 
iv IVT_ADDR_INT0 
ics ICS_AUTO 
{
    times[frame] = TCNT0;
    frame++;
    
    if(TCNT0 >= timeout)
    {
        frame = number_of_pulses;
    }

    if(frame >= number_of_pulses)
    {
        DHT_pin_dir = input;
        GICR = 0x00;
        MCUCR = 0x00;
        TCCR0 = 0x00;
        GIFR = 0x00;
        SREG_I_bit = 0;
        received = 1;
    }
    
    TCNT0 = 0x00;
}


void main() 
{
    unsigned char txt[0x06];
    
    signed char T = 0x00;
    signed char RH = 0x00;
    signed char DP = 0x00;
    signed char error_code = 0x00;

    setup();

    lcd_out(1, 1, "R.H/%:");
    lcd_out(2, 1, "T./ C:");
    lcd_out(3, 1, "DP/ C:");
    load_symbol(2, 4);
    load_symbol(3, 4);

    while(1)
    {
        request_data();
        if(received)
        {
            delay_ms(400);

            error_code = get_data(&RH, &T);

            if(error_code == no_error)
            {
                DP = calculate_dew_point(RH, T);

                ShortToStr(RH, txt);
                lcd_out(1, 17, txt);
                ShortToStr(T, txt);
                lcd_out(2, 17, txt);
                ShortToStr(DP, txt);
                lcd_out(3, 17, txt);
                
                lcd_out(4, 1, "No Error      ");
            }

            else
            {
                lcd_out(1, 19, "--");
                lcd_out(2, 19, "--");
                lcd_out(3, 19, "--");
                
                if(error_code == CRC_error)
                {
                    lcd_out(4, 1, "CRC Error   ");
                }

                else if(error_code == sync_error)
                {
                    lcd_out(4, 1, "SYNC Error  ");
                }

                else if(error_code == sensor_error)
                {
                    lcd_out(4, 1, "Sensor Error");
                }
            }
            received = 0;
         }
         
         delay_ms(600);
    };
}


void setup()
{
    clear_frames();
    received = 0;
    PORTA = 0x00;
    DDRA = 0x00;
    PORTB = 0x00;
    DDRB = 0x00;
    PORTC = 0x00;
    DDRC = 0x00;
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
    SREG_I_bit = 0;
    
    Lcd_Init();
    Lcd_Cmd(_LCD_CLEAR);
    Lcd_Cmd(_LCD_CURSOR_OFF);
}


void load_symbol(unsigned char pos_row, unsigned char pos_char)
{
    unsigned char s = 0x00;
    
    Lcd_Cmd(0x40);
    
    for (s = 0x00; s < 0x08; s++)
    {
        Lcd_Chr_CP(symbol[s]);
    }
    
    Lcd_Cmd(_LCD_RETURN_HOME);
    Lcd_Chr(pos_row, pos_char, 0);
}


void request_data()
{
    frame = 0x00;
    clear_frames();
    DHT_pin_dir = output;
    DHT_out_pin = low;
    delay_ms(hold_time);
    DHT_out_pin = high;
    DHT_pin_dir = input;
    TCCR0 = 0x02;
    GICR = 0x40;
    MCUCR = 0x02;
    GIFR = 0x40;
    TCNT0 = 0x00;
    SREG_I_bit = 1;
    
    if(TCNT0 >= timeout)
    {
        frame = number_of_pulses;
    }
}


void clear_frames()
{
    unsigned char i = 0x00;
    
    for(i = 0x00; i < number_of_pulses; i++)
    {
        times[i] = 0x00;
    }
}


signed char get_data(signed char *p1, signed char *p2)
{
    signed char tmp1 = 0x00;
    signed char tmp2 = 0x00;
    signed int CRC = 0x00;
    signed int temp = 0x00;
    
    frame = 0;
    
    if(((times[1]) >= response_min) && ((times[1]) <= response_max))
    {
        tmp1 = decode_data(2, 9);
        tmp2 = decode_data(10, 17);
        temp = (tmp1 + tmp2);
        CRC = temp;
        
        if(temp == sync_error)
        {
            return sync_error;
        }
        else
        {
            *p1 = tmp1;
        }
        
        tmp2 = decode_data(18, 25);
        tmp1 = decode_data(26, 33);
        temp = (tmp1 + tmp2);
        CRC += temp;

        if(temp == sync_error)
        {
            return sync_error;
        }
        else
        {
            *p2 = tmp2;
        }

        tmp1 = decode_data(34, 41);

        if((CRC & 0x00FF) == tmp1)
        {
            return no_error;
        }
        else
        {
            return CRC_error;
        }
    }
    else
    {
        return sensor_error;
    }
}


signed char decode_data(unsigned char start_pos, unsigned char end_pos)
{
    unsigned char i = 0x00;
    signed char tmp = 0x00;
    
    for(i = start_pos; i <= end_pos; i++)
    {
        tmp <<= 1;
        
        if((times[i] >= logic_high_min) && (times[i] <= logic_high_max))
        {
            tmp |= 1;
        }
        else if((times[i] >= logic_low_min) && (times[i] <= logic_low_max))
        {
            ;
        }
        else
        {
            return sync_error;
        }
    }
    
    return tmp;
}


signed char calculate_dew_point(float p1, float p2)
{
    float dew_point = 0.0;

    dew_point = ((log(p1 / 100.0)) + ((17.62 * p2) / (243.12 + p2)));
    dew_point = ((243.12 * dew_point) / (17.62 - dew_point));
    
    return ((signed char)dew_point);
}