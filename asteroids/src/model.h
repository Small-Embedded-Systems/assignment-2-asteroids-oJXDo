/* Asteroids Model
		exposes the parts of the model needed elsewhere. Such as the fire
		function called by the controller.
*/
struct point {
    float x,y;
};
typedef struct point coordinate_t;
typedef struct point vector_t;

/* Some initial struct types if you want to use them */
struct ship {
    coordinate_t p;
    vector_t     v;
};

//rock struct 
typedef struct asteroid_t {
    coordinate_t p;
		vector_t v;
    struct asteroid_t* next; //iterates list to the next rock
}asteroid_t; //recursive
//shot struct
typedef struct fire_t {
    coordinate_t pS;
		vector_t vS;
    struct fire_t* next; //iterates list to the next missile
}fire_t; //recursive

extern bool joyUp;
extern bool joyLeft;
extern bool joyRight;
extern bool joyDown;
void shipSpin();
void shipThrust();
void end();
extern float angle;
void physics(void);
void createMissile(fire_t *headS);