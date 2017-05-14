/* Controller
		has the code for the user interface (the input side).  This polls the joy-
		stick and sets values, or calls functions as needed
*/

/* C libraries */
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

/* hardware platform libraries */
#include <mbed.h>

/* asteroids */
#include "model.h"
#include "asteroids.h"

/* Joystick 5-way switch
*/
typedef enum {JLT, JRT, JUP, JDN, JCR} btnId_t;
DigitalIn jsBtns[] = {P5_0, P5_4, P5_2, P5_1, P5_3}; // LFT, RGHT, UP, DWN, CTR
bool jsPrsdAndRlsd(btnId_t b);

bool joyUp, joyLeft, joyRight, joyCenter, joyDown;

void controls(void)
{
	if (jsPrsdAndRlsd(JUP)) { // accelerate
		joyUp = true;
		joyLeft = false;
		joyRight = false;
	}
	
	if (jsPrsdAndRlsd(JLT)) { // turn left
		joyLeft = true;
		joyRight = false;
	}
		
	
	if (jsPrsdAndRlsd(JRT)) {// turn right
		joyRight = true;
		joyLeft = false;
	}
	if (jsPrsdAndRlsd(JDN)) { // stops
		joyRight = false;
		joyLeft = false;
		joyUp = false;
		joyDown = false;
	}
	
	if (jsPrsdAndRlsd(JCR)) {
		createMissile(missiles);// fires missile
	}

}
//Gamestate
bool (restartGame(void)) {
		if (lives==0 && jsPrsdAndRlsd(JCR)) {
			return true;
		}
		return false;
	}

bool jsPrsdAndRlsd(btnId_t b) {
	bool result = false;
	uint32_t state;
	static uint32_t savedState[5] = {1,1,1,1,1};
	//initially all 1s: nothing pressed
	state = jsBtns[b].read();
	if ((savedState[b] == 0) && (state == 1)) {
		result = true;
	}
	savedState[b] = state;
	return result;
}
