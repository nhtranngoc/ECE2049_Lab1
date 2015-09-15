/*
 * sound.h
 *
 *  Created on: Sep 12, 2015
 *      Author: nhtranngoc
 */

#ifndef SOUND_H_
#define SOUND_H_

#include <msp430.h>
#include <stdint.h>


void playBuzzer(int freq);
void introSound();
void clickSound();
void swDelay(char numLoops);
void BuzzerOff();
void winSound();
void loseSound();

#endif /* SOUND_H_ */
