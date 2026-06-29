#include <Wire.h>
#include <MPU6050_light.h>

MPU6050 mpu(Wire);

unsigned long timer = 0;

void setup () {
  Serial.begin(115200);
  Wire.begin();

  byte status = mpu.begin();
  Serial.print("status mpu 6050 : ");
  Serial.println(status);

  while(status != 0) {}

  Serial.print("Menghitung gyro offset, jangan gerakkan mpu6050");
  delay(1000);

  mpu.calcOffsets(true, true);
  Serial.println("kalibrasi selesai ");
}


void loop() {
  mpu.update();

  if(millis() - timer > 10 ) {
    
    float roll  = mpu.getAngleY();
    float pitch = mpu.getAngleX();
    float yaw   = mpu.getAngleZ();

    Serial.print("Roll :" ); Serial.print(roll); Serial.print("|");
    Serial.print("Pitch  :" ); Serial.print(pitch); Serial.print("|");
    Serial.print("Yaw :" ); Serial.print(yaw); Serial.print("\n");
  } 
  delay(20);
}