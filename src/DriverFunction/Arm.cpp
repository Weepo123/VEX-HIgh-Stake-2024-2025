// Include necessary header files for the VEX robotics system
#include "vex.h"
#include "robot-config.h"
#include "DriverFunction/DriverFunction.h"
#include "AutoFunction/PID.h"

// Global variables to control the arm's state
bool SetToGrapRing = true;  // Flag to indicate if the arm should move to grasp a ring
bool ResetHand = false;     // Flag to indicate if the arm should reset to its initial position

// Constants for arm positions (in degrees)
int GrapRingPosition = -65;  // Position for grasping rings
int ArmMaxPosition = 270;   // Maximum allowed position for the arm
int ArmMinPosition = 1;     // Minimum allowed position for the arm
double InitialArmPosition = Arm.position(degrees);

void DriverClass::ArmSpin() {
    // If the Up button is pressed and the arm is below the maximum position
    if (Controller.ButtonY.pressing()) {
        Arm.spin(fwd, 12, volt);  // Move the arm forward at 12 volts
    }
    // If the Down button is pressed and the arm is above the minimum position
    else if (Controller.ButtonRight.pressing()) {
        Arm.spin(fwd, -12, volt); // Move the arm backward at 12 volts
    }
    else if (Controller.ButtonDown.pressing()){
        // Initialize PID controller with tuned values
        PID RotationPID(1, 0.005, 0.15, 2.0, 3.0);
        timer Timer;
        Timer.reset();
        // Decide which position to move to based on the flags
        double TargetPosition = SetToGrapRing ? GrapRingPosition : ArmMinPosition;

        // Execute the PID loop until the arm reaches the target or timeout
        while (!(RotationPID.isSettled() && Timer.value() > 1)) {
            double TravelArmPosition = Arm.position(degrees);
            double CurrentArmPostion = TravelArmPosition - InitialArmPosition;
            double RotationError = TargetPosition - CurrentArmPostion;
            RotationPID.PIDCalculate(RotationError);
            double RotationVelocityRPM = fmin(600, fmax(-600, RotationPID.Value()));
            Arm.spin(fwd, RotationVelocityRPM, rpm);
            wait(10, msec);
        }
    } else {
        // Stop the arm and hold position
        Arm.stop(hold);
    }
}