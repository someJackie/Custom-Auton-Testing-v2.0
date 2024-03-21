#include "main.h"

extern void allStop(void);
extern void timeStop(double tiempo);
extern void driveE(double speed, double distance,double delayTiempo=20);
extern void turnE(double speed, double rotate,double delayTiempo=20);
extern void turnI(double speed, double rotate, double delayTiempo=20);
extern void turnIE(double speed, double rotate, double delayTiempo=20);
extern void turnPose(double speed, double targetRotate, double correctingSpeed=30, double delayTiempo=20);
extern void curveE(double radius, double angle, double speed, bool dir, bool forward, double delayTiempo=20);
extern void curve(double targetAngle, double targetDistance, double maxSpeed, double kP_angle=1, double kP_distance=1);
extern void calculateCoords();
extern double coords[2];
extern double velocityV[2];
