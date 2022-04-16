#include "defines.h"
#include "AllianceSelect.h"
	  BallFeed.resetRotation();
    Hood.resetRotation();

    #ifndef DEBUG //if DEBUG is not defined earlier this section will not compile
    #endif
	vex::task fourth (PrintScreen);
	vex::task second (ShootBall);
	vex::task first (RPMCalc);
	vex::task fifth (TurnToFlag);
	vex::task mid2 (TIMER2);
	//vex::task last(anglePIDControl);
  vex::task third (Driver);
	vex::task one (GyroTrack);
	//CapFlip.spin(vex::directionType::fwd,10,vex::velocityUnits::rpm);   

