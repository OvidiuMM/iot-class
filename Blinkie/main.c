#include <stdio.h>
#include <wiringPi.h>
#include <time.h>
#include <sys/timeb.h>
#include "blinkie.h"


int main (void)
{
  printf ("Raspberry Pi blink\n") ;

  wiringPiSetupGpio() ;
  pinMode (LED, OUTPUT) ;
  pinMode (red_led,OUTPUT);
  pinMode (green_led,OUTPUT);
  pinMode (blue_led,OUTPUT);


  for (;;)
  {
    red_on();	// On
    delay (500) ;		// mS
    red_off() ;	// Off
    delay (500) ;

    rgb_pwm();

  }



  return 0 ;
}

