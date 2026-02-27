# **Pertemuan 003 - Praktikum IoT (Internet of Things)**

Repositori ini berisi kumpulan kode Arduino (sketch) pengenalan dasar mikrokontroler untuk praktikum pada **Pertemuan 003**. Tujuan utama dari modul ini adalah mempelajari fundamental pemrograman Arduino, kontrol pengeluaran digital (*digital output*), dan dasar-dasar pertukaran informasi lewat komunikasi serial.

---

## **Daftar Proyek**

Di dalam repositori ini terdapat dua program utama, masing-masing mendemonstrasikan dasar pengenalan fungsionalitas mikrokontroler:

### **1. LED Blink Dasar (`blink.ino`)**
Sebuah pengantar fundamental untuk mengontrol komponen perangkat keras eksternal (LED standar) dengan memberikan instruksi pin arus digital sederhana.
- **Fungsi Utama:** Menyalakan dan mematikan sebuah lampu LED berirama dengan interval jeda waktu spesifik secara berkesinambungan.
- **Logika Eksekusi:** Pin eksekutor (Pin 2) akan dikonfigurasi status modenya sebagai arus antarmuka *OUTPUT*. Pin bersangkutan nantinya diberikan sinyal `HIGH` (mendapat suplai voltase/nyala) selama 1.000 milidetik (1 detik), kemudian disusul dengan sinyal tegangan `LOW` (terputus/mati) bertempo sama, diulang berurut selamanya oleh prosedur blok `loop()`.

### **2. Pengenalan Serial Monitor (`hello_world.ino`)**
Program fundamental untuk memahami dan mempraktikkan pengiriman data sederhana berbasis untaian teks (string) dari modul board balik layar ke konsol perangkat komputer pengguna melewati rute antarmuka *Serial Monitor*.
- **Fungsi Utama:** Memancarkan dan merepresentasikan teks `"Hello World"` secara repetitif pada layar *Serial Monitor*.
- **Logika Eksekusi:** Rute percakapan serial port diinisialisasi untuk berjalan di kecepatan transmisi standar (`9600` baud) dalam prosedur inisiasi. Kemudian mikrokontroler akan mengeksekusi pembuangan deretan kalimat berjejak (`println()`) secara stabil ke kabel data, setiap proses cetak tersebut diiringi instruksi menganggur (*delay*) konstan sepanjang jarak 1 detik.

---

## **Konfigurasi Hardware (Pemetaan Pin)**

Tidak diperlukan perangkaian kelistrikan eksternal (*wiring*) sama sekali. Modul pembelajaran kelistrikan pada tahap ini mengandalkan ketersediaan sensor cahaya terintegrasi pada papan pengembangan itu sendiri.

> **Catatan Penting Operasional:** Program `blink.ino` didesain untuk menyalakan _built-in LED_ (LED bawaan internal) yang sudah terpatri langsung pada board ESP32 secara bawaan pabrik, umumnya terhubung ke interupsi kelistrikan **Pin 2**. Oleh karena itu, pengguna dibebaskan sepenuhnya dari kewajiban merangkai LED tambahan eksterior, tidak perlu menggunakan *Resistor*, tidak memakai kabel _Jumper_, dan tidak membutuhkan papan sirkuit (_Breadboard_) tambahan. Praktikum `hello_world.ino` juga tidak menuntut aksesori ekstra.

---

## **Panduan Eksekusi Program**

Ikuti petunjuk konfigurasi antarmuka di bawah ini sehingga instruksional program sanggup mengalir sampai ke unit sirkuit:

1. Buka file draf target (`.ino` *sketch*) menggunakan program bantu **Arduino IDE**.
2. Hubungkan board unit ESP32/Arduino dengan mesin komputer *host* Anda melalui jalur transfer kabel port USB. 
3. Masuk ke halaman menu **Arduino IDE**, atasi parameter spesifikasi *Board* arsitektur (pastikan menggunakan module board varian ESP32) dan alamat identifikasi COM *Port* serialnya via menu navigasi atas (`Tools` > `Board` & `Tools` > `Port`).
4. Klik grafis tanda panah sirkuler atau tombol **Upload** *(pintasan tombol: Ctrl + U)*. Mohon menunggu aktivitas migrasi kompilasi prosesor hingga notifikasi berhasil "`Done uploading.`".
5. **[Khusus `hello_world.ino`]:** Aktifkan bilah penelusuran port bernama **Serial Monitor** pada fasilitas pojok kanan atas layar IDE (bisa menggunakan pintasan keyboard `Ctrl + Shift + M`). Setel drop-down opsi spesifikasi konfigurasi laju pemrosesan (_baud rate_) persis di angka tetapan `9600` untuk mulai menangkap antrean teks cetakan komunikasi.
