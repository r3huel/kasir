#include <stdio.h>   // Untuk mengelola input/output seperti printf, scanf, fopen, fclose, dll.
#include <stdlib.h>  // Untuk fungsi seperti malloc, free, system, dll.
#include <string.h>  // Untuk manipulasi string seperti strcpy, strcmp, dll.
#include <time.h>    // Untuk mengelola waktu dan tanggal seperti time(), localtime(), asctime().


//deklarasi variabel global
int pilihan1, pilihan2 = 0;                                                                 //simpen input pilihan user
char barang[5][20] = {"Buku Tulis", "Pensil", "Penghapus", "Penggaris", "Bujur Sangkar"};   //array string barang yg dijual
int harga[5] = {5000, 2000, 1000, 2000, 500};                                               //array integer harga barang
char nama_barang[5][20];                                                                    //array yg menyimpan barang yg dipilih
int harga_barang[5];                                                                        //array yg menyimpan harga barang yg dipilih
int jumlah[5];                                                                              //array yg menyimpan jumlah barang yg dipilih
float diskon[5];                                                                            //array yg menyimpan diskon barang
int total_harga, total_diskon = 0;                                  //menyimpan total harga dari barang yg dipilih dan total diskon dari barang yg dipilih
int total_bayar, bayar;                                    //menyimpan total bayar barang yg dipilih setelah dikurangi diskon dan nominal uang yg dibayarkan
int sorted_index[5] = {0,1,2,3,4};                                                          //array yg menyimpan indeks barang
int last_index = 0;                                                                         //menyimpan jumlah barang yg udah dipilih

//fungsi untuk cetak garis
void cetak_garis(int length) {
    for(int i=0; i<length; i++) {
        printf("=");
    }
}

//fungsi untuk cetak pilihan
void cetak_pilihan() {
    cetak_garis(14);
    printf("TOKO SKENSA");
    cetak_garis(14);
    printf("\n\n");

    cetak_garis(39);
    printf("\n| %-3s | %-15s | %-11s |\n", "No.", "Nama Barang", "Harga");
    cetak_garis(39);
    printf("\n");

    for(int i=0; i<5; i++){
        printf("| %-3d | %-15s | Rp%-8d |\n", i+1, barang[i], harga[i]);
    }

    cetak_garis(39);
    printf("\n99. Struk Pembayaran\n");
    printf("55. Reset\n");
    printf("00. Keluar\n");
    cetak_garis(39);
    printf("\n");
}

//fungsi untuk mengecek diskon
float cek_diskon(int jumlah, int harga) {
    if(jumlah > 5) {
        return jumlah * harga * 0.15;
    }else if(jumlah > 3) {
        return jumlah * harga * 0.1;
    }
}

//fungsi untuk mengambil waktu sekarang saat ini dan mengembalikannya dalam bentuk string.
char *get_time_now() {
    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    char *datetime = asctime(timeinfo);
    return datetime;
}

//fungsi untuk men-generate id
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

    file = fopen(filename, "w");
    fprintf(file,"=========================================================================\n");
    fprintf(file,"                               Toko SKENSA                               \n");
    fprintf(file,"                   Jl. HOS Cokroaminoto No 84 Denpasar                   \n");
    fprintf(file,"                                  Bali                                   \n");
    fprintf(file,"                             Telp: 0816285791                            \n");
    fprintf(file,"=========================================================================\n");
    fprintf(file,"| %-18s | %-11s | %-11s | %-11s |\n", "Nama Barang", "Harga", "Total Harga", "Diskon");
    for(int i=0; i<last_index; i++) {
        float total = jumlah[i] * harga_barang[i];
        fprintf(file,"| %dx %-15s | Rp.%-8d | Rp.%-8.0f | Rp.%-8.0f |\n", jumlah[i], nama_barang[i], harga_barang[i], total, diskon[i]);
    }
    fprintf(file,"=========================================================================\n");
    fprintf(file,"Total Harga : %d\n", total_harga);
    fprintf(file,"Total Diskon : %d\n", total_diskon);
    fprintf(file,"Tagihan : %d\n", total_bayar);
    fprintf(file,"=========================================================================\n");
    fprintf(file,"Pembayaran : %d\n", bayar);
    fprintf(file,"=========================================================================\n");
    fprintf(file,"Kembalian : %d\n", kembalian);
    fprintf(file,"=========================================================================\n");

    char *time_now = get_time_now();
    fprintf(file,"Waktu: %s", time_now);
    fprintf(file,"ID Struk: %s\n", id);
    fclose(file);

    printf("Struk anda telah dicetak pada file %s\n", filename);

    // Membuka file struk secara otomatis di Windows
    char command[100];
    sprintf(command, "notepad %s", filename);
    system(command);
}


int main(){

    cetak_pilihan();
    while (1){
        printf("Masukkan Pilihanmu : ");
        scanf("%d", &pilihan1);
        while (pilihan1 == 55){
            for(int i=0; i<5; i++){
                strcpy(nama_barang[i], "");
                jumlah[i] = 0;
                diskon[i] = 0;
                harga_barang[i] = 0;
            }
            last_index = 0;
            printf("Masukkan Pilihanmu : ");
            scanf("%d", &pilihan1);
        }
        if (pilihan1 == 99){
            if(last_index > 0) {
                printf("\n");
                cetak_garis(100);
                printf("\n| %-3s | %-15s | %-15s | %-15s | %-15s | %-15s |\n", "No.", "Jumlah", "Nama Barang", "Harga", "Total", "Diskon");
                for(int i=0; i<last_index-1; i++) {
                    for(int j=0; j<last_index-i-1; j++) {
                        int total_j = jumlah[sorted_index[j]] * harga_barang[sorted_index[j]];
                        int total_jp1 = jumlah[sorted_index[j+1]] * harga_barang[sorted_index[j+1]];

                        if(total_j < total_jp1) {
                            // Tukar posisi indeks
                            int temp = sorted_index[j];
                            sorted_index[j] = sorted_index[j+1];
                            sorted_index[j+1] = temp;
                        }
                    }
                }

                for(int i=0; i<last_index; i++) {
                    int index = sorted_index[i];
                    total_harga += jumlah[index] * harga_barang[index];
                    total_diskon += diskon[index];
                    float total = jumlah[index] * harga_barang[index];
                    printf("| %-3d | %-15d | %-15s | Rp.%-12d | Rp.%-12.0f | Rp.%-12.0f |\n", i+1, jumlah[index], nama_barang[index], harga_barang[index], total, diskon[index]);
                }
                cetak_garis(100);
                printf("\n");
                printf("Total Harga  = Rp. %d,-\n", total_harga);
                printf("Total Diskon = Rp. %d,-\n", total_diskon);
                total_bayar = total_harga - total_diskon;
                printf("Total Bayar  = Rp. %d,-\n", total_bayar);
                cetak_garis(100);
                printf("\n");
                printf("Masukkan uang bayar = ");
                scanf("%d", &bayar);
                while(bayar < total_bayar){
                    printf("Uang yang dimasukkan kurang!\n");
                    printf("Masukkan uang bayar = ");
                    scanf("%d", &bayar);
                }
                printf("Kembalian = %d\n", bayar - total_bayar);
                cetak_struk(total_harga, total_diskon, total_bayar, bayar, bayar-total_bayar);
                return 0;
            } else {
                printf("Anda belum memilih barang!\n\n");
            }
        }
        if (pilihan1 == 0 || pilihan1 == 00){
            return;
        }
        if(pilihan1 > 0 && pilihan1 <= 5){
            printf("Masukkan Jumlah Barang : ");
            scanf("%d", &pilihan2);
            printf("\n");

            int has = 0;
            for(int i=0; i<last_index; i++) {
                if(strcasecmp(barang[pilihan1 - 1], nama_barang[i]) == 0) {
                    jumlah[i] += pilihan2;
                    diskon[i] = cek_diskon(harga_barang[i], jumlah[i]);
                    has = 1;
                }
                break;
            }

            if(!has) {
                strcpy(nama_barang[last_index], barang[pilihan1 - 1]);
                jumlah[last_index] = pilihan2;
                harga_barang[last_index] = harga[pilihan1 - 1];
                diskon[last_index] = cek_diskon(harga[pilihan1-1], pilihan2);
                last_index += 1;
            }

            printf("Keranjang anda : \n");
            for(int i=0; i<last_index; i++) {
                printf("%s (%dx)\n", nama_barang[i], jumlah[i]);
            }
            printf("\n");
        } else {
            printf("Pilihan tidak valid! \n\n");
        }
    }
    return 0;
}
