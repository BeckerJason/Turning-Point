
         
#ifndef NERD_GYRO
#define NERD_GYRO

	float stdDev;
	float avg;
	float voltsPerDPS;
	int gyroFlipped;

//ignore data within n standard deviations of no motion average
#define GYRO_STD_DEVS 3

#define GYRO_OVERSAMPLE 1

//points or time in mSec that the gyro calibrates for
#define GYRO_CALIBRATION_POINTS 2000

float calibrationBuffer [GYRO_CALIBRATION_POINTS];

float gyroGetRate ();

/**
 * generate calibration data for the gyro by collecting
 * zero movement data for reference when reading data later
 *
 * @param gyro instance of gyro structure
 */
void gyroCalibrate (){
	float rawAverage = 0.0;
	float stdDev = 0.0;

	//calculate average gyro reading with no motion
    
    Gyro.startCalibration();
    //vex::task::sleep(2000);
	for(int i = 0; i < GYRO_CALIBRATION_POINTS; ++i){
		float raw = Gyro.value(vex::rotationUnits::raw);
		rawAverage += raw;
		calibrationBuffer [i] = raw;
		vex::task::sleep(1);
	}
	rawAverage /= GYRO_CALIBRATION_POINTS;
	avg = rawAverage;

	//calcuate the standard devation, or the average distance
	//from the average on the data read
	for (int i = 0; i < GYRO_CALIBRATION_POINTS; ++i)
		stdDev += fabs (rawAverage - calibrationBuffer [i]);
	stdDev /= (float) GYRO_CALIBRATION_POINTS;

	stdDev = stdDev;

	/*
	 * Datasheet from VEX indicates that the sensitivity of the gyro is 1.1mV/dps
	 * and the cortex ADC for raw analog reads ranges from 0-4095 for 0v-5v
	 * readings. The gyro is scaled from the nominal 2.7v-3.6v operating range
	 * that the actual chip has to work on the cortex's 5v logic voltage. The scale multiplier
	 * value is in the ballpark of 1.515.
	 */
	voltsPerDPS = 0.0011 * 1.515;
}

/**
 * initialize gyro and run the calibration subroutine
 *
 * @param gyro instance of gyro structure
 * @param portNum the port number of the gyro
 */
void gyroInit (int gyroFlipped) {
	//gyro.portNum = portNum;
	gyroFlipped = gyroFlipped;
	gyroCalibrate ();
}

/**
 * calculate filtered gyro rate data, ignoring anything within
 * GYRO_STD_DEVS standard deviations of the average gyro
 * rate value at zero motion
 *`
 * @param gyro instance of gyro structure
 *
 * @return gyro rate, in degrees per second
 */
float gyroGetRate (){
	float gyroRead = 0.0;

	#if defined (GYRO_OVERSAMPLE)
		if (GYRO_OVERSAMPLE > 0) {
			int sampleSum = 0;
			int nSamples = pow (4, GYRO_OVERSAMPLE);

			for (int i = 0; i < nSamples; ++i)
				sampleSum += Gyro.value(vex::rotationUnits::raw);
			gyroRead = (float) sampleSum / (float) nSamples;
		}
		else
			gyroRead = Gyro.value(vex::rotationUnits::raw);
	#else
		gyroRead = Gyro.value(vex::rotationUnits::raw);
	#endif

	//Difference from zero-rate value or the average calibration read
	float gyroDiff = gyroRead -avg;

	//Difference fro zero-rate value, in volts
	float gyroVoltage = gyroDiff * 5.0 / 4095.0;

	if (fabs (gyroDiff) > GYRO_STD_DEVS *stdDev)
    {
		if (gyroFlipped){return -1 * 1.28*gyroVoltage / voltsPerDPS;}
		else{return 1.28*gyroVoltage / voltsPerDPS;}
    }
	return 0;
}
#endif
void brake(vex::motor,char);
int GyroTrack()
{
	float GyroAdd = 0;
	float GyroTempCheck = 0;

	while (1)
	{
		GyroAdd = gyroGetRate() - GyroTempCheck;
		GyroTempCheck = gyroGetRate();
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

#ifndef DEBUG //if DEBUG is defined earlier this section will not compile
void AllianceSelect()
{   //screen 480x272

	Brain.Screen.clearScreen(vex::color::black);//show red blue and confirm
	int selection = 0;
	while (selection < 4)
	{
		Brain.Screen.setPenWidth(1);
		Brain.Screen.setPenColor(vex::color::black);
		if (bRight == 1 || (Brain.Screen.xPosition() > 300 && Brain.Screen.xPosition() < 420 && Brain.Screen.yPosition() > 20 && Brain.Screen.yPosition() < 60)) { selection = 1; Controller.Screen.print("Blue"); }//if Touch within blue box:: selection=1
		else if (bLeft == 1 || (Brain.Screen.xPosition() > 60 && Brain.Screen.xPosition() < 180 && Brain.Screen.yPosition() > 20 && Brain.Screen.yPosition() < 60)) { selection = 2;  Controller.Screen.clearLine(1); Controller.Screen.print("Red"); } //else if Touch within red box:: selection=2
		else if (selection == 3 && Brain.Screen.pressing() == 0) { selection = 4; } //else if Touch within select box&& Selection >0 :: selection=3
		else if ((bA && selection > 0) || (Brain.Screen.xPosition() > 180 && Brain.Screen.xPosition() < 300 && Brain.Screen.yPosition() > 100 && Brain.Screen.yPosition() < 140 && selection > 0)) { selection = 3; } //else if Touch within select box&& Selection >0 :: selection=3


		if (selection == 1) { TrackColor = 'B'; Brain.Screen.drawRectangle(297, 17, 126, 46, vex::color::green); Brain.Screen.drawRectangle(57, 17, 126, 46, vex::color::black); }  //if selection==1 draw green box around Blue and Black Box around red
		else if (selection == 2) { TrackColor = 'R'; Brain.Screen.drawRectangle(297, 17, 126, 46, vex::color::black); Brain.Screen.drawRectangle(57, 17, 126, 46, vex::color::green); }//else if selection==2 draw green box around red and Black Box around blue
		else if (selection == 3) { Brain.Screen.drawRectangle(177, 97, 126, 46, vex::color::green); }//else if selection==3 draw green box around select


		Brain.Screen.drawRectangle(60, 20, 120, 40, vex::color::red);
		Brain.Screen.drawRectangle(300, 20, 120, 40, vex::color::blue);
		Brain.Screen.drawRectangle(180, 100, 120, 40, vex::color::white);
		Brain.Screen.setPenWidth(10);
		Brain.Screen.setPenColor(vex::color::white);
		Brain.Screen.printAt(105, 45, false, "RED");
		Brain.Screen.printAt(340, 45, false, "BLUE");
		Brain.Screen.setPenColor(vex::color::black);
		Brain.Screen.printAt(210, 125, false, "SELECT");
		wait(100);
		Alliance = TrackColor;
	}
    if (TrackColor=='B'){
        Color=1;
    }
    else {
      Color=2; 
    }
}
#endif
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
		//Brain.Screen.printAt(80, 80, "%d",BallLoaded.value(vex::percentUnits::pct) );
        Brain.Screen.printAt(100, 80, "%d",BallBottom.value(vex::percentUnits::pct) );
        Brain.Screen.printAt(300, 100, "%d",RLine.value(vex::percentUnits::pct) );
        Brain.Screen.printAt(300, 130, "%d",LLine.value(vex::percentUnits::pct) );
        Brain.Screen.printAt(100, 20, "P: H:%d    Y:%d",VisionL.objects[FinalObject].height,VisionL.objects[FinalObject].centerY);
        Brain.Screen.printAt(100, 40, "P: H:%d    Y:%d",Vision.objects[FinalObject].height,Vision.objects[FinalObject].centerY);
        Brain.Screen.printAt(340, 100, "OH: %1.8f",objheight);
        Brain.Screen.printAt(340, 120, "I: %1.8f",GLOBALI);
        Brain.Screen.printAt(340, 140, "D: %1.8f",GLOBALD);
        Brain.Screen.printAt(1, 140, "VisionLR: %c",VisionLR);
//Brain.Screen.printAt(180, 80, "%d",CapIR.value() );
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
	{    FlyL.setStopping(vex::brakeType::coast);
         FlyR.setStopping(vex::brakeType::coast);
        int TempRPM = RPMGoal;
		if (fly == 2 || fly == 3)
		{//TempRPM = RPMGoal;
         //FlyR.spin(vex::directionType::fwd, RPMGoal, vex::velocityUnits::rpm);
         //FlyL.spin(vex::directionType::fwd, RPMGoal, vex::velocityUnits::rpm);
			while ((fly == 2 || fly == 3) )//&& RPMGoal == TempRPM)
			{rpmError = fabs(RPMGoal - (FlyL.velocity(vex::velocityUnits::rpm)));
             
          FlyR.spin(vex::directionType::fwd, RPMGoal, vex::velocityUnits::rpm);
         FlyL.spin(vex::directionType::fwd, RPMGoal, vex::velocityUnits::rpm);   
                
            }
 
		}
		else
		{FlyL.stop(vex::brakeType::coast); FlyR.stop(vex::brakeType::coast);
			while ((fly == 4 || fly == 1) && RPMGoal == TempRPM) { wait(100); }
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
		{	fly = 2;
         if (Shoot==2){while(Shoot!=0&&(BallBottom.value(vex::percentUnits::pct)>50&&BallLoaded.pressing()==0)){Shoot=-1;wait(10);}
                      Shoot=2;
                      while(rpmError>15&&Shoot==2){wait(10);}
                      while(rpmError<60&&Shoot==2)
                      {
                        run(Roller2,-100);
                        run(BallFeed,100);
                        run(Roll,100);
                          wait(10);
                      }
                      Shoot=-1;
                      while(rpmError>80&&Shoot==-1){wait(10);}
                      if (Shoot==-1){Shoot=2;} 
                      while(rpmError<90&&Shoot==2)
                      {
                        run(Roller2,-100);
                        run(BallFeed,100);
                        run(Roll,100);
                          wait(10);
                      }
                       Shoot=0;
                    }
                      
         else if (Shoot==1) 
         {
           while(rpmError>15&&Shoot==1){wait(10);}
                      while(rpmError<60&&Shoot==1)
                      {
                        run(Roller2,-100);
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
			  VisionL.takeSnapshot(Color, 7);
			//Brain.Screen.setPenColor(vex::color::red);
            TempXDist = 400;
							
		GlobalFlagOffset=160;
        //GlobalFlagOffsetL=310-GlobalFlagOffset;
		for (int i = 0; Vision.objects[i].exists == 1;i++)//||VisionL.objects[i].exists == 1; i++)
		{	
			if (Vision.objects[i].exists == 1&&fabs(GlobalFlagOffset - Vision.objects[i].centerX) < fabs(TempXDist)) { TempXDist = GlobalFlagOffset - Vision.objects[i].centerX;VisionLR='R'; }
			else {}
            
           /* if (VisionL.objects[i].exists == 1&&fabs(GlobalFlagOffsetL - VisionL.objects[i].centerX) < fabs(TempXDist)) { TempXDist = GlobalFlagOffsetL - VisionL.objects[i].centerX; VisionLR='L'; }
			else {}*/
		}
            
		

		TempWidth = 0;
		TempHeight = 0;
		TempYDist=400.0;			
		for (int i = 0; Vision.objects[i].exists == 1; i++)
		{
			//if (Vision.objects[i].width > 8 && Vision.objects[i].height > 8) { Brain.Screen.printAt(230, 20 + i * 20, "X:%d,Y:%d W:%d H:%d D:%1.2f", Vision.objects[i].centerX, Vision.objects[i].centerY, Vision.objects[i].width, Vision.objects[i].height, 0.0157*pow(Vision.objects[i].height, 2) - 1.0842*Vision.objects[i].height + 19.93); }
			if ((Vision.objects[i].width > 8 && Vision.objects[i].height > 8) && (Vision.objects[i].centerX > (GlobalFlagOffset - 10 - TempXDist) && Vision.objects[i].centerX < (GlobalFlagOffset + 10 - TempXDist)) && Vision.objects[i].centerY < TempYDist) { TempYDist = Vision.objects[i].centerY; TempWidth = GlobalFlagOffset - Vision.objects[i].centerX; TempHeight=Vision.objects[i].height; TempObject=i; }
																																								   
			else {}
			}
		
             
		 FinalObject=TempObject;	
		TurnDiff = TempWidth;
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
            if (SnapToFlag==1&&TempHeight>8)
             {if (TempYDist<(-6.3123*TempHeight+300.0))//high
             {FlagSum+=-0.2167*pow(TempHeight,2)+7.7833*TempHeight-48.9;}
              else{FlagSum+=-0.0318*pow(TempHeight,2)+1.5924*TempHeight+14.971;}
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
    while(1)
    { 
        if(Shoot<=0&&bY==1){run(Roller2, 90);}
        else if(Shoot<=0&&BallBottom.value(vex::percentUnits::pct)<68&&BallLoaded.pressing()==1){run(Roller2,0);}//if 2 balls seen kill roller
        else if (Shoot<=0){run(Roller2,-90);}//else roll in
        
        if(Shoot!=1&&bL1==1){ run(Roll, -100); R = 5;}//if button pressed {roll out R=5}
        else if (Shoot<=0&&IR.value()==0&&(BallBottom.value(vex::percentUnits::pct)<50||BallLoaded.pressing()==1)){R=4;run(Roll, 0);}
        else if (Shoot<=0&&IR.value()==0&&(BallBottom.value(vex::percentUnits::pct)>50&&BallLoaded.pressing()==0)){R=2;}
        else if (Shoot<=0&&R==5){R=2;}
        else{}
        if(Shoot<=0&&bY==1){run(BallFeed, -70);}
        else if(Shoot<=0&&BallLoaded.pressing()==1){run(BallFeed,0);}
        else if(Shoot<=0&&BallBottom.value(vex::percentUnits::pct)>50&&BallLoaded.pressing()==0){run(BallFeed,100);}
        else if (Shoot<=0){run(BallFeed,0);}
       /* if (Shoot==0&&bY==1){run(Roller2, 90);}
       else if(Shoot==0&&(BallLoaded.pressing()==0&&abs(BallFeed.rotation(vex::rotationUnits::deg))<60)){run(Roller2, -90);}//if no ball seen on top(limit or encoder) {run Roller in}
        else if(Shoot==0&&abs(BallFeed.rotation(vex::rotationUnits::deg))<70){run(Roller2, -90);BallFeed.startRotateTo(85,vex::rotationUnits::deg,20,vex::velocityUnits::pct);}//encoder less than a value {start running up to value run roller in}
       else if(Shoot==0&&BallFeed.isSpinning()){run(Roller2, 0);}
 else if(Shoot==0&&IR.value()==1){run(Roller2, 20);}//else if ir doesnt see ball run out
       else if(Shoot==0){run(Roller2, 0);}// else if stop
        else{}
        //if (Shoot==0&&(R==3 || R==4)&&bL1==0){}
         if(bL1==1){ run(Roll, -100); R = 5;}//if button pressed {roll out R=5}
        else if(Shoot==0&&IR.value()==0&&(BallLoaded.pressing()==1||abs(BallFeed.rotation(vex::rotationUnits::deg))>10)){R=4;run(Roll, 0);}//if ball on top and bottom {stop R=4}
        else if(Shoot==0&&IR.value()==0&&(BallLoaded.pressing()==0&&abs(BallFeed.rotation(vex::rotationUnits::deg))<10)){R=2;}
        else if (Shoot==0&&R==5){R=2;}
        else{}*/
 if (R==4){run(Roll,0);}
 if (R==2){run(Roll,80);}
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
        while (abs(enc(RF))<fabs(rotation)||abs(enc(LF))<fabs(rotation))
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
     while (abs(enc(RF))>fabs(rotation)||abs(enc(LF))>fabs(rotation))
     {
     if ((abs(enc(RF)))>fabs(rotation)){rightDrive(turningspeed*dir/3);}
            else{	
                brake(RF, 'b');
	brake(RM, 'b');
	brake(RB, 'b');}
            if( abs(enc(LF))>fabs(rotation)){leftDrive(-turningspeed*dir/3);}
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
	float tempdir = dir;
	leftDrive(dir * 5);
	rightDrive(dir * 5);
	wait(200);
	StopDrive();
	wait(100);
    LF.resetRotation();
	RF.resetRotation();
	wait(20);
	double counter = 0;
	while (fabs(enc(LF)) < fabs((dist * 360.0 / (4.0*3.14159)))) {


		float Roffset = 1.0;
		if (fabs(enc(LF)) < fabs((enc(RF)) + 5)) { Roffset = 0.9; }
		else if (fabs(enc(LF)) > fabs(enc(RF)) - 5) { Roffset = 1.1; }
		else {}
		if (counter < 100) { dir = tempdir * counter*0.01; counter+=.75; }
		else { dir = tempdir; }
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
	float tempdir = dir;
    if (MoveReturn==0){	LF.resetRotation();
	RF.resetRotation();MoveReturn=1;}
	wait(20);
	int counter = 0;
	if (fabs(enc(LF)) < fabs((dist * 360 / (4.0*3.14159)))){status=1;}
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
	float tempdir = dir;
	leftDrive(dir * 5);
	rightDrive(dir * 5);
	wait(200);
	StopDrive();
	wait(100);
	LF.resetRotation();
	RF.resetRotation();
	wait(20);
	int counter = 0;
	while (fabs(enc(LF)) < fabs((dist * 360 / (4.0*3.14159)))) {


		float Roffset = 1.0;
		if (fabs(enc(LF)) < fabs((enc(RF)) + 5)) { Roffset = 0.9; }
		else if (fabs(enc(LF)) > fabs(enc(RF)) - 5) { Roffset = 1.1; }
		else {}
		if (counter < 100) { dir = tempdir * counter*0.01; counter++;}
		else { dir = tempdir; }
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
float TempLF=0, TempRF=0;
do{
TempLF=enc(LF);
TempRF=enc(RF);
rightDrive(vel);
leftDrive(vel);
wait(100);
}while ((TempLF!=enc(LF)||TempRF!=enc(RF))&&(RLine.value(vex::percentUnits::pct)<68||LLine.value(vex::percentUnits::pct)<68)&&T3<1500);
StopDrive();
}
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
void TurnTurret(double degree)
{   Turret.resetRotation();
 int dir;
 if (degree>0){dir=-1;}
 else{dir=1;}
 //degree>0 means left
  double count=5;
 double gearratio=12.0/175.0;
 while(fabs(Turret.rotation(vex::rotationUnits::deg))<fabs((degree/gearratio)))
 {  //if(LeftTurretLimit.pressing()==1){break;}
   // else if(RightTurretLimit.pressing()==1){break;}
     if ((fabs(Turret.rotation(vex::rotationUnits::deg))>fabs(((degree/gearratio)/2)))&&count>=5){count-=1.5;}
    else{count+=1;}   
    Turret.spin(vex::directionType::fwd,(count*dir),vex::percentUnits::pct);
    wait(10);  
  Brain.Screen.printAt(230, 20,"%f", fabs(Turret.rotation(vex::rotationUnits::deg)));
    Brain.Screen.printAt(230, 50,"%f", ((degree/gearratio)));
 }
 run(Turret,0);
    TurretRunning=0;   
}
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
