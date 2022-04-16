#include "defines.h"

using namespace G;
using namespace std;
void brake(vex::motor,char);
int GyroTrack()
  {
	float GyroAdd = 0;
	float GyroTCheck = 0;

	while (1)
	{
		GyroAdd = Gyro.value(vex::rotationUnits::raw) - GyroTCheck;
		GyroTCheck =Gyro.value(vex::rotationUnits::raw);
		GlobalGyro += GyroAdd;
		wait(5);
	}
	return 0;
  }

void run(vex::motor motorname, double speed)
  {
	if (speed != 0) { motorname.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct); }
	else { motorname.stop(vex::brakeType::brake); }
  }
void brake(vex::motor motorname, char BRAKE)
  {
	if (BRAKE == 'c') { motorname.stop(vex::brakeType::coast); }
	else if (BRAKE == 'h') { motorname.stop(vex::brakeType::hold); }
	else { motorname.stop(vex::brakeType::brake); }
  }
void runRPM(vex::motor motorname, double speed)
  {
	if (speed != 0) { motorname.spin(vex::directionType::fwd, speed, vex::velocityUnits::rpm); }
	else { motorname.stop(vex::brakeType::brake); }
  }
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
float enc(vex::motor motorname) {return motorname.rotation(vex::rotationUnits::deg);}
int PrintScreen()
  {
	  while (1)
	  {
		  Brain.Screen.clearScreen(vex::color::black);
		  Brain.Screen.setPenColor(vex::color::white);
		  Brain.Screen.printAt(1, 160, "RPM %1.2f", FlyL.velocity(vex::velocityUnits::rpm));
		  Brain.Screen.printAt(1, 180, "RPM Goal %f", RPMGoal);
	    Brain.Screen.printAt(1, 60, "%f", Gyro.value(vex::rotationUnits::raw));
      //int BallVal=BallLoadSensor.value(vex::analogUnits::pct);
		  Brain.Screen.printAt(80, 80, "%d",BallTop.value(vex::percentUnits::pct) );
      Brain.Screen.printAt(100, 80, "%d",BallBottom.value(vex::percentUnits::pct) );
      Brain.Screen.printAt(300, 100, "%d",RLine.value(vex::percentUnits::pct) );
      Brain.Screen.printAt(300, 130, "%d",LLine.value(vex::percentUnits::pct) );
      //Brain.Screen.printAt(100, 20, "P: H:%d    Y:%d",VisionL.objects[FinalObject].height,VisionL.objects[FinalObject].centerY);
      Brain.Screen.printAt(100, 40, "P: H:%d    Y:%d",Vision.objects[FinalObject].height,Vision.objects[FinalObject].centerY);
      Brain.Screen.printAt(340, 100, "OH: %1.8f",objheight);
      Brain.Screen.printAt(340, 120, "I: %1.8f",GLOBALI);
      Brain.Screen.printAt(340, 140, "D: %1.8f",GLOBALD);
      Brain.Screen.printAt(1, 140, "VisionLR: %c",VisionLR);
      if (rpmError < 5.0) { Brain.Screen.setPenColor(vex::color::green); if (Shoot == 1) { Controller.rumble("."); } }
		  else { Brain.Screen.setPenColor(vex::color::white); }
	    Brain.Screen.printAt(1, 120, "RPM error %1.2f", rpmError);
      wait(75);
	  }
    return 0;
  }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RPMCalc()
  {
	  while (1)
	  {    
      FlyL.setStopping(vex::brakeType::coast);
      FlyR.setStopping(vex::brakeType::coast);
      int TRPM = RPMGoal;
		  if (fly == 2 || fly == 3)
		  {
			  while ((fly == 2 || fly == 3) )//&& RPMGoal == TRPM)
			  {
          rpmError = abs(RPMGoal - (FlyL.velocity(vex::velocityUnits::rpm)));
          FlyR.spin(vex::directionType::fwd, RPMGoal, vex::velocityUnits::rpm);
          FlyL.spin(vex::directionType::fwd, RPMGoal, vex::velocityUnits::rpm);   
        }
		  }
		  else
		  {
        FlyL.stop(vex::brakeType::coast); FlyR.stop(vex::brakeType::coast);
			  while ((fly == 4 || fly == 1) && RPMGoal == TRPM) 
        { wait(100); }
		  }
      wait(10);
	    }
	  return 0;
  }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ShootBall()
  {
	  while (1)
	  {
		  if (Shoot >= 1) //when button is pressed
		  {
        fly = 2;
        if (Shoot==2)
        {
          while(Shoot!=0&&(BallBottom.value(vex::percentUnits::pct)>50&&BallTop.value(vex::percentUnits::pct)==0))
          {Shoot=-1;wait(10);}
          Shoot=2;
          while(rpmError>15&&Shoot==2)
          {wait(10);}
          while(rpmError<60&&Shoot==2)
          {
            run(BallFeed,80);
            run(Roll,100);
            wait(10);
          }
          Shoot=-1;
          while(rpmError>80&&Shoot==-1)
          {wait(10);}
          if (Shoot==-1)
          {Shoot=2;} 
          while(rpmError<90&&Shoot==2)
          {
            run(BallFeed,100);
            run(Roll,100);
            wait(10);
          }
          Shoot=0;
        }              
        else if (Shoot==1) 
        {
          while(rpmError>15&&Shoot==1)
          {wait(10);}
          while(rpmError<60&&Shoot==1)
          {
            run(BallFeed,100);
            run(Roll,100);
            wait(10);
          }
        Shoot=0;   
        }
      }       
      wait(100); 
    }
    return 0;
  }
int TurnToFlag()
{ int Counter=0;
	while (1)
	{ 
		
            while(SnapToFlag == 1)
            {if (bX==1){SnapToFlag = 0;}
										  
             Vision.takeSnapshot(Color, 7);
			  //VisionL.takeSnapshot(Color, 7);
			//Brain.Screen.setPenColor(vex::color::red);
            TXDist = 400;
							
		GlobalFlagOffset=160;
        //GlobalFlagOffsetL=310-GlobalFlagOffset;
		for (int i = 0; Vision.objects[i].exists == 1;i++)//||VisionL.objects[i].exists == 1; i++)
		{	
			if (Vision.objects[i].exists == 1&&fabs(GlobalFlagOffset - Vision.objects[i].centerX) < fabs(TXDist)) { TXDist = GlobalFlagOffset - Vision.objects[i].centerX;VisionLR='R'; }
			else {}
            
           /* if (VisionL.objects[i].exists == 1&&fabs(GlobalFlagOffsetL - VisionL.objects[i].centerX) < fabs(TXDist)) { TXDist = GlobalFlagOffsetL - VisionL.objects[i].centerX; VisionLR='L'; }
			else {}*/
		}
            
		
    int TObject=9;
		TWidth = 0;
		THeight = 0;
		TYDist=400.0;			
		for (int i = 0; Vision.objects[i].exists == 1; i++)
		{
			//if (Vision.objects[i].width > 8 && Vision.objects[i].height > 8) { Brain.Screen.printAt(230, 20 + i * 20, "X:%d,Y:%d W:%d H:%d D:%1.2f", Vision.objects[i].centerX, Vision.objects[i].centerY, Vision.objects[i].width, Vision.objects[i].height, 0.0157*pow(Vision.objects[i].height, 2) - 1.0842*Vision.objects[i].height + 19.93); }
			if ((Vision.objects[i].width > 8 && Vision.objects[i].height > 8) && (Vision.objects[i].centerX > (GlobalFlagOffset - 10 - TXDist) && Vision.objects[i].centerX < (GlobalFlagOffset + 10 - TXDist)) && Vision.objects[i].centerY < TYDist) { TYDist = Vision.objects[i].centerY; TWidth = GlobalFlagOffset - Vision.objects[i].centerX; THeight=Vision.objects[i].height;  TObject=i; }
																																								   
			else {}
			}
		
             
		 FinalObject=TObject;	
		TurnDiff = TWidth;
		if (TurnDiff > 0) { TurnDir = 1; }
		else { TurnDir = -1; }
			    if(SnapToFlag == 1 && fabs(TurnDiff) > 4)
			    {
					double speed;
                    speed=pow(fabs(TurnDiff),1.1)*TurnDir*.5;
					Turret.spin(vex::directionType::fwd, -speed, vex::velocityUnits::pct);     
                }
				else{Turret.stop(vex::brakeType::brake);}
             
             
           
             
            
           // float AngleHeight=Vision.objects[FinalObject].height;     
            if (SnapToFlag==1&&THeight>8)
             {if (TYDist<(-6.3123*THeight+300.0))//high
             {FlagSum+=-0.2167*pow(THeight,2)+7.7833*THeight-48.9;}
              else{FlagSum+=-0.0318*pow(THeight,2)+1.5924*THeight+14.971;}
               Counter++;
                
            }
             
             if(AutoRPM==1&&Counter%6==0)//if the flagsum has been added 50 times
             {Hood.startRotateTo((FlagSum/6),vex::rotationUnits::deg,50,vex::velocityUnits::pct);}
             else if (AutoRPM==0){Hood.startRotateTo(0,vex::rotationUnits::deg,50,vex::velocityUnits::pct);}
             if (Counter==6){Counter=0;FlagSum=0;}
                      wait(17);
            }
			//wait(750);
			//SnapToFlag = 0;
	Hood.startRotateTo(0,vex::rotationUnits::deg,50,vex::velocityUnits::pct);	
    wait(10);
	}
	return 0;
}



////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
int TIMER2()
{while (1)
	{wait(1);
		T3 += 1;}
	return 0;}
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
void StopDrive()
  {
	brake(RF, 'b');
	brake(RM, 'b');
	brake(RB, 'b');
	brake(LF, 'b');
	brake(LM, 'b');
	brake(LB, 'b');
  }
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
void rightDrive(int power)
{	run(RF, power);	run(RM, power);	run(RB, power);}
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
void leftDrive(int power)
{run(LF, power);run(LM, power);	run(LB, power);
}
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
int Driver()
{BallFeed.setTimeout(3,vex::timeUnits::sec);
 int count=0;   
    while(1)
    { 
        //////Front Roller
        if (Shoot==0&&btn)
        else if (Shoot==0&&IR.value()==0&&BallBottom.value(vex::percentUnits::pct)<69&&BallTop.value(vex::percentUnits::pct)<69){run(Roll,0);}//1 1 1 
        else if (Shoot==0&&BallBottom.value(vex::percentUnits::pct)<69&&BallTop.value(vex::percentUnits::pct)<69){run(Roll,0);}//1 1 X
        else if (Shoot==0&&BallBottom.value(vex::percentUnits::pct)<69&&BallTop.value(vex::percentUnits::pct)>69&&IR.value()==0){run(Roll,30);}//0 1 1
        else if (Shoot==0&&BallBottom.value(vex::percentUnits::pct)>69&&BallTop.value(vex::percentUnits::pct)<69&&IR.value()==0){run(Roll,30);}//1 0 1
        else if (Shoot==0&&IR.value()==0){run(Roll,30);} //X X 1
        else if (Shoot==0){run(Roll,0);} //X X X

      //Ball LOader
      if (Shoot==0&&BallBottom.value(vex::percentUnits::pct)<67&&BallTop.value(vex::percentUnits::pct)<67){run(BallFeed,0);}
      else if (Shoot==0&&BallBottom.value(vex::percentUnits::pct)<67&&IR.value()==0){run(BallFeed,30);}
      else if (Shoot==0&&BallTop.value(vex::percentUnits::pct)<67){run(BallFeed,0);}
      else if (Shoot==0&&BallBottom.value(vex::percentUnits::pct)>67&&IR.value()==0){run(BallFeed,30);}
      else if (Shoot==0&&BallBottom.value(vex::percentUnits::pct)<67){run(BallFeed,0);}
      else if (Shoot==0){run(BallFeed,0);}
 //if (R==4){run(Roll,0);}
 //if (R==2){run(Roll,80);}
 wait(10);
}
 return 0;}
////////////////////////////////////////////////////////////////////////////
void Turn(double turningDegree, int turningspeed)
{
int dir; 
if (turningDegree>0){dir =1;}
else{dir=-1;}
    LF.resetRotation();
	RF.resetRotation();
    int Loffset,Roffset;
        double rotation=3*turningDegree;
        while (abs(enc(RF))<abs(rotation)||abs(enc(LF))<abs(rotation))
        {		if (abs(enc(RF))<abs(enc(LF))){Loffset=dir*10; Roffset=0;}
		else if (abs(enc(LF))<abs(enc(RF))){Loffset=0; Roffset=-dir*10;}
		else{Loffset=0; Roffset=0;}
        turningspeed*=dir;
		
		rightDrive(turningspeed+Roffset);
		leftDrive(-turningspeed+Loffset);
           /* if ((abs(enc(RF)))<fabs(rotation)){rightDrive(turningspeed*dir);}
            else if ((abs(enc(RF)))>fabs(rotation)+1){rightDrive(-turningspeed*dir/3);}
            else{	
                brake(RF, 'b');
	brake(RM, 'b');
	brake(RB, 'b');}
            if( abs(enc(LF))<fabs(rotation)){leftDrive(-turningspeed*dir);}
            else if( abs(enc(LF))>fabs(rotation)+1){leftDrive(turningspeed*dir/3);}
            else{brake(LF, 'b');
	brake(LM, 'b');
	brake(LB, 'b');}
            wait(5);
            */
          wait(5);
        }
    wait(10);
    dir*=-1;
     while (abs(enc(RF))>abs(rotation)||abs(enc(LF))>abs(rotation))
     {
     if ((abs(enc(RF)))>abs(rotation)){rightDrive(turningspeed*dir/3);}
            else{	
                brake(RF, 'b');
	brake(RM, 'b');
	brake(RB, 'b');}
            if( abs(enc(LF))>abs(rotation)){leftDrive(-turningspeed*dir/3);}
            else{brake(LF, 'b');
	brake(LM, 'b');
	brake(LB, 'b');}
            wait(5);
     }
    brake(RF, 'h');
	brake(RM, 'h');
	brake(RB, 'h');
    brake(LF, 'h');
	brake(LM, 'h');
	brake(LB, 'h');

     /*while (abs(enc(RF))>fabs(rotation)||abs(enc(LF))>fabs(rotation))
        {		if (abs(enc(RF))>abs(enc(LF))){Loffset=dir*5; Roffset=0;}
		else if (abs(enc(LF))>abs(enc(RF))){Loffset=0; Roffset=-dir*5;}
		else{Loffset=0; Roffset=0;}
        turningspeed*=dir;
		
		rightDrive(turningspeed/3+Roffset);
		leftDrive(-turningspeed/3+Loffset);
          
            wait(5);
            
        }*/


    


    wait(100);
}



void T(float degree, float vel)
{   
    T3=0;
    LF.resetRotation();
	RF.resetRotation();
	float x;
	float dir,Loffset, Roffset,speeed;
	if (degree<0){dir=-1;}
	else{dir=1;}//
	degree=degree*10;//Correction factor for this specific gyro
	while(fabs(GlobalGyro)>(abs(degree))||fabs(GlobalGyro)<(abs(degree)-10) && T3<2500)
	{
		if (abs(enc(RF))<abs(enc(LF))){Loffset=dir*10; Roffset=0;}
		else if (abs(enc(LF))<abs(enc(RF))){Loffset=0; Roffset=-dir*10;}
		else{Loffset=0; Roffset=0;}
		x=(degree-GlobalGyro)/10;
		speeed=vel;//abs(100*x/(degree*1.25))+20;/*pow((x/16),2);*//*100*cos(x/2)/2+(100/2);*/
		speeed=dir*speeed;
		rightDrive(speeed+Roffset);
		leftDrive(-speeed+Loffset);
	}
    wait(30);
    dir*=-1;
    	while(fabs(GlobalGyro)>(abs(degree)+10)||fabs(GlobalGyro)<(abs(degree)-10) && T3<2500)
	{
		if (abs(enc(RF))<abs(enc(LF))){Loffset=dir*5; Roffset=0;}
		else if (abs(enc(LF))<abs(enc(RF))){Loffset=0; Roffset=-dir*5;}
		else{Loffset=0; Roffset=0;}
		x=(degree-GlobalGyro)/10;
		speeed=vel;//abs(100*x/(degree*1.25))+20;/*pow((x/16),2);*//*100*cos(x/2)/2+(100/2);*/
		speeed=dir*speeed;
		rightDrive(speeed/3+Roffset);
		leftDrive(-speeed/3+Loffset);
	}
	rightDrive(0);
	leftDrive(0);
}






////////////////////////////////////////////////////////////////////////////
int MoveCounter = 0;
int PID_MOTOR_SCALE = 1;
int PID_MOTOR_MAX = 100;
int PID_MOTOR_MIN = (-100);
int PID_INTEGRAL_LIMIT = 50;

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
float  pid_Kp = 0.59;
float  pid_Ki = 0.09;//0.05;
float  pid_Kd = 0.0;//.05;
int   pidRunning = 0; //TURN ON OR OFF PID
float  RequestedAngle = 0, pidDriveR;
int angleSentinel = 1;

void pidTurn(float globalDegrees, float pid_Kp, float pid_Ki, float pid_Kd, int timeout)
{	int direction = 0;
	GlobalGyro = 0;
	Brain.resetTimer();
	float  pidError = 0;
	float  pidLastError = 0;
	float  pidIntegral = 0;
	float  pidDerivative = 0;
	float pidDriveR = 0;

	T3 = 0;
	while (T3 < timeout)
	{
		//Calculate Error//(Convert Dintance in inches to encoder ticks)
		pidError = fabs(globalDegrees *10) - fabs(GlobalGyro);

		// integral - if Ki is not 0(can put threshold)
		if (pid_Ki != 0)
		{
			// If we are inside controlable window then integrate the error
			if (fabs(pidError) < PID_INTEGRAL_LIMIT)	pidIntegral = pidIntegral + pidError;
			else	pidIntegral = 0;
		}
		else	pidIntegral = 0;
		///////////////////////////////////////
		//CALCULATE DERIVATIVE/////////////////
		pidDerivative = pidError - pidLastError;
		pidLastError = pidError;
		//////////////////////////////////////
		//CALCULATE DRIVE/////////////////////
		pidDriveR = (pid_Kp * pidError) + (pid_Ki * pidIntegral) + (pid_Kd * pidDerivative);
		///////////////////////////////////////
		//LIMIT DRIVE//////////////////////////
		if (pidDriveR > PID_MOTOR_MAX)	pidDriveR = PID_MOTOR_MAX;
		if (pidDriveR < PID_MOTOR_MIN)	pidDriveR = PID_MOTOR_MIN;
		///////////////////////////////////////
		//SEND POWER TO MOTORS/////////////////
		if (globalDegrees > 0)	direction = 1;
		if (globalDegrees < 0) direction = -1;
		//if(gmoveandturn==false)
		rightDrive(direction * pidDriveR * PID_MOTOR_SCALE);
		leftDrive(-direction * pidDriveR * PID_MOTOR_SCALE);
		if ((fabs(pidError) < 5) && (fabs(avgSpeed) < 10)) {
			StopDrive();
			break;
		}
		if (Brain.timer(vex::timeUnits::msec) < 40) { avgError += pidError; }
		else { avgSpeed = avgError / 3; avgError = 0; Brain.resetTimer(); }

		//REFRESH RATE 60Hz
		wait(16);
	}
	StopDrive();
}
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
int Move(float speed, float dist) {

	float dir;
	if (dist < 0) { dir = -1; }
	else { dir = 1; }
	float Tdir = dir;
	leftDrive(dir * 5);
	rightDrive(dir * 5);
	wait(200);
	StopDrive();
	wait(100);
    LF.resetRotation();
	RF.resetRotation();
	wait(20);
	double counter = 0;
	while (fabs(enc(LF)) < abs((dist * 360.0 / (4.0*3.14159)))) {


		float Roffset = 1.0;
		if (fabs(enc(LF)) < fabs((enc(RF)) + 5)) { Roffset = 0.9; }
		else if (fabs(enc(LF)) > fabs(enc(RF)) - 5) { Roffset = 1.1; }
		else {}
		if (counter < 100) { dir = Tdir * counter*0.01; counter+=.75; }
		else { dir = Tdir; }
		run(RF, speed*Roffset*dir);
		run(LF, speed*dir);
		run(RM, speed*Roffset*dir);
		run(LM, speed*dir);
		run(RB, speed*Roffset*dir);
		run(LB, speed*dir);
		wait(12);
    }
	leftDrive(0);
	rightDrive(0);
	return 1;
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
int Move2(float speed, float dist) {
int status=1;
	float dir;
	if (dist < 0) { dir = -1; }
	else { dir = 1; }
	float Tdir = dir;
    if (MoveReturn==0){	LF.resetRotation();
	RF.resetRotation();MoveReturn=1;}
	wait(20);
	int counter = 0;
	if (fabs(enc(LF)) < abs((dist * 360 / (4.0*3.14159)))){status=1;}
    else{status=0;}


		float Roffset = 1.0;
		if (fabs(enc(LF)) < fabs((enc(RF)) + 5)) { Roffset = 0.9; }
		else if (fabs(enc(LF)) > fabs(enc(RF)) - 5) { Roffset = 1.1; }
		run(RF, speed*Roffset*dir);
		run(LF, speed*dir);
		run(RM, speed*Roffset*dir);
		run(LM, speed*dir);
		run(RB, speed*Roffset*dir);
		run(LB, speed*dir);
		wait(10);
	 
    if (status==0)
    {
	leftDrive(0);
	rightDrive(0);
    }
    MoveReturn=status;
	return status;
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
int MoveNoStop(float speed, float dist) {

	float dir;
	if (dist < 0) { dir = -1; }
	else { dir = 1; }
	float Tdir = dir;
	leftDrive(dir * 5);
	rightDrive(dir * 5);
	wait(200);
	StopDrive();
	wait(100);
	LF.resetRotation();
	RF.resetRotation();
	wait(20);
	int counter = 0;
	while (fabs(enc(LF)) < abs((dist * 360 / (4.0*3.14159)))) {


		float Roffset = 1.0;
		if (fabs(enc(LF)) < fabs((enc(RF)) + 5)) { Roffset = 0.9; }
		else if (fabs(enc(LF)) > fabs(enc(RF)) - 5) { Roffset = 1.1; }
		else {}
		if (counter < 100) { dir = Tdir * counter*0.01; counter++;}
		else { dir = Tdir; }
		run(RF, speed*Roffset*dir);
		run(LF, speed*dir);
		run(RM, speed*Roffset*dir);
		run(LM, speed*dir);
		run(RB, speed*Roffset*dir);
		run(LB, speed*dir);
		wait(10);
    }
        return 0;
}
void ToWall(double vel)
{T3=0;
float TLF=0, TRF=0;
do{
TLF=enc(LF);
TRF=enc(RF);
rightDrive(vel);
leftDrive(vel);
wait(100);
}while ((TLF!=enc(LF)||TRF!=enc(RF))&&(RLine.value(vex::percentUnits::pct)<68||LLine.value(vex::percentUnits::pct)<68)&&T3<1500);
StopDrive();
}
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
void TurnTurret(double degree)
  {   
  Turret.resetRotation();
  int dir;
  if (degree>0)
    {dir=-1;}
  else
    {dir=1;}
  //degree>0 means left
  double count=5;
  double gearratio=12.0/175.0;
  while(abs(Turret.rotation(vex::rotationUnits::deg))<abs((degree/gearratio)))
    {  
      //if(LeftTurretLimit.pressing()==1){break;}
      // else if(RightTurretLimit.pressing()==1){break;}
      if ((abs(Turret.rotation(vex::rotationUnits::deg))>abs(((degree/gearratio)/2)))&&count>=5)
        {count-=1.5;}
      else{count+=1;}   
      Turret.spin(vex::directionType::fwd,(count*dir),vex::percentUnits::pct);
      wait(10);  
      //Brain.Screen.printAt(230, 20,"%f", abs(Turret.rotation(vex::rotationUnits::deg)));
      //Brain.Screen.printAt(230, 50,"%f", ((degree/gearratio)));
    }
    run(Turret,0);
  }
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
