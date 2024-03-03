#include "main.h"
#include <math.h>


double PI = 3.1415;
double wheelCir = 10.21;
double robotDiameter = 10.75;
double gearRatio = 0.5; //Gear Ratio Convertion Factor real = 0.6
void allStop(){
    //stops motors
    driveMotors.move(0);
}



/*Stops drive train for certain amount of time in milliseconds*/

void timeStop(double tiempo){
    // tiempo = time in milliseconds
    allStop();
    pros::delay(tiempo);
}

/**
 * Drives forward/backwards for a certain distance in inches and at a certain percentage of full speed
 * */
void driveE(double speed, double distance, double delayTiempo){
    //speed = speed percentage 
    //distance = distance in inches
    //delayTiempo = delay in milliseconds
    pros::lcd::set_text(7, "driveE");
    double degree =(distance/wheelCir)*360*gearRatio;
    double rpm = 2*speed;
    if (speed>100 || speed<0){
        return;
    }
    
    driveMotors.tare_position();
     
    double target = rightDown.get_position()+degree;
    driveMotors.move_relative(degree,rpm);

    pros::lcd::set_text(7,"DrivingE");
    while (!((rightDown.get_position() < target+10) && (rightDown.get_position() > target-10))){
        pros::delay(5);
    }
    timeStop(delayTiempo);
    pros::lcd::set_text(7,"Done");
    
}
/**
 * Turns robot a certain degrees at a certain speed in percentage
 * */
void turnE(double speed, double rotate, double delayTiempo){
    //speed = speed percentage
    //rotate = degrees Negative: CounterClockWise | Positive ClockWise
    //delayTiempo = delay in milliseconds
    //diameter = 11.5 inches

    if (speed>100 || speed<0){
        return;
    }  
    double degree = 3.307*rotate*gearRatio; //((33.772*(rotate/360))/3.25)*360*gearRatio; // diameter of robot / wheel diameter
    double rpm = 2*speed;

    driveMotors.tare_position();
    double target = leftDown.get_position()+degree;
    leftSide.move_relative(degree,rpm);
    rightSide.move_relative(-degree,rpm);

    while (!((leftDown.get_position() < target+5) && (leftDown.get_position() > target-5))){
        pros::lcd::set_text(7,"TurningE");
        pros::delay(5);
    }
    timeStop(delayTiempo);
    pros::lcd::set_text(7,"Done");
}
/**
 * Turns Robot a certain degrees at a certain speed in percentage
 * Keeps turning Robot until imu has sensed that it has turned the target amount of degrees
*/
void turnI(double speed, double rotate,double delayTiempo){
    //speed = speed in percentage
    //rotate = target degrees rotate (-360,360)
    double previousHeading = imuSensor.get_heading();
    imuSensor.tare_heading();

    double rpm = (speed/100)*127; //Accounting for the fact that move takes in voltage (-127,127) so just multiplying percentage by 127
    
    double direction = 1;
    if (rotate>360 ||  rotate < -360){
        return;
    }

    if (rotate<0){
        direction = -1;
    }
    //Keep spinning until imu heading matches target angle
    leftSide.move(rpm*direction);
    rightSide.move(-rpm*direction);

    double target = rotate+360;
    double currentHeading = imuSensor.get_heading()+360;

    double difference = target - currentHeading;
    if (difference<0){
        difference = -difference;
    }
    double difPercent = (difference/rotate);
    //Makes a range of +- 5 degrees from target where the robot will stop
    while (!((currentHeading>target-5) && ((currentHeading<target+5)))){
        currentHeading = imuSensor.get_heading()+360;

        difference = target - currentHeading;
        if (difference<0){
            difference = -difference;
        }
        difPercent = (difference/rotate);
        leftSide.move(difPercent*rpm*direction);
        rightSide.move(difPercent*-rpm*direction);
        pros::delay(20);
    }
    currentHeading = imuSensor.get_heading();
    double newHeading = previousHeading+target;
    timeStop(delayTiempo);
}

void turnIE(double speed, double rotate, double delayTiempo){
    double previousHeading = imuSensor.get_heading();
    imuSensor.tare_heading();
    turnE(speed,rotate+50,0);
    pros::delay(250);
    double currentHeading = imuSensor.get_heading();

    double target = rotate;
    double difference = target - currentHeading;

    double direction = 1;
    if (difference<0){
        direction = -1;
    }

    leftSide.move(30*direction);
    rightSide.move(-30*direction);
    while (!((currentHeading>target-1) && ((currentHeading<target+1)))){
        pros::delay(10);
        currentHeading = imuSensor.get_heading();
    }
    timeStop(delayTiempo);
    currentHeading = imuSensor.get_heading();
    double newHeading = previousHeading+currentHeading;
    if (newHeading<360){
        newHeading+=360;
    }
    if (newHeading>360){
        newHeading-=360;
    }
    imuSensor.set_heading(newHeading);
}

void turnPose(double speed, double targetRotate, double correctingSpeed, double delayTiempo){
    double previousHeading = imuSensor.get_heading();
    double rotate = targetRotate-previousHeading;
    if (rotate>180){
        rotate = rotate-360;
    }
    if (rotate<-180){
        rotate = 360+rotate;
    }
    turnE(speed,rotate,0);
    pros::delay(200);
    double currentHeading = imuSensor.get_heading();

    double difference = targetRotate - currentHeading;

    if (difference>180){
        difference = difference-360;
    }
    if (rotate<-180){
        difference = 360+difference;
    }


    double direction = 1;
    if (difference<0){
        direction = -1;
    }
    if (difference<0){
        difference =-difference;
    }
    double previousDifference = difference;
    leftSide.move(correctingSpeed*direction);
    rightSide.move(-correctingSpeed*direction);
    while (!((imuSensor.get_heading()>targetRotate-2) && (imuSensor.get_heading()<targetRotate+2))){
        /*
        difference = targetRotate - currentHeading; 
        if (difference<0){
            difference =-difference;
        }
        if (previousDifference<difference){
            break;
        }
        else{
            previousDifference = difference;
        }
        */
        pros::delay(10);
    }
    timeStop(delayTiempo);
}


/**
 * Makes the robot drive in a circle
*/
void curveE(double radius, double angle, double speed, double dir ,double forward, double delayTiempo){
    //out = outer arc inches
    //in = inner arc
    //speed = speed percentage
    //dir = horizontal + right | - left
    //forward = verticle + forward | - left
    if (speed>100 || speed<0){
        return;
    }
    if (dir!= 1 || dir!=-1){
        return;
    }
    if (forward!= 1 || forward!=-1){
        return;
    }

    double in = 2*radius*3.14*(angle/360); //How much inner wheels have to travel
    double out = 2*(radius+10.75)*3.14*(angle/360); // How much outer wheels have to travel
    
    double outDegree = (out/wheelCir)*360*gearRatio*forward;
    double inDegree = (in/wheelCir)*360*gearRatio*forward;
    double rpm = speed*2;
    double tiempo = (out/wheelCir)/(rpm);
    double speedIn =((in/wheelCir))/tiempo;

    if (dir==1){
        //clockwise
        
        leftSide.move_relative(inDegree,speedIn);
        rightSide.move_relative(outDegree,rpm); 

        double target = rightDown.get_position()+(outDegree*forward);
        while (!((rightDown.get_position() < target+5) && (rightDown.get_position() > target-5))){
            pros::delay(5);
        }
        timeStop(delayTiempo);
    }
    if (dir==-1){
        //counter-clockwise

        leftSide.move_relative(outDegree,rpm);
        rightSide.move_relative(inDegree,speedIn);

        double target = leftDown.get_position()+(outDegree*forward);
        while (!((leftDown.get_position() < target+5) && (leftDown.get_position() > target-5))){
            pros::delay(5);
        }
        timeStop(delayTiempo);
    }

    
}

//Odometery/Coordinate system Prototype

double coords[2]={0,0};
double velocityV[2]={0,0};
double acceleration;
double accelRad;
void calculateCoords(){
    while (true){
        double deltat = 0.0020;
        pros::c::imu_accel_s_t accel = imuSensor.get_accel();
        //use kinematics formula delta(x)=vt*.5at^2
        
        acceleration = sqrt(accel.x*accel.x+accel.y*accel.y);
        // Still need to check if accel.y or accel.x is 0 because atan of that is undefined
        accelRad = atan(accel.y/accel.x);

        //Adjusting for principle solutions of arcTan    
        if (accel.y<0 && accel.x<0){
            accelRad += PI;
        }
        if (accel.x<0 && accel.y>0){
            accelRad += PI;
        }

        coords[0] = coords[0] + velocityV[0]*deltat+.5*(deltat*deltat);
        coords[1] = coords[1] + velocityV[1]*deltat+.5*accel.y*(deltat*deltat);

        //calculate velocity (After position because initial velocity is 0 and this is the next initial velocity)

        velocityV[0] = velocityV[0] + accel.x*deltat;
        velocityV[1] = velocityV[1] + accel.y*deltat;
        
        pros::delay(20);
    }
}


