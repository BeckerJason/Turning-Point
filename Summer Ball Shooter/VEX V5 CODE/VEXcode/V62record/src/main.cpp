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
using namespace std;
#include <fstream>
std::fstream file;
  int record()
{
Brain.resetTimer();
while(1)
{
bR1=btR1;
bR2=btR2;
bL1=btL1;
bL2=btL2;
bA=btA;
bB=btB;
bX=btX;
bY=btY;
bLeft=btLeft;
bRight=btRight;
bUp=btUp;
bDown=btDown;
ch3=cht3;
ch2=cht2;
ch1=cht1;
ch4=cht4;

file.open("RecordedAuto4.txt",ofstream::ate|ofstream::out|ofstream::app);
file<<"bR1="<<bR1<<";";
file<<"bR2="<<bR2<<";";
file<<"bL1="<<bL1<<";";
file<<"bL2="<<bL2<<";";
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
file<<"while(fmod(Brain.timer(vex::timeUnits::msec),25)){wait(1);}"<<endl;
//Brain.resetTimer();
file.close();
while(fmod(Brain.timer(vex::timeUnits::msec),25)){wait(1);}
}
return 0;
}


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
  
  //vex::task ceice (ENDAUTOTIMER);
  vex::task Driver (DriverCode);
  #include "RECORDED.h"
//#include "autonom.h"
}


void usercontrol(void) {
  preautoL=false;
G::MATCHTIMER=0; 
vex::task cnwj (record);
vex::task ceice (ENDAUTOTIMER);
vex::task Driver (DriverCode);

 //#include "usercontrol.h"
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