# **Pertemuan 006 - Praktikum IoT (Internet of Things)**

Repositori ini berisi kumpulan kode Arduino (sketch) untuk praktikum dan tugas pada **Pertemuan 006**. Tujuan utama dari modul ini adalah mempelajari penggunaan sensor LDR (Light Dependent Resistor) dan sensor suhu/kelembaban DHT11 untuk mensimulasikan sistem *Smart Home* sederhana menggunakan mikrokontroler ESP32.

---

## **Daftar Proyek**

Di dalam repositori ini terdapat tiga program utama, masing-masing mendemonstrasikan tahapan fungsionalitas yang berbeda:

### **1. Pembacaan Sensor LDR (`ldr_reader.ino`)**
Sebuah pengantar fundamental untuk membaca nilai analog dari intensitas cahaya menggunakan sensor LDR.
- **Fungsi Utama:** Mendeteksi resistansi cahaya yang akan berubah-ubah nilainya dari output analog dan menampilkannya pada Serial Monitor.
- **Logika Eksekusi:** Setiap 1.000 milidetik (1 detik), program membaca nilai *analog* (0-4095 pada ESP32) dari pin LDR dan mencetaknya secara numerik di Serial Monitor.

### **2. Sistem Smart Home Terintegrasi (`smart_home_system.ino`)**
Menggabungkan pembacaan sensor LDR dan DHT11 untuk mengontrol indikator LED RGB berdasarkan parameter kondisi lingkungan.
- **Fungsi Utama:** Memonitor intensitas cahaya dan suhu lingkungan untuk mengontrol status sistem yang direpresentasikan oleh LED RGB.
- **Logika Eksekusi:** Program akan merespon dua batas kondisi (`batasCahaya = 1500`, `batasDingin = 25.0°C`, `batasPanas = 30.0°C`):
  - **Redup & Dingin:** Jika LDR < 1500 dan Suhu < 25.0°C, maka LED Biru diaktifkan dengan pola kedip.
  - **Terang & Panas:** Jika LDR >= 1500 dan Suhu > 30.0°C, maka LED Merah dinyalakan.
  - **Kondisi Normal:** Di luar dari dua kriteria ekstrem di atas, LED dimatikan.

### **3. Simulasi Sistem Smart Home (`smart_home_simulations.ino`)**
Versi demonstrasi dari integrasi sistem *Smart Home* yang menyuntikkan (inject) nilai data buatan (dummy data) untuk menguji respons dan logika visual sistem tanpa bergantung pada kondisi fisik ruangan.
- **Fungsi Utama:** Melakukan tes dinamis transisi 3 profil *Smart Home* yang mencakup variabel Suhu dan LDR.
- **Logika Eksekusi:** Sistem merotasi *skenario* buatan setiap siklus dan mengabaikan bacaan sensor aslinya:
  1. *Skenario Normal*: LDR = 2000, Suhu = 27.0°C (LED Mati).
  2. *Skenario Redup & Dingin*: LDR = 800, Suhu = 22.0°C (LED Biru Berkedip).
  3. *Skenario Terang & Panas*: LDR = 3000, Suhu = 33.0°C (LED Merah Menyala).

---

## **Konfigurasi Hardware (Pemetaan Pin ESP32)**

> **Catatan Penting:** Proyek ini didesain secara spesifik menggunakan **LED RGB Common Cathode** (Katoda Umum). Pastikan kaki negatif dilekatkan pada pin `GND` papan mikrokontroler (ESP32). Untuk modul sensor DHT11, pastikan kakinya sudah benar terhubung ke input digital.

Berdasarkan desain fisik, integrasikan rangkaian komponen keras sesuai pemetaan pin di bawah ini:

| Modul Mikrokontroler | Komponen yang Dihubungkan |
| :---: | :--- |
| **GND** | Kaki-kaki (-) Sensor dan LED RGB |
| **3.3V / 5V** | VCC / Positif (+) LDR & DHT11 |
| **Pin 34** | Jalur Data / Analog Sensor LDR |
| **Pin 4** | Jalur Komunikasi Data Sensor DHT11 |
| **Pin 15** | Kaki Kontrol LED RGB - Merah (R / Red) |
| **Pin 16** | Kaki Kontrol LED RGB - Hijau (G / Green) |
| **Pin 17** | Kaki Kontrol LED RGB - Biru (B / Blue) |

---

## **Panduan Eksekusi Program**

Ikuti petunjuk di bawah untuk mengaplikasikan berkas ke modul Anda:

1. Buka file `.ino` (*sketch*) yang ingin Anda gunakan melalui aplikasi **Arduino IDE**.
2. Rangkai perangkat fisik LED RGB, Sensor LDR, dan Sensor DHT11 pada *protoboard* serta *jumper wire* berdasarkan **[tabel pemetaan pin ESP32 di atas](#-konfigurasi-hardware-pemetaan-pin-esp32)**.
3. Sambungkan board ESP32 dengan komputer lewat kabel USB data. 
4. Di *Arduino IDE*: Pastikan Anda sudah menentukan *Board* pengembangan yang tepat (`Tools` > `Board`) beserta *Port* komunikasi eksekusinya (`Tools` > `Port`).
5. Instal library **SimpleDHT** dari *Library Manager* (`Sketch` > `Include Library` > `Manage Libraries`) jika belum ada.
6. Klik ikon panah centang **Upload** *(Ctrl + U)*. Tunggu hingga proses unggah selesai dan muncul notifikasi "`Done uploading.`".
7. Aktifkan fitur **Serial Monitor** pada IDE (atau tekan gabungan tombol `Ctrl + Shift + M`). Setel _baud rate_ pada frekuensi `115200` baud untuk melihat antarmuka jejak (*debug logs*) dan pengamatan status mikrokontroler.
