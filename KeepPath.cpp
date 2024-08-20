#include "HardwareSerial.h"
class KeepPath {
  public:
    int rightForward, rightBack, leftForward, leftBack;

    void setVel(int leftForward, int leftBack, int rightForward, int rightBack) {
      this->leftForward = leftForward;
      this->leftBack = leftBack;
      this->rightForward = rightForward;
      this->rightBack = rightBack;
    }

    void updateSensor(int sensor1, int sensor2) {
       if (sensor1 - sensor2 < -100) { 
        this->setVel(0, 0, 0, 255);
      } else if (sensor1 - sensor2 > 100) {
        this->setVel(0, 255, 0, 0);
      } else { 
        this->setVel(0, 255, 0, 255);
      }
    }
};