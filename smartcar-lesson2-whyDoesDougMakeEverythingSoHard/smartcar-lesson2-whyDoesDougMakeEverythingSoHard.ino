
/*  ___   ___  ___  _   _  ___   ___   ____ ___  ____  
 * / _ \ /___)/ _ \| | | |/ _ \ / _ \ / ___) _ \|    \ 
 *| |_| |___ | |_| | |_| | |_| | |_| ( (__| |_| | | | |
 * \___/(___/ \___/ \__  |\___/ \___(_)____)___/|_|_|_|
 *                  (____/    
 * www.osoyoo.com IR remote control smart car
 * program tutorial : http://osoyoo.com/2017/04/16/control-smart-car-with-ir/
 *  Copyright John Yu
 */
#include <IRremote.h>
#include "configuration.h"
                                                                                            
 IRrecv IR(IR_PIN);  //   IRrecv object  IR get code from IR remoter
 decode_results IRresults;   

/***************motor control***************/
void go_Advance(void)  //Forward
{
}
void go_Left(int t=0)  //Turn left
{
}
void go_Right(int t=0)  //Turn right
{
}
void go_Back(int t=0)  //Reverse
{
}
void stop_Stop()    //Stop
{
}

/**************detect IR code***************/
void do_IR_Tick()
{
  if(IR.decode(&IRresults))
  {
    if(IRresults.value==IR_ADVANCE)
    {
      //How would you make the robot advance?
    }
    else if(IRresults.value==IR_RIGHT)
    {
       //go right?
    }
    else if(IRresults.value==IR_LEFT)
    {
       //maybe this involves the drive?
    }
    else if(IRresults.value==IR_BACK)
    {
        //how is that controlled?
    }
    else if(IRresults.value==IR_STOP)
    {
        //maybe some kind of num?
    }
    IRresults.value = 0;
    IR.resume();
  }
}

/**************car control**************/
void do_Drive_Tick()
{
    switch (Drive_Num) 
    {
      case GO_ADVANCE:go_Advance();JogFlag = true;JogTimeCnt = 1;JogTime=millis();break;//if GO_ADVANCE code is detected, then go advance
      //if GO_LEFT code is detected, then turn left
      //if GO_RIGHT code is detected, then turn right
      //if GO_BACK code is detected, then backward
      //stop
      default:break;
    }
    Drive_Num=DEF;
   //keep current moving mode for  200 millis seconds
    if(millis()-JogTime>=200)
    {
      JogTime=millis();
      if(JogFlag == true) 
      {
        stopFlag = //do we want to stop while we're jogging?
        if(JogTimeCnt <= 0) 
        {
          JogFlag = //are we stopped or jogging when JogTimeCnt <=0? 
          stopFlag = //how would we set these flags to accomplish that?
        }
        JogTimeCnt--;
      }
      if(stopFlag == //hmmmmmmmmmm......)
      {
        JogTimeCnt=0;
        stop_Stop();
      }
    }
}

void setup()
{
  pinMode(dir1PinL, OUTPUT); 
  pinMode(dir2PinL, OUTPUT); 
  pinMode(speedPinL, OUTPUT);  
  pinMode(dir1PinR, OUTPUT);
  pinMode(dir2PinR, OUTPUT); 
  pinMode(speedPinR, OUTPUT); 
  stop_Stop();

  pinMode(IR_PIN, INPUT); 
  digitalWrite(IR_PIN, HIGH);  
  IR.enableIRIn();       
}


void loop()
{
  do_IR_Tick();
  do_Drive_Tick();
}
