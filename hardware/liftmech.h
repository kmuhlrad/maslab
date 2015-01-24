#ifndef LIFT_MECH_H
#define LIFT_MECH_H

#include "mraa.hpp"
#include "motor.h"
#include "servo.h"
#include "shield.h"

class LiftMech {
 	//Shield* shield;

 	Motor left_wheel;
 	Motor right_wheel;
 	Motor lift_motor;

 	Servo left_door;
 	Servo right_door;

 	Servo left_lift;
 	Servo right_lift;

 	mraa::Gpio topbeam;
 	mraa::Gpio bottombeam;

 	int counter;
 	int up;
public:
	LiftMech(Motor& lw, Motor& rw, Motor& lm, 
			 Servo& ld, Servo& rd, Servo& ll, Servo& rl,
			 int top, int bottom);
	void collect(Shield* shield);
	void score(Shield* shield);
	void reset();
};

#endif