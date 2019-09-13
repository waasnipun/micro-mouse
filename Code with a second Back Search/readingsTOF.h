#include <VL6180X.h>
#include <Wire.h>
VL6180X sensor1;
VL6180X sensor2;
VL6180X sensor3;

int leftTOF =A0;
int frontTOF = A1;
int rightTOF = A2;
int distancearray[3] ;

void init_TOF(){
    
  pinMode(frontTOF,OUTPUT);
  pinMode(leftTOF,OUTPUT);
  pinMode(rightTOF,OUTPUT);
  digitalWrite(frontTOF,LOW);
  digitalWrite(leftTOF,LOW);
  digitalWrite(rightTOF,LOW);
  delay(50);
  
  Serial.begin(9600);
  Wire.begin();
  
  digitalWrite(leftTOF, HIGH);
  delay(50);
  sensor1.init();
  sensor1.configureDefault();
  sensor1.setTimeout(500);
  sensor1.setAddress(0x54);
  

  digitalWrite(frontTOF, HIGH);
  delay(50);
  sensor2.init();
  sensor2.configureDefault();
  sensor2.setTimeout(500);
  sensor2.setAddress(0x56);

  digitalWrite(rightTOF, HIGH);
  delay(50);
  sensor3.init();
  sensor3.configureDefault();
  sensor3.setTimeout(500);
  sensor3.setAddress(0x55);

  sensor1.startRangeContinuous(40);// measure continuously for sensor 1
  sensor2.startRangeContinuous(40);// measure continuously for sensor 2 
  sensor3.startRangeContinuous(40);// measure continuously for sensor 2 
}


int16_t* readTOF(){
  distancearray[0] =sensor1.readRangeContinuousMillimeters();// get distance for sensor 1
  distancearray[1] =sensor2.readRangeContinuousMillimeters();// get distance for sensor 1
  distancearray[2] =sensor3.readRangeContinuousMillimeters();// get distance for sensor 1
/*
  Serial.pruint16_t("Sensor 1 Distnace : ");Serial.pruint16_t(distancearray[0]);
  Serial.pruint16_t(" Sensor 2 Distnace : ");Serial.pruint16_t(distancearray[1]);
  Serial.pruint16_t(" Sensor 3 Distnace : ");Serial.pruint16_tln(distancearray[2]);*/
  if (sensor1.timeoutOccurred()) { Serial.print(" TIMEOUT 1"); }
  if (sensor2.timeoutOccurred()) { Serial.print(" TIMEOUT 2"); }  
  if (sensor3.timeoutOccurred()) { Serial.print(" TIMEOUT 3"); }
    
}
int16_t leftTOFReading(){

  return distancearray[0];}

int16_t rightTOFReading(){
  
  return distancearray[2];}

int16_t frontTOFReading(){

  return distancearray[1];}
