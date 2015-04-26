#define MOTOR_MAX  30
#define MOTOR_MIN  -25

/*BASIC FUNCTIONS-------------------------------------------------------------------- */
//this moves the robot forwards

/****************************
	B = Right motor
	A = Left motor
****************************/

void Forward( int length)
{

<<<<<<< HEAD
	nMotorEncoder[rightMotor] = 0;
	nMotorEncoder[leftMotor] = 0;
	while( nMotorEncoder[rightMotor] < length ){ //set to slaves later
		motor[rightMotor] = MOTOR_MAX;
		motor[leftMotor] = MOTOR_MAX * 1.01;
=======
	nMotorPIDSpeedCtrl[leftMotor] = mtrSpeedReg;
	nMotorPIDSpeedCtrl[rightMotor] = mtrSpeedReg;



	//nSyncedMotors=synchBA;
	//nSyncedTurnRatio = 100;
	nMotorEncoder[leftMotor] = 0;
	nMotorEncoder[rightMotor] = 0;
	int mSpd = 0;
	while( nMotorEncoder[leftMotor] < length ){ //set to slaves later
		/*motor[leftMotor] = mSpd;
		if (mSpd < MOTOR_MAX)
			mSpd = mSpd + 1;
		//motor[leftMotor] = MOTOR_MAX - .35;
			*/
		motor[leftMotor] = MOTOR_MAX;
		motor[rightMotor] = MOTOR_MAX;
>>>>>>> origin/master
}
	motor[leftMotor] = 0;
	motor[rightMotor] = 0;
	nMotorEncoder[leftMotor] = 0;
	nMotorEncoder[rightMotor] = 0;
}
/*
void Forward( )
{
		//nSyncedMotors=synchAB;
	motor[rightMotor] = MOTOR_MAX;
	motor[leftMotor] = MOTOR_MAX;
}
*/
//this moves the robot to the left
void Right( int length, int turnRadians)
{
	nSyncedMotors=synchBA;
	nSyncedTurnRatio= turnRadians;

	nMotorEncoder[rightMotor] = 0;

	while( nMotorEncoder[rightMotor] < length ){
		motor[rightMotor] = MOTOR_MAX;
	}

	nMotorEncoder[rightMotor] = 0;
	nSyncedMotors = synchNone;
}
//this moves the robot right
void Left( int length, int turnRadians)
{
	nSyncedMotors=synchAB;
	nSyncedTurnRatio= turnRadians;

	nMotorEncoder[leftMotor] = 0;

	while( nMotorEncoder[leftMotor] < length ){
		motor[leftMotor] = MOTOR_MAX;

	}

	motor[leftMotor] = 0;
	nMotorEncoder[leftMotor] = 0;
	nSyncedMotors = synchNone;
}
//this moves the robot backwards
/*
void Backwards( int length)
{
	//nSyncedMotors=synchAB;
	while(nMotorEncoder[rightMotor]> (0-length)){
	motor[rightMotor] = MOTOR_MIN;
	//motor[leftMotor] = MOTOR_MIN;
	}
}
*/
//this funciton halts the robot
/*
void Halt()
{
	motor[rightMotor] = 0;
	motor[leftMotor] = 0;
}
*/
