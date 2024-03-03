#include "main.h"
#include <numeric>
#include "../include/pros/misc.h"


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
/**
 * Screen function for rightDown and LeftDown motor encoder values
*/
void screen(){
	while (true){
		pros::lcd::print(0,"rightDown: %f", rightDown.get_position());
		pros::lcd::print(1,"leftDown: %f", leftDown.get_position());
		pros::delay(10);
	}
}
/**
 * Screen function for all motor encoder values and for heading from IMU
*/
void encoderScreen(){
	while (true){
		pros::lcd::print(0,"rightUp: %f", rightUp.get_position());
		pros::lcd::print(1,"rightMiddle: %f", rightMiddle.get_position());
		pros::lcd::print(2,"rightDown: %f", rightDown.get_position());
		pros::lcd::print(3,"leftUp: %f", leftUp.get_position());
		pros::lcd::print(4,"leftMiddle: %f", leftMiddle.get_position());
		pros::lcd::print(5,"leftDown: %f", leftDown.get_position());
		pros::lcd::print(6,"Heading: %f",imuSensor.get_heading());
		pros::delay(10);
	}
}
/**
 * Screen function for custom odometry values
*/
void OdometryScreen(){
	while(true){
		pros::lcd::print(0,"x Position: %f", coords[0]);
		pros::lcd::print(1,"y Position: %f", coords[1]);

		pros::lcd::print(0,"x Velocity: %f", velocityV[0]);
		pros::lcd::print(0,"y Velocity: %f", velocityV[1]);

		pros::lcd::print(6,"Heading: %f",imuSensor.get_heading());
	}
}

/**
 * Toggle code for pnuematics that can run in the background so that extending pnuematics doesn't interrupt driving
*/
void pToggle(){
	bool leftWing = true;
	bool rightWing = true;
	bool descoreToggle = true;
	while(true){
		//wings
		if (controller.get_digital_new_press(DIGITAL_Y)==true){
			if (rightWing){
				pistonRight.set_value(true);
				rightWing = false;
			}
			else{
				pistonRight.set_value(false);
				rightWing = true;
			}
		}

		if (controller.get_digital_new_press(DIGITAL_RIGHT)==true){
			if (leftWing){
				pistonLeft.set_value(true);
				leftWing = false;
			}
			else{
				pistonLeft.set_value(false);
				leftWing = true;	
			}
		}
		
		//descore
		
		if (controller.get_digital_new_press(DIGITAL_DOWN)==true){
			if (descoreToggle){
				descore.set_value(true);
				descoreToggle = false;
				pros::delay(500);
			}
			else{
				descore.set_value(false);
				descoreToggle = true;
				pros::delay(500);
			}
		}
		pros::delay(20);
		
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
	//driveMotors.set_brake_modes(pros::E_MOTOR_BRAKE_COAST);
	//sylib::initialize();
	//IMU Calibration

	imuSensor.reset(true);



	pros::Task screenTask(encoderScreen); //continuously displays named screen function
	
	//pros::Task task(calculateCoords); //Experimental Coords 
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
	driveMotors.set_brake_modes(pros::E_MOTOR_BRAKE_COAST);
	slapperMotors.set_brake_modes(pros::E_MOTOR_BRAKE_COAST);
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	driveMotors.set_brake_modes(pros::E_MOTOR_BRAKE_BRAKE);
	slapperMotors.set_brake_modes(pros::E_MOTOR_BRAKE_COAST);
	
	//driveE(90, -50);
	//sameColorGoal();
	sameColorGoal2();
	//oppositeColorGoal();
	//simplePush();
	//autonTesting();
	//simpleSkills();
	//encodersTest();
	//skillsAuton();
}

/**
 *
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
	//pros::Task toggleTask(pToggle);
	/*
	int time = pros::millis();
	int iter = 0;
	while (imuSensor.is_calibrating()){
		pros::lcd::print(0,"IMU calibrating... %d\n",iter);
		iter+=10;
		pros::delay(10);
	}
	*/
	while (true) {
		pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
		                 (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
		                 (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);
		//Basic Movement Code
		int vert = controller.get_analog(ANALOG_LEFT_Y);
		int hori = controller.get_analog(ANALOG_RIGHT_X);

		int leftV = vert+hori;
		int rightV = vert-hori;

		leftSide.move(leftV);
		rightSide.move(rightV);

		//Looking at the temps of the slapper Motors

		if (slapper1.get_temperature()<50){
			//slapper
			if (controller.get_digital_new_press(DIGITAL_DOWN)==true){
				if (slapper1.is_stopped()==1){ //is stopped?
					slapper1.move(127);
				}
				else{
					slapper1.move(0);
				}
			}
		}
		else{
			slapper1.move(0);
		}

		//wheellock when slingshot is active
		if (slapper1.is_stopped()==0){ //is moving?
			driveMotors.set_brake_modes(pros::E_MOTOR_BRAKE_BRAKE);
		}
		else{
			driveMotors.set_brake_modes(pros::E_MOTOR_BRAKE_COAST);
		}

		
		//intake
		if (controller.get_digital(DIGITAL_R1)==true){
			intake2.move(127); //intaking
		}
		if (controller.get_digital(DIGITAL_L1)==true){
			intake2.move(-127); //outtaking
		}
		//turn off intake
		if (controller.get_digital(DIGITAL_B)==true){
			intake2.move(0);
		}

		//wings
		/* Toggle
		if (controller.get_digital(DIGITAL_R2)==true){
			if (wingsToggle){
				piston1.set_value(true);
				piston2.set_value(true);
				wingsToggle = false;
				pros::delay(100);
			}
			else{
				piston1.set_value(false);
				piston2.set_value(false);
				wingsToggle = true;
				pros::delay(100);	
			}
		}
		*/
		//descore
		/* Toggle
		if (controller.get_digital(DIGITAL_L2)==true){
			if (descoreToggle){
				descore.set_value(true);
				descoreToggle = false;
				pros::delay(100);
			}
			else{
				descore.set_value(false);
				descoreToggle = true;
				pros::delay(100);
			}
		}
		*/

		//descore
		if (controller.get_digital(DIGITAL_R2)){
			descore.set_value(true);
		}
		if (controller.get_digital(DIGITAL_L2)){
			descore.set_value(false);
		}
		
		//wings
		if (controller.get_digital(DIGITAL_Y)==true){
			pistonLeft.set_value(true);
			pistonRight.set_value(true);
		}
		if (controller.get_digital(DIGITAL_LEFT)==true){
			pistonLeft.set_value(false);
			pistonRight.set_value(false);
		}
		
		pros::delay(20);
	}
}

//extern double coords;
//extern double velocityV;


