#include <ros.h>
#include <std_msgs/Int32.h>
ros::NodeHandle v_subscriber;
long long int set_point;
void messageCb(const std_msgs::int::ConstPtr& msg);
long long counter1=0;
ros::Subscriber<std_msgs::Int32> sub("set_point", &messageCb ); 
void ISRA1() 
{
  if (digitalRead(PB_0)==digitalRead(PA_7))//check if encoder is moving clockwise or counter clockwise
    counter1++;//increase the counter in case the encoder moving clockwise
    else
    counter1--;//decrease the counter in case the encoder moving counter clockwise
}
void ISRB1 () 
  {
    if (digitalRead(PB_0)!=digitalRead(PA_7))//check if encoder is moving clockwise or counter clockwise
   counter1--;//increase the counter in case the encoder moving clockwise
  else
  counter1++;
  }
void setup() {
  // put your setup code here, to run once:
  pinMode(PB_0,INPUT_PULLUP);
  pinMode(PA_7,INPUT_PULLUP);
  attachInterrupt(PB_0,ISRA1,CHANGE);
  attachInterrupt(PA_7,ISRB1,CHANGE);
  v_subscriber.initNode();
  v_subscriber.subscribe(sub);
  
}

void loop() {
  // put your main code here, to run repeatedly:
}
  v_subscriber.spinOnce();

}
void messageCb(const std_msgs::int::ConstPtr& msg)
{
 set_point= msg->data.c_int();
}
