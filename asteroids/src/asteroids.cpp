/* Asteroids
    The game, it includes main and declares any global variables needed
		for the game state
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

/* Main game elements */
#include "model.h"
#include "view.h"
#include "controller.h"
#include "utils.h"

/* Game state */
float elapsed_time; 
int   score;
int   lives;
int 	shields;
int rockCount;
int shotCount;
struct ship player;
double shipX = 240;
double shipY = 146;
double shipTipX = shipX;
double shipTipY = shipY -15;
double shipRightX = shipX + 7;
double shipRightY = shipY + 10;
double shipLeftX = shipX - 7;
double shipLeftY = shipY +10;
double rockX = 100;
double rockY = 100;
asteroid_t *asteroids;
fire_t *missiles;

float Dt = 0.01f;

Ticker model, view, controller;

bool paused = true;
/* The single user button needs to have the PullUp resistor enabled */
DigitalIn userbutton(P2_10,PullUp);
//initialises lists
void initialiseLists() {
	asteroids = static_cast<asteroid_t*>(malloc(sizeof(asteroid_t)));
	asteroids->next = NULL;
	
	missiles = static_cast<fire_t*>(malloc(sizeof(fire_t)));
	missiles->next = NULL;
}
//reset values on restart
void reset(){
	score = 0;
	lives = 1;
	shields = 2;
}
int main() {
	srand(time(0));
	initialiseLists();
	init_DBuffer();

	view.attach( draw, 0.025);
	model.attach( physics, Dt);
	controller.attach( controls, 0.1);
	
	score = 0;
	lives = 1;
	shields = 2;
		while(true) {
			if (lives < 1) { // while lives less than 1 show end screen
				view.detach();
				model.detach();
				controller.detach();
				end();
			}
			if (restartGame()) { //game restart
				srand(time(0));
				initialiseLists();
				init_DBuffer();

				view.attach( draw, 0.025);
				model.attach( physics, Dt);
				controller.attach( controls, 0.1);
			
				reset(); // reset score, shields etc.
				draw();
			}
		}
}
