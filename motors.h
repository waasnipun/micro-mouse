#include "readingsTOF.h"
#include "EncodersOur.h"

// Change these two numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability

int16_t backturn = 65;
int16_t leftTurn = 65;
int16_t rightTurn = 70;

int16_t q =7;

int16_t pwmR=10;
int16_t pwmL=9;
int16_t forwardL=13;
int16_t reverseL=12;
int16_t forwardR=7;
int16_t reverseR=8;
long leftPosition;
long rightPosition;
int16_t lSensor;
int16_t rSensor;
int16_t fsensor;
float P = 0.7;
float D = 2.45;
float I = 0.01;
float oldErrorP =0;
float totalError ;
int16_t offset = 5 ;
float baseSpeedL = 87 ;
float baseSpeedR = 85;

float fastbaseSpeedL = 120;
float  fastbaseSpeedR = 120;

float RMS ;
float LMS ;
int16_t scale = 1;

int16_t oldEncoderL,oldEncoderR;

void initmotors(){
  pinMode(pwmR,OUTPUT);
  pinMode(forwardR,OUTPUT);
  pinMode(reverseR,OUTPUT);
  pinMode(pwmL,OUTPUT);
  pinMode(forwardL,OUTPUT);
  pinMode(reverseL,OUTPUT);
}
void motors(float leftVal,float rightVal,int16_t angle){ // motor 1--- left motor motor 2--- right motor (angle=0- normal ,angle=1 highly left, 

  if (angle == 0){                                //angle=2 highly right, angle 3-stop
    analogWrite(pwmL,scale*leftVal);              //angle 4 right 90 
    analogWrite(pwmR,scale*rightVal);             // angle 5 left 90
    digitalWrite(forwardL,HIGH);
    digitalWrite(reverseL,LOW);
    digitalWrite(forwardR,HIGH);
    digitalWrite(reverseR,LOW);
  }
  else if (angle ==1){
    analogWrite(pwmL,scale*leftVal);
    analogWrite(pwmR,scale*rightVal);
    digitalWrite(forwardL,HIGH);
    digitalWrite(reverseL,HIGH);
    digitalWrite(forwardR,HIGH);
    digitalWrite(reverseR,LOW);
  }
  else if (angle ==2){
    analogWrite(pwmL,scale*leftVal);
    analogWrite(pwmR,scale*rightVal);
    digitalWrite(forwardL,HIGH);
    digitalWrite(reverseL,LOW);
    digitalWrite(forwardR,HIGH);
    digitalWrite(reverseR,HIGH);
  }
    else if (angle ==3){
    analogWrite(pwmL,scale*leftVal);
    analogWrite(pwmR,scale*rightVal);
    digitalWrite(forwardL,HIGH);
    digitalWrite(reverseL,HIGH);
    digitalWrite(forwardR,HIGH);
    digitalWrite(reverseR,HIGH);
  }
    else if (angle==4){
    analogWrite(pwmL,scale*leftVal);
    analogWrite(pwmR,scale*rightVal);
    digitalWrite(forwardL,HIGH);
    digitalWrite(reverseL,LOW);
    digitalWrite(forwardR,LOW);
    digitalWrite(reverseR,HIGH);
  }
    else if (angle==5){
    analogWrite(pwmL,scale*leftVal);
    analogWrite(pwmR,scale*rightVal);
    digitalWrite(forwardL,LOW);
    digitalWrite(reverseL,HIGH);
    digitalWrite(forwardR,HIGH);
    digitalWrite(reverseR,LOW);
  }
    else if (angle==6){
    analogWrite(pwmL,scale*leftVal);
    analogWrite(pwmR,scale*rightVal);
    digitalWrite(forwardL,LOW);
    digitalWrite(reverseL,HIGH);
    digitalWrite(forwardR,LOW);
    digitalWrite(reverseR,HIGH);
  }
}

void moveForward(int16_t forwardValue){
  while (true){
    readTOF();
    lSensor = leftTOFReading();
    rSensor = rightTOFReading();
    
    leftPosition = returnLeftEncoder();
    rightPosition = returnRightEncoder();
  
    //readingGyro = gyroReading();
  

    //Serial.print(leftPosition);Serial.print(" ");Serial.println(rightPosition);

    float errorP=0.5*(lSensor - rSensor);
    float errorD= errorP - oldErrorP;
    
    if(lSensor>100 && rSensor>100){
      errorP = 0 ;
      errorD = 0;
    }
    else if(lSensor>100){
      errorP = 0.5*(50-rSensor) ;
    //errorP = lSensor - 50 ;
      errorD = errorP - oldErrorP;
    }
    else if(rSensor>100){
      errorP = 0.5*( lSensor - 50 );
      //errorP = 50-rSensor ;
      errorD = errorP - oldErrorP;
    }
    /*
    if (leftPosition>250 && leftPosition<300 && rightPosition<-250 && rightPosition>-300){
      errorD = 0;
      errorP = 0;
      tone(4,1400);
      delay(50);
          noTone(4); 
    }*/
    
    float errorI =  errorI + errorP ;

    totalError = (P * errorP + D * errorD + I * errorI) ;
    
    oldErrorP = errorP ;

    LMS = baseSpeedL - totalError ;
    RMS = baseSpeedR + totalError ;
    //Serial.println(readingGyro);
    //Serial.print(lSensor);Serial.print(" ");Serial.println(rSensor);

    //gyro
    /*
    if(readingGyro<0){
          readingGyro = map(readingGyro , 0 , -180, 0, 86);
          if(readingGyro<6){readingGyro*=3;}
          LMS = baseSpeedL - totalError -readingGyro ;
          RMS = baseSpeedR + totalError +readingGyro;
      }
      else if(readingGyro>0){
          readingGyro = map(readingGyro , 0 , 180, 0, 80);
          if(readingGyro<6){readingGyro*=3;}
          LMS = baseSpeedL - totalError +readingGyro;
          RMS = baseSpeedR + totalError -readingGyro;
      }
    */
    if (RMS < 0) {
      RMS = map(RMS , 0 , -255, 0, 255);
      motors(LMS,RMS,4);
      Serial.print("fucked up");
    }
    else if (LMS < 0) {
      LMS = map(LMS , 0 , -255, 0, 255);
      motors(LMS,RMS,5);
    }
    else {
      motors(LMS,RMS,0);
    }
    fsensor = frontTOFReading();
    //Serial.print(rightPosition);Serial.println(leftPosition);
    if(fsensor<70||(rightPosition>forwardValue && leftPosition>forwardValue)){
      //Serial.print("adfsfdgsdgfsfsfdd  "); Serial.println(fsensor);
      //Serial.print("encoder encoder  "); Serial.print(leftPosition); Serial.println(rightPosition);
      //motors(100,100,3);
      //delay(1000);
      tone(4,1000);
      delay(40);
      noTone(4);
      oldEncoderL = leftPosition;
      oldEncoderR = rightPosition;  
      encodersZero();
      break;
    }
  }
 //delay(50); 
}

void moveLeft(int16_t leftValue, int16_t frontValue){
  //encodersZero();
  motors(240,240,3);
  delay(150);
  readTOF();
  int16_t k = frontTOFReading();
  //Serial.print("right right  "); Serial.println(k);
  while(true){
    readTOF();
    k = frontTOFReading();
    Serial.print( "k:");
    Serial.println(k);
    if (k<30){
    motors(60,60,6);
    delay(5);   
  }
  else if (k>40 && k<120){
    motors(60,60,0);
    delay(5);
  }
  else{
   // motors(240,240,3);
    break;
  }

  }
  
  /*if (k<30){
    motors(60,60,6);
    delay(q*(50-k));   
  }
  else if (k>50 && k<150){
    motors(60,60,0);
    delay(k*5);
  }*/
  /*if(oldEncoderL<oldEncoderR){
    motors(60,60,4);
    delay(5*(oldEncoderR-oldEncoderL));
  }
  else if (oldEncoderL>oldEncoderR){
    motors(60,60,5);
    delay(5*(oldEncoderL-oldEncoderR));
  }*/
  encodersZero();
  motors(200,200,3);
  delay(250);

  //correctError();
  while(true){
    motors(leftTurn,leftTurn,5);
    delay(50);
    leftPosition = returnLeftEncoder();
    rightPosition = returnRightEncoder();
   // Serial.print(leftPosition);Serial.print(" ");Serial.println(rightPosition);
    if(rightPosition>leftValue && leftPosition>leftValue){
      //Serial.print(" leftPosition  "); Serial.print(leftPosition); Serial.print("rightPosition "); Serial.println(rightPosition);
        tone(4,1000);
        motors(200,200,3);
        delay(300);
        /*while (abs(leftPosition-rightPosition)>10){
          if (leftPosition<rightPosition){
            motors(50,50,4);
            delay(30);
          }
          else if (leftPosition>rightPosition){
            motors(50,50,5);
            delay(30);
          }leftPosition = returnLeftEncoder();
          rightPosition = returnRightEncoder();
        }*/
        noTone(4);     // Stop sound...
        encodersZero();
        moveForward(frontValue);
        break;
    }
  }

}

void moveRight(int16_t rightValue,int16_t frontValue){
  encodersZero();
  motors(200,200,3);
  delay(300);
  readTOF();
  int16_t k = frontTOFReading();
 //Serial.print("right right  ");Serial.println(k);
  while(true){
    readTOF();
    k = frontTOFReading();
    Serial.print( "k:");
    Serial.println(k);
    if (k<30){
    motors(60,60,6);
    delay(5);   
  }
  else if (k>40 && k<120){
    motors(60,60,0);
    delay(5);
  }
  else{
    //motors(240,240,3);
    //delay(100);
    break;
  }

  }
  /*if(oldEncoderL<oldEncoderR){
    motors(60,60,4);
    delay(5*(oldEncoderR-oldEncoderL));
  }
  else if (oldEncoderL>oldEncoderR){
    motors(60,60,5);
    delay(5*(oldEncoderL-oldEncoderR));
  }*/
  encodersZero();
  motors(200,200,3);
  delay(250);
  //correctError();
  while(true){
    motors(rightTurn,rightTurn,4);
    delay(50);
    leftPosition = returnLeftEncoder();
    rightPosition = returnRightEncoder();
    if(rightPosition>rightValue && leftPosition>rightValue){
      //Serial.print(" leftPosition  "); Serial.print(leftPosition); Serial.print("rightPosition "); Serial.println(rightPosition);
      tone(4,1000);
      motors(200,200,3);
      delay(300);
      /*while (abs(leftPosition-rightPosition)>10){
          if (leftPosition<rightPosition){
            motors(50,50,4);
            delay(30);
          }
          else if (leftPosition>rightPosition){
            motors(50,50,5);
            delay(30);
          }
          leftPosition = returnLeftEncoder();
          rightPosition = returnRightEncoder();
        }*/
      noTone(4);
      encodersZero();
      moveForward(frontValue);
      break;
    }
  }
}
void turn180(int16_t reverseValue){
  Serial.print("truen 180");
  //motors(240,240,3);
  //delay(250);
  for(int16_t l=0;l<2;l++){
  encodersZero();
  motors(200,200,3);
  delay(300);
  readTOF();
  int16_t k = frontTOFReading();
 //Serial.print("right right  ");Serial.println(k);
 
/*
 if (k<30){
    motors(60,60,6);
    delay(q/2*(50-k));   
  }
  else if (k>50 && k<100){
    motors(60,60,0);
    delay(k*5);
  }*/
  while(true){
    readTOF();
    k = frontTOFReading();
    Serial.print( "k:");
    Serial.println(k);
    if (k<30){
    motors(60,60,6);
    delay(5);   
  }
  else if (k>40 && k<120){
    motors(60,60,0);
    delay(5);
  }
  else{
    motors(240,240,3);
    delay(100);
    break;
  }

  }
  /*if(oldEncoderL<oldEncoderR){
    motors(60,60,4);
    delay(5*(oldEncoderR-oldEncoderL));
  }
  else if (oldEncoderL>oldEncoderR){
    motors(60,60,5);
    delay(5*(oldEncoderL-oldEncoderR));
  }*/
  encodersZero();
  motors(200,200,3);
  delay(250);
 
  //correctError();
  while(true){
    motors(rightTurn,rightTurn,4);
    delay(50);
    leftPosition = returnLeftEncoder();
    rightPosition = returnRightEncoder();
    if(rightPosition>reverseValue  && leftPosition>reverseValue ){
      //Serial.print(" leftPosition  "); Serial.print(leftPosition); Serial.print("rightPosition "); Serial.println(rightPosition);
      tone(4,1000);
      motors(200,200,3);
      delay(250);
      /*while (abs(leftPosition-rightPosition)>10){
          if (leftPosition<rightPosition){
            motors(50,50,4);
            delay(30);
          }
          else if (leftPosition>rightPosition){
            motors(50,50,5);
            delay(30);
          }
          leftPosition = returnLeftEncoder();
          rightPosition = returnRightEncoder();
        }*/
      noTone(4);
      encodersZero();
      break;
    }
  }
  if(l==1){
    motors(60,60,6);
    delay(80);
    motors(200,200,3);
    delay(100);
  }
  }
}


void moveRightFast(int16_t rightValue,int16_t frontValue){
  encodersZero();
  motors(200,200,3);
  delay(200);
  readTOF();
  int16_t k = frontTOFReading();
 //Serial.print("right right  ");Serial.println(k);
  while(true){
    readTOF();
    k = frontTOFReading();
    Serial.print( "k:");
    Serial.println(k);
    if (k<30){
    motors(60,60,6);
    delay(5);   
  }
  else if (k>40 && k<120){
    motors(60,60,0);
    delay(5);
  }
  else{
    //motors(240,240,3);
    //delay(100);
    break;
  }

  }
  /*if(oldEncoderL<oldEncoderR){
    motors(60,60,4);
    delay(5*(oldEncoderR-oldEncoderL));
  }
  else if (oldEncoderL>oldEncoderR){
    motors(60,60,5);
    delay(5*(oldEncoderL-oldEncoderR));
  }*/
  encodersZero();
  motors(200,200,3);
  delay(200);
  //correctError();
  while(true){
    motors(rightTurn+35,rightTurn+35,4);
    delay(50);
    leftPosition = returnLeftEncoder();
    rightPosition = returnRightEncoder();
    if(rightPosition>rightValue-5 && leftPosition>rightValue-5){
      //Serial.print(" leftPosition  "); Serial.print(leftPosition); Serial.print("rightPosition "); Serial.println(rightPosition);
      tone(4,1000);
      motors(200,200,3);
      delay(200);
      /*while (abs(leftPosition-rightPosition)>10){
          if (leftPosition<rightPosition){
            motors(50,50,4);
            delay(30);
          }
          else if (leftPosition>rightPosition){
            motors(50,50,5);
            delay(30);
          }
          leftPosition = returnLeftEncoder();
          rightPosition = returnRightEncoder();
        }*/
      noTone(4);
      encodersZero();
      moveForward(frontValue);
      break;
    }
  }
}
void moveLeftFast(int16_t leftValue, int16_t frontValue){
  //encodersZero();
  motors(240,240,3);
  delay(200);
  readTOF();
  int16_t k = frontTOFReading();
  //Serial.print("right right  "); Serial.println(k);
  while(true){
    readTOF();
    k = frontTOFReading();
    Serial.print( "k:");
    Serial.println(k);
    if (k<30){
    motors(60,60,6);
    delay(5);   
  }
  else if (k>40 && k<120){
    motors(60,60,0);
    delay(5);
  }
  else{
    //motors(240,240,3);
    //delay(100);
    break;
  }

  }
  
  /*if (k<30){
    motors(60,60,6);
    delay(q*(50-k));   
  }
  else if (k>50 && k<150){
    motors(60,60,0);
    delay(k*5);
  }*/
  /*if(oldEncoderL<oldEncoderR){
    motors(60,60,4);
    delay(5*(oldEncoderR-oldEncoderL));
  }
  else if (oldEncoderL>oldEncoderR){
    motors(60,60,5);
    delay(5*(oldEncoderL-oldEncoderR));
  }*/
  encodersZero();
  motors(200,200,3);
  delay(200);

  //correctError();
  while(true){
    motors(leftTurn+35,leftTurn+35,5);
    delay(50);
    leftPosition = returnLeftEncoder();
    rightPosition = returnRightEncoder();
   // Serial.print(leftPosition);Serial.print(" ");Serial.println(rightPosition);
    if(rightPosition>leftValue-5 && leftPosition>leftValue-5){
      //Serial.print(" leftPosition  "); Serial.print(leftPosition); Serial.print("rightPosition "); Serial.println(rightPosition);
        tone(4,1000);
        motors(200,200,3);
        delay(200);
        /*while (abs(leftPosition-rightPosition)>10){
          if (leftPosition<rightPosition){
            motors(50,50,4);
            delay(30);
          }
          else if (leftPosition>rightPosition){
            motors(50,50,5);
            delay(30);
          }leftPosition = returnLeftEncoder();
          rightPosition = returnRightEncoder();
        }*/
        noTone(4);     // Stop sound...
        encodersZero();
        moveForward(frontValue);
        break;
    }
  }

}

void moveForwardFast(int16_t forwardValue){
  while (true){
    readTOF();
    lSensor = leftTOFReading();
    rSensor = rightTOFReading();
    
    leftPosition = returnLeftEncoder();
    rightPosition = returnRightEncoder();
  
    //readingGyro = gyroReading();
  

    //Serial.print(leftPosition);Serial.print(" ");Serial.println(rightPosition);

    float errorP=0.5*(lSensor - rSensor);
    float errorD= errorP - oldErrorP;
    
    if(lSensor>100 && rSensor>100){
      errorP = 0 ;
      errorD = 0;
    }
    else if(lSensor>100){
      errorP = 0.5*(50-rSensor) ;
    //errorP = lSensor - 50 ;
      errorD = errorP - oldErrorP;
    }
    else if(rSensor>100){
      errorP = 0.5*( lSensor - 50 );
      //errorP = 50-rSensor ;
      errorD = errorP - oldErrorP;
    }
    /*
    if (leftPosition>250 && leftPosition<300 && rightPosition<-250 && rightPosition>-300){
      errorD = 0;
      errorP = 0;
      tone(4,1400);
      delay(50);
          noTone(4); 
    }*/
    
    float errorI =  errorI + errorP ;

    totalError = (P * errorP + D * errorD + I * errorI) ;
    
    oldErrorP = errorP ;

    LMS = fastbaseSpeedL - totalError ;
    RMS = fastbaseSpeedR + totalError ;
    //Serial.println(readingGyro);
    //Serial.print(lSensor);Serial.print(" ");Serial.println(rSensor);

    //gyro
    /*
    if(readingGyro<0){
          readingGyro = map(readingGyro , 0 , -180, 0, 86);
          if(readingGyro<6){readingGyro*=3;}
          LMS = baseSpeedL - totalError -readingGyro ;
          RMS = baseSpeedR + totalError +readingGyro;
      }
      else if(readingGyro>0){
          readingGyro = map(readingGyro , 0 , 180, 0, 80);
          if(readingGyro<6){readingGyro*=3;}
          LMS = baseSpeedL - totalError +readingGyro;
          RMS = baseSpeedR + totalError -readingGyro;
      }
    */
    if (RMS < 0) {
      RMS = map(RMS , 0 , -255, 0, 255);
      motors(LMS,RMS,4);
      Serial.print("fucked up");
    }
    else if (LMS < 0) {
      LMS = map(LMS , 0 , -255, 0, 255);
      motors(LMS,RMS,5);
    }
    else {
      motors(LMS,RMS,0);
    }
    fsensor = frontTOFReading();
    //Serial.print(rightPosition);Serial.println(leftPosition);
    if(fsensor<70||(rightPosition>forwardValue-10 && leftPosition>forwardValue-10)){
      //Serial.print("adfsfdgsdgfsfsfdd  "); Serial.println(fsensor);
      //Serial.print("encoder encoder  "); Serial.print(leftPosition); Serial.println(rightPosition);
      //motors(100,100,3);
      //delay(1000);
      tone(4,1000);
      delay(40);
      noTone(4);
      oldEncoderL = leftPosition;
      oldEncoderR = rightPosition;  
      encodersZero();
      break;
    }
  }
 //delay(50); 
}
