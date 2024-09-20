#include "vex.h"
#include "robot-config.h"
#include "DriverFunction/Pneumatics.h"

bool clamp = true;
bool hang = true;
void GoalClamp(){
    if(clamp){
        Clamp.open();
        clamp = false;
    }
    else if(!clamp){
        Clamp.close();
        clamp = true;
    }
}

void HangRobot(){
    if(hang){
        Hang.open();
        hang = false;
    }
    else if(!hang){
        Hang.close();
        hang = true;
    }
}