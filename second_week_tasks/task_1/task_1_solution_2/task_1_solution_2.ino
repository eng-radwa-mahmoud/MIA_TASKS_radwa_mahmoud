#include <MPU6050_light.h>

 #include <Wire.h>
 MPU6050 mpu(Wire);
HardwareSerial Serial3(PB_11, PB_10);

void setup() {
  // put your setup code here, to run once:
 Serial3.begin(115200);
 Wire.begin();
 mpu.begin();
 mpu.calcGyroOffsets();  
}

void loop() {
  // put your main code here, to run repeatedly:
   mpu.update();
   Serial3.print("P : ");
     Serial3.println(mpu.getAngleX());
     Serial3.print("R : ");
     Serial3.println(mpu.getAngleY());
     Serial3.print("Y : ");
     Serial3.println(mpu.getAngleZ());

}
