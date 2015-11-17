

#ifndef blinkie_h
#define blinkie_h

#include <stdio.h>
#include <wiringPi.h>
#include <time.h>
#include <sys/timeb.h>



void rgb_all_off();
void led_up(int pin);
void led_off(int pin);
void connect_leds();

//consts
#define	RED_LED	17
#define RED_RGB 25
#define GREEN_RGB 27
#define BLUE_RGB 22

#endif
