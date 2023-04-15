#include "MCP2515.h"


void MCP2515_init(void)
{
    DDRB |= 0x2C;
    
    PORTD |= 0x04;
    DDRD |= 0x08;
    
    SPI1_Init_Advanced(_SPI_MASTER, _SPI_FCY_DIV4, _SPI_CLK_HI_TRAILING);
    delay_ms(10);
    
    MCP2515_reset();
    delay_us(10);
    
    MCP2515_write_register(CNF3, R_CNF3_125kbps);
    MCP2515_write_register(CNF2, R_CNF2_125kbps);
    MCP2515_write_register(CNF1, R_CNF1_125kbps);

    MCP2515_write_register(CANINTE, (bit_mask(RX1IE) | bit_mask(RX0IE)));
    
    MCP2515_write_register(RXB0CTRL, (bit_mask(RXM1) | bit_mask(RXM0)));
    MCP2515_write_register(RXB1CTRL, (bit_mask(RXM1) | bit_mask(RXM0)));

    MCP2515_write_register(BFPCTRL, 0);
    MCP2515_write_register(TXRTSCTRL, 0);
    
    MCP2515_set_mask(0, 0x00000000, CAN_STANDARD_FRAME);
    MCP2515_set_mask(1, 0x00000000, CAN_STANDARD_FRAME);
    
    MCP2515_set_filter(0, 0x00000000, CAN_STANDARD_FRAME);
    MCP2515_set_filter(1, 0x00000000, CAN_STANDARD_FRAME);
    MCP2515_set_filter(2, 0x00000000, CAN_STANDARD_FRAME);
    MCP2515_set_filter(3, 0x00000000, CAN_STANDARD_FRAME);
    MCP2515_set_filter(4, 0x00000000, CAN_STANDARD_FRAME);
    MCP2515_set_filter(5, 0x00000000, CAN_STANDARD_FRAME);
    
    MCP2515_flush_buffers();

    MCP2515_bit_modify(CANCTRL, 0xE0, 0x00);
}


void MCP2515_reset(void)
{
    MCP2515_CS_LOW();        
    SPI1_Write(SPI_RESET);        
    MCP2515_CS_HIGH();
}


void MCP2515_write_register(unsigned char address, unsigned char value)
{
    MCP2515_CS_LOW();        
    SPI1_Write(SPI_WRITE);
    SPI1_Write(address);
    SPI1_Write(value);        
    MCP2515_CS_HIGH();
}


unsigned char MCP2515_read_register(unsigned char address)
{
    unsigned char value = 0x00;

    MCP2515_CS_LOW();
    SPI1_Write(SPI_READ);
    SPI1_Write(address);
    value = SPI1_Read(0xFF);        
    MCP2515_CS_HIGH();

    return value;
}


void MCP2515_bit_modify(unsigned char address, unsigned char bitmask, unsigned char value)
{
    MCP2515_CS_LOW();        
    SPI1_Write(SPI_BIT_MODIFY);
    SPI1_Write(address);
    SPI1_Write(bitmask);
    SPI1_Write(value);        
    MCP2515_CS_HIGH();
}


unsigned char MCP2515_read_status(unsigned char type)
{
    unsigned char value = 0x00;

    MCP2515_CS_LOW();
    SPI1_Write(type);
    value = SPI1_Read(0xFF);        
    MCP2515_CS_HIGH();

    return value;
}


unsigned char MSP2515_check_free_buffer(void)
{
    unsigned char status = 0x00;

    status = MCP2515_read_status(SPI_READ_STATUS);

    if(test_if_all_bits_set(status, 0x54) == 0x54)
    {
        return FALSE;
    }

    return TRUE;
}


unsigned char MCP2515_check_for_incoming_message(void) 
{
    return (!MCP2515_INT());
}



unsigned char MCP2515_message_TX(void)
{
    unsigned char i = 0x00;
    unsigned char status = 0x00;
    unsigned char address = 0x00;
    unsigned char TXBnDLC = 0x00;
    unsigned char TXBnSIDH = 0x00;
    unsigned char TXBnSIDL = 0x00;
    unsigned char TXBnEID8 = 0x00;
    unsigned char TXBnEID0 = 0x00;

    TXBnDLC = (CAN_TX_msg.length & length_bit_fields);

    status = MCP2515_read_status(SPI_READ_STATUS);

    if(test_if_bit_cleared(status, 2))
    {
        address = 0x00;
    }
    else if(test_if_bit_cleared(status, 4))
    {
        address = 0x02;
    }
    else if(test_if_bit_cleared(status, 6))
    {
        address = 0x04;
    }
    else
    {
        return 0;
    }
    
    switch(CAN_TX_msg.ext_id)
    {
        case CAN_EXTENDED_FRAME:
        {
            TXBnSIDH = (CAN_TX_msg.id >> 21);
            TXBnSIDL = ((CAN_TX_msg.id >> 13) & SIDL_SID);
            TXBnSIDL |= ((CAN_TX_msg.id >> 16) & SIDL_EID);
            TXBnEID8 = (CAN_TX_msg.id >> 8);
            TXBnEID0 = CAN_TX_msg.id;
            
            bit_set(TXBnSIDL, IDE);
            
            if(CAN_TX_msg.rtr)
            {
                bit_set(TXBnDLC, RTR);
            }
            
            break;
        }

        default:
        {
            TXBnSIDH = (CAN_TX_msg.id >> 3);
            TXBnSIDL = ((CAN_TX_msg.id << 5) & SIDL_SID);
            TXBnEID8 = 0x00;
            TXBnEID0 = 0x00;
            
            if(CAN_TX_msg.rtr)
            {
                bit_set(TXBnSIDL, SRR);
            }
            
            break;
        }
    }

    MCP2515_CS_LOW();
    SPI1_Write(SPI_WRITE_TX | address);
    
    SPI1_Write(TXBnSIDH);
    SPI1_Write(TXBnSIDL);
    SPI1_Write(TXBnEID8);
    SPI1_Write(TXBnEID0);
    SPI1_Write(TXBnDLC);

    for(i = 0; i < TXBnDLC; i++)
    {
        SPI1_Write(CAN_TX_msg.data_byte[i]);
    }

    MCP2515_CS_HIGH();

    delay_us(10);

    MCP2515_CS_LOW();

    if(address == 0)
    {
        address = 1;
    }

    SPI1_Write(SPI_RTS | address);
    MCP2515_CS_HIGH();

    return address;
}


unsigned char MCP2515_message_RX(void)
{
    unsigned char i = 0x00;
    unsigned char status = 0x00;
    unsigned char address = 0x00;
    unsigned char RXBnDLC = 0x00;
    unsigned char RXBnSIDH = 0x00;
    unsigned char RXBnSIDL = 0x00;
    unsigned char RXBnEID8 = 0x00;
    unsigned char RXBnEID0 = 0x00;

    unsigned long temp = 0;

    status = MCP2515_read_status(SPI_RX_STATUS);

    if(test_if_bit_set(status, 6))
    {
        address = SPI_READ_RX;
    }
    else if(test_if_bit_set(status, 7))
    {
        address = (SPI_READ_RX | 0x04);
    }
    else
    {
        return 0;
    }

    MCP2515_CS_LOW();
    SPI1_Write(address);
    
    RXBnSIDH = SPI1_Read(0xFF);
    RXBnSIDL = SPI1_Read(0xFF);
    RXBnEID8 = SPI1_Read(0xFF);
    RXBnEID0 = SPI1_Read(0xFF);
    RXBnDLC = SPI1_Read(0xFF);
    
    CAN_RX_msg.length = (RXBnDLC & length_bit_fields);
    
    for(i = 0; i < CAN_RX_msg.length; i++)
    {
        CAN_RX_msg.data_byte[i] = SPI1_Read(0xFF);
    }

    MCP2515_CS_HIGH();

    CAN_RX_msg.ext_id = get_bit(RXBnSIDL, EXIDE);
    
    switch(CAN_RX_msg.ext_id)
    {
        case CAN_EXTENDED_FRAME:
        {
            temp = ((unsigned long)RXBnSIDH);
            temp <<= 21;
            CAN_RX_msg.id = temp;
            
            temp = ((unsigned long)(RXBnSIDL & SIDL_SID));
            temp <<= 13;
            CAN_RX_msg.id |= temp;
            
            temp = ((unsigned long)(RXBnSIDL & SIDL_EID));
            temp <<= 16;
            CAN_RX_msg.id |= temp;
            
            temp = ((unsigned long)RXBnEID8);
            temp <<= 8;
            CAN_RX_msg.id |= temp;
            
            temp = ((unsigned long)RXBnEID0);
            CAN_RX_msg.id |= temp;
            
            CAN_RX_msg.rtr = get_bit(RXBnDLC, RTR);
            
            break;
        }

        default:
        {
            temp = ((unsigned long)RXBnSIDH);
            CAN_RX_msg.id = (temp << 3);
            
            temp = ((unsigned long)RXBnSIDL);
            temp &= SIDL_SID;
            CAN_RX_msg.id |= (temp >> 5);
            
            CAN_RX_msg.rtr = get_bit(RXBnSIDL, SRR);
            
            break;
        }
    }

    if(test_if_bit_set(status, 6))
    {
        MCP2515_bit_modify(CANINTF, bit_mask(RX0IF), 0);
    }
    else
    {
        MCP2515_bit_modify(CANINTF, bit_mask(RX1IF), 0);
    }
    
    return (1 + (get_reg(status, 0x07)));
}


void MCP2515_clear_RX_buffers(void)
{
    unsigned char i = 0;

    MCP2515_CS_LOW();
    SPI1_Write(SPI_WRITE);
    SPI1_Write(RXB0SIDH);

    for(i = 0; i < 13; i++)
    {
        SPI1_Write(0x00);
    }

    MCP2515_CS_HIGH();
    
    MCP2515_CS_LOW();
    SPI1_Write(SPI_WRITE);
    SPI1_Write(RXB1SIDH);

    for(i = 0; i < 13; i++)
    {
        SPI1_Write(0x00);
    }

    MCP2515_CS_HIGH();
}


void MCP2515_clear_TX_buffers(void)
{
    unsigned char i = 0;

    MCP2515_CS_LOW();
    SPI1_Write(SPI_WRITE);
    SPI1_Write(TXB0SIDH);

    for(i = 0; i < 13; i++)
    {
        SPI1_Write(0x00);
    }
    
    MCP2515_CS_HIGH();
    
    MCP2515_CS_LOW();
    SPI1_Write(SPI_WRITE);
    SPI1_Write(TXB1SIDH);

    for(i = 0; i < 13; i++)
    {
        SPI1_Write(0x00);
    }

    MCP2515_CS_HIGH();
    
    MCP2515_CS_LOW();
    SPI1_Write(SPI_WRITE);
    SPI1_Write(TXB2SIDH);

    for(i = 0; i < 13; i++)
    {
        SPI1_Write(0x00);
    }

    MCP2515_CS_HIGH();
}


void MCP2515_flush_buffers(void)
{
    MCP2515_clear_RX_buffers();
    MCP2515_clear_TX_buffers();
}


void MCP2515_set_filter(unsigned char filter_number, unsigned long filter_id, unsigned char ext_std_frame)
{
     unsigned char address = 0x00;
     unsigned char RXFnSIDH = 0x00;
     unsigned char RXFnSIDL = 0x00;
     unsigned char RXFnEID8 = 0x00;
     unsigned char RXFnEID0 = 0x00;
     
     switch(filter_number)
     {
         case 1:
         {
             address = RXF1SIDH;
             break;
         }
         
         case 2:
         {
             address = RXF2SIDH;
             break;
         }
         
         case 3:
         {
             address = RXF3SIDH;
             break;
         }
         
         case 4:
         {
             address = RXF4SIDH;
             break;
         }
         
         case 5:
         {
             address = RXF5SIDH;
             break;
         }
         
         default:
         {
             address = RXF0SIDH;
             break;
         }
     }
     
      switch(ext_std_frame)
      {
          case CAN_EXTENDED_FRAME:
          {
              RXFnSIDH = (filter_id >> 21);
              RXFnSIDL = ((filter_id >> 13) & SIDL_SID);
              RXFnSIDL |= ((filter_id >> 16) & SIDL_EID);
              RXFnEID8 = (filter_id >> 8);
              RXFnEID0 = filter_id;
              
              bit_set(RXFnSIDL, EXIDE);
              
              break;
          }
          
          default:
          {
              RXFnSIDH = (filter_id >> 3);
              RXFnSIDL = ((filter_id << 5) & SIDL_SID);
              RXFnEID8 = 0x00;
              RXFnEID0 = 0x00;
              
              break;
          }
      }
      
      MCP2515_CS_LOW();
      SPI1_Write(address);
      SPI1_Write(RXFnSIDH);
      SPI1_Write(RXFnSIDL);
      SPI1_Write(RXFnEID8);
      SPI1_Write(RXFnEID0);
      MCP2515_CS_HIGH();
}


void MCP2515_set_mask(unsigned char mask_number, unsigned long mask_id, unsigned char ext_std_frame)
{
     unsigned char address = 0x00;
     unsigned char RXMnSIDH = 0x00;
     unsigned char RXMnSIDL = 0x00;
     unsigned char RXMnEID8 = 0x00;
     unsigned char RXMnEID0 = 0x00;

     switch(mask_number)
     {
         case 1:
         {
             address = RXM0SIDH;
             break;
         }

         default:
         {
             address = RXM1SIDH;
             break;
         }
     }

      switch(ext_std_frame)
      {
          case CAN_EXTENDED_FRAME:
          {
              RXMnSIDH = (mask_id >> 21);
              RXMnSIDL = ((mask_id >> 13) & SIDL_SID);
              RXMnSIDL |= ((mask_id >> 16) & SIDL_EID);
              RXMnEID8 = (mask_id >> 8);
              RXMnEID0 = mask_id;

              bit_set(RXMnSIDL, EXIDE);

              break;
          }

          default:
          {
              RXMnSIDH = (mask_id >> 3);
              RXMnSIDL = ((mask_id << 5) & SIDL_SID);
              RXMnEID8 = 0x00;
              RXMnEID0 = 0x00;

              break;
          }
      }

      MCP2515_CS_LOW();
      SPI1_Write(address);
      SPI1_Write(RXMnSIDH);
      SPI1_Write(RXMnSIDL);
      SPI1_Write(RXMnEID8);
      SPI1_Write(RXMnEID0);
      MCP2515_CS_HIGH();
}