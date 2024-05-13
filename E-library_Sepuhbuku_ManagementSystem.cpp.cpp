#include <iostream>
#include <list>
#include <map>
#include <set>
#include <iomanip>
#include <string>
#include <queue>
#include <stack>

using namespace std;

struct Book
{
    string title;
    string author;
    int year;
    bool available;
    string borrower;

    // Default constructor
    Book() : title(""), author(""), year(0), available(false), borrower("") {}

    //Parameterized contructor
    Book(const string &t, const string &a, int y, bool av) : title(t), author(a), year(y), available(av), borrower("") {}
};

// Node untuk Binary Search Tree (BST)
struct TreeNode
{
    string key;
    TreeNode *left;
    TreeNode *right;

    TreeNode(const string &k) : key(k), left(nullptr), right(nullptr) {}
};

// Binary Search Tree (BST) untuk pencarian judul buku
class BST
{
private:
    TreeNode *root;

    // Fungsi rekursif untuk memasukkan kata ke dalam BST
    TreeNode *insert(TreeNode *node, const string &key)
    {
        if (node == nullptr)
            return new TreeNode(key);

        if (key < node->key)
            node->left = insert(node->left, key);
        else if (key > node->key)
            node->right = insert(node->right, key);

        return node;
    }

    // Fungsi rekursif untuk mencari kata dalam BST
    bool search(TreeNode *node, const string &key)
    {
        if (node == nullptr)
            return false;

        if (key == node->key)
            return true;
        else if (key < node->key)
            return search(node->left, key);
        else
            return search(node->right, key);
    }

public:
    BST() : root(nullptr) {}

    void insert(const string &key)
    {
        root = insert(root, key);
    }

    bool search(const string &key)
    {
        return search(root, key);
    }
};

int main()
{
    list<Book> books;
    map<int, string> bookIdToTitle;
    set<string> members;
    queue<Book> queueBook;
    stack<Book> basketStack;
    BST titleSearchTree;
    int bookId = 0;

    // Daftar Buku
    books.push_back(Book("The Great Gatsby", "F. Scott Fitzgerald", 1925, true));
    books.push_back(Book("The Hunger Games", "Suzanne Collins", 2008, true));
    books.push_back(Book("1984", "George Orwell", 1949, true));
    books.push_back(Book("Python Crash Course", "Eric Matthes", 2015, true));
    books.push_back(Book("Learning Python", "Mark Lutz", 2013, true));
    books.push_back(Book("Algorithms (4th Edition)", "Robert,Kevin", 2011, true));
    books.push_back(Book("A Game of Thrones", "George R.R. Martin", 1996, true));
    books.push_back(Book("Laskar Pelangi", "Andrea Hirata", 2005, true));
    books.push_back(Book("Bumi Manusia", "Pramoedya Ananta Toer", 1980, true));
    books.push_back(Book("Dunia Sophie", "Jostein Gaarder", 1991, true));
    books.push_back(Book("Pulang", "Tere Liye", 2016, true));
    books.push_back(Book("Filosofi Teras", "Henry Manampiring", 2015, true));
    books.push_back(Book("Ketika Cinta Bertasbih", "El Shirazy", 2004, true));
    books.push_back(Book("Manusia Setengah Salmon", "Raditya Dika", 2011, true));
    books.push_back(Book("Java Programming", "Rinaldi Munir", 2016, true));
    books.push_back(Book("PHP & MySQL untuk Pemula", "Yudi Yanri", 2017, true));
    books.push_back(Book("Belajar Pemrograman Arduino", "Donny Maulana", 2018, true));
    books.push_back(Book("Node.js: Konsep dan Aplikasi", "Ferdy Gale", 2018, true));
    books.push_back(Book("Belajar Bahasa C++", "Budi Raharjo", 2019, true));

    // Daftar Anggota
    members.insert("Rifqi Makarim");
    members.insert("Ralegusta Rasyid");
    members.insert("Rasyid Firmansyah");
    members.insert("Rafi Enhan");
    members.insert("Ravelin Lutfhan");
    members.insert("Rayhan Bagus");
    members.insert("Raka Aleandra");
    members.insert("Robby Septian");
    members.insert("Tito Rizqy");
    // jika tidak terdaftar Anggota sebelumnya,maka harus menambahkan anggota baru

    // Memetakan ID buku ke judul buku
    for (auto it = books.begin(); it != books.end(); ++it)
    {
        bookIdToTitle[bookId++] = it->title;

        // Memasukkan judul buku ke dalam BST
        titleSearchTree.insert(it->title);
    }

    cout << "==========================================================================================" << endl;
    cout << "\t\t\tE-LIBRARY SEPUHBUKU - MANAGEMENT SYSTEM" << endl;
    cout << "------------------------------------------------------------------------------------------" << endl;

Main_menu:

    cout << "Menu Utama : " << endl;
    cout << "1. Tambah buku baru ke dalam perpustakaan" << endl;
    cout << "2. Tambah anggota baru ke dalam perpustakaan" << endl;
    cout << "3. Proses peminjaman buku" << endl;
    cout << "4. Pengembalian buku" << endl;
    cout << "5. Anggota yang terdaftar" << endl;
    cout << "6. Menampilkan Daftar Buku" << endl;
    cout << "7. Pencarian Buku Cepat" << endl;
    cout << "8. Keluar" << endl;

    int input;
    cout << "INPUT  : ";
    cin >> input;

    switch (input)
    {
    case 1:
        // Tambah Buku
        {
            string title, author;
            int year;

            cin.ignore(); // menghapus newline dari buffer

            cout << "Judul Buku\t: ";
            getline(cin, title);

            cout << "Penulis\t\t: ";
            getline(cin, author);

            cout << "Tahun Terbit\t: ";
            cin >> year;

            // Membuat objek buku baru dengan informasi baru
            Book newbook(title, author, year, true);

            // menambahkan buku baru ke dalam list books
            books.push_back(newbook);

            // Memetakan ID buku ke judul buku
            bookIdToTitle[bookId] = title;
            bookId++;

            // Masukkan judul buku ke dalam BST
            titleSearchTree.insert(title);

            cout << "Buku berhasil ditambahkan dengan ID : " << bookId << endl;
            cout << endl;

            goto Main_menu;
        }
        break;
    case 2:
        // Tambah anggota baru
        {
            string memberName;

            cin.ignore(); // menghapus \n dari buffer

            cout << "Nama Anggota : ";
            getline(cin, memberName);

            // Menambahkan ke set
            members.insert(memberName);
            cout << "Anggota berhasil ditambahkan. " << endl;
            cout << endl;

            goto Main_menu;
        }
        break;
    case 3:
    {
        // Proses Peminjaman Buku
        string memberName, bookTitle;

        cin.ignore(); // menghapus newline dari buffer

        cout << "Nama Anggota : ";
        getline(cin, memberName);

        // cek apakah nama sudah terdaftar sebagai anggota
        if (members.find(memberName) == members.end())
        {
            cout << "Kamu belum terdaftar menjadi anggota. Silakan membuat anggota baru." << endl;
            cout << endl;
            goto Main_menu;
        }

        // Menampilkan daftar buku di perpustakaan
        cout << "------------------------------------------------------------------------------------------" << endl;
        cout << "\t\t\t\tBUKU PERPUSTAKAAN\n"
             << endl;
        cout << left
             << setw(35) << "Judul Buku"
             << setw(25) << "Penulis"
             << setw(10) << "Tahun"
             << setw(15) << "Ketersedian" << endl;
        cout << "------------------------------------------------------------------------------------------" << endl;

        for (auto &book : books)
        {
            cout << left
                 << setw(35) << book.title
                 << setw(25) << book.author
                 << setw(10) << book.year
                 << setw(15) << (book.available ? "Ada" : "Tidak ada") << endl;
        }

        cout << endl;

        string searchTitle;
        cout << "Masukkan judul buku yang ingin dipinjam : ";
        getline(cin, searchTitle);

        // Mencari buku berdasarkan judul
        bool found = false;
        for (auto &book : books)
        {
            if (book.title == searchTitle && book.available)
            {
                book.available = false; // tandai buku sebagai dipinjam
                book.borrower = memberName;
                queueBook.push(book); // tambahkan buku ke queue peminjaman
                found = true;
                cout << "Buku '" << searchTitle << "' berhasil dipinjam oleh " << book.borrower << endl;
                break;
            }
        }

        if (!found)
        {
            cout << "Buku '" << searchTitle << "' tidak tersedia atau sudah dipinjam." << endl;
        }

        cout << endl;
        goto Main_menu;
    }
    break;
    case 4:
    {
        // Pengembalian buku
        string bookToReturn;
        cin.ignore(); // Menghapus newline dari buffer
        cout << "Masukkan Judul Buku yang ingin dikembalikan : ";
        getline(cin, bookToReturn);

        bool bookReturned = false;

        while (!queueBook.empty())
        {
            Book currentBook = queueBook.front();
            queueBook.pop();

            if (currentBook.title == bookToReturn)
            {
                // Temukan buku yang ingin dikembalikan
                for (auto &book : books)
                {
                    if (book.title == bookToReturn)
                    {
                        book.available = true; // tandai buku dalam books sebagai tersedia
                        book.borrower = " ";
                        break;
                    }
                }

                cout << "Buku " << currentBook.title << " berhasil dikembalikan" << endl;
                bookReturned = true;
            }
            else
            {
                basketStack.push(currentBook); // buku lain dimasukkan ke dalam stack
            }
        }

        // Kembalikan buku dari stack ke queue (jika ada)
        while (!basketStack.empty())
        {
            queueBook.push(basketStack.top());
            basketStack.pop();
        }

        if (!bookReturned)
        {
            cout << "Buku " << bookToReturn << " tidak ditemukan dalam antrian peminjaman" << endl;
        }

        cout << endl;
        goto Main_menu;
    }
    break;

    case 5:
        // Anggota yang terdaftar
        {
            int number = 1;
            cout << "Anggota yang terdaftar\t: " << endl;
            for (const auto &Anggota : members)
            {
                cout << number << ". " << Anggota << endl;
                number++;
            }

            cout << endl;
            cout << "[1] Kembali ke Menu Utama\n[0] Keluar Program" << endl;
            int quit;
            cin >> quit;
            if (quit == 1)
            {
                system("cls");
                goto Main_menu;
            }
            else
            {
                goto QUIT;
            }
        }
        break;
    case 6:
        // Menampilkan daftar buku perpustakaan
        {
            cout << "------------------------------------------------------------------------------------------" << endl;
            cout << "\t\t\t\tBUKU PERPUSTAKAAN\n"
                 << endl;

            cout << left
                 << setw(35) << "Judul Buku"
                 << setw(25) << "Penulis"
                 << setw(10) << "Tahun"
                 << setw(15) << "Ketersedian" << endl;
            cout << "------------------------------------------------------------------------------------------" << endl;

            for (const auto &book : books)
            {
                cout << left
                     << setw(35) << book.title
                     << setw(25) << book.author
                     << setw(10) << book.year
                     << setw(15) << (book.available ? "Ada" : "Tidak ada") << endl;
            }

            cout << endl;
            cout << "[1] Kembali ke Menu Utama\n[0] Keluar Program" << endl;
            int quit;
            cin >> quit;
            if (quit == 1)
            {
                system("cls");
                goto Main_menu;
            }
            else
            {
                goto QUIT;
            }
        }
        break;
    case 7:
    {
        // Pencarian Judul Buku menggunakan BST
        string searching_Title;
        cin.ignore();

        cout << "Masukkan judul buku yang ingin dicari : ";
        getline(cin, searching_Title);

        if (titleSearchTree.search(searching_Title))
        {
            // Jika judul buku ditemukan, maka tampilkan informasi buku
            cout << "Buku Ditemukan :\n"
                 << endl;
            for (const auto &book : books)
            {
                if (book.title == searching_Title)
                {
                    cout << "Judul Buku\t: " << book.title << endl;
                    cout << "Tahun\t\t: " << book.year << endl;
                    cout << "Penulis\t\t: " << book.author << endl;

                    if (book.available)
                    {
                        cout << "Ketersediaan\t: Ada" << endl;
                    }
                    else
                    {
                        cout << "Sedang dipinjam oleh " << book.borrower << endl;
                    }
                    cout << endl;
                }
            }
        }
        else
        {
            // Jika judul buku tidak ditemukan dalam BST
            cout << "Buku dengan judul '" << searching_Title << "' tidak ditemukan." << endl;
        }

        cout << endl;
        cout << "[1] Kembali ke Menu Utama\n[0] Keluar Program" << endl;
        int exit;
        cin >> exit;
        if (exit == 1)
        {
            system("cls");
            goto Main_menu;
        }
        else
        {
            goto QUIT;
        }
    }
    break;

    case 8:
    {
    QUIT:
        // Keluar dari program
        // Cek apakah masih ada buku yang belum dikembalikan
        bool booksNotReturned = false;
        for (const auto &book : books)
        {
            if (!book.available)
            {
                booksNotReturned = true;
                break;
            }
        }

        if (booksNotReturned)
        {
            char confirm;
            cout << "Masih ada buku yang belum dikembalikan. Yakin akan keluar dari program? (Y/N): ";
            cin >> confirm;
            if (confirm == 'Y' || confirm == 'y')
            {
                cout << "Terima kasih dan Sampai Jumpa !" << endl;
                return 0; // Keluar dari program
            }
            else
            {
                goto Main_menu;
            }
        }
        else
        {
            cout << "Terima kasih dan Sampai Jumpa !" << endl;
            return 0; // Keluar dari program
        }
    }
    break;
    default:
        cout << "Pilihan tidak valid." << endl;
        goto Main_menu;
        break;
    }
    return 0;
}
