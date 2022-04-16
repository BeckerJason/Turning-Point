#include "defines.h"
using namespace std;
using namespace G; 
frontball=0;
Turret.resetRotation();
Turret.stop(brakeType::hold);
Lift.set(false);
fly=on;
roll=on;    
hood=off; 
SnapToFlag=off;   
Move(90,25,0,coast);   //move to ball under cap         
Move(40,9,0,brake);
wait(300);
Move(100,-30,0,coast);    //move back 
wait(500);
Tile(-2,2500,0,coast);
Move(30,-4,0,brake);
wait(600);


//Turn TO Flags
if (Color==1) {pidTurn(-87,0.12, 0.01, .3, 4000);} // Amount initial, secondary
else {pidTurn(95, 0.12, 0.009, .3, 4000);} //turn robot to flags

//Turn Turret to flags and SHOOT
if (Color==1) {TurnTurretTo(75,7);}///face left 
else {TurnTurretTo(75,-7);}
SnapToFlag=on;
hood=off;
Shoot=one; 
T3=zero;
while(Shoot!=0&&T3<3000){wait(10);}
Shoot=zero;
SnapToFlag=off;

//Turn turret to side
if (Color==1) {TurnTurretTo(25,35);}///face left 
else {TurnTurretTo(25,-35);}
//Move To hit Bottom Flag
Tile(1.5,1500,1,coast);
Move(30,3,1,coast);
Move(100,34,1,brake);//40
wait(200);

//Back up to side of cap
Move(100,-17,0,brake);

//Turn turret straight
if (Color==1) {TurnTurretTo(75,0);}///face fwd 
else {TurnTurretTo(75,0);}
wait(500);

//Turn to cap
if (Color==1) {pidTurn(90, 0.12, 0.01, .3, 4000);} // Amount initial, secondary
else {pidTurn(-90,0.12, 0.03, .3, 4000);} //turn robot to cap
GlobalGyro=0;

//IF 2 balls before cap 
//for(int i=0;i<10&&balls!=two;i++){wait(10);}
if (balls==two)
{
if (Color==1) {TurnTurretTo(75,-15);}///face left 
else {TurnTurretTo(75,15);} 
wait(400);
SwapColor();
SnapToFlag=on;
ManualHood=152;
wait(100);
hood=manual;
//wait(500);
Shoot=one; 
T3=zero;
while(Shoot!=0&&T3<3000){wait(10);}
Shoot=zero;
SwapColor();
hood=off;
SnapToFlag=off;
TurnTurretTo(75,0);
wait(300);
}


Intake.set(true);
wait(200);
roll=on;
Move(80,8,1,brake);
roll=off;
wait(300);
Intake.set(false);    //lower intake piston
Move(50,-4,0,coast);   //move all the way back  x
roll=on;
Move(50,-4,0,brake);
wait(1000);
//if it has 2 balls shoot middle flags
/*if (balls==two)
{
if (Color==1) {TurnTurretTo(75,-25);}///face left 
else {TurnTurretTo(75,25);}
wait(500); 
ScanFlags(2000,on,one);
//while(abs(enc(Turret))>10){run(Turret,-enc(Turret)/3);}
//run(Turret,0);
TurnTurretTo(75,0);
wait(300);
}*/

//if(abs(GlobalGyro)>50) {pidTurn(-GetGyro(), 0.05, 0.01, .3, 4000);}
GlobalGyro=0;

/////  FLIP CAP ///////
roll=reverse;      //run roll reverse
Move(60,16,1,brake);   //move fwd and flip cap
wait(200);
Move(100,-20,1,coast);
wait(500);
ToWall(-25);
Move(60,7,1,brake);
wait(500); 
if (Color==1) {pidTurn(57, 0.1, 0.01, .3, 4000);} // Amount initial, secondary
else {pidTurn(-57,0.09, 0.01, .3, 4000);} //turn robot to cap
roll=on;
/*Tile(2,4000,0,coast);
wait(50);
Tile(1.5,4000,1,coast);
Move(60,5,0,1);*/
roll=on;
Move(100,27,1,brake);
wait(100);
//for(int i=0;i<10&&balls!=two;i++){wait(10);}
if (balls==two)
{

if (Color==1){TurnTurretTo(80,-87);}
else {TurnTurretTo(80,87);}
wait(800);
SnapToFlag=on;
ManualHood=152;
hood=manual;
Hood.startRotateTo(152,vex::rotationUnits::deg,50,vex::velocityUnits::pct);
Shoot=one;
Brain.resetTimer();
while(Shoot!=zero&&Brain.timer(vex::timeUnits::msec)<2500);
Shoot=zero;
SnapToFlag=off;
hood=off;
//ScanFlags(2000,on,one);
/*SnapToFlag=on;
Shoot=one;
Brain.resetTimer();
while(Shoot!=zero&&Brain.timer(vex::timeUnits::msec)<5000);
Shoot=zero;
SnapToFlag=off;
if (Color==1){TurnTurret(110);}
else {TurnTurret(-110);}*/
TurnTurretTo(75,0);
//while(abs(enc(Turret))>10){run(Turret,-enc(Turret)/3);}
//run(Turret,0);

}

//grab ball on platform
GlobalGyro=0;
Intake.set(true);         //intake up to grab ball   
wait(500);
roll=on;
Move(40,10,1,brake);
wait(200);
Move(40,-2,1,coast); //speed,dir,ramp,stop
Intake.set(false);    //lower intake piston
Move(40,-8,0,brake);   //move all the way back  x
wait(500);
//if(abs(GlobalGyro)>50) {pidTurn(-GetGyro(), 0.05, 0.01, .3, 4000);}

//Back up to wall in front of platform
if (Color==1) {pidTurn(-57, 0.1, 0.01, .3,4000);} // Amount initial, secondary
else {pidTurn(57, 0.1, 0.01, .3, 4000);} //turn robot to flags

Move(40,-5,1,coast);
Tile(-2,2000,0,coast);
Move(40,-4,0,brake);
wait(500);
if (Color==1) {pidTurn(90, 0.12, 0.01, .3,4000);} // Amount initial, secondary
else {pidTurn(-87, 0.11, 0.01, .3, 4000);} //turn robot to flags
Tile(1.1,2000,1,coast);//while in tile
wait(100);
Tile(1.1,2000,1,coast);//while in tile just in case
Move(40,14,1,brake);
if (Color==1) {pidTurn(-90, 0.12, 0.01, .3,4000);} // Amount initial, secondary
else {pidTurn(92, 0.12, 0.01, .3, 4000);} //turn robot to flags


/*
Move(50,14,0,coast);
Tile(2,2000,0,brake);//while on grey tile
wait(500);
if (Color==1) {pidTurn(-90, 0.12, 0.01, .3,4000);} // Amount initial, secondary
else {pidTurn(90, 0.12, 0.01, .3, 4000);} //turn robot to flags
Move(100,7,1,brake);   //move all the way back  x

if (balls==two)// if holding 2 balls at back platform ball
{
if (Color==1){TurnTurret(-50);}
else {TurnTurret(50);}
SnapToFlag=on;
Shoot=one;
Brain.resetTimer();
while(Shoot!=zero&&Brain.timer(vex::timeUnits::msec)<5000);
Shoot=zero;
SnapToFlag=off;
if (Color==1){TurnTurret(50);}
else {TurnTurret(-50);}
}

//grab ball on platform
Intake.set(true);   
roll=on;
Move(40,8,1,brake);
Move(80,-5,1,coast); //speed,dir,ramp,stop
Intake.set(false);    //lower intake piston
Move(60,-3,0,brake);   //move all the way back  x
wait(500);


if (Color==1) {pidTurn(25, 0.12, 0.01, .3,4000);} // Amount initial, secondary
else {pidTurn(-25,.12, 0.01, .3,4000);} //turn robot to flags
Move(100,-10,1,coast);
wait(500);
*/
Move(100,40,1,brake);
/*if (frontball==0)
{
  if (Color==1){TurnTurretTo(75,-25);}
  else {TurnTurretTo(75,25);}
  wait(500);
  ScanFlags(3000,on,one);
  //if (Color==1){TurnTurret(-25);}
  //else {TurnTurret(25);}
  TurnTurretTo(75,0);
}
else 
{
  if (Color==1){TurnTurretTo(75,-50);}
  else {TurnTurretTo(75,50);}
}*/
if (Color==1){TurnTurretTo(80,-60);}
else {TurnTurretTo(80,60);}
wait(500);
//while(MATCHTIMER<ENDSHOT){wait(10);}
PLATFORM=no;
SnapToFlag=on;
hood=manual;
ManualHood=155;
wait(500);
Shoot=one; 
T3=zero;
while(Shoot!=0&&T3<3000){wait(10);}
hood=manual;
ManualHood=163;
Shoot=one;
T3=zero;
while(Shoot!=0&&T3<3000){wait(10);}
Shoot=zero;
SnapToFlag=off;
TurnTurretTo(75,0);
hood=off; 
/*SnapToFlag=on;
Shoot=one;
Brain.resetTimer();
while(Shoot!=zero&&Brain.timer(vex::timeUnits::msec)<5000);
Shoot=zero;
SnapToFlag=off;
if (Color==1){TurnTurret(50);}
else {TurnTurret(-50);}
while(1){100;}
*/


