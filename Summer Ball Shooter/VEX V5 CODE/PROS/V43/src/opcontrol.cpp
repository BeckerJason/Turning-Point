#include "main.h"
using namespace pros;
/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

void opcontrol() {
pros::Controller Controller1 (pros::E_CONTROLLER_MASTER);
	pros::Motor Roll  (12);
	pros::Motor LF (10);
	pros::Motor LM  (7);
	pros::Motor LB (4);
	pros::Motor RF (6);
	pros::Motor RM (5);
	pros::Motor RB (2);
	pros::Motor FlyL (18);
	pros::Motor FlyR (13);
	//pros::Motor CapFlip (21, pros::E_MOTOR_GEARSET_36, true, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor BallFeed (15);
	pros::Motor Turret (8);
	pros::Motor Roller2 (14);
	pros::Vision Vision (16);
	pros::Vision VisionL (11);
	pros::Vision VisionF (19);
	 R=2;
	 AutoRunning=0;
 SnapToFlag = 0;
	 GlobalFlagOffset=160;
	 Shoot=0;
 //R = 4;
 FlipCount = 2;
 Tran = 2;
	 RPMGoal=116;
 while (1)
 {if (bL2 == 1) { SnapToFlag = 1; }
	 //else if ((fabs(Controller1.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y)) > 2 || fabs(Controller1.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X)) > 2) && SnapToFlag == 1) { SnapToFlag = 0; }
	 else if ( AutoRunning == 0 && (abs(Controller1.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y)) > 2 || abs(Controller1.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X)) > 2))
{
		 LF.move_velocity(Controller1.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) + Controller1.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X)); //(Axis3+Axis4)/2
		 LM.move_velocity(Controller1.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) + Controller1.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X)); //(Axis3+Axis4)/2
		 LB.move_velocity(Controller1.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) + Controller1.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X)); //(Axis3+Axis4)/2
		 RF.move_velocity(Controller1.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) - Controller1.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X));//(Axis3-Axis4)/2
		 RM.move_velocity(Controller1.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) - Controller1.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X));//(Axis3-Axis4)/2
		 RB.move_velocity(Controller1.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) - Controller1.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X));//(Axis3-Axis4)/2

	 }
	 else if (AutoRunning == 0)
	 {
		 StopDrive();
	 }
	 else {}

 }

}
