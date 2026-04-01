#include <iostream>
#include <string>

using namespace std;



struct MoneyBundle {
    string serialNumber;
    string currencyType;
    int billCounts[3];
    MoneyBundle* next;
};

struct Customer {
    string customerName;
    string transactionType;
};


class MoneyStack {
private:
    MoneyBundle* top;

public:
    MoneyStack() { top = nullptr; }


    void push(string sn, string type, int b100, int b50, int b20) {
        MoneyBundle* newNode = new MoneyBundle();
        newNode->serialNumber = sn;
        newNode->currencyType = type;
        newNode->billCounts[0] = b100;
        newNode->billCounts[1] = b50;
        newNode->billCounts[2] = b20;

        newNode->next = top;
        top = newNode;
        cout << "Para Paketi Eklendi: " << sn << endl;
    }


    MoneyBundle* pop() {
        if (top == nullptr) return nullptr;
        MoneyBundle* temp = top;
        top = top->next;
        return temp;
    }

    void display() {
        cout << "\n--- KASADAKİ PARA YIĞINI ---" << endl;
        MoneyBundle* temp = top;
        if (!temp) cout << "Kasa bos!" << endl;
        while (temp) {
            cout << "[" << temp->serialNumber << " | " << temp->currencyType
                 << " | 100'luk:" << temp->billCounts[0] << " 50'lik:" << temp->billCounts[1]
                 << " 20'lik:" << temp->billCounts[2] << "]" << endl;
            temp = temp->next;
        }
    }
};


class CustomerQueue {
private:
    Customer queue[5];
    int front, rear, size;
    int capacity = 5;

public:
    CustomerQueue() {
        front = 0;
        rear = -1;
        size = 0;
    }

    void enqueue(string name, string type) {
        if (size == capacity) {
            cout << "Kuyruk dolu! Musteri alinamaz." << endl;
            return;
        }
        rear = (rear + 1) % capacity;
        queue[rear].customerName = name;
        queue[rear].transactionType = type;
        size++;
        cout << "Musteri Siraya Girdi: " << name << endl;
    }


    Customer dequeue() {
        if (size == 0) return {"", ""};
        Customer temp = queue[front];
        front = (front + 1) % capacity;
        size--;
        return temp;
    }

    bool isEmpty() { return size == 0; }

    void display() {
        cout << "\n--- BEKLEYEN MUSTERILER (KUYRUK) ---" << endl;
        if (size == 0) cout << "Kuyruk bos!" << endl;
        for (int i = 0; i < size; i++) {
            int index = (front + i) % capacity;
            cout << i + 1 << ". " << queue[index].customerName
                 << " (" << queue[index].transactionType << ")" << endl;
        }
    }
};



void islemIsle(MoneyStack& stack, CustomerQueue& queue) {
    if (queue.isEmpty()) {
        cout << "\nIslem yapilacak musteri yok!" << endl;
        return;
    }

    MoneyBundle* bundle = stack.pop();
    if (bundle == nullptr) {
        cout << "\nKasada para paketi yok! Islem yapilamiyor." << endl;
        return;
    }

    Customer cust = queue.dequeue();
    cout << "\n>>> ISLEM GERCEKLESTI <<<" << endl;
    cout << "Musteri: " << cust.customerName << " servisi tamamlandi." << endl;
    cout << "Kullanilan Paket: " << bundle->serialNumber << endl;

    delete bundle;
}

int main() {
    MoneyStack kasa;
    CustomerQueue bankaSirasi;


    kasa.push("SN001", "TL", 10, 5, 2);
    kasa.push("SN002", "USD", 5, 0, 10);

    bankaSirasi.enqueue("Ahmet Yilmaz", "Yatirma");
    bankaSirasi.enqueue("Ayse Demir", "Cek");


    kasa.display();
    bankaSirasi.display();


    islemIsle(kasa, bankaSirasi);


    kasa.display();
    bankaSirasi.display();

    return 0;
}
