#include "umkm.h"

int main() {
    PengelolaUMKM toko;
    toko.namaToko = "UMKM Maju Bersama";
    inisialisasiToko(toko);

    int pilihan;
    do {
        cout << "\n=== " << toko.namaToko << " ===\n";
        cout << "1. Tambah Produk\n";
        cout << "2. Lihat Produk\n";
        cout << "3. Transaksi Baru\n";
        cout << "4. Riwayat Transaksi\n";
        cout << "5. Produk per Kategori\n";
        cout << "0. Keluar\n";
        cout << "Pilih: ";
        cin >> pilihan;

        switch (pilihan) {
        case 1:
            tambahProduk(toko);
            break;
        case 2:
            tampilkanSemuaProduk(toko);
            break;
        case 3:
            buatTransaksiBaru(toko);
            break;
        case 4:
            tampilkanRiwayatTransaksi(toko);
            break;
        case 5:
            tampilkanProdukPerKategori(toko.kategori);
            break;
        case 0:
            cout << "Terima kasih!\n";
            break;
        default:
            cout << "Pilihan salah\n";
        }
    } while (pilihan != 0);

    return 0;
}
