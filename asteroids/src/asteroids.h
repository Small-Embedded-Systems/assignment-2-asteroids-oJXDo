/* Game state */
/*
		declares  common  datatypes  needed  for  the  game,  and  makes  the  data
		available to other modules via the extern type qualifier.
*/

extern float 	elapsed_time; /* time this ship has been active */
extern int   	score;        /* total score so far */
extern int   	lives;        /* lives remaining */
extern int	 	shields;			/* shields remaining */

extern int 	 	rockCount;
extern int 	 	shotCount;
extern double shipX; //ship pos
extern double shipY;
extern double shipTipX;		//ship sides
extern double shipTipY;
extern double shipRightX;
extern double shipRightY;
extern double shipLeftX;
extern double shipLeftY;

extern struct ship player;
extern bool joyUp, joyLeft, joyRight, joyCenter; // joystick bools

extern struct asteroid_t *asteroids; /* array of rocks / pointer to linked-list */
extern struct fire_t *missiles;  /* array of missiles / pointer to linked-list */

extern const float Dt; /* Time step for physics, needed for consistent motion */
