#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "Wire.h"
TwoWire Wire2(PB_6, PB_7);
HardwareSerial Serial3(PB_11, PB_10);
MPU6050 mpu;
uint8_t devStatus; 
bool dmpReady = false; 
Quaternion q; 
VectorInt16 aa;  
VectorInt16 aaReal; 
VectorInt16 aaWorld;  
VectorFloat gravity; 
float ypr[3];  
uint8_t fifoBuffer[64];
void setup() {
  // put your setup code here, to run once:
Wire2.begin();
Serial3.begin(115200);
mpu.initialize();
devStatus=mpu.dmpInitialize();
mpu.setXGyroOffset(51);
mpu.setYGyroOffset(8);
mpu.setZGyroOffset(21);
mpu.setXAccelOffset(1150);
mpu.setYAccelOffset(-50);
mpu.setZAccelOffset(1060);
if (devStatus == 0) {
    // Calibration Time: generate offsets and calibrate our MPU6050
    mpu.CalibrateAccel(6);
    mpu.CalibrateGyro(6);
     dmpReady = true;
        }
        
 else
 Serial3.print("DMP Initialization failed ");
    
}

void loop() {
  // put your main code here, to run repeatedly:
if (!dmpReady) return;
if (mpu.dmpGetCurrentFIFOPacket(fifoBuffer)) {
  mpu.dmpGetQuaternion(&q, fifoBuffer);
  mpu.dmpGetGravity(&gravity, &q);
  mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
  Serial3.print("ypr\t");
  Serial3.print(ypr[0] * 180/M_PI);
  Serial3.print("\t");
  Serial3.print(ypr[1] * 180/M_PI);
  Serial3.print("\t");
  Serial3.println(ypr[2] * 180/M_PI);
}

}
