  #include <Servo.h>
#include "configuration.h"

Servo head;
/*motor control*/
void go_Advance(void)  //Forward
{
//yes I'm going to make you do this again.  When you read this comment know I was twirling my moustache like a disney villain the whole time I wrote it.
}
void go_Left()  //Turn left
{
  //mwa
}
void go_Right()  //Turn right
{
  //ha
}
void go_Back()  //Reverse
{
//ha
}
void stop_Stop()    //Stop
{
//ha
}

/*set motor speed */
void set_Motorspeed(int speed_L,int speed_R)
{
  //hmm I wonder if you remember how to do this
}

void buzz_ON()   //open buzzer
{
  //which way is open?
}
void buzz_OFF()  //close buzzer
{
  //guess you'll have to find out!
}
void alarm(){
   //If only there were a way to tell arduino to turn a buzzer on, delay for a bit, and then turn it off
}

/*detection of ultrasonic distance*/
int watch(){
  long echo_distance;
  digitalWrite(Trig_PIN,LOW);
  delayMicroseconds(5);                                                                              
  digitalWrite(Trig_PIN,HIGH);
  delayMicroseconds(15);
  digitalWrite(Trig_PIN,LOW);
  echo_distance=pulseIn(Echo_PIN,HIGH);
  echo_distance=echo_distance*0.01657; //how far away is the object in cm
  //Serial.println((int)echo_distance);
  return round(echo_distance);
}
//Measures distances to the right, left, front, left diagonal, right diagonal and asign them in cm to the variables rightscanval, 
//leftscanval, centerscanval, ldiagonalscanval and rdiagonalscanval (there are 5 points for distance testing)
String watchsurrounding(){
/*  obstacle_status is a binary integer, its last 5 digits stands for if there is any obstacles in 5 directions,
 *   for example B101000 last 5 digits is 01000, which stands for Left front has obstacle, B100111 means front, right front and right ha
 */
 
int obstacle_status =B100000;
  centerscanval = watch();
  if(centerscanval<distancelimit){
    stop_Stop();
    alarm();
    obstacle_status  =obstacle_status | B100;
    }
  head.write(120);
  delay(100);
  ldiagonalscanval = watch();
  if(ldiagonalscanval<distancelimit){
    stop_Stop();
    alarm();
     obstacle_status  =obstacle_status | B1000;
    }
  head.write(170); //Didn't use 180 degrees because my servo is not able to take this angle
  delay(300);
  leftscanval = watch();
  if(leftscanval<sidedistancelimit){
    stop_Stop();
    alarm();
     obstacle_status  =obstacle_status | B10000;
    }
  head.write(120);
  delay(100);
  ldiagonalscanval = watch();
  if(ldiagonalscanval<distancelimit){
    stop_Stop();
    alarm();
    obstacle_status  =obstacle_status | B1000;
    }
  head.write(90); //use 90 degrees if you are moving your servo through the whole 180 degrees
  delay(100);
  centerscanval = watch();
  if(centerscanval<distancelimit){
    stop_Stop();
    alarm();
    obstacle_status  =obstacle_status | B100;
    }
  head.write(40);
  delay(100);
  rdiagonalscanval = watch();
  if(rdiagonalscanval<distancelimit){
    stop_Stop();
    alarm();
    obstacle_status  =obstacle_status | B10;
    }
  head.write(0);
  delay(100);
  rightscanval = watch();
  if(rightscanval<sidedistancelimit){
    stop_Stop();
    alarm();
    obstacle_status  =obstacle_status | 1;
    }
  head.write(90); //Finish looking around (look forward again)
  delay(300);
   String obstacle_str= String(obstacle_status,BIN);
  obstacle_str= obstacle_str.substring(1,6);
  
  return obstacle_str; //return 5-character string standing for 5 direction obstacle status
}

void auto_avoidance(){
  set_Motorspeed(SPEED,SPEED);
  go_Advance();  // if nothing is wrong go forward using go() function above.
  ++numcycles;
  if(numcycles>=80){ //Watch if something is around every 100 loops while moving forward 
     stop_Stop();
    String obstacle_sign=watchsurrounding(); // 5 digits of obstacle_sign binary value means the 5 direction obstacle status
      Serial.print("begin str=");
        Serial.println(obstacle_sign);
    if( obstacle_sign=="11100" || obstacle_sign=="11000"  || obstacle_sign=="10100"  || obstacle_sign=="01100"  || obstacle_sign=="01110" ||obstacle_sign=="00100"  ||obstacle_sign=="01000" ){
      go_Right();
      delay(turntime);
      stop_Stop();
    }
    if(obstacle_sign=="00111" || obstacle_sign=="00011"  || obstacle_sign=="00101" || obstacle_sign=="00110" || obstacle_sign=="01010"  || obstacle_sign=="00010"  ){
      go_Left();
      delay(turntime);
      stop_Stop();
    }
 
    if(  obstacle_sign=="01111" ||  obstacle_sign=="10111" ||  obstacle_sign=="11011" ||  obstacle_sign=="11101"  ||  obstacle_sign=="11110"  ){
          go_Back();
		  set_Motorspeed(BACK_SPEED1,BACK_SPEED2);
       delay(backtime);
          stop_Stop();
        }
    numcycles=0; //Restart count of cycles
  }
  distance = watch(); // use the watch() function to see if anything is ahead (when the robot is just moving forward and not looking around it will test the distance in front)
  if (distance<distancelimit){ // The robot will just stop if it is completely sure there's an obstacle ahead (must test 25 times) (needed to ignore ultrasonic sensor's false signals)
  go_Back();
      ++thereis;}
  if (distance>distancelimit){
      thereis=0;} //Count is restarted
  if (thereis > 25){
    stop_Stop(); // Since something is ahead, stop moving.
    thereis=0;
  }
}

void setup() {
  /*setup L298N pin mode*/
  pinMode(dir1PinL, OUTPUT); 
  pinMode(dir2PinL, OUTPUT); 
  pinMode(speedPinL, OUTPUT);  
  pinMode(dir1PinR, OUTPUT);
  pinMode(dir2PinR, OUTPUT); 
  pinMode(speedPinR, OUTPUT); 
  stop_Stop();//stop move
  /*init HC-SR04*/
  pinMode(Trig_PIN, OUTPUT); 
  pinMode(Echo_PIN,INPUT); 
  /*init buzzer*/
  pinMode(BUZZ_PIN, OUTPUT);
  digitalWrite(BUZZ_PIN, HIGH);  
  buzz_OFF(); 

  digitalWrite(Trig_PIN,LOW);
  /*init servo*/
  head.attach(SERVO_PIN); 
  head.write(90);
   delay(4000);
   
  /*baud rate*/
  Serial.begin(9600);

}

void loop() {
 auto_avoidance();
}

