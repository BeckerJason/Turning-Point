#include "defines.h"
using namespace G;
using namespace std;
using namespace vex;
    
   
    #ifdef DEBUG //if DEBUG is not defined earlier this section will not compile
    /*while(DEBUG){
        if (bUp == 1) { GLOBALP += .01; wait(100); } 
		if (bDown == 1) { GLOBALP -= .01; wait(100); }
        if (bX== 1) { GLOBALI += .0000001; wait(100); }
		if (bB == 1) {GLOBALI -= .0000001; wait(100); }
        if (bR1== 1) { GLOBALD += .05; wait(100); }
		if (bR2 == 1) {GLOBALD -= .05; wait(100); }
                wait(10);
    }  */  
    #endif
    AutoRunning=0;
	  SnapToFlag = off;
    GlobalFlagOffset=160;
    Shoot=zero;
    RPMGoal=600;
    PLATFORM=no;
    Lift.set(false);
    Hood.setMaxTorque(20,vex::percentUnits::pct);
    hood=off;
    Turret.setStopping(vex::brakeType::brake);
    MATCHTIMER=0;
	while (1)
	{ 
      /*if (bLeft==1)
      {
        climb=on;
        leftDrive(-100);
        rightDrive(-100);
        wait(250);
        leftDrive(90);
        rightDrive(90);
        wait(750);
        Lift.set(true);
        wait(1000);
        //Lift.set(false);
        //wait(500);        
        StopDrive(brake);
        climb=off;
      }*/


		//else if ((fabs(ch3) > 2 || fabs(ch4) > 2) && SnapToFlag == 1) { SnapToFlag = 0; }
		if ( AutoRunning == 0 && (abs(ch3) > 2 || abs(ch4) > 2))
        {   if(abs(LF.velocity(vex::velocityUnits::pct))>(ch3 + ch4/1.5))
        {
            run(LF, ((ch3 + ch4)+LF.velocity(vex::velocityUnits::pct)+LF.velocity(vex::velocityUnits::pct))/3); //(Axis3+Axis4)/2
			run(LM, ((ch3 + ch4/1.5)+LM.velocity(vex::velocityUnits::pct)+LM.velocity(vex::velocityUnits::pct))/3); //(Axis3+Axis4)/2
			run(LB, ((ch3 + ch4/1.5)+LB.velocity(vex::velocityUnits::pct)+LB.velocity(vex::velocityUnits::pct))/3); //(Axis3+Axis4)/2
			run(RF, ((ch3 - ch4/1.5)+RF.velocity(vex::velocityUnits::pct)+RF.velocity(vex::velocityUnits::pct))/3);//(Axis3-Axis4)/2
			run(RM, ((ch3 - ch4/1.5)+RM.velocity(vex::velocityUnits::pct)+RM.velocity(vex::velocityUnits::pct))/3);//(Axis3-Axis4)/2
			run(RB, ((ch3 - ch4/1.5)+RB.velocity(vex::velocityUnits::pct)+RB.velocity(vex::velocityUnits::pct))/3);//(Axis3-Axis4)/2
          
            } 
         else{
			run(LF, (ch3 + ch4/1.5)); //(Axis3+Axis4)/2
			run(LM, (ch3 + ch4/1.5)); //(Axis3+Axis4)/2
			run(LB, (ch3 + ch4/1.5)); //(Axis3+Axis4)/2
			run(RF, (ch3 - ch4/1.5));//(Axis3-Axis4)/2
			run(RM, (ch3 - ch4/1.5));//(Axis3-Axis4)/2
			run(RB, (ch3 - ch4/1.5));//(Axis3-Axis4)/2
         }
		}
		else if (AutoRunning == 0)
		{
			StopDrive(brake);
		}
		else {}
    Intake.set(bLeft);

    if (fly ==on){ if (bR1 && !G::flyprev) fly = off;}
    else if (fly == off) {if (bR1 && !G::flyprev) fly = on;}
    G::flyprev = bR1;

    if (roll ==on){ if (bR2 && !G::rollprev) roll = off;}
    else if (roll == off) {if (bR2 && !G::rollprev) roll = on;}
    G::rollprev = bR2;

    if ( lift==on){ if (bB && !G::liftprev) lift = off;Lift.set(false);}
    else if (lift == off) {if (bB && !G::liftprev) lift = on;Lift.set(true);}
    G::liftprev = bB;

    //if (PLATFORM==yes){ if (bX && !G::platformprev) PLATFORM = no;}
    //else if (PLATFORM == yes) {if (bX && !G::platformprev) PLATFORM = yes;}
    //xxG::platformprev = bX;
  
    if (hood==on||hood==off)
    {
    if (bUp==1||bpUp==1){hood=on;}
    else if (bDown==1||bpDown==1){hood=off;}
		if (bA == 1&&Shoot==zero) { Shoot = one; } //Shoot ball
    else if (bRight == 1&&Shoot==zero) { Shoot = two; }
		else if (bY == 1||bpY==1) { Shoot = zero; } //Stop Mid shot
		else {}
    }
		//if (bUp == 1 && RPMGoal < 200) { RPMGoal += 2; wait(200); }
		//if (bDown == 1 && RPMGoal > 50) { RPMGoal -= 2; wait(200); }
		//else {}
        if (abs(ch1)>5){run(Turret,ch1);SnapToFlag=off;}
        else if (abs(chp1)>5){run(Turret,chp1);SnapToFlag=off;}
        else if (bL2==1||bpL2==1){SnapToFlag=on;}
        else if (SnapToFlag==off){run(Turret,0);}

     // if (bX==1){ScanFlags(4000,);}
        wait(20);
        
	} 