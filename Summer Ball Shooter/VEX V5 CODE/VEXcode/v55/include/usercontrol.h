#include "defines.h"
using namespace G;
using namespace std;
    
 
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
    AutoRunning=0;
	SnapToFlag = 0;
    GlobalFlagOffset=160;
    Shoot=zero;
    RPMGoal=600;
	while (1)
	{
      if (bLeft==1)
      {
        climb=on;
        leftDrive(-100);
        rightDrive(-100);
        wait(250);
        leftDrive(100);
        rightDrive(100);
        wait(750);
        Lift.set(true);
        wait(1000);
        //Lift.set(false);
        //wait(500);        
        StopDrive('b');
        climb=off;
      }


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
			StopDrive('b');
		}
		else {}
    

    if (fly ==on){ if (bR1 && !G::flyprev) fly = off;}
    else if (fly == off) {if (bR1 && !G::flyprev) fly = on;}
    G::flyprev = bR1;

    if (roll ==on){ if (bR2 && !G::rollprev) roll = off;}
    else if (roll == off) {if (bR2 && !G::rollprev) roll = on;}
    G::rollprev = bR2;

    if ( lift==on){ if (bB && !G::liftprev) lift = off;Lift.set(false);}
    else if (lift == off) {if (bB && !G::liftprev) lift = on;Lift.set(true);}
    G::liftprev = bB;

    
    if (bUp==1){hood=on;}
    else if (bDown==1){hood=off;}
		if (bA == 1&&Shoot==zero) { Shoot = one; } //Shoot ball
    else if (bRight == 1&&Shoot==zero) { Shoot = two; }
		else if (bY == 1) { Shoot = zero; } //Stop Mid shot
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