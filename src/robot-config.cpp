#include "vex.h"
using namespace vex;
using signature = vision::signature;
using code = vision::code;

//Brain
brain Brain;

//Left Side Motor
motor L1 = motor(PORT11, ratio6_1, true);
motor L2 = motor(PORT13, ratio6_1, false);
motor L3 = motor(PORT12, ratio6_1, true);

//Right Side Motor
motor R1 = motor(PORT19, ratio6_1, false);
motor R2 = motor(PORT18, ratio6_1, true);
motor R3 = motor(PORT20, ratio6_1, false);

//Intake Motor
motor Intake1 = motor(PORT1, ratio6_1, true);
motor Intake2 = motor(PORT15, ratio6_1, false);

//Arm Motor
motor Arm = motor(PORT16, ratio18_1, true);

//Sensor
inertial Inertial = inertial(PORT10);
distance Distance = distance(PORT2);
encoder Encoder = encoder(Brain.ThreeWirePort.B);

//Neumatics Parts
pneumatics Clamp = pneumatics(Brain.ThreeWirePort.A);
pneumatics Hang = pneumatics(Brain.ThreeWirePort.C);

//Controller
controller Controller = controller(primary);

//Motor Group
motor_group Intake(Intake1, Intake2);
motor_group LeftMotor(L1, L2, L3);
motor_group RightMotor(R1, R2, R3);
void vexcodeInit(void) {}