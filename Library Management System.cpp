#include <iostream>
#include <vector>
#include <string>
#include <cassert>

using namespace std;

// Book Class - Represents a book in the library
class Book {
public:
    string title, author, bookId; // Book's title, author, and bookId
    bool isAvailable; // Availability of the book (true if available, false if borrowed)
    
    // Constructor to initialize a book with a title, author, and bookId, and set it as available
    Book(string t, string a, string i) : title(t), author(a), bookId(i), isAvailable(true) {}
};

// User Class - Represents a user of the library
class User {
public:
    string name; // User's name
    int id; // User's ID
    vector<string> borrowedBooks; // List of books borrowed by the user
    
    // Constructor to initialize a user with a name and ID
    User(string n, int i) : name(n), id(i) {}
    
    // Method for a user to borrow a book (adds the bookId of the borrowed book to the borrowedBooks list)
    void borrowBook(string bookId) {
        borrowedBooks.push_back(bookId);
    }
    
    // Method for a user to return a book (removes the bookId from the borrowedBooks list)
    void returnBook(string bookId) {
        for (auto it = borrowedBooks.begin(); it != borrowedBooks.end(); ++it) {
            if (*it == bookId) {
                borrowedBooks.erase(it); // Remove the book from borrowed list
                return;
            }
        }
    }
};

// Library Class - Represents the library that manages books and users
class Library {
private:
    vector<Book> books; // List of books in the library
    vector<User> users; // List of users in the library
public:
    // Method to add a new book to the library
    void addBook(string title, string author, string bookId) {
        books.push_back(Book(title, author, bookId));
    }
    
    // Method to remove a book from the library by its bookId
    void removeBook(string bookId) {
        for (auto it = books.begin(); it != books.end(); ++it) {
            if (it->bookId == bookId) {
                books.erase(it); // Remove the book from the list
                return;
            }
        }
    }
    
    // Method to search for a book by its title, author, or bookId (keyword can match any of these)
    void searchBook(string keyword) {
        for (const auto& book : books) {
            // Check if the keyword matches any part of the book's title, author, or bookId
            if (book.title.find(keyword) != string::npos || book.author.find(keyword) != string::npos || book.bookId == keyword) {
                cout << "Title: " << book.title << ", Author: " << book.author << ", bookId: " << book.bookId << "\n";
            }
        }
    }
    
    // Method to add a new user to the library
    void addUser(string name, int id) {
        users.push_back(User(name, id));
    }
    
    // Method for a user to borrow a book by its bookId
    void borrowBook(int userId, string bookId) {
        for (auto& book : books) {
            // Check if the book is available and matches the given bookId
            if (book.bookId == bookId && book.isAvailable) {
                for (auto& user : users) {
                    // Check if the user exists in the library
                    if (user.id == userId) {
                        user.borrowBook(bookId); // Add the book to the user's borrowed list
                        book.isAvailable = false; // Mark the book as unavailable
                        return;
                    }
                }
            }
        }
    }
    
    // Method for a user to return a borrowed book by its bookId
    void returnBook(int userId, string bookId) {
        for (auto& user : users) {
            // Check if the user exists in the library
            if (user.id == userId) {
                user.returnBook(bookId); // Remove the book from the user's borrowed list
                for (auto& book : books) {
                    // Mark the book as available when returned
                    if (book.bookId == bookId) {
                        book.isAvailable = true;
                        return;
                    }
                }
            }
        }
    }
    
    // Method to run test cases on the library functionality
    void runTests() {
        addBook("Test Book", "Test Author", "11111"); // Add a test book to the library
        assert(books.size() == 1); // Assert that the library has 1 book
        
        addUser("Test User", 101); // Add a test user
        assert(users.size() == 1); // Assert that the library has 1 user
        
        borrowBook(101, "11111"); // The user borrows the test book
        assert(!books[0].isAvailable); // Assert that the book is no longer available
        
        returnBook(101, "11111"); // The user returns the book
        assert(books[0].isAvailable); // Assert that the book is now available
        
        removeBook("11111"); // Remove the test book from the library
        assert(books.size() == 0); // Assert that the library has no books
        
        cout << "All tests passed successfully!\n"; // Output success message
    }
};

// Main function
int main() {
    Library lib; // Create a library object
    lib.runTests(); // Run the test cases
    return 0; // Return success
}
