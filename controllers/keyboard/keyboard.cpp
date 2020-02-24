#include <webots/DistanceSensor.hpp>
#include <webots/Motor.hpp>
#include <webots/Robot.hpp>
#include <webots/Keyboard.hpp>


#define TIME_STEP 64
using namespace webots;
using namespace std;

int main(int argc, char **argv) {
  Robot *robot = new Robot();
  Keyboard kb;
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
  kb.enable(TIME_STEP);
  double leftSpeed = 0.0;
  double rightSpeed = 0.0;
  
  while (robot->step(TIME_STEP) != -1) {
    int key=kb.getKey();
    
    if (key==315){
    leftSpeed = 1.0;
    rightSpeed = 1.0;
    cout<<"Keyboard press - Up arrow(Forward)"<<endl;
    cout<<"Left motor speed: 10m/s"<<endl;
    cout<<"Right motor speed: 10m/s"<<endl;
    } else if (key==317){
    leftSpeed = -1.0;
    rightSpeed = -1.0;
    cout<<"Keyboard press - Down arrow(Backward)"<<endl;
    cout<<"Left motor speed: -10m/s"<<endl;
    cout<<"Right motor speed: -10m/s"<<endl;
    }else if (key==316){
    leftSpeed = 1.0;
    rightSpeed = -1.0;
    cout<<"Keyboard press - Right arrow(Right)"<<endl;
    cout<<"Left motor speed: 10m/s"<<endl;
    cout<<"Right motor speed: -10m/s"<<endl;
    }else if (key==314){
    leftSpeed = -1.0;
    rightSpeed = 1.0;
    cout<<"Keyboard press - Left arrow(Left)"<<endl;
    cout<<"Left motor speed: -10m/s"<<endl;
    cout<<"Right motor speed: 10m/s"<<endl;
    }else {
    leftSpeed = 0.0;
    rightSpeed = 0.0;
    cout<<"No Keyboard press - (Stationary)"<<endl;
    cout<<"Left motor speed: 0m/s"<<endl;
    cout<<"Right motor speed: 0m/s"<<endl;
    }
    std::cout<<"Obstacle Distance from sensor:"<<endl;
    std::cout<<"Right Sensor: "<<ds[0]->getValue()/100 << " cm"<<std::endl;
    std::cout<<"Left Sensor: "<<ds[1]->getValue()/100 << " cm"<<std::endl;
    // std::cout<<ds[1]->getValue()<<"=Left Sensor"<<std::endl;
    wheels[0]->setVelocity(leftSpeed);
    wheels[1]->setVelocity(rightSpeed);
    wheels[2]->setVelocity(leftSpeed);
    wheels[3]->setVelocity(rightSpeed);
    
  }
  delete robot;
  return 0;  // EXIT_SUCCESS
}
