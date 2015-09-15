/* --COPYRIGHT--,BSD
 * Copyright (c) 2012, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --/COPYRIGHT--*/

/**************************************************************************************/
/* This program is an implementation of Space Invaders on MSP430F5529 EXP Board for ECE2049 A15.
 * Authors: Nam Tran Ngoc (nhtranngoc)
 * 			Julia Szemiot (jjszemiot)
 * Date: 9/9/2015
 */

#include <main.h>

void main(void){
	//Initialize interrupt
    // Variable to record button state for later
	// Stop WDT
    WDTCTL = WDTPW | WDTHOLD;		// Stop watchdog timer
    //Perform initializations (see peripherals.c)
    configTouchPadLEDs();
    configDisplay();
    configCapButtons();

    //Initialize state as a variable of type gameState. Starts at WELCOME.
    enum gameState state=WELCOME;

	/* Don't forget, you're here forever!*/
    while(1){
		switch(state){
			case WELCOME:
				initInterrupt();
				clrScr();
				GrFlush(&g_sContext);
			    // Intro Screen -- Write to the display screen
			    GrStringDrawCentered(&g_sContext, "SPACE INVADERS", AUTO_STRING_LENGTH, 51, 30, TRANSPARENT_TEXT);
			    // Refresh the display now that we have finished writing to it
			    GrFlush(&g_sContext);
			    introSound();
				state=MENU;
				break;

			case MENU:
			    GrStringDrawCentered(&g_sContext, "Press X to Start", AUTO_STRING_LENGTH, 51, 50, TRANSPARENT_TEXT);
				P1OUT |= LED8;   // turn on all 5 LEDs
			    // Refresh the display now that we have finished writing to it
			    GrFlush(&g_sContext);
			    //Check for keypress on X
			    while(checkButton() == NONE_BUTTON){ //Do nothing and wait. And wait.
			    	P1OUT &= ~(checkButton() << 1);
			    	if(checkButton() == 0){
			    		clickSound();
			    		P1OUT = 0x00;
					    GrStringDrawCentered(&g_sContext, "SPACE INVADERS", AUTO_STRING_LENGTH, 51, 30, TRANSPARENT_TEXT);
			    		countdown();
			    		P1OUT |= (LED4+LED5+LED6+LED7+LED8);   // turn on all 5 LEDs
			    		state=GAME_INIT;
			    		break;
			    	}
			    }
				break;

			case GAME_INIT:
				clrScr();
				generateAlien(5+level);
				alienHeight=0; //Reset alien Height.
				int result = renderAlien();
			    GrFlush(&g_sContext);
				state=CHECK_BUTTON;
				break;

			case CHECK_BUTTON:
				clrScr();
				killAlien(checkButton());
				result = renderAlien();
				GrFlush(&g_sContext);
				if (result == 1) state = LOSE;
				if (result == 2)state = WIN;
				break;

			case WIN: //Come back to init and makes the game harder. Heh.
				GrStringDrawCentered(&g_sContext, "U gud son", AUTO_STRING_LENGTH, 51, 30, TRANSPARENT_TEXT);
				//@TODO: Fix line kerning.
			    GrStringDrawCentered(&g_sContext, "Press X to continue", AUTO_STRING_LENGTH, 51, 50, TRANSPARENT_TEXT);
				GrFlush(&g_sContext);
			    while(checkButton() == NONE_BUTTON){ //Do nothing and wait. And wait.
			    	P1OUT &= ~(checkButton() << 1);
			    	if(checkButton() == 0){
						winSound();
			    		P1OUT = 0x00;
			    		countdown();
			    		P1OUT |= (LED4+LED5+LED6+LED7+LED8);   // turn on all 5 LEDs
			    		level++; //Add number of aliens
			    		millisecLeft-=5;
			    		state=GAME_INIT;
			    		break;
			    	}
			    }
				break;

			case LOSE:
				GrClearDisplay(&g_sContext);
				GrFlush(&g_sContext);
				GrStringDrawCentered(&g_sContext, "You got rekt m8", AUTO_STRING_LENGTH, 51, 30, TRANSPARENT_TEXT);
				//@TODO: Fix line kerning
			    GrStringDrawCentered(&g_sContext, "Press X to start over", AUTO_STRING_LENGTH, 51, 50, TRANSPARENT_TEXT);
				GrFlush(&g_sContext);

			    while(checkButton() == NONE_BUTTON){ //Do nothing and wait. And wait.
			    	P1OUT &= ~(checkButton() << 1);
			    	if(checkButton() == 0){
			    		loseSound();
			    		P1OUT = 0x00;
			    		countdown();
			    		P1OUT |= (LED4+LED5+LED6+LED7+LED8);   // turn on all 5 LEDs
			    		state=WELCOME;
			    		break;
			    	}
			    }
				break;

			default:
				//Something happened here. Let's go back.
				state=WELCOME;
				break;
	    }
    }
}

//-----------------ULTILITY FUNCTIONS-----------------------------------------

void countdown(){
	//THIS IS NOT THE RIGHT WAY TO DO IT.
	GrClearDisplay(&g_sContext);
	GrStringDrawCentered(&g_sContext, "3", AUTO_STRING_LENGTH, 51, 30, TRANSPARENT_TEXT);
	playBuzzer(40);
	GrFlush(&g_sContext);
	swDelay(2);
	BuzzerOff();
	GrClearDisplay(&g_sContext);
	GrStringDrawCentered(&g_sContext, "2", AUTO_STRING_LENGTH, 51, 30, TRANSPARENT_TEXT);
	playBuzzer(40);
	GrFlush(&g_sContext);
	swDelay(2);
	BuzzerOff();
	GrClearDisplay(&g_sContext);
	GrStringDrawCentered(&g_sContext, "1", AUTO_STRING_LENGTH, 51, 30, TRANSPARENT_TEXT);
	playBuzzer(40);
	GrFlush(&g_sContext);
	swDelay(2);
	BuzzerOff();
}

void clrScr(){
	GrClearDisplay(&g_sContext);
}

int checkButton(){
	switch(CapButtonRead()){
		case NONE_BUTTON:
			return -1;
		case X_BUTTON:
			return 0;
		case SQ_BUTTON:
			return 1;
		case OCT_BUTTON:
			return 2;
		case TRI_BUTTON:
			return 3;
		case CIR_BUTTON:
			return 4;
	}
}

void swDelay(char numLoops){
	// This function is a software delay. It performs
	// useless loops to waste a bit of time
	//
	// Input: numLoops = number of delay loops to execute
	// Output: none
	//
	// smj, ECE2049, 25 Aug 2013

	volatile unsigned int i,j;	// volatile to prevent optimization
			                            // by compiler
	for (j=0; j<numLoops; j++)
    {
    	i = 50000 ;					// SW Delay
   	    while (i > 0)				// could also have used while (i)
	       i--;
    }
}

void initInterrupt(){
	TA2CTL= TASSEL_1 + ID_1 + MC_1; //General settings: Use ACLK, Divider =1, UP mode
	TA2CCR0=327; //327 ACLK tics = ~.01 sec
	TA2CCTL0 = CCIE; //TA2CCR0 interrupt enabled

	_BIS_SR(GIE); // Global Interrupt enable
}


#pragma vector= TIMER2_A0_VECTOR //Timer interrupt to get the aliens to go down
__interrupt void Timer_A2_ISR(void){
	millisecLeft--; //Countdown
	if (millisecLeft==0){
		alienHeight++;
		millisecLeft=20;
	}
}
