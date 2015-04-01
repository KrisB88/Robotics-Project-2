#pragma config(Sensor, S1,     HTSMUX,         sensorI2CCustom)
#pragma config(Sensor, S2,     compassSensor,  sensorI2CCustom)
#pragma config(Motor,  motorA,          rightMotor,    tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          leftMotor,     tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorC,          clawMotor,     tmotorNXT, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*Authors: Stephen Kinser
					 Kris Brown
					 Ashley Eden Cox

Project 2: Part 1
Due: 03/23/15
*/

// Include drivers for multiplexer and light sensor
#include "drivers/hitechnic-sensormux.h"
#include "drivers/lego-ultrasound.h"
#include "drivers/lego-light.h"
#include "drivers/lego-touch.h"
#include "drivers/hitechnic-compass.h"
#include "drivers/hitechnic-touchmux.h"
#include "motion.h"
//#include "music.h"
// Define easy names for sensors connected to multiplexer
const tMUXSensor lightSensor = msensor_S1_4;	//Light sensor in smux port 4
const tMUXSensor  touchRight= msensor_S1_3;	//Touch right smux port 3
const tMUXSensor  touchLeft = msensor_S1_2; //Touch left smux port 2
const tMUXSensor ultrasonicSensor = msensor_S1_1; // Ultrasonic smux port 1

#define MAX_DISTANCE 15
#define UNDEFINED_FLOOR 24
#define UNDEFINED_NEST 13
bool  random_walk;
//declaring motor speeds

int compassReading;
int nestValue = 15;
int floorValue = 25;

task MoveTowardsEgg();
task DetectWall();
task Wander();
task StopAtEgg();
task PushEggTowardsNest();


/* THESE ARE THE MAIN TASKS AS DESCRIBED ON THE PROJECT DESCRIPTION---------------------- */
//this makes the robot wander
task Wander()
{
					nxtDisplayTextLine(0, "Task: Wander");
					nxtDisplayCenteredTextLine(1, "------------------");

	//add in a loop for timer to make the robot stop program after a certain amount of time (nothing is found)
	//random_walk= true;
	ClearTimer(T1);
	//time10[T1] < 120000
	while(time10[T1] < 120000 /*&& wall == false*/)//2 minutes
	{
		//nMotorEncoder[leftMotor]=0; //not sure if need to reset periodically
		//nMotorEncoder[rightMotor]=0;
		int decision =random(100)%3;//%3 //explicit "don't reach the default case"
		switch(decision){ //goes in one of the 8 directions
			case 0:
						Forward();
						break;
			case 1:
						Left(0 , 100); //pass two arguments, the length of distance traveled and the turn radius
						break;
			case 2:
						Right(0 , 100);
						break;
			default:
						nxtDisplayStringAt(5, 31, "error with random number generator");
						wait10Msec(1000);
						break;

	}
	}

	//enable(pid);
	//Forward();

}

//this will make the robot push the egg towards the nest
//need compass values from COMPASS_PORT to find way back to nest

//this will makes the robot push the egg into the nest(blue zone)
//will be using the LIGHT_SENSOR to find the colors of the nest and line to it
task PushEggTowardsNest()
{
	//StopTask(MoveTowardsEgg);
	StopTask(StopAtEgg);
					nxtDisplayTextLine(0, "Move Toward Nest");
					nxtDisplayCenteredTextLine(1, "------------------");
					nxtDisplayCenteredTextLine(2, "performing 180 degree turn");
					nSyncedMotors=synchBA;
					nSyncedTurnRatio= 150;
		while((compassReading + 180) %360 != HTMCsetTarget(compassSensor)){// hopefully do a 180 degree turn
					motor[rightMotor] = MOTOR_MAX;
					nxtDisplayCenteredTextLine(3, "Current:%4d", HTMCsetTarget(compassSensor));
					nxtDisplayCenteredTextLine(4, "Home:%4d", compassReading);
					nxtDisplayClearTextLine(3);
				//	wait1Msec(1000);
			}
			//Halt();
			motor[rightMotor] =0;
			nxtDisplayClearTextLine(2);
			nxtDisplayClearTextLine(3);
			nxtDisplayClearTextLine(4);
			int currentFloor =LSvalNorm(lightSensor);
			while( currentFloor > nestValue+ 5){
					nxtDisplayClearTextLine(2);
					//nxtDisplayTextLine(0, "Task: Move Toward Nest");
					nxtDisplayCenteredTextLine(1, "------------------");
					nxtDisplayCenteredTextLine(2, "Current: %4d", currentFloor);
					nxtDisplayTextLine(3, "Nest Value: %4d", nestValue);
					nxtDisplayTextLine(4, "Floor Value: %4d", floorValue);
					Forward();

				 	currentFloor =LSvalNorm(lightSensor);
			}
			Halt();
			wait1Msec(1000);

			raiseArm();

			Right(15, 100);
			HaltArm();
			StartTask(Wander);

}
task MoveTowardsEgg()
{
	int distance = 5; // need to test value
	while(USreadDist(ultrasonicSensor)> MAX_DISTANCE){  // too far away to tell
					nxtDisplayTextLine(3, "Ultra Sonic:");
					nxtDisplayCenteredTextLine(4, "%4d" , ultrasonicSensor);
					//wait1Msec(1000);
					nxtDisplayClearTextLine(3);
					nxtDisplayClearTextLine(4);

}
	Halt();
	wait1Msec(200);
	StopTask(Wander);// turn off temporarily
				nxtDisplayClearTextLine(0);
				nxtDisplayClearTextLine(1);
				random_walk= false;
	while(USreadDist(ultrasonicSensor) > distance ){
		nxtDisplayCenteredTextLine(0, "Task:");
	 	nxtDisplayCenteredTextLine(1,  "Move Towards Egg" );
		nxtDisplayCenteredTextLine(2, "Range: %d",USreadDist(ultrasonicSensor));

		Right(15,100);
		int tempDistRight= USreadDist(ultrasonicSensor);

		Left(15,100);
		int tempDistLeft = USreadDist(ultrasonicSensor);
		Forward();

		if(tempDistRight < tempDistLeft) {
			Right(25, 100);

			//wait1Msec(10);
		}
		else {
			Left(25, 100);
			//wait1Msec(10);
	}
	nxtDisplayClearTextLine(2);
	wait1Msec(15); // might be a problem with the updates
}
	//lowerArm();
	nxtDisplayClearTextLine(0);
	nxtDisplayClearTextLine(1);
	StartTask(StopAtEgg);
}
/*this stops the robot when it hits the egg
we will be using values from the ULTRASONIC_PORT
when readings are negative or not in range, that means we have the egg
*/
task StopAtEgg()
{
	StopTask(MoveTowardsEgg);
		nxtDisplayCenteredTextLine(0, "Task:");
	 	nxtDisplayCenteredTextLine(1, "Stop At Egg" );
		nxtDisplayCenteredTextLine(2, "Lowering Arm" );
	//symph5();

	wait1Msec(1000);
	lowerArm();

	//egg=true;// assume it was sucessful for now
	nxtDisplayClearTextLine(0);
	nxtDisplayClearTextLine(1);
	nxtDisplayClearTextLine(2);
	StartTask(PushEggTowardsNest);
}



//this will detect a wall
//when LEFT_TOUCH_SENSOR or RIGHT_TOUCH_SENSOR is pressed?
//how do we tell the wall is different from the eggs?
task DetectWall()
{
	//wall= true;
	nxtDisplayTextLine(6, "Wall Not Detected");
	while( true){ //while this isn't detected, do nothing
		if(TSreadState(touchLeft) || TSreadState(touchRight)){
				nxtDisplayClearTextLine(6);
				nxtDisplayTextLine(6, "Wall Detected");


				StopTask(Wander);
				//StopTask(MoveTowardsEgg);
				//StopTask(StopAtEgg);
				//StopTask(PushEggTowardsNest);
				wait10Msec(50);

					//Halt();
				motor[rightMotor]=0;
				motor[clawMotor]=0;
				Backwards(1);
				wait10Msec(50);
				Right(15,150);
				Halt();



				motor[rightMotor] = 0;
				//StartTask(Wander);
				//StartTask(MoveTowardsEgg);

				//wall= false;
				//StopTask(DetectWall);
				//StartTask(Wander);
			 	nxtDisplayClearTextLine(6);
			 	//releaseCPU();
			 	EndTimeSlice();
		}
		else{
		//DO NOTHING
		wait10Msec(100);
		}
	}
}

//this is where all the functions are called
task main()
{

	//initialize because junk values are a thing
	nMotorEncoder[leftMotor]=0;
	nMotorEncoder[rightMotor]=0;
	nMotorEncoder[clawMotor]=0;

	floorValue=0;
	nestValue=0;


/*************************************************************
									Get the Compass Value
**************************************************************/
/*
while (nNxtButtonPressed != 3) {
	 // The enter button has been pressed, switch
    // to the other mode
    //nxtDisplayClearTextLine(0);
    nxtDisplayClearTextLine(1);
    compassReading = HTMCsetTarget(compassSensor);// could use the "Norm value" too
    nxtDisplayTextLine(0, "Lego");
    nxtDisplayTextLine(1, "Compass Value:" );
    nxtDisplayTextLine(2, "\t %4d", compassReading);
     wait1Msec(25);
  }
  wait1Msec(2000);
    nxtDisplayClearTextLine(0);
    nxtDisplayClearTextLine(1);
    nxtDisplayClearTextLine(2);
*/
  /**********************************************************
  								Actually Start Task Here
  **********************************************************/
  /*
if(floorValue ==0 && nestValue == 0){
	floorValue= UNDEFINED_FLOOR;
	nestValue = UNDEFINED_NEST;
}
*/
	Forward(360);
	wait1Msec(2000);
	Right(360*3,75);
	wait1Msec(2000);
	Left(360*3, 75);
	//StartTask(Wander);
	//StartTask(DetectWall);
  //raiseArm();

	//StartTask(Wander);
	//wait10Msec(5);
	//StartTask(MoveTowardsEgg);
	//wait10Msec(5);

  //StartTask(PushEggTowardsNest);
  //raiseArm();
  //wait10Msec(1000);
  //lowerArm();
//while(true){
//	if(wall == false)
//	{
//		StartTask(DetectWall);
//	}
//}

	 // set to some logical expression later, preferrably a "We have completed the task" or I have pressed a button
		// this may be difficult without prior knowledge of the course
}	//StopAllTasks();
