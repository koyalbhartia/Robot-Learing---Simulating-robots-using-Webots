#include <webots/DistanceSensor.hpp>
#include <webots/Motor.hpp>
#include <webots/Robot.hpp>
#define TIME_STEP 64

using namespace webots;
using namespace std;

int main(int argc, char **argv) {
  Robot *robot = new Robot();
  DistanceSensor *ds[2];
  char dsNames[2][10] = {"ds_right", "ds_left"};
  for (int i = 0; i < 2; i++) {
    ds[i] = robot->getDistanceSensor(dsNames[i]);
    ds[i]->enable(TIME_STEP);
  }
  Motor *wheels[4];
  char wheels_names[4][8] = {"wheel1", "wheel2", "wheel3", "wheel4"};
  for (int i = 0; i < 4; i++) {
    wheels[i] = robot->getMotor(wheels_names[i]);
    wheels[i]->setPosition(INFINITY);
    wheels[i]->setVelocity(0.0);
  }
  int avoidObstacleCounter = 0;
  while (robot->step(TIME_STEP) != -1) {
    double leftSpeed = 1.0;
    double rightSpeed = 1.0;
    if (avoidObstacleCounter > 0) {
      avoidObstacleCounter--;
      leftSpeed = 1.0;
      rightSpeed = -1.0;
    } else { // read sensors
      for (int i = 0; i < 2; i++) {
        if (ds[i]->getValue() < 950.0)
          avoidObstacleCounter = 100;
      }
    }
    wheels[0]->setVelocity(leftSpeed);
    wheels[1]->setVelocity(rightSpeed);
    wheels[2]->setVelocity(leftSpeed);
    wheels[3]->setVelocity(rightSpeed);
    // cout<<"Speed of left wheel"<<leftSpeed<<endl;
    // cout<<"Speed of right wheel"<<rightSpeed<<endl;
    if(leftSpeed==1)
    {if(rightSpeed==1)
      cout<<"Robot Moving Forward"<<endl;
      else if (rightSpeed==-1)
      cout<<"Robot Moving Right"<<endl;
    }
    else if(leftSpeed==-1)
    {if(rightSpeed==1)
      cout<<"Robot Moving Left"<<endl;
      else if (rightSpeed==-1)
      cout<<"Robot Moving Backward"<<endl;
    }    
  }
  delete robot;
  return 0;  // EXIT_SUCCESS
}