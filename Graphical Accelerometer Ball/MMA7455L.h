sbit Soft_I2C_Scl_Output    at PORTB0_bit;
sbit Soft_I2C_Sda_Output    at PORTB1_bit;
sbit Soft_I2C_Scl_Input     at PINB0_bit;
sbit Soft_I2C_Sda_Input     at PINB1_bit;
sbit Soft_I2C_Scl_Direction at DDB0_bit;
sbit Soft_I2C_Sda_Direction at DDB1_bit;


#define MMA7455L_write_address      0x3A
#define MMA7455L_read_address       0x3B 
                                                
#define X_out_L                     0x00           
#define X_out_H                     0x01  
#define Y_out_L                     0x02  
#define Y_out_H                     0x03    
#define Z_out_L                     0x04  
#define Z_out_H                     0x05    
#define X_out                       0x06    
#define Y_out                       0x07  
#define Z_out                       0x08      
#define STATUS                      0x09  
#define DETSRC                      0x0A  
#define TOUT                        0x0B
#define RSV1                        0x0C
#define I2C_Address                 0x0D
#define User_Info                   0x0E
#define Who_Am_I                    0x0F
#define X_offset_L                  0x10  
#define X_offset_H                  0x11  
#define Y_offset_L                  0x12  
#define Y_offset_H                  0x13    
#define Z_offset_L                  0x14  
#define Z_offset_H                  0x15 
#define MCTL                        0x16
#define INTRST                      0x17
#define CTL1                        0x18
#define CTL2                        0x19
#define LDTH                        0x1A
#define PDTH                        0x1B
#define PW                          0x1C
#define LT                          0x1D
#define TW                          0x1E
#define RSV2                        0x1F    

#define MMA_7455_2G_MODE            0x05 
#define MMA_7455_4G_MODE            0x09     
#define MMA_7455_8G_MODE            0x01  

                      
void init_MMA7455L(unsigned char sensitivity);       
void offset_calibration();
unsigned char read_accelerometer_axis(unsigned char address);    


signed char x_offset = 0;
signed char y_offset = 0; 
signed char x_axis = 0;
signed char y_axis = 0;
