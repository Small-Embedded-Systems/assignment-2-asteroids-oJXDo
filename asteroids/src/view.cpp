/* Asteroids view
		Handles all the drawing of the screen.  I can declare the display variable
		in here, as it isn’t needed in other parts of the program
*/

/* C libraries */
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

/* hardware platform libraries */
#include <display.h>
#include <mbed.h>

#include "asteroids.h"
#include "model.h"
#include "utils.h"
#include "objects.h"

Display *graphics = Display::theDisplay();

const colour_t background = rgb(0,51,102); /* Midnight Blue */
const float pi = 3.1415926f;


/* double buffering functions */
void init_DBuffer(void)
{   /* initialise the LCD driver to use second frame in buffer */
    uint16_t *bufferbase = graphics->getFb();
    uint16_t *nextbuffer = bufferbase+ (480*272);
    LPC_LCD->UPBASE = (uint32_t)nextbuffer;
}

void swap_DBuffer(void)
{   /* swaps frames used by the LCD driver and the graphics object */
    uint16_t *buffer = graphics->getFb();
    graphics->setFb( (uint16_t*) LPC_LCD->UPBASE);
    LPC_LCD->UPBASE = (uint32_t)buffer;
}
//draws main game interface
void drawUI(void)
{		/*Background */
    graphics->fillScreen(background);
		graphics->setTextSize(1);
		graphics->drawLine(0, 15, 480, 15, WHITE);
		graphics->setCursor(210, 5);
		graphics->printf("ASTEROIDS");
		/*Lives*/
	for(int i=1 ; i<=lives ; i++){

		//graphics->drawBitmap(16,16,lives_bit, 10,10, RED);

	}
		/*Score & lives*/
		graphics->setCursor(400, 5);
		graphics->setTextSize(1);
		graphics->printf("score: %d", score);
		
		graphics->setCursor(10, 5);
		graphics->setTextSize(1);
		graphics->printf("lives remaining: %d", lives);

}
//draws ship
void drawShip() {
		graphics->drawLine(shipTipX,shipTipY,shipRightX,shipRightY,GREEN); //right
	  graphics->drawLine(shipX, shipY,shipRightX,shipRightY, GREEN); //bottom
	  graphics->drawLine(shipLeftX, shipLeftY,shipX, shipY, GREEN);//bottom
    graphics->drawLine(shipLeftX, shipLeftY,shipTipX, shipTipY, GREEN);//left
}
//draws rock to screen with bitmap use
void drawRock(asteroid_t *head) {
	asteroid_t* current = head;
	while ( current !=NULL) {
		graphics->drawBitmap(current->p.x,current->p.y,rock,16,16,WHITE);
		current = current->next;
	}
}
//draws missile
void drawMissile(fire_t *headS) {
	fire_t* currentS = headS;
	while ( currentS !=NULL) {
		graphics->fillCircle(currentS->pS.x, currentS->pS.y, 2, RED);
		currentS = currentS->next;
	}
}
//draws shields
void drawShield() {
	for (int i=1;i<=shields;i++){
		graphics->drawCircle (shipX, shipY, 14 + (i*3), BLUE);
  }
}
//end game screen
void end() {
	swap_DBuffer();
	graphics->fillScreen(BLACK);
	graphics->setTextSize(3);
	graphics->setCursor(100,35);
	graphics->printf("GAME OVER, You Lose");
	graphics->setTextSize(2);
	graphics->setCursor(120,100);
	graphics->printf("Total score = %d", score);
	graphics->setCursor(120,170);
	graphics->printf("Click to replay");
	graphics->setTextSize(1);
	init_DBuffer();
}

void incScore() {
	score++;
}

void draw(void)
{
	swap_DBuffer();
	graphics->fillScreen(background);
	drawUI();
	drawShip();
	drawShield();
	drawRock(asteroids);
	drawMissile(missiles);
	incScore();

}
