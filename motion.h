#define MOTOR_MAX  50
#define MOTOR_MIN  -25

/*BASIC FUNCTIONS-------------------------------------------------------------------- */
//this moves the robot forwards

/****************************
	A = Right motor
	B = Left motor
****************************/

void Forward( int length)
{
	nSyncedMotors=synchAB;
	nSyncedTurnRatio = 100;
	nMotorEncoder[rightMotor] = 0;
	//nMotorEncoder[leftMotor] = 0;

	while( nMotorEncoder[rightMotor] < length ){ //set to slaves later
		motor[rightMotor] = MOTOR_MAX;
		//motor[leftMotor] = MOTOR_MAX;
}
	motor[rightMotor] = 0;
	nMotorEncoder[rightMotor] = 0;
}
void Forward( )
{
		//nSyncedMotors=synchAB;
	motor[rightMotor] = MOTOR_MAX;
	motor[leftMotor] = MOTOR_MAX;
}
//this moves the robot to the left
void Left( int length, int turnRadians)
{
	nSyncedMotors=synchAB;
	nSyncedTurnRatio= turnRadians;

	nMotorEncoder[rightMotor] = 0;

	while( nMotorEncoder[rightMotor] < length ){
		motor[rightMotor] = MOTOR_MAX;
	}

	nMotorEncoder[rightMotor] = 0;
}
//this moves the robot right
void Right( int length, int turnRadians)
{
	nSyncedMotors=synchBA;
	nSyncedTurnRatio= turnRadians;

	nMotorEncoder[leftMotor] = 0;
	//nMotorEncoder[rightMotor] = 0;

	while( nMotorEncoder[leftMotor] < length ){
		motor[leftMotor] = MOTOR_MAX;

	}

	motor[leftMotor] = 0;
	nMotorEncoder[leftMotor] = 0;
	//nMotorEncoder[rightMotor] = 0;
}
//this moves the robot backwards
void Backwards( int length)
{
	nSyncedMotors=synchAB;
	while(nMotorEncoder[rightMotor]> (0-length)){
	motor[rightMotor] = MOTOR_MIN;
	//motor[leftMotor] = MOTOR_MIN;
	}
}
//this funciton halts the robot
void Halt()
{
	motor[rightMotor] = 0;
	motor[leftMotor] = 0;
}
void raiseArm(){
	//int count=0;
	//while(count < 1){ //setting it to arbitrary value until can make an angle based assumption
	while(nMotorEncoder[clawMotor]> (0-150)){
	motor[clawMotor]= MOTOR_MIN;
	//count++;
	}
	//motor[clawMotor]=0;

}
void lowerArm(){
	//int count=0;
	//while(count < 1){ //setting it to arbitrary value until can make an angle based assumption
nMotorEncoder[clawMotor] = 0;
while(nMotorEncoder[clawMotor]< 150){
	motor[clawMotor]= MOTOR_MAX;
	}
}
void HaltArm(){
motor[clawMotor]=0;

}
