#include <ros.h>
#include <std_msgs/Int32.h>
ros::NodeHandle v_subscriber;
long long int set_point;
void messageCb(const std_msgs::Int32::ConstPtr& msg);
long long counter1=0;
ros::Subscriber<std_msgs::Int32> sub("set_point", messageCb ); 
long int current_speed;
long int current_error=0,sum_error=0,previous_error=0,delta_error=0,pwm=0;
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
  if ((millis()-prev_time)>200)
  { prev_time=millis();
    current_speed=(((counter1*60))/.2)/512;
    counter1=0;
    current_error=set_point-current_speed;
    sum_errror=sum_error+current_error;
    delta_error=current_error-previous_error;
    previous_error=current_error;
    pwm=.2*current_error+.5*sum_error+.8*delta_error;
    digitalWrite(PA_1,HIGH);
    digitalWrite(PA_1,LOW);
    if (abs(pwm)>255)
     analogWrite(PA_0,255);
     else
    analogWrite(PA_0,abs(pwm));
  }
  
  v_subscriber.spinOnce();
  
}
void messageCb(const std_msgs::Int32::ConstPtr& msg)
{
 set_point= msg->data.c_int();
}
