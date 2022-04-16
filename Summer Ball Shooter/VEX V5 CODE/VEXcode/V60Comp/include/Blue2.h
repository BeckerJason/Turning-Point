#include "defines.h"
using namespace std;
using namespace G; 
Turret.resetRotation();
Lift.set(false);
fly=on;
roll=on;    
hood=off; 
SnapToFlag=off;  
Move(90,40,1,brake);   //move to ball under cap
wait(400);         
Move(100,-45,1,coast);    //move back 
//Move(60,-10,1,coast);
ToWall(-20);          //back to wall
leftDrive(0);
rightDrive(0);
Move(100,8,1,brake);
wait(300);
if (Color==1) {pidTurn(-90,0.12, 0.01, .3, 4000);} // Amount initial, secondary
else {pidTurn(90, 0.12, 0.01, .3, 4000);} //turn robot to flags
//ScanFlags(2000,on,zero);
if (Color==1) {TurnTurret(7);}///face left 
else {TurnTurret(-7);}
SnapToFlag=on;
wait(600);
Shoot=one;
T3=zero;
while(Shoot!=0&&T3<2000){wait(10);}
hood=on;
wait(200);
Shoot=one;
T3=zero;
while(Shoot!=0&&T3<2000){wait(10);}
Shoot=zero;
SnapToFlag=off;
//ScanFlags(2000,on,one);
while(abs(enc(Turret))>10){run(Turret,-enc(Turret)/3);}
run(Turret,0);
wait(300);
if (Color==1) {TurnTurret(45);}///face left 
else {TurnTurret(-45);}

GlobalGyro=0;
//Tile(1.5,2000,1,coast);
Move(100,45,0,brake);
wait(200);
Move(100,-22,0,brake);
if (Color==1) {TurnTurret(-45);}///face fwd 
else {TurnTurret(45);}
//if(abs(GlobalGyro)>10) {pidTurn(-GetGyro(), 0.05, 0.01, .3, 4000);}
wait(500);
if (Color==1) {pidTurn(90, 0.12, 0.01, .3, 4000);} // Amount initial, secondary
else {pidTurn(-90,0.12, 0.03, .3, 4000);} //turn robot to cap
GlobalGyro=0;
Intake.set(true);
wait(500);
roll=on;
Move(40,8.5,1,brake);
Intake.set(false);    //lower intake piston
Move(60,-8.5,0,brake);   //move all the way back  x

wait(1000);
//if it has 2 balls shoot middle flags
if (balls==two)
{
if (Color==1) {TurnTurret(-25);}///face left 
else {TurnTurret(25);} 
SnapToFlag=on;
hood=on;
wait(600);
Shoot=one;
T3=zero;
while(Shoot!=0&&T3<2000){wait(10);}
Shoot=zero;
SnapToFlag=off;
if (Color==1) {TurnTurret(25);}///face left 
else {TurnTurret(-25);} 
}
//if(abs(GlobalGyro)>50) {pidTurn(-GetGyro(), 0.05, 0.01, .3, 4000);}
GlobalGyro=0;
roll=reverse;      //run roll reverse
Move(100,20,1,brake);   //move fwd and flip cap
wait(200);
Move(100,-25,1,coast);
ToWall(-20);
Move(60,7,1,brake);
wait(500);
if (Color==1) {pidTurn(57, 0.1, 0.01, .3, 4000);} // Amount initial, secondary
else {pidTurn(-57,0.1, 0.01, .3, 4000);} //turn robot to cap
roll=on;
/*Tile(2,4000,0,coast);
wait(50);
Tile(1.5,4000,1,coast);
Move(60,5,0,1);*/
roll=on;
Move(100,28.5,1,brake);
wait(100);
if (balls==two)
{
if (Color==1){TurnTurret(-110);}
else {TurnTurret(110);}
SnapToFlag=on;
Shoot=one;
Brain.resetTimer();
while(Shoot!=zero&&Brain.timer(vex::timeUnits::msec)<5000);
Shoot=zero;
SnapToFlag=off;
if (Color==1){TurnTurret(110);}
else {TurnTurret(-110);}
}

//grab ball on platform
GlobalGyro=0;
Intake.set(true);         //intake up to grab ball   
wait(500);
roll=on;
Move(40,10,1,brake);
Move(80,-2,1,coast); //speed,dir,ramp,stop
Intake.set(false);    //lower intake piston
Move(60,-8,0,brake);   //move all the way back  x
wait(500);
//if(abs(GlobalGyro)>50) {pidTurn(-GetGyro(), 0.05, 0.01, .3, 4000);}

//Back up to wall in front of platform
if (Color==1) {pidTurn(-57, 0.1, 0.01, .3,4000);} // Amount initial, secondary
else {pidTurn(57, 0.1, 0.01, .3, 4000);} //turn robot to flags

Move(40,-5,1,coast);
Tile(-2,2000,0,coast);
Move(40,-2,0,brake);
wait(500);
if (Color==1) {pidTurn(90, 0.12, 0.01, .3,4000);} // Amount initial, secondary
else {pidTurn(-90, 0.12, 0.01, .3, 4000);} //turn robot to flags
Tile(1.5,2000,1,coast);//while in tile
wait(100);
Tile(1.5,2000,1,coast);//while in tile just in case
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
Move(100,-10,1,brake);
ToWall(-20);
Move(100,48,1,brake);

while(1){100;}


