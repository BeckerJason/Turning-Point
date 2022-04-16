#include "defines.h"
using namespace std;
using namespace G; 
Lift.set(0);
fly=on;
roll=on;   
hood=off;
SnapToFlag=off;  
Move(100,40,1,1);   //move to ball under cap
wait(200);         
Move(-100,45,1,0);    //move back 

ToWall(-20);          //back to wall
leftDrive(0);
rightDrive(0);
Move(40,10,1,1);
wait(200);
if (Color==1) {pidTurn(-90,0.12, 0.01, .3, 4000);} // Amount initial, secondary
else {pidTurn(90, 0.12, 0.01, .3, 4000);} //turn robot to flags
ScanFlags(2000,on,one);
wait(300);
ScanFlags(2000,on,one);
Turret.rotateTo(0,vex::rotationUnits::deg);
if (Color==1) {TurnTurret(45);}///face left 
else {TurnTurret(-45);}

GlobalGyro=0;

rightDrive(5);
wait(400);
Move(100,45,1,1);
wait(500);
Move(100,-20,0,1);
if (Color==1) {TurnTurret(-45);}///face fwd 
else {TurnTurret(45);}
//if(abs(GlobalGyro)>10) {pidTurn(-GetGyro(), 0.05, 0.01, .3, 4000);}
//wait(300);
if (Color==1) {pidTurn(90-GetGyro(), 0.12, 0.01, .3, 4000);} // Amount initial, secondary
else {pidTurn(-90-GetGyro(),0.12, 0.01, .3, 4000);} //turn robot to flags
GlobalGyro=0;
Intake.set(true);
wait(500);
roll=on;
Move(60,10,1,1);
Intake.set(false);    //lower intake piston
Move(60,-10,0,1);   //move all the way back  x
wait(500); 
if(abs(GlobalGyro)>50) {pidTurn(-GetGyro(), 0.05, 0.01, .3, 4000);}
GlobalGyro=0;
roll=reverse;      //run roll reverse
Move(100,20,1,1);   //move fwd and flip cap
wait(200);
if (Color==1) {pidTurn(90-GetGyro(),0.12, 0.01, .3, 4000); leftDrive(5);wait(200);} // Amount initial, secondary
else {pidTurn(-90-GetGyro(),0.12, 0.01, .3, 4000);rightDrive(5);wait(200);} //turn robot to flags
roll=on;
Move(100,24,1,1);
wait(100);
if (balls==two)
{
if (Color==1){TurnTurret(-150);}
else {TurnTurret(150);}
SnapToFlag=on;
Shoot=one;
Brain.resetTimer();
while(Shoot!=zero&&Brain.timer(vex::timeUnits::msec)<5000);
Shoot=zero;
SnapToFlag=off;
if (Color==1){TurnTurret(150);}
else {TurnTurret(-150);}
}

//grab ball on platform
GlobalGyro=0;
Intake.set(true);         //intake up to grab ball   
wait(500);
roll=on;
Move(40,10,1,1);
Move(80,-2,1,0); //speed,dir,ramp,stop
Intake.set(false);    //lower intake piston
Move(60,-8,0,1);   //move all the way back  x
wait(500);
if(abs(GlobalGyro)>50) {pidTurn(-GetGyro(), 0.05, 0.01, .3, 4000);}

//Back up to wall in front of platform
if (Color==1) {pidTurn(-110, 0.12, 0.01, .3,4000);} // Amount initial, secondary
else {pidTurn(110, 0.12, 0.01, .3, 4000);} //turn robot to flags
Move(100,-48,1,1);   //move all the way back  x
ToWall(-30);
Move(100,18,1,1);   //move all the way back  x

if (balls==two)// if holding 2 balls at back platform ball
{
if (Color==1){TurnTurret(50);}
else {TurnTurret(-50);}
SnapToFlag=on;
Shoot=one;
Brain.resetTimer();
while(Shoot!=zero&&Brain.timer(vex::timeUnits::msec)<5000);
Shoot=zero;
SnapToFlag=off;
if (Color==1){TurnTurret(-50);}
else {TurnTurret(50);}
}

//grab ball on platform
Intake.set(true);   
wait(750);
roll=on;
Move(40,10,1,1);
Move(80,-5,1,0); //speed,dir,ramp,stop
Intake.set(false);    //lower intake piston
Move(60,-5,0,1);   //move all the way back  x
wait(500);


if (Color==1) {pidTurn(50, 0.12, 0.01, .3,4000);} // Amount initial, secondary
else {pidTurn(-50,0.12, 0.01, .3,4000);} //turn robot to flags
Move(100,-10,1,1);
ToWall(-20);
Move(100,48,1,1);
while(1){100;}


