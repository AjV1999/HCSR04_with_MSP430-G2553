# HCSR04_with_MSP430-G2553
This is an Embedded-C based program module to interface the HCSR04 Ultrasonic module with the MSP430-G2553 microcontroller developed by Texas Instruments.

The HC-SR04 ultrasonic sensor is a simple senor with 4 pins:
1)	Vcc : +5V DC input; 
2)	Trig: Trigger input to emit ultrasound wave
3)	Echo: Echo output from sensor when the reflected wave is received
4)	GND: Ground of the sensor

We also setup an LCD display to display the distance measured using our sensor setup with our microcontroller.

The ultrasonic sensor uses sonar waves to estimate the distance. When the trigger input is high from the microcontroller the sensor emits a sound wave and the wave reflected back when received by the sensor now turns the echo input high. The time between transmission and reception of the signal allows to calculate the distance to an object using the velocity of sound in air and a simple distance formula:

						S = (V x t)/2
            
Here S is distance, V is speed and t is the time taken by the sound wave. The distance is divided by 2 to account for time taken to travel to and from the object.

