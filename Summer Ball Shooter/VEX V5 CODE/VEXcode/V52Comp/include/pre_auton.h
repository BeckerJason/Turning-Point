#include "defines.h"
using namespace G;
using namespace std;
using namespace vex;
#include "AllianceSelect.h"
#include "AutoSelect.h"
wait(200);

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
	vex::task okay (GyroTrack);
	//CapFlip.spin(vex::directionType::fwd,10,vex::velocityUnits::rpm);   
