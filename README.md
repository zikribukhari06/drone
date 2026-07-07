# Drone
ini berisikan file file yang mendukung projek drone, beserta keterangan dan penjelasan yang dibutuhkan dalam proses pengembangan.
# Remote
file remote berisikan file file selama mempelajari mekanisme dari trasnmission flow yang bersifat universal, sehingga ini dapat digunakan untuk projek sejenisnya yng membutuhkan remote control.
# recv
pada sisi receiver, kode yang digunakan mengubah input analog 0-255 menjadi PULSA RC, namun jika projek dapat langsung menggunakan input analog sebagai PWM, maka proes mapping bisa di hilangkan dan langsung di write ke penggerak.
# Input Remote
### 1. Hovering (Melayang Diam)

* Hovering adalah kondisi ketika drone melayang stabil pada satu titik tanpa bergerak ke segala arah.
* Kondisi ini terjadi ketika kecepatan putaran keempat motor sama sehingga gaya dorong yang dihasilkan seimbang dengan gaya gravitasi.
* Hovering merupakan kondisi dasar yang digunakan sebelum drone melakukan manuver lainnya.

### 2. Throttle (Gerakan Naik dan Turun)

* Throttle mengatur pergerakan drone secara vertikal, yaitu naik atau turun.
* Untuk membuat drone naik, kecepatan seluruh motor ditingkatkan sehingga gaya dorong lebih besar daripada berat drone.
* Untuk membuat drone turun, kecepatan seluruh motor dikurangi sehingga gaya dorong lebih kecil daripada berat drone.

### 3. Pitch (Gerakan Maju dan Mundur)

* Pitch mengendalikan gerakan drone ke arah depan atau belakang.
* Drone bergerak maju dengan meningkatkan kecepatan motor belakang dan mengurangi kecepatan motor depan, sehingga bodi condong ke depan.
* Drone bergerak mundur dengan meningkatkan kecepatan motor depan dan mengurangi kecepatan motor belakang, sehingga bodi condong ke belakang.

### 4. Roll (Gerakan Kiri dan Kanan)

* Roll mengendalikan gerakan drone ke arah kiri atau kanan tanpa mengubah arah hadapnya.
* Drone bergerak ke kanan dengan meningkatkan kecepatan motor sisi kiri dan mengurangi kecepatan motor sisi kanan, sehingga bodi miring ke kanan.
* Drone bergerak ke kiri dengan meningkatkan kecepatan motor sisi kanan dan mengurangi kecepatan motor sisi kiri, sehingga bodi miring ke kiri.

### 5. Yaw (Rotasi atau Perubahan Arah Hadap)

* Yaw mengendalikan putaran drone pada sumbu vertikal sehingga arah hadap drone berubah.
* Putaran terjadi karena adanya perbedaan torsi antara pasangan motor yang berputar searah jarum jam dan berlawanan arah jarum jam.
* Yaw ke kiri diperoleh dengan meningkatkan kecepatan motor yang berputar searah jarum jam, sedangkan yaw ke kanan diperoleh dengan meningkatkan kecepatan motor yang berputar berlawanan arah jarum jam.

# Rumus mixer motor dari input trothle pitch yaw roll 
Motor 1 (Depan Kanan)  = T - P - R + Y

Motor 2 (Belakang Kiri) = T + P + R + Y

Motor 3 (Depan Kiri)    = T - P + R - Y

Motor 4 (Belakang Kanan) = T + P - R - Y

# mpu6050 
disini merupakan program dasar dalam mengoperasikan mpu6050 untuk mendapatkan angle pitch roll dan yaw secara real time, yang dimana hasilkan data ini akan diproses untuk algoritma pid

# PID
ketika melkaukan tunning PID, alih alih hanya menggunakan trail and error. saya berencana untuk merekan semua history angle, sehingga saya dapat mengubahnya meenjadi sebuah grafik untuk menunjukan karakteristik dari pergerakan drone terhadap koreksi PID. sehingga saya dpat menentukan nilai P I D dengan lebih teoritis.
berikut langkah langkah dalam menentukan PID secara matematis
1. membuat Ki dan Kd menjadi 0, sehingga pergerkan hanya akan didsarkan oleh respon komponen P
2. naikkan nilai Kp secara perlahan sampai didapatkan grafik osilasi yang stabil
3. berdasarkan grafik yang dihasilkan, maka akan didapatkan nilai Ku yaitu nilai Kp terakhir, dan Pu yaitu waktu satu periode
4. setelah data Ku dan Pu didapat, masukkan dalam tabel perhitungan PID dengan metode Kalkulasi Ziegler-Nichols.

# link layout esp32
https://lastminuteengineers.com/esp32-pinout-reference/#esp32-dac-pin


