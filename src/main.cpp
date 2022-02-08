/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\runch                                            */
/*    Created:      Sun Feb 06 2022                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Drivetrain           drivetrain    1, 3, 2, 4, 9   
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

class pid {
  private:
    void linedrive (double distance, double dir, float velocity, double porportion, double slowdown) {
      //higher porportion causes the pid "reacting" turning amount to be higher
      //lower porportion causes the pid "reacting" turning amount to be lower
      //velocity changes base speed
      //just set dir to 0
      //slowdown is the decellaration multiplier, higher it is the more it slows down.
      Inertial.resetHeading();
      Inertial.resetRotation();
      if (velocity > 0) {
        //driving forward
        while (((LeftDriveSmart.rotation(rotationUnits::deg)+RightDriveSmart.rotation(rotationUnits::deg))/2)*12.57/360 < distance) {
          //getting closer
          if(((LeftDriveSmart.rotation(rotationUnits::deg)+RightDriveSmart.rotation(rotationUnits::deg))/2)*12.57/360 > (distance-6)) {
            Mobile.Screen.clearScreen();
            Mobile.Screen.newLine();
            Mobile.Screen.print(((dir-(Inertial.yaw())*porportion)));
            Mobile.Screen.print(":subtracting_value");
            Mobile.Screen.newLine();
            Mobile.Screen.print(Inertial.yaw());
            Mobile.Screen.print(":yaw_value");
            Mobile.Screen.newLine();
            Mobile.Screen.print(((LeftDriveSmart.rotation(rotationUnits::deg)+RightDriveSmart.rotation(rotationUnits::deg))/2)*12.57/360);
            Mobile.Screen.print(":inches_value");
            //actual pid
            double out = distance-(((LeftDriveSmart.rotation(rotationUnits::deg)+RightDriveSmart.rotation(rotationUnits::deg))/2)*12.57/360);
            LeftDriveSmart.spin(vex::directionType::fwd, (velocity-out*slowdown)-(dir-(Inertial.yaw()*porportion)), vex::velocityUnits::pct);
            RightDriveSmart.spin(vex::directionType::fwd, (velocity-out*slowdown)+(dir-(Inertial.yaw()*porportion)), vex::velocityUnits::pct);
          } else {
            //normal
            //displayinfo
            Mobile.Screen.clearScreen();
            Mobile.Screen.newLine();
            Mobile.Screen.print(((dir-(Inertial.yaw())*porportion)));
            Mobile.Screen.print(":subtracting_value");
            Mobile.Screen.newLine();
            Mobile.Screen.print(Inertial.yaw());
            Mobile.Screen.print(":yaw_value");
            Mobile.Screen.newLine();
            Mobile.Screen.print(((LeftDriveSmart.rotation(rotationUnits::deg)+RightDriveSmart.rotation(rotationUnits::deg))/2)*12.57/360);
            Mobile.Screen.print(":inches_value");
            //actual pid
            LeftDriveSmart.spin(vex::directionType::fwd, (velocity-(dir-(Inertial.yaw())*porportion)), vex::velocityUnits::pct);
            RightDriveSmart.spin(vex::directionType::fwd, (velocity+(dir-(Inertial.yaw())*porportion)), vex::velocityUnits::pct);
          }
        }
      } else {
        //driving backwards
        while (((LeftDriveSmart.rotation(rotationUnits::deg)+RightDriveSmart.rotation(rotationUnits::deg))/2)*12.57/360 > distance) {
          //getting closer 
          if(((LeftDriveSmart.rotation(rotationUnits::deg)+RightDriveSmart.rotation(rotationUnits::deg))/2)*12.57/360 < (distance+6)) {
            Mobile.Screen.clearScreen();
            Mobile.Screen.newLine();
            Mobile.Screen.print(((dir-(Inertial.yaw())*porportion)));
            Mobile.Screen.print(":subtracting_value");
            Mobile.Screen.newLine();
            Mobile.Screen.print(Inertial.yaw());
            Mobile.Screen.print(":yaw_value");
            Mobile.Screen.newLine();
            Mobile.Screen.print(((LeftDriveSmart.rotation(rotationUnits::deg)+RightDriveSmart.rotation(rotationUnits::deg))/2)*12.57/360);
            Mobile.Screen.print(":inches_value");
            //actual pid
            double out = distance-(((LeftDriveSmart.rotation(rotationUnits::deg)+RightDriveSmart.rotation(rotationUnits::deg))/2)*12.57/360);
            LeftDriveSmart.spin(vex::directionType::fwd, (velocity-out*slowdown)+(dir-(Inertial.yaw()*porportion)), vex::velocityUnits::pct);
            RightDriveSmart.spin(vex::directionType::fwd, (velocity-out*slowdown)-(dir-(Inertial.yaw()*porportion)), vex::velocityUnits::pct);
          } else{
            //normal
            //displayinfo
            Mobile.Screen.clearScreen();
            Mobile.Screen.newLine();
            Mobile.Screen.print(((dir-(Inertial.yaw())*porportion)));
            Mobile.Screen.print(":subtracting_value");
            Mobile.Screen.newLine();
            Mobile.Screen.print(Inertial.yaw());
            Mobile.Screen.print(":yaw_value");
            Mobile.Screen.newLine();
            Mobile.Screen.print(((LeftDriveSmart.rotation(rotationUnits::deg)+RightDriveSmart.rotation(rotationUnits::deg))/2)*12.57/360);
            Mobile.Screen.print(":inches_value");
            //actual pid
            LeftDriveSmart.spin(vex::directionType::fwd, (velocity+(dir-(Inertial.yaw())*porportion)), vex::velocityUnits::pct);
            RightDriveSmart.spin(vex::directionType::fwd, (velocity-(dir-(Inertial.yaw())*porportion)), vex::velocityUnits::pct);
          }
        }
      }
      LeftDriveSmart.stop(brakeType::brake);
      RightDriveSmart.stop(brakeType::brake);
    }
  public:
    void drive (double distance, double dir, float velocity, double porportion, double slowdown) {
      linedrive(distance,dir,velocity,porportion,slowdown);
    }
};
pid PID;
int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  PID.drive(20,0,90,1.5,5);
  
}
