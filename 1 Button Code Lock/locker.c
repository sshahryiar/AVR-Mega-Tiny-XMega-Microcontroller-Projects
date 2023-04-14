#define key        PIND0_bit
#define lock       PORTD1_bit
#define rly        PORTD2_bit
#define confirm    PORTB7_bit

#define dly        600


bit lock_flag;
bit key_press;
bit unlocked;
unsigned short i = 0, s = 0, k = 0;
unsigned short set_code[3];
unsigned short pass[3];


const unsigned char digits[15] =
{
    0x3F,       // 0
    0x06,       // 1
    0x5B,       // 2
    0x4F,       // 3
    0x66,       // 4
    0x6D,       // 5
    0x7D,       // 6
    0x07,       // 7
    0x7F,       // 8
    0x6F,       // 9
    0x79,       // E - Enter code
    0x3E,       // U - Unlocked with success
    0x39,       // C - Change code
    0x71,       // F - Failed
    0x38        // L - Locked
};


void setup_MCU();
void get_set_code();
void get_status();
void perform_operations();
void get_password();
void change_password();
void change_msg();


void main()
{
    setup_MCU();
    for(;;)
    {
        get_status();
        perform_operations();
    }
}


void setup_MCU()
{
    lock_flag = 0;
    key_press = 0;
    unlocked = 0;
    get_set_code();
    DDRB = 0xFF;
    DDRD = 0x06;
    lock = 0;
    rly = 0;
    PORTB = 0xFF;
    delay_ms(500);
    PORTB = 0x00;
    delay_ms(500);
}


void get_set_code()
{
    for(s=0;s<3; s++)
    {
        pass[s] = eeprom_read((0x0007 + s));
        delay_ms(10);
    }
    if(pass[0] > 9 || pass [1] > 9 || pass[2] > 9)
    {
           eeprom_write(0x0007, 1);
           delay_ms(10);
           eeprom_write(0x0008, 2);
           delay_ms(10);
           eeprom_write(0x0009, 3);
           delay_ms(10);
    }
}


void get_status()
{
    if(lock_flag == 0)          //locked
    {
        lock = 0;
        rly = 0;
        PORTB = (digits[14]);
    }
    if(lock_flag == 1)         //unlocked
    {
       lock = 1;
       rly = 1;
       PORTB = (digits[11]);
    }
}


void perform_operations()
{
    if(key && (unlocked == 1))
    {
       delay_ms(20);
       if(key)
       {
            unlocked = 0;
            lock_flag = 0;
            get_status();
            delay_ms(500);
       }
    }
    if(key && (key_press == 0))
    {
        delay_ms(20);
        if(key)
        {
            delay_ms(500);
            if(key)
            {
                change_msg();
                change_password();
                change_msg();
            }
            PORTB = (digits[10]);
            delay_ms(1000);
            key_press = 1;
        }
        else
        {
            key_press = 0;
        }
    }
    if(key_press == 1)
    {
        PORTB = 0x00;
        delay_ms(500);
        get_password();
        key_press = 0;
    }
}


void get_password()
{
    for(s=0; s<3; s++)
    {
        for(i=0; i<=9; i++)
        {
            PORTB = (digits[i]);
            delay_ms(dly);
            if(key)
            {
               set_code[s] = i;
               confirm = 1;
               while(key);
               confirm = 0;
               k++;
            }
        }
        delay_ms(200);
    }
    get_set_code();
    delay_ms(10);
    if((set_code[0] == pass [0]) && (set_code[1] == pass [1]) && (set_code[2] == pass [2] && k == 3))
    {
        lock_flag = 1;
        unlocked = 1;
        k = 0;
    }
    else
    {
        lock_flag = 0;
        for(s=0;s<4;s++)
        {
            PORTB = (digits[13]);
            delay_ms(400);
            PORTB = 0x00;
            delay_ms(400);
            k = 0;
        }
    }
}


void change_password()
{

    for(s=0; s<3; s++)
    {
        for(i=0; i<=9; i++)
        {
            PORTB = (digits[i]);
            delay_ms(dly);
            if(key)
            {
               set_code[s] = i;
               confirm = 1;
               while(key);
               confirm = 0;
               k++;
            }
        }
        delay_ms(200);
    }
    get_set_code();
    delay_ms(10);
    if((set_code[0] == pass [0]) && (set_code[1] == pass [1]) && (set_code[2] == pass [2] && k == 3))
    {
        k = 0;
        change_msg();
        for(s=0; s<3; s++)
        {
            for(i=0; i<=9; i++)
            {
                PORTB = (digits[i]);
                delay_ms(dly);
                if(key)
                {
                  eeprom_write((0x0007 + s), i);
                   delay_ms(10);
                   confirm = 1;
                   while(key);
                   confirm = 0;
                   k++;
                }
            }
            delay_ms(200);
        }
        if(k == 3)
        {
            k = 0;
        }
        else
        {
            for(s=0;s<3; s++)
            {
                pass[s] = eeprom_read((0x0007 + s));
                delay_ms(10);
                eeprom_write((0x0007 + s), pass[s]);
                delay_ms(20);
            }
            k = 0;
        }
    }
    else
    {
        for(s=0;s<4;s++)
        {
            PORTB = (digits[13]);
            delay_ms(400);
            PORTB = 0x00;
            delay_ms(400);
            k = 0;
        }
    }
}


void change_msg()
{
    unsigned short fl = 0;
    PORTB = 0x00;
    for(fl=1; fl<4; fl++)
    {
        PORTB = 0x00;
        delay_ms(300);
        PORTB = (digits[12]);
        delay_ms(300);
    }
}