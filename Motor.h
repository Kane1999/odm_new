// motor defination
# define L_PWM_PIN 10
# define L_DIR_PIN 16
# define R_PWM_PIN 9
# define R_DIR_PIN 15
# define FWD LOW
# define REV HIGH
# define INIT_LEFT_SPEED 20
# define INIT_RIGHT_SPEED 21

class Motor{
  public:
    void Init(){
      // Set all the motor pins as outputs
      pinMode(L_PWM_PIN,OUTPUT);
      pinMode(L_DIR_PIN,OUTPUT);
      pinMode(R_PWM_PIN,OUTPUT);
      pinMode(R_DIR_PIN,OUTPUT);
       // Set initial direction
      digitalWrite( L_DIR_PIN, FWD );
      digitalWrite( R_DIR_PIN, FWD );
      // Set initial power values for PWM
      digitalWrite( L_PWM_PIN, FWD );
      digitalWrite( R_PWM_PIN, FWD );
    }

    float execute(float error_value){
      // Set the direction of rotation for the left and right motor here
      digitalWrite(L_DIR_PIN, FWD);
      digitalWrite(R_DIR_PIN, FWD);
      // the volume of motor operation
      forward(error_value);
    }
    void forward(float error_value){
      analogWrite(L_PWM_PIN,INIT_LEFT_SPEED - error_value);           
      analogWrite(R_PWM_PIN, INIT_RIGHT_SPEED + error_value); 
    }
    void r_180_rotation(){
      digitalWrite(L_DIR_PIN, REV);
      digitalWrite(R_DIR_PIN, FWD);
      for(int pos = 0; pos < 37; pos += 1){ 
        analogWrite(L_PWM_PIN,pos);      
        analogWrite(R_PWM_PIN,pos);
        delay(50); 
      }
    }
};