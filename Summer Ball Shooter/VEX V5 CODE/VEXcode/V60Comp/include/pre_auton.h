#include "defines.h"
//Lift.set(false);
//lift=off; 
using namespace G; 
using namespace std; 
using namespace vex;
     #ifndef DEBUG //if DEBUG is not defined earlier this section will not compile
    #include "AllianceSelect.h"
    #endif
	  BallFeed.resetRotation();
    Hood.resetRotation();
	vex::task fourth (PrintScreen);
	vex::task second (ShootBall);
	vex::task first (RPMCalc);
	vex::task fifth (TurnToFlag);
	vex::task mid2 (TIMER2);
	//vex::task last(anglePIDControl);
  vex::task third (Driver);
	vex::task okay (GyroTrack);
	//CapFlip.spin(vex::directionType::fwd,10,vex::velocityUnits::rpm);   

