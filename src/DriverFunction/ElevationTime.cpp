#include "vex.h"
#include "robot-config.h"
#include "DriverFunction/DriverFunction.h"

using namespace vex;

void DriverClass::ElevationTime() {
    if (Elevation.value() == 95) {
        Controller.rumble("- - -");  // Trigger controller rumble with pattern "- - -"
    }

    if (Elevation.value() == 100) {
        Controller.rumble("- - -"); // Trigger controller rumble with pattern "- - -"
    }
}