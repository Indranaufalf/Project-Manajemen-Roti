#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstring>
#include <string>
using namespace std;

struct account {
    string username;
    string password;
} kasir[50];

struct makan {
    string id;
    string nama;
    int stok;
    int harga;
} roti[100];

struct data {
    string nama_pembeli;
    string nama_roti;
    int jumlah;
    int total;
} transaksi[100];

int jumlahroti = 0, banyakakunkasir = 0, jumlahtransaksi = 0;

void tambahroti(){
    int banyakroti;
    cout<<"Banyak roti yang ingin ditambah : "; cin>>banyakroti;
    if (jumlahroti < 0){
        jumlahroti = 0;
    }
    for(int i = jumlahroti ; i<banyakroti+jumlahroti;i++){
        cout<<"Roti "<<i+1<<endl;
        cout<<"ID Roti\t: "; cin>>roti[i].id;
        cin.ignore();
        cout<<"Nama Roti\t: "; getline(cin,roti[i].nama);
        cout<<"Stok Roti\t: "; cin>>roti[i].stok;
        cout<<"Harga Roti\t: "; cin>>roti[i].harga;
        cout<<endl;
    }
    jumlahroti = jumlahroti + banyakroti;
    ofstream recoveryroti("dataroti.txt");
    if (!recoveryroti.is_open()){
        cout<<"Data gagal disimpan.\n";
        return;
    }
    for (int i = 0; i<jumlahroti; i++){
        recoveryroti<<roti[i].id<<","<<roti[i].nama<<","<<roti[i].stok<<","<<roti[i].harga<<"\n";
    }
    recoveryroti.close();
    ofstream recoveryjumlah("datajumlah.txt");
    if (!recoveryjumlah.is_open()){
        cout<<"Data gagal disimpan.\n";
        return;
    }
    recoveryjumlah<<jumlahroti<<","<<banyakakunkasir<<","<<jumlahtransaksi<<"\n";
    recoveryjumlah.close();
    cout<<"[DATA TERSIMPAN]\n";
    system("pause");
}

void lihatroti(){
    int pilih;
    cout << "\033c";
    if (jumlahroti == 0) {
        cout << "Belum ada produk roti." << endl;
        return;
    }
    string garis = "======================================================";
    cout << garis << endl;
    cout << left;
    cout << "| " << setfill(' ') << setw(3) << "No" << " | " << setw(8) << "ID Roti" << " | " << setw(12) << "Roti" << " | " << setw(6) << "Stok" << " | " << setw(8) << "Harga" << " |" << endl;
    cout << garis << endl;
    for (int i = 0; i < jumlahroti; i++){
        cout << "| " << setw(3) << i+1 << " | " << setw(8) << roti[i].id << " | " << setw(12) << roti[i].nama << " | " << setw(6) << roti[i].stok << " | " << setw(8) << roti[i].harga << " |" << endl; 
    }
    cout<<garis<<endl<<endl;
    system("pause");
}

void lihatdaftarroti(){
    cout << setfill('=') << setw(35) << "=" << endl;
    cout << "|" << setfill(' ') << setw(24) << "DAFTAR ROTI" << setw(11) << "|\n";
    cout << setfill('=') << setw(35) << "=" << endl<<endl;
    if (jumlahroti == 0) {
        cout << "Belum ada produk roti." << endl;
        return;
    }
    lihatroti();
}

void editroti(){
    string edit;
    int posisi;
    char editulang;
    bool ketemu = false;
    do {
        cout<<"[EDIT ROTI]\n";
        if (roti[0].id.empty() || jumlahroti < 1) {
            cout<<"Data Roti masih kosong.\nSilahkan input roti terlebih dahulu.\n";
            system("pause");
            return;
        }
        cout<<"Daftar Roti :\n\n";
        for(int i = 0 ; i<jumlahroti;i++){
            cout<<"Roti "<<i+1<<endl;
            cout<<"ID\t: "<<roti[i].id<<endl;
            cout<<"Nama\t: "<<roti[i].nama<<endl;
            cout<<"Stok\t: "<<roti[i].stok<<endl;
            cout<<"Harga\t: "<<roti[i].harga<<endl;
            cout<<endl;
        }
    
        cout<<"Masukkan ID Roti : "; cin>>edit;
        for (int i = 0; i<jumlahroti; i++){
            if (roti[i].id == edit){
                posisi = i;
                ketemu = true;
                break;
            }
        }
        if (ketemu){
            cout<<"ID\t: "<<roti[posisi].id<<endl;
            cout<<"Nama\t: "<<roti[posisi].nama<<endl;
            cout<<"Stok\t: "<<roti[posisi].stok<<endl;
            cout<<"Harga\t:"<<roti[posisi].harga<<endl;
            cout<<"Masukkan data update \n";
            cout<<"ID\t: "; cin>>roti[posisi].id;
            cin.ignore();
            cout<<"Nama\t: "; getline(cin,roti[posisi].nama);
            cout<<"Stok\t: "; cin>>roti[posisi].stok;
            cout<<"Harga\t: "; cin>>roti[posisi].harga;
            ofstream recoveryroti("dataroti.txt");
            if (!recoveryroti.is_open()){
                cout<<"Data gagal disimpan.\n";
                return;
            }
            for (int i = 0; i<jumlahroti; i++){
                recoveryroti<<roti[i].id<<","<<roti[i].nama<<","<<roti[i].stok<<","<<roti[i].harga<<"\n";
            }
            recoveryroti.close();
            cout<<"[DATA TERSIMPAN]\n\n";
            editulang = 'n';
        } else {
            cout<<"Mohon maaf, data yang Anda cari tidak ditemukan.\n";
            cout<<"Apakah Anda ingin mencari ulang data lain? (y/n) : "; cin>>editulang;
        }
    } while (editulang == 'y' || editulang == 'Y');

}

void hapusroti(){
    string hapus;
    int posisi;
    bool ketemu = false;
    char yakin, hapusulang;
    do {
        cout<<"[HAPUS ROTI]\n";
        if (roti[0].id.empty() || jumlahroti < 1) {
            cout<<"Data Roti masih kosong.\nSilahkan input roti terlebih dahulu.\n";
            system("pause");
            return;
        }
        cout<<"Daftar Roti :\n\n";
        for(int i = 0 ; i<jumlahroti;i++){
            cout<<"Roti "<<i+1<<endl;
            cout<<"ID\t: "<<roti[i].id<<endl;
            cout<<"Nama\t: "<<roti[i].nama<<endl;
            cout<<"Stok\t: "<<roti[i].stok<<endl;
            cout<<"Harga\t: "<<roti[i].harga<<endl;
            cout<<endl;
        }
    
        cout<<"Masukkan ID Roti : "; cin>>hapus;
        for (int i = 0; i<jumlahroti; i++){
            if (roti[i].id == hapus){
                posisi = i;
                ketemu = true;
                break;
            }
        }
        if (ketemu){
            cout<<"ID\t: "<<roti[posisi].id<<endl;
            cout<<"Nama\t: "<<roti[posisi].nama<<endl;
            cout<<"Stok\t: "<<roti[posisi].stok<<endl;
            cout<<"Harga\t:"<<roti[posisi].harga<<endl;
            cout<<"Anda yakin untuk menghapus data ini? (y/n) : "; cin>>yakin;
            if (yakin == 'y' || yakin == 'Y'){
                if (posisi == jumlahroti-1){
                    jumlahroti = jumlahroti-1;
                } else {
                    for (int i = posisi; i < jumlahroti-1;i++){
                        swap (roti[i].id, roti[i+1].id);
                        swap (roti[i].nama, roti[i+1].nama);
                        swap (roti[i].stok, roti[i+1].stok);
                        swap (roti[i].harga, roti[i+1].harga);
                    }
                    jumlahroti = jumlahroti-1;
                }
            } else {
                return;
            }
            ofstream recoveryroti("dataroti.txt");
            if (!recoveryroti.is_open()){
                cout<<"Data gagal disimpan.\n";
                return;
            }
            for (int i = 0; i<jumlahroti; i++){
                recoveryroti<<roti[i].id<<","<<roti[i].nama<<","<<roti[i].stok<<","<<roti[i].harga<<"\n";
            }
            recoveryroti.close();
            ofstream recoveryjumlah("datajumlah.txt");
            if (!recoveryjumlah.is_open()){
                cout<<"Data gagal disimpan.\n";
                return;
            }
            recoveryjumlah<<jumlahroti<<","<<banyakakunkasir<<","<<jumlahtransaksi<<"\n";
            recoveryjumlah.close();
            cout<<"[DATA TERSIMPAN]\n\n";
            hapusulang = 'n';
        } else {
            cout<<"Mohon maaf, data yang Anda cari tidak ditemukan.\n";
            cout<<"Apakah Anda ingin mencari ulang data lain? (y/n) : "; cin>>hapusulang;
        }
    } while(hapusulang == 'y' || hapusulang == 'Y');
}

void kelolaprodukroti(){
    int menu;
    do {
        cout<<" -- KELOLA PRODUK ROTI --\n";
        cout<<"1. Tambah Roti\n";
        cout<<"2. Lihat Daftar Roti\n";
        cout<<"3. Edit Roti\n";
        cout<<"4. Hapus Roti\n";
        cout<<"5. Kembali\n";
        cout<<"0. Exit\n";
        cout<<"Pilih : "; cin>>menu;
        switch (menu){
            case 1:
            system("cls");
            tambahroti();
            break;
            
            case 2:
            system("cls");
            lihatdaftarroti();
            break;
            
            case 3:
            system("cls");
            editroti();
            break;
            
            case 4:
            system("cls");
            hapusroti();
            break;
            
            case 5:
            system("cls");
            return;
            break;
    
            case 0:
            exit(0);
            break;
    
            default:
            cout<<"Pilihan menu tidak valid.\nSilahkan masukkan ulang pilihan!\n";
            break;
        }
    } while (!(menu == 5 || menu == 0));
}

void tambahakunkasir(){
    string konfirmasi;
    char buatulang, akunbaru;
    if (banyakakunkasir < 0){
        banyakakunkasir = 0;
    }
    cout<<"[TAMBAH AKUN KASIR]\n";
    cout<<"Masukkan username baru (tanpa spasi) : "; cin>>kasir[banyakakunkasir].username;
    do {
        cout<<"Masukkan password baru : "; cin>>kasir[banyakakunkasir].password;
        cout<<"Konfirmasi password : "; cin>>konfirmasi;
        cout<<"\n";
        if (kasir[banyakakunkasir].password == konfirmasi){
            banyakakunkasir++;
            ofstream recoveryakun("dataakunkasir.txt");
            if (!recoveryakun.is_open()){
                cout<<"Akun gagal dibuat.\n";
                return;
            }
            for (int i = 0; i<banyakakunkasir; i++){
                recoveryakun<<kasir[i].username<<","<<kasir[i].password<<"\n";
            }
            recoveryakun.close();
            ofstream recoveryjumlah("datajumlah.txt");
            if (!recoveryjumlah.is_open()){
                cout<<"Data gagal disimpan.\n";
                return;
            }
            recoveryjumlah<<jumlahroti<<","<<banyakakunkasir<<","<<jumlahtransaksi<<"\n";
            recoveryjumlah.close();
            cout<<"[AKUN BERHASIL DIBUAT]\n";
            buatulang = 'n';
            system("pause");
        } else {
            cout<<"Konfirmasi password tidak sesuai.\n";
            cout<<"Ingin mengubah/input ulang password baru? (y/n) : "; cin>>buatulang;
        }
    } while (buatulang == 'y' || buatulang == 'Y');
}

void lihatdaftarakunkasir(){
    cout<<"[DAFTAR AKUN KASIR]\n";
    if (kasir[0].username.empty() || banyakakunkasir < 1){
        cout<<"Belum ada akun kasir yang dibuat.\nSilahkan buat akun kasir terlebih dahulu.\n";
    } else {
        cout << "No\tUsername\t\tPassword" << endl;
        cout << "====================================================" << endl;
        for (int i = 0; i < banyakakunkasir; i++) {
            cout << (i+1) << "\t" << kasir[i].username << "\t\t\t" << kasir[i].password << endl;
        }
    }
    cout<<endl;
    system("pause");
}

void hapusakunkasir(){
    string hapus;
    int posisi;
    bool ketemu = false;
    char yakin, hapusulang;
    do {
        cout<<"[HAPUS AKUN]\n\n";
        if (kasir[0].username.empty() || banyakakunkasir < 1){
            cout<<"Belum ada akun kasir yang dibuat.\nSilahkan buat akun kasir terlebih dahulu.\n";
            system("pause");
            return;
        }
        cout<<"Daftar akun kasir :\n";
        for(int i = 0; i < banyakakunkasir; i++){
            cout<<"Akun ke-"<<i+1<<endl;
            cout<<"Username : "<<kasir[i].username<<endl;
            cout<<"Password : "<<kasir[i].password<<endl<<endl;
        }
        cout<<"Username akun yang akan dihapus : "; cin>>hapus;
        for (int i = 0; i<banyakakunkasir; i++){
            if (kasir[i].username == hapus){
                posisi = i;
                ketemu = true;
                break;
            }
        }
        if (ketemu){
            cout<<"Username : "<<kasir[posisi].username<<endl;
            cout<<"Password : "<<kasir[posisi].password<<endl;
            cout<<"Anda yakin untuk menghapus akun ini? (y/n) : "; cin>>yakin;
            if (yakin == 'y' || yakin == 'Y'){
                if (posisi == banyakakunkasir-1){
                    banyakakunkasir = banyakakunkasir-1;
                } else {
                    for (int i = posisi; i <banyakakunkasir-1;i++){
                        swap (kasir[i].username, kasir[i+1].username);
                        swap (kasir[i].password, kasir[i+1].password);
                    }
                    banyakakunkasir = banyakakunkasir-1;
                }
            } else {
                return;
            }
            ofstream recoveryakun("dataakunkasir.txt");
            if (!recoveryakun.is_open()){
                cout<<"Akun gagal dihapus.\n";
                return;
            }
            for (int i = 0; i<banyakakunkasir; i++){
                recoveryakun<<kasir[i].username<<","<<kasir[i].password<<"\n";
            }
            recoveryakun.close();
            ofstream recoveryjumlah("datajumlah.txt");
            if (!recoveryjumlah.is_open()){
                cout<<"Data gagal disimpan.\n";
                return;
            }
            recoveryjumlah<<jumlahroti<<","<<banyakakunkasir<<","<<jumlahtransaksi<<"\n";
            recoveryjumlah.close();
            cout<<"[DATA TERSIMPAN]\n\n";
            hapusulang = 'n';
            system("pause");
        } else {
            cout<<"Mohon maaf, data yang Anda cari tidak ditemukan.\n";
            cout<<"Apakah Anda ingin mencari ulang data lain? (y/n) : "; cin>>hapusulang;
        }
    } while (hapusulang == 'y' || hapusulang == 'Y');
}

void kelolaakunkasir(){
    int menu;
    do {
        cout<<" -- KELOLA AKUN KASIR --\n";
        cout<<"1. Tambah Akun Kasir\n";
        cout<<"2. Lihat Daftar Akun Kasir\n";
        cout<<"3. Hapus Akun Kasir\n";
        cout<<"4. Kembali\n";
        cout<<"0. Exit\n";
        cout<<"Pilih : "; cin>>menu;
        switch (menu){
            case 1:
            system("cls");
            tambahakunkasir();
            break;
            
            case 2:
            system("cls");
            lihatdaftarakunkasir();
            break;
            
            case 3:
            system("cls");
            hapusakunkasir();
            break;
            
            case 4:
            system("cls");
            return;
            break;
    
            case 0:
            exit(0);
            break;
    
            default:
            break;
        }
    } while (!(menu == 0 || menu == 4));
}

void lihattransaksi(){
    cout<<"[LIHAT TRANSAKSI]\n";
    if (transaksi[0].nama_pembeli.empty() || jumlahtransaksi < 1){
        cout<<"Belum ada riwayat transaksi.\n";
        system("pause");
        return;
    }
    string garis = "================================================================";
    cout << garis << endl;
    cout << left;
    cout << "| " << setfill(' ')  << setw(3) << "No" << " | " << setw(15) << "Nama Pembeli" << " | " << setw(12) << "Roti" << " | " << setw(6) << "Jumlah" << " | " << setw(12) << "Total Harga" << " |" << endl;
    cout << garis << endl;
    for(int i = 0; i<jumlahtransaksi; i++){
        cout << "| " << setfill(' ')  << setw(3) << i+1 << " | " << setw(15) << transaksi[i].nama_pembeli << " | " << setw(12) << transaksi[i].nama_roti << " | " << setw(6) << transaksi[i].jumlah << " | " << setw(12) << transaksi[i].total << " |" << endl;
    }
    cout<<garis<<endl<<endl;
    system("pause");
}

void sortingharga(){
    cout<<"[SORTING TOTAL HARGA]\n\n";
    for (int i = 0; i < jumlahtransaksi-1; i++){
        for (int j = 0; j < jumlahtransaksi-i-1; j++){
            if (transaksi[j].total < transaksi[j+1].total){
                swap (transaksi[j].nama_pembeli, transaksi[j+1].nama_pembeli);
                swap (transaksi[j].nama_roti, transaksi[j+1].nama_roti);
                swap (transaksi[j].jumlah, transaksi[j+1].jumlah);
                swap (transaksi[j].total, transaksi[j+1].total);
            }
        }
    }
    string garis = "================================================================";
    cout << garis << endl;
    cout << left;
    cout << "| " << setfill(' ')  << setw(3) << "No" << " | " << setw(15) << "Nama Pembeli" << " | " << setw(12) << "Roti" << " | " << setw(6) << "Jumlah" << " | " << setw(12) << "Total Harga" << " |" << endl;
    cout << garis << endl;
    for(int i = 0; i<jumlahtransaksi; i++){
        cout << "| " << setfill(' ')  << setw(3) << i+1 << " | " << setw(15) << transaksi[i].nama_pembeli << " | " << setw(12) << transaksi[i].nama_roti << " | " << setw(6) << transaksi[i].jumlah << " | " << setw(12) << transaksi[i].total << " |" << endl;
    }
    cout<<garis<<endl<<endl;
    system("pause");
}

void sortingpembeli(){
    cout<<"[SORTING PEMBELI]\n\n";
    for (int i = 0; i < jumlahtransaksi-1; i++){
        for (int j = 0; j < jumlahtransaksi-i-1; j++){
            if (transaksi[j].nama_pembeli > transaksi[j+1].nama_pembeli){
                swap (transaksi[j].nama_pembeli, transaksi[j+1].nama_pembeli);
                swap (transaksi[j].nama_roti, transaksi[j+1].nama_roti);
                swap (transaksi[j].jumlah, transaksi[j+1].jumlah);
                swap (transaksi[j].total, transaksi[j+1].total);
            }
        }
    }
    string garis = "================================================================";
    cout << garis << endl;
    cout << left;
    cout << "| " << setfill(' ')  << setw(3) << "No" << " | " << setw(15) << "Nama Pembeli" << " | " << setw(12) << "Roti" << " | " << setw(6) << "Jumlah" << " | " << setw(12) << "Total Harga" << " |" << endl;
    cout << garis << endl;
    for(int i = 0; i<jumlahtransaksi; i++){
        cout << "| " << setfill(' ')  << setw(3) << i+1 << " | " << setw(15) << transaksi[i].nama_pembeli << " | " << setw(12) << transaksi[i].nama_roti << " | " << setw(6) << transaksi[i].jumlah << " | " << setw(12) << transaksi[i].total << " |" << endl;
    }
    cout<<garis<<endl<<endl;
    system("pause");
}

void sortingtransaksi(){
    int menu;
    do {
        cout<<"[SORTING TRANSAKSI]\n";
        cout<<"1. Sorting berdasarkan total harga (Desc)\n";
        cout<<"2. Sorting berdasarkan nama pembeli (Asc)\n";
        cout<<"Pilih : "; cin>>menu;
        switch(menu){
            case 1:
            system("cls");
            sortingharga();
            break;
            
            case 2:
            system("cls");
            sortingpembeli();
            break;
    
            default:
            cout<<"Input tidak valid!\n";
            break;
        }
    } while (!(menu == 1 || menu == 2));
}

void lihatpenjualan(){
    int menu;
    do {
        cout<<" -- LIHAT PENJUALAN --\n";
        cout<<"1. Lihat Transaksi Penjualan\n";
        cout<<"2. Sorting Transaksi\n";
        cout<<"3. Kembali\n";
        cout<<"0. Exit\n";
        cout<<"Pilih : "; cin>>menu;
        switch(menu){
            case 1:
            system("cls");
            lihattransaksi();
            break;
            
            case 2:
            system("cls");
            sortingtransaksi();
            break;
            
            case 3:
            system("cls");
            return;
            break;
    
            case 0:
            exit(0);
            break;
    
            default:
            cout<<"Pilihan tidak valid.\nSilahkan masukkan ulang pilihan!\n";
            break;
        }
    } while (!(menu == 3 || menu == 0));
}

void menuadmin(){
    int menu;
    do {
        cout<<" -- MAIN MENU -- \n";
        cout<<"1. Kelola Produk Roti\n";
        cout<<"2. Kelola Akun Kasir\n";
        cout<<"3. Lihat Penjualan\n";
        cout<<"4. Logout\n";
        cout<<"0. Exit\n";
        cout<<"Pilih : "; cin>>menu;
        switch (menu){
            case 1:
            system("cls");
            kelolaprodukroti();
            break;
            
            case 2:
            system("cls");
            kelolaakunkasir();
            break;
            
            case 3:
            system("cls");
            lihatpenjualan();
            break;
            
            case 4:
            system("cls");
            return;
            break;
    
            case 0:
            exit(0);
            break;
            
            default:
            cout<<"Pilihan tidak valid.\nSilahkan masukkan ulang pilihan!\n";
            break;
        }
    } while (!(menu == 4 || menu == 0));
}

void beliRoti(){
    string mauroti;
    int beli;
    cout << "\033c";
    cout << setfill('=') << setw(35) << "=" << endl;
    cout << "|" << setfill(' ') << setw(24) << "Beli Roti" << setw(11) << "|\n";
    cout << setfill('=') << setw(35) << "=" << endl;
    if (jumlahroti == 0) {
        cout << "Tidak ada produk tersedia!" << endl;
        return;
    }
    lihatroti();
    cout << "Nama Pembeli: ";
    cin.ignore();
    getline(cin, transaksi[jumlahtransaksi].nama_pembeli);

    cout << "Pilih Roti: "; cin >> mauroti;
    bool found = false;
    for (int i = 0; i < jumlahroti; i++) {
        if (roti[i].id == mauroti) {
            transaksi[jumlahtransaksi].nama_roti = mauroti;
            cout << "Roti dipilih: " << roti[i].nama << endl;
            cout << "Harga: Rp " << roti[i].harga << endl;
            cout << "Stok tersedia: " << roti[i].stok << endl;
            cout << "Jumlah beli: "; cin >> beli;
            if (beli > roti[i].stok) {
                cout << "Stok tidak cukup!" << endl;
                return;}
            transaksi[jumlahtransaksi].jumlah = beli;
            transaksi[jumlahtransaksi].total = beli*roti[i].harga;
            roti[i].stok -= beli;
            jumlahtransaksi++;
            found = true;
            break;
        }
    }
    if (!found){
        cout<<"Roti yang Anda cari tidak tersedia!\n";
    } else {
        ofstream recoveryroti("dataroti.txt");
        if (!recoveryroti.is_open()){
            cout<<"Data gagal disimpan.\n";
            return;
        }
        for (int i = 0; i<jumlahroti; i++){
            recoveryroti<<roti[i].id<<","<<roti[i].nama<<","<<roti[i].stok<<","<<roti[i].harga<<"\n";
        }
        recoveryroti.close();
        ofstream recoverytransaksi("datatransaksi.txt");
        if (!recoverytransaksi.is_open()){
            cout<<"Data gagal disimpan.\n";
            return;
        }
        for (int i = 0; i<jumlahtransaksi; i++){
            recoverytransaksi<<transaksi[i].nama_pembeli<<","<<transaksi[i].nama_roti<<","<<transaksi[i].jumlah<<","<<transaksi[i].total<<"\n";
        }
        recoverytransaksi.close();
        ofstream recoveryjumlah("datajumlah.txt");
        if (!recoveryjumlah.is_open()){
            cout<<"Data gagal disimpan.\n";
            return;
        }
        recoveryjumlah<<jumlahroti<<","<<banyakakunkasir<<","<<jumlahtransaksi<<"\n";
        recoveryjumlah.close();
        cout<<"[TRANSAKSI SUKSES]\n";
        system("pause");
    }
}

int cariRotiByNama(string *nama) {
    for (int i = 0; i < jumlahroti; i++) {
        if (roti[i].nama == *nama){
            return i;
        }
    }
    return -1;
}

void cariRoti(){
    int pilih;
    cout << "\033c";
    cout << setfill('=') << setw(35) << "=" << endl;
    cout << "|" << setfill(' ') << setw(24) << "Cari Roti" << setw(11) << "|\n";
    cout << setfill('=') << setw(35) << "=" << endl;
    string nama;
    cout << "Masukkan nama roti: ";
    cin.ignore();
    getline(cin, nama);
    
    int index = cariRotiByNama(&nama);
    if (index != -1) {
        cout << "\nProduk ditemukan:" << endl;
        cout << "ID: " << roti[index].id << endl;
        cout << "Nama: " << roti[index].nama << endl;
        cout << "Stok: " << roti[index].stok << endl;
        cout << "Harga: Rp " << roti[index].harga << endl;
    } else {
        cout << "Produk tidak ditemukan!" << endl;
    }
    system("pause");
}

void menuKasir(){
    int pilih;
    do{
        cout << "\033c";
        cout << right;
        cout << setfill('=') << setw(35) << "=" << endl;
        cout << "|" << setfill(' ') << setw(19) << "Beranda" << setw(16) << "|\n";
        cout << setfill('=') << setw(35) << "=" << endl;
        cout << "1. Beli Roti \n";
        cout << "2. Cari Roti \n";
        cout << "3. Lihat Semua Roti \n"; 
        cout << "4. Logout\n"; 
        cout << "0. Keluar\n";
        cout << "Pilih menu : "; cin >> pilih;
        
        switch(pilih){
            case 1:
            system("cls");
            beliRoti();
            system("pause");
            break;
            
            case 2:
            system("cls");
            cariRoti();
            system("pause");
            break;
            
            case 3:
            system("cls");
            lihatdaftarroti();
            system("pause");
            break;
            
            case 4:
            system("cls");
            return;
            break;
            
            case 0:
            exit(0);
            break;
            
            default:
            cout << "Pilihan tidak valid!\n";
            system("pause");
            break;
        }
    } while (!(pilih == 4 || pilih == 0));
}

int main(){
    string username, password;
    int k = 0, l = 0, m = 0;
    char ulang, pulih;
    bool terdaftar = false;
    system("cls");
    cout<<"Apakah Anda ingin memulihkan data sebelumnya ? (y/n) : "; cin>>pulih;
    if (pulih == 'y' || pulih == 'Y'){
        string baris;
        ifstream dataroti ("dataroti.txt");
        if (!dataroti.is_open()){
            cout<<"Data gagal dipulihkan.\n";
            return -1;
        }
        while (getline(dataroti, baris)){
            stringstream ss(baris);
            string temp1;
            getline(ss, roti[k].id, ',');
            getline(ss, roti[k].nama, ',');
            getline(ss, temp1, ','); roti[k].stok = stoi(temp1);
            getline(ss, temp1, ','); roti[k].harga = stoi(temp1);
            k++;
        }
        dataroti.close();
        string baris1;
        ifstream dataakun ("dataakunkasir.txt");
        if (!dataakun.is_open()){
            cout<<"Data gagal dipulihkan.\n";
            return -1;
        }
        while (getline(dataakun, baris1)){
            stringstream ss(baris1);
            getline(ss, kasir[l].username, ',');
            getline(ss, kasir[l].password, ',');
            l++;
        }
        dataakun.close();
        string baris2;
        ifstream datatransaksi ("datatransaksi.txt");
        if (!datatransaksi.is_open()){
            cout<<"Data gagal dipulihkan.\n";
            return -1;
        }
        while (getline(datatransaksi, baris2)){
            stringstream ss(baris2);
            string temp2;
            getline(ss, transaksi[m].nama_pembeli, ',');
            getline(ss, transaksi[m].nama_roti, ',');
            getline(ss, temp2, ','); transaksi[m].jumlah = stoi(temp2);
            getline(ss, temp2, ','); transaksi[m].total = stoi(temp2);
            m++;
        }
        datatransaksi.close();
        string baris3;
        ifstream datajumlah ("datajumlah.txt");
        if (!datajumlah.is_open()){
            cout<<"Data gagal dipulihkan.\n";
            return -1;
        }
        while (getline(datajumlah, baris3)){
            stringstream ss(baris3);
            string temp3;
            getline(ss, temp3, ','); jumlahroti = stoi(temp3);
            getline(ss, temp3, ','); banyakakunkasir = stoi(temp3);
            getline(ss, temp3, ','); jumlahtransaksi = stoi(temp3);
        }
        datajumlah.close();
    }
    system("cls");
    do {
        cout<<"Silahkan login terlebih dahulu!\n";
        cout<<"Username\t: "; cin>>username;
        cout<<"Password\t: "; cin>>password;
        for (int i = 0; i<banyakakunkasir; i++){
            if (kasir[i].username == username && kasir[i].password == password){
                terdaftar = true;
                break;
            }
        }
        if (username == "admin" && password == "admin123"){
            system("cls");
            menuadmin();
            ulang = 'y';
        } else if (terdaftar){
            system("cls");
            menuKasir();
            ulang = 'y';
        } else {
            cout<<"Gagal Login.\n Username atau password yang Anda masukkan salah!\n";
            cout<<"Login ulang? (y/n) : "; cin>>ulang;
        }
    } while (ulang == 'y' || ulang == 'Y');
    return 0;
}