#include "lcd.c"
#include "lcd_print.c"
#include "MAX31855.c"


void setup(void);


void main(void)
{
    float t_in = 0.0;
    float t_out = 0.0;
    unsigned char fault_msg = 0x00;
    
    setup();
    
    LCD_goto(0, 0);
    LCD_putstr("Tj/ C:");
    print_symbol(3, 0, 0);
    
    LCD_goto(0, 1);
    LCD_putstr("Ta/ C:");
    print_symbol(3, 1, 0);
    
    while(1)
    {
        fault_msg = MAX31855_get_data(&t_out, &t_in);

        switch(fault_msg)
        {
          case thermocouple_not_detected:
          {
            LCD_goto(0, 3);
            LCD_putstr("   Check Sensor!    ");
            break;
          }

        case thermocouple_short_circuited_to_GND:
        {
        LCD_goto(0, 3);
        LCD_putstr("   Check Jn-GND!    ");
        break;
        }

        case thermocouple_short_circuited_to_VCC:
        {
        LCD_goto(0, 3);
        LCD_putstr("   Check Jn-VCC!    ");
        break;
        }

        default:
        {
        print_F(11, 1, t_out, 2);
        print_F(11, 2, t_in, 2);
        LCD_goto(0, 3);
        LCD_putstr("    System Okay.    ");
        break;
        }
        };

        delay_ms(400);
    };
}


void setup(void)
{
    LCD_init();
    LCD_clear_home();
    load_custom_symbol();
    MAX31855_init();
}