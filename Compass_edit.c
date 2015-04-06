//*!!Sensor,    S1,                  GGG, sensorLightActive,      ,              !!*//
//*!!                                                                            !!*//
//*!!Start automatically generated configuration code.                           !!*//


#pragma platform (NXT, FTC)
#pragma fileExtension("rtm")

#include "AdvancedSensors.c"    // include library files



task main()
{
	int nCompassHeading;
	int nLastX     = 31; // out of range to force initial display
	int nLastY     = 31; // out of range to force initial display
	tSensors nCompass = S2;

	nxtDisplayCenteredBigTextLine(0, "Compass");
	nxtDisplayCenteredBigTextLine(2, "Test");

  nxtDisplayCenteredTextLine(5, "Connect Compass");
  nxtDisplayCenteredTextLine(6, "to any port");

	SensorType[nCompass] = sensorI2CHiTechnicCompass;
  nCompassHeading = SensorValue[nCompass];
	wait1Msec(10);

	//
	// Clear screen and setup variables
	//
	eraseDisplay();
	//
	// Repeat forever display angle and sine on the NXT LCD display
	//
  nxtDrawEllipse(0, 62, 62, 0);
	nxtDisplayStringAt(29, 58, "N");
	nxtDisplayStringAt(29,  8, "S");
	nxtDisplayStringAt( 3, 34, "W");
	nxtDisplayStringAt(54, 34, "E");
  nxtDrawLine(31, 31, nLastX, nLastY);
  while (true)
	{
		int X;
		int Y;

	  //
	  // Normalize
	  //
	  nCompassHeading = SensorValue[nCompass] % 360;
	  if (nCompassHeading < 0)
	    nCompassHeading += 360;

    X = 31 + (float) (sinDegrees(nCompassHeading) * 31);
    Y = 31 + (float) (cosDegrees(nCompassHeading) * 31);
	  if ((nLastX != X)  || (nLastY != Y))
	  {
	  	//
	  	// Position has changed. Redraw some screen elements
	  	// If unchanged, skip to avoid screen flicker
	  	//
		  nxtInvertLine(31, 31, X,  Y);
		  nxtInvertLine(31, 31, nLastX, nLastY);
			//nxtInvertLine(31, 31, nLastLastX, nLastLastX);

		  //
		  // Numeric display of 'compass on right of screen
		  //
		  nxtDisplayStringAt(57, 60, "Heading");
		  nxtDisplayStringAt(65, 52, "%+5d", nCompassHeading);

		  nxtDisplayStringAt(75, 16, "Port");
		  nxtDisplayStringAt(80,  8, "S%1d", (short) ((short) nCompass + 1));

		  nLastX = X;
		  nLastY = Y;
		}

  }
  return;
}
