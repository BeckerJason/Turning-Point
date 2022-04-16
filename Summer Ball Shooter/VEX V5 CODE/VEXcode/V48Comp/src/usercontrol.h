#include "globals.h"
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