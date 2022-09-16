
#include <AccelStepper.h>

// The X Stepper pins
#define ML_DIR_PIN 2
#define ML_STEP_PIN 3
// The Y stepper pins
#define MR_DIR_PIN 4
#define MR_STEP_PIN 5

// Define some steppers and the pins the will use
AccelStepper ML(AccelStepper::DRIVER, ML_STEP_PIN, ML_DIR_PIN);
AccelStepper MR(AccelStepper::DRIVER, MR_STEP_PIN, MR_DIR_PIN);
float cm(float x){
  return x*33.6842153;
  // 800 PAS 1 TOUR  20*800 PAS= 475CM  // 800PAS 23.75CM // 1CM 33.6842153PAS
}
void forward(int x){
   
    ML.move(cm(x));
    MR.move(cm(x));
     while(ML.run()){
          MR.run(); 
     }
}
void right(int x){
  x=0.134*x;            // 7.7*PI*x/180
    ML.move(cm(x));
    MR.move(-cm(x));
     while(ML.run()){
          MR.run(); 
     }
}
void ARCright(int x, int degre=90){ // RAYON , ANGLE 
  double  dL=degre*0.017454*(x+15.4);//*1030707; // (15.4 DIAMETRE+x)*degre*PI*/180
  double  dR=degre*0.017454*x;// degre*PI*x/180
  Serial.println(dL);
  MR.setAcceleration(17000.0);ML.setAcceleration(17000.0);
  MR.setMaxSpeed(1300.0);
  ML.setMaxSpeed(1208*dL/dR);
  ML.move(cm(dL));
  MR.move(cm(dR));
  while((MR.distanceToGo()!=0)&&(ML.distanceToGo()!=0)){
          MR.run(); ML.run();
     }
  ML.setMaxSpeed(2000.0);MR.setMaxSpeed(2000.0);
  ML.setAcceleration(2000.0);MR.setAcceleration(2000.0);
}
void setup()
{  
  Serial.begin(9600);
    ML.setMaxSpeed(2000.0);
    ML.setAcceleration(2000.0);
    ML.setCurrentPosition( 0 );

    MR.setMaxSpeed(2000.0);
    MR.setAcceleration(2000.0);
    MR.setCurrentPosition( 0 );

    delay(3000);
}

void loop() 
{


forward(50);
//    delay(5000);
//right(360*2);
//ARCright(50);
delay(2000);

  
//    if (MR.distanceToGo() == 0){  
//  MR.moveTo(-MR.currentPosition());
//
//    }

}
