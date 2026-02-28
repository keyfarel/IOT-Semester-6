# **Pertemuan 005 - Praktikum IoT (Internet of Things)**

Repositori ini berisi kumpulan kode Arduino (sketch) untuk praktikum dan tugas pada **Pertemuan 005**. Tujuan utama dari modul ini adalah mempelajari pembacaan data lingkungan dari sensor suhu dan kelembaban udara (**DHT11**) serta pengembangannya untuk memberikan indikator visual suhu menggunakan modul **LED RGB (Common Cathode)** dan mikrokontroler ESP32.

---

## **Daftar Proyek**

Di dalam repositori ini terdapat tiga program utama, masing-masing mendemonstrasikan tahapan fungsionalitas yang berbeda:

### **1. Pembacaan Suhu dan Kelembaban Dasar (`temperature_reader.ino`)**
Sebuah program fundamental untuk menguji fungsionalitas sensor balikan DHT11 dan memastikan koneksi pemrosesan *data sampling* dapat bekerja dengan baik.
- **Fungsi Utama:** Mendapatkan nilai Suhu (dalam Celcius) dan persentase Kelembaban udara dari lingkungan sekitar (sekitar sensor).
- **Logika Eksekusi:** Melakukan transisi *sampling* data dari sensor melalui `SimpleDHT` setiap 1,5 detik untuk memposting detail ke Serial Monitor. Pemrograman mencakup mekanisme peringatan *error* jika pengambilan data gagal merespon.

### **2. Pendeteksi Suhu dengan Indikator Visual Kota (`temperature-detections.ino`)**
Implementasi tingkat lanjut yang menyambungkan nilai suhu rill pada lingkungan dengan rentang visual fungsionalitas yang ditampilkan dari warna-warni pada komponen LED RGB.
- **Fungsi Utama:** Mendeteksi tingkatan status ambang batas nilai suhu (Dingin, Normal, Panas) dan memberikan respon nyala warna pada lampu indikator (LED).
- **Logika Eksekusi:**
  - **DINGIN (< 25 °C):** Menghidupkan mode warna **HIJAU** pada LED RGB.
  - **NORMAL (25 °C - 30 °C):** Menghidupkan mode warna **BIRU** pada LED RGB.
  - **PANAS (> 30 °C):** Menghidupkan mode warna **MERAH** pada LED RGB.
- **Konversi Nilai:** Selain menampilkan nilai skala lingkungan dalam standar Celcius secara repetitif (perulangan tiap 2 detik), program ini juga secara bersamaan mengkalkulasi suhu lokal ke format Kelvin (ditambah konstanta 273.15) dan Reamur (dibagi 0.8) guna mencetaknya ke laporan monitor log (bersifat real-time).

### **3. Simulasi Perubahan Suhu (Mode Demo Bertahap) (`temperature_simulations.ino`)**
Program demonstrasi alternatif untuk mementaskan perputaran animasi dari LED RGB tanpa bergantung penuh dari pembacaan DHT11 di habitat asli yang cenderung konstan dan jarang berfluktuasi drastis secara cepat.
- **Fungsi Utama:** Melakukan tes dinamis pada modul cahaya (LED RGB) menggunakan skenario manipulasi nilai dari suhu buatan (virtual step).
- **Logika Eksekusi:** Siklus manipulasi suhu diawali secara eksplisit di angka `21.0 °C` (merupakan kategori DINGIN). Nilai komputasi tersebut otomatis merangkak bertambah (`+1.5` poin setiap 1,5 detik) hingga bersentuhan di koridor ambang atas `33.0 °C` (keluarga sub-kategori PANAS). Ketika mendeteksi kondisi ekstrim tsb, nilai manipulasi lantas berputar balik dengan tren menyusut (`-1.5`) hingga batas dasar.

---

## **Konfigurasi Hardware (Pemetaan Pin ESP32)**

> **Catatan Penting:** Proyek ini didesain menggunakan modul **Sensor Suhu dan Kelembaban (DHT11)** dan juga **LED RGB Common Cathode** (Katoda Umum). Pastikan pin sumber listrik negatif komponen terkait dilekatkan pada pin aliran Ground (`GND`) milik mikrokontroler (ESP32).

Berdasarkan desain fisik fungsionalitas berkas `.ino`, integrasikan rangka rangkaian komponen eksternal selaras dengan pemetaan pin-kaki di bawah ini:

| Modul Mikrokontroler (ESP32) | Pin / Modul Eksternal | Modul Kegunaan |
| :---: | :--- | :--- |
| **GND** | Pin `-` DHT11 & Kaki Paling Panjang (Negatif) LED RGB | Arus Balik / Ground |
| **3V3/VIN** | Pin `+` (VCC) DHT11 | Sumber Daya 3.3v |
| **Pin 4** | Pin `Data` / `Signal` (OUT) DHT11 | Transfer Data Komunikasi DHT |
| **Pin 15** | Kaki Warna Merah (R / Red) LED RGB | Sinyal Visual Panas |
| **Pin 16** | Kaki Warna Hijau (G / Green) LED RGB | Sinyal Visual Dingin |
| **Pin 17** | Kaki Warna Biru (B / Blue) LED RGB | Sinyal Visual Normal |

---

## **Panduan Eksekusi Program**

Ikuti petunjuk di bawah untuk mengaplikasikan berkas program ke dalam mikrokontroler Anda:

1. Buka file draf ekstensi `.ino` (*sketch*) yang ingin disimulasikan melalui jendela aplikasi **Arduino IDE**.
2. Rangkai perangkat fisik (DHT11 & Modul LED) di atas *protoboard/breadboard* menggunakan kabel penghubung *jumper wire* berdasarkan instruksi **[tabel pemetaan pin ESP32 di atas](#-konfigurasi-hardware-pemetaan-pin-esp32)**.
3. Sambungkan perangkat board perantara IDE (ESP32) menuju soket USB milik komputer. 
4. Di aplikasi editor *Arduino IDE*: Pastikan kalian sudah memverifikasi model jenis *Board* pendukung dengan benar (`Tools` > `Board`) beserta pendeteksian jalur kabel koneksi / *Port* transfer eksekusinya (`Tools` > `Port`).
5. Jangan lupa *Install* / pasang berkas pendukung pada fitur `Library Manager`: **Library "SimpleDHT"** sebelum mengunggah kode sumber.
6. Lakukan penekanan ikon panah bundar kompilasi **Upload** *(via GUI / Ctrl + U)*. Tunggu sebentar hingga layar menunjukkan lapor `"Done uploading."`
7. Terakhir, tampilkan terminal baca melalui kontrol klik fitur **Serial Monitor** pada sisi ujung kanan layar IDE (atau pintasan gabungan tombol `Ctrl + Shift + M`). Setel ukuran konversi besaran laju bingkai kecepatan bit antarmuka pada nilai **`115200`** *baud rate* mendalangi fungsi *debug logs* mikrokontroler.
