#include "main.h"

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	pros::lcd::register_btn1_cb(on_center_button);
}


void disabled() {}

void competition_initialize() {}

void autonomous() {}

void opcontrol() {
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	pros::Motor frontLeftMtr(1);
	pros::Motor frontRightMtr(2);
	pros::Motor backLeftMtr(3);
	pros::Motor backRightMtr(4);

	pros::Motor topShootingMotor(5);
	pros::Motor bottomShootingMotor(6);

	int speed, turning, left, right;
	int tsm = 0, bsm = 0;

	while (true) {
		speed = master.get_analog(ANALOG_LEFT_Y);
		turning = master.get_analog(ANALOG_RIGHT_X);

		left = speed + turning;
		right = speed - turning;

		frontLeftMtr = left;
		backLeftMtr = left;
		frontRightMtr = right;
		backRightMtr = right;

		tsm = 0;
		bsm = 0;

		// Shoot
		if(master.get_digital(L2)) {
			tsm = -127;
			bsm = -127;

		} else if(master.get_digital(L1)) {
			tsm = 127;
			bsm = -127;
		}

		topShootingMotor = tsm;
		bottomShootingMotor = bsm;

		// Move couter clockwwise
		//reverse both;

		// Passing throuhg
		// don't reverse top
		// reverse bottom

		//intake on
		// intake off

		pros::delay(20);
	}
}
