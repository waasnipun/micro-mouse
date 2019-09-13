#define RH_ENCODER_A 2
#define LH_ENCODER_A 3
volatile int16_t EncoderValueLeft=0;
volatile int16_t EncoderValueRight=0;

void countLeft()
{
      EncoderValueLeft++;
  
}
void countRight()
{
      EncoderValueRight++;
   
}

void encodersZero(){
    EncoderValueLeft = 0;
    EncoderValueRight = 0;
}
void initEncoders(){
  pinMode(LH_ENCODER_A,INPUT);
  pinMode(RH_ENCODER_A,INPUT);
  attachInterrupt(digitalPinToInterrupt(2), countLeft, RISING);
  attachInterrupt(digitalPinToInterrupt(3), countRight, RISING);

}
int16_t returnLeftEncoder(){
    return EncoderValueLeft;
}
int16_t returnRightEncoder(){
    return EncoderValueRight;
}
