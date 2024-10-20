#include "vex.h"
#include "robot-config.h"
#include "AutoFunction/movement.h"

#include <iostream>
#include <thread>

using namespace vex;

void Autonomous(){
    AutoClass Auto;
    Auto.MoveTurnTileWithPID(2, Inertial.rotation(), 600.0, 600.0, 0.0, 3.0);
    Auto.Turn(360.0, 600.0, 0.0);
}