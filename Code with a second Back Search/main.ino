//#include "maze1.h"
#include "motors.h"
#include "comeback.h"
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
  if(pushcount == 2){
    buzzer(2);
    //arena_2 = maze_2();
    //delay(500);
    //Serial.pruint16_t("xddf - ");Serial.pruint16_tln(arena_2[x_search][y_search]);
    //Serial.pruint16_t("y - ");Serial.pruint16_tln(y_search);
    //Serial.pruint16_t("dir - ");Serial.pruint16_tln(dir_search);
   
   // returnxyDir[2] = 5- returnxyDir[2];
    arena_1 = maze(2);
    delay(1000);
    returnxyDir =   solve(arena_1,returnxyDir[0],returnxyDir[1],returnxyDir[2],2);
    delete[] arena_1;
   // Serial.pruint16_tln(returnxyDir[2]);
    pushcount++;
    
  }
  if(pushcount==3){
    secondgoing(returnxyDir[2]);
    pushcount++;
  }


}

void buzzer(int16_t freq){
  for(int16_t i=0;i<freq;i++){
    tone(4,1000);
    delay(500);
    noTone(4);
    delay(100);
  }

}


