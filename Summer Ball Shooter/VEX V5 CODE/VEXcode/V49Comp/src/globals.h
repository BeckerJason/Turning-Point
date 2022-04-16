extern char TrackColor = 'R';
extern char Alliance = 'R';
extern int AutoNumber = 1;//76 red 106 blue
extern float RPMGoal = 600,rpm = 0, rpmError = 100.0, TurnDiff = 0, TempHeight = 0, TempWidth = 0, TurnDir = 1, TempXDist = 200, GlobalFlagOffset = 160,TempYDist=0;
extern int  fly = 4, R = 4, Tran = 0,LiftVar=2, Shoot = 0, SnapToFlag = 0, AutoRunning = 0, FlipCount,TurretRunning=0;//flywheel//Roller//Transmission
extern int MoveReturn=0;
extern int T1 = 0, T3 = 0;
extern float avgSpeed = 0;
extern float avgError = 0;
extern float GlobalGyro = 0;
extern double AutoRPM=0;
extern int Color=1;
extern float FinalObject=20,TempObject=0;
extern char VisionLR='R';
extern float GlobalFlagOffsetL;
extern float GLOBALP=0.7,GLOBALI=0.000001,GLOBALD=4.1;
extern float FlagSum=0;
extern float objheight;
//float GLOBALP=1.4,GLOBALI=0.0000001,GLOBALD=8.1;

#define extern  bL2  Controller.ButtonL2.pressing()
#define extern bL1 Controller.ButtonL1.pressing()
#define extern bA  Controller.ButtonA.pressing()
#define extern bR2  Controller.ButtonR2.pressing()
#define extern bR1  Controller.ButtonR1.pressing()
#define extern bB  Controller.ButtonB.pressing()
#define extern bX  Controller.ButtonX.pressing()
#define extern bY  Controller.ButtonY.pressing()
#define extern bLeft Controller.ButtonLeft.pressing()
#define extern bRight  Controller.ButtonRight.pressing()
#define extern bUp  Controller.ButtonUp.pressing()
#define extern bDown  Controller.ButtonDown.pressing()
#define extern ch3  Controller.Axis3.value()
#define extern ch4  Controller.Axis4.value()
#define extern ch1  Controller.Axis1.value()
#define extern ch2  Controller.Axis2.value()
#define extern wait vex::task::sleep