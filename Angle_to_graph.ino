#include<MPU6050_light.h>
#include<Wire.h>

MPU6050 mpu(Wire);

unsigned long waktu_lama = 0;
unsigned long waktu_sekarang = 0;
float dt = 0;
const unsigned long batas = 100000.0f;

float Kp = 0.8;
float Ki = 0.1;
float Kd = 0.1;

float P = 0;
float I = I;
float D = 0;
float PID = 0;

float point_set = 0;
float Error = 0;
float sigma_error = 0;
float Error_lama = 0;
float Selisih_error = 0;



void setup() {
  Serial.begin(115200);
  Wire.begin();
  byte status = mpu.begin();
  Serial.println(status);
  if(status != 0) {
    Serial.print("mpu gagal di inisialisasi");
  }
  Serial.println("memulai kalibrasi MPU....");
  mpu.calcOffsets(false,true);
  delay(1000);
  Serial.println("kalibrasi selesai...");
  delay(1000);
  waktu_lama = micros();
  // put your setup code here, to run once:

}

void loop() {
  mpu.update();

  waktu_sekarang = micros();
  if(waktu_sekarang - waktu_lama >= batas ) {
    dt = (waktu_sekarang - waktu_lama ) /1000000.0f;
    waktu_lama = waktu_sekarang;

    float pitch = mpu.getAngleY();
    Error = point_set - pitch;

    P = Kp * Error;

    sigma_error += Error;

    I = Ki * (sigma_error * dt);
    Selisih_error = Error - Error_lama;

    D = Kd * (Selisih_error /dt);

    Error_lama = Error;
    PID = P + I + D;
    //batas atas dan batas bawah
    Serial.print("batas_atas:");
    Serial.print(45);
    Serial.print(",");
    Serial.print("batas_bawah:");
    Serial.print(-45);
    Serial.print(",");
    // 
    Serial.print("P:");
    Serial.print(P);
    Serial.print(",");
    Serial.print("I:");
    Serial.print(I);
    Serial.print(",");
    Serial.print("D:");
    Serial.print(D);
    Serial.print(",");
    Serial.print("PID:");
    Serial.print(PID);
    Serial.print(",");
    Serial.print("pitch:");
    Serial.print(pitch);
    Serial.print(",");
    Serial.print("Error:");
    Serial.println(Error);



}


}
