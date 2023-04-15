#define LIDAR_address                  0xC4


void LIDAR_write(unsigned char address, unsigned char value);
unsigned char LIDAR_read_byte(unsigned char address);
unsigned int LIDAR_read_word(unsigned char address);
unsigned int LIDAR_get_distance();