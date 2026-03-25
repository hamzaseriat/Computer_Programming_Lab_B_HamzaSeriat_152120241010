#include <iostream>
#include <string>

using namespace std;

struct Page {
    string Url;
    string title;
    int AccessTime[3]; // "AccesTime" olan yazımı düzelttim
    Page* next;
    Page* prev;
};

Page* head = nullptr;
Page* current = nullptr;

void goforward() {
    if (current != nullptr && current->next != nullptr) {
        current = current->next;
        cout << "Ileri gidildi, su anki sayfa: " << current->title << endl;
    } else {
        cout << "Ileride sayfa yok" << endl;
    }
}

void goback() {
    if (current != nullptr && current->prev != nullptr) {
        current = current->prev;
        cout << "Geri gidildi, su anki sayfa: " << current->title << endl;
    } else {
        cout << "Geride sayfa yok" << endl;
    }
}

void deletethepage() {
    if (current == nullptr) {
        cout << "Silinecek sayfa yok" << endl;
        return;
    }

    Page* silincek = current;

    if (silincek->prev != nullptr) {
        silincek->prev->next = silincek->next;
    } else {
        head = silincek->next;
    }

    if (silincek->next != nullptr) {
        silincek->next->prev = silincek->prev;
        current = silincek->next;
    } else {
        current = silincek->prev;
    }

    delete silincek;
    cout << "Mevcut sayfa silindi.\n";
}

void toshowlist() {
    if (head == nullptr) {
        cout << "Gecmis bos." << endl;
        return;
    }
    Page* temp = head;
    cout << "\n--- Tarama Gecmisi ---" << endl;
    while (temp != nullptr) {
        if (temp == current) cout << "-> ";
        cout << "[" << temp->AccessTime[0] << ":" << temp->AccessTime[1] << ":" << temp->AccessTime[2] << "] "
             << temp->title << " (" << temp->Url << ")" << endl;
        temp = temp->next;
    }
}

void ziyaret(string u, string t, int h, int m, int s) {
    Page* newPage = new Page;
    newPage->Url = u;
    newPage->title = t;
    newPage->AccessTime[0] = h;
    newPage->AccessTime[1] = m;
    newPage->AccessTime[2] = s;
    newPage->next = nullptr;
    newPage->prev = nullptr;

    if (head == nullptr) {
        head = newPage;
        current = newPage;
    } else {

        Page* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newPage;
        newPage->prev = temp;
        current = newPage;
    }
    cout << "Ziyaret edildi: " << t << endl;
}

int main() {
    int secim;
    string url, baslik;
    int h, m, s;

    do {
        cout << "\n--- Tarayici Menusu ---" << endl;
        cout << "1. Yeni Sayfa Ziyaret Et" << endl;
        cout << "2. Geri Git" << endl;
        cout << "3. Ileri Git" << endl;
        cout << "4. Mevcut Sayfayi Sil" << endl;
        cout << "5. Gecmisi Listele" << endl;
        cout << "0. Cikis" << endl;
        cout << "Seciminiz: ";
        cin >> secim;

        switch (secim) {
            case 1:
            cout << "URL girin: "; cin >> url;
            cout << "Baslik girin: ";
            cin.ignore(); // Önceki cin'den kalan '\n' karakterini temizler
            getline(cin, baslik);
            cout << "Saat (SS DD SN): "; cin >> h >> m >> s;
            ziyaret(url, baslik, h, m, s);
            break;
        case 2:
            goback();
            break;
        case 3:
            goforward();
            break;
        case 4:
            deletethepage();
            break;
        case 5:
            toshowlist();
            break;
        case 0:
            cout << "Cikis yapiliyor..." << endl;
            break;
        default:
            cout << "Gecersiz secim!" << endl;
    }
} while (secim != 0);
}

