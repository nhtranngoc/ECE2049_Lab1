/*
 * alien.h
 *
 *  Created on: Sep 14, 2015
 *      Author: nhtranngoc
 */

#ifndef ALIEN_H_
#define ALIEN_H_

#include <stdint.h>
#include <stdlib.h>
#include "grlib.h"
#include "LcdDriver/Dogs102x64_UC1701.h"
#include "peripherals.h"
#include "images.h"
#include "sound.h"

//int millisecLeft= 100; //Starts at 5 second for each pixel lower
extern int alienHeight;
//int deadLine=0;
//int level=1;
extern int alienLeft;
extern int gameGrid[5][4];

void generateAlien(int numAlien);
void killAlien(int col);
int renderAlien();
int lookForAlien(int col);

#endif /* ALIEN_H_ */
