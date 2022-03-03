#include <P1AM.h>

int inputCounts = 0;
float inputVolts = 0;


int platformForwardCounts = 0;
int platformBackCounts = 0;
float platformForward = 0;
float platformBack = 0;

int lowerFrontCounts = 0;
int raiseFrontCounts = 0;
int lowerBackCounts = 0;
int raiseBackCounts = 0;

float lowerFront = 0;
float raiseFront = 0;
float lowerBack = 0;
float raiseBack = 0;

int raiseSampleCounts = 0;
int lowerSampleCounts = 0;
float raiseSample = 0;
float lowerSample = 0;

unsigned long sampleActuatorsTime = 0;


const int n = 50; //Amount of times to staple
int stapleCount = 0; //Staple Count
const int sampleDownTime = 7000; //Time samples will be up
const int sampleUpTime = 1000; //Time samples will be down
int sampleDownTimePrevious = 0;
int sampleUpTimePrevious = 1000;
int platformMoveTimePrevious = 0;
const int platformMoveTime = 100;
const int retractTime = n*platformMoveTime;
int platformState =LOW;
int triggersState=LOW;  

int count = 0;


const int triggersTime = 7000;
int triggersTimePrevious = 0;


int sampleState = HIGH;


void setup() {
  // put you\r setup code here, to run once:
  
 Serial.begin(115200);  //initialize serial communication at 115200 bits per second 
  while (!P1.init()){ 
    ; //Wait for Modules to Sign on   
  }
      
    P1.writeDiscrete(HIGH,1,1);
    P1.writeDiscrete(HIGH,1,2);
    P1.writeDiscrete(HIGH,1,5);
    P1.writeDiscrete(HIGH,1,6);    
    P1.writeDiscrete(LOW,1,3);
    P1.writeDiscrete(LOW,1,4);
    P1.writeDiscrete(LOW,1,7);
    P1.writeDiscrete(LOW,1,8);
    delay(2000);
    P1.writeDiscrete(LOW,1,1);
    P1.writeDiscrete(LOW,1,2);
    P1.writeDiscrete(LOW,1,5);
    P1.writeDiscrete(LOW,1,6);    
    P1.writeDiscrete(LOW,1,3);
    P1.writeDiscrete(LOW,1,4);
    P1.writeDiscrete(LOW,1,7);
    P1.writeDiscrete(LOW,1,8);
    sampleState = HIGH;    
}

int frontTopSensor = 0;
int frontBottomSensor = 0;
int backTopSensor = 0;
int backBottomSensor = 0;

void loop() {
  // put your main code here, to run repeatedly:
  inputCounts = P1.readAnalog(7,6);
  inputVolts = 10 * ((float)inputCounts/8191);
  //Serial.println(inputVolts);

  unsigned long currentMillis = millis();
  frontBottomSensor = P1.readDiscrete(8,1);
  frontTopSensor = P1.readDiscrete(8,2);
  backTopSensor = P1.readDiscrete(8,3);
  backBottomSensor = P1.readDiscrete(8,4);
    
  if(inputVolts >=2){
    //AUTOMODE
    if(frontBottomSensor == 1){
      P1.writeDiscrete(LOW,2,2);
      P1.writeDiscrete(LOW,2,4);
      P1.writeDiscrete(HIGH,2,1);
      P1.writeDiscrete(HIGH,2,3);

      P1.writeDiscrete(HIGH,2,5);
      P1.writeDiscrete(HIGH,2,7);
    }
    else if (frontTopSensor == 1){
      P1.writeDiscrete(LOW,2,1);
      P1.writeDiscrete(LOW,2,3);
      P1.writeDiscrete(HIGH,2,2);
      P1.writeDiscrete(HIGH,2,4);

      P1.writeDiscrete(HIGH,2,6);
      P1.writeDiscrete(HIGH,2,8); 
           
      //RaiseSamples
      P1.writeDiscrete(HIGH,1,1);
      P1.writeDiscrete(HIGH,1,3);
      P1.writeDiscrete(HIGH,1,5);
      P1.writeDiscrete(HIGH,1,7);

      //MovePlatform Back
      P1.writeDiscrete(HIGH,3,2);
      
      delay(1000);

      //Stop Platform
      P1.writeDiscrete(LOW,3,2);

      //MOVE PLATFORM BACK
      P1.writeDiscrete(LOW,3,2);

      //LOWERSAMPLES
      P1.writeDiscrete(LOW,1,1);
      P1.writeDiscrete(LOW,1,3);
      P1.writeDiscrete(LOW,1,5);
      P1.writeDiscrete(LOW,1,7);  
      P1.writeDiscrete(HIGH,1,2);
      P1.writeDiscrete(HIGH,1,4);
      P1.writeDiscrete(HIGH,1,6);
      P1.writeDiscrete(HIGH,1,8);
      delay(500);
      P1.writeDiscrete(LOW,1,2);
      P1.writeDiscrete(LOW,1,4);
      P1.writeDiscrete(LOW,1,6);
      P1.writeDiscrete(LOW,1,8);     
    }

    if ( backBottomSensor == 1 && frontBottomSensor == 0){
      P1.writeDiscrete(LOW,2,6);
      P1.writeDiscrete(LOW,2,8);
    }

    else if (backTopSensor == 1 && frontTopSensor == 0){
      P1.writeDiscrete(LOW,2,5);
      P1.writeDiscrete(LOW,2,7); 
    }
  }


  else{
    //MANUAL MODE
  //READ SENSORS


    
  //Serial.println("In Manual Mode");

  //READING PLATFORM
  platformForwardCounts = P1.readAnalog(7,3);
  platformForward = 10 * ((float)platformForwardCounts/8191);
  //Serial.println(platformForward);

  platformBackCounts = P1.readAnalog(7,4);
  platformBack = 10 * ((float)platformBackCounts/8191);
  //Serial.println(platformBack);


  //READING FRONT ACTUARORS
  lowerFrontCounts = P1.readAnalog(6,8);
  lowerFront = 10 * ((float)lowerFrontCounts/8191);
  raiseFrontCounts = P1.readAnalog(6,5);
  raiseFront = 10 * ((float)raiseFrontCounts/8191);


  //READING BACK ACTUATAORS
  lowerBackCounts = P1.readAnalog(7,1);
  lowerBack = 10 * ((float)lowerBackCounts/8191);
  raiseBackCounts = P1.readAnalog(6,6);
  raiseBack = 10 * ((float)raiseBackCounts/8191);

  //READING SAMPLE ACTUATAORS
  raiseSampleCounts = P1.readAnalog(6,7);
  raiseSample = 10 * ((float)raiseSampleCounts/8191);
  //Serial.println(raiseSample);
  lowerSampleCounts = P1.readAnalog(7,2);
  lowerSample = 10 * ((float)lowerSampleCounts/8191);
  //Serial.println(lowerSample);

    //PLATFORM CONTROL
    if (platformForward>=2){
      P1.writeDiscrete(HIGH,3,1);
    }
    else{
      P1.writeDiscrete(LOW,3,1);
    }
    if(platformBack>=2){
      //MOVE PLATFORM BACK
      P1.writeDiscrete(HIGH,3,2);
    }
    else{
      P1.writeDiscrete(LOW,3,2);
    }


    //FRONT CONTROL
    if (raiseFront>=2 && frontTopSensor == 0){
      P1.writeDiscrete(HIGH,2,1);
      P1.writeDiscrete(HIGH,2,3);
    }
    else{
      P1.writeDiscrete(LOW,2,1);
      P1.writeDiscrete(LOW,2,3);
    }
    if(lowerFront>=2 && frontBottomSensor == 0){
      P1.writeDiscrete(HIGH,2,2);
      P1.writeDiscrete(HIGH,2,4);    
      }
    else{
      P1.writeDiscrete(LOW,2,2);
      P1.writeDiscrete(LOW,2,4);      
      }


    // BACK CONTROL
    if (raiseBack>=2 && backTopSensor == 0 ){
      P1.writeDiscrete(HIGH,2,5);
      P1.writeDiscrete(HIGH,2,7);      
      }
    else{
      P1.writeDiscrete(LOW,2,5);
      P1.writeDiscrete(LOW,2,7);      
      }
    if(lowerBack>=2 && backBottomSensor ==0){
      //MOVE PLATFORM BACK
      P1.writeDiscrete(HIGH,2,6);
      P1.writeDiscrete(HIGH,2,8);      
      }
    else{
      P1.writeDiscrete(LOW,2,6);
      P1.writeDiscrete(LOW,2,8);
      }


      //SAMPLE CONTROL
    if (raiseSample>=2){
      P1.writeDiscrete(HIGH,1,1);
      P1.writeDiscrete(HIGH,1,3);
      P1.writeDiscrete(HIGH,1,5);
      P1.writeDiscrete(HIGH,1,7);      
      }
    else{
      P1.writeDiscrete(LOW,1,1);
      P1.writeDiscrete(LOW,1,3);
      P1.writeDiscrete(LOW,1,5);
      P1.writeDiscrete(LOW,1,7);  
      }
    if(lowerSample>=2){
      //MOVE PLATFORM BACK
      P1.writeDiscrete(HIGH,1,2);
      P1.writeDiscrete(HIGH,1,4);
      P1.writeDiscrete(HIGH,1,6);
      P1.writeDiscrete(HIGH,1,8);     
      }
    else{
      P1.writeDiscrete(LOW,1,2);
      P1.writeDiscrete(LOW,1,4);
      P1.writeDiscrete(LOW,1,6);
      P1.writeDiscrete(LOW,1,8);  
      }
    }
}
