#include "mraa.hpp"
#include "motor.h"
#include "servo.h"
#include "shield.h"
#include "liftmech.h"

LiftMech::LiftMech(Motor* lw, Motor* rw, Motor* lm, 
			             Servo* ld, Servo* rd, Servo* ll, Servo* rl,
			             int top, int bottom, Shield* sh) : topbeam(top), bottombeam(bottom)
{
  left_wheel = lw;
  right_wheel = rw;
  lift_motor = lm;

  left_door = ld;
  right_door = rd;

  left_lift = ll;
  right_lift = rl;

  shield = sh;

  counter = 0;
  up = 1;
}

void LiftMech::collect(Shield* shield) {
  lift_motor->setSpeed(shield, 0.2);

  while(counter != 2) {
    if ((!topbeam.read() && up)) {
      lift_motor->stop(shield);
      sleep(1);
      counter++;

      if (counter == 2) {
        break;
      }
      //put the doors out
      left_door->setDegree(shield, 150-150);
      right_door->setDegree(shield, 150);
      sleep(1);

      //wiggle
      left_wheel->setSpeed(shield, 0.25);
      right_wheel->setSpeed(shield, -0.25);
      usleep(250000);
      left_wheel->stop(shield);
      right_wheel->stop(shield);
      usleep(300000);
      left_wheel->setSpeed(shield, -0.25);
      right_wheel->setSpeed(shield, 0.25);
      usleep(500000);
      left_wheel->stop(shield);
      right_wheel->stop(shield);
      usleep(300000);
      left_wheel->setSpeed(shield, 0.25);
      right_wheel->setSpeed(shield, -0.25);
      usleep(500000);
      left_wheel->stop(shield);
      right_wheel->stop(shield);
      usleep(300000);
      left_wheel->setSpeed(shield, -0.25);
      right_wheel->setSpeed(shield, 0.25);
      usleep(500000);
      left_wheel->stop(shield);
      right_wheel->stop(shield);
      usleep(300000);
      left_wheel->setSpeed(shield, 0.25);
      right_wheel->setSpeed(shield, -0.25);
      usleep(200000);
      left_wheel->stop(shield);
      right_wheel->stop(shield);
      usleep(300000);

      //drive forward slightly
      left_wheel->setSpeed(shield, 0.2);
      right_wheel->setSpeed(shield, 0.2);
      usleep(300000);
      left_wheel->setSpeed(shield, 0);
      right_wheel->setSpeed(shield, 0);

      //put the doors back
      left_door->setDegree(shield, 150-0);
      right_door->setDegree(shield, 0);
      sleep(1);

      //drop stack 
      left_lift->setDegree(shield, 180 - 90);
      right_lift->setDegree(shield, 90);
      sleep(2);

      up = 0;
    } else if (!bottombeam.read() && !up) {
      lift_motor->stop(shield);
      sleep(1);

      //grab the blocks
      left_lift->setDegree(shield, 180 - 40);
      right_lift->setDegree(shield, 40);
      sleep(2);

      up = 1;
    } else if (!topbeam.read() && !up) {
      lift_motor->setSpeed(shield, -0.1);
    } else if (!bottombeam.read() && up) {
      lift_motor->setSpeed(shield, 0.15);
    }
  }
}

void LiftMech::score(Shield* shield) {
  //close doors
  left_door->setDegree(shield, 150-150);
  right_door->setDegree(shield, 150);
  sleep(1);

  //drop cubes
  left_lift->setDegree(shield, 180 - 90);
  right_lift->setDegree(shield, 90);
}

void LiftMech::reset() {
  counter = 0;
}