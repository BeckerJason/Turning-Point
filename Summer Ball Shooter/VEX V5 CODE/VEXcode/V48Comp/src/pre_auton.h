#include "globals.h"
void pre_auton(void) {
	    BallFeed.resetRotation();
    Hood.resetRotation();
gyroInit(0);
    #ifndef DEBUG //if DEBUG is not defined earlier this section will not compile
	AllianceSelect();
    #endif
	vex::task fourth(PrintScreen);
	vex::task second(ShootBall);
	vex::task first(RPMCalc);
	vex::task fifth(TurnToFlag);
	vex::task mid2(TIMER2);
	//vex::task last(anglePIDControl);
  vex::task third (Driver);
	vex::task one(GyroTrack);
	//CapFlip.spin(vex::directionType::fwd,10,vex::velocityUnits::rpm);   

}