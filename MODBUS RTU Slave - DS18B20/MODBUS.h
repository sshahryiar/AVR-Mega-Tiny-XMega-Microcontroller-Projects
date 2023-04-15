#define own_ID                                  0x46  //70

#define FC_read_coils                           0x01
#define FC_read_discrete_inputs                 0x02
#define FC_read_holding_registers               0x03
#define FC_read_input_registers                 0x04
#define FC_write_single_coil                    0x05
#define FC_write_single_register                0x06
#define FC_write_multiple_coils                 0x0F
#define FC_write_multiple_registers             0x10

#define coil_1                                  0
#define coil_2                                  1
#define coil_3                                  2
#define coil_4                                  3

#define discrete_input_1                        100
#define discrete_input_2                        101
#define discrete_input_3                        102
#define discrete_input_4                        103

#define input_register_1                        300
#define input_register_2                        301

#define holding_register_1                      400
#define holding_register_2                      401

#define no_of_coils                             4
#define no_of_inputs                            4
#define no_of_input_regs                        2
#define no_of_holding_regs                      2

#define addr_coil_start                         coil_1
#define addr_coil_end                           coil_4

#define addr_input_start                        discrete_input_1
#define addr_input_end                          discrete_input_4

#define addr_input_reg_start                    input_register_1
#define addr_input_reg_end                      input_register_2

#define addr_holding_reg_start                  holding_register_1
#define addr_holding_reg_end                    holding_register_2

#define id_byte                                 0
#define function_code_byte                      1
#define byte_length_byte                        2

#define location_start_high_byte                2
#define location_start_low_byte                 3
#define location_end_high_byte                  4
#define location_end_low_byte                   5
#define byte_size_byte                          6
#define CRC_high_byte                           6
#define CRC_low_byte                            7

#define coil_ON                                 0xFF00
#define coil_OFF                                0x0000

#define TX_buffer_length                        16
#define RX_buffer_length                        16
#define mandatory_bytes_to_read                 7
#define fixed_no_of_bytes_to_read               5

#define REDE                                    PORTD2_bit

#define DIR_RX                                  REDE = 0
#define DIR_TX                                  REDE = 1


unsigned char cnt = 0x00;
volatile unsigned char TX_buffer[TX_buffer_length];
volatile unsigned char RX_buffer[RX_buffer_length];

unsigned char coils[no_of_coils] = {0, 0, 0, 0};
unsigned char discrete_inputs[no_of_inputs] = {0, 0, 0, 0};
unsigned int input_registers[no_of_input_regs] = {0x0000, 0x0000};
unsigned int holding_registers[no_of_holding_regs] = {0x0000, 0x0000};


void flush_RX_buffer(void);
void flush_TX_buffer(void);
unsigned int MODBUS_RTU_CRC16(unsigned char *data_input, unsigned char data_length);
void MODBUS_receive_task(void);
void MODBUS_send_task(unsigned char function_code, unsigned char data_length, unsigned char *values);