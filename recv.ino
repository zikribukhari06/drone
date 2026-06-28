#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h> // Library wajib untuk menghasilkan pulsa PWM standar Drone/FC

// 1. Inisialisasi nRF24L01 pada Drone (CE=9, CSN=10)
RF24 radio(9, 10);
const byte alamatKomunikasi[6] = "RC001"; // Harus SAMA dengan Remote

// 2. Struktur Paket Data harus identik dengan yang ada di Remote
struct PaketRemote {
  byte throttle;
  byte yaw;
  byte pitch;
  byte roll;
};
PaketRemote dataTerima;

// 3. Membuat objek Servo untuk setiap channel input Flight Controller
Servo chThrottle;
Servo chYaw;
Servo chPitch;
Servo chRoll;

void setup() {
  Serial.begin(9600);
  
  // 4. Menghubungkan pin fisik Arduino ke pin input Flight Controller Drone
  chThrottle.attach(2); // Hubungkan ke pin Throttle di FC
  chYaw.attach(3);      // Hubungkan ke pin Yaw di FC
  chPitch.attach(4);    // Hubungkan ke pin Pitch di FC
  chRoll.attach(5);     // Hubungkan ke pin Roll di FC

  // 5. Konfigurasi Modul Radio Penerima
  if (!radio.begin()) {
    Serial.println("Hardware nRF24L01 di Drone tidak terdeteksi!");
    while (1);
  }
  
  radio.openReadingPipe(1, alamatKomunikasi); // Membuka jalur dengeran di alamat "RC001"
  radio.setPALevel(RF24_PA_LOW);              // Set daya rendah untuk uji coba meja
  radio.setDataRate(RF24_2MBPS);              // Kecepatan data sama dengan remote (2 Mbps)
  radio.startListening();                     // Set modul fokus sebagai Receiver (Mendengarkan)
  
  Serial.println("Drone Siap Menerima Sinyal...");
}

void loop() {
  // 6. Cek apakah ada paket data radio yang masuk di udara
  if (radio.available()) {
    
    // 7. Tahap Membongkar Paket: Membaca data dan memasukkannya ke struct dataTerima
    radio.read(&dataTerima, sizeof(dataTerima));
    
    // 8. Tahap Konversi (Mapping) dari byte (0-255) ke Pulsa RC (1000us - 2000us)
    int pwmThrottle = map(dataTerima.throttle, 0, 255, 1000, 2000);
    int pwmYaw      = map(dataTerima.yaw,      0, 255, 1000, 2000);
    int pwmPitch    = map(dataTerima.pitch,    0, 255, 1000, 2000);
    int pwmRoll     = map(dataTerima.roll,     0, 255, 1000, 2000);
    
    // 9. Tahap Eksekusi: Tembakkan pulsa PWM murni ke Flight Controller
    chThrottle.writeMicroseconds(pwmThrottle);
    chYaw.writeMicroseconds(pwmYaw);
    chPitch.writeMicroseconds(pwmPitch);
    chRoll.writeMicroseconds(pwmRoll);
    
    // Debugging (Melihat data yang masuk di Serial Monitor Drone)
    Serial.print("Diterima -> T: "); Serial.print(pwmThrottle);
    Serial.print(" | Y: "); Serial.print(pwmYaw);
    Serial.print(" | P: "); Serial.print(pwmPitch);
    Serial.print(" | R: "); Serial.println(pwmRoll);
  }
  else {
    // 10. FITUR SAFETY (Failsafe): Jika sinyal remote putus, paksa drone melambat/mati
    // (Akan dibahas di bawah demi keamanan terbang)
  }
}