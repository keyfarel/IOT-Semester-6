# **Praktikum Internet of Things (IoT) - Semester 6**

Repositori ini didedikasikan sebagai pusat dokumentasi dan penyimpanan kode sumber (sketch) untuk mata kuliah Praktikum **Internet of Things (IoT)** Semester 6. 

Sebagian besar proyek pembelajaran pada repositori ini dieksekusi menggunakan mikrokontroler **ESP32** dan ditulis dengan bahasa pemrograman C/C++ memanfaatkan lingkungan pengembangan **Arduino IDE**.

---

## **Daftar Modul Praktikum**

Seiring berjalannya jadwal perkuliahan, repositori ini akan terus diperbarui dengan modul-modul praktikum terbaru. Berikut adalah indeks pertemuan yang telah tersedia:

| Pertemuan | Direktori Modul | Topik Pembelajaran Utama | Ringkasan Materi |
| :---: | :--- | :--- | :--- |
| **003** | [`/Pertemuan_003`](./Pertemuan_003) | Pengenalan Mikrokontroler & Komunikasi Serial | Mempelajari fundamental pemrograman Arduino, kontrol *digital output* dasar (blink LED), dan dasar pertukaran informasi (teks) ke komputer melewati *Serial Monitor*. |
| **004** | [`/Pertemuan_004`](./Pertemuan_004) | Kontrol LED RGB & Pembangkit Sinyal SOS | Pemahaman dasar kontrol LED RGB (Common Cathode) multwarna serta implementasi algoritma perulangan dan penundaan (delay) untuk membangkitkan pola sinyal darurat Morse (SOS). |

---

## **Kebutuhan Perangkat**

Untuk mempraktikkan proyek-proyek yang terlampir, Anda mereplika lingkungan perangkat keras dan lunak berikut:

### **1. Hardware (Perangkat Keras)**
- **Mikrokontroler:** Board ESP32 (Disarankan) atau board kompatibel lainnya seperti Arduino Uno, NodeMCU ESP8266.
- **Kabel Komunikasi:** Kabel Data USB (Type Micro-B atau Type-C, menyesuaikan antarmuka board).
- **Penghubung Sirkuit:** Kabel Jumper (Male-to-Male / Male-to-Female).
- **Papan Rangkaian:** Breadboard / Protoboard.
- **Komponen Spesifik:** LED RGB Common Cathode, Resistor standar, Sensor (menyesuaikan kebutuhan tiap pertemuan).

### **2. Software (Perangkat Lunak)**
- **Integrated Development Environment:** Arduino IDE (Disarankan menggunakan versi 1.8.x atau 2.x ke atas).
- **Konfigurasi Board:** Board Manager ESP32 terinstal (*contoh: ESP32 by Espressif Systems*).
- **Driver Port:** Driver USB to UART (*contoh: CP210x, CH340*) apabila port board tidak terdeteksi oleh sistem operasi komputer Anda.

---

## **Panduan Penggunaan Repositori**

Ikuti instruksi komprehensif berikut untuk memulai eksplorasi mandiri Anda:

1. **Kloning Repositori:** Unduh salinan repositori ini ke dalam penyimpanan lokal Anda melalui terminal/command prompt:
   ```bash
   git clone https://github.com/keyfarel/IOT-Semester-6.git
   ```
2. **Navigasi Direktori:** Masuk ke dalam folder pertemuan spesifik yang ingin Anda pelajari (Sebagai contoh: `/Pertemuan_004`).
3. **Pelajari Dokumentasi:** Sangat disarankan untuk membaca file `README.md` yang terdapat pada tiap-tiap subfolder. File tersebut berisi instruksi terperinci, skema rangkaian hardware, dan penjelasan krusial terkait jalannya program.
4. **Buka Kode Sumber:** Muat file berekstensi `.ino` menggunakan **Arduino IDE**.
5. **Konfigurasi Lingkungan:** Pastikan pengaturan **Board** serta **Port** komunikasi di dalam Arduino IDE sudah sesuai sebelum Anda menekan tombol *Upload* ke mikrokontroler.

---

## **Lisensi & Hak Cipta**

Dokumentasi serta kode sumber di dalam repositori ini disusun sepenuhnya untuk tujuan pendidikan, referensi pembelajaran, dan penyelesaian kewajiban akademis mata kuliah Praktikum Internet of Things (IoT) Semester 6. Bebas untuk digunakan dan dimodifikasi sebagai media pembelajaran.
