int16_t back_encoderValue = 182;
int16_t back_lencoder = 70;
int16_t back_rencoder = 70;
int16_t back_reverseValue = 70;

void comeBack1(int16_t ** path,int16_t lenthOfPath,int16_t startDirection,int16_t position){
    //initializing a path array
    int16_t direction = startDirection;
    //Serial.pruint16_t("Shortest Path Go  ");Serial.pruint16_tln(lenthOfPath);
    //turn180(back_reverseValue);
    //motors(60,60,0);
    //delay(260);
    //Loop to solve the maze
    if(position == 1){ // going from path1 (from zero to length of the path)
    for(int16_t count_loop = 0;count_loop<=lenthOfPath;count_loop++){
 
        if( count_loop == lenthOfPath){
            Serial.println("stop ");
            tone(4,1200);
            motors(230,230,3);
            delay(2000);
            noTone(4);
            turn180(back_lencoder);
            startDirection = 5- startDirection;
            break;
        }
        int16_t x1 = path[count_loop][0] ;
        int16_t y1 = path[count_loop][1] ;
        int16_t x2 = path[count_loop+1][0] ;
        int16_t y2 = path[count_loop+1][1] ;
        
        //Serial.pruint16_t(x1); Serial.pruint16_t("  "); Serial.pruint16_tln( y1);

        if(direction == 1){
            if (x1 != x2)
            {
            //Serial.pruint16_tln("Move Front1");
            direction = 1;
            moveForward(back_encoderValue);
            continue;
            }
            else if(y1<y2){
                //Serial.pruint16_tln("Move Right");
                direction = 3;
                moveRight(back_rencoder,back_encoderValue);

                continue;
            }
            else if  (y1>y2){
                //Serial.pruint16_tln("Move Left");
                direction = 2;
                moveLeft(back_lencoder,back_encoderValue);

                continue;
            }
            

        }
        else if(direction == 2){
            if(y1 != y2){
                //Serial.pruint16_tln("Move Left");
                direction = 2;
                moveForward(back_encoderValue);

                continue;
            }
            else if(x1>x2){
            //Serial.pruint16_tln("Move Front");
            direction = 1;
            moveRight(back_rencoder,back_encoderValue);
            continue;
            }
            else if(x1<x2){
                //Serial.pruint16_tln("Move Back");
                direction = 4;
                moveLeft(back_lencoder,back_encoderValue);

                continue;
            }
            
        }
        else if(direction == 3){
            if(y1 != y2){
                // Serial.pruint16_tln("Move right");
                direction = 3;
                moveForward(back_encoderValue);

                continue;
            }
            else if(x1>x2){
                //Serial.pruint16_tln("Move Front");
                direction = 1;
                moveLeft(back_lencoder,back_encoderValue);

                continue;
            }
            else if(x1<x2){
                //Serial.pruint16_tln("Move Back");
                direction = 4;
                moveRight(back_rencoder,back_encoderValue);

                continue;
            }
            
            
        }
        else if(direction == 4){
            if(x1 != x2){
                //Serial.pruint16_tln("Move Back");
                direction = 4;
                moveForward(back_encoderValue);

                continue;
            }
            else if(y1<y2){
                //Serial.pruint16_tln("Move right");
                direction = 3;
                moveLeft(back_rencoder,back_encoderValue);

                continue;
            }
            else if(y1>y2){
            //Serial.pruint16_tln("Move left");
            direction = 2;
            moveRight(back_lencoder,back_encoderValue);
            continue;
            }
        
        }
    }



}
if(position == 2){ // going from path2 (from  length of the path to zero)
    for(int16_t count_loop = lenthOfPath-1;count_loop>=0;count_loop--){
 
        if(count_loop == 0){
            Serial.println("stop ");
            tone(4,1200);
            motors(230,230,3);
            delay(2000);
            noTone(4);
            turn180(back_lencoder);
            startDirection = 5- startDirection;
            break;
        }
        int16_t x1 = path[count_loop][0] ;
        int16_t y1 = path[count_loop][1] ;
        int16_t x2 = path[count_loop-1][0] ;
        int16_t y2 = path[count_loop-1][1] ;
        
        //Serial.pruint16_t(x1); Serial.pruint16_t("  "); Serial.pruint16_tln( y1);

        if(direction == 1){
            if (x1 != x2)
            {
            //Serial.pruint16_tln("Move Front1");
            direction = 1;
            moveForward(back_encoderValue);
            continue;
            }
            else if(y1<y2){
                //Serial.pruint16_tln("Move Right");
                direction = 3;
                moveRight(back_rencoder,back_encoderValue);

                continue;
            }
            else if  (y1>y2){
                //Serial.pruint16_tln("Move Left");
                direction = 2;
                moveLeft(back_lencoder,back_encoderValue);

                continue;
            }
            

        }
        else if(direction == 2){
            if(y1 != y2){
                //Serial.pruint16_tln("Move Left");
                direction = 2;
                moveForward(back_encoderValue);

                continue;
            }
            else if(x1>x2){
            //Serial.pruint16_tln("Move Front");
            direction = 1;
            moveRight(back_rencoder,back_encoderValue);
            continue;
            }
            else if(x1<x2){
                //Serial.pruint16_tln("Move Back");
                direction = 4;
                moveLeft(back_lencoder,back_encoderValue);

                continue;
            }
            
        }
        else if(direction == 3){
            if(y1 != y2){
                // Serial.pruint16_tln("Move right");
                direction = 3;
                moveForward(back_encoderValue);

                continue;
            }
            else if(x1>x2){
                //Serial.pruint16_tln("Move Front");
                direction = 1;
                moveLeft(back_lencoder,back_encoderValue);

                continue;
            }
            else if(x1<x2){
                //Serial.pruint16_tln("Move Back");
                direction = 4;
                moveRight(back_rencoder,back_encoderValue);

                continue;
            }
            
            
        }
        else if(direction == 4){
            if(x1 != x2){
                //Serial.pruint16_tln("Move Back");
                direction = 4;
                moveForward(back_encoderValue);

                continue;
            }
            else if(y1<y2){
                //Serial.pruint16_tln("Move right");
                direction = 3;
                moveLeft(back_rencoder,back_encoderValue);

                continue;
            }
            else if(y1>y2){
            //Serial.pruint16_tln("Move left");
            direction = 2;
            moveRight(back_lencoder,back_encoderValue);
            continue;
            }
        
        }
    }



}



}



void comeBack2(int16_t path[50][2],int16_t lenthOfPath,int16_t startDirection,int16_t position){
    //initializing a path array
    int16_t direction = startDirection;
    //Serial.pruint16_t("Shortest Path Go  ");Serial.pruint16_tln(lenthOfPath);
    //turn180(back_reverseValue);
    //motors(60,60,0);
    //delay(260);
    //Loop to solve the maze
    if(position == 1){ // going from path1 (from zero to length of the path)
    for(int16_t count_loop = 0;count_loop<=lenthOfPath;count_loop++){
 
        if( count_loop == lenthOfPath){
            Serial.println("stop ");
            tone(4,1200);
            motors(230,230,3);
            delay(2000);
            noTone(4);
            turn180(back_lencoder);
            startDirection = 5- startDirection;
            break;
        }
        int16_t x1 = path[count_loop][0] ;
        int16_t y1 = path[count_loop][1] ;
        int16_t x2 = path[count_loop+1][0] ;
        int16_t y2 = path[count_loop+1][1] ;
        
        //Serial.pruint16_t(x1); Serial.pruint16_t("  "); Serial.pruint16_tln( y1);

        if(direction == 1){
            if (x1 != x2)
            {
            //Serial.pruint16_tln("Move Front1");
            direction = 1;
            moveForward(back_encoderValue);
            continue;
            }
            else if(y1<y2){
                //Serial.pruint16_tln("Move Right");
                direction = 3;
                moveRight(back_rencoder,back_encoderValue);

                continue;
            }
            else if  (y1>y2){
                //Serial.pruint16_tln("Move Left");
                direction = 2;
                moveLeft(back_lencoder,back_encoderValue);

                continue;
            }
            

        }
        else if(direction == 2){
            if(y1 != y2){
                //Serial.pruint16_tln("Move Left");
                direction = 2;
                moveForward(back_encoderValue);

                continue;
            }
            else if(x1>x2){
            //Serial.pruint16_tln("Move Front");
            direction = 1;
            moveRight(back_rencoder,back_encoderValue);
            continue;
            }
            else if(x1<x2){
                //Serial.pruint16_tln("Move Back");
                direction = 4;
                moveLeft(back_lencoder,back_encoderValue);

                continue;
            }
            
        }
        else if(direction == 3){
            if(y1 != y2){
                // Serial.pruint16_tln("Move right");
                direction = 3;
                moveForward(back_encoderValue);

                continue;
            }
            else if(x1>x2){
                //Serial.pruint16_tln("Move Front");
                direction = 1;
                moveLeft(back_lencoder,back_encoderValue);

                continue;
            }
            else if(x1<x2){
                //Serial.pruint16_tln("Move Back");
                direction = 4;
                moveRight(back_rencoder,back_encoderValue);

                continue;
            }
            
            
        }
        else if(direction == 4){
            if(x1 != x2){
                //Serial.pruint16_tln("Move Back");
                direction = 4;
                moveForward(back_encoderValue);

                continue;
            }
            else if(y1<y2){
                //Serial.pruint16_tln("Move right");
                direction = 3;
                moveLeft(back_rencoder,back_encoderValue);

                continue;
            }
            else if(y1>y2){
            //Serial.pruint16_tln("Move left");
            direction = 2;
            moveRight(back_lencoder,back_encoderValue);
            continue;
            }
        
        }
    }



}
if(position == 2){ // going from path2 (from  length of the path to zero)
    for(int16_t count_loop = lenthOfPath-1;count_loop>=0;count_loop--){
 
        if(count_loop == 0){
            Serial.println("stop ");
            tone(4,1200);
            motors(230,230,3);
            delay(2000);
            noTone(4);
            turn180(back_lencoder);
            startDirection = 5- startDirection;
            break;
        }
        int16_t x1 = path[count_loop][0] ;
        int16_t y1 = path[count_loop][1] ;
        int16_t x2 = path[count_loop-1][0] ;
        int16_t y2 = path[count_loop-1][1] ;
        
        //Serial.pruint16_t(x1); Serial.pruint16_t("  "); Serial.pruint16_tln( y1);

        if(direction == 1){
            if (x1 != x2)
            { 
            //Serial.pruint16_tln("Move Front1");
            direction = 1;
            moveForward(back_encoderValue);
            continue;
            }
            else if(y1<y2){
                //Serial.pruint16_tln("Move Right");
                direction = 3;
                moveRight(back_rencoder,back_encoderValue);

                continue;
            }
            else if  (y1>y2){
                //Serial.pruint16_tln("Move Left");
                direction = 2;
                moveLeft(back_lencoder,back_encoderValue);

                continue;
            }
            

        }
        else if(direction == 2){
            if(y1 != y2){
                //Serial.pruint16_tln("Move Left");
                direction = 2;
                moveForward(back_encoderValue);

                continue;
            }
            else if(x1>x2){
            //Serial.pruint16_tln("Move Front");
            direction = 1;
            moveRight(back_rencoder,back_encoderValue);
            continue;
            }
            else if(x1<x2){
                //Serial.pruint16_tln("Move Back");
                direction = 4;
                moveLeft(back_lencoder,back_encoderValue);

                continue;
            }
            
        }
        else if(direction == 3){
            if(y1 != y2){
                // Serial.pruint16_tln("Move right");
                direction = 3;
                moveForward(back_encoderValue);

                continue;
            }
            else if(x1>x2){
                //Serial.pruint16_tln("Move Front");
                direction = 1;
                moveLeft(back_lencoder,back_encoderValue);

                continue;
            }
            else if(x1<x2){
                //Serial.pruint16_tln("Move Back");
                direction = 4;
                moveRight(back_rencoder,back_encoderValue);

                continue;
            }
            
            
        }
        else if(direction == 4){
            if(x1 != x2){
                //Serial.pruint16_tln("Move Back");
                direction = 4;
                moveForward(back_encoderValue);

                continue;
            }
            else if(y1<y2){
                //Serial.pruint16_tln("Move right");
                direction = 3;
                moveLeft(back_rencoder,back_encoderValue);

                continue;
            }
            else if(y1>y2){
            //Serial.pruint16_tln("Move left");
            direction = 2;
            moveRight(back_lencoder,back_encoderValue);
            continue;
            }
        
        }
    }



}



}