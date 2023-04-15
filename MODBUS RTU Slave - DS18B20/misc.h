#define HIGH                                1
#define LOW                                 0

#define TRUE                                1
#define FALSE                               0

#define YES                                 1
#define NO                                  0

#define ON                                  1
#define OFF                                 0

#define ENABLE                              1
#define DISABLE                             0

#define bit_set(reg, bit_val)               reg |= (1 << bit_val)
#define bit_clr(reg, bit_val)               reg &= (~(1 << bit_val))
#define bit_tgl(reg, bit_val)               reg ^= (1 << bit_val)
#define get_bit(reg, bit_val)               (reg & (1 << bit_val))
#define get_reg(reg, msk)                   (reg & msk)


unsigned int make_word(unsigned char HB, unsigned char LB);
void get_HB_LB(unsigned int value, unsigned char *HB, unsigned char *LB);