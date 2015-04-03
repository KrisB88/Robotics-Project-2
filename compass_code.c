#pragma config(Sensor, S2,     compass,             sensorI2CHiTechnicCompass)
//#pragma config(Motor,  motorA,          rightMotor,    tmotorNXT, PIDControl, encoder)
//#pragma config(Motor,  motorB,          leftMotor,     tmotorNXT, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
/*
int nNewHeading;
int nOldHeading = 999;

task main()
{
  nxtDisplayCenteredBigTextLine(1, "Compass");
  while (true)
  {
  	//	motor[rightMotor] = 50;
	    //motor[leftMotor] = 50;
    nNewHeading = SensorValue[compass];
    if (abs(nNewHeading - nOldHeading) > 1)
    {
      // Only update when changed to avoid LCD screen flicker
      nxtDisplayCenteredBigTextLine(4, "%d", nNewHeading);
      nOldHeading = nNewHeading;
    }
  }
}

*/


//#pragma config(Sensor, S1,     compass,             sensorI2CHiTechnicCompass)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//////////////////////////////////////////////////////////////////////////////
//
//                     HiTechnio Compass Sensor Calibration
//
// A small little program to calibrate the HiTechnic Compass.
//
// When started, the program displays the compass heading on the NXT LCD.
//
// When ENTER button is pushed, then compass is put into calibration mode and
// remains in that mode until the ENTER button is pressed again.
//
// When in "calibration" mode the compass should be slowly rotated in a circle.
// For details, refer to the technical documentation on the HiTechnic site.
//
//////////////////////////////////////////////////////////////////////////////

void calibrateCompass();   // Function prototype


task main()
{
  while(true)
  {
    switch (nNxtButtonPressed)
    {
    case kEnterButton:
      calibrateCompass();
      break;

    default:
		  // Display the value of the compass

      nxtDisplayCenteredBigTextLine(0, "Compass");
		  nxtDisplayCenteredBigTextLine(2, "%d", SensorValue[S1]);
	    nxtDisplayCenteredTextLine(5, "Press ENTER");
	    nxtDisplayCenteredTextLine(6, "to Calibrate");
      break;
    }
  }
}

//////////////////////////////////////////////////////////////////////////////
//
//                          calibrateCompass
//
// Function to calibrate a HiTechnic Compass
//
//////////////////////////////////////////////////////////////////////////////

void calibrateCompass()
{
  typedef struct
  {
    byte nMsgSize;
    byte nDeviceAddress;
    byte nLocationPtr;
    byte nCompassMode;
  } TI2C_Output;

  TI2C_Output sOutput;

  enum
  {
  	kCommandRead      = 0x00,
  	kCommandCalibrate = 0x43,
  };

  while (nNxtButtonPressed == kEnterButton)
  {}

  // Send "Calibration mode" message via I2C

  sOutput.nMsgSize       = 3;
  sOutput.nDeviceAddress = 0x02;
  sOutput.nLocationPtr   = 0x41;
  sOutput.nCompassMode   = kCommandCalibrate;

  nxtDisplayCenteredBigTextLine(0, "Compass");
  nxtDisplayCenteredBigTextLine(2, "Calibrate");
  nxtDisplayCenteredTextLine(5, "Press ENTER");
  nxtDisplayCenteredTextLine(6, "to finish");
  //SensorType[compass] = sensorI2CCustomStd;// change to a type that allows user messaging

  nI2CBytesReady[S3] = 0;
  //sendI2CMsg(S3, sOutput.nMsgSize, 0);
  wait1Msec(40);
  while (nNxtButtonPressed != kEnterButton)
  {
    wait1Msec(1000);
    PlaySound(soundBlip);
  }

  while (nNxtButtonPressed == kEnterButton)
  {}

  // End Calibration by sending a "Read Compass" message via I2C

  sOutput.nMsgSize       = 3;
  sOutput.nDeviceAddress = 0x02;
  sOutput.nLocationPtr   = 0x41;
  sOutput.nCompassMode   = kCommandRead;
  nI2CBytesReady[S3] = 0;
  //sendI2CMsg(S3, sOutput.nMsgSize, 0);

  SensorType[S1] = sensorI2CHiTechnicCompass; // restore as a compass type
  eraseDisplay();
  return;
}
