# SoalShift_modul2_F08
Semoga berkah dan berhasil mengerjakan soal praktikum Sistem Operasi sampai selesai

1. Elen mempunyai pekerjaan pada studio sebagai fotografer. Suatu hari ada seorang klien yang bernama Kusuma yang meminta untuk mengubah nama file yang memiliki ekstensi .png menjadi "[namafile]_grey.png)". Karena jumlah file yang diberikan Kusuma tidak manusiawi, maka Elen meminta bantuan kalian untuk membuat suatu program C yang dapat mengubah nama secara otomatis dan diletakkan pada direktori /home/[user]/modul2/gambar.
Catatan : Tidak boleh menggunakan crontab.

<h3>Jawaban:</h3>

```
chdir("/");
DIR *dp;
struct dirent *ep;
//buka folder direktori
dp = opendir ("/home/zaky/Documents");
```

- Langkah pertama, kita membuka direktori dimana file berekstensi png berada, kebetulan kami menaruhnya di Documents.

```
while ((ep = readdir (dp)) != NULL){
```

- Langkah selanjutnya kita membaca isi direktorinya, jika masih ada isinya (belum NULL) maka program tersebut masih berjalan membaca isi direktorinya.

```
char *titik = strrchr(dupli, '.');
if (!titik)
    continue;
char *extensi = strdup(titik + 1);
if (strcmp (extensi, "png") == 0){
```
- Fungsi *strrchr* disitu berfungsi untuk mencari titik yang terletak sebelum file ekstensinya.
- Lalu fungsi *strdup* di program itu berfungsi untuk menduplikat nama ekstensinya, lalu diambil nilainya oleh variabel extensi.
- Selanjutnya kita bandingkan dengan *strcmp*, membandingkan isi dari extensi dengan "png" jika benar isi dari extensi adalah png maka bernilai "0".

```
strcat(dupli, "_grey.");
strcat(tempat, dupli);
strcat(tempat, extensi);
```
- Langkah terakhir kita mau menyelipkan  "_grey." dan ekstensi "png"nya dengan *strcat*.

 
 2. Pada suatu hari Kusuma dicampakkan oleh Elen karena Elen dimenangkan oleh orang lain. Semua kenangan tentang Elen berada pada file bernama “elen.ku” pada direktori “hatiku”. Karena sedih berkepanjangan, tugas kalian sebagai teman Kusuma adalah membantunya untuk menghapus semua kenangan tentang Elen dengan membuat program C yang bisa mendeteksi owner dan group dan menghapus file “elen.ku” setiap 3 detik dengan syarat ketika owner dan grupnya menjadi “www-data”. Ternyata kamu memiliki kendala karena permission pada file “elen.ku”. Jadi, ubahlah permissionnya menjadi 777. Setelah kenangan tentang Elen terhapus, maka Kusuma bisa move on.
Catatan: Tidak boleh menggunakan crontab

<h3>Jawaban:</h3>

```
struct stat stb;
char folderelen[30]="/home/zaky/hatiku/elen.ku";
stat(folderelen, &stb);
```
- Langkah pertama kita mau mengetahui status sistem filenya dari file elen.ku dengan *stat* 

```
struct passwd *pwd = getpwuid(stb.st_uid);
struct group *grp = getgrgid(stb.st_gid);
```
- Proses untuk bisa merubah dan menangkap nama baru owner dan group dari suatu file, dalam kasus ini filenya bernama "elen.ku"

```
char mydata[10]="www-data";
int usr=strcmp(pwd->pw_name, mydata);
int grup=strcmp(grp->gr_name, mydata);
```
- Proses ini untuk membandingkan nama owner dan group yang kita rubah dengan nama yang diminta dari soal yaitu "www-data"

```
if(usr==0 && grup==0){
		remove(folderelen);
	}
```
- Jika sama dengan 0 yang bernilai benar maka file elen.ku akan diremove/dihapus
- Akan tetapi soal meminta kita untuk men chmod 777 untuk mencegah permission pada file “elen.ku”, caranya dibawah ini ;

```
chmod ("/home/zaky/hatiku/elen.ku",  S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IWGRP|S_IXGRP|S_IROTH|S_IWOTH|S_IXOTH);
```

  3. Diberikan file campur2.zip. Di dalam file tersebut terdapat folder “campur2”. 
Buatlah program C yang dapat :
i)  mengekstrak file zip tersebut.
ii) menyimpan daftar file dari folder “campur2” yang memiliki ekstensi .txt ke dalam file daftar.txt. 
Catatan:  
Gunakan fork dan exec.
Gunakan minimal 3 proses yang diakhiri dengan exec.
Gunakan pipe
Pastikan file daftar.txt dapat diakses dari text editor

<h3>Jawaban:</h3>
  
  4. Dalam direktori /home/[user]/Documents/makanan terdapat file makan_enak.txt yang berisikan daftar makanan terkenal di Surabaya. Elen sedang melakukan diet dan seringkali tergiur untuk membaca isi makan_enak.txt karena ngidam makanan enak. Sebagai teman yang baik, Anda membantu Elen dengan membuat program C yang berjalan setiap 5 detik untuk memeriksa apakah file makan_enak.txt pernah dibuka setidaknya 30 detik yang lalu (rentang 0 - 30 detik).
Jika file itu pernah dibuka, program Anda akan membuat 1 file makan_sehat#.txt di direktori /home/[user]/Documents/makanan dengan '#' berisi bilangan bulat dari 1 sampai tak hingga untuk mengingatkan Elen agar berdiet.
- Contoh : File makan_enak.txt terakhir dibuka pada detik ke-1, Pada detik ke-10 terdapat file makan_sehat1.txt dan makan_sehat2.txt
- Catatan : dilarang menggunakan crontab
- Contoh nama file : makan_sehat1.txt, makan_sehat2.txt, dst

<h3>Jawaban:</h3>

- Variable “i” digunakan sebagai penomoran file makan_sehat#.txt.
- Membuat file dengan nama makan_sehat di dalam folder makanan.
- Strcat dibawah ini digunakan untuk menyelipkan nama, agar format file dapat sesuai yang diminta oleh soal.
```
char directory[200] = "/home/zaky/Documents/makanan/makan_sehat"; 
strcat(directory, makan); 
strcat(directory,".txt"); 
```
- Setiap file makan_sehat berhasil di write, “i” di increment.
- Membuat proses yang berjalan setiap 5 detik.
- Mengambil time dari program yang dijalankan lalu menyimpannya dalam variable timer.
- Stat digunakan untuk return informasi file, dan mengambil informasi berupa waktu akses dari file makan_enak.txt.
```
stat("/home/zaky/Documents/makanan/makan_enak.txt", &cek);
```
- Setelah didapatkan waktu saaat program dijalankan dan waktu terakhir file makan_enak.txt diakses, kemudian dicari selisih dari keduanya dengan menggunakan fungsi difftime.
```
if(difftime(time(&timer), cek.st_atime) <= 30) 
```
- jika difftime <= 30, maka akan dijalankan dalam rentang waktu 0-30 detik setelah file makan_enak diakses, setelah itu dibuatlah file makan_sehat#.txt.

5. Kerjakan poin a dan b di bawah:
Buatlah program c untuk mencatat log setiap menit dari file log pada syslog ke /home/[user]/log/[dd:MM:yyyy-hh:mm]/log#.log
Ket:
Per 30 menit membuat folder /[dd:MM:yyyy-hh:mm]
Per menit memasukkan log#.log ke dalam folder tersebut
‘#’ : increment per menit. Mulai dari 1
Buatlah program c untuk menghentikan program di atas.
NB: Dilarang menggunakan crontab dan tidak memakai argumen ketika menjalankan program.

<h3>Jawaban:</h3>
<h3>A</h3>

```
    sprintf(nampung, "%d", time.tm_mday);
    strcat(namafd, nampung);
    strcat(namafd, ":");
    sprintf(nampung, "%d", time.tm_mon+1);
    strcat(namafd, nampung);
    strcat(namafd, ":");
    sprintf(nampung, "%d", time.tm_year+1900);
    strcat(namafd, nampung);
    strcat(namafd, "-");
    sprintf(nampung, "%d", time.tm_hour);
    strcat(namafd, nampung);
    strcat(namafd, ":");
    sprintf(nampung, "%d", time.tm_min);
    strcat(namafd, nampung);
```

- Langkah pertama kita membuat format foldernya dengan menggunakan fungsi dengan variabel "fname".
- Lalu di dalam fungsi tersebut kita akan menggunakan "strcat" untuk menyelipkan/menambahkan format nama filenya dan "sprintf" untuk menampung nilai-nilai waktu yang kita ambil dengan (tm_mday : hari, tm_mon : bulan, tm_year : tahun, tm_hour : jam, dan dan tm_min : menit).

```
char folder[200];
memset(&folder, 0, sizeof(folder));
strcat(folder, fname(1));

strcat(namapath, folder);
mkdir(namapath, S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IWGRP|S_IXGRP|S_IROTH|S_IWOTH|S_IXOTH);
```
- Proses ini berfungsi untuk membuat folder dengan chmod 777, akan tetapi jika di pemrograman c kita menggunakan (S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IWGRP|S_IXGRP|S_IROTH|S_IWOTH|S_IXOTH) agar bisa di write,read,execute oleh owner, group, dan other

```
if (diff==1)
	    {
		memset(&sebelum, 0, sizeof(sebelum));
		strcat(sebelum, fname(1));
		memset(&alterFolder, 0, sizeof(alterFolder));
		strcat(alterFolder, fname(0));
	    }
```
- Kondisi dimana untuk mengganti nama folder yang baru formatnya sesuai dengan pertambahan waktu yang telah diatur

```
char flagchar[200];
memset(&flagchar, 0, sizeof(flagchar));
sprintf(flagchar, "%d", tanda+1);
strcat (artlog, flagchar);
strcat (artlog, ".log");
```
- Code di atas merupakan proses untuk format nama filenya yang nilainya bertambah secara urut

```
FILE *baca = fopen ((char*)pathsyslog, "r");
FILE *pindah = fopen ((char*)artlog, "w");
```
- Code di atas untuk membaca isi filenya dengan "r" lalu diwrite "w" ke file yang lainnya
- Tapi untuk mengeceknya isi file itu sudah habis atau belum kita menggunakan EOF
```
while ((konten = fgetc(baca))!=EOF){
	fputc(konten,pindah);
}
```
```
if(tanda%30==0)
	break;
```
- Berfungsi memberhentikan pertambahan file di setiap pertambahan folder di menit 30

<h3>B</h3>

- Kita disuruh untuk memberhentikan program yang berjalan pada soal A
- Maka dari itu kita menggunakan exec dan "killalll" file outputnya, caranya sebagai berikut ;
```
  char *argv[3] = {"killall", "test_nomer5", NULL};
  //lalu diexecv
```
