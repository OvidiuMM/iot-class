#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>

// LED Pin - wiringPi pin 0 is BCM_GPIO 17.
void red_on();
void red_off();

void rgb_on();
void rgb_off();
void rgb_pwm();
void led_up(int led);


//vars
#define	LED	17
#define red_led 25
#define green_led 27
#define blue_led 22


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

void led_up(int led){
int i;
for ( i=0; i < 256; i= i +1 ){
    delay(4);
    //digitalWrite(led,i);
    digitalWrite(led,i);
}
}

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


