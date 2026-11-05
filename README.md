# oprec-sar-2026-ARYAKAVI-RADITYA-IMARAN
# Jawaban Challenge Task Software SAR 2026

## Q1 - Servo capit

### a

Rumus asli: `500 + 1900 * deg / 180`.

| `deg` | Pulsa |
|---:|---:|
| 72 | 1260 µs |
| 90 | 1450 µs |
| 200 | 2611 µs |
| -10 | 395 µs |

Nilai `200°` dan `-10°` berbahaya karena keluar dari rentang servo 0–180° dan pulsa 500–2400.

### b

```c
int deg_to_us(int deg) {
  if (deg < 0) deg = 0;
  if (deg > 180) deg = 180;
  return 500 + 1900 * deg / 180;
}
```

### c

Capit depan: `72° = 1260`.

Capit belakang: `90° = 1450`.

## Q2 - Korban atau dummy?

### a

Fungsi hanya memeriksa `cls == 1`. Kasus yang salah lolos:

1. Korban dengan confidence `0.2` tetap lolos.
2. Korban dengan umur deteksi `1500 ms` tetap lolos.
3. Korban dengan confidence rendah dan data basi tetap lolos.

Dummy tetap ditolak, tetapi syarat confidence dan umur belum diperiksa.

### b

```c
bool mau_ambil(det_t d) {
  return d.cls == 1 && d.age_ms < 1000 && d.conf >= 0.5f;
}
```

### c

Robot mengejar korban dengan confidence `0.9`, tetapi tidak langsung mengambilnya jika jarak tidak diketahui. Dummy tetap ditolak karena `cls == 0`. Robot perlu mencari jarak atau melakukan konfirmasi ulang. Mengejar dummy dapat membuat misi gagal.

## Q3 - Lengan 2-joint

### a

Dengan `q1 = 30°` dan `q2 = 60°`, maka `q1 + q2 = 90°`.

```text
x = 120(0.866) + 60(0) = 103.92 mm
z = 120(0.5) + 60(1) = 120.00 mm
```

Posisi capit adalah sekitar **(103.92 mm, 120.00 mm)**.

### b

Jangkauan maksimum saat lengan lurus:

```text
L1 + L2 = 120 + 60 = 180 mm
```

Jangkauan minimum saat lengan melipat penuh:

```text
|L1 - L2| = |120 - 60| = 60 mm
```

### c

Untuk `(-40, 140)`:

```text
sqrt((-40)^2 + 140^2) = sqrt(21200) = 145.60 mm
```

Titik ini **di dalam jangkauan**.

Untuk `(-100, 80)`:

```text
sqrt((-100)^2 + 80^2) = sqrt(16400) = 128.06 mm
```

Titik ini juga **di dalam jangkauan**.

## Q4 - Jalan yang benar

### a

Dengan `tran_ms = 320`:

| Speed | Stride diminta | Stride nyata |
|---:|---:|---:|
| 50 mm/s | 16 mm | 16 mm |
| 100 mm/s | 32 mm | 32 mm |
| 150 mm/s | 48 mm | 35 mm |
| 200 mm/s | 64 mm | 35 mm |

Batas mulai memotong pada:

```text
speed = 35 × 1000 / 320 = 109.375 mm/s
```

Di atas sekitar `109.4 mm/s`, stride nyata tidak bertambah. Karena itu, menambah speed hanya menambah perintah, bukan jarak setiap langkah.

### b

1. Uji kecepatan `50, 75, 100, 110, 125, dan 150 mm/s`.
2. Jalankan robot lurus sejauh 1 meter pada permukaan yang sama.
3. Ulangi setiap kecepatan minimal tiga kali.
4. Ukur waktu tempuh, drift arah dalam derajat, dan jumlah kaki yang selip.
5. Pilih speed tercepat yang tidak memotong stride, drift tetap dalam batas arena, dan selip berada di bawah batas aman.

Saya akan mulai dari 50 mm/s, lalu menaikkan speed bertahap agar risiko jatuh dan keluar jalur kecil.

### c

Koreksi harus berlawanan arah dengan bias. Besar koreksi minimal:

```text
4.5 / 13.7 = 0.3285 rad/s
```

Batas `0.35 rad/s` cukup karena `0.35 > 0.3285`. Sisa margin hanya sekitar `0.0215 rad/s`, sehingga feed-forward sekitar `-0.3285 rad/s` perlu dikalibrasi sesuai tanda bias. Jika noise membuat koreksi sering mentok, turunkan speed atau naikkan batas koreksi secara aman.

## Q5 — Melihat korban

### a

Korban tepat di depan hidung berarti sudut badan harus `0°`. Kamera membaca `+6°`, jadi:

```text
trim = 0 - 6 = -6°
```

Untuk `KORBAN 6.0 500 0.87`:

```text
b = 6 - 6 - atan2(50, 500) × 57.2958
b = 0 - 5.7106
b ≈ -5.71°
```

### b

Aturan `boleh_ambil`:

1. Tolak `DUMMY` selalu.
2. Tolak data dengan umur `>= 1000 ms`.
3. Tolak confidence `< 0.5`.
4. Jika jarak `<= 0` dan ada korban lain dengan jarak diketahui, tolak deteksi tersebut.

Dummy bukan target misi. Data basi dapat membuat robot bergerak menuju posisi lama. Confidence rendah meningkatkan risiko mengejar objek yang salah. Jarak tidak diketahui membuat pendekatan dan pengangkatan tidak aman jika ada target yang informasinya lebih lengkap.

### c

Robot tidak mengejar dummy. Robot boleh mendekati posisi secara perlahan sambil meminta konfirmasi beberapa frame berikutnya untuk korban dengan confidence `0.55`. Robot mengambil hanya setelah korban tetap terdeteksi, kelasnya konsisten, dan jaraknya masuk akal.

Jika langsung memilih dummy, misi dapat gagal. Jika terlalu cepat mengabaikan korban, robot kehilangan waktu dan kesempatan misi.

Dua penyebab confidence menipu:

1. Cahaya berubah atau pantulan membuat warna orange terlihat seperti objek lain. Atasi dengan exposure/white balance terkunci dan verifikasi beberapa frame.
2. Oklusi atau sudut korban 45° menyembunyikan lengan. Atasi dengan mendekat pelan, mengubah sudut pandang, dan memakai konsistensi temporal.

## Penggunaan AI

AI dipakai untuk membantu menghitung nilai numerik, dan mendebugging atau test apakah kode sesuai. Keputusan, pemeriksaan hasil, dan penjelasan jawaban harus dipahami serta diverifikasi sebelum interview.