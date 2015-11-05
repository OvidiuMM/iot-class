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

/*******functions*****/

/*FUnction that checks sensor bus and file access
* takes file descriptor and file path&bame
**/
int check_sensor(int file, char *fichero){

 if ((file = open(fichero, O_RDWR)) < 0)
    {
        /*ERROR*/
        perror("Failed to open i2c bus!\n");
        exit(1);
    }
else{
    printf("Succesful bus access.\n");
}

 if (ioctl(file, I2C_SLAVE, DEVICE_ADDRESS) < 0){
    perror("Failed to axquire bus acces and talk to slave! \n");
    exit(1);
    }
    else{
    printf("Succesful file access. \n");

    }

return file;
}

/*Function that writes the read bit
*
**/
void read_request(int file, unsigned char buf[10] ){
if ((write(file, buf, 1)) != 1) {							// Send register we want to read from
		printf("Error writing to i2c slave\n");
		exit(1);
	}
}

/*Function that reads the data recived
*
**/
unsigned char *sensor_data(int file,unsigned char buf[10] ){
if (read(file, buf, 4) != 4) {						// Read back data into buf[]
		printf("Unable to read from slave\n");
		exit(1);
	}

	/*else {
	unsigned char highByte = buf[2];
		unsigned char lowByte = buf[3];
		unsigned int result = (highByte <<8) + lowByte;			// Calculate bearing as a word value
		printf("Software v: %u \n",buf[0]);
		printf("Bearing as byte: %u \n",buf[1]);
		printf("Bearing as decimal: %u.%u\n",result/10, result%10); // display bearing with decimal place
}*/
	return buf;
}

float get_humidity(unsigned char seis_h, unsigned char ocho_h){
        unsigned int result =( (seis_h <<26)>>18) + ocho_h;			// Calculate bearing as a word value
		printf("Raw humidity:%u \n",result);
        //int val=(result / ((2^14)-2) * 100);
        float val = result / (pow(2.0,14) -2) *100;
        printf("Humitidy : %f \n", val);
return val;
}


float get_temperature(unsigned char ocho_t, unsigned char seis_t){
         unsigned int result =( (ocho_t <<8) + seis_t) >> 2;			// Calculate bearing as a word value)
		printf("Raw temp: %u \n",result);
       // int val=(result / ((2^14)-2) * 165)-40;
       float val = (result / (pow(2.0,14) -2) *165)-40;
        printf("Temp : %f \n", val);
        return val;
}

/**Close connection to sensor (file)
**/
void close_connection(int file, char *fichero){

if (close(file)<0){
printf("Unable to close slave\n");
		exit(1);
}

}
int main()
{

//vars defintion
char *fichero= "/dev/i2c-1";
int fd =0;
unsigned char buf[10];
float temp=0;
float hum=0;

//start device checking
fd=check_sensor(fd, fichero);

int repet=1;
//if this process must be repeated
while (repet=1){
//ask for data

buf[0]=0;
read_request(fd,buf);

sensor_data(fd,buf);

//Check data
unsigned int read_status = buf[0]>>6;

if (read_status >1)
{

    printf("Status is : %i", read_status);

    }
    else{
if (read_status = 1){
    printf("Status is : %i so it has been already fetched", read_status);

}
//parse data

hum=get_humidity(buf[0],buf[1]);
temp=get_temperature(buf[2],buf[3]);


/*int counter=0;
while (counter < 5){
printf("buf %i is equal to : %c", counter, buf[counter]);
counter= counter+1;
}
*/
//store and represent humidity and temperature information
//TODO:
sleep(2);
}
//while closure
}

//if needed this closes the connection
//->close_connection(fd,buf);
return 0;
}
