/*
 * sound.c
 *
 *  Created on: Sep 12, 2015
 *      Author: nhtranngoc
 */
#include "sound.h"

void introSound(){
    playBuzzer(110);
    swDelay(1);
    playBuzzer(150);
    swDelay(1);
    playBuzzer(100);
    swDelay(1);
    playBuzzer(140);
    swDelay(1);
    playBuzzer(80);
    swDelay(1);
    playBuzzer(50);
    swDelay(1);
    BuzzerOff();
}

void clickSound(){
	playBuzzer(30);
	volatile unsigned int i=5000;		// volatile to prevent optimization by compiler
   	while (i > 0) i--;
	BuzzerOff();
}

void winSound(){
    playBuzzer(50);
    swDelay(1);
    playBuzzer(45);
    swDelay(1);
    playBuzzer(30);
    swDelay(1);
    playBuzzer(35);
    swDelay(1);
    playBuzzer(30);
    swDelay(1);
    playBuzzer(25);
    swDelay(1);
    BuzzerOff();
}

void loseSound(){
    playBuzzer(100);
    swDelay(1);
    playBuzzer(105);
    swDelay(1);
    playBuzzer(110);
    swDelay(1);
    playBuzzer(115);
    swDelay(1);
    playBuzzer(120);
    swDelay(1);
    playBuzzer(125);
    swDelay(1);
    BuzzerOff();
}

void playBuzzer(int freq){ //Using code from buzzerOn() in peripherals.c
// Initialize PWM output on P7.5, which corresponds to TB0.3
	P7SEL |= BIT5; // Select peripheral output mode for P7.5
	P7DIR |= BIT5;

	TB0CTL  = (TBSSEL__ACLK|ID__1|MC__UP);  // Configure Timer B0 to use ACLK, divide by 1, up mode
	TB0CTL  &= ~TBIE; 						// Explicitly Disable timer interrupts for safety

	// Now configure the timer period, which controls the PWM period
	// Doing this with a hard coded values is NOT the best method
	// I do it here only as an example. You will fix this in Lab 2.
	TB0CCR0   = freq; 					// Set the PWM period in ACLK ticks
	TB0CCTL0 &= ~CCIE;					// Disable timer interrupts

	// Configure CC register 3, which is connected to our PWM pin TB0.3
	TB0CCTL3  = OUTMOD_7;					// Set/reset mode for PWM
	TB0CCTL3 &= ~CCIE;						// Disable capture/compare interrupts
	TB0CCR3   = TB0CCR0/2; 					// Configure a 50% duty cycle
}

