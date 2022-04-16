#define KF 0
#define KP 1.0f
#define KI 0.001f
#define KD 0.1f
//void run(pros::Motor motorname, double speed)
//{ //pros::motor_pid_s_t pid = pros::Motor::convert_pid(KF, KP, KI, KD);
//  motorname.move(speed);
	//if (speed != 0) { motorname.move(speed); }
	//else { motorname.stop(vex::brakeType::brake); }
//}
void StopDrive()
{
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
	RF.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	RM.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	RB.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	LF.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	LM.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	LB.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
}
