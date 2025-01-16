#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Book {
    int bookID;
    string title;
    string author;
    int quantity;
};

void load_Books(Book books[], int &count);
void save_Books(Book books[], int count);
void add_New_Book(Book books[], int &count);
void search_Books(Book books[], int count);
void show_Books(Book books[], int count);

const int MAX_BOOKS = 100; 

int main() {
    Book books[MAX_BOOKS];
    int book_Count = 0;

    load_Books(books, book_Count);

    int option;
    do {
        cout << "\nLibrary System\n";
        cout << "---------------\n";
        cout << "1. Add Book\n";
        cout << "2. Search Book\n";
        cout << "3. Show All Books\n";
        cout << "4. Exit\n";
        cout << "Select an option: ";
        cin >> option;

        if (option == 1) {
            add_New_Book(books, book_Count);
        } else if (option == 2) {
            search_Books(books, book_Count);
        } else if (option == 3) {
            show_Books(books, book_Count);
        } else if (option == 4) {
            save_Books(books, book_Count);
            cout << "Goodbye! Data saved.\n";
        } else {
            cout << "Invalid option. Try again.\n";
        }
    } while (option != 4);

    return 0;
}

void load_Books(Book books[], int &count) {
    ifstream file("library.txt");
    count = 0;
    if (file.is_open()) {
        while (file >> books[count].bookID) {
            file.ignore();
            getline(file, books[count].title);
            getline(file, books[count].author);
            file >> books[count].quantity;
            file.ignore();
            count++;
        }
        file.close();
    } else {
        cout << "No existing data found. Starting fresh.\n";
    }
}

void save_Books(Book books[], int count) {
    ofstream file("library.txt");
    if (file.is_open()) {
        for (int i = 0; i < count; i++) {
            file << books[i].bookID << "\n";
            file << books[i].title << "\n";
            file << books[i].author << "\n";
            file << books[i].quantity << "\n";
        }
        file.close();
    } else {
        cout << "Error saving data.\n";
    }
}

void add_New_Book(Book books[], int &count) {
    if (count >= MAX_BOOKS) {
        cout << "Cannot add more books, inventory is full.\n";
        return;
    }
    cout << "Enter Book ID: ";
    cin >> books[count].bookID;
    cin.ignore();
    cout << "Enter Title: ";
    getline(cin, books[count].title);
    cout << "Enter Author: ";
    getline(cin, books[count].author);
    cout << "Enter Quantity: ";
    cin >> books[count].quantity;

    count++;
    cout << "Book added!\n";
}

void search_Books(Book books[], int count) {
    int choice;
    cout << "Search by:\n1. Book ID\n2. Title\nChoose: ";
    cin >> choice;

    if (choice == 1) {
        int id;
        cout << "Enter Book ID: ";
        cin >> id;
        for (int i = 0; i < count; i++) {
            if (books[i].bookID == id) {
                cout << "Book Found: " << books[i].title << " by " << books[i].author
                     << ", Quantity: " << books[i].quantity << "\n";
                return;
            }
        }
    } else if (choice == 2) {
        string title;
        cout << "Enter Title: ";
        cin.ignore();
        getline(cin, title);
        for (int i = 0; i < count; i++) {
            if (books[i].title.find(title) != string::npos) {
                cout << "Book Found: " << books[i].title << " by " << books[i].author
                     << ", Quantity: " << books[i].quantity << "\n";
                return;
            }
        }
    }
    cout << "Book not found.\n";
}

void show_Books(Book books[], int count) {
    if (count == 0) {
        cout << "No books available.\n";
        return;
    }
    for (int i = 0; i < count; i++) {
        cout << "ID: " << books[i].bookID << ", Title: " << books[i].title
             << ", Author: " << books[i].author << ", Quantity: " << books[i].quantity << "\n";
    }
}