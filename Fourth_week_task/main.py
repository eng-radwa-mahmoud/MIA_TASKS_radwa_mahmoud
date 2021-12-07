#!/usr/bin/env python
import time
from time import sleep

import rospy
from std_msgs.msg import Int32
z=0 #sensor reading
prev_time=0
current_time=0
delta_yaw=0
q=2 #process varience
r=5 #sensor varience
pred_yaw_angle=0
k=3 #kalman_gain

def math_model():
    listener()
    yaw_angle1=z
    time.sleep(.01)
    listener()
    yaw_angle2=z
    delta_yaw=yaw_angle2-yaw_angle1
    

def callback(data):
    z = data.data
def listener():
    rospy.init_node('listener', anonymous=True)
    rospy.Subscriber("yaw_angle", Int32, callback)
    rospy.spin()
   


def initialize():
    yaw_angle = 0
    probability = 3
    return yaw_angle , probability

def predict(yaw_angle , probability):
    prev_time=time.time()
    dt=(time.time()-prev_time)
    pred_yaw_nagle= yaw_angle + ((dt*delta_yaw)/.01)          # State Transition Equation (Dynamic Model or Prediction Model)
    probability = probability + q       # Predicted Covariance equation
    return pred_yaw_angle, probability

def measure():
    sensor_reading=z
    return sensor_reading

def update(probability, sensor_reading):
    k = probability / ( probability + r)                # Kalman Gain
    yaw_angle= pred_yaw_angle + k * (sensor_reading - pred_yaw_angle)             # State Update
    probability = (1 - k) * probability                # Covariance Update
    return yaw_angle, probability

def runKalmanFilter():
    yaw_angle, probability  = initialize()

    while 1:
        listener()
        pred_yaw_angle, probability= predict(yaw_angle, probability )
        sensor_reading = measure()
        yaw_angle, probability  = update(probability , sensor_reading)
if __name__ == '__main__':
    math_model()
    runKalmanFilter()


