#define Read_ROM                    0x33
#define Convert_Temperature         0x44
#define Copy_Scatchpad              0x48
#define Write_Scatchpad             0x4E
#define Match_ROM                   0x55
#define Read_Power_Supply           0xB4
#define Recall_EE                   0xB8
#define Read_Scatchpad              0xBE
#define Skip_ROM                    0xCC
#define Alarm_Seach                 0xEC
#define Search_ROM                  0xF0

#define DS18B20_pin                 0x05


signed int get_temp();