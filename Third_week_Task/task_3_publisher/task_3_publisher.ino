#include <ros.h>
#include <std_msgs/Int32.h>
ros::NodeHandle v_publish;
  std_msgs::Int32 int_msg;
 ros::Publisher chatter("set_point", &int_msg);
 long int set_speed=100;
void setup() {
  // put your setup code here, to run once:
 v_publish.initNode();
  v_publish.advertise(chatter);
}

void loop() {
  // put your main code here, to run repeatedly:
  int_msg.data=set_speed;
  chatter.publish( &int_msg );
  v_publish.spinOnce();

}
