#include "main.h"
using namespace pros;
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	pros::lcd::register_btn1_cb(on_center_button);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize(){
 pros::Controller Controller (E_CONTROLLER_MASTER);
	Motor Roll (12, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
Motor LF (10, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
Motor LM (7, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
Motor LB(4, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
Motor RF(6, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
Motor RM(5, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
Motor RB(2, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
Motor FlyL(18, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
Motor FlyR(13, E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_DEGREES);
//pros::Motor CapFlip (21, E_MOTOR_GEARSET_36, true, E_MOTOR_ENCODER_DEGREES);
Motor BallFeed(15, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);
Motor Turret(8, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_DEGREES);
Motor Roller2(14, E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_DEGREES);}
