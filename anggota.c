#include "fungsi.h"

void daftarAnggota() {
    FILE *fp = fopen("data/anggota.txt", "a+");
    Anggota a;
    printf("Masukkan ID anggota: "); scanf("%d", &a.id);
    getchar();
    printf("Nama: "); fgets(a.nama, 100, stdin); a.nama[strcspn(a.nama, "\n")] = 0;
    printf("Username: "); scanf("%s", a.username);
    printf("Password: "); scanf("%s", a.password);
    fwrite(&a, sizeof(Anggota), 1, fp);
    fclose(fp);
    printf("Pendaftaran anggota berhasil!\n");
}

int loginAnggota() {
    FILE *fp = fopen("data/anggota.txt", "r");
    char user[50], pass[50];
    Anggota a;
    printf("Username: "); scanf("%s", user);
    printf("Password: "); scanf("%s", pass);
    while (fread(&a, sizeof(Anggota), 1, fp)) {
        if (strcmp(a.username, user) == 0 && strcmp(a.password, pass) == 0) {
            fclose(fp);
            return a.id;
        }
    }
    fclose(fp);
    printf("Login gagal.\n");
    return -1;
}
