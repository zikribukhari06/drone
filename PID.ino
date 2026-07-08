#include <Wire.h>
#include <MPU6050_light.h>

MPU6050 mpu(Wire);

float waktu_lama = 0;
float Kp = 5;
float Ki = 0.1;
float Kd = 0.3;
float point_set = 0;
float Error_lama = 0;
float sigma_Error = 0;
float selisih_Error = 0;
unsigned long timer = 0; // variabel penampung waktu 
unsigned long awal = 0; // variabel penampung waktu loop pertama kali di mulai
const unsigned long batas = 100000; // membatasi siklus perhitungan PID dalam micro second
float dt = 0;


void setup() {
  Serial.begin(115200);
  Wire.begin();

  byte status = mpu.begin();
  Serial.println("status mpu(0-aman, 1-error) :"); Serial.print("status");
  while(status != 0) {
    Serial.println("mpu gagal di inisialisasi");
  }
  mpu.calcOffsets(true, true); // kalibrasi gyro dan acc
  Serial.println("kalibrasi.....");
  delay(1000);
  Serial.println("kalibrasi selesai");
    // put your setu/p code here, to run once:
  timer = micros();

}

void loop() {
  mpu.update();

  awal = micros();

  if(awal - timer >= batas ) { // membatasi siklus dalam 100hz

    dt = (awal - timer ) /1000000.0f; // melakukan perhitungan selisih antar siklus sebagai data dt
    timer = awal;

    float Aktual_pitch = mpu.getAngleX(); // pembacaan angle pitch 
    float Error = point_set - Aktual_pitch; // menghitung Error berdasarkan point_set

    float P = Kp * Error; // perhitungan komponen P

    sigma_Error += Error; // perhitungan akumulasi keseluruhan error yang sudah terjadi 

    float I = Ki * ( sigma_Error * dt); // perhitungan komponen I

    selisih_Error = Error - Error_lama;
    float D = Kd * (selisih_Error /dt);

    Error_lama = Error;
    float PID = P + I + D;

    Serial.print("pitch : "); Serial.print(Aktual_pitch);Serial.print("| ");
    Serial.print("Error : "); Serial.print(Error);Serial.println("|");
    Serial.println("\n");
    Serial.print("P : ");Serial.print(P);Serial.print("|");
    Serial.print(" I : ");Serial.print(I);Serial.print("|");
    Serial.print(" D : ");Serial.print(D);Serial.println("|");
    Serial.print("PID : ");Serial.println(PID);
    
  }
  // put your main code here, to run repeatedly:

}
