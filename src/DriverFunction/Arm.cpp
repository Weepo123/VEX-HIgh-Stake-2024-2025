// Include necessary header files for the VEX robotics system
#include "vex.h"
#include "robot-config.h"
#include "DriverFunction/DriverFunction.h"

// Global variables to control the arm's state
bool SetToGrapRing = true;  // Flag to indicate if the arm should move to grasp a ring
bool ResetHand = false;     // Flag to indicate if the arm should reset to its initial position

// Constants for arm positions (in degrees)
int GrapRingPosition = 30;  // Position for grasping rings
int ArmMaxPosition = 270;   // Maximum allowed position for the arm
int ArmMinPosition = 5;     // Minimum allowed position for the arm

// Function to automatically set the arm's position
void ArmSet() {
    // If the arm is set to grasp a ring
    if(SetToGrapRing){
        // If the arm hasn't reached the grasping position yet
        if (Arm.position(deg) < GrapRingPosition) {
            Arm.spin(fwd, -12, volt);  // Move the arm forward at 12 volts
        }
        // If the arm has reached or passed the grasping position
        if (Arm.position(deg) >= GrapRingPosition) {
            Arm.stop(hold);           // Stop the arm and hold its position
            SetToGrapRing = false;    // Turn off the grasping flag
            ResetHand = true;         // Set the flag to reset the arm
        }
    }

    // If the arm is set to reset
    if (ResetHand) {
        // If the arm is at or past the maximum position
        if (Arm.position(deg) >= ArmMaxPosition) {
            Arm.spin(fwd, 12, volt); // Move the arm backward at 12 volts
        }
        // If the arm has moved past the minimum position but not reached max
        else if (Arm.position(deg) > ArmMinPosition) {
            Arm.stop(coast);          // Stop the arm and allow it to coast
            ResetHand = false;        // Turn off the reset flag
            SetToGrapRing = true;     // Set the flag to grasp rings again
        }
    }
}

// Function to manually control the arm's position
void DriverClass::ArmSpin() {
    // If the Up button is pressed and the arm is within the allowed range
    if (Controller.ButtonY.pressing()) {
        Arm.spin(fwd, 12, volt);      // Move the arm forward at 12 volts
    }
    // If the Down button is pressed and the arm is within the allowed range
    else if (Controller.ButtonRight.pressing()) {
        Arm.spin(fwd, -12, volt);     // Move the arm backward at 12 volts
    }
    // If no button is pressed or the arm is outside the allowed range
    else {
        Arm.stop(hold);              // Stop the arm and apply the brake
    }
}