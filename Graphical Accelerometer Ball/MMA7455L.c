#include "MMA7455L.h"


void init_MMA7455L(unsigned char sensitivity)  
{
    Soft_I2C_Start();
    Soft_I2C_Write(MMA7455L_write_address);
    Soft_I2C_Write(MCTL);
    if(sensitivity == 2)
    {
        Soft_I2C_Write(MMA_7455_2G_MODE);
    }
    if(sensitivity == 4)
    {                  
        Soft_I2C_Write(MMA_7455_4G_MODE);
    }
    if(sensitivity == 8)
    {
        Soft_I2C_Write(MMA_7455_8G_MODE);
    }          
    Soft_I2C_Stop();
    delay_ms(250);
}   


void offset_calibration() 
{          
    delay_ms(2000);        
    x_offset = read_accelerometer_axis(X_out);
    y_offset = read_accelerometer_axis(Y_out);    
    delay_ms(1000);     
}   
                                        
                                                                
unsigned char read_accelerometer_axis(unsigned char address)   
{   
    unsigned char samples = 0;                           
    unsigned char data_value = 0;
    unsigned int avg = 0; 
    
    for(samples = 0; samples < 32; samples += 1)
    {
        Soft_I2C_Start();
        Soft_I2C_Write(MMA7455L_write_address);
        Soft_I2C_Write(address);
        Soft_I2C_Start();
        Soft_I2C_Write(MMA7455L_read_address);
        avg += Soft_I2C_Read(0);
        Soft_I2C_Stop();
    }      
    data_value = avg >> 5;
    return data_value;               
}                                                                                                         


void read_and_compensate()        
{                                              
    x_axis = read_accelerometer_axis(X_out);
    x_axis -= x_offset;    
    y_axis = read_accelerometer_axis(Y_out);   
    y_axis -= y_offset;      
}  