#define setup     PINB0_bit
#define up        PINB1_bit
#define down      PINB2_bit
#define save      PINB3_bit

#define heater    PORTD0_bit
#define cooler    PORTD1_bit
#define Fault_H   PORTD2_bit
#define Fault_C   PORTD3_bit

#define ee_t_high        0x0
#define ee_t_low         0x4
#define ee_t_delta       0x8
#define ee_pass_times    0xE


sbit LCD_RS at PORTC2_bit;
sbit LCD_EN at PORTC3_bit;
sbit LCD_D4 at PORTC4_bit;
sbit LCD_D5 at PORTC5_bit;
sbit LCD_D6 at PORTC6_bit;
sbit LCD_D7 at PORTC7_bit;

sbit LCD_RS_Direction at DDC2_bit;
sbit LCD_EN_Direction at DDC3_bit;
sbit LCD_D4_Direction at DDC4_bit;
sbit LCD_D5_Direction at DDC5_bit;
sbit LCD_D6_Direction at DDC6_bit;
sbit LCD_D7_Direction at DDC7_bit;


bit h;
bit c;

float t=0.0;
float temp=0.0;

unsigned long pass=0;

unsigned int t_low=0;
unsigned int t_high=0;
unsigned int t_delta=0;

unsigned char pass_times=0;

void setup_mcu();
unsigned char scan_keys();
unsigned long adc_avg();
void temp_display();
void settings();
signed int inc_dec(signed int variable,signed int max,signed int min,unsigned char x,unsigned char y);
void display_common(unsigned char x,unsigned char y,unsigned char convert);
void compare_temp();
void controller_state(unsigned short state);
void check_fault(unsigned short stat);
void read_memory();
void fault_messages();
void settings_demanded();
void all_tasks();


void main()
{
     setup_mcu();
     read_memory();
     while(1)
     {
          all_tasks();
     };
}

void setup_mcu()
{
     Lcd_Init();
     Sound_Init(&PORTD,4);
     Lcd_Cmd(_LCD_CLEAR);
     Lcd_Cmd(_LCD_CURSOR_OFF);
     DDRD=0xFF;
     PORTD=0x00;
     DDRB=0x00;
     c=0;
     h=0;
}

unsigned char scan_keys()
{
     if(setup)
     {
              Sound_Play(888,99);
              return 1;
     }
     else if(up)
     {
              Sound_Play(900,9);
              return 2;
     }
     else if(down)
     {
              Sound_Play(700,9);
              return 3;
     }
     else if(save)
     {
              Sound_Play(800,99);
              return 4;
     }
     else
     {
              return 0;
     }
}

unsigned long adc_avg()
{
    unsigned char sample=0;
    register unsigned int adc=0;
    for(sample=0;sample<64;sample++)
    {
         adc+=((float)ADC_Read(0));
         delay_us(20);
    }
    adc=adc>>6;
    return adc;
}

void temp_display()
{
    register unsigned long conv=0;
    unsigned char ch=0;
    t=((adc_avg())*48.9);
    temp=(t*0.01);
    conv=t;
    ch=(conv/1000);
    Lcd_Chr(2,1,(48+ch));
    ch=((conv/100)%10);
    Lcd_Chr_CP((48+ch));
    Lcd_Chr_CP(46);
    ch=(conv/10)%10;
    Lcd_Chr_CP(48+ch);
    ch=(conv)%10;
    Lcd_Chr_CP(48+ch);
    Lcd_Out_CP("'C");
    Delay_ms(100);
}

void settings()
{
     Lcd_Cmd(_LCD_CLEAR);
     read_memory();
     
     if(h||c)
     {
             lcd_out(1,1,"Reset Alarm?      ");
             lcd_out(2,1,"Up=Yes   Down=No");
             do
             {
                 if(scan_keys()==2)
                 {
                     c=0;
                     h=0;
                     break;
                 }
                 if(scan_keys()==3)
                 {
                     break;
                 }
             }while(1);
     }
     Lcd_Cmd(_LCD_CLEAR);
     delay_ms(500);

     lcd_out(1,1,"Settings Step 1/3     ");
     lcd_out(2,1,"High Temp. Limit:");
     lcd_out(3,4,"'C");
     t_high = inc_dec(t_high,99,0,1,3);
     if((t_high>=0)&&(t_high<=99))
     {
           eeprom_write(ee_t_high,t_high);
           Lcd_Cmd(_LCD_CLEAR);
     }
     delay_ms(500);
     lcd_out(1,1,"Settings Step 2/3");
     lcd_out(2,1,"Low Temp. Limit:");
     lcd_out(3,4,"'C");
     t_low=inc_dec(t_low,99,0,1,3);
     if(t_low>=0 && t_low<=99)
     {
           eeprom_write(ee_t_low,t_low);
           Lcd_Cmd(_LCD_CLEAR);
     }
     delay_ms(500);
     lcd_out(1,1,"Settings Step 3/3");
     lcd_out(2,1,"No. of passes:  ");
     pass_times=inc_dec(pass_times,99,0,1,3);
     if(pass_times>=0 && pass_times<=99)
     {
           eeprom_write(ee_pass_times,pass_times);
           Lcd_Cmd(_LCD_CLEAR);
     }
     delay_ms(500);
     pass_times=(eeprom_read(ee_pass_times));
     t_high=(eeprom_read(ee_t_high));
     t_low=(eeprom_read(ee_t_low));
     t_delta=(((t_high-t_low)/2));
     eeprom_write(ee_t_delta,t_delta);
     delay_ms(100);
}


signed int inc_dec(signed int variable,signed int max,signed int min,unsigned char x,unsigned char y)
{
     do
     {
         display_common(x,y,variable);
         if(scan_keys()==2)
         {
               variable+=1;
         }
         if(scan_keys()==3)
         {
                variable-=1;
         }
         if(variable>max)
         {
                 variable=min;
         }
         if(variable<min)
         {
                 variable=max;
         }
         if(scan_keys()==4)
         {
                  return variable;
         }
         if(scan_keys()==1)
         {
                  return (max+1);
         }
     }while(1);
}

void display_common(unsigned char x,unsigned char y,unsigned char convert)
{
    unsigned char t = 0;
    t=(convert/10);
    Lcd_Chr(y,x,(48+t));
    t=(convert%10);
    Lcd_Chr(y,(++x),(48+t));
}

void compare_temp()
{
     if(temp>=t_high)
     {
         Lcd_Out(3,1,"High Temperature!");
         controller_state(1);
     }
     if(temp<=t_low)
     {
         Lcd_Out(3,1,"Low Temperature! ");
         controller_state(2);
     }
     if(((temp<t_high)&&temp>=(t_high-t_delta))||((temp>t_low)&&temp<(t_delta+t_low)))
     {
         Lcd_Out(3,1,"Within Limit.    ");
         controller_state(0);
     }
}


void controller_state(unsigned short state)
{
     if(state==1)
     {
         if(c==0)
         {
                  heater=0;
                  cooler=1;
                  check_fault(1);
         }
     }
     else if(state==2)
     {
         if(h==0)
         {
                 heater=1;
                 cooler=0;
                 check_fault(2);
         }
     }
     else
     {
         heater=0;
         cooler=0;
     }
}


void check_fault(unsigned short stat)
{
     if(stat==1)
     {
          pass++;
          if((temp>=t_high)&&(pass==(pass_times*10)))
          {
              Fault_C=1;
              c=1;
              heater=0;
              cooler=0;
              pass=0;
          }
          if((temp<=(t_high-t_delta))&&(pass==(pass_times*10)))
          {
             heater=0;
             cooler=0;
             c=0;
             pass=0;
          }
     }
     if(stat==2)
     {
          pass++;
          if((temp<=t_low)&&(pass==(pass_times*10)))
          {
              Fault_H=1;
              h=1;
              heater=0;
              cooler=0;
              pass=0;
          }
          if((temp>(t_low+t_delta))&&(pass==(pass_times*10)))
          {
             heater=0;
             cooler=0;
             h=0;
             pass=0;
          }
     }
     delay_ms(100);
}


void read_memory()
{
     pass_times=(eeprom_read(ee_pass_times));
     delay_ms(30);
     t_high=(eeprom_read(ee_t_high));
     delay_ms(30);
     t_low=(eeprom_read(ee_t_low));
     delay_ms(30);
     if(pass_times>99)
     {
          eeprom_write(ee_pass_times, 45);
          delay_ms(30);
          pass_times=(eeprom_read(ee_pass_times));
          delay_ms(30);
     }
     if(t_high>99)
     {
          eeprom_write(ee_t_high, 40);
          delay_ms(30);
          t_high=(eeprom_read(ee_t_high));
          delay_ms(30);
     }
     if(t_low>99)
     {
          eeprom_write(ee_t_low, 20);
          delay_ms(30);
          t_low=(eeprom_read(ee_t_low));
          delay_ms(30);
     }
     t_delta=(((t_high-t_low)/2));
     eeprom_write(ee_t_delta,t_delta);
     delay_ms(30);
}


void fault_messages()
{
          if((h==0) && (c==0))
          {
                   Lcd_Out(4,1,"System Okay.             ");
                   Fault_C=0;
                   Fault_H=0;
          }
          if((h==1) || (c==1))
          {
                   Sound_Play(550,150);
                   if((h==1) && (c==0))
                   {
                           Lcd_Out(4,1,"Alarm! Heater Fault.");
                           delay_ms(600);
                   }
                   else if((h==0) && (c==1))
                   {
                           Lcd_Out(4,1,"Alarm! Cooler Fault.");
                           delay_ms(600);
                   }
                   else if((h==1) && (c==1))
                   {
                            Lcd_Out(4,1,"System Failed.      ");
                            delay_ms(600);
                   }
          }
}


void settings_demanded()
{
          if(scan_keys()==1)
          {
              delay_ms(9);
              while(scan_keys()==1);
              settings();
          };
}


void all_tasks()
{
          Lcd_Out(1,1,"Active Temperature: ");
          temp_display();
          fault_messages();
          settings_demanded();
          compare_temp();
}