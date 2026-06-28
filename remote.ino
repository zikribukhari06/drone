#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// 1. Inisialisasi pin CE dan CSN untuk nRF24L01 pada Arduino Nano
// Pin SPI sisanya (SCK=13, MISO=12, MOSI=11) sudah otomatis diatur oleh hardware
RF24 radio(9, 10); 

// 2. Alamat unik komunkasi (5 Byte). Harus SAMA antara Remote dan Drone
const byte alamatKomunikasi[6] = "RC001";

// 3. Struktur Paket Data Universal (Maksimal 32 Byte)
// Kita gunakan tipe data 'byte' agar paket sangat ringan (hanya 4 Byte)
struct PaketRemote {
  byte throttle; // Joystick Kiri - Vertikal (A0)
  byte yaw;      // Joystick Kiri - Horisontal (A1)
  byte pitch;    // Joystick Kanan - Vertikal (A2)
  byte roll;     // Joystick Kanan - Horisontal (A3)
};

// Membuat objek dari struct untuk menampung data aktual
PaketRemote dataKirim;

void setup() {
  Serial.begin(9600);
  
  // 4. Konfigurasi Modul Radio
  if (!radio.begin()) {
    Serial.println("Hardware nRF24L01 tidak terdeteksi!");
    while (1); // Berhenti di sini jika kabel radio ada yang salah
  }
  
  radio.openWritingPipe(alamatKomunikasi); // Mengatur alamat pengiriman
  radio.setPALevel(RF24_PA_LOW);           // Set daya pancar (LOW untuk uji coba dekat agar aman)
  radio.setDataRate(RF24_2MBPS);           // Kecepatan transfer tinggi untuk latensi rendah
  radio.stopListening();                   // Mengatur modul murni sebagai Transmitter (Pemancar)
  
  Serial.println("Remote Siap Memancar...");
}

void loop() {
  // 5. Tahap Mapping: Membaca analog (0-1023) dan mengubahnya ke byte (0-255)
  dataKirim.throttle = map(analogRead(A0), 0, 1023, 0, 255);
  dataKirim.yaw      = map(analogRead(A1), 0, 1023, 0, 255);
  dataKirim.pitch    = map(analogRead(A2), 0, 1023, 0, 255);
  dataKirim.roll     = map(analogRead(A3), 0, 1023, 0, 255);

  // 6. Tahap Transmisi: Mengirimkan struct dataKirim secara utuh lewat udara
  bool suksesTerkirim = radio.write(&dataKirim, sizeof(dataKirim));

  // 7. Debugging via Serial Monitor (Opsional, untuk melihat angka pas pergerakan stik)
  if (suksesTerkirim) {
    Serial.print("Terkirim -> T: "); Serial.print(dataKirim.throttle);
    Serial.print(" | Y: "); Serial.print(dataKirim.yaw);
    Serial.print(" | P: "); Serial.print(dataKirim.pitch);
    Serial.print(" | R: "); Serial.println(dataKirim.roll);
  } else {
    Serial.println("Gagal Mengirim Paket (Drone di luar jangkauan / mati)");
  }

  // Jeda kirim 20 milidetik (Mengirim data 50 kali dalam satu detik)
  delay(20); 
}