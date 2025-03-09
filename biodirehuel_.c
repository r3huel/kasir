#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//deklarasi global variabel
int pilihan1, pilihan2 = 0; //simpan pilihan user
char barang[5][20] = {"Buku Tulis", "Pensil", "Penghapus", "Penggaris", "Bujur Sangkar"}; //array tempat simpan nama barang
int harga[5] = {5000, 2000, 1000, 1000, 500}; //array tempat simpan harga barang
char nama_barang[5][20]; //menyimpan barang yg dipilih user
int harga_barang[5];//menyimpan barang yg dipilih user
int jumlah[5];//menyimpan barang yg dipilih user
float diskon[5];//menyimpan barang yg dipilih user
int total_harga, total_diskon = 0;// Variabel total harga, diskon, dan pembayaran
int total_bayar, bayar;// Variabel total harga, diskon, dan pembayaran
int sorted_index[5] = {0, 1, 2, 3, 4};// Variabel untuk sorting barang berdasarkan jumlah
int last_index = 0;// Menyimpan jumlah barang yang sudah dipilih

//fungsi cetak =
void cetak_garis(int length) {
    for(int i=0; i<length; i++) {
        printf("=");
    }
}

//fungsi cetak -
void cetak_garis2(int length) {
    for(int i=0; i<length; i++) {
        printf("-");
    }
}

//cetak halaman awal
void cetak_pilihan() {
    printf("Selamat datang di Toko SKENSA.");
    printf("\n");
    printf("Silahkan pilih barang yang Anda inginkan:");
    printf("\n");
    printf("\n");
    cetak_garis(43);
    printf("\n");
    printf("|%-1s| %-23s | %-9s |", "No.", "Barang", "Harga");
    printf("\n");
    cetak_garis2(43);
    printf("\n");

    // Loop buat cetak daftar barang dan harga
    for(int i=0; i<5; i++) {
        printf("| %-1d | %-23s | Rp.%-6d |", i+1, barang[i], harga[i]);
        printf("\n");
    }

    cetak_garis(43);
    printf("\n");
    printf("99. Struk Pembayaran");
    printf("\n");
    printf("55. Reset Pilihan");
    printf("\n");
    printf("00. Keluar");
    printf("\n");
    cetak_garis(43);
    printf("\n");
}

//fungsi untuk mengecek diskon
float cek_diskon(int harga, int jumlah) {
    if(jumlah >= 5) {
        return jumlah * harga * 0.15; //diskon 15%
    } else if(jumlah >= 3) {
        return jumlah * harga * 0.1; //diskon 10%
    }
    return 0; //diskon 0% kalo dibawah =3
}

//fungsi untuk mengambil waktu sekarang kemudian return dalam string
char *get_time_now() {
    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    char *datetime = asctime(timeinfo);
    return datetime;
}

//fungsi untuk generate id
char *generate_ID() {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char *id = malloc(sizeof(char) * 20);
    sprintf(id, "%d%d%d%d%d%d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    return id;
}

//fungsi untuk cetak struk
void cetak_struk(int total_harga, int total_diskon, int total_bayar, int bayar, int kembalian) {
    FILE *file;
    char *id = generate_ID();
    char filename[50];
    sprintf(filename, "%s.txt", id);

    file = fopen(filename, "w"); //buka file txt
    fprintf(file,"=============================================================\n");
    fprintf(file,"|                        Toko SKENSA                        |\n");
    fprintf(file,"|            Jl. HOS Cokroaminoto No. 84, Denpasar          |\n");
    fprintf(file,"|                            Bali                           |\n");
    fprintf(file,"|                      Telp: 0816285791                     |\n");
    fprintf(file,"| ID Struk: %s                                      |\n", id);
    fprintf(file,"|===========================================================|\n");
    fprintf(file,"| %-16s | %-10s | %-10s | %-12s |\n", "Nama Barang", "Harga", "Total", "Diskon");
    fprintf(file,"|===========================================================|\n");

    // Loop buat masukin data barang yang dibeli // sorting
    for(int i=0; i<last_index; i++) {
        float total = jumlah[i] * harga_barang[i];
        fprintf(file,"| %dx %-13s | Rp.%-7d | Rp.%-7.0f | Rp.%-9.0f |\n", jumlah[i], nama_barang[i], harga_barang[i], total, diskon[i]);
    }
    fprintf(file,"|===========================================================|\n|                                                           |\n");
    fprintf(file,"|Total Harga   = Rp.%d,-                                 |\n", total_harga);
    fprintf(file,"|Total Diskon  = Rp.%d,-                                   |\n", total_diskon);
    fprintf(file,"|Tagihan       = Rp.%d,-                                  |\n", total_bayar);
    fprintf(file,"|Pembayaran    = Rp.%d,-                                   |\n", bayar);
    fprintf(file,"|Kembalian     = Rp.%d,-                                   |\n|                                                           |\n", kembalian);
    char *time_now = get_time_now();
    fprintf(file,"|Waktu/Hari : %s", time_now);
    fprintf(file,"=============================================================\n");
    fclose(file);

    printf("Struk anda telah dicetak pada file %s", filename);
    printf("\n");

    // buka file txt otomatis
    char command[100];
    sprintf(command, "notepad %s", filename);
    system(command);
}

int main(){
    // Reset variabel total
    total_harga = 0;
    total_diskon = 0;

    cetak_pilihan();
    while (1){
        printf("Input pilihan yang Anda inginkan: ");
        scanf("%d", &pilihan1);

        if (pilihan1 == 55){
            // Reset pilihan
            for(int i=0; i<5; i++){
                strcpy(nama_barang[i], "");
                jumlah[i] = 0;
                diskon[i] = 0;
                harga_barang[i] = 0;
            }
            last_index = 0;
            total_harga = 0;
            total_diskon = 0;
            printf("Pilihan telah direset!");
            printf("\n");
            printf("\n");
            continue;
        }

        //rekapan bayar
        if (pilihan1 == 99){
            if(last_index > 0) {
                // reset total sebelum menghitung ulang
                total_harga = 0;
                total_diskon = 0;

                printf("\nRekap Pesanan Barang");
                printf("\n");
                cetak_garis(100);
                printf("\n| %-3s | %-15s | %-15s | %-15s | %-15s | %-18s |\n", "No.", "Jumlah", "Nama Barang", "Harga", "Total", "Diskon");

                // sorting berdasarkan jumlah barang (banyak ke dikit)
                for(int i=0; i<last_index-1; i++) {
                    for(int j=0; j<last_index-i-1; j++) {
                        if(jumlah[sorted_index[j]] < jumlah[sorted_index[j+1]]) {
                            // tukar posisi indeks
                            int temp = sorted_index[j];
                            sorted_index[j] = sorted_index[j+1];
                            sorted_index[j+1] = temp;
                        }
                    }
                }

                for(int i=0; i<last_index; i++) {
                    int index = sorted_index[i];
                    float total = jumlah[index] * harga_barang[index];
                    // hitung ulang diskon sesuai posisi setelah sorting
                    diskon[index] = cek_diskon(harga_barang[index], jumlah[index]);

                    total_harga += total;
                    total_diskon += diskon[index];

                    printf("| %-3d | %-15d | %-15s | Rp.%-12d | Rp.%-12.0f | Rp.%-15.0f |\n", i+1, jumlah[index], nama_barang[index], harga_barang[index], total, diskon[index]);
                }
                cetak_garis(100);
                printf("\n");
                printf("\n");
                printf("Total Harga  = Rp.%d,-\n", total_harga);
                printf("Total Diskon = Rp.%d,-\n", total_diskon);
                total_bayar = total_harga - total_diskon;
                printf("Total Bayar  = Rp.%d,-\n", total_bayar);
                cetak_garis(100);
                printf("\n");
                printf("\n");
                printf("Masukkan uang bayar = ");
                scanf("%d", &bayar);
                printf("\n");
                while(bayar < total_bayar){
                    printf("Uang yang dimasukkan kurang!\n");
                    printf("Masukkan uang bayar = ");
                    scanf("%d", &bayar);
                }
                int kembalian = bayar - total_bayar;
                printf("Kembalian = Rp.%d\n", kembalian);
                cetak_struk(total_harga, total_diskon, total_bayar, bayar, kembalian);
                return 0;
            } else {
                printf("Anda belum memilih barang!\n\n");
            }
        }

        // Keluar program
        if (pilihan1 == 0 || pilihan1 == 00){
            printf("Terima kasih telah berbelanja di Toko SKENSA!\n");
            return 0;
        }

        // Pilih barang
        if(pilihan1 > 0 && pilihan1 <= 5){
            printf("Masukkan jumlah barang : ");
            scanf("%d", &pilihan2);
            printf("\n");

            int has = 0;
            for(int i=0; i<last_index; i++) {
                if(strcmp(barang[pilihan1 - 1], nama_barang[i]) == 0) {
                    jumlah[i] += pilihan2;
                    diskon[i] = cek_diskon(harga_barang[i], jumlah[i]);
                    has = 1;
                    break; // keluar dari loop jika barang sudah ditemukan
                }
            }

            if(!has) {
                strcpy(nama_barang[last_index], barang[pilihan1 - 1]);
                jumlah[last_index] = pilihan2;
                harga_barang[last_index] = harga[pilihan1 - 1];
                diskon[last_index] = cek_diskon(harga[pilihan1-1], jumlah[last_index]);
                last_index += 1;
            }

            printf("Keranjang anda : \n");
            for(int i=0; i<last_index; i++) {
                printf("%s (%dx)\n", nama_barang[i], jumlah[i]);
            }
            printf("\n");
        } else if (pilihan1 != 55 && pilihan1 != 99 && pilihan1 != 0 && pilihan1 != 00) {
            printf("Pilihan tidak valid! \n\n");
        }
    }
    return 0;
}
