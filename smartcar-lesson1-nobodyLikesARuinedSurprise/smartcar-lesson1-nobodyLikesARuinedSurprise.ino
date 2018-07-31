/*  ___   ___  ___  _   _  ___   ___   ____ ___  ____  
 * / _ \ /___)/ _ \| | | |/ _ \ / _ \ / ___) _ \|    \ 
 *| |_| |___ | |_| | |_| | |_| | |_| ( (__| |_| | | | |
 * \___/(___/ \___/ \__  |\___/ \___(_)____)___/|_|_|_|
 *                  (____/ 
 * Arduino Smart Car Tutorial Lesson 1
 * Tutorial URL http://osoyoo.com/2017/04/23/arduinosmartcarlesson1/
 * CopyRight www.osoyoo.com

 * After running the code, smart car will go forward 5 seconds, then go backward 5
 * seconds, then left turn for 5 seconds then right turn for 5 seconds then stop. 
 * 
 */
 
#include "configuration.h"

/*motor control*/
void go_Advance(void)  //Forward
{
}
void go_Left(void)  //Turn left
{
}
void go_Right(void)  //Turn right
{
}
void go_Back(void)  //Reverse
{
}
void stop_Stop()    //Stop
{
}

/*set motor speed */
void set_Motorspeed(int speed_L,int speed_R)
{
  //digital or analog? (what pin?,what value?);
  //hint: 2 pins
}

//Pins initialize
void init_GPIO()
{
	pinMode(dir1PinL, OUTPUT); 
	pinMode(dir2PinL, OUTPUT); 
	pinMode(speedPinL, OUTPUT);  
 
	pinMode(dir1PinR, OUTPUT);
  pinMode(dir2PinR, OUTPUT); 
  pinMode(speedPinR, OUTPUT); 
	stop_Stop();
}

//Doug: Use this script to test your 'go_' functions above
void setup()
{
	init_GPIO();
	go_Advance();//Forward ter
  set_Motorspeed(255,255);
  delay(5000);
  
  go_Back();//Reverse
  set_Motorspeed(255,255);
  delay(5000);
  
  go_Left();//Turn left
  set_Motorspeed(255,255);
  delay(5000);
  
  go_Right();//Turn right
  set_Motorspeed(255,255);
  delay(5000);
  
  stop_Stop();//Stop

}

void loop(){
  //Tell your robot to do your own commands here
}

