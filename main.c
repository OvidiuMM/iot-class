#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <math.h>
#include <unistd.h>
#include <fcntl.h>
#include "temphum.h"
#include "blinkie.h"


int main()
{

SENSOR sens;
sens.fichero="/dev/i2c-1";
sens.fd=0;
sens.temp=0;
sens.hum=0;

while (1){
if (start_inquire(&sens))
{print_status(&sens);}
else {
 printf("Status is : bad");
}
printf ("Raspberry Pi blink\n") ;

  wiringPiSetupGpio() ;
  pinMode (RED_LED, OUTPUT) ;
  pinMode (RED_RGB,OUTPUT);
  pinMode (GREEN_RGB,OUTPUT);
  pinMode (BLUE_RGB,OUTPUT);

    led_up(RED_LED);	// On
    delay (500) ;		// mS
    led_off(RED_LED) ;	// Off


   rgb_all_off();
    delay(1500);
    led_up(RED_RGB);
    delay(1500);

     led_off(RED_RGB);

    rgb_all_off();
    delay(1500);
    led_up(GREEN_RGB);

    delay(1500);
    digitalWrite(RED_LED,LOW);

    rgb_all_off();
       delay(1500);
   led_up(BLUE_RGB);

  }


return 0;
}



