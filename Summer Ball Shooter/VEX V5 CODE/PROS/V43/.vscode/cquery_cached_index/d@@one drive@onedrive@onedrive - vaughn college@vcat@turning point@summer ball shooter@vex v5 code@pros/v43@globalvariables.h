using namespace std;
char TrackColor = 'R';
char Alliance = 'R';
int AutoNumber = 1;//76 red 106 blue
float RPMGoal = 114, rpm = 0, rpmError = 100.0, TurnDiff = 0, TempHeight = 0, TempWidth = 0, TurnDir = 1, TempXDist = 200, GlobalFlagOffset = 160;
int  fly = 4, R = 4, Tran = 0, LiftVar = 2, Shoot = 0, SnapToFlag = 0, AutoRunning = 0, FlipCount, TurretRunning = 0;//flywheel//Roller//Transmission
int MoveReturn = 0;
int T1 = 0, T3 = 0;
float avgSpeed = 0;
float avgError = 0;
float GlobalGyro = 0;
int FlagYDim = 0;
double AutoRPM = 0;
int Color = 1;
float FinalObject = 20, TempObject = 0;
char VisionLR = 'R';
float GlobalFlagOffsetL;
float GLOBALP = 0.7, GLOBALI = 0.000001, GLOBALD = 4.1;
//float GLOBALP=1.4,GLOBALI=0.0000001,GLOBALD=8.1;
#define bL2  Controller.get_digital(E_CONTROLLER_DIGITAL_L2)
#define bL1 Controller.get_digital(E_CONTROLLER_DIGITAL_L1)
#define bA  Controller.get_digital(E_CONTROLLER_DIGITAL_A)
#define bR2  Controller.get_digital(E_CONTROLLER_DIGITAL_R2)
#define bR1  Controller.get_digital(E_CONTROLLER_DIGITAL_R1)
#define bB  Controller.get_digital(E_CONTROLLER_DIGITAL_B)
#define bX  Controller.get_digital(E_CONTROLLER_DIGITAL_X)
#define bY  Controller.get_digital(E_CONTROLLER_DIGITAL_Y)
#define bLeft Controller.get_digital(E_CONTROLLER_DIGITAL_LEFT)
#define bRight  Controller.get_digital(E_CONTROLLER_DIGITAL_RIGHT)
#define bUp  Controller.get_digital(E_CONTROLLER_DIGITAL_UP)
#define bDown  Controller.get_digital(E_CONTROLLER_DIGITAL_DOWN)
#define ch3  Controller.get_analog(E_CONTROLLER_ANALOG_LEFT_Y )
#define ch4  Controller.get_analog(E_CONTROLLER_ANALOG_LEFT_X )
#define ch1  Controller.get_analog(E_CONTROLLER_ANALOG_RIGHT_X )
#define ch2  Controller.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y)
#define wait delay
