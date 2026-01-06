#include "umkm.h"
#include <iomanip>
#include <map>



void inisialisasiToko(PengelolaUMKM &p) {
    p.firstProduk = NULL;
    p.firstTransaksi = NULL;
    p.kategori.first = NULL;
    p.autoID = 1;
}


void rebuildGraphKategori(PengelolaUMKM &p) {
    NodeKategori* k = p.kategori.first;
    while (k) {
        Edge* e = k->firstEdge;
        while (e) {
            Edge* delE = e;
            e = e->next;
            delete delE;
        }
        NodeKategori* delK = k;
        k = k->next;
        delete delK;
    }
    p.kategori.first = NULL;

    Produk* prod = p.firstProduk;
    while (prod) {
        hubungkanProdukKeKategori(p.kategori, prod);
        prod = prod->next;
    }
}

void tambahProduk(PengelolaUMKM &p) {
    Produk* baru = new Produk;
    baru->id = p.autoID++;
    baru->next = NULL;

    cin.ignore();
    cout << "Nama Produk : ";
    getline(cin, baru->nama);

    cout << "Kategori    : ";
    getline(cin, baru->kategori);

    string inputHarga;
    cout << "Harga       : ";
    getline(cin, inputHarga);


    for (int i = 0; i < inputHarga.length(); i++) {
        if (inputHarga[i] == '.')
            inputHarga.erase(i--, 1);
        }


    for (char c : inputHarga) {
        if (!isdigit(c)) {
            cout << "Harga harus berupa angka!\n";
            delete baru;
        return;
    }
}

baru->harga = stol(inputHarga);


    cout << "Stok        : ";
    cin >> baru->stok;
    if (cin.fail()) {
        cout << "Inputan harus angka!\n";
        cin.clear();
        cin.ignore(1000, '\n');
        delete baru;
        return;
    }

    if (!p.firstProduk)
        p.firstProduk = baru;
    else {
        Produk* t = p.firstProduk;
        while (t->next) t = t->next;
        t->next = baru;
    }

    rebuildGraphKategori(p);
    cout << "Produk berhasil ditambahkan!\n";
}


void tampilkanSemuaProduk(PengelolaUMKM p) {
    Produk* t = p.firstProduk;
    cout << "\n+----+----------------+-------------+-----------+------+\n";
    cout << "| ID | Nama Produk    | Kategori    | Harga     | Stok |\n";
    cout << "+----+----------------+-------------+-----------+------+\n";

    while (t) {
        cout << "| " << setw(2) << t->id
             << " | " << left << setw(14) << t->nama
             << " | " << setw(11) << t->kategori
             << " | " << right << setw(9) << t->harga
             << " | " << setw(4) << t->stok << " |\n";
        t = t->next;
    }
    cout << "+----+----------------+-------------+-----------+------+\n";
}

void editProduk(PengelolaUMKM &p) {
    int id;
    cout << "ID Produk: ";
    cin >> id;

    Produk* t = p.firstProduk;
    while (t && t->id != id) t = t->next;

    if (!t) {
        cout << "Produk tidak ditemukan!\n";
        return;
    }

    cin.ignore();
    cout << "Nama Baru     : ";
    getline(cin, t->nama);
    cout << "Kategori Baru : ";
    getline(cin, t->kategori);
    cout << "Harga Baru    : ";
    cin >> t->harga;
    cout << "Stok Baru     : ";
    cin >> t->stok;

    rebuildGraphKategori(p);
    cout << "Produk berhasil diedit!\n";
}

void hapusProduk(PengelolaUMKM &p) {
    int id;
    cout << "ID Produk: ";
    cin >> id;

    Produk *curr = p.firstProduk, *prev = NULL;
    while (curr && curr->id != id) {
        prev = curr;
        curr = curr->next;
    }

    if (!curr) {
        cout << "Produk tidak ditemukan!\n";
        return;
    }

    char konfirmasi;
    cout << "Yakin hapus produk \"" << curr->nama << "\"? (y/n): ";
    cin >> konfirmasi;

    if (konfirmasi != 'y' && konfirmasi != 'Y') {
        cout << "Penghapusan dibatalkan.\n";
        return;
    }
    if (!prev)
        p.firstProduk = curr->next;
    else
        prev->next = curr->next;

    delete curr;
    rebuildGraphKategori(p);
    cout << "Produk berhasil dihapus!\n";
}


/* ================= TRANSAKSI ================= */
void buatTransaksiBaru(PengelolaUMKM &p) {
    int id, qty;
    cout << "ID Produk: ";
    cin >> id;

    Produk* prod = p.firstProduk;
    while (prod && prod->id != id) prod = prod->next;

    if (!prod) {
        cout << "Produk tidak ditemukan!\n";
        return;
    }

    cout << "Jumlah beli: ";
    cin >> qty;

    if (prod->stok < qty) {
        cout << "Stok tidak cukup!\n";
        return;
    }

    prod->stok -= qty;

    Transaksi* t = new Transaksi;
    t->idTransaksi = (p.firstTransaksi == NULL) ? 1 : p.firstTransaksi->idTransaksi + 1;
    t->jumlah = qty;
    t->totalHarga = qty * prod->harga;
    t->tanggal = "Hari Ini";
    t->produk = prod;
    t->next = p.firstTransaksi;

    p.firstTransaksi = t;
    cout << "Transaksi berhasil!\n";
}

void tampilkanRiwayatTransaksi(PengelolaUMKM p) {
    Transaksi* t = p.firstTransaksi;
    cout << "\nRiwayat Transaksi:\n";
    while (t) {
        cout << "- " << t->produk->nama
             << " x" << t->jumlah
             << " = " << t->totalHarga << endl;
        t = t->next;
    }
}


void listStokMenipis(PengelolaUMKM p, int batas) {
    cout << "\nProduk stok <= " << batas << ":\n";
    for (Produk* t = p.firstProduk; t; t = t->next)
        if (t->stok <= batas)
            cout << "- " << t->nama << " (" << t->stok << ")\n";
}

void laporanPenjualanTabel(PengelolaUMKM p) {
    if (!p.firstTransaksi) {
        cout << "Belum ada transaksi.\n";
        return;
    }

    map<int,int> totalTerjual;
    map<int,long> totalOmzet;
    map<int,Produk*> data;

    long grand = 0;
    for (Transaksi* t = p.firstTransaksi; t; t = t->next) {
        int id = t->produk->id;
        totalTerjual[id] += t->jumlah;
        totalOmzet[id] += t->totalHarga;
        data[id] = t->produk;
        grand += t->totalHarga;
    }

    cout << "\n+----+----------------+-----------+---------------+---------------+\n";
    cout << "| ID | Nama Produk    | Harga     | Terjual (pcs) | Total Omset   |\n";
    cout << "+----+----------------+-----------+---------------+---------------+\n";

    for (auto &it : totalTerjual) {
        Produk* pdk = data[it.first];
        cout << "| " << setw(2) << it.first
             << " | " << left << setw(14) << pdk->nama
             << " | " << right << setw(9) << pdk->harga
             << " | " << setw(13) << it.second
             << " | " << setw(13) << totalOmzet[it.first] << " |\n";
    }

    cout << "+----+----------------+-----------+---------------+---------------+\n";
    cout << "TOTAL PENDAPATAN: Rp " << grand << endl;
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
    while (k && k->namaKategori != p->kategori)
        k = k->next;

    if (!k) {
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
    while (k) {
        cout << "\nKategori: " << k->namaKategori << endl;
        Edge* e = k->firstEdge;
        while (e) {
            cout << "- " << e->produk->nama << endl;
            e = e->next;
        }
        k = k->next;
    }
}

void searchProdukByKategori(GraphKategori G, string kategori) {
    NodeKategori* k = G.first;
    while (k && k->namaKategori != kategori)
        k = k->next;

    if (!k) {
        cout << "Kategori tidak ditemukan!\n";
        return;
    }

    cout << "\nProduk kategori " << kategori << ":\n";
    for (Edge* e = k->firstEdge; e; e = e->next)
        cout << "- " << e->produk->nama << endl;
}
