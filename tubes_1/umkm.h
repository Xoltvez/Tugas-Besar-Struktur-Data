#ifndef UMKM_H
#define UMKM_H

#include <iostream>
#include <string>
using namespace std;

/* ================= SINGLE LINKED LIST ================= */
// Produk
struct Produk {
    int id;
    string nama;
    string kategori;
    long harga;
    int stok;
    Produk* next;
};

/* ================= MULTI LINKED LIST ================= */
// Transaksi
struct Transaksi {
    int idTransaksi;
    int jumlah;
    long totalHarga;
    string tanggal;

    Produk* produk;        // relasi ke produk
    Transaksi* next;
};

/* ================= GRAPH ================= */
// Graph Kategori
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
    int autoID;   // counter ID produk
};


/* ================= function ================= */
// Inisialisasi
void inisialisasiToko(PengelolaUMKM &p);

// Produk (Single Linked List)
void tambahProduk(PengelolaUMKM &p);
void tampilkanSemuaProduk(PengelolaUMKM p);

// Transaksi (Multi Linked List)
void buatTransaksiBaru(PengelolaUMKM &p);
void tampilkanRiwayatTransaksi(PengelolaUMKM p);

// Graph Kategori
void tambahKategori(GraphKategori &G, string nama);
void hubungkanProdukKeKategori(GraphKategori &G, Produk* p);
void tampilkanProdukPerKategori(GraphKategori G);

#endif
