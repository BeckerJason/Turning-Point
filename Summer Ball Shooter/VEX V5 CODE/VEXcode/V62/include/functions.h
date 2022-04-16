#include "defines.h"
using namespace G;
using namespace std;
using namespace vex;
//changed
int ENDAUTOTIMER()
  {  
  while (1)
	{wait(100); 
		MATCHTIMER += 100;}
	return 0;
  }
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
float GetGyro(){return GlobalGyro/10;}
void run(vex::motor motorname, double speed)
  {
	if (speed != 0) { motorname.spin(vex::directionType::fwd, speed, vex::velocityUnits::pct); }
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
      Brain.Screen.printAt(340, 100, "MID %d",MIDCount);
      Brain.Screen.printAt(340, 120, "HIGH %d",HIGHCount);
      Brain.Screen.printAt(340, 140, "MT %d ",MATCHTIMER);
      Brain.Screen.printAt(1, 140, "balls: %d",balls);
      if (rpmError < 5.0) { Brain.Screen.setPenColor(vex::color::green);}
      else { Brain.Screen.setPenColor(vex::color::white); }
      if (balls == one) {Controller.Screen.print("1");Partner.Screen.print("1");}
      else if (balls == two) {Controller.Screen.print("2");Partner.Screen.print("2");}
      else {Controller.Screen.print("0");Partner.Screen.print("0");}
      if(Shoot==2){Partner.rumble("-");}

 
		  
	    Brain.Screen.printAt(1, 120, "RPM error %1.2f", rpmError);
      wait(75); 
	  }
    return 0;
  } 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RPMCalc()
  {
	  while (1)
	  {    
      FlyL.setStopping(vex::brakeType::coast);
      FlyR.setStopping(vex::brakeType::coast);
      int TRPM = RPMGoal;
		  //if (fly == 2 || fly == 3)
		  if (fly == on)
      {
			  while (fly == on )//&& RPMGoal == TRPM)
			  {
          rpmError = abs(RPMGoal - (FlyL.velocity(vex::velocityUnits::rpm)));
          FlyR.spin(vex::directionType::fwd, RPMGoal, vex::velocityUnits::rpm);
          FlyL.spin(vex::directionType::fwd, RPMGoal, vex::velocityUnits::rpm);   
        }
		  }
		  else
		  {
        FlyL.stop(vex::brakeType::coast); FlyR.stop(vex::brakeType::coast);
			  //while ((fly == 4 || fly == 1) && RPMGoal == TRPM)
        while ((fly == off) && RPMGoal == TRPM) 
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
		  if (Shoot != zero) //when button is pressed
		  { 
        fly = on;
        if (Shoot==two) 
        {


         
          while(rpmError>40&&Shoot==two)  //while the error is greater than 15 wait
          {wait(5);MIDCount=0;
          }
          while(rpmError<75&&Shoot==two)// while the error<60 shoot ball
          { hood=off;
            //MIDCount=0;
            run(BallFeed,100);
            ballfeed=on;
            run(Roll,100);
            roll=on;
            wait(10);
            
          }          //when this while exits it has shot the first ball
          Shoot=one;          //set shoot mode to 1 ball
          
          HIGHCount=0;
          //ManualHood=149;
          
          //SnapToFlag=on;
          
          while(rpmError>55&&Shoot!=zero) //wait for error to be above 80
          {ManualHood=158;
            hood=manual;
            //HIGHCount=0;
             run(BallFeed,0);
              ballfeed=off;
              run(Roll,0);
              roll=off;
            wait(10);
            
          }
          wait(100);
         while(rpmError<75&&Shoot!=zero)
          {  //if (i==0) {wait(1000);}
          ManualHood=158;
            hood=manual;
            //HIGHCount=0;
            run(BallFeed,100);
            run(Roll,100);
            wait(10);
          }
          while(rpmError>55)
          {wait(10);}
          if (hood==manual){hood=off;}
          wait(500);
          roll=on;
          Shoot=zero; 
        }              
        else if (Shoot==one) 
        {
          while(rpmError>25&&Shoot==one)
          {
            if (BallTop.value(vex::percentUnits::pct)<BALLDETECTION)
            {
              run(BallFeed,0);
              ballfeed=off;
              run(Roll,0);
              roll=off;
            }
            else
            {
            run(BallFeed,80);
            ballfeed=on;
            run(Roll,100);
            roll=on;
            }
            wait(10);
            }
          while(rpmError<60&&Shoot==one)
          {
            run(BallFeed,100);
            run(Roll,100);
            wait(10);
          }
          Brain.resetTimer();
          while(Brain.timer(vex::timeUnits::msec)<600&&BallBottom.value(vex::percentUnits::pct)>BALLDETECTION)
          {
          run(BallFeed,-80);
            run(Roll,0);
          }
          
          
        Shoot=zero;
        roll=on;   
        }
      }       
      wait(100); 
    }
    return 0;
  }
  
int 
TurnToFlag()
{ int Counter=0;

  float HIGH=0;
  float MID=0; 
  Hood.setTimeout(5,vex::timeUnits::sec); 
  Hood.setMaxTorque(10, vex::percentUnits::pct);
  while(preautoL==true){wait(10);}
  Hood.resetRotation();
  //wait(1000);
	while (1)
	{ 
		
            while(SnapToFlag == on||SnapToFlag ==scan)
            {if (bY==1||bpY==1){SnapToFlag = off;}
										  
										  
            Vision.takeSnapshot(3,TOTALSNAPSHOTS);//take picture of green markers
      for (int i=0;i<TOTALSNAPSHOTS;i++)
      {
        GreenMarker.id[i]=Vision.objects[i].id;
        GreenMarker.originX[i]=Vision.objects[i].originX;
        GreenMarker.originY[i]=Vision.objects[i].originY;
        GreenMarker.centerX[i]=Vision.objects[i].centerX;
        GreenMarker.centerY[i]=Vision.objects[i].centerY;
        GreenMarker.width[i]=Vision.objects[i].width;
        GreenMarker.height[i]=Vision.objects[i].height;
        GreenMarker.angle[i]=Vision.objects[i].angle;
        GreenMarker.exists[i]=Vision.objects[i].exists;
      }

    //Brain.Screen.drawRectangle(GreenMarker.centerX[i] - (GreenMarker.width[i]/2),GreenMarker.centerY[i] - (GreenMarker.height[i]/2),GreenMarker.width[i],GreenMarker.height[i],vex::color::white); 
       
         if (Color==Blue){Vision.takeSnapshot(REDCOLOR, TOTALSNAPSHOTS);}
   else {Vision.takeSnapshot(BLUECOLOR, TOTALSNAPSHOTS);}
			//Brain.Screen.setPenColor(vex::color::red);
            int TXDist = 400; 
		GlobalFlagOffset=160;
        //GlobalFlagOffsetL=310-GlobalFlagOffset;
		for (int i = 0; Vision.objects[i].exists == 1;i++)//||VisionL.objects[i].exists == 1; i++)
		{	
			if (Vision.objects[i].exists == 1&&fabs(GlobalFlagOffset - Vision.objects[i].centerX) < fabs(TXDist)) 
      {
        for (int j = 0; GreenMarker.exists[j] == 1;j++)//||VisionL.objects[i].exists == 1; i++)
		    {	
          //if there is a green marker in close range to the flag
          if (Vision.objects[i].centerX<GreenMarker.centerX[j]+40&&Vision.objects[i].centerX>GreenMarker.centerX[j]-30&&Vision.objects[i].centerY<GreenMarker.centerY[j]+10&&Vision.objects[i].centerY>GreenMarker.centerY[j]-10)  
          {
            TXDist = GlobalFlagOffset - Vision.objects[i].centerX;
            j=TOTALSNAPSHOTS+1;
          }
          else{}
        }
        
      }
			else {}
		}        
		
    int TObject=9;
		int TWidth = 0;
		int THeight = 0;
		float TYDist=400.0;			
		for (int i = 0; Vision.objects[i].exists == 1; i++)
		{
			//if (Vision.objects[i].width > 8 && Vision.objects[i].height > 8) { Brain.Screen.printAt(230, 20 + i * 20, "X:%d,Y:%d W:%d H:%d D:%1.2f", Vision.objects[i].centerX, Vision.objects[i].centerY, Vision.objects[i].width, Vision.objects[i].height, 0.0157*pow(Vision.objects[i].height, 2) - 1.0842*Vision.objects[i].height + 19.93); }
			if ((Vision.objects[i].width > 8 && Vision.objects[i].height > 8) && (Vision.objects[i].centerX > (GlobalFlagOffset - 15 - TXDist) && Vision.objects[i].centerX < (GlobalFlagOffset + 15 - TXDist)) && Vision.objects[i].centerY < TYDist) 
      { for (int j = 0; GreenMarker.exists[j] == 1;j++)//||VisionL.objects[i].exists == 1; i++)
		    {	
          //if there is a green marker in close range to the flag
          if (Vision.objects[i].centerX<GreenMarker.centerX[j]+40&&Vision.objects[i].centerX>GreenMarker.centerX[j]-30&&Vision.objects[i].centerY<GreenMarker.centerY[j]+10&&Vision.objects[i].centerY>GreenMarker.centerY[j]-10)  
          {
            TYDist = Vision.objects[i].centerY; TWidth = GlobalFlagOffset - Vision.objects[i].centerX; THeight=Vision.objects[i].height;  TObject=i; 
            j=TOTALSNAPSHOTS+1;
          }
          else{}
        }
        
         
      }
																																								   
			else {}
		} 
		
             
		FinalObject=TObject;	
		TurnDiff = TWidth;
		if (TurnDiff > 0) { TurnDir = 1; }
		else { TurnDir = -1; }
			    if(SnapToFlag == on && fabs(TurnDiff) > 4)
			    {
            //Controller.Screen.clearLine(); 
//Controller.Screen.print("%f",TurnDiff);
					double speed;
                    speed=pow(fabs(TurnDiff),1.1)*TurnDir*.4;
					Turret.spin(vex::directionType::fwd, -speed, vex::velocityUnits::pct);     
                }
				else if (SnapToFlag==on){Turret.stop(vex::brakeType::brake);
        }
             
             
           
              
             
           // float AngleHeight=Vision.objects[FinalObject].height;     
            if (SnapToFlag==on&&THeight>8)
            {
              if (TYDist<(-7*THeight+320.0))//high
              {HIGH+=-0.2946*pow(THeight,2)+10.111*THeight+51.6; HIGHCount++;}
              else
              {MID+=-0.0259*pow(THeight,2)+1.1575*THeight+135.68;MIDCount++;}
              Counter++;  
            }
            if (HIGHCount==11||MIDCount==11)
            {
              if(HIGHCount>MIDCount)
              {FlagSum=HIGH/HIGHCount;}
              else
              {FlagSum=MID/MIDCount;}
              HIGH=0;MID=0;
              HIGHCount=0;  
              MIDCount=0;
            }
            if(hood==on&&(FlagSum)>100&&(FlagSum)<200&&HIGHCount==0&&MIDCount==0)//if the flagsum has been added 50 times
            {Hood.startRotateTo(FlagSum,vex::rotationUnits::deg,50,vex::velocityUnits::pct);}
            else if (hood==off){Hood.startRotateTo(142,vex::rotationUnits::deg,50,vex::velocityUnits::pct);}
            //else if (hood==twoshot){Hood.startRotateTo(160,vex::rotationUnits::deg,50,vex::velocityUnits::pct);}  
            else if (hood==manual){Hood.startRotateTo(ManualHood,vex::rotationUnits::deg,50,vex::velocityUnits::pct);}
            FlagSum=0;
              wait(25);
            }
            if (hood==off||hood==on){Hood.startRotateTo(142,vex::rotationUnits::deg,50,vex::velocityUnits::pct);}
            //else if (hood==twoshot){Hood.startRotateTo(180+PLATFORM/2,vex::rotationUnits::deg,50,vex::velocityUnits::pct);}
            //else if (hood==reverse){Hood.startRotateTo(155,vex::rotationUnits::deg,50,vex::velocityUnits::pct);}
            else if (hood==manual){Hood.startRotateTo(ManualHood,vex::rotationUnits::deg,25,vex::velocityUnits::pct);}
    wait(100);
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
void StopDrive(vex::brakeType brake)
  {
	BRAKE(RF, brake);
	BRAKE(RM, brake);
	BRAKE(RB, brake);
	BRAKE(LF, brake);
	BRAKE(LM, brake); 
	BRAKE(LB, brake);
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
{
  //BallFeed.setTimeout(3,vex::timeUnits::sec);
 BallFeed.setMaxTorque(100,vex::percentUnits::pct);
 int count=0;
  
    while(1) 
    { 
      //////Front Roller
      if (Shoot==0)
      {
        if (bL1||roll==reverse){run(Roll,-92);}
        //else if (balls==2){run(Roll,0);} //2 Balls OFF
        else if (IR.value()==0&&BallBottom.value(vex::percentUnits::pct)<BALLDETECTION&&BallTop.value(vex::percentUnits::pct)<BALLDETECTION){run(Roll,0);}//1 1 1 
        else if (BallBottom.value(vex::percentUnits::pct)<BALLDETECTION&&BallTop.value(vex::percentUnits::pct)<BALLDETECTION){run(Roll,0);}//1 1 X
        else if (BallBottom.value(vex::percentUnits::pct)<BALLDETECTION&&BallTop.value(vex::percentUnits::pct)>BALLDETECTION&&IR.value()==0){run(Roll,30);}//0 1 1
        else if (BallBottom.value(vex::percentUnits::pct)>BALLDETECTION&&BallTop.value(vex::percentUnits::pct)<BALLDETECTION&&IR.value()==0){run(Roll,0);}//1 0 1
        else if (IR.value()==0){run(Roll,30);} //X X 1
        else if (roll==on){run(Roll,80);}
        else {run(Roll,0);} //X X X

        //Ball LOader
        if (bY==1||bpY==1){run(BallFeed,-20);} 
        else if (BallBottom.value(vex::percentUnits::pct)<BALLDETECTION&&BallTop.value(vex::percentUnits::pct)<67){run(BallFeed,0);}//1 1 X
        else if (BallBottom.value(vex::percentUnits::pct)<BALLDETECTION&&IR.value()==0){run(BallFeed,80);}//0 1 1
        else if (BallTop.value(vex::percentUnits::pct)<BALLDETECTION&&IR.value()==0){run(BallFeed,0);}//1 0 1
        else if (BallTop.value(vex::percentUnits::pct)<BALLDETECTION){run(BallFeed,-80);}//1 0 0    
        else if (BallBottom.value(vex::percentUnits::pct)>BALLDETECTION&&IR.value()==0){run(BallFeed,100);}//0 0 1
        else if (BallBottom.value(vex::percentUnits::pct)<BALLDETECTION){run(BallFeed,0);}//0 1 0
        else {run(BallFeed,0);}
      }
      int tempball=0;
      if (IR.value()==0) {tempball++;}
      if (BallBottom.value(vex::percentUnits::pct)<=69) {tempball++;}
      if(tempball<2){
      if (BallTop.value(vex::percentUnits::pct)<=69) {tempball++;}
      }
      balls=tempball; 
     


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
                BRAKE(RF, brake);
	BRAKE(RM, brake);
	BRAKE(RB, brake);}
            if( abs(enc(LF))<fabs(rotation)){leftDrive(-turningspeed*dir);}
            else if( abs(enc(LF))>fabs(rotation)+1){leftDrive(turningspeed*dir/3);}
            else{BRAKE(LF, brake);
	BRAKE(LM, brake);
	BRAKE(LB, brake);}
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
                BRAKE(RF, brake);
	BRAKE(RM, brake);
	BRAKE(RB, brake);}
            if( abs(enc(LF))>abs(rotation)){leftDrive(-turningspeed*dir/3);}
            else{BRAKE(LF, brake);
	BRAKE(LM, brake); 
	BRAKE(LB, brake);}
            wait(5);
     }
    BRAKE(RF, hold);
	BRAKE(RM, hold);
	BRAKE(RB, hold);
    BRAKE(LF, hold);
	BRAKE(LM, hold);
	BRAKE(LB, hold);

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
int PID_INTEGRAL_LIMIT = 40;
 
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////

void pidTurn(float globalDegrees, float pid_Kp, float pid_Ki, float pid_Kd, int timeout)
{	    LF.resetRotation();
	RF.resetRotation();
  int LASTDIR=1;
  float RO=1;
  int direction = 0;
	GlobalGyro = 0;
	Brain.resetTimer();
	float  pidError = 0;
	float  pidLastError = 0;
	float  pidIntegral = 0;
	float  pidDerivative = 0;
	float pidDriveR = 0;

	T3 = 0;
	while (T3 < timeout)
	{ if (fabs(enc(RF))-5>fabs(enc(LF))){RO=.8;}
    else if(fabs(enc(LF))-5>fabs(enc(RF))){RO=1.2;}
    else {RO=1;}
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
		rightDrive(direction * pidDriveR * PID_MOTOR_SCALE*RO);
		leftDrive(-direction * pidDriveR * PID_MOTOR_SCALE);
		if ((fabs(pidError) < 10) && (fabs(avgSpeed) < 10)) {
			StopDrive(brake);
			break;
		}
		if (Brain.timer(vex::timeUnits::msec) < 40) { avgError += pidError; }
		else { avgSpeed = avgError / 3; avgError = 0; Brain.resetTimer(); }
    LASTDIR=direction;
		//REFRESH RATE 60Hz 
    //while(fmod(Brain.timer(vex::timeUnits::msec),16)>2){wait(1);}
		wait(16);
	}
  StopDrive(brake);
  wait(300);
leftDrive(LASTDIR*2);
rightDrive(-LASTDIR*2);
wait(300);

	StopDrive(brake);
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
int Move(float speed, float dist,bool rampspeed,vex::brakeType X) {

	float dir;
	if (dist < 0) { dir = -1; }
	else { dir = 1; }
	float Tdir = dir;
    LM.resetRotation();
	RM.resetRotation();
	wait(20);
  T3=0;
	double counter=100;
if(rampspeed){counter=50;}
	while (fabs(enc(LM)) < abs((dist * 360.0 / (4.0*3.14159)))&&T3<4000) {


		float Roffset = 1.0;
		if (fabs(enc(LM)) < fabs((enc(RM)) + 2)) { Roffset = 0.9; }
		else if (fabs(enc(LM)) > fabs(enc(RM)) - 2) { Roffset = 1.1; }
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
  StopDrive(X);
  return 1;
}

////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
void ToWall(double vel)
{T3=0;
float TLF=0, TRF=0;
SetDriveTorque(30);
LF.resetRotation();
RF.resetRotation();
rightDrive(vel);
leftDrive(vel);
wait(300);
do{
TLF=enc(LM);
TRF=enc(RM); 
rightDrive(vel);
leftDrive(vel);
wait(100);
}while ((TLF!=enc(LM)||TRF!=enc(RM))&&(RLine.value(vex::percentUnits::pct)<65||LLine.value(vex::percentUnits::pct)<65)&&T3<2500);
StopDrive(coast);
SetDriveTorque(100);
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
      if ((abs(Turret.rotation(vex::rotationUnits::deg))>abs(((degree/gearratio)/2)))&&count>=5)
        {count-=1.5;}
      else{count+=1;}   
      Turret.spin(vex::directionType::fwd,(count*dir),vex::percentUnits::pct);
      wait(10);  
    }
    run(Turret,0);
  }

 


  void TurnTurretTo(double speed,double degree)
  {   
    double gearratio=12.0/175.0;
    
    Turret.startRotateTo(-degree/gearratio,vex::rotationUnits::deg,speed,vex::velocityUnits::pct);

  }
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////





 //AUT MACROS
 void GrabTwoBalls()
{
 Intake.set(true);
wait(750);
Move(20,10,1,brake);
roll=on;
Move(20,-5,1,coast); //speed,dir,ramp,stop
Intake.set(false);
Move(20,-5,0,brake);
}
void SetDriveTorque(double Torque)
{
LF.setMaxTorque(Torque, percentUnits::pct);
LB.setMaxTorque(Torque, percentUnits::pct);
LM.setMaxTorque(Torque, percentUnits::pct);
RF.setMaxTorque(Torque, percentUnits::pct);
RM.setMaxTorque(Torque, percentUnits::pct);
RB.setMaxTorque(Torque, percentUnits::pct);
}     
      

int ScanFlags(int timeout,_Toggle HON,_Shoot SON)
{
  int FlagCounter=0;  
  int dir=1;
  hood=HON;          //turn hood on
  SnapToFlag=on;     //begin snap to flag
  wait(100);        //wait to allow time for first flag sensing
  Brain.resetTimer();
  for(int i=0;Brain.timer(vex::timeUnits::msec)<timeout&&balls!=0;i++)  //While timer less than timeout and has ball
  {
    if (i==20||(i-20)%40==0){dir*=-1;} //if the current loop count is a multiple of 10 flip turret direction
    if (FlagCounter>10)
    {SnapToFlag=on;
      Shoot=SON; 
      while(Shoot!=zero&&Brain.timer(vex::timeUnits::msec)<timeout){wait(10);}
      Shoot=zero;
      break;
    }
    if(FinalObject<TOTALSNAPSHOTS+1){SnapToFlag=on;FlagCounter++;wait(10);i--;}  //SnapToFlag will calculate FinalObject, which is initially TOTALSNAPSHOTS+1. if<TOTALSNAPSHOTS than a flag was seen
    else
    {Shoot=zero;
      SnapToFlag=scan;
      run(Turret,20*dir); 
      wait(27);
      if (FlagCounter>0){FlagCounter--;}
    }
    
  }
  Shoot=zero;
  SnapToFlag=off;
  hood=off;
  return 0;
}


void Tile(double fact,int timeout,bool intile,vex::brakeType X)
{
  T3=0;
if (intile==1)
{
while(T3<timeout&&(RLine.value(vex::percentUnits::pct)<TILE||RLine.value(vex::percentUnits::pct)<TILE))
{
  if (RLine.value(vex::percentUnits::pct)-TILE<0&&LLine.value(vex::percentUnits::pct)-TILE<0)
  {
    rightDrive(-fact*(RLine.value(vex::percentUnits::pct)-TILE));
    leftDrive(-fact*(RLine.value(vex::percentUnits::pct)-TILE));
  }
  else
  {
  rightDrive(-1*fact*(RLine.value(vex::percentUnits::pct)-TILE));
  leftDrive(-1*fact*(LLine.value(vex::percentUnits::pct)-TILE));
  }
  wait(10);
}
}
else{
while(T3<timeout&&(RLine.value(vex::percentUnits::pct)>TILE||RLine.value(vex::percentUnits::pct)>TILE))
{
  if (RLine.value(vex::percentUnits::pct)-TILE>0&&LLine.value(vex::percentUnits::pct)-TILE>0)
  {
    rightDrive(fact*(RLine.value(vex::percentUnits::pct)-TILE));
    leftDrive(fact*(RLine.value(vex::percentUnits::pct)-TILE));
  }
  else {
  rightDrive(fact*(RLine.value(vex::percentUnits::pct)-TILE));
  leftDrive(fact*(LLine.value(vex::percentUnits::pct)-TILE));
  }
  wait(10);
}
}
StopDrive(X);
}

void SwapColor()
{
if(Color==Red){Color=Blue;}
else {Color=Red;}
}