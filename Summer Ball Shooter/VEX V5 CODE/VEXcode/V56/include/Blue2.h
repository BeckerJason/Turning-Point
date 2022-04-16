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
wait(20);
ToWall(-20);          //back to wall
leftDrive(0);
rightDrive(0);
if (Color==1) {TurnTurret(-85);} //face turret to flags
else {TurnTurret(85);}
ScanFlags(4000,off,one); //timeout,hood,shoot
Shoot=zero;
if (Color==1) {TurnTurret(85);}///face fwd 
else {TurnTurret(-85);}
Move(40,5,1,1);
wait(200);
if (Color==1) {pidTurn(-90, 0.07, 0.05, 0.00, 4000);} // Amount initial, secondary
else {pidTurn(90, 0.07, 0.001, 0.00, 4000);} //turn robot to flags
Move(100,38.5,1,1);
wait(300);

