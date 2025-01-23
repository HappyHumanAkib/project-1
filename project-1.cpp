#include <bits/stdc++.h>
using namespace std;
struct Book {
    int id;
    string title;
    string author;
    bool isAvailable;
};

struct User {
    int id;
    string name;
    int borrowedBookId;
};

class Library {
private:
    vector<Book> books;
    vector<User> users;

public:
    // Add a new book
    void addBook(int id, const string& title, const string& author) {
        books.push_back({id, title, author, true});
    }
    // Add a new user
    void addUser(int id, const string& name) {
        users.push_back({id, name, -1});
    }
    // Search for a book by title
    void searchBookByTitle(const string& title) {
        for (const auto& book : books) {
            if (book.title == title) {
                cout << "Book ID: " << book.id << ", Title: " << book.title
                          << ", Author: " << book.author << ", Available: "
                          << (book.isAvailable ? "Yes" : "No") << "\n";
                return;
            }
        }
        cout << "Book not found!\n";
    }
    // Borrow a book
    void borrowBook(int userId, int bookId) {
        auto userIt = find_if(users.begin(), users.end(), [&](const User& user) {
            return user.id == userId;
        });

        auto bookIt = find_if(books.begin(), books.end(), [&](const Book& book) {
            return book.id == bookId;
        });

        if (userIt == users.end()) {
            cout << "User not found!\n";
            return;
        }
        if (bookIt == books.end() || !bookIt->isAvailable) {
            cout << "Book not available!\n";
            return;
        }

        userIt->borrowedBookId = bookId;
        bookIt->isAvailable = false;

        cout << "Book borrowed successfully!\n";
    }
    // Return a book
    void returnBook(int userId) {
        auto userIt = find_if(users.begin(), users.end(), [&](const User& user) {
            return user.id == userId;
        });

        if (userIt == users.end() || userIt->borrowedBookId == -1) {
            cout << "No borrowed book found for this user!\n";
            return;
        }

        auto bookIt = find_if(books.begin(), books.end(), [&](const Book& book) {
            return book.id == userIt->borrowedBookId;
        });

        if (bookIt != books.end()) {
            bookIt->isAvailable = true;
        }

        userIt->borrowedBookId = -1;
        cout << "Book returned successfully!\n";
    }
    // Display all books
    void displayBooks() {
        cout << "\nAvailable Books:\n";
        for (const auto& book : books) {
            cout << "ID: " << book.id << ", Title: " << book.title
                      << ", Author: " << book.author << ", Available: "
                      << (book.isAvailable ? "Yes" : "No") << "\n";
        }
    }
};
int main() {
    Library library;

    // Adding some books
    library.addBook(1, "2023", "Akib Al Hassan");
    library.addBook(2, "HappyHuman", "Akib Al Hassan");

    // Adding some users
    library.addUser(1, "FARHAN");
    library.addUser(2, "Nisho");

    // Display books
    library.displayBooks();

    // Borrow a book
    library.borrowBook(1, 1);
    library.displayBooks();

    // Return a book
    library.returnBook(1);
    library.displayBooks();

    // Search for a book
    library.searchBookByTitle("2023");

    return 0;
}
