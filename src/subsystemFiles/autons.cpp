#include "main.h"

//Game Autons
void sameColorGoal(){
	//Same Color Goal
	//Drop intake
	driveE(100,-7);
	pros::delay(250);
	//grab triball
	intake2.move(127);
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
	intake2.move(0);
	
	//turnE(50,-45);
	driveE(100,10);
	pistonRight.set_value(false);
	pros::delay(100);
	driveE(100,-10);
	driveE(100,10);
	driveE(50,-10);
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
	intake2.move(127);
	driveE(30,10,350);
	//drive to goal
	driveE(50,-10);
	driveE(100,-24);
	turnPose(100,45,40);
	//Push triball in
	driveE(100,18);
	intake2.move(0);
	turnPose(100,18,50);
	driveMotors.move(100);
	intake2.move(-127);
	pros::delay(500);
	intake2.move(0);

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
	intake2.move(127);
	driveE(40,-4);
	turnPose(100,70,50);
	intake2.move(-127);
	pros::delay(250);
	//Grab triball 2
	turnPose(75,320,30);
	intake2.move(127);
	driveE(100,12,0);
	driveE(30,10,200);
	turnPose(100,90);
	//Push into goal
	pistonLeft.set_value(true);
	intake2.move(-127);
	driveE(100,20);
	intake2.move(0);
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
	turnPose(100,90);
	pros::delay(2000);
	turnPose(100,180);
	pros::delay(2000);
	turnPose(100,270);
	pros::delay(1000);
	turnPose(100,90);


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
	driveE(50, -15);
	turnE(30, -50);
	driveE(10, -4);
	turnE(10,-21);
	
	//Start Shooting
	descore.set_value(true);
	slapperMotors.move(127);
	pros::delay(5000); //Shooting

	//Move to other side
	slapperMotors.move(0);
	descore.set_value(false);
	turnE(30, 50,120);
	driveE(80,32);
	turnE(60, -18);
	driveE(80,85);
	turnE(60, -65);
	// Push in on right side
	driveE(60, 5);
	turnE(60,-55);
	driveE(70, 20);
	turnE(70, 15);
	pistonRight.set_value(true);
	pistonLeft.set_value(true);
	turnE(70, 40);
	driveMotors.move(127);
	pros::delay(1000);
	driveMotors.move(-127);
	pros::delay(500);
	driveMotors.move(127);
	pros::delay(600);
	driveMotors.move(0);
	pistonRight.set_value(false);
	pistonLeft.set_value(false);
	driveE(100,-17,200);
	//first push on center
	turnPose(100, 200);
	driveE(100, 45, 200);
	turnPose(100,320,40);
	pistonRight.set_value(true);
	pistonLeft.set_value(true);
	driveMotors.move(127);
	pros::delay(1000);
	driveMotors.move(-127);
	pros::delay(500);
	driveMotors.move(127);
	pros::delay(600);
	driveMotors.move(-127);
	pros::delay(500);
	driveMotors.move(127);
	pros::delay(600);
	driveMotors.move(0);
	pistonRight.set_value(false);
	pistonLeft.set_value(false);
	//second push on center
	driveE(100,-18);
	turnPose(100,250);
	driveE(100,18);
	turnPose(100,340);
	pistonRight.set_value(true);
	pistonLeft.set_value(true);
	driveMotors.move(127);
	pros::delay(1000);
	driveMotors.move(-127);
	pros::delay(500);
	driveMotors.move(127);
	pros::delay(600);
	driveMotors.move(-127);
	pros::delay(500);
	driveMotors.move(127);
	pros::delay(600);
	driveMotors.move(0);
	pistonRight.set_value(false);
	pistonLeft.set_value(false);





	//turnI(60, 330, 20);
	/**
	//Push in on right
	pistonLeft.set_value(true);
	pros::delay(100);
	driveE(60, 50);
	//turnE(60, -60);
	driveE(30, -25);
	driveE(30, 30);
	driveE(30, -35);
	turnE(60, -30);
	driveE(50, -20);
	driveE(50, 40);
	turnE(100, 40);
	*/

	/*
	//Skills Auton Path
	//Push Triball into goal
	driveE(100,-30);
	turnE(50,-30);
	driveE(100,-5);
	//Line up shooting
	driveE(100,5);
	turnE(50,45);
	driveE(50,10);
	turnE(50,90);
	driveE(35,-7);
	//Shooting
	driveMotors.move(-10);
	pros::delay(40*1000);
	driveMotors.move(0);
	//Drive to Other Side
	driveE(30,5);
	turnE(50,90);
	driveE(75,-25);
	turnE(50,45);
	driveE(100,-85);
	//Push on right Side of Goal
	turnE(50,45);
	driveE(100,-40);
	//Drive to middle
	driveE(35,5);
	turnE(75,-90);
	driveE(100,40);
	turnE(75,-90);
	driveE(100,15);
	//Push into Middle 1
	pistonLeft.set_value(true);
	pistonRight.set_value(true);
	turnE(75,-90);
	driveE(100,30);
	//Push into Middle 2
	pistonLeft.set_value(false);
	pistonRight.set_value(false);
	driveE(100,-30);
	turnE(75,90);
	driveE(100,15);
	pistonLeft.set_value(true);
	pistonRight.set_value(true);
	turnE(75,-90);
	driveE(100,30);
	//Drive to left Side
	pistonLeft.set_value(false);
	pistonRight.set_value(false);
	driveE(100,-30);
	turnE(75,-90);
	driveE(100,-20);
	turnE(75,-90);
	driveE(100,-40);
	//Push left side
	turnE(75,-135);
	driveE(100,-30);
	*/
}
	


