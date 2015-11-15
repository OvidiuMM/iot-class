#include "blinkie.h"

//vars
//#define	LED	17
//#define red_led 25
//#define green_led 27
//#define blue_led 22
//
//#define 5_per_freq 1
//#define 50_per_freq 10
//#define 90_per_freq 18
//
//
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
