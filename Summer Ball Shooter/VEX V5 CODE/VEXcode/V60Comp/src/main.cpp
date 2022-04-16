/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       Jason                                                     */
/*    Created:      Sun Mar 31 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                             */
/*----------------------------------------------------------------------------*/
#include "defines.h"
vex::competition Competition; 
#include <fstream>
std::ofstream file; 
#include "functions.h" 
using namespace std;  
using namespace G;
using namespace vex;
int record()
{Brain.resetTimer();
while (1)
{
bR1=btR1;
bR2=btR2;
bL1=btL1;
bL2=btL2;
bA=btA;
bY=btY;
bB=btB;
bX=btX;
bB=btB;
bLeft=btLeft;
bRight=btRight;
bUp=btUp;
bDown=btDown;
ch3=chl3;
ch4=chl4;
ch1=chl1;
ch2=chl2;
file.open("RecordedAuto.txt",ofstream::ate|ofstream::out|ofstream::app);
file<<"bR1="<<bR1<<";";
file<<"bR2="<<bR2<<";";
file<<"bL2="<<bL2<<";";
file<<"bL1="<<bL1<<";";
file<<"bA="<<bA<<";";
file<<"bB="<<bB<<";";
file<<"bY="<<bY<<";";
file<<"bX="<<bX<<";";
file<<"bLeft="<<bLeft<<";";
file<<"bRight="<<bRight<<";";
file<<"bUp="<<bUp<<";";
file<<"bDown="<<bDown<<";";
file<<"ch1="<<ch1<<";";
file<<"ch2="<<ch2<<";";
file<<"ch3="<<ch3<<";";
file<<"ch4="<<ch4<<";";
wait(10);
file<<"wait("<<Brain.timer(vex::timeUnits::msec)<<");"<<endl;
Brain.resetTimer();
file.close();

}

return 0;
}
#include "AUTOREPLAY.h"

  
 
//void pre_auton(void); 
//
void pre_auton(void) {
//#include "DrawPicture.h"
#include "pre_auton.h" 
}

//
void auton(void) {
#include "autonom.h"
//vex::task AUTORUN (RUNAUTO);
//#include "usercontrol.h"
}


void usercontrol(void) {
vex::task RECORDER (record);
#include "usercontrol.h"
} 

int main() {
AutoRunning = 0;
   Lift.set(false); 
   Intake.set(false);
   wait(1000);
   Gyro.startCalibration();
   wait(2000);
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