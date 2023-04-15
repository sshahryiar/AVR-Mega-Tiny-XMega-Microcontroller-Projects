#include "io.h"
#include "clock.h"
#include "ST7735.c"
#include "BMP180.c"


const unsigned char symbol[][5] = {0x00, 0x0C, 0x12, 0x12, 0x0C};


void setup();
void clock_setup();
void GPIO_setup();
void draw_background();
float map(float value, float x_min, float x_max, float y_min, float y_max);
float constrain(float value, float value_min, float value_max);
void print_symbol(unsigned int x_pos, unsigned int y_pos, unsigned char font_size, unsigned int colour, unsigned int back_colour, char ch);


void main()
{
    unsigned char sample = 0;
    unsigned char tp = 0;
    unsigned char pp = 0;
    
    float T = 0.0;
    float P = 0.0;
    
    setup();
    draw_background();

    while(1)
    {
        T = read_uncompensated_temperature();
        T = get_temperature(T);
        P = read_uncompensated_pressure(OSS_value);
        P = get_pressure(P, OSS_value);
        P *= 0.001;
        
        print_str(1, 120, 1, Red, Black, "T/ C:");
        print_symbol(13, 120, 1, Red, Black, 0);
        print_F(36, 120, 1, Red, Black, T, 2);
        
        print_str(80, 120, 1, Green, Black, "P/kPa:");
        print_F(116, 120, 1, Green, Black, P, 2);

        tp = map(T, 0, 100, 10, 110);
        tp = constrain(tp, 10, 110);
        pp = map(P, 50, 150, 10, 110);
        pp = constrain(pp, 10, 110);
        
        Draw_V_Line((58 + sample), 10, 110, Black);
        
        Draw_Pixel((sample + 58), (120 - tp), Red);
        Draw_Pixel((sample + 58), (120 - pp), Green);
        sample++;
        
        if(sample > 99)
        {
           sample = 0;
        }
        
        PORTE_OUT.B2 ^= 1;
        delay_ms(400);
    };
}


void setup()
{
    clock_setup();
    GPIO_setup();
    BMP180_init();
    ST7735_init();
    Set_Rotation(0x03);
    TFT_fill(Swap_Colour(Black));
}


void clock_setup()
{
    OSC_CTRL |= OSC_RC32KEN_bm;
    while(!(OSC_STATUS & OSC_RC32KRDY_bm));
    OSC_CTRL |= OSC_RC32MEN_bm;
    CPU_CCP = CCP_IOREG_gc;
    CLK_PSCTRL = ((CLK_PSCTRL & (~(CLK_PSADIV_gm | CLK_PSBCDIV1_bm
                | CLK_PSBCDIV0_bm))) | CLK_PSADIV_1_gc | CLK_PSBCDIV_2_2_gc);
    OSC_DFLLCTRL = ((OSC_DFLLCTRL & (~(OSC_RC32MCREF_gm | OSC_RC2MCREF_bm))) |
                  OSC_RC32MCREF_RC32K_gc);
    DFLLRC32M_CTRL |= DFLL_ENABLE_bm;
    while(!(OSC_STATUS & OSC_RC32MRDY_bm));
    CPU_CCP = CCP_IOREG_gc;
    CLK_CTRL = ((CLK_CTRL & (~CLK_SCLKSEL_gm)) | CLK_SCLKSEL_RC32M_gc);
    OSC_CTRL &= (~(OSC_RC2MEN_bm | OSC_XOSCEN_bm | OSC_PLLEN_bm));
    PORTCFG_CLKEVOUT = 0x00;
}


void GPIO_setup()
{
    PORTA_OUT = 0x00;
    PORTA_DIR = 0x00;
    PORTCFG_MPCMASK = 0xFF;
    PORTA_PIN0CTRL = (PORT_OPC_TOTEM_gc | PORT_ISC_BOTHEDGES_gc);
    PORTA_INTCTRL = ((PORTA_INTCTRL & (~(PORT_INT1LVL_gm | PORT_INT0LVL_gm))) |
            PORT_INT1LVL_OFF_gc | PORT_INT0LVL_OFF_gc);
    PORTA_INT0MASK = 0x00;
    PORTA_INT1MASK = 0x00;

    PORTB_OUT = 0x00;
    PORTB_DIR = 0x00;
    PORTCFG_MPCMASK = 0x0F;
    PORTB_PIN0CTRL = (PORT_OPC_TOTEM_gc | PORT_ISC_BOTHEDGES_gc);
    PORTB_INTCTRL = ((PORTB_INTCTRL & (~(PORT_INT1LVL_gm | PORT_INT0LVL_gm))) |
            PORT_INT1LVL_OFF_gc | PORT_INT0LVL_OFF_gc);
    PORTB_INT0MASK = 0x00;
    PORTB_INT1MASK = 0x00;


    PORTC_OUT = 0x00;
    PORTC_DIR = 0xBE;
    PORTCFG_MPCMASK = 0xFF;
    PORTC_PIN0CTRL = (PORT_OPC_TOTEM_gc | PORT_ISC_BOTHEDGES_gc);
    PORTC_REMAP = ((0 << PORT_SPI_bp) | (0 << PORT_USART0_bp) | (0 << PORT_TC0D_bp) | (0 << PORT_TC0C_bp) | (0 << PORT_TC0B_bp) | (0 << PORT_TC0A_bp));
    PORTC_INTCTRL = ((PORTC_INTCTRL & (~(PORT_INT1LVL_gm | PORT_INT0LVL_gm))) |
            PORT_INT1LVL_OFF_gc | PORT_INT0LVL_OFF_gc);
    PORTC_INT0MASK = 0x00;
    PORTC_INT1MASK = 0x00;

    PORTD_OUT = 0x00;
    PORTD_DIR = 0x00;
    PORTCFG_MPCMASK = 0xFF;
    PORTD_PIN0CTRL = (PORT_OPC_PULLUP_gc | PORT_ISC_BOTHEDGES_gc);
    PORTD_INTCTRL = ((PORTD_INTCTRL & (~(PORT_INT1LVL_gm | PORT_INT0LVL_gm))) |
            PORT_INT1LVL_OFF_gc | PORT_INT0LVL_OFF_gc);
    PORTD_INT0MASK = 0x00;
    PORTD_INT1MASK = 0x00;

    PORTE_OUT = 0x0C;
    PORTE_DIR = 0x0C;
    PORTCFG_MPCMASK = 0x0F;
    PORTE_PIN0CTRL = (PORT_OPC_TOTEM_gc | PORT_ISC_BOTHEDGES_gc);
    PORTE_INTCTRL = ((PORTE_INTCTRL & (~(PORT_INT1LVL_gm | PORT_INT0LVL_gm))) |
            PORT_INT1LVL_OFF_gc | PORT_INT0LVL_OFF_gc);
    PORTE_INT0MASK = 0x00;
    PORTE_INT1MASK = 0x00;

    PORTR_OUT = 0x00;
    PORTR_DIR = 0x00;
    PORTCFG_MPCMASK = 0x03;
    PORTR_PIN0CTRL = (PORT_OPC_TOTEM_gc | PORT_ISC_BOTHEDGES_gc);
    PORTR_INTCTRL = ((PORTR_INTCTRL & (~(PORT_INT1LVL_gm | PORT_INT0LVL_gm))) |
            PORT_INT1LVL_OFF_gc | PORT_INT0LVL_OFF_gc);
    PORTR_INT0MASK = 0x00;
    PORTR_INT1MASK = 0x00;

    PORTCFG_VPCTRLA = (PORTCFG_VP13MAP_PORTB_gc | PORTCFG_VP02MAP_PORTA_gc);
    PORTCFG_VPCTRLB = (PORTCFG_VP13MAP_PORTD_gc | PORTCFG_VP02MAP_PORTC_gc);
}


void draw_background()
{
    unsigned char points = 0x00;

    print_str(60, 1, 1, Light_Blue, Black, "BMP180 + XMega");
    
    Draw_Rectangle(57, 9, 158, 111, NO, SQUARE, White, Black);
    
    Draw_V_Line(50, 110, 10, Red);
    Draw_V_Line(25, 110, 10, Green);
    
    for(points = 0; points <= 100; points += 10)
    {
        Draw_H_Line(23, 27, (10 + points), Green);
        Draw_H_Line(48, 52, (10 + points), Red);
    }
    
    for(points = 0; points <= 95; points += 10)
    {
        Draw_H_Line(24, 26, (15 + points), Green);
        Draw_H_Line(49, 51, (15 + points), Red);
    }
    
    print_str(0, 1, 1, Green, Black, "kPa");
    print_symbol(40, 1, 1, Red, Black, 0);
    print_str(46, 1, 1, Red, Black, "C");
    
    print_str(0, 10, 1, Green, Black, "150");
    print_str(31, 20, 1, Red, Black, "90");
    
    print_str(0, 60, 1, Green, Black, "100");
    print_str(31, 60, 1, Red, Black, "50");
    
    print_str(0, 106, 1, Green, Black, "50");
    print_str(31, 106, 1, Red, Black, "0");
}


float map(float value, float x_min, float x_max, float y_min, float y_max)
{
    return (y_min + (((y_max - y_min) / ((x_max - x_min)) * (value - x_min))));
}


float constrain(float value, float value_min, float value_max)
{
    if(value >= value_max)
    {
       return value_max;
    }
    else if(value <= value_min)
    {
       return value_min;
    }
    else
    {
       return value;
    }
}


void print_symbol(unsigned int x_pos, unsigned int y_pos, unsigned char font_size, unsigned int colour, unsigned int back_colour, char ch)
{
     unsigned char i = 0x00;
     unsigned char j = 0x00;
     unsigned char value = 0x00;

     if(font_size <= 0)
     {
         font_size = 1;
     }

     if(x_pos < font_size)
     {
         x_pos = font_size;
     }

     for(i = 0x00; i < 0x05; i++)
     {
         for(j = 0x00; j < 0x08; j++)
         {
             value = 0x0000;
             value = ((symbol[((unsigned char)ch)][i]));

             if(((value >> j) & 0x01) != 0x00)
             {
                 Draw_Font_Pixel(x_pos, y_pos, colour, font_size);
             }
             else
             {
                 Draw_Font_Pixel(x_pos, y_pos, back_colour, font_size);
             }

             y_pos += font_size;
          }

          y_pos -= (font_size << 0x03);
          x_pos += font_size;
      }
}