#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Book {
    int id;
    string title;
    string author;
    bool available;

public:
    Book(int bookId, string bookTitle, string bookAuthor)
        : id(bookId), title(bookTitle), author(bookAuthor), available(true) {}

    int getId() const { return id; }
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    bool isAvailable() const { return available; }

    void setAvailability(bool status) { available = status; }

    void display() const {
        cout << "ID: " << id << ", Title: " << title
             << ", Author: " << author << ", Available: " << (available ? "Yes" : "No") << endl;
    }
};

class Member {
    int memberId;
    string name;

public:
    Member(int id, string memberName) : memberId(id), name(memberName) {}

    int getId() const { return memberId; }
    string getName() const { return name; }

    void display() const {
        cout << "Member ID: " << memberId << ", Name: " << name << endl;
    }
};

class Library {
    vector<Book> books;
    vector<Member> members;

public:
    void addBook(int bookId, string title, string author) {
        books.push_back(Book(bookId, title, author));
    }

    void addMember(int memberId, string name) {
        members.push_back(Member(memberId, name));
    }

    void borrowBook(int memberId, int bookId) {
        auto bookIt = find_if(books.begin(), books.end(), [&](Book &b) { return b.getId() == bookId; });
        if (bookIt == books.end() || !bookIt->isAvailable()) {
            cout << "Book not available.\n";
            return;
        }
        
        auto memberIt = find_if(members.begin(), members.end(), [&](Member &m) { return m.getId() == memberId; });
        if (memberIt == members.end()) {
            cout << "Member not found.\n";
            return;
        }
        
        bookIt->setAvailability(false);
        cout << memberIt->getName() << " borrowed the book: " << bookIt->getTitle() << endl;
    }

    void returnBook(int bookId) {
        auto bookIt = find_if(books.begin(), books.end(), [&](Book &b) { return b.getId() == bookId; });
        if (bookIt == books.end() || bookIt->isAvailable()) {
            cout << "Invalid return attempt.\n";
            return;
        }
        
        bookIt->setAvailability(true);
        cout << "Book " << bookIt->getTitle() << " has been returned.\n";
    }

    void displayBooks() const {
        cout << "Library Books:\n";
        for (const auto &book : books) {
            book.display();
        }
    }

    void displayMembers() const {
        cout << "Library Members:\n";
        for (const auto &member : members) {
            member.display();
        }
    }
};

int main() {
    Library library;
    library.addBook(1, "1984", "George Orwell");
    library.addBook(2, "To Kill a Mockingbird", "Harper Lee");

    library.addMember(100, "Alice");
    library.addMember(101, "Bob");

    library.displayBooks();
    library.displayMembers();

    library.borrowBook(100, 1);
    library.borrowBook(101, 2);

    library.displayBooks();
    library.returnBook(1);
    library.displayBooks();

    return 0;
}
