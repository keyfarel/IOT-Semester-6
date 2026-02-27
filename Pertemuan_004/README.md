# **Pertemuan 004 - Praktikum IoT (Internet of Things)**

Repositori ini berisi kumpulan kode Arduino (sketch) untuk praktikum dan tugas pada **Pertemuan 004**. Tujuan utama dari modul ini adalah mempelajari kontrol dasar dan implementasi pengkodean **LED RGB (Common Cathode)** menjadi sinyal morse darurat (SOS) menggunakan mikrokontroler ESP32.

---

## **Daftar Proyek**

Di dalam repositori ini terdapat tiga program utama, masing-masing mendemonstrasikan tahapan fungsionalitas yang berbeda:

### **1. Kontrol Dasar LED RGB (`project_1_led_rgb.ino`)**
Sebuah pengantar fundamental untuk mengontrol komponen RGB LED dengan menyalakan setiap segmen warna secara bergilir.
- **Fungsi Utama:** Mengaktifkan warna LED secara bergantian membentuk sekuens **Merah → Hijau → Biru**.
- **Logika Eksekusi:** Setiap pin warna akan diberikan sinyal `HIGH` selama 1.000 milidetik (1 detik), sebelum dimatikan kembali untuk memberi giliran bagi warna selanjutnya.

### **2. Pembangkit Sinyal SOS Tunggal (`project_2_led_rgb.ino`)**
Mengonversi durasi waktu nyala LED menjadi sandi morse internasional untuk tanda bahaya darurat (SOS) menggunakan satu indikator warna (merah).
- **Fungsi Utama:** Mentransmisikan sinyal cahaya berpola **SOS** (`*** --- ***`).
  - **S (Titik):** Tiga kilatan bernada cepat (Indikator ON: 150ms, OFF: 100ms).
  - **O (Garis):** Tiga kilatan bernada lambat (Indikator ON: 400ms, OFF: 100ms).
  - **S (Titik):** Kembali dengan tiga kilatan cepat.
- **Logika Eksekusi:** Saat satu siklus transmisi SOS selesai sepenuhnya, program melakukan jeda hening selama 5 detik, kemudian mengulangi proses transmisi tersebut dari awal secara terus-menerus.

### **3. Tugas Praktikum: SOS Multiwarna (`tugas_led_rgb.ino`)**
Implementasi komprehensif yang memadukan kontrol warna RGB dari _Project 1_ dan pembangkitan sinyal SOS dari _Project 2_.
- **Fungsi Utama:** Melakukan transmisi sinyal darurat SOS secara repetitif, namun dengan memberikan perubahan indikator warna pada setiap permulaan siklus.
- **Logika Eksekusi:**
  1. Mentransmisi siklus sinyal SOS menggunakan warna **Merah**, lalu ditahan selama 5 detik.
  2. Mentransmisi siklus sinyal SOS menggunakan warna **Hijau**, lalu ditahan selama 5 detik.
  3. Mentransmisi siklus sinyal SOS menggunakan warna **Biru**, ditahan 5 detik—lalu rotasi kembali bertukar menjadi warna Merah.

---

## **Konfigurasi Hardware (Pemetaan Pin ESP32)**

> **Catatan Penting:** Proyek ini didesain secara spesifik untuk jenis **LED RGB Common Cathode** (Katoda Umum). Pastikan kaki negatif dilekatkan pada pin `GND` papan mikrokontroler (ESP32) dan kaki-kaki warna dikontrol oleh logika aktif _HIGH_ sebagaimana yang sudah direncanakan dalam berkas `.ino`.

Berdasarkan desain fisik, integrasikan rangkaian komponen keras sesuai pemetaan pin di bawah ini:

| Modul Mikrokontroler | Pin Modul LED RGB (Common Cathode) |
| :---: | :--- |
| **GND** | Kaki Panjang Utma (Negatif / Katoda) |
| **Pin 15** | Kaki Kontrol Warna Merah (R / Red) |
| **Pin 16** | Kaki Kontrol Warna Hijau (G / Green) |
| **Pin 17** | Kaki Kontrol Warna Biru (B / Blue) |

---

## **Panduan Eksekusi Program**

Ikuti petunjuk di bawah untuk mengaplikasikan berkas ke modul Anda:

1. Buka file `.ino` (*sketch*) yang ingin Anda gunakan melalui aplikasi **Arduino IDE**.
2. Rangkai perangkat fisik LED pada *protoboard* dan *jumper wire* berdasarkan **[tabel pemetaan pin ESP32 di atas](#-konfigurasi-hardware-pemetaan-pin-esp32)**.
3. Sambungkan board ESP32 dengan komputer lewat kabel USB data. 
4. Di *Arduino IDE*: Pastikan Anda sudah menentukan *Board* pengembangan yang tepat (`Tools` > `Board`) beserta *Port* komunikasi eksekusinya (`Tools` > `Port`).
5. Klik ikon panah centang **Upload** *(Ctrl + U)*. Tunggu hingga proses unggah selesai dan muncul notifikasi "`Done uploading.`".
6. Aktifkan fitur **Serial Monitor** pada IDE (atau tekan gabungan tombol `Ctrl + Shift + M`). Setel _baud rate_ pada frekuensi `115200` baud untuk melihat antarmuka jejak (*debug logs*) dan pengamatan status mikrokontroler.
