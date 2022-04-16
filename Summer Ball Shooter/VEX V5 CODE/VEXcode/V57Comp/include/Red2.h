#include "defines.h"
using namespace std;
using namespace G; 

Intake.set(true);
wait(750);
Move(20,10,1,1);
roll=on; 
Move(20,-5,1,0); //speed,dir,ramp,stop
Intake.set(false);
Move(20,-5,0,1);
while(1){100;}
     