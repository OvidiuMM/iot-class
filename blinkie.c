#include "blinkie.h"


 void rgb_all_off(){
    digitalWrite(RED_RGB,LOW);
    digitalWrite(GREEN_RGB,LOW);
    digitalWrite(BLUE_RGB,LOW);
}

void led_up(int pin){
    digitalWrite(pin,HIGH);
}

void led_off(int pin)
{
digitalWrite(pin,LOW);
}

void connect_leds(){
 wiringPiSetupGpio() ;
  pinMode (RED_LED, OUTPUT) ;
  pinMode (RED_RGB,OUTPUT);
  pinMode (GREEN_RGB,OUTPUT);
  pinMode (BLUE_RGB,OUTPUT);

}
