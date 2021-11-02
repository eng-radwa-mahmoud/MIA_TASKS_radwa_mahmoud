unsigned long long int accx,accy,accz;
HardwareSerial Serial3(PB_11, PB_10);
#include<Wire.h>
TwoWire Wire2(PB_6, PB_7);
  void setIMUregister(unsigned int reg,unsigned int val)//function  used to initialize imu and configure  Accelerometer
{
  Wire2.beginTransmission(0x68);//begin i2c communication with the imu , 0x68:address of imu
  Wire2.write(reg);
  Wire2.write(val);
  Wire2.endTransmission();
}
void readIMUacc () //function to read  Accelerometerreading in direction of x ,y ,z axes
{
Wire2.beginTransmission(0x68);
Wire2.write(0x3B);//0x3B:register to satrt taking data from
Wire2.endTransmission();
Wire2.requestFrom(0x68,6);//request 6 bytes from the imu starrting from 0x3B location
while(Wire.available()<6)
{
  accx=(Wire2.read()<<8)|(Wire2.read());
  accy=(Wire2.read()<<8)|(Wire2.read());
  accz=(Wire2.read()<<8)|(Wire2.read());
}
}
void calibrate_acc()//function to calibrate the readings of  Accelerometer and calculate the final result
{ unsigned long long accxofset=0;
  unsigned long long accyofset=0;
  unsigned long long acczofset=0;
  //loop to take many reading of  Accelerometer
  for (int i=0;i<5000;i++) 
  {
    readIMUacc();//cal of function to calcute the reading of  Accelerometer
    accxofset+=accx;
    accyofset+=accy;
    acczofset+=accz;   
  }
  //calculate the average of readings:
  accxofset/=5000;
  accyofset/=5000;
  acczofset/=5000;
  //mappinng the readings of the  Accelerometer to the actual values:
  accx=(accxofset*16)/32767;
  accy=(accxofset*16)/32767;
  accz=(accxofset*16)/32767;  
}
void setup() {
  Serial3.begin(115200);
  setIMUregister(0x6B,0x00);// call of function to initialize the imu
  setIMUregister(0x1C,0x18);//call of function to configure the  Accelerometer
  

}

void loop() {
  
  
  calibrate_acc();//call of function to calculate and calibrate the readings of  Accelerometer
  int pitch=180*atan2(accx,sqrt(accy*accy+accz*accz))/PI;//equation to calculate the pitch angle
  int roll=180*atan2(accy,sqrt(accx*accx+accz*accz))/PI;//equation to calculate the roll angle
  int yaw=180*atan2(accz,sqrt(accx*accx+accy*accy))/PI;//equation to calculate the yaw angle
  Serial3.print("pitch=");
  Serial3.println(pitch,DEC);
  Serial3.print("roll=");
  Serial3.println(roll,DEC);
  Serial3.print("yaw=");
  Serial3.println(yaw,DEC);
}
