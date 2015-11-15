#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <math.h>
#include <unistd.h>
#include <fcntl.h>
//#include "temphum.h"

#define DEVICE_ADDRESS 0x27


//****vars defintion****
//structure that will hold  sensor data
struct temp_hum{
char *fichero;
int fd;
unsigned char buf[10];
float temp,hum;
};
//for ease of use a typedef is defined
typedef struct temp_hum SENSOR;

/********fuctions definitions***/
int start_inquire(SENSOR *sens);
int sens_inquire(SENSOR *sens);
void print_status(SENSOR *sens);
int check_sensor(int file, char *fichero);
void read_request(int file, unsigned char buf[10]);
unsigned char *sensor_data(int file, unsigned char buf[10] );

float get_humidity(unsigned char seis_h, unsigned char ocho_h);
float get_temperature(unsigned char ocho_t, unsigned char seis_t);
void close_connection(int file, char *fichero);
