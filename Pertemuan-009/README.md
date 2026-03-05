# **Pertemuan 009 - Praktikum IoT (Internet of Things)**

Repositori ini berisi kode referensi untuk praktikum **Pertemuan 009**. Tujuan utama dari modul ini adalah mempelajari komunikasi jaringan TCP antara perangkat mikrokontroler (ESP32) sebagai *client* yang mengirimkan data sensor (suhu dan kelembapan dari DHT11) ke program peladen (Python *Server*) jarak jauh melalui *tunneling* dengan platform **Pinggy**.

---

## **Daftar Proyek**

Di dalam repositori ini terdapat dua komponen utama yang independen dan saling terhubung melalui akses internet:

### **1. Firmware ESP32 (TCP Client)**
Berada di direktori `firmware/dht_11_socket/sketch_mar5a.ino`.
- **Fungsi Utama:** Membaca data parameter termal (suhu dan kelembapan dari komponen sensor DHT11) dan mengirimkan parameter tersebut menuju server Python jarak jauh menggunakan basis soket protokol TCP lewat koneksi WiFi *access point*.
- **Logika Eksekusi:** Menghubungkan platform ESP32 ke gerbang jaringan WiFi sekitar. Setelah otentikasi sukses, program secara sekuensial mengkalkulasi sampel nilai DHT11. ESP kemudian menjalin permohonan koneksi klien langsung menuju server destinasi (*host* dan *port* rute TCP dari Pinggy). Sesampainya pada tahap *established*, ESP32 merangkai serta membuang muatan *(payload)* data string suhu dan kelembapan, dilanjut dengan sesi pasif menunggu paket konfirmasi keberhasilan operasional pengiriman dari rute server sebelum akhirnya secara sengaja memutus kembali koneksi dan memutar rutinitas dengan periode waktu komputasi 5 detik.

### **2. Program Python (TCP Server)**
Berada di direktori `server/server.py`.
- **Fungsi Utama:** Mendengarkan permintaan instansiasi sesi pertukaran TCP *socket* yang menyambangi peladen (dari ESP32), membaca interpretasi kumpulan data *byte* kiriman, menampilkannya menjadi struktur *string* manusiawi ke papan pengawas (konsole log *prompt* logis), terakhir meretas komunikasi timbal balik *(feedback)* berisikan label sukses pada ujung klien.
- **Logika Eksekusi:** Digelorakan menjadi entitas TCP Socket *Server* pada rute jaringan fundamental `0.0.0.0` menumpang lokalisasi *port* `2004`. Aplikasi memberdayakan rancangan fungsionalitas turunan *Multithreading* milik pustaka terintegrasi sistem (`Thread`), difungsikan guna memanen konjungsi sesi permintaan majemuk entitas *client* sekaligus dalam wadah `ClientThread`. Ekstraksi ini memungkinkan antrean transmisi interupsi perangkat lebih adaptif menyerap data dari masifnya kuantitas sensor yang menyinggahi pos layanan. Sebagai bentuk formalitas pertukaran ujung perantara, deret karakter ASCII berbunyi `"Data DHT11 aman diterima server!\n"` dikapalkan kembali sebagai lampu validasi.

---

## **Konfigurasi Hardware (Pemetaan Pin ESP32)**

> **Catatan Penting:** Proyek ini bergantung minimalisasinya terhadap rel sirkulasi transmisi *Internet* stabil dan perantara nilai referensi yaitu komponen sensor **DHT11** yang dihubungkan ke pin ESP32.

Mengacu pada arsitektur matriks kelistrikannya, jalinkan setiap polaritas komponen sesuai deskripsi penempatan antarmuka *wiring* sirkuit perakitannya:

| Modul Mikrokontroler | Komponen yang Dihubungkan |
| :---: | :--- |
| **GND** | Konduktor Negatif (-) milik Sensor DHT11 |
| **3.3V / 5V** | Suplai *Vcc* Energi Positif (+) penyokong daya pengukuran modul DHT11 |
| **Pin 4** | Jalur Serial Distribusi (*Data Signal*) komponen Sensor DHT11 |

---

## **Panduan Eksekusi Program**

Ikuti metodologi operasional esensial berurut demi mengaktifkan arsitektur *Client-Server IoT* Anda mempedomani dokumentasi ini:

1. **Distribusi IP Publik:** Jalankan Pinggy Tunnel. Buka sesi *terminal*, proyeksikan *command* transmisi perantara Pinggy demi membedah eksklusivitas lingkungan lokal *port* `2004` ke arah dunia publik (misal: `ssh -p 443 -R0:127.0.0.1:2004 tcp@a.pinggy.io`). 
2. **Nyalakan Peladen Data:** Eksekusi skrip operasional server (`python server.py`) dan pastikan melahirkan jejak eksekusi `"Server berjalan dan menunggu koneksi ESP di port 2004..."`.
3. **Kustomisasi Parameter Firmware:** Buka skrip integrasi `firmware/dht_11_socket/sketch_mar5a.ino` lewat antarmuka kompilator **Arduino IDE**.
4. Subtitusi kredensial nirkabel WiFi (konstanta `ssid` maupun `password`).
5. Perbarui target proyektil saluran internet pada konstanta `host` serta `port` mencontoh referensi tertera dari platform transmisi **Pinggy** (langkah 1).
6. Rekatkan kabel komunikasi serial ESP32 yang tepat pada parameter seleksi COM *Port* (*Board Manager: ESP32*), sesudahnya aplikasikan opsi fungsi kompilator **Upload**.
7. Inisialisasi jendela pantau lalu lintas berlandaskan alat evaluasi **Serial Monitor Arduino** (resolusi pergerakan pembacaan sinkron `115200` baud). Monitorlah tahapan pengait parameter integrasi WiFi (*bridging*), perakitan transmisi gerbang Pinggy lokal, manuver emisi proyektil nilai logis DHT11, berikut sinkronisasi balik otentikasi keberhasilan *push* Python PC.
