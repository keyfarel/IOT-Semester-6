# **Pertemuan 007 - Praktikum IoT (Internet of Things)**

Repositori ini berisi kumpulan kode Arduino (sketch) untuk praktikum dan tugas pada **Pertemuan 007**. Tujuan utama dari modul ini adalah mempelajari penggunaan modul display OLED (berbasis I2C), melakukan pemindaian alamat I2C, serta mengintegrasikan tampilan visual dengan sensor suhu DHT11, modul WiFi, dan *NTP Server* untuk membuat prototipe *Smart Home Clock* interaktif menggunakan mikrokontroler ESP32.

---

## **Daftar Proyek**

Di dalam repositori ini terdapat lima program utama, masing-masing mendemonstrasikan tahapan fungsionalitas yang berbeda:

### **1. Pemeriksaan Alamat I2C (`led_address_checking.ino`)**
Program utilitas dasar untuk memindai port I2C yang aktif.
- **Fungsi Utama:** Mendeteksi perangkat komunikasi I2C yang terhubung (seperti layar OLED) dan menampilkan alamat heksadesimalnya pada kontrol *Serial Monitor*.
- **Logika Eksekusi:** Melakukan iterasi pemindaian alamat I2C dari rentang 1 hingga 127 dan mencoba menjalin transmisi data. Jika sukses dan terdapat konfirmasi perangkat, maka alamat akan dicetak. Status dipindai berulang setiap 3 detik.

### **2. Teks Berjalan Dasar pada OLED (`lcd_display.ino`)**
Pengantar dasar penggunaan library komprehensif *U8g2* untuk mengontrol layar OLED secara monokromatik.
- **Fungsi Utama:** Menampilkan teks diam ("Polinema") dan teks animasi berjalan ("Kelas IoT.").
- **Logika Eksekusi:** Menggunakan iterasi *looping* untuk memanipulasi nilai parameter koordinat mendatar (`x`) pada penggambaran karakter sehingga menciptakan efek *scrolling* pergeseran dari luar piksel kanan menuju ujung kiri batas layar.

### **3. Modifikasi Tampilan OLED Lanjutan (`lcd_modify.ino`)**
Pengembangan dari program teks sederhana dengan tambahan komponen bentuk geometris untuk mendesain antarmuka (UI) yang lebih elegan.
- **Fungsi Utama:** Menyajikan bentuk antarmuka visual yang lebih rapi menggunakan komposisi *border*/bingkai bertepi lengkung, perataan posisi teks menengah ("Key Firdausi"), pemisah garis grafis horisontal, dan pesan teks yang bergerak ("Praktikum IoT - D4 Teknik Informatika").
- **Logika Eksekusi:** Menggambar instrumen garis, sudut, dan perataan rasio karakter absolut di belakang layar kompilasi memori internal sebelum secara serempak diproyeksikan (`sendBuffer()`) guna menciptakan kelancaran animasi berkecepatan 10 milidetik *delay*.

### **4. Jam Smart Home Terintegrasi (`smart_home_clock.ino`)**
Puncak integrasi sistem dari pertemuan sebelumnya dengan menggabungkan kapabilitas antarmuka internet (WiFi), pelacakan dan sinkronisasi waktu aktual secara independen (*NTP Server*), kalkulasi termal sensor (DHT11), dan panel instrumen (*dashboard*) perantara layar OLED.
- **Fungsi Utama:** Mempresentasikan waktu *real-time*, rekaman tanggal sistem, nilai suhu parameter (°C & °F) dalam desain panel *dashboard* terstruktur, serta memproyeksikan perwakilan aktuator respon termal dalam spektrum spektrum warna lampu pada modul LED RGB.
- **Logika Eksekusi:** Membangkitkan proses verifikasi otentikasi sandi (WiFi) dengan dilengkapi animasi visual interaktif (*progress bar loading*) secara otonom saat *startup*. Apabila sudah terbentuk integrasi lokal (mendapatkan *IP Address*), perangkat akan menyelaraskan mesin waktu asinkron dari *pool.ntp.org*. Sesudahnya, panel ditimpa secara rutin menampilkan nilai bacaan *temperature*. LED akan menampilkan nyala dinamis berdasarkan matriks (Dingin: Hijau `< 25°C`, Rentang Aman: Biru `25-30°C`, Ekstrem Panas: Merah `> 30°C`).

### **5. Simulasi Jam Smart Home (`smart_home_clock_simulations.ino`)**
Versi pengujian validasi dari jam *Smart Home* yang mengganti angka *output* suhu alami menjadi nilai buatan terprogram (data *dummy* termutasi) yang berguna mempercepat siklus observasi antarmuka pergantian status respon warna LED maupun nilai di monitor.
- **Fungsi Utama:** Metode simulasi (*hardware interface testing*) terhadap perpindahan kelap-kelip lampu RGB berbasis parameter kondisi berurutan secara cepat menggunakan injeksi fungsi kode dan mengabaikan interaksi kontak di dunia nyata.
- **Logika Eksekusi:** Melabrak bacaan sirkuit data asli termik (DHT11) dengan nilai *statik* termodifikasi bertahap dari basis 22.0°C. Proyeksi berosilasi secara mandiri melompat naik dengan selisih konstan 1°C per detik hingga mencetak limit maksimal (32.0°C), lalu grafiknya akan menukik menurun mundur layaknya siklus *ping-pong*. Indikator kelap-kelip LED maupun *layout* monitor OLED akan bekerja normal mersepon variabel artifisial ini secara proaktif.

---

## **Konfigurasi Hardware (Pemetaan Pin ESP32)**

> **Catatan Penting:** Proyek ini bergantung pada kelengkapan ketersambungan *hardware* yakni **Layar OLED I2C**, **Sensor DHT11**, dan aktuator semacam **LED RGB Common Cathode**. Modul layar OLED diprogram untuk menyesuaikan pin I2C *default* perangkat periferal ESP32, yakni pada perpaduan jalur transmisi *SDA* (Pin 21) dan denyut *SCL* (Pin 22).

Mengacu pada arsitektur *wiring* sirkuit perakitannya, jalinkan setiap polaritas komponen sesuai deskripsi rel tabel pemetaan berikut:

| Modul Mikrokontroler | Komponen yang Dihubungkan |
| :---: | :--- |
| **GND** | Konduktor Negatif (-) milik Sensor DHT11, Layar OLED, dan LED RGB |
| **3.3V / 5V** | Suplai VCC atau Positif (+) untuk modul pengukuran DHT11 & Layar OLED |
| **Pin 4** | Kanal Distribusi (*Data*) Sensor DHT11 |
| **Pin 15** | Kaki Kontrol Kecerahan LED RGB - Corak Merah (R / *Red*) |
| **Pin 16** | Kaki Kontrol Kecerahan LED RGB - Corak Hijau (G / *Green*) |
| **Pin 17** | Kaki Kontrol Kecerahan LED RGB - Corak Biru (B / *Blue*) |
| **Pin 21 (SDA)** | Terminal Lalulintas Data (*SDA*) pada bus transmisi Layar OLED I2C |
| **Pin 22 (SCL)** | Terminal Pembangkit Sinyal Jam (*SCL*) sinkronisasi Layar OLED I2C |

---

## **Panduan Eksekusi Program**

Ikuti prosedur sekuensial langkah esensial berikut guna menerjemahkan instruksi pada modul elektronika ESP32:

1. Akses spesifik fail berformat `.ino` (*Arduino sketch*) yang ingin dikompilasi ke memori mikrokontroler dengan perangkat lunak **Arduino IDE**.
2. Rangkum integrasi dan rakit elemen terpisah mencakup Layar OLED, Sensor DHT11, berikut LED RGB pada hamparan modul *breadboard* atau perantara kabel konektor (*jumper wires*). Rujuk detail penempatan menurut referensi **[tabel panduan matriks konfigurasi piranti keras atas](#-konfigurasi-hardware-pemetaan-pin-esp32)**.
3. Kunci konektivitas penghantar dari papan utama ESP32 yang sedang mati atau minim listrik menuju terminal portal masuk data gawai komputer memelopori kabel format USB mikro.
4. Apabila mengeksekusi integrasi WiFi (`smart_home_clock.ino` / `-simulations.ino`), jangan lupa sesuaikan konfigurasi parameter `ssid` dan variabel `password` terhadap *router* area lokal atau mode transmisi nirkabel *hotspot* seluler Anda pribadi.
5. Jalankan aplikasi *Arduino IDE*. Evaluasi konfigurasi modul dengan memilih preferensi *Board* (`Tools` > `Board` > seri ESP32 relevan) yang sejajar dengan identifikasi protokol serial letak *Port* baca PC (`Tools` > `Port`).
6. Antisipasi ketiadaan repositori *Library*, persiapkan perpustakaan eksternal fungsional dasar yang diperlukan (di bagian menu fitur `Sketch` > `Include Library` > `Manage Libraries`). Repositori utamanya yaitu, instalasi profil pengolah antarmuka bernama **U8g2** (dikembangkan *oliver*) guna mengaktivasi integrasi OLED, disamping pustaka pengukuran sensor **SimpleDHT**.
7. Inisialisasi proses konversi sintaks bahasa manusia lalu transmisi menggunakan instruksi ketukan opsi **Upload** (diwajahkan dengan logo ikon panah menyemping kanan bundar atau kombinasi tombol `Ctrl + U`). Antisipasi penyelesaian integrasi unggahan menanti instruksi berpesan "`Done uploading.`".
8. Gunakan pemantauan operasional pada mode fitur *Serial Monitor* (menekan silang fungsional ikon bersimbol teropong kaca pembesar atau pemanggilan praktis tombol gabungan `Ctrl + Shift + M`). Evaluasi transmisi frekuensi serial (sebagai jejak identifikasi masalah / *debug tracing*) menyertakan pemilihan kustom skala *baud rate* menuju resolusi kecepatan pembacaan setara `115200` baud.
