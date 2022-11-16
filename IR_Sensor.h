// color-detector defination
# define LS_LEFT_PIN  A0
# define LS_CENTRE_PIN A2
# define LS_RIGHT_PIN A3
# define MOST_LEFT_PWM_PIN A11
# define MOST_RIGHT_PWM_PIN A4
# define EMIT 11
# define MAX_SENSOR 5 // nums of sensors

// Global Variable
int Ls_Pin[MAX_SENSOR] = {LS_LEFT_PIN, LS_CENTRE_PIN, LS_RIGHT_PIN, MOST_LEFT_PWM_PIN, MOST_RIGHT_PWM_PIN};

class IR_Sensor{
  private:
    unsigned long start_time;
    float error_value;
    float turn_pwm;  
  public:
    unsigned long current_read[ MAX_SENSOR ];
    unsigned long previous_read[ MAX_SENSOR ];
    void Init(){
      start_time = millis();
      pinMode(EMIT,OUTPUT);
      pinMode(Ls_Pin[0],INPUT);
      pinMode(Ls_Pin[1],INPUT);
      pinMode(Ls_Pin[2],INPUT);
      pinMode(Ls_Pin[3],INPUT);
      pinMode(Ls_Pin[4],INPUT);
      digitalWrite(EMIT,HIGH);
      //init sensor data
      current_read[0]=0;
      current_read[1]=0;
      current_read[2]=0;
      current_read[3]=0;
      current_read[4]=0;
      previous_read[0]=0;
      previous_read[1]=0;
      previous_read[2]=0;
      previous_read[3]=0;
      previous_read[4]=0;
      error_value = 0;
      turn_pwm = 0;
    }
    float execute(){
      pinMode( Ls_Pin[0], OUTPUT );
      digitalWrite( Ls_Pin[0], HIGH );
      pinMode( Ls_Pin[1], OUTPUT );
      digitalWrite( Ls_Pin[1], HIGH );
      pinMode( Ls_Pin[2], OUTPUT );
      digitalWrite( Ls_Pin[2], HIGH );
      pinMode( Ls_Pin[3], OUTPUT );
      digitalWrite( Ls_Pin[3], HIGH );
      pinMode( Ls_Pin[4], OUTPUT );
      digitalWrite( Ls_Pin[4], HIGH );
      // Tiny delay for capacitor to charge.
      delayMicroseconds(10);
      //  Turn input pin back to an input
      pinMode( Ls_Pin[0], INPUT );
      pinMode( Ls_Pin[1], INPUT );
      pinMode( Ls_Pin[2], INPUT );
      pinMode( Ls_Pin[3], INPUT );
      pinMode( Ls_Pin[4], INPUT );
      // ReadLineSensor();
      Read_5_Sensor(MAX_SENSOR);
      error_value = Get_Line_Error();
      Data_Alignment();
      turn_pwm = 5;
      turn_pwm = turn_pwm * error_value;

      return turn_pwm;
    }
    // Read 5 IR sensor reading 
    void Read_5_Sensor(const int sensor_num) {
          unsigned long start_time;  
          unsigned long current_time;
          unsigned long elapsed_time;
          unsigned long timeout = 5000;
          //Begin measurement of time in microseconds.
          int remaining = sensor_num;
          start_time=micros();
          while(remaining > 0){   
            for(int i =0; i < sensor_num; i++){
              current_time = micros();
              elapsed_time = current_time - start_time; 
              if( digitalRead( Ls_Pin[i] ) == LOW ){
              // Check to see if it is the same as the initialization value.
                if(current_read[i]== previous_read[i]){     
                  current_read[i] = elapsed_time;
                  remaining = remaining - 1;
                }
              }
            }
          }
          Serial.print("Left line sensor: " );
          Serial.print( current_read[0] );
          Serial.print("\n");
          Serial.print("Center line sensor: " );
          Serial.print( current_read[1] );
          Serial.print("\n");
          Serial.print("Right line sensor: " );
          Serial.print( current_read[2] );
          Serial.print("\n");
          Serial.print("Most Left line sensor: " );
          Serial.print( current_read[3] );  
          Serial.print("\n");
          Serial.print("Most Right line sensor: " );
          Serial.print( current_read[4] );  
          Serial.print("\n");
          delay(100);
      }
      // Single P-control.
      float Get_Line_Error(){
        float e_line;
        float w_left;
        float w_right;

        w_left = (static_cast<float>(current_read[0])-600)/(2400-650) + ((static_cast<float>(current_read[1])-600)/(2400-650))*0.5;
        w_right = (static_cast<float>(current_read[2])-600)/(2400-650)+ ((static_cast<float>(current_read[1])-600)/(2400-650))*0.5;
        e_line = w_left - w_right;

        return e_line;
      }
      // Align the sensor readings at the current moment with the previous moment.
      void Data_Alignment(){
        for (int i =0;i< MAX_SENSOR;i++){
          previous_read[i]=current_read[i];
        }
      }
};