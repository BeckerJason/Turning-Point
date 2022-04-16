/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\Jason                                            */
/*    Created:      Thu Apr 04 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"
#include "Vision.h"
using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;
vex::motor29   Lift = vex::motor29(Brain.ThreeWirePort.B);
vex::motor29   Lift2 = vex::motor29(Brain.ThreeWirePort.H);

// define your global instances of motors and other devices here


int main() {
    int count = 0;
   Lift.spin(directionType::fwd,0,velocityUnits::pct );
    while(1) {
        Brain.Screen.printAt( 10, 50, "Hello V5 %d", count++ );
        // Allow other tasks to run
        this_thread::sleep_for(10);
    }
}
