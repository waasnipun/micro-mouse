//#include "motors.h"
//#include "comeback.h"

int16_t  array_index;
int16_t frontSensor ;
int16_t leftSensor ;
int16_t rightSensor ;
int16_t frontthreshold = 160;
int16_t leftthreshold = 120;
int16_t rightthreshold = 120;
//int16_t encoderValue = 82;
//int16_t lencoder = 28;
//int16_t rencoder = 28;
//int16_t reverseValue = 70;

int16_t encoderValue = 183;
int16_t lencoder = 70;
int16_t rencoder = 70;
int16_t reverseValue = 70;

int16_t turnBack = 0;
int16_t turnBacksearch = 0;

int16_t countloop = 0;
int16_t current_x;
int16_t current_y;

int16_t length1=0,length2=0;
int16_t mousepath[50][2];  
int16_t** pathFirst; 

void updateScreen(int16_t **maze,int16_t rows ){       //show the maze to the screen
    for(int16_t i=0;i<rows;i++){
        for(int16_t j=0;j<rows;j++){
            if(maze[i][j]>=10){
            Serial.print("| ");
            Serial.print(maze[i][j]);Serial.print(" |");
            }
            else{
                Serial.print("| ");
                Serial.print(maze[i][j]);Serial.print("  |");   
            }
        }
        Serial.print("\n");
    }
}

int16_t** maze(int16_t shift){ // ceate the maze
    int16_t rows = 14;
    int16_t** maze = new int16_t*[rows];
    for(int16_t i=0;i<rows;i++){
        maze[i] = new int16_t[rows];
        }  
    if(shift==1){    
    int16_t start = rows-2;    
    for(int16_t j=0;j<rows/2;j++){
        int16_t temp = start;
        for(int16_t i=0;i<rows/2;i++){
            maze[j][i] = temp;
            maze[j][rows-1-i] = temp;
            maze[rows-1-j][i] = temp;
            maze[rows-1-j][rows-1-i] = temp;
            temp--;
            }
        start--;
    }
    }
    else if(shift==2){ 
    for(int16_t i = 0;i<14;i++){
        for (int16_t j = 0; j<14;j++){
            maze[i][j] = 13-i+j;
        }
    }
    delay(500);
    //updateScreen(maze,14);
    }
    return maze;

}

int16_t** updatearena(int16_t ** arena,int16_t pathi[196][2],int16_t val){ //increment the went path in arena
    for(int16_t i=array_index-1;i>=0;i--){
        int16_t newx = pathi[i][0];
        int16_t newy = pathi[i][1];
        arena[newx][newy] = val+1;
        val+=1;
    }
   return arena;
}


int16_t temp[3];

int16_t* solve(int16_t ** arena , int16_t x, int16_t y, int16_t direction,int16_t run){
    
    array_index = 0;
    //initializing a path array
 
    for(int16_t i=0;i<50;i++){
        mousepath[i][0]=0;
        mousepath[i][1]=0;
    }
    /*int16_t** mousepath = new int16_t*[50];
        for(int16_t i = 0; i < 50; i++){
            mousepath[i] = new int16_t[2];
        }*/
    /*int16_t x = 13;
    int16_t y = 0;

    int16_t direction = 1;*/

    //Loop to solve the maze
    while(arena[x][y]>=0){
        //updateScreen(arena,14);
        //Serial.print(" value ");Serial.print(arena[x][y]);
        
        //Reading TOf Valuies every time
        readTOF();
        frontSensor = frontTOFReading();
        leftSensor = leftTOFReading();
        rightSensor = rightTOFReading();
        //Serial.print("front :");Serial.println(frontSensor);
        //Serial.print("left :");Serial.println(leftSensor);
        //Serial.print("right :");Serial.println(rightSensor);
        if(frontSensor<70 && leftSensor <70 && rightSensor<70 && x!=13 && y!=0){
            turn180(reverseValue);
            turnBack = 1;
            //arena[x][y] = 1000;
            //Serial.println("Turn 180 ");
            if(direction==1){direction=4;}
            else if(direction==4){direction=1;}
            else if(direction==2){direction=3;}
            else if(direction==3){direction=2;}
            continue;
        }
        //updating the path
        mousepath[array_index][0] = x;
        mousepath[array_index][1] = y;
     
        for(int16_t i=0;i<array_index;i++){   
            if(x==mousepath[i][0] && y==mousepath[i][1]){
                arena[mousepath[array_index-1][0]][mousepath[array_index-1][1]] = 700;
                //Serial.print("loop confirmed , next time turning back");
                //turn180(reverseValue);
                //updatearena(arena,mousepath,arena[x][y]);
            //arena[x][y] = 1000;
            //Serial.println("Turn 180 ");
            /*if(direction==1){direction=4;}
            else if(direction==4){direction=1;}
            else if(direction==2){direction=3;}
            else if(direction==3){direction=2;}
            moveForward(encoderValue);*/
                /*for(int16_t j=i;j<array_index;j++){

                }*/
                /*if (turnBack ==1){
                    arena[mousepath[i+1][0]][mousepath[i+1][1]] = 700;
                    turnBacksearch = 1;
                }
               // for (int16_t j=i+1;j<array_index-1;j++){
                else if (countloop ==0 ){
                    current_x = x;
                    current_y = y;
                    countloop ++;
                } 
                else if (countloop == 1 && current_x ==x && current_y == y ){
                    countloop ++;
                }
                else if (countloop == 2){
                    arena[mousepath[i+1][0]][mousepath[i+1][1]] = 700;
                    countloop = 0;
                }
            else{
                turnBacksearch = 0;
            */
            
                    //Serial.print("sdfsdffsdgsfgsdfgsdgs");Serial.print(mousepath[i][0]); Serial.println(mousepath[i][1]);
                //}
                array_index = i;
                continue;
                
            }
        }
    
/*
        for (int16_t k =0;k<=array_index;k++){
            Serial.print(mousepath[k][0]);Serial.print(" ");Serial.print(mousepath[k][1]);Serial.print("  ");
        }
        Serial.println("");*/
        array_index++;
        //Serial.print(" left");Serial.print(leftSensor);
        //Serial.print(" right");Serial.println(rightSensor);
        //Serial.print("kotuwa     ");Serial.print(mousepath[array_index-1][0]);Serial.print(" ");Serial.print(mousepath[array_index-1][1]);
       // Serial.print("   kotuwe value 1     ");Serial.println(arena[mousepath[array_index-1][0]][mousepath[array_index-1][1]]);
        if(arena[x][y]==0){
            Serial.println("stop ");
            tone(4,1200);
            motors(100,100,3);
            delay(500);
            noTone(4);
            //delay(1000);
            turn180(reverseValue);
            direction = 5-direction;
            
            //Serial.println(array_index);
            if(run==1){
                length1 = array_index;
                pathFirst = new int16_t*[length1];
                int16_t tempX;
                int16_t tempY;
                for(int16_t i = 0; i < length1; i++){
                    pathFirst[i] = new int16_t[2];
        }
                for(int16_t i=0;i<array_index;i++){
                    tempX = mousepath[i][0];
                    tempY = mousepath[i][1];
                    pathFirst[i][0] = tempX; 
                    pathFirst[i][1] = tempY;                
                 }
                //delete[] mousepath;
                //mousepath = NULL;
                 Serial.print("Run 1 length ;");Serial.println(length1);
                 for (int16_t k =0;k<length1;k++){
                    Serial.print(pathFirst[k][0]);Serial.print(" ");Serial.print(pathFirst[k][1]);Serial.print("  ");
                } 
            }
            else if(run ==2){
                length2 = array_index;
                
                

                //pathSecond = new int16_t*[length2];
                //int16_t tempXnew;
                //int16_t tempYnew;
               /* for(int16_t i = 0; i < length2; i++){
                    pathSecond[i] = new int16_t[2];
        }*/
                /*for(int16_t i=0;i<length2;i++){
                  // tempXnew = mousepath[i][0];
                    //tempYnew = mousepath[i][1];
                    pathSecond[i] = mousepath[i]; 
                    //pathSecond[i][1] = mousepath[i][1]; 
                     }*/
                //changetoPathTwo(mousepath,length2); 
                //delete[] mousepath;
                //mousepath = NULL;
                /*Serial.print("Run 2 length ;");Serial.println(length2);
                for (int16_t k =0;k<length2;k++){
                    Serial.print(mousepath[k][0]);Serial.print(" ");Serial.print(mousepath[k][1]);Serial.print("  ");
                }
                
                Serial.println("-----------------------");

                if(length1<length2){
                        Serial.print("smallest path is 1 ;");Serial.println(length1);
                        for (int16_t k =0;k<length1;k++){
                    Serial.print(pathFirst[k][0]);Serial.print(" ");Serial.print(pathFirst[k][1]);Serial.print("  ");
                }
                Serial.println();
                for (int16_t k =0;k<length2;k++){
                    Serial.print(mousepath[k][0]);Serial.print(" ");Serial.print(mousepath[k][1]);Serial.print("  ");
                }
                }
                else{
                    Serial.print("smallest path is 2 ;");Serial.println(length2);
                       
                for (int16_t k =0;k<length1;k++){
                    Serial.print(pathFirst[k][0]);Serial.print(" ");Serial.print(pathFirst[k][1]);Serial.print("  ");
                }
                Serial.println();
                 for (int16_t k =0;k<length2;k++){
                    Serial.print(mousepath[k][0]);Serial.print(" ");Serial.print(mousepath[k][1]);Serial.print("  ");
                }
                }*/
                secondgoing(direction);
               
            }            
                       
                     
            //arena_2 = maze_2();
            //comeBack(path,array_index,direction);
            //solve_2(arena_2,x,y,direction);
            delay(500);
            //updateScreen(arena,14);
            temp[0] = x;
            temp[1] = y;
            temp[2] = direction;

            //Serial.print("x - ");Serial.println(temp[0]);
            //Serial.print("y - ");Serial.println(temp[1]);
            //Serial.print("dir - ");Serial.println(temp[2]);
            //pushcount++;
            return temp;
        }
        /*Serial.print("left ");Serial.println(leftSensor);
        Serial.print("right ");Serial.println(rightSensor);
        Serial.print("front ");Serial.println(frontSensor);
        Serial.print(direction);*/
        // front eka 700 unahama
        if(direction ==1 && arena[x-1][y]>=700 && rightSensor <rightthreshold && leftSensor<leftthreshold){
            turn180(reverseValue);
            turnBack = 1;
            //arena[x][y] = 1000;
            //Serial.println("Turn 180 ");
            if(direction==1){direction=4;}
            else if(direction==4){direction=1;}
            else if(direction==2){direction=3;}
            else if(direction==3){direction=2;}
            continue;
            }
        
        else if(direction ==2 && arena[x][y-1]>=700 && rightSensor <rightthreshold && leftSensor<leftthreshold){
            turn180(reverseValue);
            turnBack = 1;
            //arena[x][y] = 1000;
            //Serial.println("Turn 180 ");
            if(direction==1){direction=4;}
            else if(direction==4){direction=1;}
            else if(direction==2){direction=3;}
            else if(direction==3){direction=2;}
            continue;
        }
        else if(direction ==3 && arena[x][y+1]>=700 && rightSensor <rightthreshold && leftSensor<leftthreshold){
            turn180(reverseValue);
            turnBack = 1;
            //arena[x][y] = 1000;
            //Serial.println("Turn 180 ");
            if(direction==1){direction=4;}
            else if(direction==4){direction=1;}
            else if(direction==2){direction=3;}
            else if(direction==3){direction=2;}
            continue;
        }
        else if(direction ==4 && arena[x+1][y]>=700 && rightSensor <rightthreshold && leftSensor<leftthreshold){
            turn180(reverseValue);
            turnBack = 1;
            //arena[x][y] = 1000;
            //Serial.println("Turn 180 ");
            if(direction==1){direction=4;}
            else if(direction==4){direction=1;}
            else if(direction==2){direction=3;}
            else if(direction==3){direction=2;}
            continue;
        }

        //right eka 700 unahama
        if(direction ==1 && arena[x][y+1]>=700 && leftSensor<leftthreshold && frontSensor<frontthreshold){
            turn180(reverseValue);
            turnBack = 1;
            //arena[x][y] = 1000;
            //Serial.println("Turn 180 ");
            if(direction==1){direction=4;}
            else if(direction==4){direction=1;}
            else if(direction==2){direction=3;}
            else if(direction==3){direction=2;}
            continue;
            }
        
        else if(direction ==2 && arena[x-1][y]>=700 && leftSensor<leftthreshold && frontSensor<frontthreshold){
            turn180(reverseValue);
            turnBack = 1;
            //arena[x][y] = 1000;
            //Serial.println("Turn 180 ");
            if(direction==1){direction=4;}
            else if(direction==4){direction=1;}
            else if(direction==2){direction=3;}
            else if(direction==3){direction=2;}
            continue;
        }
        else if(direction ==3 && arena[x+1][y]>=700 && leftSensor<leftthreshold && frontSensor<frontthreshold){
            turn180(reverseValue);
            turnBack = 1;
            //arena[x][y] = 1000;
            //Serial.println("Turn 180 ");
            if(direction==1){direction=4;}
            else if(direction==4){direction=1;}
            else if(direction==2){direction=3;}
            else if(direction==3){direction=2;}
            continue;
        }
        else if(direction ==4 && arena[x][y-1]>=700 && leftSensor<leftthreshold && frontSensor<frontthreshold){
            turn180(reverseValue);
            turnBack = 1;
            //arena[x][y] = 1000;
            //Serial.println("Turn 180 ");
            if(direction==1){direction=4;}
            else if(direction==4){direction=1;}
            else if(direction==2){direction=3;}
            else if(direction==3){direction=2;}
            continue;
        }

        //left eka 700 unahama
        if(direction ==1 && arena[x][y-1]>=700 && rightSensor <rightthreshold && frontSensor<frontthreshold){
            turn180(reverseValue);
            turnBack = 1;
            //arena[x][y] = 1000;
            //Serial.println("Turn 180 ");
            if(direction==1){direction=4;}
            else if(direction==4){direction=1;}
            else if(direction==2){direction=3;}
            else if(direction==3){direction=2;}
            continue;
            }
        
        else if(direction ==2 && arena[x+1][y]>=700 && rightSensor <rightthreshold && frontSensor<frontthreshold){
            turn180(reverseValue);
            turnBack = 1;
            //arena[x][y] = 1000;
            //Serial.println("Turn 180 ");
            if(direction==1){direction=4;}
            else if(direction==4){direction=1;}
            else if(direction==2){direction=3;}
            else if(direction==3){direction=2;}
            continue;
        }
        else if(direction ==3 && arena[x-1][y]>=700 && rightSensor <rightthreshold && frontSensor<frontthreshold){
            turn180(reverseValue);
            turnBack = 1;
            //arena[x][y] = 1000;
            //Serial.println("Turn 180 ");
            if(direction==1){direction=4;}
            else if(direction==4){direction=1;}
            else if(direction==2){direction=3;}
            else if(direction==3){direction=2;}
            continue;
        }
        else if(direction ==4 && arena[x][y+1]>=700 && rightSensor <rightthreshold && frontSensor<frontthreshold){
            turn180(reverseValue);
            turnBack = 1;
            //arena[x][y] = 1000;
            //Serial.println("Turn 180 ");
            if(direction==1){direction=4;}
            else if(direction==4){direction=1;}
            else if(direction==2){direction=3;}
            else if(direction==3){direction=2;}
            continue;
        }
        // main floodfill conditions
        if(direction == 1){
        
            
            if( x>=0 && x<14 && y>=0 && y<14 && frontSensor>frontthreshold && arena[x-1][y]<arena[x][y] && arena[x-1][y] < 700){
            //Serial.println("Move Front1");
            direction = 1;
            moveForward(encoderValue);
            x--;
            continue;
            }
            else if(x>=0 && x<14 && y>=0 && y<14 && rightSensor >rightthreshold && arena[x][y+1]<arena[x][y] && arena[x][y+1] <700){
                //Serial.println("Move Right");
                direction = 3;
                moveRight(rencoder,encoderValue);
                y++;
                continue;
            }
            else if(x>=0 && x<14 && y>=0 && y<14 && leftSensor>leftthreshold && arena[x][y-1]<arena[x][y] && arena[x][y-1]< 700){
                //Serial.println("Move Left");
                direction = 2;
                moveLeft(lencoder,encoderValue);
                y--;
                continue;
            }
            

        }
        else if(direction == 2){
            if(x>=0 && x<14 && y>=0 && y<14 && frontSensor>frontthreshold && arena[x][y-1]<arena[x][y] && arena[x][y-1]< 700){
                //Serial.println("Move Left");
                direction = 2;
                moveForward(encoderValue);
                y = y-1;
                continue;
            }
            else if(x>=0 && x<14 && y>=0 && y<14 && rightSensor >rightthreshold && arena[x-1][y]<arena[x][y] && arena[x-1][y]< 700){
            //Serial.println("Move Front");
            direction = 1;
            moveRight(rencoder,encoderValue);
            x = x-1;
            continue;
            }
            else if(x>=0 && x<14 && y>=0 && y<14 && leftSensor>leftthreshold && arena[x+1][y]<arena[x][y] && arena[x+1][y]< 700){
                //Serial.println("Move Back");
                direction = 4;
                moveLeft(lencoder,encoderValue);
                x = x+1;
                continue;
            }
            
        }
        else if(direction == 3){
            if(x>=0 && x<14 && y>=0 && y<14 && frontSensor>frontthreshold && arena[x][y+1]<arena[x][y] && arena[x][y+1]< 700){
                // Serial.println("Move right");
                direction = 3;
                moveForward(encoderValue);
                y = y+1;
                continue;
            }
            else if(x>=0 && x<14 && y>=0 && y<14 && leftSensor>leftthreshold && arena[x-1][y]<arena[x][y]  && arena[x-1][y]< 700){
                //Serial.println("Move Front");
                direction = 1;
                moveLeft(lencoder,encoderValue);
                x = x-1;
                continue;
            }
            else if(x>=0 && x<14 && y>=0 && y<14 && rightSensor >rightthreshold && arena[x+1][y]<arena[x][y] && arena[x+1][y]< 700){
                //Serial.println("Move Back");
                direction = 4;
                moveRight(rencoder,encoderValue);
                x = x+1;
                continue;
            }
            
            
        }
        else if(direction == 4){
            if(x>=0 && x<14 && y>=0 && y<14 && frontSensor>frontthreshold  && arena[x+1][y]<arena[x][y] && arena[x+1][y]< 700){
                //Serial.println("Move Back");
                direction = 4;
                moveForward(encoderValue);
                x = x+1;
                continue;
            }
            else if(x>=0 && x<14 && y>=0 && y<14 && leftSensor>leftthreshold && arena[x][y+1]<arena[x][y] && arena[x][y+1] < 700){
                //Serial.println("Move right");
                direction = 3;
                moveLeft(rencoder,encoderValue);
                y = y+1;
                continue;
            }
            else if(x>=0 && x<14 && y>=0 && y<14 && rightSensor >rightthreshold && arena[x][y-1]<arena[x][y] && arena[x][y-1] < 700){
            //Serial.println("Move left");
            direction = 2;
            moveRight(lencoder,encoderValue);
            y = y-1;
            continue;
            }
            
            
            
        }
        if(direction ==1){
        if(x>=0 && x<14 && y>=0 && y<14 && frontSensor>frontthreshold && arena[x-1][y]==arena[x][y] && arena[x-1][y] < 700){
        // Serial.println("Move Front");
            direction = 1;
            moveForward(encoderValue);
            x = x-1;
            arena = updatearena(arena,mousepath,arena[x][y]);
            //updateScreen(arena,14);
            continue;
            }
            else if(x>=0 && x<14 && y>=0 && y<14 && rightSensor >rightthreshold && arena[x][y+1]==arena[x][y] && arena[x][y+1] < 700){
                //Serial.println("Move Right");
                direction = 3;
                moveRight(lencoder,encoderValue);
                y = y+1;
                arena = updatearena(arena,mousepath,arena[x][y]);
                //updateScreen(arena,14);
                continue;
            }
            else if(x>=0 && x<14 && y>=0 && y<14 && leftSensor>leftthreshold && arena[x][y-1]==arena[x][y] && arena[x][y-1] < 700){
                //Serial.println("Move Left");
                direction = 2;
                y = y-1;
                moveLeft(rencoder,encoderValue);
                arena = updatearena(arena,mousepath,arena[x][y]);
                //updateScreen(arena,14);
                continue;
            }

        }
        else if(direction == 2){
            if(x>=0 && x<14 && y>=0 && y<14 && frontSensor>frontthreshold && arena[x][y-1]==arena[x][y] && arena[x][y-1] < 700){
                //Serial.println("Move Left");
                direction = 2;
                y = y-1;
                moveForward(encoderValue);
                arena = updatearena(arena,mousepath,arena[x][y]);
                //updateScreen(arena,14);
                continue;
            }
            else if(x>=0 && x<14 && y>=0 && y<14 && rightSensor >rightthreshold && arena[x-1][y]==arena[x][y] && arena[x-1][y] < 700){
            //Serial.println("Move Front");
            direction = 1;
            x = x-1;
            moveRight(lencoder,encoderValue);
            arena = updatearena(arena,mousepath,arena[x][y]);
            //updateScreen(arena,14);
            continue;
            }
            else if(x>=0 && x<14 && y>=0 && y<14 && leftSensor>leftthreshold  && arena[x+1][y]==arena[x][y] && arena[x+1][y] < 700){
                //Serial.println("Move Back");
                direction = 4;
                x = x+1;
                moveLeft(rencoder,encoderValue);
                arena = updatearena(arena,mousepath,arena[x][y]);
                //updateScreen(arena,14);
                continue;
            }
            
        }
        else if(direction == 3){
            if(x>=0 && x<14 && y>=0 && y<14 && frontSensor>frontthreshold  && arena[x][y+1]==arena[x][y] && arena[x][y+1] < 700){
                //Serial.println("Move right");
                direction = 3;
                y = y+1;
                moveForward(encoderValue);
                arena = updatearena(arena,mousepath,arena[x][y]);
                //updateScreen(arena,14);
                continue;
            }
            else if(x>=0 && x<14 && y>=0 && y<14 && leftSensor>leftthreshold  && arena[x-1][y]==arena[x][y] && arena[x-1][y] < 700){
            //Serial.println("Move Front");
            direction = 1;
            x = x-1;
            moveLeft(rencoder,encoderValue);
            arena = updatearena(arena,mousepath,arena[x][y]);
            //updateScreen(arena,14);
            continue;
            }
            else if(x>=0 && x<14 && y>=0 && y<14 && rightSensor >rightthreshold && arena[x+1][y]==arena[x][y] && arena[x+1][y] < 700){
            // Serial.println("Move Back");
                direction = 4;
                x = x+1;
                moveRight(lencoder,encoderValue);
                arena = updatearena(arena,mousepath,arena[x][y]);
                //updateScreen(arena,14);
                continue;
            }
            
        }
        else if(direction == 4){
            if(x>=0 && x<14 && y>=0 && y<14 && frontSensor>frontthreshold  && arena[x+1][y]==arena[x][y] && arena[x+1][y]< 700){
                //Serial.println("Move Back");
                direction = 4;
                x = x+1;
                moveForward(encoderValue);
                arena = updatearena(arena,mousepath,arena[x][y]);
                //updateScreen(arena,14);
                continue;
            }
            else if(x>=0 && x<14 && y>=0 && y<14 && leftSensor>leftthreshold && arena[x][y+1]==arena[x][y] && arena[x][y+1] < 700){
                //Serial.println("Move right");
                direction = 3;
                y = y+1;
                moveLeft(rencoder,encoderValue);
                arena = updatearena(arena,mousepath,arena[x][y]);
                //updateScreen(arena,14);
                continue;
            }
            else if(x>=0 && x<14 && y>=0 && y<14 && rightSensor >rightthreshold && arena[x][y-1]==arena[x][y] && arena[x][y-1] < 700){
            //Serial.println("Move left");
            direction = 2;
            y = y-1;
            moveRight(lencoder,encoderValue);
            arena = updatearena(arena,mousepath,arena[x][y]);
            //updateScreen(arena,14);
            continue;
            }
            
            
        }
        

        if(direction ==1){
        if(x>=0 && x<14 && y>=0 && y<14 && frontSensor>frontthreshold && arena[x-1][y]>arena[x][y] && arena[x-1][y] < 700){
        // Serial.println("Move Front");
            direction = 1;
            moveForward(encoderValue);
            x = x-1;
            arena = updatearena(arena,mousepath,arena[x][y]);
            //updateScreen(arena,14);
            continue;
            }
            else if(x>=0 && x<14 && y>=0 && y<14 && rightSensor >rightthreshold && arena[x][y+1]>arena[x][y] && arena[x][y+1] < 700){
                //Serial.println("Move Right");
                direction = 3;
                moveRight(lencoder,encoderValue);
                y = y+1;
                arena = updatearena(arena,mousepath,arena[x][y]);
                //updateScreen(arena,14);
                continue;
            }
            else if(x>=0 && x<14 && y>=0 && y<14 && leftSensor>leftthreshold && arena[x][y-1]>arena[x][y] && arena[x][y-1] < 700){
                //Serial.println("Move Left");
                direction = 2;
                y = y-1;
                moveLeft(rencoder,encoderValue);
                arena = updatearena(arena,mousepath,arena[x][y]);
                //updateScreen(arena,14);
                continue;
            }

        }
        else if(direction == 2){
            if(x>=0 && x<14 && y>=0 && y<14 && frontSensor>frontthreshold && arena[x][y-1]>arena[x][y] && arena[x][y-1]< 700){
                //Serial.println("Move Left");
                direction = 2;
                y = y-1;
                moveForward(encoderValue);
                arena = updatearena(arena,mousepath,arena[x][y]);
                //updateScreen(arena,14);
                continue;
            }
            else if(x>=0 && x<14 && y>=0 && y<14 && rightSensor >rightthreshold && arena[x-1][y]>arena[x][y] && arena[x-1][y] < 700){
            //Serial.println("Move Front");
            direction = 1;
            x = x-1;
            moveRight(lencoder,encoderValue);
            arena = updatearena(arena,mousepath,arena[x][y]);
            //updateScreen(arena,14);
            continue;
            }
            else if(x>=0 && x<14 && y>=0 && y<14 && leftSensor>leftthreshold  && arena[x+1][y]>arena[x][y] && arena[x+1][y] < 700){
                //Serial.println("Move Back");
                direction = 4;
                x = x+1;
                moveLeft(rencoder,encoderValue);
                arena = updatearena(arena,mousepath,arena[x][y]);
                //updateScreen(arena,14);
                continue;
            }
            
        }
        else if(direction == 3){
            if(x>=0 && x<14 && y>=0 && y<14 && frontSensor>frontthreshold  && arena[x][y+1]>arena[x][y] && arena[x][y+1] < 700){
                //Serial.println("Move right");
                direction = 3;
                y = y+1;
                moveForward(encoderValue);
                arena = updatearena(arena,mousepath,arena[x][y]);
                //updateScreen(arena,14);
                continue;
            }
            else if(x>=0 && x<14 && y>=0 && y<14 && leftSensor>leftthreshold  && arena[x-1][y]>arena[x][y] && arena[x-1][y] < 700){
            //Serial.println("Move Front");
            direction = 1;
            x = x-1;
            moveLeft(rencoder,encoderValue);
            arena = updatearena(arena,mousepath,arena[x][y]);
            //updateScreen(arena,14);
            continue;
            }
            else if(x>=0 && x<14 && y>=0 && y<14 && rightSensor >rightthreshold && arena[x+1][y]>arena[x][y] && arena[x+1][y] < 700){
            // Serial.println("Move Back");
                direction = 4;
                x = x+1;
                moveRight(lencoder,encoderValue);
                arena = updatearena(arena,mousepath,arena[x][y]);
                //updateScreen(arena,14);
                continue;
            }
            
        }
        else if(direction == 4){
            if(x>=0 && x<14 && y>=0 && y<14 && frontSensor>frontthreshold  && arena[x+1][y]>arena[x][y] && arena[x+1][y] < 700){
                //Serial.println("Move Back");
                direction = 4;
                x = x+1;
                moveForward(encoderValue);
                arena = updatearena(arena,mousepath,arena[x][y]);
                //updateScreen(arena,14);
                continue;
            }
            else if(x>=0 && x<14 && y>=0 && y<14 && leftSensor>leftthreshold && arena[x][y+1]>arena[x][y] && arena[x][y+1] < 700){
                //Serial.println("Move right");
                direction = 3;
                y = y+1;
                moveLeft(rencoder,encoderValue);
                arena = updatearena(arena,mousepath,arena[x][y]);
                //updateScreen(arena,14);
                continue;
            }
            else if(x>=0 && x<14 && y>=0 && y<14 && rightSensor >rightthreshold && arena[x][y-1]>arena[x][y] && arena[x][y-1] < 700){
            //Serial.println("Move left");
            direction = 2;
            y = y-1;
            moveRight(lencoder,encoderValue);
            arena = updatearena(arena,mousepath,arena[x][y]);
            //updateScreen(arena,14);
            continue;
            }
            
            
        }
        

    }
}
//int16_t tempXnew;
//int16_t tempYnew;

// converting mousepath to path2
/*void changetoPathTwo(int16_t mousepathnew[50][2],int16_t length2new){
    pathSecond = new int16_t*[length2new];
    for(int16_t i = 0; i < length2new; i++){
        pathSecond[i] = new int16_t[2];
        }
    for(int16_t i=0;i<length2new;i++){
            tempXnew = mousepathnew[i][0];
            tempYnew = mousepathnew[i][1];
            pathSecond[i][0] = tempXnew; 
            pathSecond[i][1] = tempYnew; 
                     }
delete[] arena_1;
                //mousepath = NULL
                //mousepath = NULL
}*/
void secondgoing(int16_t searchStopdirection){
    delay(1000);
    if (length1<length2 && searchStopdirection==3){
        moveLeft(rencoder,encoderValue);     
        searchStopdirection=1;
        comeBack1(pathFirst,length1,searchStopdirection,1);
    } 
    else if (length1<length2 && searchStopdirection==1){       
        searchStopdirection=1;
        comeBack1(pathFirst,length1,searchStopdirection,1);
    }
    else if (length1>=length2 && searchStopdirection==3){
        //moveLeftWithoutForward(lencoder); 
        searchStopdirection=3;
        comeBack2(mousepath,length2,searchStopdirection,2);
    }
    else if (length1>=length2 && searchStopdirection==1){
        //moveLeftWithoutForward(lencoder);    
        searchStopdirection=1;
        comeBack2(mousepath,length2,searchStopdirection,2);
    }


    


}

