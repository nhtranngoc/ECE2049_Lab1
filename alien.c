/*
 * alien.c
 *
 *  Created on: Sep 14, 2015
 *      Author: nhtranngoc
 */

#include "alien.h"

//-------------ALIENS--FUNCTIONS------------------------
int lookForAlien(int column){ //Return lowest position on a row
	//Iterate through the column and return position of the lowest alien in column
	int i, lowest;
	for (i=3; i>=0; i--){
		if((gameGrid[column][i] == 1) && (i >= lowest)){ //Check if there's an alien
			lowest=i;
		}
		else lowest=-1;
	}
	return lowest;

}

void killAlien(int col){
	//Remove lowest alien in array.
	if(col == -1) return;
    int i;
    for (i = 3; i >= 0; i--)
    {
        if (gameGrid[col][i] != 0)
        {
            gameGrid[col][i] = 0;
            clickSound();
            return;
        }
    }
}

void generateAlien(int numAlien){
	int i,j;
	alienLeft=numAlien;
	for(i=0;i<6;i++){			//Not making the loop customizable to gameGrid cause I'm lazy.
		for(j=0;j<5;j++){
			if(!(alienLeft == 0)){
				gameGrid[i][j]=rand()%2; //Fill in gameGrid with random 0s and 1s
				if(gameGrid[i][j]==1) {
//					generatedAlien++;
					alienLeft--;
				}
			}
		}
	}
}

int renderAlien(){
	int i,j, xCoord, yCoord, sumAlien=0;
	for(i=0;i<5;i++){
		for(j=0;j<4;j++){
			if(gameGrid[i][j] == 1){ //If there's an alien at that position
				sumAlien++;
				xCoord = 5 + i*19;
				yCoord = j*12 + alienHeight;
			    GrImageDraw(&g_sContext, &SPACEINVADER_11x8, xCoord, yCoord);
			    //@TODO: Fix deadLine
			    if (yCoord >= 60) return 1;
			}
		}
	}
	if (sumAlien == 0) return 2;
	return 0;
}
