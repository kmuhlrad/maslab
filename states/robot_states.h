#ifndef ROBOT_STATES_H
#define ROBOT_STATES_H

enum robot_states {
	START = 0,
	STACKSEARCH = 1,
	DRIVE = 2,
	WIGGLE = 3,
	LIFT = 4,
	PLATFORMSEARCH = 5,
	ALIGN = 6,
	DROP = 7
};

#endif