#include "defines.h"
using namespace std;
using namespace G;
   
    Lift.set(0);
	fly = on;
	run(Roll, 120);
	RPMGoal = 110; 
	//wait(200);
	
	StopDrive();
    wait(50);
	Move(100, 38.74);//40
	wait(300);//200
	Move(100, -22.263);//20   
	Shoot = one;
	Brain.resetTimer();
	while (Shoot == one) { wait(10); if (Brain.timer(vex::timeUnits::msec) > 2000) { break; } }
	Shoot = zero;
	wait(50);//250
	if (Alliance == 'B') { pidTurn(90, 0.07, 0.05, 0.00, 4000); }//Amount initial, secondary
	else{ pidTurn(-90, 0.07, 0.001, 0.00, 4000);}
    ///leftDrive(-2);
    ///rightDrive(-2);					
    ///wait(300);
    roll=on;
	run(Roll, -100);
	TrackColor=Alliance;
	//wait(100);
	//leftDrive(-50);
	//rightDrive(-50);
	//wait(1000);
  ToWall(-30);
	StopDrive();
  run(Roll,-50);
	while (Move(90, 50.26) != 1) {wait(10); }//Drive forward but if ball is seen by sensor kill flipper
//2400

   // while(Vision.objects[0].exists!=1){wait(5);}rightDrive(10);
    wait(200);//400  
 
	Move(90, -10);//480
	wait(300);//600
	if (Alliance == 'B') { pidTurn(53, 0.07, 0.02, 0.01, 3000); }//Amount initial, secondary	 
	else{ pidTurn(-50, 0.07, 0.001, 0.01, 3000);}
      	leftDrive(1);
	rightDrive(1);																	   
	wait(200);
    run(Roll, 100);
	//wait(300);
	Move(70, 22.6);//890/////GRAB BALL UNDER CAP
	//wait(100);//700
    //run(Roll, 0);
    //Move2(50,3);
    wait (100);//300
    run(Roll,100);
    //wait(300);
    //Move(30,-3);
    Move(100, -11.25);//203//3 was added
    wait(200);//400
        	if (Alliance == 'B') { pidTurn(35, 0.07, 0.01, 0.01, 3000); }//Amount initial, secondary
	else{ pidTurn(-29, 0.07, 0.001, 0.01, 3000);}
    wait(200);
	/*Shoot = 1;
    Brain.resetTimer();
	while (Shoo0t == 1) { wait(10); if (Brain.timer(vex::timeUnits::msec) > 2000) { break; } }
	Shoot = 0;*/
  	leftDrive(-100);
	rightDrive(-100);																	   
	wait(900);
	ToWall(-40);
	StopDrive(); 
    //wait(300);
				  
    Move(80,3);						 
    wait(200);
   if (Alliance == 'B') { pidTurn(-97, 0.07, 0.01, 0.01, 3000); }//Amount initial, secondary
	else{ pidTurn(97, 0.07, 0.001, 0.01, 3000);}
    
         if (Alliance == 'B') { TurnTurret(50);}
    else {TurnTurret(-50);}
      	//leftDrive(20);
	//rightDrive(20);
	//wait(2000);
    RPMGoal=145;
    ToWall(25);
    StopDrive();
     Move(80,-3);
     if (Alliance == 'B') { TurnTurret(-55);}
    else {TurnTurret(55);}
    if (Alliance == 'B') { pidTurn(-5, 0.04, 0.01, 0.01, 1000); }//Amount initial, secondary	 
	else{ pidTurn(5, 0.04, 0.01, 0.01, 1000);}
    Move(100,-11.18);//270//12.18
    Shoot = 1;
    Brain.resetTimer();
	while (Shoot == 1) { wait(10); if (Brain.timer(vex::timeUnits::msec) > 2000) { break; } }
	Shoot = 0;
     Move(90,3);//270//12.18
    wait(300);
			   
          if (Alliance == 'B') { pidTurn(100, 0.07, 0.05, 0.00, 3000); }//Amount initial, secondary
	else{ pidTurn(-100, 0.07, 0.001, 0.01, 3000);}					
    //wait(300);
      	//leftDrive(-20);
	//rightDrive(-20);									
	//wait(1500);
    ToWall(-30); 
    StopDrive();
     //if (Alliance == 'B') { TurnTurret(-15);}
    //TurnTurret(15);
								 					
    //wait(300);
    Move(60,85);

	run(Roll, 0);
    roll = off;
    	fly = off;