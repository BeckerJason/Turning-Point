#include "defines.h"
using namespace std;
using namespace G; 
fly=on;

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