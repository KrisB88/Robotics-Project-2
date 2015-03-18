#pragma config(Sensor, S1,     touchLeft,      sensorTouch)
#pragma config(Sensor, S2,     touchRight,     sensorTouch)
#pragma config(Sensor, S3,     ultrasonicSensor, sensorSONAR)
#pragma config(Sensor, S4,     lightSensor,    sensorLightActive)
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

//setting up the enabler, the priority process, active process, name, and num process
/* int process_priority[10];
 int process_enable[10];
 char process_name[10][20];

int num_process = 0;
int active_process = 0;*/




//declaring motor speeds
int MOTOR_MAX = 50;
int MOTOR_MIN = -50;
bool wall=false;


/*BASIC FUNCTIONS-------------------------------------------------------------------- */
//this moves the robot forwards
void Forward( int length)
{
	nSyncedMotors=synchAB;
	//nxtDisplayCenteredTextLine(0, "%d",(nMotorEncoder[leftMotor]));
	//wait10Msec(10000);
	while(nMotorEncoder[leftMotor]< length){ //set to slaves later
	motor[rightMotor] = MOTOR_MAX;
	motor[leftMotor] = MOTOR_MAX;
}
}
void Forward( )
{


	motor[rightMotor] = MOTOR_MAX;
	motor[leftMotor] = MOTOR_MAX;

}
//this moves the robot to the left
void Left( int length, int turnRadians)
{
	nSyncedMotors=synchAB;
	nSyncedTurnRatio= turnRadians
	//	nxtDisplayCenteredTextLine(0, "%d",(nMotorEncoder[leftMotor]));
	//wait10Msec(10000);
	while(nMotorEncoder[leftMotor]<length){
	//motor[rightMotor] = MOTOR_MIN;
	motor[leftMotor] = MOTOR_MAX;
}
}
//this moves the robot right
void Right( int length, int turnRadians)
{
	nSyncedMotors=synchAB;
	nSyncedTurnRatio= turnRadians;
	while(nMotorEncoder[leftMotor]<length){
	motor[rightMotor] = MOTOR_MAX;
	//motor[leftMotor] = MOTOR_MIN;
}
}
//this moves the robot backwards
void Backwards( int length)
{
	nSyncedMotors=synchAB;
	while(nMotorEncoder[leftMotor]<length){
	motor[rightMotor] = MOTOR_MIN;
	motor[leftMotor] = MOTOR_MIN;
	}
}
//this funciton halts the robot
void Halt()
{
	motor[rightMotor] = 0;
	motor[leftMotor] = 0;
}


/*SENSOR FUNCTIONS----------------------------------------------------------------------*/
bool left_touch()
{
	return	SensorValue(touchLeft)==0;
	//return /*DigitalPinValue???*/ digital(LEFT_TOUCH_PORT);
}

bool right_touch()
{
	return	SensorValue(touchRight)==0;
	//return /*DigitalPinValue???*/ digital(RIGHT_TOUCH_PORT);
}
/* ENABLE AND DISABLE FUNCTIONS---------------------------------------------------------
void enable(int pid)
{
	process_enable[pid] = process_priority[pid];
}

void disable(int pid)
{
	process_enable[pid] = 0;
}*/
/*-----------maybe a helper function like periodic turn to help the robot wander more effectively? */
/*void periodic_turn(int pid)
{
	while(true)
	{
		if( time100)
		{
			enable(pid);
			Right(pid);
			//msleep(500L); Use halt instead?
			Halt(pid);
			disable(pid);
			//msleep();
			Halt(pid);
		}
	}
}*/

/* THESE ARE THE MAIN TASKS AS DESCRIBED ON THE PROJECT DESCRIPTION---------------------- */
//this makes the robot wander
task Wander()
{
	//add in a loop for timer to make the robot stop program after a certain amount of time (nothing is found)
	ClearTimer(T1);
	//time10[T1] < 120000
	while(time10[T1] < 120000 && wall== false)//2 minutes
	{
		//nMotorEncoder[leftMotor]=0; //not sure if need to reset periodically
		//nMotorEncoder[rightMotor]=0;
		int decision =random(3);
		switch(decision){ //goes in one of the 8 directions
			case 0:
				Forward(random(500)+250);
			break;
			case 1:
				Left(random(500) + 250, 45); //pass two arguments, the length of distance traveled and the turn radius
			break;
			case 2:
				Right(random(500) + 250, 45);
			break;
	/*		case 3:
				Backwards(random(500) + 250);
			break;
			case 4:
				Forward(random(500) + 250);
				Left(random(500) + 250);
			break;
			case 5:
				Forward(random(500) + 250);
				Right(random(500) + 250);
			break;
			case 6:
				Backwards(random(500) + 250);
				Left(random(500) + 250);
			break;
			case 7:
				Backwards(random(500) + 250);
				Right(random(500) + 250);
				break;
*/
			default:
			nxtDisplayStringAt(0, 31, "error with random number generator");
			wait10Msec(1000);
			break;

	}
	}

	//enable(pid);
	//Forward();
}

//this makes the robot move towards the egg
//useing the ULTRASONIC_PORT to close the distance from robot to egg
task MoveTowardsEgg()
{
	int distance = 10;
	while(SensorValue(ultrasonicSensor) > distance ){
		Forward();
	}
}
/*this stops the robot when it hits the egg
we will be using values from the ULTRASONIC_PORT
when readings are negative or not in range, that means we have the egg
*/
//task StopAtEgg()
//{

//}

//this will make the robot push the egg towards the nest
//need compass values from COMPASS_PORT to find way back to nest
task PushEggTowardsNest()
{

}
//this will makes the robot push the egg into the nest(blue zone)
//will be using the LIGHT_SENSOR to detect the colors of the nest and line to it
task PushEggIntoNest()
{

}

//this will detect a wall
//when LEFT_TOUCH_SENSOR or RIGHT_TOUCH_SENSOR is pressed?
//how do we tell the wall is different from the eggs?
task DetectWall()
{
	while( !left_touch() && !right_touch()); //while this isn't detected, do nothing

		wall= true;
		Halt();//when detected stop
		wait10Msec(100);// wait
		Backwards(750); //then backwards
		Right(250, 45);// turn to get out of the way

}

//this is where all the functions are called
task main()
{
	int nestValue;
	//initialize because junk values are a thing
	nMotorEncoder[leftMotor]=0;
	nMotorEncoder[rightMotor]=0;
	nMotorEncoder[clawMotor]=0;
	//Forward(1000); //for debugging
	//Right(500, 45); //for debugging
	//StartTask(Wander);
	//StartTask(DetectWall);
	//while(true);
//getting values of the tape, nest and field
	while(SensorValue(touchLeft) == 0)
	{
		nxtDisplayStringAt(0, 31, "Read Nest Value Now");
	}
	nestValue=SensorValue(lightSensor);
	wait1Msec(1000);
/*
	while(SensorValue(touchLeft) == 0)
	{
		nxtDisplayStringAt(0, 31, "Read Tape Value Now");
	}
	tapeValue = SensorValue(lightSensor);

	while(SensorValue(touchLeft) == 0)
	{
		nxtDisplayStringAt(0, 31, "Read Field Value Now");
	}
	*/
	//fieldValue = SensorValue(lightSensor);
	//CompassReading= SensorValue();
	//touch twice to turn on
	//use compass to set home location
	//


	//while(true)
	//{


	//}


}
