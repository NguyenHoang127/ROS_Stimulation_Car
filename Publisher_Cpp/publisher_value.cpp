//Library ROS
#include "ros/ros.h"
#include "std_msgs/Float64.h"
#include "std_msgs/Int32.h"

//Library Raspberry
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<stdint.h>
#include<setjmp.h>

#include <wiringPi.h>
#include <wiringSerial.h>

//------------------------------------------------------------------------------------------------
char value;
int fd;
jmp_buf jumb;

//-----------------------------------------------------------------------------------------------
char State_Receive[1];
char Level_Receive[1];
char Value_X[5];
char ALL_BIT[8];

int32_t State_Int;
int32_t Level_Int;
int32_t Value_X_int;
int32_t Value_Y_int;

float wheel1 = 0.0;
float wheel2 = 0.0;
float wheel3 = 0.0;
float wheel4 = 0.0;

void Receive_Data()
{
    State_Receive[0] = serialGetchar(fd);
    State_Int = atoi(State_Receive);
    
    Level_Receive[0] = serialGetchar(fd);
    Level_Int = 2.0*atoi(Level_Receive);

    ALL_BIT[0] = serialGetchar(fd);
    ALL_BIT[1] = serialGetchar(fd);
    ALL_BIT[2] = serialGetchar(fd);
    ALL_BIT[3] = serialGetchar(fd);

    ALL_BIT[4] = serialGetchar(fd);
    ALL_BIT[5] = serialGetchar(fd);
    ALL_BIT[6] = serialGetchar(fd);
    ALL_BIT[7] = serialGetchar(fd);

    strncpy(Value_X,ALL_BIT,4);
    Value_X[4] ='\0';

    Value_X_int = atoi(Value_X);
    Value_Y_int = atoi(ALL_BIT+4);
}

void Joystick()
{
  if(State_Int == 1)
  {
    //Stop
    if((Value_X_int >= 400) && (Value_X_int <= 600))
    {
        wheel1  = 0.0;
        wheel2  = 0.0;
        wheel3  = 0.0;
        wheel4  = 0.0;
    }
    if((Value_Y_int >= 400) && (Value_Y_int <= 600))
    {
        wheel1  = 0.0;
        wheel2  = 0.0;
        wheel3  = 0.0;
        wheel4  = 0.0;
    }

    //Forward
    if(Value_X_int > 600 && (400 <= Value_Y_int <= 600))     
    {
        wheel1 =  2.0*Level_Int;
        wheel2 =  2.0*Level_Int;  
        wheel3 =  -2.0*Level_Int;  
        wheel4 =  -2.0*Level_Int;  
    }
    if(Value_X_int > 700 && (400 <= Value_Y_int <= 600))     
    {
        wheel1 =  4.0*Level_Int;
        wheel2 =  4.0*Level_Int;  
        wheel3 =  -4.0*Level_Int;  
        wheel4 =  -4.0*Level_Int;  
    }

    if(Value_X_int > 800 && (400 <= Value_Y_int <= 600))     
    {
        wheel1 =  6.0*Level_Int;
        wheel2 =  6.0*Level_Int;  
        wheel3 =  -6.0*Level_Int;  
        wheel4 =  -6.0*Level_Int;  
    }

    if(Value_X_int > 900 && (400 <= Value_Y_int <= 600))     
    {
        wheel1 =  8.0*Level_Int;
        wheel2 =  8.0*Level_Int;  
        wheel3 =  -8.0*Level_Int;  
        wheel4 =  -8.0*Level_Int;  
    }

    //Backward
    if(Value_X_int < 400 && (400 <= Value_Y_int <= 600))   
    {
        wheel1 =  -2.0*Level_Int;
        wheel2 =  -2.0*Level_Int;  
        wheel3 =   2.0*Level_Int;  
        wheel4 =   2.0*Level_Int;  
    }
    if(Value_X_int < 300 && (400 <= Value_Y_int <= 600))   
    {
        wheel1 =  -4.0*Level_Int;
        wheel2 =  -4.0*Level_Int;  
        wheel3 =   4.0*Level_Int;  
        wheel4 =   4.0*Level_Int;  
    }
    if(Value_X_int < 200 && (400 <= Value_Y_int <= 600))   
    {
        wheel1 =  -6.0*Level_Int;
        wheel2 =  -6.0*Level_Int;  
        wheel3 =   6.0*Level_Int;  
        wheel4 =   6.0*Level_Int;  
    }
    if(Value_X_int < 100 && (400 <= Value_Y_int <= 600))   
    {
        wheel1 =  -8.0*Level_Int;
        wheel2 =  -8.0*Level_Int;  
        wheel3 =   8.0*Level_Int;  
        wheel4 =   8.0*Level_Int;  
    }

    //Xoay Tai Cho
    if(Value_Y_int > 600 && (400 <= Value_X_int <= 600))
    {
        wheel1 =  1.0*Level_Int;
        wheel2 =  1.0*Level_Int; 
        wheel3 =  1.0*Level_Int; 
        wheel4 =  1.0*Level_Int; 
    }
    if(Value_Y_int > 700 && (400 <= Value_X_int <= 600))
    {
        wheel1 =  2.0*Level_Int;
        wheel2 =  2.0*Level_Int; 
        wheel3 =  2.0*Level_Int; 
        wheel4 =  2.0*Level_Int; 
    }
    if(Value_Y_int > 800 && (400 <= Value_X_int <= 600))
    {
        wheel1 =  3.0*Level_Int;
        wheel2 =  3.0*Level_Int; 
        wheel3 =  3.0*Level_Int; 
        wheel4 =  3.0*Level_Int; 
    }
    if(Value_Y_int > 900 && (400 <= Value_X_int <= 600))
    {
        wheel1 =  4.0*Level_Int;
        wheel2 =  4.0*Level_Int; 
        wheel3 =  4.0*Level_Int; 
        wheel4 =  4.0*Level_Int; 
    }
    if(Value_Y_int < 400 && (400 <= Value_X_int <= 600))
    {
        wheel1 =  -1.0*Level_Int;
        wheel2 =  -1.0*Level_Int; 
        wheel3 =  -1.0*Level_Int; 
        wheel4 =  -1.0*Level_Int; 
    }
    if(Value_Y_int < 300 && (400 <= Value_X_int <= 600))
    {
        wheel1 =  -2.0*Level_Int;
        wheel2 =  -2.0*Level_Int; 
        wheel3 =  -2.0*Level_Int; 
        wheel4 =  -2.0*Level_Int; 
    }
    if(Value_Y_int < 200 && (400 <= Value_X_int <= 600))
    {
        wheel1 =  -3.0*Level_Int;
        wheel2 =  -3.0*Level_Int; 
        wheel3 =  -3.0*Level_Int; 
        wheel4 =  -3.0*Level_Int; 
    }
    if(Value_Y_int < 100 && (400 <= Value_X_int <= 600))
    {
        wheel1 =  -4.0*Level_Int;
        wheel2 =  -4.0*Level_Int; 
        wheel3 =  -4.0*Level_Int; 
        wheel4 =  -4.0*Level_Int; 
    }

    //Re trai, phai:
    if(Value_X_int > 600 && Value_Y_int > 600)
    {
        wheel1 =  8.0*Level_Int;
        wheel2 =  8.0*Level_Int; 
        wheel3 =  -3.0*Level_Int; 
        wheel4 =  -3.0*Level_Int; 
    }
    if(Value_X_int > 600 && Value_Y_int < 400)
    {
        wheel1 =  3.0*Level_Int;
        wheel2 =  3.0*Level_Int; 
        wheel3 =  -8.0*Level_Int; 
        wheel4 =  -8.0*Level_Int; 
    }
  }
}

void mainControl(void)
{
    wiringPiSetup();
    fd = serialOpen("/dev/ttyAMA0",115200);
}

int main(int argc, char **argv)
{
  mainControl();

  ros::init(argc, argv, "Publisher");

  ros::NodeHandle n;

  ros::Publisher topic_pub1 = n.advertise<std_msgs::Float64>("/robot4wd_/wheel1_controller/command", 1000);
  ros::Publisher topic_pub2 = n.advertise<std_msgs::Float64>("/robot4wd_/wheel2_controller/command", 1000);
  ros::Publisher topic_pub3 = n.advertise<std_msgs::Float64>("/robot4wd_/wheel3_controller/command", 1000);
  ros::Publisher topic_pub4 = n.advertise<std_msgs::Float64>("/robot4wd_/wheel4_controller/command", 1000);


  ros::Publisher topic_pub5 = n.advertise<std_msgs::Int32>("/my_diffbot/value_x", 1000);
  ros::Publisher topic_pub6 = n.advertise<std_msgs::Int32>("/my_diffbot/value_y", 1000);
  
  ros::Publisher topic_pub7 = n.advertise<std_msgs::Int32>("/my_diffbot/state", 1000);
  ros::Publisher topic_pub8 = n.advertise<std_msgs::Int32>("/my_diffbot/level", 1000);

  ros::Rate loop_rate(10);

  while (ros::ok())
  {
    if(serialGetchar(fd)==23)
    {
      Receive_Data();
      Joystick();

      //Setup
      std_msgs::Float64 data_car1;
      std_msgs::Float64 data_car2;
      std_msgs::Float64 data_car3;
      std_msgs::Float64 data_car4;
      
      std_msgs::Int32 value_x_msg;
      std_msgs::Int32 value_y_msg;

      std_msgs::Int32 state_msg;
      std_msgs::Int32 level_msg;

      data_car1.data = wheel1;
      data_car2.data = wheel2;
      data_car3.data = wheel3;
      data_car4.data = wheel4;
      
      //Connect Data
      value_x_msg.data = Value_X_int;
      value_y_msg.data = Value_Y_int;

      state_msg.data = State_Int;
      level_msg.data = Level_Int;

      //Show Data
      topic_pub1.publish(data_car1);
      topic_pub2.publish(data_car2);
      topic_pub3.publish(data_car3);
      topic_pub4.publish(data_car4);

      topic_pub3.publish(value_x_msg);
      topic_pub4.publish(value_y_msg);

      topic_pub5.publish(state_msg);
      topic_pub6.publish(level_msg);

      ros::spinOnce();
    }
  }
  serialClose(fd);
  return 0;
}