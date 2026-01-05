#include "umkm.h"

int main() {
    PengelolaUMKM toko;
    toko.namaToko = "UMKM Wong Nyeni";
    inisialisasiToko(toko);

    int pilih;
    do {
        cout << "\n=== " << toko.namaToko << " ===\n";
        cout << "1. Tambah Produk\n";
        cout << "2. Lihat Produk\n";
        cout << "3. Transaksi Baru\n";
        cout << "4. Riwayat Transaksi\n";
        cout << "5. Produk per Kategori\n";
        cout << "6. Edit Produk\n";
        cout << "7. Hapus Produk\n";
        cout << "8. List Stok Menipis\n";
        cout << "9. Search by Kategori\n";
        cout << "10. Laporan Penjualan dan Pendapatan\n";
        cout << "0. Keluar\n";
        cout << "Pilih: ";
        cin >> pilih;

        switch (pilih) {
        case 1: tambahProduk(toko); break;
        case 2: tampilkanSemuaProduk(toko); break;
        case 3: buatTransaksiBaru(toko); break;
        case 4: tampilkanRiwayatTransaksi(toko); break;
        case 5: tampilkanProdukPerKategori(toko.kategori); break;
        case 6: editProduk(toko); break;
        case 7: hapusProduk(toko); break;
        case 8: listStokMenipis(toko, 5); break;
        case 9: {
            string k;
            cin.ignore();
            cout << "Kategori: ";
            getline(cin, k);
            searchProdukByKategori(toko.kategori, k);
            break;
        }
        case 10: laporanPenjualanTabel(toko); break;
        case 0: cout << "Terima kasih!\n"; break;
        default: cout << "Pilihan salah!\n";
        }
    } while (pilih != 0);

    return 0;
}
