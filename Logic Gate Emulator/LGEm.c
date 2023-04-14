#define ee_state 0x00

#define S PINC0_bit
#define A PINC1_bit
#define B PINC2_bit
#define F PORTD0_bit

short state = 0;

void set_mcu();
void AND();
void OR();
void NAND();
void NOR();
void EXOR();
void EXNOR();
void MUX();
void NOT();
void BUFFER();
void display_status(unsigned short disp);

void mode_select()
org IVT_ADDR_INT1
{
   PORTB7_bit = 1;
   state+=1;
   delay_ms(9);
   PORTB7_bit = 1;
   eeprom_write(ee_state,state);
   if(state>8)
   {
      state = 0;
   }
   PORTB7_bit = 0;
}

void main()
{
   set_mcu();
   for(;;)
   {
      display_status(state);
      if(state==0)
      {
         AND();
      }
      else if(state==1)
      {
         OR();
      }
      else if(state==2)
      {
         NAND();
      }
      else if(state==3)
      {
         NOR();
      }
      else if(state==4)
      {
         EXOR();
      }
      else if(state==5)
      {
         EXNOR();
      }
      else if(state==6)
      {
         MUX();
      }
      else if(state==7)
      {
         NOT();
      }
      else
      {
         BUFFER();
      }
   }
}

void set_mcu()
{
     state = eeprom_read(ee_state);
     PORTB=0x00;
     DDRB=0xFF;
     PORTC=0x00;
     DDRC=0x00;
     PORTD=0x00;
     DDRD=0x01;
     GICR=0x80;
     MCUCR=0x0C;
     GIFR=0x80;
     asm sei;
     display_status(state);
}

void AND()
{
   if(A&B==1)
   {
      F=1;
   }
   else
   {
      F=0;
   }
}

void OR()
{
   if(A|B==1)
   {
      F=1;
   }
   else
   {
      F=0;
   }
}

void NAND()
{
   if((A&B)==1)
   {
      F=0;
   }
   else
   {
      F=1;
   }
}

void NOR()
{
   if((A|B)==1)
   {
      F=0;
   }
   else
   {
      F=1;
   }
}

void EXOR()
{
   if(A^B==1)
   {
      F=1;
   }
   else
   {
      F=0;
   }
}

void EXNOR()
{
   if((A^B)==1)
   {
      F=0;
   }
   else
   {
      F=1;
   }
}

void MUX()
{
   if((A&!S|B&S)==1)
   {
      F=1;
   }
   else
   {
      F=0;
   }
}

void NOT()
{
   if(A==1)
   {
      F=0;
   }
   else
   {
      F=1;
   }
}

void BUFFER()
{
   if(A==1)
   {
      F=1;
   }
   else
   {
      F=0;
   }
}

void display_status(unsigned short disp)
{
     const unsigned short num[10] = {0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
     PORTB = num[disp];
}
