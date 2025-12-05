#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct User {
    string name;
    string email;
    string password;
};

struct Product {
    string name;
    int price;
    bool available;
};

struct Rental {
    string user;
    string product;
    int days;
    int total;
};

vector<User> users;
vector<Product> products;
vector<Rental> rentals;

int findUser(string email, string password) {
    for (int i = 0; i < users.size(); i++) {
        if (users[i].email == email && users[i].password == password)
            return i;
    }
    return -1;
}

void registerUser() {
    User u;
    cout << "\n=== REGISTER USER ===\n";
    cout << "Nama: ";
    cin >> u.name;
    cout << "Email: ";
    cin >> u.email;
    cout << "Password: ";
    cin >> u.password;

    users.push_back(u);
    cout << "Akun berhasil dibuat!\n";
}

int login() {
    string email, password;
    cout << "\n=== LOGIN ===\n";
    cout << "Email: ";
    cin >> email;
    cout << "Password: ";
    cin >> password;

    int index = findUser(email, password);

    if (index != -1) {
        cout << "Login berhasil!\n";
        return index;
    } else {
        cout << "Email atau password salah!\n";
        return -1;
    }
}

void listProducts() {
    cout << "\n=== DAFTAR PRODUK ===\n";
    for (int i = 0; i < products.size(); i++) {
        cout << i+1 << ". " << products[i].name 
             << " | Rp " << products[i].price 
             << " /hari | Status: " 
             << (products[i].available ? "Tersedia" : "Disewa") 
             << endl;
    }
}

void rentProduct(string username) {
    listProducts();
    int pilihan, hari;

    cout << "\nPilih produk (nomor): ";
    cin >> pilihan;
    pilihan--;

    if (pilihan < 0 || pilihan >= products.size()) {
        cout << "Pilihan tidak valid!\n";
        return;
    }

    if (!products[pilihan].available) {
        cout << "Produk sedang disewa orang lain!\n";
        return;
    }

    cout << "Berapa hari sewa? ";
    cin >> hari;

    int total = hari * products[pilihan].price;

    rentals.push_back({username, products[pilihan].name, hari, total});
    products[pilihan].available = false;

    cout << "\nSewa berhasil!\nTotal bayar: Rp " << total << endl;
}

void viewRentalHistory(string username) {
    cout << "\n=== RIWAYAT SEWA ===\n";

    for (auto &r : rentals) {
        if (r.user == username) {
            cout << "Produk: " << r.product 
                 << " | Hari: " << r.days 
                 << " | Total: Rp " << r.total << endl;
        }
    }
}

int main() {
    // Data produk default
    products.push_back({"iPhone 14", 70000, true});
    products.push_back({"MacBook Air M1", 120000, true});
    products.push_back({"iPad Pro", 90000, true});

    while (true) {
        cout << "\n=== MENU UTAMA ===\n";
        cout << "1. Register\n2. Login\n3. Keluar\nPilih: ";

        int menu;
        cin >> menu;

        if (menu == 1) {
            registerUser();
        } 
        else if (menu == 2) {
            int userIndex = login();
            if (userIndex != -1) {
                int pilih2;
                do {
                    cout << "\n=== MENU PENGGUNA ===\n";
                    cout << "1. Lihat Produk\n";
                    cout << "2. Sewa Produk\n";
                    cout << "3. Riwayat Sewa\n";
                    cout << "4. Logout\n";
                    cout << "Pilih: ";
                    cin >> pilih2;

                    if (pilih2 == 1) listProducts();
                    else if (pilih2 == 2) rentProduct(users[userIndex].name);
                    else if (pilih2 == 3) viewRentalHistory(users[userIndex].name);

                } while (pilih2 != 4);
            }
        }
        else if (menu == 3) {
            cout << "Keluar dari aplikasi.\n";
            break;
        }
        else {
            cout << "Pilihan tidak valid!\n";
        }
    }

    return 0;
}
