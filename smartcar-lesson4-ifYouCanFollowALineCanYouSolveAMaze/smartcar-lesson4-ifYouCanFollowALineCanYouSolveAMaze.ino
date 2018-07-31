 #include "configuration.h"
 char sensor[5];
 /*read sensor value string, 1 stands for black, 0 starnds for white, i.e 10000 means the first sensor(from left) detect black line, other 4 sensors detected white ground */
String read_sensor_values()
{   int sensorvalue=32;
  sensor[0]= digitalRead(LFSensor_0);
 
  sensor[1]=digitalRead(LFSensor_1);
 
  sensor[2]=digitalRead(LFSensor_2);
 
  sensor[3]=digitalRead(LFSensor_3);
 
  sensor[4]=digitalRead(LFSensor_4);
  sensorvalue +=sensor[0]*16+sensor[1]*8+sensor[2]*4+sensor[3]*2+sensor[4];
 
  String senstr= String(sensorvalue,BIN);
  return senstr.substring(1,6);
}

void go_Advance(void)  //Forward
{
  digitalWrite(dir1PinL, HIGH);
  digitalWrite(dir2PinL,LOW);
  digitalWrite(dir1PinR,HIGH);
  digitalWrite(dir2PinR,LOW);
}
void go_Left(void)  //Turn left
{
  digitalWrite(dir1PinL, HIGH);
  digitalWrite(dir2PinL,LOW);
  digitalWrite(dir1PinR,LOW);
  digitalWrite(dir2PinR,HIGH);
}
void go_Right(void)  //Turn right
{
  digitalWrite(dir1PinL, LOW);
  digitalWrite(dir2PinL,HIGH);
  digitalWrite(dir1PinR,HIGH);
  digitalWrite(dir2PinR,LOW);
}
void go_Back(void)  //Reverse
{
  digitalWrite(dir1PinL, LOW);
  digitalWrite(dir2PinL,HIGH);
  digitalWrite(dir1PinR,LOW);
  digitalWrite(dir2PinR,HIGH);
}
void stop_Stop()    //Stop
{
  digitalWrite(dir1PinL, LOW);
  digitalWrite(dir2PinL,LOW);
  digitalWrite(dir1PinR,LOW);
  digitalWrite(dir2PinR,LOW);
}
/*set motor speed */
void set_Motorspeed(int speed_L,int speed_R)
{
  analogWrite(speedPinL,speed_L); 
  analogWrite(speedPinR,speed_R);   
}

void setup()
{
 pinMode(speedPinL,OUTPUT); //left motor PWM pin
 pinMode(speedPinR,OUTPUT); //rignt motor PWM  pin
 pinMode(dir1PinL,OUTPUT); //left motor direction pin1
 pinMode(dir2PinL,OUTPUT); //left motor direction pin2
 pinMode(dir1PinR,OUTPUT); //right motor direction Pin 1
 pinMode(dir2PinR,OUTPUT);  //right motor direction Pin 2

  /*line follow sensors */
 pinMode(LFSensor_0,INPUT);
 pinMode(LFSensor_1,INPUT);
 pinMode(LFSensor_2,INPUT);
 pinMode(LFSensor_3,INPUT);
 pinMode(LFSensor_4,INPUT); 
 Serial.begin(9600);
}

void auto_tracking(){
 String sensorval= read_sensor_values();
 if (sensorval=="00100" or sensorval=="01100" or sensorval=="11100" or sensorval=="11000" or sensorval=="10000"  or sensorval=="01000")
 { 
  //The black line is in the left of the car, need  left turn 
      go_Left();  //Turn left
    set_Motorspeed(0,SPEED);
    }

 if (sensorval=="00110" or sensorval=="00111" or sensorval=="00011" or sensorval=="00001"  or sensorval=="00010" ){ //The black line is  on the right of the car, need  right turn 
  
     go_Right();  //Turn right
       set_Motorspeed(SPEED,0);
    }
 
 if (sensorval=="11111" or sensorval=="01111" or sensorval=="11110"){
     stop_Stop();   //The car front touch stop line, need stop
     set_Motorspeed(0,0);
    }
}

void loop(){
 
auto_tracking();
}

