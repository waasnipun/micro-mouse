
int16_t back_encoderValue_b = 170;
int16_t back_lencoder_b = 70;
int16_t back_rencoder_b = 70;
int16_t back_reverseValue_b = 70;

int16_t comeBackprevious(int16_t path[180][2],int16_t lenthOfPath,int16_t startDirection){
    //initializing a path array

    int16_t direction = startDirection;
    int16_t position = lenthOfPath-1;

    

    //Loop to solve the maze
    while(true){
 
        if(position == 0){
            Serial.println("stop ");
            tone(4,1200);
            motors(230,230,3);
            delay(500);
            noTone(4);
            turn180(back_reverseValue_b);
            return(direction);
            break;
        }
        int16_t x1 = path[position][0] ;
        int16_t y1 = path[position][1] ;
        int16_t x2 = path[position-1][0] ;
        int16_t y2 = path[position-1][1] ;
        
        Serial.print(x1); Serial.print("  "); Serial.println( y1);

        if(direction == 1){
            if (x1 != x2)
            {
            //Serial.println("Move Front1");
            direction = 1;
            moveForward(back_encoderValue_b);
            position --;
            continue;
            }
            else if(y1<y2){
                //Serial.println("Move Right");
                direction = 3;
                moveRight(back_rencoder_b,back_encoderValue_b);
                position --;
                continue;
            }
            else if  (y1>y2){
                //Serial.println("Move Left");
                direction = 2;
                moveLeft(back_lencoder_b,back_encoderValue_b);
                position --;
                continue;
            }
            

        }
        else if(direction == 2){
            if(y1 != y2){
                //Serial.println("Move Left");
                direction = 2;
                moveForward(back_encoderValue_b);
                position --;
                continue;
            }
            else if(x1>x2){
            //Serial.println("Move Front");
            direction = 1;
            moveRight(back_rencoder_b,back_encoderValue_b);
            position --;
            continue;
            }
            else if(x1<x2){
                //Serial.println("Move Back");
                direction = 4;
                moveLeft(back_lencoder_b,back_encoderValue_b);
                position --;
                continue;
            }
            
        }
        else if(direction == 3){
            if(y1 != y2){
                // Serial.println("Move right");
                direction = 3;
                moveForward(back_encoderValue_b);
                position --;
                continue;
            }
            else if(x1>x2){
                //Serial.println("Move Front");
                direction = 1;
                moveLeft(back_lencoder_b,back_encoderValue_b);
                position --;
                continue;
            }
            else if(x1<x2){
                //Serial.println("Move Back");
                direction = 4;
                moveRight(back_rencoder_b,back_encoderValue_b);
                position --;
                continue;
            }
            
            
        }
        else if(direction == 4){
            if(x1 != x2){
                //Serial.println("Move Back");
                direction = 4;
                moveForward(back_encoderValue_b);
                position --;
                continue;
            }
            else if(y1<y2){
                //Serial.println("Move right");
                direction = 3;
                moveLeft(back_rencoder_b,back_encoderValue_b);
                position --;
                continue;
            }
            else if(y1>y2){
            //Serial.println("Move left");
            direction = 2;
            moveRight(back_lencoder_b,back_encoderValue_b);
            position --;
            continue;
            }
        
        }
    }
}

int16_t gofrontFast(int16_t path[180][2],int16_t lenthOfPath,int16_t startDirection){
    //initializing a path array
     P = 0.8;
     D = 2.9;
     I = 0.01;
    int16_t direction = startDirection;
    int16_t position = 0;
    Serial.println("dsfsdfsdffsf");Serial.println(direction);

    

    //Loop to solve the maze
    while(true){
 
        if(position == lenthOfPath-1){
            Serial.println("stop ");
            tone(4,1200);
            motors(230,230,3);
            delay(1000);
            noTone(4);
            turn180(back_reverseValue_b);
            return direction;
            break;
        }
        int16_t x1 = path[position][0] ;
        int16_t y1 = path[position][1] ;
        int16_t x2 = path[position+1][0] ;
        int16_t y2 = path[position+1][1] ;
        
        Serial.print(x1); Serial.print("  "); Serial.println( y1);

        if(direction == 1){
            if (x1 != x2)
            {
            //Serial.println("Move Front1");
            direction = 1;
            moveForwardFast(back_encoderValue_b);
            position ++;
            continue;
            }
            else if(y1<y2){
                //Serial.println("Move Right");
                direction = 3;
                moveRightFast(back_rencoder_b,back_encoderValue_b);
                position ++;
                continue;
            }
            else if  (y1>y2){
                //Serial.println("Move Left");
                direction = 2;
                moveLeftFast(back_lencoder_b,back_encoderValue_b);
                position ++;
                continue;
            }
            

        }
        else if(direction == 2){
            if(y1 != y2){
                //Serial.println("Move Left");
                direction = 2;
                moveForwardFast(back_encoderValue_b);
                position --;
                continue;
            }
            else if(x1>x2){
            //Serial.println("Move Front");
            direction = 1;
            moveRightFast(back_rencoder_b,back_encoderValue_b);
            position ++;
            continue;
            }
            else if(x1<x2){
                //Serial.println("Move Back");
                direction = 4;
                moveLeftFast(back_lencoder_b,back_encoderValue_b);
                position ++;
                continue;
            }
            
        }
        else if(direction == 3){
            if(y1 != y2){
                // Serial.println("Move right");
                direction = 3;
                moveForwardFast(back_encoderValue_b);
                position ++;
                continue;
            }
            else if(x1>x2){
                //Serial.println("Move Front");
                direction = 1;
                moveLeftFast(back_lencoder_b,back_encoderValue_b);
                position ++;
                continue;
            }
            else if(x1<x2){
                //Serial.println("Move Back");
                direction = 4;
                moveRightFast(back_rencoder_b,back_encoderValue_b);
                position ++;
                continue;
            }
            
            
        }
        else if(direction == 4){
            if(x1 != x2){
                //Serial.println("Move Back");
                direction = 4;
                moveForwardFast(back_encoderValue_b);
                position ++;
                continue;
            }
            else if(y1<y2){
                //Serial.println("Move right");
                direction = 3;
                moveLeftFast(back_rencoder_b,back_encoderValue_b);
                position ++;
                continue;
            }
            else if(y1>y2){
            //Serial.println("Move left");
            direction = 2;
            moveRightFast(back_lencoder_b,back_encoderValue_b);
            position ++;
            continue;
            }
        
        }
    }
}