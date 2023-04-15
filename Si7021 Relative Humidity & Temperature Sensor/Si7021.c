#include "Si7021.h"


void Si7021_init(void)
{
    TWI_Init(100000);
    delay_ms(200);
    Si7021_config();
}


void Si7021_read_word(unsigned char reg_addr, signed int *HB, signed int *LB)
{
    TWI_Start();
    TWI_Write(Si7021_write_cmd);
    TWI_Write(reg_addr);

    TWI_Start();
    TWI_Write(Si7021_read_cmd);
    *HB = ((signed int)TWI_Read(1));
    *LB = ((signed int)TWI_Read(0));
    TWI_Stop();
}


unsigned char Si7021_read_byte(unsigned char reg_addr)
{
    unsigned char value = 0;

    TWI_Start();
    TWI_Write(Si7021_write_cmd);
    TWI_Write(reg_addr);
    
    TWI_Start();
    TWI_Write(Si7021_read_cmd);
    value = TWI_Read(0);
    TWI_Stop();
    return value;
}


void Si7021_write_byte(unsigned char reg_addr, unsigned char value)
{
    TWI_Start();
    TWI_Write(Si7021_write_cmd);
    TWI_Write(reg_addr);
    TWI_Write(value);
    TWI_Stop();
}


void Si7021_config(void)
{
    Si7021_write_byte(Si7021_Write_Heater_Control_Register, 0x09);
    Si7021_write_byte(Si7021_Write_Config_Register, (Si7021_Config_Resolution_RH_12_T14 | Si70211_Config_Heater_On));
    delay_ms(900);
    Si7021_write_byte(Si7021_Write_Heater_Control_Register, 0x00);
    Si7021_write_byte(Si7021_Write_Config_Register, (Si7021_Config_Resolution_RH_12_T14 | Si70211_Config_Heater_Off));
    delay_ms(900);
}


float get_RH()
{
    float RH = 0;

    signed int HB = 0;
    signed int LB = 0;
    
    unsigned int res = 0;

    Si7021_read_word(Si7021_Measure_RH_Hold_Mode, &HB, &LB);

    res = ((HB << 8) | LB);
    res &= 0xFFFC;
    RH = ((res * 125.0) / 65536.0);
    RH -= 6.0;

    return RH;
}


float get_temperature()
{
    float res = 0;
    
    signed int HB = 0;
    signed int LB = 0;

    Si7021_read_word(Si7021_Measure_T_Hold_Mode, &HB, &LB);

    HB <<= 8;
    HB |= LB;

    res = ((175.72 * HB) / 65536.0);
    res -= 46.85;
    
    return res;
}