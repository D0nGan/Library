#include <iostream>//Hello GitHub
#include <fstream>
#include <windows.h>      
#include <conio.h>      
#include <Vector>    
#include <string>    

using namespace std;

class Book {
private:
    string name, author, year;
public:
    void add(string n, string a, string y) {
        name = n;
        author = a;
        year = y;
    }
    string GetName() { return name; }
    string GetAuthor() { return author; }
    string GetYear() { return year; }
}books[10];
int quantity = 0;
vector <string> Vbooks;

void ReadLibrary() {
    system("cls");
    cout << "Загрузка...";
    ifstream file("Books.txt");
    if (!file) {
        ofstream newfile("Books.txt");
        newfile.close();
    }
    else if (file.peek() == EOF) quantity = 0;
    else
    {
        string name, author, year;
        for (quantity = 0; !file.eof(); quantity++) {
            getline(file, name, ',');
            getline(file, author, ',');
            getline(file, year);
            books[quantity].add(name, author, year);
        }
    }
    system("cls");
    file.close();
}
void WriteLibrary() {
    ofstream file("Books.txt");
    for (int i = 0; i < quantity; i++) {
        if (i == 0) file << books[i].GetName() << ',' << books[i].GetAuthor() << ',' << books[i].GetYear();
        else file << "\n" << books[i].GetName() << ',' << books[i].GetAuthor() << ',' << books[i].GetYear();
    }
    file.close();
}
void VectorBook(vector <string>* Vbooks);

void AllBook();

void AddBook();
void AB(int x);

void DelBook();
void DB(int d);

void RnmBook();

int choice(vector <string> menu, string heading) {
    bool e = true;
    int m = 0;
    do {
        system("cls");
        cout << heading << endl;
        int n = menu.size();
        for (int i = 0; i < n; i++) {
            if (i == m) cout << "\x1B[31m" << menu[i] << "\x1B[37m" << endl;
            else cout << menu[i] << endl;
        }
        switch (_getch()) {
        case(72): m--; break;
        case(80): m++; break;
        case(13): e = false; break;
        }
        if (m > n - 1) m = 0;
        if (m < 0) m = n - 1;
    } while (e);
    return m;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    ReadLibrary();
    vector <string> menu = { "Добавить книгу", "Удалить книгу", "Переименовать книгу", "Проcмотреть список книг", "Выйти" };
    do {
        switch (choice(menu, "Меню: \n")) {
        case(0): AddBook(); break;
        case(1): DelBook(); break;
        case(2): RnmBook(); break;
        case(3): AllBook(); break;
        case(4): exit(1); break;
        }
    } while (true);
}

void VectorBook(vector <string>* Vbooks) {
    if (quantity == 0) { system("cls"); cout << "В библиотеке нет книг!"; system("pause"); main(); }
    else {
        cout << "Список доступных книг:\n";
        for (int i = 0; i < quantity; i++) {
            Vbooks->push_back(books[i].GetName() + "; " + books[i].GetAuthor() + "; " + books[i].GetYear());
        }
    }
}

void AllBook() {
    VectorBook(&Vbooks);
    for (int i = 0; i < Vbooks.size(); i++) {
        cout << i + 1 << ". " << Vbooks[i] << endl;
    }
    system("pause");
}

void AddBook() {
    string name, author, year;
    system("cls");
    if (quantity > 9) cout << "Слишком большое кол-во книг в библиотеке!";
    else {
        AB(quantity);
        cout << "\nКнига успешно добавлена!" << endl;
        quantity++;
        WriteLibrary();
        system("pause");
    }
}
void AB(int x) {
    system("cls");
    string n, a, y;
    cout << "Введите название книги: ";
    getline(cin, n);
    cout << "Введите автора книги: ";
    getline(cin, a);
    cout << "Введите год книги: ";
    getline(cin, y);
    books[x].add(n, a, y);
}

void DelBook() {
    system("cls");
    VectorBook(&Vbooks);
    int d = choice(Vbooks, "Какую книгу вы хотите удалить ? \n\n");
    system("cls");
    string text = "Вы действительно хотите удалить эту книгу?\n";
    text += books[d].GetName() + "; " + books[d].GetAuthor() + "; " + books[d].GetYear() + "\n";
    vector <string> YN = { "Да", "Нет" };
    switch (choice(YN, text)) {
    case(1): main();
    case(0): {
        DB(d);
        cout << "Книга успешно удалена!";
        system("pause");
    } break;
    }
}
void DB(int d) {
    if (quantity == 1) quantity--;
    else {
        for (int i = d; i < quantity - 1; i++) {
            books[i] = books[i + 1];
        }
        quantity--;
    }
    WriteLibrary();
}

void RnmBook() {
    system("cls");
    VectorBook(&Vbooks);
    int d = choice(Vbooks, "Какую книгу вы хотите Переименовать?\n");
    system("cls");
    string text = "Вы уверены, что хотите Переименовать эту книгу?\n";
    text += books[d].GetName() + "; " + books[d].GetAuthor() + "; " + books[d].GetYear() + "\n";
    vector <string> YN = { "Да", "Нет" };
    switch (choice(YN, text)) {
    case(1): main();
    case(0): {
        AB(d);
        cout << "Книга успешно переименована!";
        WriteLibrary();
        system("pause");
    } break;
    }
}