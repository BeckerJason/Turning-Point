/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\Jason                                            */
/*    Created:      Sun Mar 24 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain Brain;

 

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////


// A global instance of vex::competition

vex::competition Competition;
// define you global instances of motors and other devices here
//#include "robot-config.h"
vex::controller Controller = vex::controller();
vex::digital_out Lift = vex::digital_out(Brain.ThreeWirePort.A);
vex::digital_out Trans = vex::digital_out(Brain.ThreeWirePort.B);
vex::digital_in IR = vex::digital_in(Brain.ThreeWirePort.C);
vex::line BallBottom = vex::line(Brain.ThreeWirePort.D);
vex::limit BallLoaded = vex::limit(Brain.ThreeWirePort.E);
vex::line RLine = vex::line(Brain.ThreeWirePort.F);
vex::line LLine = vex::line(Brain.ThreeWirePort.G);
vex::gyro Gyro = vex::gyro(Brain.ThreeWirePort.H);
  
vex::motor Hood = vex::motor(vex::PORT1,vex::gearSetting::ratio36_1,false);
vex::motor FlyL = vex::motor(vex::PORT6,vex::gearSetting::ratio6_1,true);
vex::motor FlyR = vex::motor(vex::PORT7,vex::gearSetting::ratio6_1,true);

vex::motor Turret = vex::motor(vex::PORT12,vex::gearSetting::ratio6_1,false);
vex::motor BallFeed = vex::motor(vex::PORT13,vex::gearSetting::ratio18_1,true);
vex::motor LF = vex::motor(vex::PORT14,vex::gearSetting::ratio18_1,true);
vex::motor LB = vex::motor(vex::PORT15,vex::gearSetting::ratio18_1,false);
vex::motor LM = vex::motor(vex::PORT16,vex::gearSetting::ratio18_1,true);
vex::motor RB = vex::motor(vex::PORT17,vex::gearSetting::ratio18_1,false);
vex::motor RM = vex::motor(vex::PORT18,vex::gearSetting::ratio18_1,true);
vex::motor RF = vex::motor(vex::PORT19,vex::gearSetting::ratio18_1,false);
vex::motor Roll = vex::motor(vex::PORT20,vex::gearSetting::ratio18_1,false);


vex::motor Roller2 = vex::motor(vex::PORT21,vex::gearSetting::ratio18_1,true);
#include "VisionCode1.h"
#include "VisionCode2.h"
#include "globals.h"
 void gyroInit(int);     
using namespace std;

#include "functions.h"
/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */ 
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/
//void pre_auton(void); 
//#include "pre_auton.h"
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
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/
//void autonomous(void);
//#include "autonomous.h"
void autonomous(void) {
    	//CapFlip.spin(vex::directionType::fwd, 15, vex::velocityUnits::rpm);
    Trans.set(0);
	fly = 2;
	run(Roll, 120);
	RPMGoal = 110;
	//wait(200);
	
	StopDrive();
    wait(50);
	Move(100, 38.74);//40
	wait(300);//200
	Move(100, -22.263);//20   
	Shoot = 1;
	Brain.resetTimer();
	while (Shoot == 1) { wait(10); if (Brain.timer(vex::timeUnits::msec) > 2000) { break; } }
	Shoot = 0;
	wait(50);//250
	if (Alliance == 'B') { pidTurn(90, 0.07, 0.05, 0.00, 4000); }//Amount initial, secondary
	else{ pidTurn(-90, 0.07, 0.001, 0.00, 4000);}
    ///leftDrive(-2);
    ///rightDrive(-2);					
    ///wait(300);
    R=6;
	run(Roll, -100);
	TrackColor=Alliance;
	//wait(100);
	//leftDrive(-50);
	//rightDrive(-50);
	//wait(1000);
    ToWall(-30);
	StopDrive();
    run(Roll,-50);
	while (Move(90, 50.26) != 1) {wait(10); }//Drive forward but if ball is seen by sensor kill flipper
//2400

   // while(Vision.objects[0].exists!=1){wait(5);}rightDrive(10);
    wait(200);//400  
 
	Move(90, -10);//480
	wait(300);//600
	if (Alliance == 'B') { pidTurn(53, 0.07, 0.02, 0.01, 3000); }//Amount initial, secondary	 
	else{ pidTurn(-50, 0.07, 0.001, 0.01, 3000);}
      	leftDrive(1);
	rightDrive(1);																	   
	wait(200);
    run(Roll, 100);
	//wait(300);
	Move(70, 22.6);//890/////GRAB BALL UNDER CAP
	//wait(100);//700
    //run(Roll, 0);
    //Move2(50,3);
    wait (100);//300
    run(Roll,100);
    //wait(300);
    //Move(30,-3);
    Move(100, -11.25);//203//3 was added
    wait(200);//400
        	if (Alliance == 'B') { pidTurn(35, 0.07, 0.01, 0.01, 3000); }//Amount initial, secondary
	else{ pidTurn(-29, 0.07, 0.001, 0.01, 3000);}
    wait(200);
	/*Shoot = 1;
    Brain.resetTimer();
	while (Shoo0t == 1) { wait(10); if (Brain.timer(vex::timeUnits::msec) > 2000) { break; } }
	Shoot = 0;*/
  	leftDrive(-100);
	rightDrive(-100);																	   
	wait(900);
	ToWall(-40);
	StopDrive(); 
    //wait(300);
				  
    Move(80,3);						 
    wait(200);
   if (Alliance == 'B') { pidTurn(-97, 0.07, 0.01, 0.01, 3000); }//Amount initial, secondary
	else{ pidTurn(97, 0.07, 0.001, 0.01, 3000);}
    
         if (Alliance == 'B') { TurnTurret(50);}
    else {TurnTurret(-50);}
      	//leftDrive(20);
	//rightDrive(20);
	//wait(2000);
    RPMGoal=145;
    ToWall(25);
    StopDrive();
     Move(80,-3);
     if (Alliance == 'B') { TurnTurret(-55);}
    else {TurnTurret(55);}
    if (Alliance == 'B') { pidTurn(-5, 0.04, 0.01, 0.01, 1000); }//Amount initial, secondary	 
	else{ pidTurn(5, 0.04, 0.01, 0.01, 1000);}
    Move(100,-11.18);//270//12.18
    Shoot = 1;
    Brain.resetTimer();
	while (Shoot == 1) { wait(10); if (Brain.timer(vex::timeUnits::msec) > 2000) { break; } }
	Shoot = 0;
     Move(90,3);//270//12.18
    wait(300);
			   
          if (Alliance == 'B') { pidTurn(100, 0.07, 0.05, 0.00, 3000); }//Amount initial, secondary
	else{ pidTurn(-100, 0.07, 0.001, 0.01, 3000);}					
    //wait(300);
      	//leftDrive(-20);
	//rightDrive(-20);									
	//wait(1500);
    ToWall(-30);
    StopDrive();
     //if (Alliance == 'B') { TurnTurret(-15);}
    //TurnTurret(15);
								 					
    //wait(300);
    Move(60,85);

	run(Roll, 0);
    R = 4;
    	fly = 4;
	while (1) { wait(100); }
    
}
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/
//void usercontrol(void);
//#include "usercontrol.h"

void usercontrol(void) {
    #ifdef DEBUG //if DEBUG is not defined earlier this section will not compile
    while(DEBUG){
        if (bUp == 1) { GLOBALP += .01; wait(100); }
		if (bDown == 1) { GLOBALP -= .01; wait(100); }
        if (bX== 1) { GLOBALI += .0000001; wait(100); }
		if (bB == 1) {GLOBALI -= .0000001; wait(100); }
        if (bR1== 1) { GLOBALD += .05; wait(100); }
		if (bR2 == 1) {GLOBALD -= .05; wait(100); }
                wait(10);
    }
    #endif
    R=2;
    AutoRunning=0;
	SnapToFlag = 0;
    GlobalFlagOffset=160;
    Shoot=0;
	//R = 4;
	FlipCount = 2;
	Tran = 2;
    RPMGoal=600;
	while (1)
	{
		if (bL2 == 1) { SnapToFlag = 1; }
		//else if ((fabs(ch3) > 2 || fabs(ch4) > 2) && SnapToFlag == 1) { SnapToFlag = 0; }
		else if ( AutoRunning == 0 && (abs(ch3) > 2 || abs(ch4) > 2))
        {   if(abs(LF.velocity(vex::velocityUnits::pct))>(ch3 + ch4))
        {
            run(LF, ((ch3 + ch4)+LF.velocity(vex::velocityUnits::pct)+LF.velocity(vex::velocityUnits::pct))/3); //(Axis3+Axis4)/2
			run(LM, ((ch3 + ch4)+LM.velocity(vex::velocityUnits::pct)+LM.velocity(vex::velocityUnits::pct))/3); //(Axis3+Axis4)/2
			run(LB, ((ch3 + ch4)+LB.velocity(vex::velocityUnits::pct)+LB.velocity(vex::velocityUnits::pct))/3); //(Axis3+Axis4)/2
			run(RF, ((ch3 - ch4)+RF.velocity(vex::velocityUnits::pct)+RF.velocity(vex::velocityUnits::pct))/3);//(Axis3-Axis4)/2
			run(RM, ((ch3 - ch4)+RM.velocity(vex::velocityUnits::pct)+RM.velocity(vex::velocityUnits::pct))/3);//(Axis3-Axis4)/2
			run(RB, ((ch3 - ch4)+RB.velocity(vex::velocityUnits::pct)+RB.velocity(vex::velocityUnits::pct))/3);//(Axis3-Axis4)/2
          
            } 
         else{
			run(LF, (ch3 + ch4)); //(Axis3+Axis4)/2
			run(LM, (ch3 + ch4)); //(Axis3+Axis4)/2
			run(LB, (ch3 + ch4)); //(Axis3+Axis4)/2
			run(RF, (ch3 - ch4));//(Axis3-Axis4)/2
			run(RM, (ch3 - ch4));//(Axis3-Axis4)/2
			run(RB, (ch3 - ch4));//(Axis3-Axis4)/2
         }
		}
		else if (AutoRunning == 0)
		{
			StopDrive();
		}
		else {}

		if (fly == 4 && bR1 == 0) { fly = 1; }//Flywheel
		else if (fly == 1 && bR1 == 1) { fly = 2; }
		else if (fly == 2 && bR1 == 0) { fly = 3; }
		else if (fly == 3 && bR1 == 1) { fly = 4; }
		else {}
        		if (R == 4 && bR2 == 0) { run(Roll, 0); R = 1; } //Roller //4 for off
		else if (R == 1 && bR2 == 1) { run(Roll, 80); R = 2; }//2 for on
		else if (R == 2 && bR2 == 0) { run(Roll, 80); R = 3; }
		else if (R == 3 && bR2 == 1) { run(Roll, 0); R = 4; }
		else {}

		if (Tran == 4 && bB == 0) { Trans.set(true); Tran = 1; } //Trans
		else if (Tran == 1 && bB == 1) { Trans.set(false); Tran = 2; }
		else if (Tran == 2 && bB == 0) { Trans.set(false); Tran = 3; }
		else if (Tran == 3 && bB == 1) { Trans.set(true); Tran = 4; }
		else {}
		
        if (LiftVar == 4 && bLeft == 0) { Lift.set(true); LiftVar = 1; } //Trans
		else if (LiftVar == 1 && bLeft == 1) { Lift.set(false); LiftVar = 2; }
		else if (LiftVar == 2 && bLeft == 0) {Lift.set(false); LiftVar = 3; }
		else if (LiftVar == 3 && bLeft == 1) { Lift.set(true); LiftVar = 4; }
		else {}
        if (bUp==1){AutoRPM=1;}
        else if (bDown==1){AutoRPM=0;}
		if (bA == 1&&Shoot==0) { Shoot = 1; } //Shoot ball
        else if (bRight == 1&&Shoot==0) { Shoot = 2; }
		else if (bY == 1) { Shoot = 0; } //Stop Mid shot
		else {}
		//if (bUp == 1 && RPMGoal < 200) { RPMGoal += 2; wait(200); }
		//if (bDown == 1 && RPMGoal > 50) { RPMGoal -= 2; wait(200); }
		//else {}
        if (abs(ch1)>5){run(Turret,ch1);SnapToFlag*=2;}
        else if (bL2==1){SnapToFlag=1;}
        else if (SnapToFlag>1){SnapToFlag=0;}
        else if (SnapToFlag==0){run(Turret,0);}
        wait(20);
        
	}
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
AutoRunning = 0;
    Lift.set(false);
    gyroInit(0);
	//Run the pre-autonomous function. 
	pre_auton();

	//Set up callbacks for autonomous and driver control periods.
	Competition.autonomous(autonomous);
	Competition.drivercontrol(usercontrol);

	//Prevent main from exiting with an infinite loop.                        
	while (1) {
		wait(100);//Sleep the task for a short amount of time to prevent wasted resources.
	}

	while (1) { wait(1000); }  
}