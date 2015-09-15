/*
 * main.h
 *
 *  Created on: Sep 12, 2015
 *      Author: nhtranngoc
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <msp430.h>
#include <stdint.h>
#include <stdlib.h>
#include "inc\hw_memmap.h"
#include "driverlibHeaders.h"
#include "CTS_Layer.h"
#include "grlib.h"
#include "LcdDriver/Dogs102x64_UC1701.h"
#include "peripherals.h"
#include "images.h"
#include "sound.h"
#include "alien.h"


// Define global variables

#define MAX_ALIEN 25

//Enumerate gameState as a type.
enum gameState {
	WELCOME,
	MENU,
	GAME_INIT,
	CHECK_BUTTON,
	WIN,
	LOSE
};

//x position would be 0 to 4 - so that there can only be 5 aliens on a row, starting from the left.
//y postition would be 0 to 3 - to there are 4 rows of aliens for a total of a 5x4 board.

int gameGrid[5][4];

unsigned int highScore=0;
int millisecLeft= 100; //Starts at 5 second for each pixel lower
int alienHeight=0;
int deadLine=0;
int level=1;
int alienLeft;

char buffer[50];

// Function prototypes for this file
void swDelay(char numLoops);
void countdown();
void initInterrupt();
void clrScr();
int checkButton();

#endif /* MAIN_H_ */
