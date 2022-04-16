#include "defines.h"
using namespace std;
using namespace G;

fly=on;
if (Color==1){TurnTurretTo(80,-80);}
else {TurnTurretTo(80,80);}
wait(1000);
PLATFORM=no;
GlobalFlagOffset=160;
SnapToFlag=on; 
hood=manual; 
ManualHood=156;
wait(3000); 
//while(MATCHTIMER<ENDSHOT){wait(10);}
Shoot=one; 
T3=zero;
while(Shoot!=0&&T3<3000){wait(10);}
hood=manual;
ManualHood=162;
GlobalFlagOffset=160;
Shoot=one;
T3=zero;
while(Shoot!=0&&T3<3000){wait(10);}
Shoot=zero;
SnapToFlag=off;
TurnTurretTo(75,0);
hood=off; 