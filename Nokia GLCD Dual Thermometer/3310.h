#ifndef _lph7779_v3
#define _lph7779_v3
#include <all.h>     
//===================
#define nok_sclk  portb.f4
#define nok_sda   portb.f3
#define nok_dc    portb.f2
#define nok_cs    portb.f1
#define nok_res   portb.f0
#define putchar(c) nokia_printchar(c)  


#define PIXEL_OFF 0
#define PIXEL_ON  1
#define PIXEL_XOR 2

#define LCDCOLMAX         84
#define LCDROWMAX          6
#define LCDPIXELROWMAX    48     
                                              

unsigned short newline=0;
int ddram;
char charsel,char_row,charpos,chardata,plot_value;
long plot_value32,plot_llsb,plot_ulsb,plot_lmsb,plot_umsb;   
static unsigned char lcd_buffer[LCDROWMAX][LCDCOLMAX];  


//ASCII Table of Character, The characters are need to be drawn pixel by pixel

const char TABLE5[240]={0x00,0x00,0x00,0x00,0x00,   // 20 space          
                  0x00,0x00,0x5f,0x00,0x00,   // 21 !
                  0x00,0x07,0x00,0x07,0x00,   // 22 "
                  0x14,0x7f,0x14,0x7f,0x14,   // 23 #
                  0x24,0x2a,0x7f,0x2a,0x12,   // 24 $
                  0x23,0x13,0x08,0x64,0x62,   // 25 %
                  0x36,0x49,0x55,0x22,0x50,   // 26 &
                  0x00,0x05,0x03,0x00,0x00,   // 27 '
                  0x00,0x1c,0x22,0x41,0x00,   // 28 (
                  0x00,0x41,0x22,0x1c,0x00,   // 29 )
                  0x14,0x08,0x3e,0x08,0x14,   // 2a *
                  0x08,0x08,0x3e,0x08,0x08,   // 2b +
                  0x00,0x50,0x30,0x00,0x00,   // 2c ,
                  0x08,0x08,0x08,0x08,0x08,   // 2d -
                  0x00,0x60,0x60,0x00,0x00,   // 2e .
                  0x20,0x10,0x08,0x04,0x02,   // 2f /
                  0x3e,0x51,0x49,0x45,0x3e,   // 30 0
                  0x00,0x42,0x7f,0x40,0x00,   // 31 1
                  0x42,0x61,0x51,0x49,0x46,   // 32 2
                  0x21,0x41,0x45,0x4b,0x31,   // 33 3
                  0x18,0x14,0x12,0x7f,0x10,   // 34 4
                  0x27,0x45,0x45,0x45,0x39,   // 35 5
                  0x3c,0x4a,0x49,0x49,0x30,   // 36 6
                  0x01,0x71,0x09,0x05,0x03,   // 37 7
                  0x36,0x49,0x49,0x49,0x36,   // 38 8
                  0x06,0x49,0x49,0x29,0x1e,   // 39 9
                  0x00,0x36,0x36,0x00,0x00,   // 3a :
                  0x00,0x56,0x36,0x00,0x00,   // 3b ;
                  0x08,0x14,0x22,0x41,0x00,   // 3c <
                  0x14,0x14,0x14,0x14,0x14,   // 3d =
                  0x00,0x41,0x22,0x14,0x08,   // 3e >
                  0x02,0x01,0x51,0x09,0x06,   // 3f ?
                  0x32,0x49,0x79,0x41,0x3e,   // 40 @
                  0x7e,0x11,0x11,0x11,0x7e,   // 41 A
                  0x7f,0x49,0x49,0x49,0x36,   // 42 B
                  0x3e,0x41,0x41,0x41,0x22,   // 43 C
                  0x7f,0x41,0x41,0x22,0x1c,   // 44 D
                  0x7f,0x49,0x49,0x49,0x41,   // 45 E
                  0x7f,0x09,0x09,0x09,0x01,   // 46 F
                  0x3e,0x41,0x49,0x49,0x7a,   // 47 G
                  0x7f,0x08,0x08,0x08,0x7f,   // 48 H
                  0x00,0x41,0x7f,0x41,0x00,   // 49 I
                  0x20,0x40,0x41,0x3f,0x01,   // 4a J
                  0x7f,0x08,0x14,0x22,0x41,   // 4b K
                  0x7f,0x40,0x40,0x40,0x40,   // 4c L
                  0x7f,0x02,0x0c,0x02,0x7f,   // 4d M
                  0x7f,0x04,0x08,0x10,0x7f,   // 4e N
                  0x3e,0x41,0x41,0x41,0x3e};   // 4f O


const char TABLE6[240]=            {0x7f,0x09,0x09,0x09,0x06,   // 50 P
                  0x3e,0x41,0x51,0x21,0x5e,   // 51 Q
                  0x7f,0x09,0x19,0x29,0x46,   // 52 R
                  0x46,0x49,0x49,0x49,0x31,   // 53 S
                  0x01,0x01,0x7f,0x01,0x01,   // 54 T
                  0x3f,0x40,0x40,0x40,0x3f,   // 55 U
                  0x1f,0x20,0x40,0x20,0x1f,   // 56 V
                  0x3f,0x40,0x38,0x40,0x3f,   // 57 W
                  0x63,0x14,0x08,0x14,0x63,   // 58 X
                  0x07,0x08,0x70,0x08,0x07,   // 59 Y
                  0x61,0x51,0x49,0x45,0x43,   // 5a Z
                  0x00,0x7f,0x41,0x41,0x00,   // 5b [
                  0x02,0x04,0x08,0x10,0x20,   // 5c
                  0x00,0x41,0x41,0x7f,0x00,   // 5d
                  0x04,0x02,0x01,0x02,0x04,   // 5e
                  0x40,0x40,0x40,0x40,0x40,   // 5f
                  0x00,0x01,0x02,0x04,0x00,   // 60
                  0x20,0x54,0x54,0x54,0x78,   // 61 a
                  0x7f,0x48,0x44,0x44,0x38,   // 62 b
                  0x38,0x44,0x44,0x44,0x20,   // 63 c
                  0x38,0x44,0x44,0x48,0x7f,   // 64 d
                  0x38,0x54,0x54,0x54,0x18,   // 65 e
                  0x08,0x7e,0x09,0x01,0x02,   // 66 f
                  0x0c,0x52,0x52,0x52,0x3e,   // 67 g
                  0x7f,0x08,0x04,0x04,0x78,   // 68 h
                  0x00,0x44,0x7d,0x40,0x00,   // 69 i
                  0x20,0x40,0x44,0x3d,0x00,   // 6a j
                  0x7f,0x10,0x28,0x44,0x00,   // 6b k
                  0x00,0x41,0x7f,0x40,0x00,   // 6c l
                  0x7c,0x04,0x18,0x04,0x78,   // 6d m
                  0x7c,0x08,0x04,0x04,0x78,   // 6e n
                  0x38,0x44,0x44,0x44,0x38,   // 6f o
                  0x7c,0x14,0x14,0x14,0x08,   // 70 p
                  0x08,0x14,0x14,0x18,0x7c,   // 71 q
                  0x7c,0x08,0x04,0x04,0x08,   // 72 r
                  0x48,0x54,0x54,0x54,0x20,   // 73 s
                  0x04,0x3f,0x44,0x40,0x20,   // 74 t
                  0x3c,0x40,0x40,0x20,0x7c,   // 75 u
                  0x1c,0x20,0x40,0x20,0x1c,   // 76 v
                  0x3c,0x40,0x30,0x40,0x3c,   // 77 w
                  0x44,0x28,0x10,0x28,0x44,   // 78 x
                  0x0c,0x50,0x50,0x50,0x3c,   // 79 y
                  0x44,0x64,0x54,0x4c,0x44,   // 7a z
                  0x00,0x08,0x36,0x41,0x00,   // 7b
                  0x00,0x00,0x7f,0x00,0x00,   // 7c
                  0x00,0x41,0x36,0x08,0x00,   // 7d
                  0x10,0x08,0x08,0x10,0x08,   // 7e
                  0x78,0x46,0x41,0x46,0x78};   // 7f
            

// Functions Used 

void    nokia_init(void); // Initialising the Nokia LCD
void    nokia_write_command(char bytefornokia_command);// Sending Command to the LCD
void    nokia_write_data(char bytefornokia_data);// Sending DATA to LCD
void    nokia_write_dorc(char bytefornokia);// DATA or Command
void    nokia_gotoxy(byte xnokia, byte ynokia);// Position
void    nokia_erase_y(byte ynokia);
void    nokia_erase_x(byte xnokia);
void    nokia_printchar(byte cvar);
void    nokia_clean_ddram(void);
void    table_to_nokialcd(void);
void    nokia_plot(byte xnokia,byte plot_value8);
void    nokia_write_data_inv(char bytefornokia_data_inv);
void    nokia_clear_screen(void);
void    nokia_clear_xy(byte xnokia, byte ynokia); 
void    LcdPixel (signed char x, signed char y, char c);
void    drawLine(signed char x1, signed char y1, signed char x2, signed char y2, unsigned char c);
void    drawCircle(unsigned char xc, unsigned char yc, unsigned char r, unsigned char c);
void    drawFilledRectangle(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned char c);
void    drawRectangle(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned char c);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void nokia_init(void)
{
nok_dc=1;            // bytes are stored in the display data ram, address counter, incremented automatically
nok_cs=1;            // chip disabled
                  
nok_res=0;            
delay_ms(10);         
nok_res=1;
   
nokia_write_command(0x21);   // set extins extended instruction set
nokia_write_command(0xc2);   // Vop  v1: 0xc8 (for 3V)// v2: 0xa0 (for 3V) // v3: 0xc2 (2v6-5v)   
nokia_write_command(0x13);   // bias
nokia_write_command(0x20);   // horizontal mode from left to right, X axe are incremented automatically , 0x22 for vertical addressing ,back on normal instruction set too
nokia_write_command(0x09);   // all on
      
nokia_clean_ddram();      // reset DDRAM, otherwise the lcd is blurred with random pixels
         
nokia_write_command(0x08);   // mod control blank change (all off)
      
nokia_write_command(0x0c);   // mod control normal change

}

// CLearing the Display Data Ram

void nokia_clean_ddram(void)
{
nokia_gotoxy(0,0);         // 84*6=504      clear LCD
for (ddram=504;ddram>0;ddram--){nokia_write_data(0x00);}

}


// Sending Command

void nokia_write_command(char bytefornokia_command)
{

nok_dc=0;   // byte is a command it is read with the eight SCLK pulse
nok_cs=0;   // chip enabled
nokia_write_dorc(bytefornokia_command);
nok_cs=1;   // chip disabled

}

// Sending Data

void nokia_write_data(char bytefornokia_data)
{

nok_dc=1;
nok_cs=0;   // chip enabled
nokia_write_dorc(bytefornokia_data);
nok_cs=1;   // chip disabled

}


// Writing Data OR Command Serially

void nokia_write_dorc(char bytefornokia)       
{
char caa;
for (caa=8;caa>0;caa--) {
      nok_sclk=0;
      // delay_us(2);
      if ((bytefornokia&0x80)==0){nok_sda=0;}
      else {nok_sda=1;}
      nok_sclk=1;
      bytefornokia=bytefornokia<<1;
               }
}

//////////////////////////////////////////////////////////////////////////////////
void nokia_gotoxy(byte xnokia, byte ynokia)      // Nokia LCD 3310 Position cursor
{
      nokia_write_command(0x40|(ynokia&0x07));   // Y axe initialisation: 0100 0yyy   
      
      nokia_write_command(0x80|(xnokia&0x7f));   // X axe initialisation: 1xxx xxxx
}
//////////////////////////////////////////////////////////////////////////////////
void nokia_erase_y(byte ynokia)
{
 char row;
 for(row=0;row<79;row++)
{
nokia_gotoxy(row,ynokia);
nokia_printchar(' ');

}
}
//////////////////////////////////////////////////////////////////////////////////
void nokia_erase_x(byte xnokia)
{
char column;

for (column=0;column!=6;column++){
      nokia_gotoxy(xnokia,column);
      nokia_write_data(0x00);
      nokia_write_data(0x00);
      nokia_write_data(0x00);
      nokia_write_data(0x00);
      nokia_write_data(0x00);
      nokia_write_data(0x00);
      
                           }
}
//////////////////////////////////////////////////////////////////////////////////

void nokia_printchar(byte cvar)               // Write 1 character to LCD
{
charsel=cvar;
table_to_nokialcd();
}



// Extracting the ASCII Values from the Table

void table_to_nokialcd(void)   
{
if (charsel<0x20)return;
if (charsel>0x7f)return;

for (char_row=0;char_row<5;char_row++) {      // 5 bytes
   
if (charsel<0x50){charpos=(((charsel&0xff)-0x20)*5);chardata=TABLE5[(charpos+char_row)];}            // use TABLE5
else if (charsel>0x4f){charpos=(((charsel&0xff)-0x50)*5);chardata=TABLE6[(charpos+char_row)];}            // use TABLE6                     
            
            
   nokia_write_data(chardata);      // send data to nokia   
                              }

   nokia_write_data(0x00);      //    1 byte (always blank)
   
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



void nokia_write_data_inv(char bytefornokia_data_inv)
{
char caa;

nok_dc=1;
nok_cs=0;   // chip enabled

for (caa=8;caa>0;caa--) {
      nok_sclk=0;
      delay_us(2);
      if ((bytefornokia_data_inv&0x01)==0){nok_sda=0;}
      else {nok_sda=1;}
      nok_sclk=1;
      bytefornokia_data_inv=bytefornokia_data_inv>>1;
               }

nok_cs=1;   // chip disabled
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void nokia_clear_screen(void)
{
nokia_erase_y(0);
nokia_erase_y(1);
nokia_erase_y(2);
nokia_erase_y(3);
nokia_erase_y(4);
nokia_erase_y(5);

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void nokia_clear_xy(byte xnokia, byte ynokia)
{

nokia_gotoxy(xnokia,ynokia);
nokia_printchar(' ');


}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void printf(char*ptr)
{

 while(*ptr){
             putchar(*ptr++);

             }
 }
 //====================================
void putc(char c)
{
  unsigned char data_val[3]={0};
  data_val[1] =c%10;
  data_val[0] =(char)((c/10)%10);
  data_val[1]+=48;
  data_val[0]+=48;
  printf(data_val);
}
//=================================== 


void LcdPixel (signed char x, signed char y, char c) {
    
    unsigned char value;
    unsigned char row;
    
    if( x < 0 || x >= LCDCOLMAX || y < 0 || y >= LCDPIXELROWMAX ) return;

    row = y / 8;

    value = lcd_buffer[row][x];
    if( c == PIXEL_ON ) {
        value |= (1 << (y % 8));
    } else if( c == PIXEL_XOR ) {
        value ^= (1 << (y % 8));
    } else {
        value &= ~(1 << (y % 8));
    }

    lcd_buffer[row][x] = value;

    nokia_gotoxy(x,row);
    nokia_write_data(value);
}


void drawLine(signed char x1, signed char y1, signed char x2, signed char y2, unsigned char c) 
{
    signed char dx, dy, stepx, stepy, fraction;

    dy = y2 - y1;
    dx = x2 - x1;

    /* dy is negative */
    if ( dy < 0 ) {
        dy = -dy;
        stepy = -1;
    } else {
        stepy = 1;
    }

    /* dx is negative */
    if ( dx < 0 ) {
        dx = -dx;
        stepx = -1;
    } else {
        stepx = 1;
    }

    dx <<= 1;
    dy <<= 1;

    /* Draw initial position */
    LcdPixel (x1, y1, c);

    /* Draw next positions until end */
    if ( dx > dy ) {
        /* Take fraction */
        fraction = dy - ( dx >> 1);
        while ( x1 != x2 ) {
            if ( fraction >= 0 ) {
                y1 += stepy;
                fraction -= dx;
            }
            x1 += stepx;
            fraction += dy;

            /* Draw calculated point */
            LcdPixel( x1, y1, c );
        }
    } else {
        fraction = dx - ( dy >> 1);
        while ( y1 != y2 ) {
            if ( fraction >= 0 ) {
                x1 += stepx;
                fraction -= dy;
            }
            y1 += stepy;
            fraction += dx;
            LcdPixel( x1, y1, c );
        }
    }
}


void drawCircle(unsigned char xc, unsigned char yc, unsigned char r, unsigned char c) 
{
    unsigned char x=0;
    unsigned char y=r;
    signed char p=0;
    p = (3 - (2 * r));
    LcdPixel((byte)(xc+x),(byte)(yc-y),c);

    for(x=0;x<=y;x++) 
    {
        if (p<0) 
        {
            y=y;
            p=(p+(4*x)+6);
        } else 
        {
            y=y-1;
            p=p+((4*(x-y)+10));
        }

        LcdPixel((byte)(xc+x),(byte)(yc-y), c);
        LcdPixel((byte)(xc-x),(byte)(yc-y), c);
        LcdPixel((byte)(xc+x),(byte)(yc+y), c);
        LcdPixel((byte)(xc-x),(byte)(yc+y), c);
        LcdPixel((byte)(xc+y),(byte)(yc-x), c);
        LcdPixel((byte)(xc-y),(byte)(yc-x), c);
        LcdPixel((byte)(xc+y),(byte)(yc+x), c);
        LcdPixel((byte)(xc-y),(byte)(yc+x), c);
     }
}


void drawFilledRectangle(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned char c) 
{
   unsigned char i=0;
   for(i=y1; i <= y2; i++ )
   {
             drawLine( x1, i, x2, i, c );
   }
}


void drawRectangle(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned char c)
{
    drawLine( x1, y1, x2, y1, c );
    drawLine( x1, y1, x1, y2, c );
    drawLine( x1, y2, x2, y2, c );
    drawLine( x2, y1, x2, y2, c );
}   
 
 

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif