/*----------------------------------------------------------------------------*/
/*                                                                            */
/*  This file includes standard libraries as well as the vex libraries        */
/*      GLOBAL VARIABLES ARE ENTERED IN THE 'G' NAMESPACE HERE                */
/*          ROBOT  PORT CONFIGURATIONS ARE ENTERED HERE                        */
/*            PROTOTYPES FOR FUNTIONS ARE ENTERED HERE                        */
/*----------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> 
#include <cmath>
#include <cstdlib>
#include "v5.h"
#include "v5_vcs.h"
 
 
#ifndef ENUMS
#define ENUMS
typedef enum _Toggle {on,off,twoshot,scan,reverse} ToggleMode;
ToggleMode fly = off;
ToggleMode roll = off;
ToggleMode hood=off;
ToggleMode ballfeed=off;
ToggleMode lift=off;
ToggleMode climb=off;
ToggleMode SnapToFlag=off;

//ToggleMode Shoot=off;
typedef enum _Shoot {zero=0,one=1,two=2,three=3,intake=4} ShootMode;
ShootMode Shoot=zero;
typedef enum _Alliance {Red=2,Blue=1} Alliance;
Alliance Color = Red;  
#endif

#ifndef GLOBALS
#define GLOBALS
namespace G{
  #define TOTALSNAPSHOTS 7
class VisionObject {
  public:
          int     id[TOTALSNAPSHOTS];
          int     originX[TOTALSNAPSHOTS];
          int     originY[TOTALSNAPSHOTS];
          int     centerX[TOTALSNAPSHOTS];
          int     centerY[TOTALSNAPSHOTS];
          int     width[TOTALSNAPSHOTS];
          int     height[TOTALSNAPSHOTS];
          double  angle[TOTALSNAPSHOTS];
          bool    exists[TOTALSNAPSHOTS];
} GreenMarker;

bool flyprev=false;
bool rollprev=false;
bool hoodprev=false;
bool ballfeedprev=false;
bool liftprev=false;
static float RPMGoal = 600, rpmError = 100.0, TurnDiff = 0, THeight = 0, TWidth = 0, TurnDir = 1, TXDist = 200, GlobalFlagOffset = 160,TYDist=0;
static int AutoRunning = 0;
static int MoveReturn=0,balls=0;
static int T1 = 0, T3 = 0;
static float avgSpeed = 0;
static float avgError = 0;
static float GlobalGyro = 0;
static float FinalObject=20;
static float GLOBALP=0.7,GLOBALI=0.000001,GLOBALD=4.1;
static float FlagSum=0;
static float objheight;
static int selection;
//float GLOBALP=1.4,GLOBALI=0.0000001,GLOBALD=8.1;
};
#endif



#ifndef ROBOTSETUP
#define ROBOTSETUP
vex::brain Brain;
vex::controller   Controller = vex::controller();
vex::line   RLine = vex::line(Brain.ThreeWirePort.A);
vex::digital_out   Lift = vex::digital_out(Brain.ThreeWirePort.B);
vex::digital_in   IR = vex::digital_in(Brain.ThreeWirePort.C);
vex::line   BallBottom = vex::line(Brain.ThreeWirePort.D);
vex::line   BallTop= vex::line(Brain.ThreeWirePort.E);
vex::line   LLine = vex::line(Brain.ThreeWirePort.F);
vex::gyro   Gyro = vex::gyro(Brain.ThreeWirePort.G);
vex::digital_out   Intake = vex::digital_out(Brain.ThreeWirePort.H);

vex::motor Hood = vex::motor(vex::PORT1,vex::gearSetting::ratio36_1,false);
vex::motor FlyL = vex::motor(vex::PORT6,vex::gearSetting::ratio6_1,true);
vex::motor FlyR = vex::motor(vex::PORT7,vex::gearSetting::ratio6_1,true);
vex::motor Turret = vex::motor(vex::PORT12,vex::gearSetting::ratio6_1,false);
vex::motor BallFeed = vex::motor(vex::PORT13,vex::gearSetting::ratio18_1,true);
vex::motor LF = vex::motor(vex::PORT14,vex::gearSetting::ratio18_1,true);
vex::motor LB = vex::motor(vex::PORT15,vex::gearSetting::ratio18_1,true);
vex::motor LM = vex::motor(vex::PORT16,vex::gearSetting::ratio18_1,false);
vex::motor RB = vex::motor(vex::PORT17,vex::gearSetting::ratio18_1,false);
vex::motor RM = vex::motor(vex::PORT18,vex::gearSetting::ratio18_1,true);
vex::motor RF = vex::motor(vex::PORT19,vex::gearSetting::ratio18_1,false);
vex::motor Roll = vex::motor(vex::PORT20,vex::gearSetting::ratio6_1,false);
#include "VisionDef.h"
#define   bL2  Controller.ButtonL2.pressing()
#define   bL1 Controller.ButtonL1.pressing()
#define   bA  Controller.ButtonA.pressing()
#define   bR2  Controller.ButtonR2.pressing()
#define   bR1  Controller.ButtonR1.pressing()
#define   bB  Controller.ButtonB.pressing()
#define   bX  Controller.ButtonX.pressing()
#define   bY  Controller.ButtonY.pressing()
#define   bLeft Controller.ButtonLeft.pressing()
#define   bRight  Controller.ButtonRight.pressing()
#define   bUp  Controller.ButtonUp.pressing()
#define   bDown  Controller.ButtonDown.pressing()
#define   ch3  Controller.Axis3.value()
#define   ch4  Controller.Axis4.value()
#define   ch1  Controller.Axis1.value()
#define   ch2  Controller.Axis2.value()
#define   wait vex::task::sleep
#define BALLDETECTION 35  
#define TOTALSNAPSHOTS 7
#endif

#ifndef FUNCTIONS
#define FUNCTIONS
void brake(vex::motor,char);
int GyroTrack();
void run(vex::motor,double);
void brake(vex::motor, char);
void runRPM(vex::motor, double);
float enc(vex::motor);
int PrintScreen();
int RPMCalc();
int ShootBall();
int TurnToFlag();
int TIMER2();
void StopDrive();
void rightDrive(int);
void leftDrive(int);
int Driver();
void Turn(double ,int);
void T(float, float);
void pidTurn(float , float, float , float, int);
int Move(float, float);
int Move2(float, float);
int MoveNoStop(float, float);
void ToWall(double);
void TurnTurret(double);
int ScanFlags(int,_Toggle,_Shoot);
#endif 