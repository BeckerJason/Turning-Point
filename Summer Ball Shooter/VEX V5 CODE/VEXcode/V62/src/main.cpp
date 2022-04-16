/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Jason                                                     */
/*    Created:      Sun Mar 31 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                             */
/*----------------------------------------------------------------------------*/

//red 2 blue 3
#include "defines.h"
vex::competition Competition;  
#include "functions.h"
  
 
//void pre_auton(void); 
//
void pre_auton(void) {
  preautoL=true;
//#include "DrawPicture.h"
#include "pre_auton.h" 
}

//
void auton(void) { 
  preautoL=false;
  G::MATCHTIMER=0;
  vex::task ceice (ENDAUTOTIMER);
#include "autonom.h"
}


void usercontrol(void) {
  preautoL=false;
G::MATCHTIMER=0; 
vex::task ceice (ENDAUTOTIMER);
 #include "usercontrol.h"
} 

int main() {
AutoRunning = 0;
   Lift.set(false);  
   Intake.set(false);
   wait(1000);
   Gyro.startCalibration();
   wait(3000);
	//Run the pre-autonomous function. 
	pre_auton();

	//Set up callbacks for autonomous and driver control periods.
	Competition.autonomous(auton);
	Competition.drivercontrol(usercontrol);

	//Prevent main from exiting with an infinite loop.                        
	while (1) {
		wait(100);//Sleep the task for a short amount of time to prevent wasted resources.
	}
}