#ifndef UMKM_H
#define UMKM_H

#include <iostream>
#include <string>
using namespace std;

/* ================= SINGLE LINKED LIST ================= */
struct Produk {
    int id;
    string nama;
    string kategori;
    long harga;
    int stok;
    Produk* next;
};

/* ================= MULTI LINKED LIST ================= */
struct Transaksi {
    int idTransaksi;
    int jumlah;
    long totalHarga;
    string tanggal;
    Produk* produk;
    Transaksi* next;
};

/* ================= GRAPH ================= */
struct Edge {
    Produk* produk;
    Edge* next;
};

struct NodeKategori {
    string namaKategori;
    Edge* firstEdge;
    NodeKategori* next;
};

struct GraphKategori {
    NodeKategori* first;
};


struct PengelolaUMKM {
    string namaToko;
    Produk* firstProduk;
    Transaksi* firstTransaksi;
    GraphKategori kategori;
    int autoID;
};

/* ================= FUNGSI ================= */
void inisialisasiToko(PengelolaUMKM &p);

/* Produk */
void tambahProduk(PengelolaUMKM &p);
void tampilkanSemuaProduk(PengelolaUMKM p);
void editProduk(PengelolaUMKM &p);
void hapusProduk(PengelolaUMKM &p);

/* Transaksi */
void buatTransaksiBaru(PengelolaUMKM &p);
void tampilkanRiwayatTransaksi(PengelolaUMKM p);

/* Laporan */
void listStokMenipis(PengelolaUMKM p, int batas);
void laporanPenjualanTabel(PengelolaUMKM p);

/* Graph */
void tambahKategori(GraphKategori &G, string nama);
void hubungkanProdukKeKategori(GraphKategori &G, Produk* p);
void tampilkanProdukPerKategori(GraphKategori G);
void searchProdukByKategori(GraphKategori G, string kategori);
void rebuildGraphKategori(PengelolaUMKM &p);

#endif
