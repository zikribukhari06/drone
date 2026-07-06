#include <Wire.h>
#include <MPU6050_light.h>

MPU6050 mpu(Wire);

unsigned long timer = 0;

void setup () {
  Serial.begin(115200);
  Wire.begin();

  byte status = mpu.begin();
  Serial.print("status mpu 6050 : ");
  Serial.println(status); // status menjunjukan kondisi error dari mpu, maka akan benilai 1 ketika error dan 0 ketika berhasil di inisialisasi

  while(status != 0) {
    Serial.println("MPU gagal diinisialisasikan.....");
    delay(1000);
  } // jika status bernilai 1 maka program akan mengalami loop sampai program status bernilai 0

  Serial.print("Menghitung gyro offset, jangan gerakkan mpu6050");
  delay(1000);
  
  mpu.calcOffsets(true, true); //(gyro, acc), nilai true dan false menunujukan apakah keduanya ingin dikalibrasi atau tidak, true jika iya.
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
