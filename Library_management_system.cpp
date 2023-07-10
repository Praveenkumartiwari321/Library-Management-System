#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct Book
{
    int id;
    string title;
    string author;
    bool available;
};

vector<Book> library;

// Function to add a new book to the library
void addBook()
{
    Book newBook;
    cout << "Enter book ID: ";
    cin >> newBook.id;
    cin.ignore();
    cout << "Enter book title: ";
    getline(cin, newBook.title);
    cout << "Enter book author: ";
    getline(cin, newBook.author);
    newBook.available = true;
    library.push_back(newBook);
    cout << "Book added successfully!" << endl;
}

// Function to search for a book by title
void searchBookByTitle()
{
    string searchTitle;
    cout << "Enter book title to search: ";
    cin.ignore();
    getline(cin, searchTitle);
    bool found = false;
    for (const auto &book : library)
    {
        if (book.title == searchTitle)
        {
            cout << "Book found!" << endl;
            cout << "ID: " << book.id << endl;
            cout << "Title: " << book.title << endl;
            cout << "Author: " << book.author << endl;
            cout << "Status: " << (book.available ? "Available" : "Issued") << endl;
            found = true;
            break;
        }
    }
    if (!found)
    {
        cout << "Book not found!" << endl;
    }
}

// Function to search for a book by ID
void searchBookById()
{
    int searchId;
    cout << "Enter book ID to search: ";
    cin >> searchId;
    bool found = false;
    for (const auto &book : library)
    {
        if (book.id == searchId)
        {
            cout << "Book found!" << endl;
            cout << "ID: " << book.id << endl;
            cout << "Title: " << book.title << endl;
            cout << "Author: " << book.author << endl;
            cout << "Status: " << (book.available ? "Available" : "Issued") << endl;
            found = true;
            break;
        }
    }
    if (!found)
    {
        cout << "Book not found!" << endl;
    }
}

// Function to issue a book
void issueBook()
{
    int issueId;
    cout << "Enter book ID to issue: ";
    cin >> issueId;
    bool found = false;
    for (auto &book : library)
    {
        if (book.id == issueId)
        {
            if (book.available)
            {
                book.available = false;
                cout << "Book issued successfully!" << endl;
            }
            else
            {
                cout << "Book is already issued!" << endl;
            }
            found = true;
            break;
        }
    }
    if (!found)
    {
        cout << "Book not found!" << endl;
    }
}

// Function to return a book
void returnBook()
{
    int returnId;
    cout << "Enter book ID to return: ";
    cin >> returnId;
    bool found = false;
    for (auto &book : library)
    {
        if (book.id == returnId)
        {
            if (!book.available)
            {
                book.available = true;
                cout << "Book returned successfully!" << endl;
            }
            else
            {
                cout << "Book is already available!" << endl;
            }
            found = true;
            break;
        }
    }
    if (!found)
    {
        cout << "Book not found!" << endl;
    }
}

// Function to list all books in the library
void listBooks()
{
    cout << "Library Books:" << endl;
    for (const auto &book : library)
    {
        cout << "ID: " << book.id << endl;
        cout << "Title: " << book.title << endl;
        cout << "Author: " << book.author << endl;
        cout << "Status: " << (book.available ? "Available" : "Issued") << endl;
        cout << "-------------------------" << endl;
    }
}

// Function to delete a book from the library
void deleteBook()
{
    int deleteId;
    cout << "Enter book ID to delete: ";
    cin >> deleteId;
    auto it = find_if(library.begin(), library.end(), [deleteId](const Book &book)
                      { return book.id == deleteId; });
    if (it != library.end())
    {
        library.erase(it);
        cout << "Book deleted successfully!" << endl;
    }
    else
    {
        cout << "Book not found!" << endl;
    }
}

// Function to save library data to a file
void saveDataToFile()
{
    ofstream file("library.txt");
    if (file.is_open())
    {
        for (const auto &book : library)
        {
            file << book.id << "," << book.title << "," << book.author << "," << book.available << endl;
        }
        file.close();
        cout << "Library data saved to file." << endl;
    }
    else
    {
        cout << "Error: Unable to open file." << endl;
    }
}

// Function to load library data from a file
void loadDataFromFile()
{
    ifstream file("library.txt");
    if (file.is_open())
    {
        library.clear();
        string line;
        while (getline(file, line))
        {
            Book book;
            size_t pos = line.find(",");
            book.id = stoi(line.substr(0, pos));
            line = line.substr(pos + 1);

            pos = line.find(",");
            book.title = line.substr(0, pos);
            line = line.substr(pos + 1);

            pos = line.find(",");
            book.author = line.substr(0, pos);
            line = line.substr(pos + 1);

            book.available = stoi(line);
            library.push_back(book);
        }
        file.close();
        cout << "Library data loaded from file." << endl;
    }
    else
    {
        cout << "Error: Unable to open file." << endl;
    }
}

int main()
{
    int choice;
    loadDataFromFile(); // Load library data from file

    do
    {
        cout << "=========================" << endl;
        cout << "Library Management System" << endl;
        cout << "=========================" << endl;
        cout << "1. Add a book" << endl;
        cout << "2. Search for a book by title" << endl;
        cout << "3. Search for a book by ID" << endl;
        cout << "4. Issue a book" << endl;
        cout << "5. Return a book" << endl;
        cout << "6. List all books" << endl;
        cout << "7. Delete a book" << endl;
        cout << "8. Save library data to file" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            addBook();
            break;
        case 2:
            searchBookByTitle();
            break;
        case 3:
            searchBookById();
            break;
        case 4:
            issueBook();
            break;
        case 5:
            returnBook();
            break;
        case 6:
            listBooks();
            break;
        case 7:
            deleteBook();
            break;
        case 8:
            saveDataToFile();
            break;
        case 0:
            saveDataToFile(); // Save library data to file before exiting
            cout << "Exiting the program." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    } while (choice != 0);

    return 0;
}
