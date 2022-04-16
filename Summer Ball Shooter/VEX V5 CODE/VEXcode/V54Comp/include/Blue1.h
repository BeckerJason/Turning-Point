#include "defines.h"
using namespace std;
using namespace G;
 
Lift.set(false); //start with the lift off
Inake.set(false); //make sure intake piston is off
fly = on; //Turn Flywheel on
roll=off; //start with front roller off
RPMGoal = 600; //Set the RPM Goal to 600
StopDrive(); //make sure the drivetrain is stopped
Move(100, 38.74,1,1);   // move 100% 38" ramp stop to hit bottom flag
wait(300);          // 200
Move(100, -22.263); // 20
Shoot = one;
Brain.resetTimer();
while (Shoot == one) {
  wait(10);
  if (Brain.timer(vex::timeUnits::msec) > 2000) {
    break;
  }
} 
Shoot = zero;
wait(50); // 250
if (Alliance == 'B') {
  pidTurn(90, 0.07, 0.05, 0.00, 4000);
} // Amount initial, secondary
else {
  pidTurn(-90, 0.07, 0.001, 0.00, 4000);
}