#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <math.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <sys/types.h>
#include <pthread.h>
#include <geniePi.h>  //the ViSi-Genie-RaspPi library

#include "temphum.h"
#include "blinkie.h"

//***FUNCTIONS DEC.****//
//red led on when temp>x
int alarm_led_switch();
//rgb led on
int rgb_led_managemente(int hum_perc);
//if hum < 40% red led flashing
//if 70%> hum > 40% green led flashing
//if hum > 70% blue led flashing

void system_management(SENSOR *sens);

int handleGenieEvent(struct genieReplyStruct * reply);

void err_f(char mess[]);
void write_string(char mess[]);
//***FUNCTIONS DEF.****//

void err_f(char mess[]){
    printf("ERROR\n");
    puts(mess);
    write_string(mess);
    exit 1;
}

void write_string(char mess[]){

genieWriteStr(0x01, mess); //write to Strings0
}

int alarm_led_switch(){

    led_off(RED_LED) ;	// Off
    delay (500) ;		// mS
    led_up(RED_LED);	// On
}

//rgb led on
int rgb_led_managemente(int hum_perc){

//if hum < 40% red led flashing
//if 70%> hum > 40% green led flashing
//if hum > 70% blue led flashing
rgb_all_off();
if (hum_perc < 40){

 led_up(RED_RGB);
}
else if (hum_perc < 70)
{
     led_up(GREEN_RGB);
}
else{
    led_up(BLUE_RGB);
}

}

//This a thread for writing to the cool gauge. The value of
//the cool gauge will change from 0 to 99 and then from 99 to 0.
//This process repeats forever, running in parallel with the main.
static void *handleKnob(void *data)
{
  int gaugeVal = 0;   //holds the value of the cool gauge
  int step = 1;       //increment or decrement value, initialized to 1.

  for(;;)             //infinite loop
  {
    //write to Coolgauge0
    genieWriteObj(GENIE_OBJ_COOL_GAUGE, 0x00, gaugeVal);
    usleep(10000);    //10-millisecond delay
    printf("Thread Program is running.\n");
    gaugeVal += step; //increment or decrement

    if(gaugeVal == 99)	step = -1;
    if(gaugeVal == 0)	step = 1;
  }
  return NULL;
}

//This is the event handler. Messages received from the display
//are processed here.
int handleGenieEvent(struct genieReplyStruct * reply)
{
  if(reply->cmd == GENIE_REPORT)    //check if the cmd byte is a report event
  {
    if(reply->object == GENIE_OBJ_KNOB) //check if the object byte is that of a slider
      {
        if(reply->index == 0)		  //check if the index byte is that of Slider0
          //write to the LED digits object
          //genieWriteObj(GENIE_OBJ_LED_DIGITS, 0x00, reply->data);
          return replay->data;
      }
  }

  //if the received message is not a report event, print a message on the terminal window
  else
    printf("Unhandled event: command: %2d, object: %2d, index: %d, data: %d \r\n", reply->cmd, reply->object, reply->index, reply->data);

    replay 0;
}


void system_management(SENSOR *sens){


/*Screen 1*/

//Temperature: Displays the temperature measurement obtained from the sensor.
//Angularmeter0

//Humidity: Displays the %HR obtained from the sensor.
//Meter0

//Knob: Sets the threshold. If temperature is over the threshold the Alarm LED will be on.
//Knob0

//Alarm LED: The temperature is above the threshold.
//Userled0



/*Screen 2*/

//Clock: Displays the time in hours, minutes and seconds.
//Leddigits0 && Leddigits1

//Message: Displays the temperature and humidity in text format.
//Strings1


  pthread_t myThread;              //declare a thread
  struct genieReplyStruct reply ;  //declare a genieReplyStruct type structure
  int threshold_val=0;
  char c_temp[];
  char c_hum[];
  char* data;

  //print some information on the terminal window
  printf("\n\n");
  printf("Ovidiu assignment for IoT class\n");
  printf("==================================\n");
  printf("Program is running. Press Ctrl + C to close.\n");

  //first inquier of the sensor
  if (start_inquire(&sens)) {print_status(&sens);}
  else { err_f("Can't recover temperature and humidity data");}

  //open the Raspberry Pi's onboard serial port, baud rate is 115200
  //make sure that the display module has the same baud rate
  genieSetup("/dev/ttyAMA0", 115200);

  //start the thread for writing to the cool gauge
  (void)pthread_create (&myThread,  NULL, handlKnob, NULL);


  for(;;)                         //infinite loop
  {
  printf("Program is running.\n");
  sens_inquire(&sens);
    while(genieReplyAvail())      //check if a message is available
    {
      genieGetReply(&reply);      //take out a message from the events buffer
      if (threshold_val = handleGenieEvent(&reply))   //call the event handler to process the message
      {
        if (sens->temp >= threshold_val)
        {
            //activate alerm red led
            genieWriteObj(GENIE_OBJ_USER_LED, 0x00,1)
        }
        else
        {
            //deactivate alerm red led
            genieWriteObj(GENIE_OBJ_USER_LED, 0x00,0)

        }
      }
    }
    //update all the others visual elements


/*Screen 1*/

//Temperature: Displays the temperature measurement obtained from the sensor.
//Angularmeter0
genieWriteObj(GENIE_OBJ_ANGULAR_METER,0x00,sens->temp);

//Humidity: Displays the %HR obtained from the sensor.
//Meter0
genieWriteObj(GENIE_OBJ_METER,0x00,sens->hum);

/*Screen 2*/

//Clock: Displays the time in hours, minutes and seconds.
//Leddigits0 && Leddigits1
int hour_min=(localtime(time(NULL))->tm_hour *100)+ localtime(time(NULL))->tm_min;

genieWriteObj(GENIE_OBJ_LED_DIGITS,0x00,hour_min);
genieWriteObj(GENIE_OBJ_LED_DIGITS,0x01,localtime(time(NULL))->tm_sec);

//Message: Displays the temperature and humidity in text format.
//Strings1
/*c_temp[]="Temperature is ";
  char c_hum[]=" Humidity is";



  data=malloc((strlen(c_temp)+))
  */
  sprintf(data,"Temperature is: %f \n Humidity is: %f",sens->temp,sens->hum);
  write_string(data);

    usleep(10000);                //10-millisecond delay.Don't hog the
  }	                          //CPU in case anything else is happening
  return 0;


}

int main()
{
/* REQUIRENMETS
Measurement of temperature and humidity using an HIH-6120-021-001 I2C sensor form Honeywell.
· A red LED will be ON when temperature exceeds a threshold. A RGB LED indicates the range of the
relative humidity.
· Implementation of the HMI using a touch screen. The touch screen is the uLCD-43PT-PI from 4D
Systems.
· The system should be autonomous in the sense that it doesn’t need user intervention for booting
or starting the applications. Once you apply the power supply it must boots and starts the
operation.
· The system has to be connected to an Ethernet/TCP-IP based network allowing the developer to
interact with it.
· The system must be implemented using CodeBlocks with the exception of the software used in the
Windows platforms for the HMI design.
*/

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

  /*wiringPiSetupGpio() ;
  pinMode (RED_LED, OUTPUT) ;
  pinMode (RED_RGB,OUTPUT);
  pinMode (GREEN_RGB,OUTPUT);
  pinMode (BLUE_RGB,OUTPUT);
*/
connect_leds();
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



