#include "SHT1x.c"
#include "BMP085.c"
#include "SSD1306.c"
#include "other_interfaces.c"


void setup();
void static_displays();
void send_header();
void send_data(float value, unsigned char length);


void main()
{
    unsigned int L = 0;
    
    float P = 0.0;
    float T = 0.0;
    float W = 0.0;
    float BV = 0.0;
    float RH = 0.0;
    float DP = 0.0;

    setup();
    static_displays();
    BMP085_Calibration();

    while(1)
    {
        status_LED = 1;
        
        TWI_Close();
        Read_SHT1x(&T, &RH);
        BV = get_bv();
        W = get_wind_speed();
        L = get_lux();
        
        TWI_Init(100000);
        P = BMP085_get_pressure_in_kPa();
        T += BMP085_get_temp();
        T /= 2.0;
        DP = SHT1x_get_dew_point(T, RH);

        OLED_print_float(86, 1, BV, 2);
        OLED_print_float(80, 2, T, 2);
        OLED_print_float(80, 3, RH, 2);
        OLED_print_float(80, 4, DP, 2);
        OLED_print_float(80, 5, P, 1);
        OLED_print_float(80, 6, W, 2);
        OLED_print_int(80, 7, L);
        delay_ms(300);
        
        send_header();
        
        send_data(BV, 4);
        send_data(W, 4);
        send_data(L, 4);
        send_data(P, 6);
        send_data(T, 4);
        send_data(DP, 4);
        send_data(RH, 4);
        
        status_LED = 0;
        delay_ms(300);
    };
}


void setup()
{
     CLKPR = 0x80;
     CLKPR = 0x00;
     PORTB = 0x00;
     DDRB = 0x00;
     PORTC = 0x00;
     DDRC = 0x00;
     PORTD = 0x00;
     DDRD = 0x00;
     TCCR0A = 0x00;
     TCCR0B = 0x00;
     TCNT0 = 0x00;
     OCR0A = 0x00;
     OCR0B = 0x00;
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
     TCCR2A = 0x00;
     TCCR2B = 0x00;
     TCNT2 = 0x00;
     OCR2A = 0x00;
     OCR2B = 0x00;
     EICRA = 0x00;
     EIMSK = 0x00;
     PCICR = 0x00;
     TIMSK0 = 0x00;
     TIMSK1 = 0x00;
     TIMSK2 = 0x00;
     UCSR0B = 0x00;
     ACSR = 0x80;
     ADCSRB = 0x00;
     DIDR1 = 0x00;
     DIDR0 = 0x00;
     ADMUX = 0x40;;
     ADCSRA = 0xA3;
     ADCSRB&=0xF8;
     SPCR = 0x00;
     TWCR = 0x00;

     OLED_init();
     BMP085_init();
     SHT1x_init();
     other_interfaces_init();
}


void static_displays()
{
    OLED_print_string(4, 0, "AVR Weather Station");
    OLED_print_string(6, 1, "BV/V :");
    OLED_print_string(6, 2, "T/'C :");
    OLED_print_string(6, 3, "RH/% :");
    OLED_print_string(6, 4, "DP/'C:");
    OLED_print_string(6, 5, "P/kPA:");
    OLED_print_string(6, 6, "W/m/s:");
    OLED_print_string(6, 7, "L/lux:");
}


void send_header()
{
     UART_Write_Text("S\r\n");
}


void send_data(float value, unsigned char length)
{
     unsigned char txt[12];
     unsigned char buffer[12];

     memset(txt, 0x00, sizeof(txt));
     memset(buffer, 0x00, sizeof(buffer));
     
     sprintf(buffer, "%1f", value);
     strncpy(txt, buffer, length);
     UART_Write_Text(txt);
     UART_Write_Text("\r\n");
}