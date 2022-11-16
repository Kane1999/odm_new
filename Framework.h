#include "Motor.h"
#include "IR_Sensor.h"

Motor motor;
IR_Sensor ir_sensor;

class Framework{
  private:
    float error;
  public:
    void Init(){
      error = 0;
      motor.Init();
      ir_sensor.Init();
    }
    void execute(){
      error = ir_sensor.execute();
      delay(10);
      motor.execute(error);
    }
};