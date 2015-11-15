#ifndef temphum_h
#define temphum_h

#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <math.h>
#include <unistd.h>
#include <fcntl.h>

#define DEVICE_ADDRESS 0x27

/********fuctions definitions***/
int check_sensor(int file, char *fichero);
void read_request(int file, unsigned char buf[10]);
unsigned char *sensor_data(int file, unsigned char buf[10] );

float get_humidity(unsigned char seis_h, unsigned char ocho_h);
float get_temperature(unsigned char ocho_t, unsigned char seis_t);
void close_connection(int file, char *fichero);

#endif
