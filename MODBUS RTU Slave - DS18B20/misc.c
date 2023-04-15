#include "misc.h"

unsigned int make_word(unsigned char HB, unsigned char LB)
{
    unsigned int tmp = 0;

    tmp = HB;
    tmp <<= 8;
    tmp |= LB;

    return tmp;
}


void get_HB_LB(unsigned int value, unsigned char *HB, unsigned char *LB)
{
    *LB = (value & 0x00FF);
    *HB = ((value & 0xFF00) >> 0x08);
}