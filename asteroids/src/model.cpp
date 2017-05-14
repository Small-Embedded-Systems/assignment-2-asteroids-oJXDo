/* Asteroids model
		handles updating the game state, moving the objects, and handling collisions
*/
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#include "model.h"
#include "utils.h"
#include "asteroids.h"

double x,y,x1,y1,x2,y2;
    int radius = 15;
    float angle = 0.0;
		float length = 20;
    float angle_stepsize = 0.025;
		float PI = 3.1415926f;
		float velX;
		float velY;
		float missleVelX;
		float missleVelY;

void shipTurn()
{
	x = length * cos (angle);
	y = length * sin (angle);
	x1 = length * cos (angle + 3.83972);
	y1 = length * sin (angle + 3.83972);
	x2 = length * cos (angle + 2.44346);
	y2 = length * sin (angle + 2.44346);
	
	shipTipX = x + shipX;
	shipTipY = y + shipY;
	
	shipRightX = x1 + shipX;
	shipRightY = y1 + shipY;
	
	shipLeftX = x2 + shipX;
	shipLeftY = y2 + shipY;
	
	if (angle > 2 * pi) {
		angle = 0.1;
	}
	if (angle < 0) {
		angle = (2*pi) - 0.1;
	}
	if (joyLeft == true) {
		angle += angle_stepsize;
	}
	if (joyRight == true) {
		angle -= angle_stepsize;
	}
	if (joyCenter == true) {
		joyRight = false;
		joyLeft = false;
		joyUp = false;
	}
}
//controls ship speed
void thrust() {
		velX = (10 * cos (angle));
		velY = (10 * sin (angle));
		if (joyUp == true) {
				shipX += (velX / 20);
				shipY += (velY / 20);
		}	
}
//ship wrap method
void shipWrapper(){
	if (shipX < 0 ){
		shipX = 478;
	}
	else if (shipX > 480){
		shipX = 3;
	} 
	else if (shipY < 27){
		shipY = 271;
	}
	else if (shipY > 272){
		shipY = 28;
	}
}
//adds new node in asteroids list
void spawnRock(asteroid_t* head) {
	if(rockCount < 5 ) {
    asteroid_t* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = (asteroid_t*)malloc(sizeof(asteroid_t));
    current->next->p.x = randrange(16, 470);current->next->p.y =  randrange(16, 260); // position
		current->next->v.x = randrange(-1, 2);current->next->v.y = randrange(-1, 2); // velocity 
		if(current->next->v.x == 0 && current->next->v.y == 0){
			current->next->v.x = randrange(-1, 2);current->next->v.y = randrange(-1, 2);
	}
    current->next->next = NULL;
		rockCount++;
	}
}
//rock wrap and movement method
void rockWrapper(asteroid_t* head) {
	asteroid_t* current = head;
		if (current !=NULL) {
			current->p.x += current->v.x;
			current->p.y += current->v.y;
		
			if (current->p.x > 500) {
				current->p.x = -20;
			}
			if (current->p.x < -20) {
				current->p.x = 500;
			}
			if (current->p.y > 290) {
				current->p.y = -20;
			}
			if (current->p.y < -20) {
				current->p.y = 290;
			}
		current = current->next;
		rockWrapper(current);
	}
}
//collision detection
void rockColl (asteroid_t* head) {
	asteroid_t* current = head;
		if (current !=NULL) {
			if (current->p.x < shipX +18 && current->p.x > shipX - 18 && current->p.y > shipY -18 && current->p.y < shipY + 18) {
				current->p.x = randrange(10, 470); //relocates rock once hits ship
				current->p.y = randrange(10, 260);
				shields--; //decrement shield on collision
				score = score - 50;
				if (shields < 0) {
					lives--; //decrement lives on collision once shield are depleated
					score = score - 100;
					shields = 2;
				} if (lives <=0) {
						end(); // draws end game screen lives = 0 
				}if (score <=0) {
						 score = 0;
				}
			}
		current = current->next;
		rockColl(current);
		}
}
//adds new node to missileList
void createMissile(fire_t* headS) {
	fire_t* currentS = headS;
	while (currentS->next !=NULL) {
			currentS = currentS->next;
	}
	currentS->next = (fire_t*)malloc(sizeof(fire_t));
	currentS->next->pS.x = shipTipX; //missile direction to front of ship
	currentS->next->pS.y = shipTipY;
	currentS->next->vS.x = velX/5; // velocity
	currentS->next->vS.y = velY/5;
	currentS->next->next = NULL;
	shotCount++;
}
//controls missile movement
void missileMethods(fire_t* headS) {
	fire_t* currentS = headS;
	while (currentS !=NULL) {
		currentS-> pS.x += currentS-> vS.x;
		currentS-> pS.y += currentS-> vS.y;
		currentS=currentS->next;
	}
}
// load methods for physics
void physics(void) {
	thrust();
	spawnRock(asteroids);
	rockWrapper(asteroids);
	rockColl(asteroids);
	missileMethods(missiles);
	shipWrapper();
	shipTurn();
}
