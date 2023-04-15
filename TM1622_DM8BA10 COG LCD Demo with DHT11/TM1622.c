#include "TM1622.h"
#include "tables.h"


void TM162x_init(void)
{
      TM1622_CS_PIN_DIR_OUT;
      TM1622_WR_PIN_DIR_OUT;
      TM1622_DAT_PIN_DIR_OUT;
      delay_ms(100);

      TM162x_write_command(TM1622_CMD_SYS_EN);
      TM162x_write_command(TM1622_CMD_RC_32K);
      TM162x_write_command(TM1622_CMD_LCD_OFF);
      TM162x_all_elements_state(RESET);
      TM162x_write_command(TM1622_CMD_LCD_ON);
      delay_ms(100);

      TM162x_all_segments_state(SET);
      delay_ms(200);
      TM162x_all_segments_state(RESET);
}


void TM162x_all_elements_state(unsigned char state)
{
      unsigned char i = 0;

      for(i = 0; i < TM1622_ADDRS; i++)
      {
          switch(state)
          {
              case SET:
              {
                  TM162x_write_data(i, 0x0F, 4);
                  break;
              }

              default:
              {
                  TM162x_write_data(i, 0x00, 4);
                  break;
              }
          }
      }
}


void TM162x_all_segments_state(unsigned char state)
{
      unsigned char i = 0;

      for(i = 0; i < TM1622_no_of_digits; i++)
      {
          switch(state)
          {
              case SET:
              {
                  TM162x_write_data(digit_address[i], 0xFFFF, 16);
                  break;
              }

              default:
              {
                  TM162x_write_data(digit_address[i], 0x0000, 16);
                  break;
              }
          }
      }
}


void TM162x_write_bits(unsigned int value, unsigned char no_of_bits, unsigned char format)
{
      signed char i = no_of_bits;
      unsigned int mask = 0;

      if(format == LSB_FORMAT)
      {
          mask = 1;
      }
      else
      {
          mask = (1 << (no_of_bits - 1));
      }

      while(i > 0)
      {
          delay_us(4);
          TM1622_WR_PIN_LOW;

          if((value & mask) != 0)
          {
              TM1622_DAT_PIN_HIGH;
          }
          else
          {
              TM1622_DAT_PIN_LOW;
          }

          delay_us(4);
          TM1622_WR_PIN_HIGH;
          delay_us(4);
          
          if(format == LSB_FORMAT)
          {
              value >>= 1;
          }
          else
          {
              value <<= 1;
          }

          i--;
      }
}


void TM162x_write_command(unsigned char value)
{
     TM1622_CS_PIN_LOW;
     TM162x_write_bits(TM1622_COMMAND_OP_ID, 3, MSB_FORMAT);
     TM162x_write_bits(value, 8, MSB_FORMAT);
     TM162x_write_bits(1, 1, MSB_FORMAT);
     TM1622_CS_PIN_HIGH;
}


void TM162x_write_data(unsigned char address, unsigned int value, unsigned char no_of_bits)
{
     signed int i = ((no_of_bits >> 2) - 1);
     unsigned int nib = 0x0000;

     TM1622_CS_PIN_LOW;

     TM162x_write_bits(TM1622_WRITE_OP_ID, 3, MSB_FORMAT);
     TM162x_write_bits(address, 6, MSB_FORMAT);

     while(i >= 0)
     {
        nib = ((value & (0x0F) << (i << 2)) >> (i << 2));
        TM162x_write_bits(nib, 4, LSB_FORMAT);

        i--;
     }

     TM1622_CS_PIN_HIGH;
}


void TM1622_write_char(unsigned char pos, char ch)
{
    TM162x_write_data(digit_address[((TM1622_no_of_digits - 1) - pos)], font[(ch - 0x20)], 16);
}


void TM1622_write_str(unsigned char pos, char *ch)
{
    while((*ch != '\r') && (pos <= 9))
    {
       TM1622_write_char(pos++, *ch++);
    };
}


void TM1622_print_custom_char(unsigned char pos, unsigned char char_index)
{
    TM162x_write_data(digit_address[((TM1622_no_of_digits - 1) - pos)], custom_char[char_index], 16);
}


void TM1622_clear_display(void)
{
    signed char i = (TM1622_no_of_digits - 1);

    while(i > -1)
    {
        TM1622_write_char(i, ' ');
        i--;
    };
    delay_ms(20);
}