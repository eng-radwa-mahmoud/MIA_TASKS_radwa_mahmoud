#include <ros.h>
#include <std_msgs/Int32.h>
ros::NodeHandle encoder;
  std_msgs::Int32 int_msg;
 ros::Publisher chatter("counts_encoder", &int_msg);
long long counter1=0;
void ISRA1() 
{
  if (digitalRead(PB_0)==digitalRead(PB_7))//check if encoder is moving clockwise or counter clockwise
    counter1++;//increase the counter in case the encoder moving clockwise
    else
    counter1--;//decrease the counter in case the encoder moving counter clockwise
}
void ISRB1 () 
  {
    if (digitalRead(PA_0)!=digitalRead(PA_7))//check if encoder is moving clockwise or counter clockwise
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
  encoder.initNode();
  encoder.advertise(chatter);
}

void loop() {
  // put your main code here, to run repeatedly:
  int_msg.data=counter1;
  chatter.publish( &int_msg );
  encoder.spinOnce();

}
