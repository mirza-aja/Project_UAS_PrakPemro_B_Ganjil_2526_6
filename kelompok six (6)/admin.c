#include "fungsi.h"

void daftarAdmin() {
    FILE *fp = fopen("data/admin.txt", "a+");
    Admin z; 
    printf("Masukkan ID atmin: "); scanf("%d", &z.idatmin);
    getchar();
    printf("Nama: "); fgets(z.namaatmin, 100, stdin); z.namaatmin[strcspn(z.namaatmin, "\n")] = 0;
    printf("Username: "); scanf("%s", z.uname);
    printf("Password: "); scanf("%s", z.pw);
    fwrite(&z, sizeof(Admin), 1, fp);
    fclose(fp);
    printf("Pendaftaran anggota berhasil!\n");
}

int loginAdmin() {
    FILE *fp = fopen("data/admin.txt", "r");
    char user[50], pass[50];
    Admin z;
    printf("Username: "); scanf("%s", user);
    printf("Password: "); scanf("%s", pass);
    while (fread(&z, sizeof(Admin), 1, fp)) {
        if (strcmp(z.uname, user) == 0 && strcmp(z.pw, pass) == 0) {
            fclose(fp);
            return 0;
        }
    }
    fclose(fp);
    printf("Login gagal.\n");
    return -1;
}
