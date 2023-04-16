#include "AiP650.h"


static const unsigned char segment_code[12] =
{
	0x3F,	//0
	0x06,	//1
	0x5B,	//2
	0x4F,	//3
	0x66,	//4
	0x6D,	//5
	0x7D,	//6
	0x07,	//7
	0x7F,	//8
	0x6F,	//9
	0x40,   //-
	0x00    // Blank
};


void AiP650_GPIO_init(void)
{
    SDA_DDR = HIGH;
    SCK_DDR = HIGH;
    delay_ms(40);
    SDA_pin = HIGH;
    SCK_pin = HIGH;
}


void AiP650_init(void)
{
    AiP650_GPIO_init();
    
    AiP650_start();
    AiP650_write(AiP650_CMD_MODE);
    AiP650_write((0 << 4) | (0x00) | 0x01);
    AiP650_stop();
    AiP650_clear_display();
}


void AiP650_start(void)
{
    SDA_pin = HIGH;
    SCK_pin = HIGH;
    delay_us(bit_delay);
    SDA_pin = LOW;
    SCK_pin = LOW;
    delay_us(bit_delay);
}


void AiP650_stop(void)
{
    SCK_pin = LOW;
    SDA_pin = LOW;
    delay_us(bit_delay);
    SCK_pin = HIGH;
    SDA_pin = HIGH;
    delay_us(bit_delay);
}


void AiP650_write(unsigned char value)
{
     signed char i = 0x08;

     while(i > 0)
     {
         SCK_pin = LOW;
         delay_us(bit_delay);
         
         if((value & 0x80) != 0x00)
         {
             SDA_pin = HIGH;
         }
         else
         {
             SDA_pin = LOW;
         }
         
         value <<= 1;
         
         SCK_pin = HIGH;
         delay_us(bit_delay);

         i--;
     };
     
     delay_us(10);
     SCK_pin = LOW;
     SDA_DDR = LOW;
     delay_us(bit_delay);
     SCK_pin = HIGH;
     delay_us(bit_delay);
     
     if(SDA_in == LOW)
     {
         SDA_pin = LOW;
     }
     
     SDA_DDR = HIGH;
}


void AiP650_send(unsigned char address, unsigned char value)
{
    AiP650_start();
    AiP650_write((AiP650_CMD_ADDRESS | (address << 1)));
    AiP650_write(value);
    AiP650_stop();
}


void AiP650_clear_display(void)
{
    signed char i = AiP650_NUM_of_DIGITS;
    
    while(i > -1)
    {
        i--;
        AiP650_send(i, segment_code[11]);
    };
}


void AiP650_print_int(signed int value)
{
    unsigned char sign = 0x00;
    
    if((value > -1000) && (value < 1000))
    {
        if(value < 0)
        {
            value = -value;
            sign = 0x0A;
        }
        else
        {
            sign = 0x0B;
        }

        if((value >= 0) && (value < 10))
        {
             AiP650_send(0, 0);
             AiP650_send(1, 0);
             AiP650_send(2, segment_code[sign]);
             AiP650_send(3, segment_code[(value % 10)]);
        }

        else if((value >= 10) && (value < 100))
        {
             AiP650_send(0, 0);
             AiP650_send(1, segment_code[sign]);
             AiP650_send(2, segment_code[(value / 10)]);
             AiP650_send(3, segment_code[(value % 10)]);
        }

        else
        {
             AiP650_send(0, segment_code[sign]);
             AiP650_send(1, segment_code[(value / 100)]);
             AiP650_send(2, segment_code[((value / 10) % 10)]);
             AiP650_send(3, segment_code[(value % 10)]);
        }
     }
     else
     {
         AiP650_send(0, segment_code[0x0A]);
         AiP650_send(1, segment_code[0x0A]);
         AiP650_send(2, segment_code[0x0A]);
         AiP650_send(3, segment_code[0x0A]);
     }
}


void AiP650_print_float(float f_value)
{
    unsigned char sign = 0x00;
    signed int value = 0x0000;

    if((f_value > -100.0) && (f_value < 100.0))
    {
        if(f_value < 0)
        {
            f_value = -f_value;
            sign = 0x0A;
        }
        else
        {
            sign = 0x0B;
        }
        
        value = ((int)(f_value * 10));

        if((value >= 0) && (value < 10))
        {
             AiP650_send(0, 0);
             AiP650_send(1, segment_code[sign]);
             AiP650_send(2, (segment_code[0x00] | 0x80));
             AiP650_send(3, segment_code[(value % 10)]);
        }

        else if((value >= 10) && (value < 100))
        {
             AiP650_send(0, 0);
             AiP650_send(1, segment_code[sign]);
             AiP650_send(2, (segment_code[(value / 10)] | 0x80));
             AiP650_send(3, segment_code[(value % 10)]);
        }

        else
        {
             AiP650_send(0, segment_code[sign]);
             AiP650_send(1, segment_code[(value / 100)]);
             AiP650_send(2, (segment_code[((value / 10) % 10)] | 0x80));
             AiP650_send(3, segment_code[(value % 10)]);
        }
     }
     else
     {
         AiP650_send(0, segment_code[0x0A]);
         AiP650_send(1, segment_code[0x0A]);
         AiP650_send(2, segment_code[0x0A]);
         AiP650_send(3, segment_code[0x0A]);
     }
}