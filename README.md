# README #

### What is this repository for? ###
* Simple temperature and humidity app with display
* IoT class assignment
* Version 0.9


### How do I get set up? ###
* raspberrypi B+, HIH-6120-021-001 sensor & 4d Systems uLCD-43PT
* red and RGB led

* Summary of set up
  Connect all the hardware using a circuit board.
  For the display connection follow the instructions.
  Clone repo to /usr/local/

* Configuration
  In order to use the leds connect them to this GPIO pins:
  define RED_LED 17
  define RED_RGB 25
  define GREEN_RGB 27
  define BLUE_RGB 22

* Dependencies
  The following libraries must be installed:
  The ViSi-Genie-RaspPi library (https://github.com/4dsystems/ViSi-Genie-RaspPi-Library)
  The WiringPi library (http://wiringpi.com/download-and-install/)

* How to run tests
  No test suite defined

* Deployment instructions
  Start/stop/save logs using appmanager.sh script (se usage function)
  Note: you can add this script to /etc/rc.local in order to launch it at startup

### Contribution guidelines ###

* see contributors file

### Who do I talk to? ###

* ovidiu5891@gmail.com