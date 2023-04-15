#define MCP3008_Start                   0x01

#define MCP3008_S_CH0                   0x80
#define MCP3008_S_CH1                   0x90
#define MCP3008_S_CH2                   0xA0
#define MCP3008_S_CH3                   0xB0
#define MCP3008_S_CH4                   0xC0
#define MCP3008_S_CH5                   0xD0
#define MCP3008_S_CH6                   0xE0
#define MCP3008_S_CH7                   0xF0

#define MCP3008_D_CH0P_CH1N             0x00
#define MCP3008_D_CH0N_CH1P             0x10
#define MCP3008_D_CH2P_CH3N             0x20
#define MCP3008_D_CH2N_CH3P             0x30
#define MCP3008_D_CH4P_CH5N             0x40
#define MCP3008_D_CH4N_CH5P             0x50
#define MCP3008_D_CH6P_CH7N             0x60
#define MCP3008_D_CH6N_CH7P             0x70

#define MCP3008_DIFFERENTIAL_MODE       0x00
#define MCP3008_SINGLE_MODE             0x01

#define LOW                             0
#define HIGH                            1

#define MCP3008_CS                      PORTB4_bit


void MCP3008_init(void);
signed int MCP3008_read(unsigned char channel, unsigned char type);