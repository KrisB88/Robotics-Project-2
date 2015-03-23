#pragma config(Sensor, S1,     HTSMUX,         sensorI2CCustom)
#pragma config(Motor,  motorA,          rightMotor,    tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          leftMotor,     tmotorNXT, PIDControl, encoder)

#include "drivers/hitechnic-sensormux.h"
#include "drivers/lego-touch.h"
#include "motion.h"

const tMUXSensor  touchRight= msensor_S1_3;	//Touch right smux port 3
const tMUXSensor  touchLeft = msensor_S1_2; //Touch left smux port 2


task main()
{



}
