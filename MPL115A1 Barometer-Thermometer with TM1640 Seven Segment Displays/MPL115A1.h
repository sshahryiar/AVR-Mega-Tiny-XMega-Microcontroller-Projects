#define LOW                   0
#define HIGH                  1

#define PRESH              0x80
#define PRESL              0x82
#define TEMPH              0x84
#define TEMPL              0x86

#define A0_H               0x88                                                
#define A0_L               0x8A
#define B1_H               0x8C
#define B1_L               0x8E
#define B2_H               0x90             
#define B2_L               0x92
#define C12_H              0x94
#define C12_L              0x96                   

#define conv_cmd           0x24             

#define SDN_pin            PORTB1_bit
#define CSN_pin            PORTB2_bit
#define SDI_pin            PORTB3_bit
#define SD0_pin            PINB4_bit
#define SCK_pin            PORTB5_bit


struct
{
  float A0_;           
  float B1_;   
  float B2_;    
  float C12_;
}coefficients; 
                                

void MPL115A1_init(void);
unsigned char MPL115A1_read(unsigned char address);
void MPL115A1_write(unsigned char address, unsigned char value);
void MPL115A1_get_coefficients(void);
void MPL115A1_get_bytes(unsigned int *hb, unsigned int *lb, unsigned char address);
void MPL115A1_get_data(float *pres, float *temp);