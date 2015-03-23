void Forward( int length)
{
	nSyncedMotors=synchAB;
	while(nMotorEncoder[leftMotor]< length){ //set to slaves later
	motor[rightMotor] = MOTOR_MAX;
	motor[leftMotor] = MOTOR_MAX;
}
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
	nSyncedMotors=synchBA;
	nSyncedTurnRatio= turnRadians;
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
	while(nMotorEncoder[rightMotor]<length){
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
	//motor[leftMotor] = MOTOR_MIN;
	}
}
//this funciton halts the robot
void Halt()
{
	motor[rightMotor] = 0;
	motor[leftMotor] = 0;
}
