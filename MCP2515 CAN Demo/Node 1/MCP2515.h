#include "MCP2515_defintions.h"
#include "misc.h"


#define MCP2515_CS_LOW()            PORTD3_bit = LOW
#define MCP2515_CS_HIGH()           PORTD3_bit = HIGH

#define MCP2515_INT()               PIND2_bit

#define CAN_STANDARD_FRAME          0
#define CAN_EXTENDED_FRAME          1

#define CAN_STANDARD_ID_MASK        0x07FF

#define CAN_EXTENDED_ID_MASK        0x1FFFFFFF

#define CAN_DATA_FIELD_LENGTH       8

#define SIDL_SID                    0xE0
#define SIDL_EID                    0x03
#define length_bit_fields           0x0F

// CAN Bitrate 125 kbps
#define R_CNF1_125kbps              (bit_mask(BRP2) | bit_mask(BRP1) | bit_mask(BRP0))
#define R_CNF2_125kbps              (bit_mask(BTLMODE) | bit_mask(PHSEG11))
#define R_CNF3_125kbps              (bit_mask(PHSEG21))

// CAN Bitrate 250 kbps
#define R_CNF1_250kbps              (bit_mask(BRP1) | bit_mask(BRP0))
#define R_CNF2_250kbps              (bit_mask(BTLMODE) | bit_mask(PHSEG11))
#define R_CNF3_250kbps              (bit_mask(PHSEG21))

// CAN Bitrate 500 kbps
#define R_CNF1_500kbps              (bit_mask(BRP0))
#define R_CNF2_500kbps              (bit_mask(BTLMODE) | bit_mask(PHSEG11))
#define R_CNF3_500kbps              (bit_mask(PHSEG21))

// CAN Bitrate 1 Mbps
#define R_CNF1_1Mbps                0
#define R_CNF2_1Mbps                (bit_mask(BTLMODE) | bit_mask(PHSEG11))
#define R_CNF3_1Mbps                (bit_mask(PHSEG21))


typedef struct CAN_msg
{
    unsigned long id;
    unsigned char ext_id: 1;
    unsigned char rtr: 1;
    unsigned char length: 4;
    unsigned char data_byte[CAN_DATA_FIELD_LENGTH];
};

struct CAN_msg CAN_TX_msg;
struct CAN_msg CAN_RX_msg;


void MCP2515_init(void);
void MCP2515_reset(void);
void MCP2515_write_register(unsigned char address, unsigned char value);
unsigned char MCP2515_read_register(unsigned char address);
void MCP2515_bit_modify(unsigned char address, unsigned char bitmask, unsigned char value);
unsigned char MCP2515_read_status(unsigned char type);
unsigned char MSP2515_check_free_buffer(void);
unsigned char MCP2515_check_for_incoming_message(void);
unsigned char MCP2515_message_TX(void);
unsigned char MCP2515_message_RX(void);
void MCP2515_clear_RX_buffers(void);
void MCP2515_clear_TX_buffers(void);
void MCP2515_flush_buffers(void);
void MCP2515_set_filter(unsigned char filter_number, unsigned long filter_id, unsigned char ext_std_frame);
void MCP2515_set_mask(unsigned char mask_number, unsigned long mask_id, unsigned char ext_std_frame);