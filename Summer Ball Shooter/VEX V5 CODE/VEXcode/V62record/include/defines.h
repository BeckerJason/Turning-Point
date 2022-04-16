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
typedef enum _Toggle {on,off,twoshot,scan,reverse,MIDPLAT,HIGHPLAT=121,manual} ToggleMode;
ToggleMode fly = off;
ToggleMode roll = off;
ToggleMode hood=off;
ToggleMode ballfeed=off;
ToggleMode lift=off;
ToggleMode climb=off;
ToggleMode SnapToFlag=off;

//ToggleMode Shoot=off;
typedef enum _Shoot {zero=0,one=1,two=2,three=3,intake=4,handoff} ShootMode;
ShootMode Shoot=zero;
typedef enum _Alliance {Red=2,Blue=1} Alliance;
Alliance Color = Blue;  
typedef enum _HOODADJUST {no=0,yes=20} HOODADJUST;
HOODADJUST PLATFORM = no;  
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
bool platformprev=false; 
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
static int selection=2;
float SavedGyro=0;
int MATCHTIMER=0;
int frontball=0;
int ManualHood;
int HIGHCount=0;
  int MIDCount=0;
  bool preautoL=0;

bool bR1,bR2,bL1,bL2,bUp,bDown,bLeft,bRight, bX,bY,bA,bB;
int ch1,ch2,ch3,ch4;


//float GLOBALP=1.4,GLOBALI=0.0000001,GLOBALD=8.1;
};
#endif

 

#ifndef ROBOTSETUP
#define ROBOTSETUP
vex::brain Brain;
vex::controller   Controller = vex::controller(vex::controllerType::primary);
vex::controller Partner= vex::controller(vex::controllerType::partner);
vex::line   RLine = vex::line(Brain.ThreeWirePort.A);
vex::digital_out   Lift = vex::digital_out(Brain.ThreeWirePort.B);
vex::digital_in   IR = vex::digital_in(Brain.ThreeWirePort.C);
vex::line   BallBottom = vex::line(Brain.ThreeWirePort.D);
vex::line   BallTop= vex::line(Brain.ThreeWirePort.E);
vex::line   LLine = vex::line(Brain.ThreeWirePort.F);
vex::gyro   Gyro = vex::gyro(Brain.ThreeWirePort.H);
vex::digital_out   Intake = vex::digital_out(Brain.ThreeWirePort.G);

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
#define   btL2  Controller.ButtonL2.pressing()
#define   btL1 Controller.ButtonL1.pressing()
#define   btA  Controller.ButtonA.pressing()
#define   btR2  Controller.ButtonR2.pressing()
#define   btR1  Controller.ButtonR1.pressing()
#define   btB  Controller.ButtonB.pressing()
#define   btX  Controller.ButtonX.pressing()
#define   btY  Controller.ButtonY.pressing()
#define   btLeft Controller.ButtonLeft.pressing()
#define   btRight  Controller.ButtonRight.pressing()
#define   btUp  Controller.ButtonUp.pressing()
#define   btDown  Controller.ButtonDown.pressing()
#define   cht3  Controller.Axis3.value()
#define   cht4  Controller.Axis4.value()
#define   cht1  Controller.Axis1.value()
#define   cht2  Controller.Axis2.value()
#define   bpL2  Partner.ButtonL2.pressing()
#define   bpL1 Partner.ButtonL1.pressing()
#define   bpA  Partner.ButtonA.pressing()
#define   bpR2  Partner.ButtonR2.pressing()
#define   bpR1  Partner.ButtonR1.pressing()
#define   bpB  Partner.ButtonB.pressing()
#define   bpX  Partner.ButtonX.pressing()
#define   bpY  Partner.ButtonY.pressing()
#define   bpLeft Partner.ButtonLeft.pressing()
#define   bpRight  Partner.ButtonRight.pressing()
#define   bpUp  Partner.ButtonUp.pressing()
#define   bpDown  Partner.ButtonDown.pressing()
#define   chp3  Partner.Axis3.value()
#define   chp4  Partner.Axis4.value()
#define   chp1  Partner.Axis1.value()
#define   chp2  Partner.Axis2.value()
#define   wait vex::task::sleep 
#define BALLDETECTION 35  
#define TOTALSNAPSHOTS 7
#define BRAKE(x,y) x.stop(vex::brakeType::y)
#define DEBUG
#define TILE 48
#define ENDSHOT 42000
#endif

#ifndef FUNCTIONS
#define FUNCTIONS
int GyroTrack();
void run(vex::motor,double);
void runRPM(vex::motor, double);
float enc(vex::motor);
int PrintScreen();
int RPMCalc();
int ShootBall();
int TurnToFlag();
int TIMER2();
void StopDrive(vex::brakeType);
void rightDrive(int);
void leftDrive(int); 
int Driver();
void Turn(double ,int); 
void T(float, float);
void pidTurn(float , float, float , float, int);
int Move(float, float,bool,vex::brakeType);
int Move2(float, float);
int MoveNoStop(float, float);
void ToWall(double);
void TurnTurret(double);
void TurnTurretTo(double,double);
int ScanFlags(int,_Toggle,_Shoot);
void SetDriveTorque(double);
int ENDAUTOTIMER();
#endif 