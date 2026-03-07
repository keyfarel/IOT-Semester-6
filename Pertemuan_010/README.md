# **Pertemuan 010 - Praktikum IoT (Internet of Things)**

Repositori ini berisi kode referensi untuk praktikum **Pertemuan 010**. Tujuan utama dari modul ini adalah mengimplementasikan arsitektur *Smart Village* berbasis IoT. Proyek ini menggunakan komunikasi jaringan TCP antara perangkat mikrokontroler (ESP32) sebagai *client* yang mengirimkan data multi-sensor (suhu dan kelembapan dari DHT11, serta intensitas cahaya dari LDR) ke program peladen (Python *Server*) jarak jauh melalui *tunneling* dengan platform **Pinggy**. Server akan memproses kondisi lingkungan ("Siang" atau "Malam") dan merespons dengan perintah aktuator (menyalakan/mematikan LED sebagai simulasi Lampu Jalan).

---

## **Daftar Proyek**

Di dalam repositori ini terdapat dua komponen utama yang independen dan saling terhubung melalui akses internet:

### **1. Firmware ESP32 (TCP Client)**
Berada di direktori `firmware/socket_server.ino`.
- **Fungsi Utama:** Membaca data parameter termal (suhu dan kelembapan dari sensor DHT11) dan intensitas cahaya lingkungan (dari sensor LDR), kemudian mengirimkan gabungan data tersebut menuju server Python jarak jauh menggunakan basis soket protokol TCP lewat koneksi WiFi *access point*. Program ini juga menerima perintah balik untuk mengontrol aktuator (LED).
- **Logika Eksekusi:** Menghubungkan platform ESP32 ke gerbang jaringan WiFi sekitar. Setelah terhubung, program secara periodik membaca nilai DHT11 dan mengonversi nilai analog LDR untuk menentukan parameter "Siang" atau "Malam". ESP kemudian mengirimkan serangkaian muatan *(payload)* string berisi data ke server destinasi (melalui *host* dan *port* rute TCP dari Pinggy). Setelah itu, ESP32 menunggu dan membaca respons server untuk mengeksekusi perintah aktuator (`led-on` atau `led-off`) yang merepresentasikan status nyala/mati lampu jalan, lalu beristirahat selama 5 detik sebelum mengulang siklus.

### **2. Program Python (TCP Server)**
Berada di direktori `server/server.py`.
- **Fungsi Utama:** Mendengarkan permintaan koneksi TCP yang datang dari ESP32, membaca data string yang memuat informasi suhu, kelembapan, dan kondisi cahaya, memproses logika cerdas (*Smart Village*), serta mengirimkan perintah aktuasi balik (*feedback*) kepada klien.
- **Logika Eksekusi:** Berjalan sebagai entitas TCP Socket *Server* pada rute jaringan fundamental `0.0.0.0` di *port* `2004`. Aplikasi menggunakan arsitektur *Multithreading* milik pustaka bawaan (`Thread`) lewat kelas `ClientThread` untuk mengelola koneksi klien yang masuk secara asinkron. Begitu menerima paket data dari klien, server melakukan inspeksi teks: bila ditemukan kata `"Malam"`, server merespons dengan perintah `"led-on\n"`; sebaliknya untuk `"Siang"` dikirimkan `"led-off\n"`. Pesan log aktivitas turut dicetak ke antarmuka terminal server secara *real-time*.

---

## **Konfigurasi Hardware (Pemetaan Pin ESP32)**

> **Catatan Penting:** Proyek ini membutuhkan koneksi *Internet* stabil dan perantara nilai referensi yaitu komponen sensor **DHT11**, sensor **LDR** (Light Dependent Resistor), serta **LED** yang dihubungkan ke pin ESP32.

Mengacu pada arsitektur matriks kelistrikannya, hubungkan setiap komponen sesuai deskripsi penempatan antarmuka berikut:

| Modul Mikrokontroler | Komponen yang Dihubungkan |
| :---: | :--- |
| **GND** | Konduktor Negatif (-) Sensor DHT11, LDR |
| **3.3V / 5V** | Suplai *Vcc* Energi Positif (+) untuk Sensor DHT11 dan LDR (disertai resistor *pull-down* yang sesuai) |
| **Pin 4** | Jalur Serial Distribusi (*Data Signal*) komponen Sensor DHT11 |
| **Pin 34** | Jalur Pembacaan Analog *(Analog Input)* komponen Sensor LDR |
| **Pin 2** | Konfigurasi internal *(Built-in LED)* ESP32 sebagai aktuator simulasi Lampu Jalan |

---

## **Panduan Eksekusi Program**

Ikuti langkah-langkah berikut untuk mengaktifkan sistem *Client-Server IoT Smart Village* Anda:

1. **Distribusi IP Publik:** Jalankan Pinggy Tunnel. Buka terminal komputer, lalu jalankan perintah penerusan *port* lokal `2004` ke layanan publik Pinggy (misal: `ssh -p 443 -R0:127.0.0.1:2004 tcp@a.pinggy.io`). 
2. **Nyalakan Peladen Data:** Eksekusi skrip operasional server (`python server.py` di dalam direktori `server/`) dan pastikan muncul log eksekusi `"Server Smart Village berjalan di port 2004..."`.
3. **Kustomisasi Parameter Firmware:** Buka skrip integrasi `firmware/socket_server.ino` menggunakan antarmuka kompilator **Arduino IDE**.
4. Subtitusi kredensial koneksi nirkabel WiFi proyek (pada variabel `ssid` maupun `password`).
5. Perbarui target proyektil saluran internet pada konstanta `host` serta `port` mencontoh referensi dari *output* terminal platform transmisi **Pinggy** (langkah 1).
6. Sambungkan ESP32 pada *port* USB yang sesuai dengan pilihan *COM Port* pada konfigurasi *Board Manager*. Setelah itu, jalankan instruksi kompilasi dan **Upload** ke ESP32.
7. Inisialisasi jendela evaluasi **Serial Monitor Arduino** (resolusi *baud rate* pada `115200`). Monitorlah tahap demi tahap dari proses perakitan koneksi WiFi, koneksi TCP ke jaringan Pinggy, transmisi *payload* sensor berkala, sampai eksekusi penerimaan perintah aktuasi `led-on` atau `led-off` dari sistem peladen.
