#include "fungsi.h"

void getTanggalSekarang(char *buffer) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(buffer, "%02d-%02d-%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
}

int hitungSelisihHari(const char *awal, const char *akhir) {
    struct tm t1 = {0}, t2 = {0};
    sscanf(awal, "%d-%d-%d", &t1.tm_mday, &t1.tm_mon, &t1.tm_year);
    sscanf(akhir, "%d-%d-%d", &t2.tm_mday, &t2.tm_mon, &t2.tm_year);
    t1.tm_mon--; t2.tm_mon--; t1.tm_year -= 1900; t2.tm_year -= 1900;
    time_t time1 = mktime(&t1), time2 = mktime(&t2);
    return (int)difftime(time2, time1) / (60 * 60 * 24);
}

void pinjamBuku(int idAnggota) {
    FILE *fb = fopen("data/buku.txt", "r+");
    FILE *fp = fopen("data/pinjam.txt", "a+");
    Buku b; Peminjaman p;
    int idBuku, found = 0;

    printf("Masukkan ID buku yang ingin dipinjam: ");
    scanf("%d", &idBuku);
    while (fread(&b, sizeof(Buku), 1, fb)) {
        if (b.id == idBuku && b.status == 1) {
            found = 1;
            b.status = 0;
            b.dipinjamCount++;
            fseek(fb, -sizeof(Buku), SEEK_CUR);
            fwrite(&b, sizeof(Buku), 1, fb);
            getTanggalSekarang(p.tanggalPinjam);
            strcpy(p.tanggalKembali, "-");
            p.idBuku = idBuku;
            p.idAnggota = idAnggota;
            p.denda = 0;
            fwrite(&p, sizeof(Peminjaman), 1, fp);
            printf("Buku berhasil dipinjam pada tanggal %s\n", p.tanggalPinjam);
            break;
        }
    }
    fclose(fb); fclose(fp);
    if (!found) printf("Buku tidak tersedia.\n");
}

void kembalikanBuku(int idAnggota) {
    FILE *fp = fopen("data/pinjam.txt", "r+");
    FILE *fb = fopen("data/buku.txt", "r+");
    Peminjaman p; Buku b; int idBuku, found = 0;
    char tglSekarang[20];

    printf("Masukkan ID buku yang dikembalikan: ");
    scanf("%d", &idBuku);
    getTanggalSekarang(tglSekarang);

    while (fread(&p, sizeof(Peminjaman), 1, fp)) {
        if (p.idBuku == idBuku && p.idAnggota == idAnggota && strcmp(p.tanggalKembali, "-") == 0) {
            found = 1;
            strcpy(p.tanggalKembali, tglSekarang);
            p.lamaPinjam = hitungSelisihHari(p.tanggalPinjam, p.tanggalKembali);
            if (p.lamaPinjam > MAX_DURASI)
                p.denda = (p.lamaPinjam - MAX_DURASI) * DENDA_PER_HARI;

            fseek(fp, -sizeof(Peminjaman), SEEK_CUR);
            fwrite(&p, sizeof(Peminjaman), 1, fp);

            rewind(fb);
            while (fread(&b, sizeof(Buku), 1, fb)) {
                if (b.id == idBuku) {
                    b.status = 1;
                    fseek(fb, -sizeof(Buku), SEEK_CUR);
                    fwrite(&b, sizeof(Buku), 1, fb);
                    break;
                }
            }
            printf("Buku dikembalikan pada %s. Denda: Rp%d\n", tglSekarang, p.denda);
            break;
        }
    }
    fclose(fp); fclose(fb);
    if (!found) printf("Data peminjaman tidak ditemukan.\n");
}
void lihatRiwayatPeminjaman(int idAnggota) {
    FILE *fp = fopen("data/pinjam.txt", "r");
    if (!fp) { printf("Belum ada data peminjaman.\n"); return; }
    Peminjaman p;
    int found = 0;
    printf("\n=== RIWAYAT PEMINJAMAN ANDA ===\n");
    while (fread(&p, sizeof(Peminjaman), 1, fp)) {
        if (p.idAnggota == idAnggota) {
            printf("ID Buku: %d | Tgl Pinjam: %s | Tgl Kembali: %s | Denda: Rp%d\n",
                   p.idBuku, p.tanggalPinjam, p.tanggalKembali, p.denda);
            found = 1;
        }
    }
    if (!found) printf("Belum ada riwayat peminjaman.\n");
    fclose(fp);
}
