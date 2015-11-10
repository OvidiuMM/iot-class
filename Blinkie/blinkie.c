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
 void red_on(){
  digitalWrite (LED, HIGH) ;	// On

 }
void red_off(){

    digitalWrite (LED, LOW) ;	// Off

}

void rgb_on(){

}
void rgb_off(){
    digitalWrite(red_led,LOW);
    digitalWrite(green_led,LOW);
    digitalWrite(blue_led,LOW);
}

void rgb_pwm()
{
    rgb_off();
    delay(500);
    led_up(red_led);

    rgb_off();
    delay(500);
    led_up(green_led);

    rgb_off();
    delay(500);
    led_up(blue_led);

}

void make_pwm(int led){

//obtain the actual time(second)
time_t start_t = time(0);
struct timeb start_time_mili;
struct timeb new_time_mili;
ftime (&start_time_mili);

//time_t end_t = time(NULL);
int counter=0;

while ((time (0) - start_t ) < 1)
{
	//if counter value goes above 20 (21) reset it
	if (counter > 20)
	{
		counter = 0;
	}
	
	counter=counter+1;

//get the actual time in millisecconds
	ftime(&new_time_mili);
//get the time elapsed since method was called
	int time_lapsed= (new_time_mili.millitm - start_time_mili.millitm) * 1000 ;

// wiringPi frequency is ~ 4.1MHz ~ 4100000 clock cicles / second
// it will be reduced due to math operations

//      #from 0 to 5% don't do nothing
if ( time_lapsed  < 5)
{
digitalWrite(led,LOW);

//led is off
}

//      #from 5% to 50% freq is 1/20

else if ( time_lapsed < 50)
{

if ((counter * 5_per_frez / 20 ) = 1)
 {
digitalWrite(led,i);
}
	
//      #from 50% to 90% freq is 10/20
}
else if ( time_lapsed < 90)
{
if (((counter * 50_per_frez) % 2 ) = 1)
 {
digitalWrite(led,i);
}


}
//      #from 90 to 100% freq is 18/20
else if ( time_lapsed < 100)
{
 if ((counter / 90_per_frez) > 1)
{
digitalWrite(led,i);
} 
}

	
}
}

void led_up(int led){
    digitalWrite(led,i);
}

