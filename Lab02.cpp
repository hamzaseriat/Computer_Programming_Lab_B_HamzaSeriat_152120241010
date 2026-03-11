#include <iostream>
#include <string>
using namespace std;

struct Node{
    string SongTitle;
    Node* next;
};

void addSong(Node*& head ,string SongTitle ){
    Node* newNode = new Node;
    newNode->SongTitle = SongTitle;
    newNode->next = head;
    head = newNode;
}

void searchSong(Node* head, string SongTitle) {
    Node* temp = head;

    while (temp != NULL) {
        if (temp->SongTitle == SongTitle) {
            cout << "Song found: " << SongTitle << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Song not found\n";
}

void Listsongs(Node* head){
    if(head == NULL){
        cout << "Playlist is empty..\n";
        return;
    }

    Node* temp = head;
    int k = 1;

    while(temp != NULL){
        cout << k << ". " << temp->SongTitle << endl;
        temp = temp->next;
        k++;
    }
}

int main(){
    cout << "Welcome to Music Playlist\n";

    Node* head = NULL;
    int choice;
    string title;

    while(true){
        cout << "\nWhat would you like to do?\n";
        cout << "1. Add\n2. Search\n3. List\n4. Exit\n";

        cin >> choice;
        cin.ignore();

        if(choice == 1){
            cout << "Enter the Song Title:\n";
            getline(cin , title);
            addSong(head,title);
        }

        else if(choice == 2){
            cout << "Enter the Song Search:\n";
            getline(cin,title);
            searchSong(head,title);
        }

        else if(choice == 3){
            Listsongs(head);
        }

        else if(choice == 4){
            break;
        }

        else{
            cout << "Invalid choice..\n";
        }
    }

    return 0;
}
