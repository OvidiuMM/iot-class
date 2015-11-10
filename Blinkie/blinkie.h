#ifndef _blinkie_h
#define _blinkie_h

#include <stdio.h>
#include <wiringPi.h>
#include <time.h>
#include <sys/timeb.h>

// LED Pin - wiringPi pin 0 is BCM_GPIO 17.
void red_on();
void red_off();

void rgb_on();
void rgb_off();
void rgb_pwm();
void led_up(int led);
void make_pwm(int led);

//vars
#define	LED	17
#define red_led 25
#define green_led 27
#define blue_led 22

#define 5_per_freq 1
#define 50_per_freq 10
#define 90_per_freq 18
