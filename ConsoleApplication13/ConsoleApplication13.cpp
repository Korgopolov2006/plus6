
#include <iostream>
#include <string>
#include <Windows.h>
#include <iomanip>
#include <vector>

using namespace std;

class Book {
private:
    string title;
    string author;
    string genre;
    string description;
    bool reserved;

public:
    Book(string t, string a, string g, string d) : title(t), author(a), genre(g), description(d), reserved(false) {}

    string getTitle() {
        return title;
    }

    string getAuthor() {
        return author;
    }

    string getGenre() {
        return genre;
    }

    string getDescription() {
        return description;
    }

    bool isReserved() {
        return reserved;
    }

    void reserve() {
        reserved = true;
    }

    void cancelReservation() {
        reserved = false;
    }
};

class LibraryCatalog {
private:
    vector<Book> books;

public:
    void searchBooks(string criteria) {
        for (Book book : books) {
            if (book.getTitle() == criteria || book.getAuthor() == criteria || book.getGenre() == criteria || book.getDescription() == criteria) {
                displayBookInfo(book);
            }
        }
    }

    void addBook(Book newBook) {
        books.push_back(newBook);
    }

    void displayBookInfo(Book book) {
        cout << "Название: " << book.getTitle() << endl;
        cout << "Автор: " << book.getAuthor() << endl;
        cout << "Жанр: " << book.getGenre() << endl;
        cout << "Описание: " << book.getDescription() << endl;
        if (book.isReserved()) {
            cout << "Зарезервировано: Да" << endl;
        }
        else {
            cout << "Зарезервировано: нет" << endl;
        }
    }

    void reserveBook(string title) {
        for (Book& book : books) {
            if (book.getTitle() == title && !book.isReserved()) {
                book.reserve();
                cout << "Книга \"" << title << "\" успешно зарезервирована." << endl;
                return;
            }
        }
        cout << "Книга не найдена или уже зарезервирована." << endl;
    }

    void showReservedBooks() {
        for (Book book : books) {
            if (book.isReserved()) {
                displayBookInfo(book);
            }
        }
    }

    void cancelReservation(string title) {
        for (Book& book : books) {
            if (book.getTitle() == title && book.isReserved()) {
                book.cancelReservation();
                cout << "Резерв на книгу \"" << title << "\" успешно отменен." << endl;
                return;
            }
        }
        cout << "Книга не найдена или не зарезервирована." << endl;
    }
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");
    LibraryCatalog catalog;


    Book book1("Война и мир", "Лев Толстой", "Роман", "Одно из величайших произведений русской литературы");
    Book book2("Преступление и наказание", "Фёдор Достоевский", "Роман", "Психологический роман о преступлении и наказании");
    Book book3("Мастер и Маргарита", "Михаил Булгаков", "Роман", "Одно из самых известных произведений русской литературы");

    catalog.addBook(book1);
    catalog.addBook(book2);
    catalog.addBook(book3);

    int choice = 0;
    while (choice != 7) {
        cout << "Выберите действие:" << endl;
        cout << "1. Поиск книги" << endl;
        cout << "2. Добавить книгу" << endl;
        cout << "3. Просмотр информации о книге" << endl;
        cout << "4. Зарезервировать книгу" << endl;
        cout << "5. Просмотр зарезервированных книг" << endl;
        cout << "6. Отменить резервацию книги" << endl;
        cout << "7. Выход из программы" << endl;

        cin >> choice;

        string title , author, genre, criteria;
        Book newBook("", "", "", "");

        switch (choice) {
        case 1:
            cout << "Введите критерий для поиска книги (название, автор, жанр, описание): ";
            cin.ignore();
            getline(cin, criteria);
            catalog.searchBooks(criteria);
            break;
        case 2:
            cout << "Введите название книги: ";
            cin >> title;
            cout << "Введите автора: ";
            cin >> author;
            cout << "Введите жанр: ";
            cin >> genre;
            cout << "Введите описание: ";
            cin >> criteria;
            cin.ignore();
            getline(cin, criteria);
            newBook = Book(title, criteria, criteria, criteria);
            catalog.addBook(newBook);
            break;
       /* case 3:
            cout << "Введите название книги: ";
            cin.ignore();
            getline(cin, title);
            for (Book book : catalog.getBooks()) {
                if (book.getTitle() == title) {
                    catalog.displayBookInfo(book);
                    break;
                }
            }
            break;*/
        case 4:
            cout << "Введите название книги для резервации: ";
            cin.ignore();
            getline(cin, title);
            catalog.reserveBook(title);
            break;
        case 5:
            catalog.showReservedBooks();
            break;
        case 6:
            cout << "Введите название книги для отмены резервации: ";
            cin.ignore();
            getline(cin, title);
            catalog.cancelReservation(title);
            break;
        case 7:
            cout << "Программа завершена." << endl;
            break;
        default:
            cout << "Неверный выбор. Повторите ввод." << endl;
        }
    }

    return 0;
}