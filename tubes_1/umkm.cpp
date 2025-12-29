#include "umkm.h"
#include <cstdlib>

/* ================= INISIALISASI ================= */
void inisialisasiToko(PengelolaUMKM &p) {
    p.firstProduk = NULL;
    p.firstTransaksi = NULL;
    p.kategori.first = NULL;
    p.autoID = 1;   // mulai dari 1
}


/* ================= PRODUK ================= */
void tambahProduk(PengelolaUMKM &p) {
    Produk* baru = new Produk;
    baru->next = NULL;

    baru->id = p.autoID;
    p.autoID++;   

    baru->id = rand() % 900 + 100;
    cout << "Nama Produk : ";
    cin.ignore();
    getline(cin, baru->nama);
    cout << "Kategori    : ";
    getline(cin, baru->kategori);
    cout << "Harga       : ";
    cin >> baru->harga;
    cout << "Stok        : ";
    cin >> baru->stok;

    if (p.firstProduk == NULL)
        p.firstProduk = baru;
    else {
        Produk* temp = p.firstProduk;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = baru;
    }

    hubungkanProdukKeKategori(p.kategori, baru);
    cout << "Produk berhasil ditambahkan\n";
}

void tampilkanSemuaProduk(PengelolaUMKM p) {
    Produk* temp = p.firstProduk;
    cout << "\nID\tNama\tKategori\tHarga\tStok\n";
    while (temp != NULL) {
        cout << temp->id << "\t"
             << temp->nama << "\t"
             << temp->kategori << "\t"
             << temp->harga << "\t"
             << temp->stok << endl;
        temp = temp->next;
    }
}

/* ================= TRANSAKSI ================= */
void buatTransaksiBaru(PengelolaUMKM &p) {
    int id, qty;
    cout << "Masukkan ID Produk: ";
    cin >> id;

    Produk* prod = p.firstProduk;
    while (prod != NULL && prod->id != id)
        prod = prod->next;

    if (prod == NULL) {
        cout << "Produk tidak ditemukan\n";
        return;
    }

    cout << "Jumlah beli: ";
    cin >> qty;

    if (prod->stok < qty) {
        cout << "Stok tidak cukup\n";
        return;
    }

    prod->stok -= qty;

    Transaksi* t = new Transaksi;
    t->idTransaksi = rand() % 1000;
    t->jumlah = qty;
    t->totalHarga = qty * prod->harga;
    t->tanggal = "20-10-2023";
    t->produk = prod;
    t->next = p.firstTransaksi;

    p.firstTransaksi = t;

    cout << "Transaksi berhasil\n";
}

void tampilkanRiwayatTransaksi(PengelolaUMKM p) {
    Transaksi* t = p.firstTransaksi;
    cout << "\nID\tProduk\tJumlah\tTotal\n";
    while (t != NULL) {
        cout << t->idTransaksi << "\t"
             << t->produk->nama << "\t"
             << t->jumlah << "\t"
             << t->totalHarga << endl;
        t = t->next;
    }
}

/* ================= GRAPH ================= */
void tambahKategori(GraphKategori &G, string nama) {
    NodeKategori* n = new NodeKategori;
    n->namaKategori = nama;
    n->firstEdge = NULL;
    n->next = G.first;
    G.first = n;
}

void hubungkanProdukKeKategori(GraphKategori &G, Produk* p) {
    NodeKategori* k = G.first;
    while (k != NULL && k->namaKategori != p->kategori)
        k = k->next;

    if (k == NULL) {
        tambahKategori(G, p->kategori);
        k = G.first;
    }

    Edge* e = new Edge;
    e->produk = p;
    e->next = k->firstEdge;
    k->firstEdge = e;
}

void tampilkanProdukPerKategori(GraphKategori G) {
    NodeKategori* k = G.first;
    while (k != NULL) {
        cout << "\nKategori: " << k->namaKategori << endl;
        Edge* e = k->firstEdge;
        while (e != NULL) {
            cout << "- " << e->produk->nama << endl;
            e = e->next;
        }
        k = k->next;
    }
}
