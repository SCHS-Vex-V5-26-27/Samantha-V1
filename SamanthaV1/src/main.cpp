#pragma region VEXcode Generated Robot Configuration
// Make sure all required headers are included.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>


#include "vex.h"

using namespace vex;

// Brain should be defined by default
brain Brain;


// START V5 MACROS
#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)
// END V5 MACROS


// Robot configuration code.



// generating and setting random seed
void initializeRandomSeed(){
  int systemTime = Brain.Timer.systemHighResolution();
  double batteryCurrent = Brain.Battery.current();
  double batteryVoltage = Brain.Battery.voltage(voltageUnits::mV);

  // Combine these values into a single integer
  int seed = int(batteryVoltage + batteryCurrent * 100) + systemTime;

  // Set the seed
  srand(seed);
}



void vexcodeInit() {

  //Initializing random seed.
  initializeRandomSeed(); 
}


// Helper to make playing sounds from the V5 in VEXcode easier and
// keeps the code cleaner by making it clear what is happening.
void playVexcodeSound(const char *soundName) {
  printf("VEXPlaySound:%s\n", soundName);
  wait(5, msec);
}

#pragma endregion VEXcode Generated Robot Configuration
#include <cmath>

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       me                                                        */
/*    Created:      15/10/2026                                                */
/*    Description:  I LOVE SQUIRRELS                                          */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*
SAMANTHA
(squirrel-powered automated movement and advanced nibbling toaster handled automotive)
*/

// Include the V5 Library
#include "vex.h"

// Allows for easier use of the VEX Library
using namespace vex;

/*------------------------------*/
/*  GLOBAL OBJECTS & VARIABLES  */
/*------------------------------*/
int controllerDeadzone = 0;

//The brain is referenced as "Brain", but his name is MARTIN.  Please do not deadname him.
//MARTIN - "mindful advanced respectable toaster interface node"

controller THOMAS = controller();

//Create objects for motors and define their respective groups
//STEVE - "spinning transport enabling vehicle engineish"
motor STEVE1 = motor(PORT19, true); //Front right
motor STEVE2 = motor(PORT11, false); //Front left
motor STEVE3 = motor(PORT20, true); //Back right
motor STEVE4 = motor(PORT12, false); //Back left
//Labor unions
motor_group rightPushyThing = motor_group(STEVE1, STEVE3);
motor_group leftPushyThing = motor_group(STEVE2, STEVE4);

/*------------------------*/
/*      PROJECT CODE      */
/*------------------------*/

void leftPushyThingControl() {
  //Left track:
  while (true) {

    //Set the current position of the controller stick to an int:
    int32_t leftStick = THOMAS.Axis3.position();

    if (leftStick > (0 + controllerDeadzone)) {
      //Forward movement:
      leftPushyThing.setVelocity(std::abs(leftStick), percent);
      leftPushyThing.spin(forward);

    } else if (leftStick < (0 - controllerDeadzone)) {
      //Backward movement:
      leftPushyThing.setVelocity(std::abs(leftStick), percent);
      leftPushyThing.spin(reverse);

    } else {
      //No movement:
      leftPushyThing.setVelocity(0, percent);

    }
  }
}

void rightPushyThingControl() {
  //Right track
  while (true) {

    //Set the current position of the controller stick to an int:
    int32_t rightStick = THOMAS.Axis2.position();

    if (rightStick > (0 + controllerDeadzone)) {
      //Forward movement:
      rightPushyThing.setVelocity(std::abs(rightStick), percent);
      rightPushyThing.spin(forward);

    } else if (rightStick < (0 - controllerDeadzone)) {
      //Backward movement:
      rightPushyThing.setVelocity(std::abs(rightStick), percent);
      rightPushyThing.spin(reverse);

    } else {
      //No movement:
      rightPushyThing.setVelocity(0, percent);

    }
  }
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  // Begin project code

  //Create threads for motor control:
  thread leftPushyThingControlThread = thread(leftPushyThingControl);
  thread rightPushyThingControlThread = thread(rightPushyThingControl);

  //Press X on controller to end program:
  while (true) {
    if (THOMAS.ButtonX.pressing()) {
      Brain.programStop(); 
    }
  }
}