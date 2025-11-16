#ifndef FUNGSI_H
#define FUNGSI_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 100
#define MAX_DURASI 7
#define DENDA_PER_HARI 1000

typedef struct {
    int id;
    char judul[100];
    char penulis[100];
    char kategori[50];
    int status; 
    int dipinjamCount;
} Buku;

typedef struct {
    int id;
    char nama[100];
    char username[50];
    char password[50];
} Anggota;
typedef struct {
    int idatmin;
    char namaatmin[100];
    char uname[50];
    char pw[50];
} Admin;

typedef struct {
    int idPinjam;
    int idBuku;
    int idAnggota;
    char tanggalPinjam[20];
    char tanggalKembali[20];
    int lamaPinjam;
    int denda;
} Peminjaman;

//searching machine
void cariBuku();
void tampilkanRanking();
void lihatRiwayatPeminjaman(int idAnggota);


// Fungsi buku
void tambahBuku();
void tampilkanBuku();
void editBuku();
void hapusBuku();

// Fungsi anggota
void daftarAnggota();
int loginAnggota();

// Fungsi pinjam
void pinjamBuku(int idAnggota);
void kembalikanBuku(int idAnggota);

// Login admin
void daftarAdmin();
int loginAdmin();

// Utilitas
void getTanggalSekarang(char *buffer);
int hitungSelisihHari(const char *awal, const char *akhir);

#endif
