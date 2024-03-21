#include "main.h"

//Game Autons
void sameColorGoal(){
	//Same Color Goal
	//Drop intake
	driveE(100,-7);
	pros::delay(250);
	//grab triball
	intake.move(127);
	driveE(35,16);
	pros::delay(200);
	//Push 2 triballs
	driveE(100,-20);
	driveE(50,-17);
	driveE(50,5);
	turnE(25,170);
	pistonRight.set_value(true);
	driveE(50,28);
	turnE(50,-45);
	driveE(100,15);
	//Push both triballs in
	intake.move(0);
	
	//turnE(50,-45);
	driveE(100,10);
	pistonRight.set_value(false);
	pros::delay(100);
	driveE(100,-10);
	driveE(100,10);
	driveE(50,-10);
}
void angryOppositeColor(){
	//Same Color Goal
	//Rushing to steal triball
	pistonLeft.set_value(true);
	driveE(100,20,0);
	pistonLeft.set_value(false);
	intake.move(127);
	driveE(100,10,0);
	driveE(50,5,0);
	driveE(30,5,300);
	//Drive Back and push other over
	driveE(50,-5,0);
	turnPose(100,255,50);
	driveMotors.move(-127);
	pros::delay(500);
	driveMotors.move(0);
	//drive to descore
	driveE(50,7);
	turnPose(100,335);
	driveE(100,45);
	//descore
	turnPose(100,135);
	descore.set_value(true);
	driveE(50,17);
}

void AWPoppositeColor(){
	imuSensor.tare_heading();
	driveMotors.set_brake_modes(pros::E_MOTOR_BRAKE_COAST);
	driveE(100,20,0);
	turnPose(100,90,45,500);
	driveMotors.set_brake_modes(pros::E_MOTOR_BRAKE_BRAKE);




}

void sameColorGoal2(){
	//kick triball
	/*
	pistonRight.set_value(true);
	pros::delay(250);
	pistonRight.set_value(false);
	pros::delay(100);
	*/
	//unstuck intake
	/*
	driveMotors.move(-127);
	pros::delay(500);
	driveMotors.move(0);
	*/
	//drive to pick up triball
	turnPose(100,270,30);
	driveE(100,24,0);
	intake.move(127);
	driveE(30,10,350);
	//drive to goal
	driveE(50,-10);
	driveE(100,-24);
	turnPose(100,45,40);
	//Push triball in
	driveE(100,18);
	intake.move(0);
	turnPose(100,18,50);
	driveMotors.move(100);
	intake.move(-127);
	pros::delay(500);
	intake.move(0);

	driveMotors.move(0);
	driveE(100,-5,200);
	driveMotors.move(127);
	pros::delay(500);
	driveMotors.move(0);

	//Grab other triball
	driveE(100,-17,250);
	turnPose(100,300);
	driveE(100,45);
	driveE(30,8,200);
	intake.move(127);
	driveE(40,-4);
	turnPose(100,70,50);
	intake.move(-127);
	pros::delay(250);
	//Grab triball 2
	turnPose(75,320,30);
	intake.move(127);
	driveE(100,12,0);
	driveE(30,10,200);
	turnPose(100,90);
	//Push into goal
	pistonLeft.set_value(true);
	intake.move(-127);
	driveE(100,20);
	intake.move(0);
	driveMotors.move(100);
	pros::delay(500);
	driveMotors.move(0);
	pistonRight.set_value(false);
	driveE(75,-7,200);

}

void oppositeColorGoal(){
	//Opposite Color Goal
	//Push triball in
	driveE(35,-17);
	turnPose(100,45);
	driveE(35,10);
	pros::delay(1000);
	driveE(50,10);
	descore.set_value(true);
	driveE(50,6);
	turnE(100,-180);
	descore.set_value(false);
}


	
//Simple Push
void simplePush(){
	driveMotors.move(-127);
	pros::delay(1250);
	driveMotors.move(127);
	pros::delay(250);
	driveMotors.move(0);
}

//Testing autoFunctions
void autonTesting(){
	turnPose(100,45);
	pros::delay(2000);
	turnPose(100,90);
	pros::delay(2000);
	turnPose(100,300);
	pros::delay(1000);
	turnPose(100,315);


}
void simpleSkills(){
	//Simple Skills
	driveE(75,-22);
	turnE(50,-85);
	pros::delay(200);
	driveE(50,-35);
	descore.set_value(true);
	slapperMotors.move(-127);
	driveMotors.move(-10);
	
	pros::delay(45*1000);
	slapperMotors.move(0);
	driveE(100,10);
	turnE(50,-25);
	driveE(100,100);
}

void encodersTest(){ 
	//Testing Encoders
	driveMotors.move(30);
	pros::delay(10000); //10 Seconds
	driveMotors.move(0);
}

void skillsAuton(){
	//alignment
	/*
	driveE(50, -15);
	turnE(30, -50);
	driveE(10, -4);
	turnE(10,-21);
	*/
	//Starting Alignment
	imuSensor.tare_heading();
	//slapperMotors.move(127);
	pros::delay(100);
	//slapperMotors.move(80);
	pros::delay(500);
	driveE(75,-13);
	//slapperMotors.move(0);
	turnPose(100,305,35);
	driveMotors.move(-90);
	pros::delay(100);

	//Start Shooting
	//slapperMotors.move(127);
	descore.set_value(true);
	driveMotors.set_brake_modes(pros::E_MOTOR_BRAKE_BRAKE);
	driveMotors.move(-10);
	pros::delay(1000);
	driveMotors.move(0);
	pros::delay(3000); //Shooting 24 Seconds


	//Move to other side
	slapperMotors.move(0);
	descore.set_value(false);
	driveE(50,5);
	turnPose(100,345,50);
	driveE(80,30);
	turnPose(100, 320,50);
	driveE(100,95);

	// Push in on right side
	turnPose(100, 285,50);
	driveE(100, 27);
	turnPose(100,240,50);
	//pistonLeft.set_value(true);
	driveMotors.move(127);
	pros::delay(500);
	driveMotors.move(-127);
	pros::delay(200);
	driveMotors.move(127);
	pros::delay(300);
	driveMotors.move(0);
	//pistonLeft.set_value(false);
	//pistonRight.set_value(false);
	//pistonLeft.set_value(false);
	driveE(75,-13,400);

	//first push on center
	turnPose(100, 168,35);
	driveE(100, 58,100);
	turnPose(100,220,40);
	driveE(100,5);
	turnPose(100,285,60);
	pistonRight.set_value(true);
	pistonLeft.set_value(true);
	driveMotors.move(127);
	pros::delay(1000);
	driveE(100,-10);
	driveMotors.move(127);
	pros::delay(500);
	driveMotors.move(0);
	pistonRight.set_value(false);
	pistonLeft.set_value(false);



	//second push on center
	driveE(100,-20);
	turnPose(100,225,60);
	driveE(100,10);
	turnPose(100,285,60);
	pistonRight.set_value(true);
	pistonLeft.set_value(true);
	driveMotors.move(127);
	pros::delay(1000);
	driveE(100,-10);
	driveMotors.move(127);
	pros::delay(500);
	driveMotors.move(0);
	pistonRight.set_value(false);
	pistonLeft.set_value(false);

	//Left side push
	driveE(100,-23);
	turnPose(100,265,40);
	driveE(100,55);
	turnPose(100,350,35);

	/*
	//Third Push on Middle
	driveE(100,-22);
	turnPose(100,220,60);
	driveE(100,20);
	turnPose(100,285,60);
	pistonRight.set_value(true);
	pistonLeft.set_value(true);
	driveMotors.move(127);
	pros::delay(1000);
	driveMotors.move(-127);
	pros::delay(500);
	driveMotors.move(127);
	pros::delay(600);
	driveMotors.move(0);
	pistonRight.set_value(false);
	pistonLeft.set_value(false);
	*/
	/*
	// Reposition
	driveMotors.move(-80);
	pros::delay(2000);
	driveMotors.move(30);
	pros::delay(400);
	turnPose(100, 260);

	//Final push
	driveE(90, 8);
	turnPose(100, 280);
	driveMotors.move(127);
	pros::delay(850);
	driveMotors.move(0);
	pros::delay(50);
	driveMotors.move(-90);
	pros::delay(690);
	driveMotors.move(0);
	// Second reposition
	*/
	/**
	//Left Side Push
	driveE(100,-17);
	turnPose(100,270,60);
	driveE(100,40);
	turnPose(100,345);
	driveE(100,18);
	turnPose(100,45);
	driveMotors.move(127);
	pros::delay(1000);
	driveMotors.move(-127);
	pros::delay(500);
	driveMotors.move(127);
	pros::delay(600);
	driveMotors.move(0);
	driveE(100,-18);
	*/
}

void complexAuton(){
	//Starting Alignment
	imuSensor.tare_heading();
	//slapperMotors.move(127);
	pros::delay(100);
	//slapperMotors.move(80);
	pros::delay(500);
	driveE(75,-11);
	//slapperMotors.move(0);
	turnPose(100,305,35);
	driveE(50,-5);

	//Curving into barrier
	driveE(50, 6);
	turnPose(100, 120);
}

