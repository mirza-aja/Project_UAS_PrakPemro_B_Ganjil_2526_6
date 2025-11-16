#include "fungsi.h"

void tambahBuku() {
    FILE *fp = fopen("data/buku.txt", "a+");
    Buku b;
    printf("Masukkan ID buku: "); scanf("%d", &b.id);
    getchar();
    printf("Judul: "); fgets(b.judul, 100, stdin); b.judul[strcspn(b.judul, "\n")] = 0;
    printf("Penulis: "); fgets(b.penulis, 100, stdin); b.penulis[strcspn(b.penulis, "\n")] = 0;
    printf("Kategori (Fiksi/Non-Fiksi/Komik/Majalah/Referensi): ");
    fgets(b.kategori, 50, stdin); b.kategori[strcspn(b.kategori, "\n")] = 0;
    b.status = 1;
    b.dipinjamCount = 0;
    fwrite(&b, sizeof(Buku), 1, fp);
    fclose(fp);
    printf("Buku berhasil ditambahkan!\n");
}

void tampilkanBuku() {
    FILE *fp = fopen("data/buku.txt", "r");
    Buku b;
    printf("\n=== DAFTAR BUKU ===\n");
    while (fread(&b, sizeof(Buku), 1, fp)) {
        printf("ID: %d | %s (%s) - %s | %s\n",
               b.id, b.judul, b.penulis, b.kategori,
               b.status ? "Tersedia" : "Dipinjam");
    }
    fclose(fp);
}

void editBuku() {
    FILE *fp = fopen("data/buku.txt", "r+");
    Buku b; int id, found = 0;
    printf("Masukkan ID buku yang ingin diedit: ");
    scanf("%d", &id);
    while (fread(&b, sizeof(Buku), 1, fp)) {
        if (b.id == id) {
            found = 1;
            getchar();
            printf("Judul baru: "); fgets(b.judul, 100, stdin);
            b.judul[strcspn(b.judul, "\n")] = 0;
            fseek(fp, -sizeof(Buku), SEEK_CUR);
            fwrite(&b, sizeof(Buku), 1, fp);
            break;
        }
    }
    fclose(fp);
    if (found) printf("Buku berhasil diedit!\n");
    else printf("Buku tidak ditemukan.\n");
}

void hapusBuku() {
    FILE *fp = fopen("data/buku.txt", "r");
    FILE *temp = fopen("data/temp.txt", "w");
    Buku b; int id;
    printf("Masukkan ID buku yang akan dihapus: ");
    scanf("%d", &id);
    while (fread(&b, sizeof(Buku), 1, fp)) {
        if (b.id != id)
            fwrite(&b, sizeof(Buku), 1, temp);
    }
    fclose(fp); fclose(temp);
    remove("data/buku.txt");
    rename("data/temp.txt", "data/buku.txt");
    printf("Buku berhasil dihapus!\n");
}
