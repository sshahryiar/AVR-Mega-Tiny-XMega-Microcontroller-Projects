#include "MODBUS.h"


void UART1_Interrupt()
iv IVT_ADDR_USART_RXC
ics ICS_AUTO
{
    RX_buffer[cnt++] = UDR;
    RXC_bit = 0;
}


void flush_RX_buffer(void)
{
    signed char i = (RX_buffer_length - 1);

    while(i > -1)
    {
        RX_buffer[i--] = 0x00;
    };

    cnt = 0x00;
}


void flush_TX_buffer(void)
{
    signed char i = (TX_buffer_length - 1);

    while(i > -1)
    {
        TX_buffer[i--] = 0x00;
    };
}


unsigned int MODBUS_RTU_CRC16(unsigned char *data_input, unsigned char data_length)
{
    unsigned char n = 0x08;
    unsigned char s = 0x00;
    unsigned int CRC_word = 0xFFFF;

    for(s = 0x00; s < data_length; s++)
    {
        CRC_word ^= ((unsigned int)data_input[s]);

        n = 8;
        
        while(n > 0)
        {
            if((CRC_word & 0x0001) == 0)
            {
              CRC_word >>= 1;
            }

            else
            {
              CRC_word >>= 1;
              CRC_word ^= 0xA001;
            }

            n--;
      }
    }

    return CRC_word;
}


void MODBUS_receive_task(void)
{
     bit error_flag;

     unsigned char low_byte = 0x00;
     unsigned char high_byte = 0x00;

     unsigned int temp1 = 0x0000;
     unsigned int temp2 = 0x0000;
     unsigned int temp3 = 0x0000;
     unsigned int temp4 = 0x0000;
     unsigned int temp5 = 0x0000;
     unsigned int temp6 = 0x0000;
     unsigned int temp7 = 0x0000;

     static unsigned char data_array[0x08] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

     error_flag = 0;

     if(RX_buffer[id_byte] == own_ID)
     {
         switch(RX_buffer[function_code_byte])
         {
             case FC_read_coils:
             {
                 temp1 = make_word(RX_buffer[location_start_high_byte], RX_buffer[location_start_low_byte]);

                 if((temp1 >= addr_coil_start) && (temp1 <= addr_coil_end))
                 {
                     temp2 = make_word(RX_buffer[location_end_high_byte], RX_buffer[location_end_low_byte]);

                     if((temp2 <= no_of_coils) && (temp2 + temp1 - 1) <= addr_coil_end)
                     {
                         temp3 = make_word(RX_buffer[CRC_low_byte], RX_buffer[CRC_high_byte]);
                         temp4 = MODBUS_RTU_CRC16(RX_buffer, 6);

                         if(temp4 == temp3)
                         {
                             temp4 = 0x0000;
                             temp5 = ((temp1 - addr_coil_start) + temp2 - 1);

                             while(temp2)
                             {
                                 temp4 <<= 1;
                                 temp4 |= coils[temp5];
                                 temp5--;
                                 temp2--;
                             };

                             data_array[0] = 0x01;
                             data_array[1] = ((unsigned char)temp4);

                             MODBUS_send_task(FC_read_coils, 2, data_array);
                         }

                         else
                         {
                             error_flag = 1;
                         }
                     }

                     else
                     {
                         error_flag = 1;
                     }
                 }

                 else
                 {
                     error_flag = 1;
                 }

                 switch(error_flag)
                 {
                     case 1:
                     {
                       data_array[0] = 0x02;
                       MODBUS_send_task((FC_read_coils | 0x80), 1, data_array);
                       break;
                     }
                     default:
                     {
                       break;
                     }
                 }

                 break;
             }

             case FC_read_discrete_inputs:
             {
                 temp1 = make_word(RX_buffer[location_start_high_byte], RX_buffer[location_start_low_byte]);

                 if((temp1 >= addr_input_start) && (temp1 <= addr_input_end))
                 {
                     temp2 = make_word(RX_buffer[location_end_high_byte], RX_buffer[location_end_low_byte]);

                     if((temp2 <= no_of_inputs) && (temp2 + temp1 - 1) <= addr_input_end)
                     {
                         temp3 = make_word(RX_buffer[CRC_low_byte], RX_buffer[CRC_high_byte]);
                         temp4 = MODBUS_RTU_CRC16(RX_buffer, 6);

                         if(temp4 == temp3)
                         {
                             temp4 = 0x0000;
                             temp5 = ((temp1 - addr_input_start) + temp2 - 1);

                             while(temp2)
                             {
                                 temp4 <<= 1;
                                 temp4 |= discrete_inputs[temp5];
                                 temp5--;
                                 temp2--;
                             };

                             data_array[0] = 0x01;
                             data_array[1] = ((unsigned char)temp4);

                             MODBUS_send_task(FC_read_discrete_inputs, 2, data_array);
                          }

                          else
                          {
                              error_flag = 1;
                          }
                     }

                     else
                     {
                         error_flag = 1;
                     }
                 }

                 else
                 {
                     error_flag = 1;
                 }

                 switch(error_flag)
                 {
                     case 1:
                     {
                       data_array[0] = 0x02;
                       MODBUS_send_task((FC_read_discrete_inputs | 0x80), 1, data_array);
                       break;
                     }
                     default:
                     {
                       break;
                     }
                 }

                 break;
             }

             case FC_read_holding_registers:
             {
                 temp1 = make_word(RX_buffer[location_start_high_byte], RX_buffer[location_start_low_byte]);

                 if((temp1 >= addr_holding_reg_start) && (temp1 <= addr_holding_reg_end))
                 {
                     temp2 = make_word(RX_buffer[location_end_high_byte], RX_buffer[location_end_low_byte]);

                     if((temp2 <= no_of_holding_regs) && (temp2 + temp1 - 1) <= addr_holding_reg_end)
                     {
                         temp3 = make_word(RX_buffer[CRC_low_byte], RX_buffer[CRC_high_byte]);
                         temp4 = MODBUS_RTU_CRC16(RX_buffer, 6);

                         if(temp4 == temp3)
                         {
                             data_array[0] = temp2;
                             data_array[0] <<= 1;

                             if(temp2 > 1)
                             {

                                 for(temp3 = (temp1 - addr_holding_reg_start); temp3 < temp2; temp3++)
                                 {
                                     get_HB_LB(holding_registers[((temp1 - addr_holding_reg_start) + temp3)], &high_byte, &low_byte);
                                     data_array[1 + temp3 + temp3] = high_byte;
                                     data_array[2 + temp3 + temp3] = low_byte;
                                 }
                             }

                             else
                             {
                                     get_HB_LB(holding_registers[(temp1 - addr_holding_reg_start)], &high_byte, &low_byte);
                                     data_array[1] = high_byte;
                                     data_array[2] = low_byte;
                             }

                             MODBUS_send_task(FC_read_holding_registers, ((temp2 << 1) + 1), data_array);
                         }

                         else
                         {
                             error_flag = 1;
                         }
                     }

                     else
                     {
                         error_flag = 1;
                     }
                 }

                 else
                 {
                     error_flag = 1;
                 }

                 switch(error_flag)
                 {
                     case 1:
                     {
                       data_array[0] = 0x02;
                       MODBUS_send_task((FC_read_holding_registers | 0x80), 1, data_array);
                       break;
                     }
                     default:
                     {
                       break;
                     }
                 }

                 break;
             }

             case FC_read_input_registers:
             {
                 temp1 = make_word(RX_buffer[location_start_high_byte], RX_buffer[location_start_low_byte]);

                 if((temp1 >= addr_input_reg_start) && (temp1 <= addr_input_reg_end))
                 {
                     temp2 = make_word(RX_buffer[location_end_high_byte], RX_buffer[location_end_low_byte]);

                     if((temp2 <= no_of_input_regs) && (temp2 + temp1 - 1) <= addr_input_reg_end)
                     {
                         temp3 = make_word(RX_buffer[CRC_low_byte], RX_buffer[CRC_high_byte]);
                         temp4 = MODBUS_RTU_CRC16(RX_buffer, 6);

                         if(temp4 == temp3)
                         {
                             data_array[0] = temp2;
                             data_array[0] <<= 1;

                             if(temp2 > 1)
                             {

                                 for(temp3 = (temp1 - addr_input_reg_start); temp3 < temp2; temp3++)
                                 {
                                     get_HB_LB(input_registers[((temp1 - addr_input_reg_start) + temp3)], &high_byte, &low_byte);
                                     data_array[1 + temp3 + temp3] = high_byte;
                                     data_array[2 + temp3 + temp3] = low_byte;
                                 }
                             }

                             else
                             {
                                     get_HB_LB(input_registers[(temp1 - addr_input_reg_start)], &high_byte, &low_byte);
                                     data_array[1] = high_byte;
                                     data_array[2] = low_byte;
                             }

                             MODBUS_send_task(FC_read_input_registers, ((temp2 << 1) + 1), data_array);
                         }

                         else
                         {
                             error_flag = 1;
                         }
                     }

                     else
                     {
                         error_flag = 1;
                     }
                 }

                 else
                 {
                     error_flag = 1;
                 }

                 switch(error_flag)
                 {
                     case 1:
                     {
                       data_array[0] = 0x02;
                       MODBUS_send_task((FC_read_input_registers | 0x80), 1, data_array);
                       break;
                     }
                     default:
                     {
                       break;
                     }
                 }

                 break;
             }

             case FC_write_single_coil:
             {
                 temp2 = make_word(RX_buffer[location_start_high_byte], RX_buffer[location_start_low_byte]);

                 if((temp2 >= addr_coil_start) && (temp2 <= addr_coil_end))
                 {
                      temp1 = make_word(RX_buffer[CRC_low_byte], RX_buffer[CRC_high_byte]);
                      temp3 = MODBUS_RTU_CRC16(RX_buffer, 6);

                      if(temp1 == temp3)
                      {
                          temp1 = make_word(RX_buffer[location_end_high_byte], RX_buffer[location_end_low_byte]);

                          if(temp1 == coil_ON)
                          {
                              coils[temp2] = ON;
                          }

                          else if(temp1 == coil_OFF)
                          {
                              coils[temp2] = OFF;
                          }

                          data_array[0] = RX_buffer[location_start_high_byte];
                          data_array[1] = RX_buffer[location_start_low_byte];
                          data_array[2] = RX_buffer[location_end_high_byte];
                          data_array[3] = RX_buffer[location_end_low_byte];

                          MODBUS_send_task(FC_write_single_coil, 4 , data_array);
                      }

                      else
                      {
                          error_flag = 1;
                      }
                 }

                 else
                 {
                     error_flag = 1;
                 }

                 switch(error_flag)
                 {
                     case 1:
                     {
                       data_array[0] = 0x02;
                       MODBUS_send_task((FC_write_single_coil | 0x80), 1, data_array);
                       break;
                     }
                     default:
                     {
                       break;
                     }
                 }

                 break;
             }

             case FC_write_single_register:
             {
                 temp1 = make_word(RX_buffer[location_start_high_byte], RX_buffer[location_start_low_byte]);

                 if((temp1 >= addr_holding_reg_start) && (temp1 <= addr_holding_reg_end))
                 {
                     temp3 = make_word(RX_buffer[CRC_low_byte], RX_buffer[CRC_high_byte]);
                     temp4 = MODBUS_RTU_CRC16(RX_buffer, 6);

                     if(temp4 == temp3)
                     {
                         temp2 = make_word(RX_buffer[location_end_high_byte], RX_buffer[location_end_low_byte]);
                         holding_registers[temp1 - addr_holding_reg_start] = temp2;

                         data_array[0] = RX_buffer[location_start_high_byte];
                         data_array[1] = RX_buffer[location_start_low_byte];
                         data_array[2] = RX_buffer[location_end_high_byte];
                         data_array[3] = RX_buffer[location_end_low_byte];

                         MODBUS_send_task(FC_write_single_register, 4 , data_array);
                     }

                     else
                     {
                         error_flag = 1;
                     }
                 }

                 else
                 {
                     error_flag = 1;
                 }

                 switch(error_flag)
                 {
                     case 1:
                     {
                       data_array[0] = 0x02;
                       MODBUS_send_task((FC_write_single_register | 0x80), 1, data_array);
                       break;
                     }
                     default:
                     {
                       break;
                     }
                 }

                 break;
             }

             case FC_write_multiple_coils:
             {
                 temp1 = make_word(RX_buffer[location_start_high_byte], RX_buffer[location_start_low_byte]);

                 if((temp1 >= addr_coil_start) && (temp1 <= addr_coil_end))
                 {
                     temp2 = make_word(RX_buffer[location_end_high_byte], RX_buffer[location_end_low_byte]);
                     temp3 = (temp2 + temp1 - 1);

                     if((temp2 <= no_of_coils) && (temp3 <= addr_coil_end))
                     {
                         temp3 = RX_buffer[byte_size_byte];

                         if((temp2 > 0) && (temp2 <= 8))
                         {
                             temp4 = 1;
                         }
                         else if((temp2 > 8) && (temp2 <= 16))
                         {
                             temp4 = 2;
                         }

                         if(temp3 == temp4)
                         {
                             temp7 = (mandatory_bytes_to_read + temp4);

                             temp5 = make_word(RX_buffer[(1 + temp7)], RX_buffer[temp7]);
                             temp6 = MODBUS_RTU_CRC16(RX_buffer, temp7);

                             if(temp6 == temp5)
                             {
                                 if(temp3 == 1)
                                 {
                                     temp4 = RX_buffer[(temp7 - 1)];
                                     temp5 = (temp1 - addr_coil_start);

                                     if(temp2 > 1)
                                     {
                                         for(temp6 = temp5; temp6 < (temp2 + temp5); temp6++)
                                         {
                                             coils[temp6] = (temp4 & 0x01);
                                             temp4 >>= 1;
                                         }
                                     }

                                     else
                                     {
                                         coils[temp5] = temp4;
                                     }
                                 }

                                 else
                                 {
                                     temp4 = make_word(RX_buffer[(temp7 - 1)], RX_buffer[temp7]);

                                     for(temp6 = temp5; temp6 < (temp2 + temp5); temp6++)
                                     {
                                         coils[temp6] = (temp4 & 0x01);
                                         temp4 >>= 1;
                                     }
                                 }

                                 data_array[0] = RX_buffer[location_start_high_byte];
                                 data_array[1] = RX_buffer[location_start_low_byte];
                                 data_array[2] = RX_buffer[location_end_high_byte];
                                 data_array[3] = RX_buffer[location_end_low_byte];

                                 MODBUS_send_task(FC_write_multiple_coils, 4 , data_array);
                             }

                             else
                             {
                                 error_flag = 1;
                             }
                          }

                          else
                          {
                              error_flag = 1;
                          }
                     }

                     else
                     {
                         error_flag = 1;
                     }
                 }

                 else
                 {
                     error_flag = 1;
                 }

                 switch(error_flag)
                 {
                     case 1:
                     {
                       data_array[0] = 0x02;
                       MODBUS_send_task((FC_write_multiple_coils | 0x80), 1, data_array);
                       break;
                     }

                     default:
                     {
                       break;
                     }
                 }

                 break;
             }

             case FC_write_multiple_registers:
             {
                 temp1 = make_word(RX_buffer[location_start_high_byte], RX_buffer[location_start_low_byte]);

                 if((temp1 >= addr_holding_reg_start) && (temp1 <= addr_holding_reg_end))
                 {
                     temp2 = make_word(RX_buffer[location_end_high_byte], RX_buffer[location_end_low_byte]);
                     temp3 = (temp2 + temp1 - 1);

                     if((temp2 <= no_of_holding_regs) && (temp3 <= addr_holding_reg_end))
                     {
                         temp3 = RX_buffer[byte_size_byte];
                         temp4 = (temp2 << 1);

                         if(temp3 == temp4)
                         {
                             temp7 = (mandatory_bytes_to_read + temp3);

                             temp5 = make_word(RX_buffer[(1 + temp7)], RX_buffer[temp7]);
                             temp6 = MODBUS_RTU_CRC16(RX_buffer, temp7);

                             if(temp6 == temp5)
                             {
                                 temp5 = (temp1 - addr_holding_reg_start);
                                 temp3 = mandatory_bytes_to_read;

                                 if(temp2 == 1)
                                 {
                                     holding_registers[temp5] = make_word(RX_buffer[temp3], RX_buffer[(1 + temp3)]);
                                 }

                                 else
                                 {
                                     for(temp6 = temp5; temp6 < (temp2 + temp5); temp6++)
                                     {
                                         holding_registers[temp6] = make_word(RX_buffer[temp3], RX_buffer[(1 + temp3)]);
                                         temp3 += 2;
                                     }
                                 }

                                 data_array[0] = RX_buffer[location_start_high_byte];
                                 data_array[1] = RX_buffer[location_start_low_byte];
                                 data_array[2] = RX_buffer[location_end_high_byte];
                                 data_array[3] = RX_buffer[location_end_low_byte];

                                 MODBUS_send_task(FC_write_multiple_registers, 4 , data_array);
                             }

                             else
                             {
                                 error_flag = 1;
                             }
                          }

                          else
                          {
                              error_flag = 1;
                          }
                     }

                     else
                     {
                         error_flag = 1;
                     }
                 }

                 else
                 {
                     error_flag = 1;
                 }

                 switch(error_flag)
                 {
                     case 1:
                     {
                       data_array[0] = 0x02;
                       MODBUS_send_task((FC_write_multiple_registers | 0x80), 1, data_array);
                       break;
                     }

                     default:
                     {
                       break;
                     }
                 }

                 break;
             }
             
             default:
             {
                 break;
             }
         }
         
     }

     flush_RX_buffer();
}


void MODBUS_send_task(unsigned char function_code, unsigned char data_length, unsigned char *values)
{
     unsigned char hb = 0x00;
     unsigned char lb = 0x00;
     unsigned char byte_count = 0x00;

     flush_TX_buffer();

     TX_buffer[id_byte] = own_ID;
     TX_buffer[function_code_byte] = function_code;

     for(byte_count = 0; byte_count < data_length; byte_count++)
     {
         TX_buffer[2 + byte_count] = values[byte_count];
     }

     get_HB_LB(MODBUS_RTU_CRC16(TX_buffer, (data_length + 2)), &hb, &lb);

     TX_buffer[2 + data_length] = lb;
     TX_buffer[3 + data_length] = hb;

     DIR_TX;

     for(byte_count = 0; byte_count < (6 + data_length); byte_count++)
     {
         UART1_Write(TX_buffer[byte_count]);
     }

     DIR_RX;
}