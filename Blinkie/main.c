#include <stdio.h>
#include <wiringPi.h>
#include <time.h>
#include <sys/timeb.h>
#include "blinkie.h"



int main (void)
{
  printf ("Raspberry Pi blink\n") ;

  wiringPiSetupGpio() ;
  pinMode (RED_LED, OUTPUT) ;
  pinMode (RED_RGB,OUTPUT);
  pinMode (GREEN_RGB,OUTPUT);
  pinMode (BLUE_RGB,OUTPUT);


  for (;;)
  {
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



  return 0 ;
}

