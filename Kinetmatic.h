#include "Glb_Define.h"
class Kinematics {
  private:
    unsigned long CurrentTime = 0;
    float HalfRad = 180;
    float AngularGlb = 0;
    float AngularLeft = 0;
    float AngularRight = 0;
    float RX = 0;
    float RadWheel = 16;
    float RadCar = 44.7;

    void GetTime(){
      CurrentTime = millis() - Timer;
    }

    float LeftEncoderDiff() {
      return EncoderLeftCounting - EncoderLeftCountingPre;
    }
    
    float RightEncoderDiff() {
      return EncoderRightCounting - EncoderRightCountingPre;
    }

    float AngularSum() {
      return AngularLeft + AngularRight;
    }

    float AngularDiff() {
      return AngularRight - AngularLeft;
    }
  public:
    float EncoderLeftCounting, EncoderRightCounting, EncoderLeftCountingPre, EncoderRightCountingPre;
    unsigned long Frequency = 100;
    float X_GLB = 0;
    float Y_GLB = 0;
    float ThetaGlb = 0;
    float ThetaGlbAbs = 0;
    
    void GetAngular(){
        GetTime();
        if (CurrentTime >= Frequency){
            AngularLeft =  LeftEncoderDiff() * PI / HalfRad;
            AngularRight = RightEncoderDiff() * PI / HalfRad;
            
            RX = AngularSum() * RadWheel / 2;
            AngularGlb = AngularDiff() * RadWheel / 2 * RadCar;

            X_GLB = X_GLB + RX * cos(ThetaGlb);
            Y_GLB = Y_GLB + RX * sin(ThetaGlb);
            
            ThetaGlb = ThetaGlb + AngularGlb;
            ThetaGlbAbs = ThetaGlb - (int)(ThetaGlb / Pi * 2) * Pi * 2;

            EncoderLeftCountingPre = EncoderLeftCounting;
            EncoderRightCountingPre = EncoderRightCounting;
            Timer = millis();
        }
    }
};

