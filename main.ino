//#include "maze1.h"
#include "motors.h"
int16_t pushcount = 0;


int16_t** arena_1;

int16_t* returnxyDir;
void setup(){

  Serial.begin(9600);
  Wire.begin();
  delay(1000);
  arena_1 = maze(1);
  //updateScreen(arena,14);
  init_TOF();
  initEncoders();
  initmotors();
  pinMode(A3,INPUT);
  buzzer(1);
  digitalWrite(5,HIGH);

  /*
  for (int16_t i = 0; i < 3; ++i){
    {
      delete[] arena[i];
    }
    delete[] arena;
  }*/

}
void loop(){
  
  readTOF();
  int16_t frontDistance = frontTOFReading();
  if(frontDistance<100){
    pushcount++;
  }
  if(pushcount == 1){
    buzzer(2);
    returnxyDir =  solve(arena_1,13,0,1,1);    
    pushcount++;
    
  }
  
  

  


}

void buzzer(int16_t freq){
  for(int16_t i=0;i<freq;i++){
    tone(4,1000);
    delay(300);
    noTone(4);
    delay(100);
  }

}


