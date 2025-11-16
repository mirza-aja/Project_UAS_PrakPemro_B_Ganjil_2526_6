#include "fungsi.h"

//biar cpet😅    
//gcc main.c buku.c anggota.c admin.c pinjam.c -o perpustakaan


void menuAdmin(int idatmin) {
    int pilih;
    do {
        printf("\n=== MENU ADMIN ===\n");
        printf("1. Tambah Buku\n2. Lihat Buku\n3. Edit Buku\n4. Hapus Buku\n5. Daftar Anggota\n6. Cari Buku\n7. Rngking Buku\n0. Logout\nPilih: ");
        scanf("%d", &pilih);
        switch (pilih) {
            case 1: tambahBuku(); break;
            case 2: tampilkanBuku(); break;
            case 3: editBuku(); break;
            case 4: hapusBuku(); break;
            case 5: daftarAnggota(); break;
            case 6: cariBuku(); break;
            case 7: tampilkanRanking(); break;
        }
    } while (pilih != 0);
}

void menuAnggota(int id) {
    int pilih;
    do {
        printf("\n=== MENU ANGGOTA ===\n");
        printf("1. Lihat Buku\n2. Pinjam Buku\n3. Kembalikan Buku\n4. Lihat Riwayat Peminjaman\n0. Logout\nPilih: ");
        scanf("%d", &pilih);
        switch (pilih) {
            case 1: tampilkanBuku(); break;
            case 2: pinjamBuku(id); break;
            case 3: kembalikanBuku(id); break;
            case 4: lihatRiwayatPeminjaman(id); break;
        }
    } while (pilih != 0);
}

int main() {
    system("mkdir -p data");
    int pilih;
    do {
        printf("\n=== SISTEM PERPUSTAKAAN MINI ===\n");
        printf("1. Login Admin\n2. Login Anggota\n3. Daftar Anggota\n4. Daftar Admin\n0. Keluar\nPilih: ");
        scanf("%d", &pilih);
        if (pilih == 1) {
            int idatmin = loginAdmin();
            if (idatmin != -1) menuAdmin(idatmin);
            }else if (pilih == 4) {
            daftarAdmin();
            }
            
            else if (pilih == 2) {
            int id = loginAnggota();
            if (id != -1) menuAnggota(id);
        } else if (pilih == 3) daftarAnggota();
    } while (pilih != 0);
    printf("Terima kasih telah menggunakan sistem ini!\n");
    return 0;
}
