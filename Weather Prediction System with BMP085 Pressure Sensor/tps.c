#include "BMP085.c"


#define SET                !PINB3_bit
#define INC                !PINB2_bit
#define DEC                !PINB1_bit
#define ESC                !PINB0_bit


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


const unsigned char symbol[0x08] = {0x00, 0x06, 0x09, 0x09, 0x06, 0x00, 0x00, 0x00};


void setup();
void print_symbol(unsigned char x_pos, unsigned char y_pos);
void lcd_print_int(unsigned char x_pos, unsigned char y_pos, signed long value);
void lcd_print_decimal(unsigned char x_pos, unsigned char y_pos, unsigned int value, unsigned char points);
void lcd_print_float(unsigned char x_pos, unsigned char y_pos, float value, unsigned char points);
unsigned char predict_weather(float p, float alt);
float get_altitude(float p);
float change_value(float value, float value_max, float value_min);


void main() 
{
    unsigned char wt = 0;
    
    float temperature = 0.0;
    float pressure = 0.0;
    float actual_altitude = 13.6;
    float measured_altitude = 0.0;
    
    setup();
    
    Lcd_Out(1, 3, "T./ C");
    Lcd_Out(1, 14, "P/kPa");
    Lcd_Out(3, 1, "Alt/m: A      C");
    Lcd_Out(4, 1, "Wthr.:");
    print_symbol(6, 1);
    
    while(1)
    {
        temperature = read_uncompensated_temperature();
        temperature = get_temperature(temperature);
        pressure = read_uncompensated_pressure(3);
        pressure = get_pressure(pressure, 3);
        measured_altitude = get_altitude(pressure);
        wt = predict_weather(pressure, actual_altitude);

        pressure /= 1000.0;
        
        lcd_print_float(2, 2, temperature, 2);
        lcd_print_float(12, 2, pressure, 2);
        lcd_print_float(9, 3, actual_altitude, 1);
        lcd_print_float(16, 3, measured_altitude, 1);
        
        switch(wt)
        {
            case clear:
            {
                Lcd_Out(4, 13, " Clear *");
                break;
            }
            
            case cloudy:
            {
                Lcd_Out(4, 13, "Cloudy @");
                break;
            }
            
            case rain:
            {
                Lcd_Out(4, 13, " Rain !!");
                break;
            }
        }
        
        actual_altitude = change_value(actual_altitude, 99.9, -9.9);
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
    DDRD = 0x70;
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
    UCSRB = 0x00;
    ACSR = 0x80;
    SFIOR = 0x00;
    ADCSRA = 0x00;
    SPCR = 0x00;
    
    TWI_Init(100000);
    
    Lcd_Init();
    Lcd_Cmd(_LCD_CLEAR);
    Lcd_Cmd(_LCD_CURSOR_OFF);
    
    BMP085_Calibration();
}


void print_symbol(unsigned char x_pos, unsigned char y_pos)
{
    unsigned char s = 0;
    
    Lcd_Cmd(64);
    
    for(s = 0; s < 8; s++)
    {
        Lcd_Chr_CP(symbol[s]);
    }
    
    Lcd_Cmd(_LCD_RETURN_HOME);
    Lcd_Chr(y_pos, x_pos, 0);
}


void lcd_print_int(unsigned char x_pos, unsigned char y_pos, signed long value)
{
    unsigned char ch = 0x00;

    if(value < 0)
    {
        Lcd_Chr(y_pos, x_pos, '-');
        value = -value;
    }
    else
    {
        Lcd_Chr(y_pos, x_pos, ' ');
    }

    if(value > 9999)
    {
        ch = (value / 10000);
        Lcd_Chr(y_pos, (x_pos + 1), (0x30 + ch));

        ch = ((value % 10000)/ 1000);
        Lcd_Chr(y_pos, (x_pos + 2), (0x30 + ch));

        ch = ((value % 1000) / 100);
        Lcd_Chr(y_pos, (x_pos + 3), (0x30 + ch));

        ch = ((value % 100) / 10);
        Lcd_Chr(y_pos, (x_pos + 4), (0x30 + ch));

        ch = (value % 10);
        Lcd_Chr(y_pos, (x_pos + 5), (0x30 + ch));
    }

    else if((value > 999) && (value <= 9999))
    {
        ch = ((value % 10000)/ 1000);
        Lcd_Chr(y_pos, (x_pos + 1), (0x30 + ch));

        ch = ((value % 1000) / 100);
        Lcd_Chr(y_pos, (x_pos + 2), (0x30 + ch));

        ch = ((value % 100) / 10);
        Lcd_Chr(y_pos, (x_pos + 3), (0x30 + ch));

        ch = (value % 10);
        Lcd_Chr(y_pos, (x_pos + 4), (0x30 + ch));
        Lcd_Chr(y_pos, (x_pos + 2), ' ');
    }
    else if((value > 99) && (value <= 999))
    {
        ch = ((value % 1000) / 100);
        Lcd_Chr(y_pos, (x_pos + 1), (0x30 + ch));

        ch = ((value % 100) / 10);
        Lcd_Chr(y_pos, (x_pos + 2), (0x30 + ch));

        ch = (value % 10);
        Lcd_Chr(y_pos, (x_pos + 3), (0x30 + ch));
        Lcd_Chr(y_pos, (x_pos + 4), ' ');
        Lcd_Chr(y_pos, (x_pos + 5), ' ');
    }
    else if((value > 9) && (value <= 99))
    {
        ch = ((value % 100) / 10);
        Lcd_Chr(y_pos, (x_pos + 1), (0x30 + ch));

        ch = (value % 10);
        Lcd_Chr(y_pos, (x_pos + 2), (0x30 + ch));

        Lcd_Chr(y_pos, (x_pos + 3), ' ');
        Lcd_Chr(y_pos, (x_pos + 4), ' ');
        Lcd_Chr(y_pos, (x_pos + 5), ' ');
    }
    else
    {
        ch = (value % 10);
        Lcd_Chr(y_pos, (x_pos + 1), (0x30 + ch));
        Lcd_Chr(y_pos, (x_pos + 2), ' ');
        Lcd_Chr(y_pos, (x_pos + 3), ' ');
        Lcd_Chr(y_pos, (x_pos + 4), ' ');
        Lcd_Chr(y_pos, (x_pos + 5), ' ');
    }
}


void lcd_print_decimal(unsigned char x_pos, unsigned char y_pos, unsigned int value, unsigned char points)
{
    unsigned char ch = 0x00;

    Lcd_chr(y_pos, x_pos, '.');

    ch = (value / 1000);
    Lcd_chr(y_pos, (x_pos + 1), (0x30 + ch));

    if(points > 1)
    {
        ch = ((value % 1000) / 100);
        Lcd_chr(y_pos, (x_pos + 2), (0x30 + ch));


        if(points > 2)
        {
            ch = ((value % 100) / 10);
            Lcd_chr(y_pos, (x_pos + 3), (0x30 + ch));

            if(points > 3)
            {
                ch = (value % 10);
                Lcd_chr(y_pos, (x_pos + 4), (0x30 + ch));
            }
        }
    }
}


void lcd_print_float(unsigned char x_pos, unsigned char y_pos, float value, unsigned char points)
{
    signed long tmp = 0x00;

    tmp = value;
    lcd_print_int(x_pos, y_pos, tmp);
    tmp = ((value - tmp) * 10000);

    if(tmp < 0)
    {
       tmp = -tmp;
    }

    if((value >= 10000) && (value < 100000))
    {
        lcd_print_decimal((x_pos + 6), y_pos, tmp, points);
    }
    else if((value >= 1000) && (value < 10000))
    {
        lcd_print_decimal((x_pos + 5), y_pos, tmp, points);
    }
    else if((value >= 100) && (value < 1000))
    {
        lcd_print_decimal((x_pos + 4), y_pos, tmp, points);
    }
    else if((value >= 10) && (value < 100))
    {
        lcd_print_decimal((x_pos + 3), y_pos, tmp, points);
    }
    else if(value < 10)
    {
        lcd_print_decimal((x_pos + 2), y_pos, tmp, points);
        if((value) < 0)
        {
            Lcd_Chr(y_pos, x_pos, '-');
        }
        else
        {
            Lcd_Chr(y_pos, x_pos, ' ');
        }
    }
}


unsigned char predict_weather(float p, float alt)
{
    float tp = 0;
    
    tp = (alt / const2);
    tp = (1.0 - tp);
    tp = pow(tp, const1);
    tp *= std_atm_pressure_at_sea_lvl;
    
    if((p - tp) > 250)
    {
          return clear;
    }
    
    else if(((p - tp) >= -250) && ((p - tp) <= 250))
    {
         return cloudy;
    }
    
    else if((p - tp) < -250)
    {
         return rain;
    }
}


float get_altitude(float p)
{
    float alt = 0.0;

    alt = (p / std_atm_pressure_at_sea_lvl);
    alt = pow(alt, const3);
    alt = (1.0 - alt);
    alt *= const2;

    return alt;
}


float change_value(float value, float value_max, float value_min)
{
    static bit settings;
    
    if(SET)
    {
        while(SET);
        settings = 1;
    }
    
    if(settings == 1)
    {
        if(INC)
        {
            value += 0.1;
        }
        
        if(value > value_max)
        {
            value = value_min;
        }
        
        if(DEC)
        {
            value -= 0.1;
        }

        if(value < value_min)
        {
            value = value_max;
        }
        
        if(ESC)
        {
            while(ESC);
            settings = 0;
        }
        
        
        delay_ms(40);
    }
    
    else
    {
        delay_ms(600);
    }
    
    return value;
}