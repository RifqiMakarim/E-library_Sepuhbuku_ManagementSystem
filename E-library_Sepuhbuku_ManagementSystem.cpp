// Rifqi Makarim (L0123122)

#include <iostream>
#include <list>
#include <map>
#include <set>
#include <vector>
#include <iomanip>
#include <string>
#include <queue>
#include <stack>
#include <unordered_map>
#include <sstream>
#include <limits>
#include <utility>

using namespace std;

struct Book
{
    string title;
    string author;
    int year;
    bool available;
    string borrower;
    string genre;

    // Default constructor
    Book() : title(""), author(""), year(0), available(false), borrower(""), genre("") {}

    // Parameterized contructor
    Book(const string &t, const string &a, int y, bool av, const string &g) : title(t), author(a), year(y), available(av), borrower(""), genre(g) {}
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

// Definisi Pengurus Perpustakaan menggunakan Binary Tree
struct OrganizerNode
{
    string name;
    string role;
    int OrganizerID;
    OrganizerNode *left;
    OrganizerNode *right;

    OrganizerNode(const string &n, const string &r, int id) : name(n), role(r), OrganizerID(id), left(nullptr), right(nullptr) {}
};

// Fungsi untuk insert node ke dalam Binary Tree
OrganizerNode *insertNode(OrganizerNode *root, const string &name, const string &role, int memberID)
{
    if (root == nullptr)
        return new OrganizerNode(name, role, memberID);

    // Pilih secara acak antara left atau right untuk insert
    if (rand() % 2 == 0)
        root->left = insertNode(root->left, name, role, memberID);
    else
        root->right = insertNode(root->right, name, role, memberID);

    return root;
}

// Fungsi untuk menampilkan inorder traversal dari Binary Tree
void inorderTraversal(OrganizerNode *node)
{
    if (node == nullptr)
        return;

    inorderTraversal(node->left);
    cout << setw(25) << node->name << setw(15) << node->role << setw(10) << node->OrganizerID << endl;
    inorderTraversal(node->right);
}

// Kelompok Perpustakaan dengan disjoint set
class DisjointSet
{
private:
    unordered_map<string, string> parent;
    unordered_map<string, int> size;

public:
    // Constructor
    DisjointSet() {}

    // Inisialisasi setiap anggota sebagai kelompok terpisah
    void makeSet(const vector<string> &people)
    {
        for (const string &person : people)
        {
            parent[person] = person;
            size[person] = 1;
        }
    }

    // Temukan representatif (root) dari kelompok
    string find(string person)
    {
        if (parent[person] != person)
        {
            parent[person] = find(parent[person]); // Path compression
        }
        return parent[person];
    }

    // Gabungkan dua kelompok menjadi satu
    void unionSets(string person1, string person2)
    {
        string root1 = find(person1);
        string root2 = find(person2);

        if (root1 != root2)
        {
            if (size[root1] < size[root2])
            {
                swap(root1, root2);
            }
            parent[root2] = root1;
            size[root1] += size[root2];
        }
    }

    // Menampilkan semua kelompok pertemanan
    void displayGroups()
    {
        unordered_map<string, vector<string>> groups;

        // Mengelompokkan semua anggota berdasarkan root mereka
        for (auto &pair : parent)
        {
            string person = pair.first;
            string root = find(person);
            groups[root].push_back(person);
        }

        // Menampilkan kelompok pertemanan dengan nama anggota
        cout << "Jumlah kelompok perpustakaan : " << groups.size() << endl;
        for (const auto &group : groups)
        {
            cout << "Kelompok " << group.first << "\t: ";
            for (const string &person : group.second)
            {
                cout << person << " ";
            }
            cout << endl;
        }
    }
};

void swap(Book &a, Book &b)
{
    Book temp = a;
    a = b;
    b = temp;
}

// QuickSort partition function untuk tahun
int partitionYear(vector<Book> &books, int low, int high)
{
    int pivot = books[high].year;
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++)
    {
        if (books[j].year < pivot)
        {
            i++;
            swap(books[i], books[j]);
        }
    }
    swap(books[i + 1], books[high]);
    return (i + 1);
}

// QuickSort function untuk tahun
void quickSortYear(vector<Book> &books, int low, int high)
{
    if (low < high)
    {
        int pi = partitionYear(books, low, high);
        quickSortYear(books, low, pi - 1);
        quickSortYear(books, pi + 1, high);
    }
}

// QuickSort partition function untuk penulis
int partitionAuthor(vector<Book> &books, int low, int high)
{
    string pivot = books[high].author;
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++)
    {
        if (books[j].author < pivot)
        {
            i++;
            swap(books[i], books[j]);
        }
    }
    swap(books[i + 1], books[high]);
    return (i + 1);
}

// QuickSort untuk penulis
void quickSortAuthor(vector<Book> &books, int low, int high)
{
    if (low < high)
    {
        int pi = partitionAuthor(books, low, high);
        quickSortAuthor(books, low, pi - 1);
        quickSortAuthor(books, pi + 1, high);
    }
}

// Struktur untuk merepresentasikan edge
struct Edge
{
    int to;
    int weight;
    Edge(int _to, int _weight) : to(_to), weight(_weight) {}
};

class Graph
{
private:
    int numNodes;
    vector<vector<Edge>> adjList;
    vector<string> nodeNames; // Untuk menyimpan nama daerah rumah

public:
    Graph(int numNodes) : numNodes(numNodes)
    {
        adjList.resize(numNodes + 1);   // Mulai dari indeks 1
        nodeNames.resize(numNodes + 1); // Mulai dari indeks 1
    }

    // Menambahkan edge ke graf (bidirectional)
    void addEdge(int u, int v, int weight)
    {
        adjList[u].push_back(Edge(v, weight));
        adjList[v].push_back(Edge(u, weight)); // Jika graf tidak berarah
    }

    // Menambahkan nama daerah rumah
    void addNodeName(int node, string name)
    {
        nodeNames[node] = name;
    }

    // Algoritma Prim untuk mencari MST
    vector<Edge> primMST()
    {
        vector<bool> visited(numNodes + 1, false);
        vector<Edge> minimumSpanningTree;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        // Memulai dari node 1
        pq.push(make_pair(0, 1)); // Bobot, node
        while (!pq.empty())
        {
            int u = pq.top().second;
            int minWeight = pq.top().first;
            pq.pop();

            if (visited[u])
                continue;
            visited[u] = true;

            // Menambahkan edge ke MST
            if (u != 1)
            { // Kecuali jika node adalah node awal (1)
                minimumSpanningTree.push_back(Edge(u, minWeight));
            }

            // Memproses tetangga
            for (Edge &edge : adjList[u])
            {
                int v = edge.to;
                int weight = edge.weight;
                if (!visited[v])
                {
                    pq.push(make_pair(weight, v));
                }
            }
        }

        return minimumSpanningTree;
    }

    // Menampilkan MST beserta rutenya
    void printMST(const vector<Edge> &mstEdges)
    {
        int totalWeight = 0;
        cout << endl;
        cout << "Menggunakan Minimum Spanning Tree (MST) dengan Algoritma Prim\n";
        cout << "Berikut Urutan Cabang Terdekat : " << endl;
        for (const Edge &edge : mstEdges)
        {
            cout << "Cabang " << edge.to << " dengan jarak " << edge.weight << " dari cabang 1\n";
            totalWeight += edge.weight;
        }
        cout << "Total jarak minimum: " << totalWeight << endl;
    }

    // Algoritma Dijkstra untuk mencari jalur terpendek dari cabang 1 ke rumah
    void dijkstraShortestPath(int target)
    {
        vector<int> dist(numNodes + 1, numeric_limits<int>::max());
        vector<int> parent(numNodes + 1, -1);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        dist[1] = 0;              // Jarak dari node 1 ke node 1 adalah 0
        pq.push(make_pair(0, 1)); // Bobot, node

        while (!pq.empty())
        {
            int u = pq.top().second;
            int currDist = pq.top().first;
            pq.pop();

            if (currDist > dist[u])
                continue;

            for (Edge &edge : adjList[u])
            {
                int v = edge.to;
                int weight = edge.weight;
                if (dist[u] + weight < dist[v])
                {
                    dist[v] = dist[u] + weight;
                    pq.push(make_pair(dist[v], v));
                    parent[v] = u;
                }
            }
        }

        // Mencetak rute terpendek
        if (dist[target] == numeric_limits<int>::max())
        {
            cout << "Tidak ada jalur dari Cabang 1 ke rumah " << nodeNames[target] << endl;
            return;
        }

        vector<int> path;
        for (int at = target; at != -1; at = parent[at])
        {
            path.push_back(at);
        }

        // Menggunakan fungsi reverseVector untuk membalikkan urutan
        reverseVector(path);

        cout << endl;
        cout << "Jalur tercepat untuk pengiriman buku dari Cabang 1 ke rumah " << nodeNames[target] << ":\n";
        for (size_t i = 0; i < path.size(); ++i)
        {
            if (i > 0)
                cout << " -> ";
            cout << nodeNames[path[i]];
        }
        cout << "\nJarak : " << dist[target] << endl;
    }

    // Fungsi untuk membalikkan vektor
    void reverseVector(vector<int> &path)
    {
        int n = path.size();
        for (int i = 0; i < n / 2; ++i)
        {
            swap(path[i], path[n - i - 1]);
        }
    }
};

// Struktur untuk merepresentasikan node dalam tree
struct Tree_Node
{
    string name;
    vector<Tree_Node *> children;

    Tree_Node(const string &name) : name(name) {}
};

class BookCategoryTree
{
private:
    Tree_Node *root;

    // Fungsi rekursif untuk menampilkan tree
    void printTree(Tree_Node *node, int depth) const
    {
        if (!node)
            return;
        for (int i = 0; i < depth; ++i)
        {
            cout << "  ";
        }
        cout << "- " << node->name << endl;
        for (Tree_Node *child : node->children)
        {
            printTree(child, depth + 1);
        }
    }

public:
    BookCategoryTree(const string &rootName)
    {
        root = new Tree_Node(rootName);
    }

    // Menambahkan kategori atau subkategori
    Tree_Node *addCategory(Tree_Node *parent, const string &categoryName)
    {
        Tree_Node *newCategory = new Tree_Node(categoryName);
        parent->children.push_back(newCategory);
        return newCategory;
    }

    // Menampilkan tree dari root
    void printTree() const
    {
        printTree(root, 0);
    }

    // Mengakses root tree
    Tree_Node *getRoot() const
    {
        return root;
    }
};

int main()
{
    list<Book> books;
    map<int, string> bookIdToTitle;
    set<string> members;
    queue<Book> queueBook;
    stack<Book> basketStack;
    vector<string> people;
    BST titleSearchTree;

    int bookId = 0;

    // Daftar Buku
    books.push_back(Book("The Great Gatsby", "F. Scott Fitzgerald", 1925, true, "Fiction"));
    books.push_back(Book("The Hunger Games", "Suzanne Collins", 2008, true, "Science Fiction"));
    books.push_back(Book("1984", "George Orwell", 1949, true, "Dystopian"));
    books.push_back(Book("Python Crash Course", "Eric Matthes", 2015, true, "Programming"));
    books.push_back(Book("Learning Python", "Mark Lutz", 2013, true, "Programming"));
    books.push_back(Book("Algorithms (4th Edition)", "Robert,Kevin", 2011, true, "Computer Science"));
    books.push_back(Book("A Game of Thrones", "George R.R. Martin", 1996, true, "Fantasy"));
    books.push_back(Book("Laskar Pelangi", "Andrea Hirata", 2005, true, "Indonesian Literature"));
    books.push_back(Book("Bumi Manusia", "Pramoedya Ananta Toer", 1980, true, "Indonesian Literature"));
    books.push_back(Book("Dunia Sophie", "Jostein Gaarder", 1991, true, "Philosophy"));
    books.push_back(Book("Pulang", "Tere Liye", 2016, true, "Indonesian Literature"));
    books.push_back(Book("Filosofi Teras", "Henry Manampiring", 2015, true, "Philosophy"));
    books.push_back(Book("Ketika Cinta Bertasbih", "El Shirazy", 2004, true, "Religious"));
    books.push_back(Book("Manusia Setengah Salmon", "Raditya Dika", 2011, true, "Comedy"));
    books.push_back(Book("Java Programming", "Rinaldi Munir", 2016, true, "Programming"));
    books.push_back(Book("PHP & MySQL untuk Pemula", "Yudi Yanri", 2017, true, "Programming"));
    books.push_back(Book("Belajar Pemrograman Arduino", "Donny Maulana", 2018, true, "Electronics"));
    books.push_back(Book("Node.js: Konsep dan Aplikasi", "Ferdy Gale", 2018, true, "Programming"));
    books.push_back(Book("Belajar Bahasa C++", "Budi Raharjo", 2019, true, "Programming"));

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

    // Daftar Pengurus Perpustakaan
    OrganizerNode *root = nullptr;
    root = insertNode(root, "Muhammad Dzimar", "Ketua", 1101);
    root = insertNode(root, "Kartika Wulandari", "Sekretaris", 1102);
    root = insertNode(root, "Muhammad Syarif", "Editor", 1103);
    root = insertNode(root, "Naufal Narendro", "Admin IT", 1104);
    root = insertNode(root, "Azmi Naufal", "Admin IT", 1105);
    root = insertNode(root, "Mahrus Ali", "Admin IT", 1106);
    root = insertNode(root, "Bambang Pacul", "Penjaga", 1107);
    root = insertNode(root, "Ginting Kei Boon", "Penjaga", 1108);

    // Inisialisasi Graph untuk perpustakaan dengan 5 cabang
    int numLibraryNodes = 5;
    Graph libraryGraph(numLibraryNodes);

    // Menambahkan edge antar cabang perpustakaan
    libraryGraph.addEdge(1, 2, 10);
    libraryGraph.addEdge(1, 5, 20);
    libraryGraph.addEdge(2, 3, 30);
    libraryGraph.addEdge(2, 4, 40);
    libraryGraph.addEdge(2, 5, 50);
    libraryGraph.addEdge(3, 4, 60);
    libraryGraph.addEdge(4, 5, 70);

    vector<Edge> mst = libraryGraph.primMST();

    // Inisialisasi Graph untuk layanan pengantaran buku ke rumah dengan 8 daerah rumah (A-H)
    int numDeliveryNodes = 9; // 1 cabang + 8 daerah rumah
    Graph deliveryGraph(numDeliveryNodes);
    // Menambahkan nama-nama daerah rumah (A-H)
    deliveryGraph.addNodeName(1, "Cabang 1");
    deliveryGraph.addNodeName(2, "A");
    deliveryGraph.addNodeName(3, "B");
    deliveryGraph.addNodeName(4, "C");
    deliveryGraph.addNodeName(5, "D");
    deliveryGraph.addNodeName(6, "E");
    deliveryGraph.addNodeName(7, "F");
    deliveryGraph.addNodeName(8, "G");
    deliveryGraph.addNodeName(9, "H");

    // Menambahkan edge antar cabang perpustakaan dan daerah rumah
    deliveryGraph.addEdge(1, 2, 20); // Jarak dari cabang 1 ke A adalah 20
    deliveryGraph.addEdge(1, 5, 80); // Jarak dari cabang 1 ke D adalah 80
    deliveryGraph.addEdge(1, 8, 90); // Jarak dari cabang 1 ke G adalah 90
    deliveryGraph.addEdge(2, 3, 20); // Jarak dari A ke B adalah 20
    deliveryGraph.addEdge(3, 7, 10); // Jarak dari B ke F adalah 10
    deliveryGraph.addEdge(4, 7, 50); // Jarak dari C ke F adalah 50
    deliveryGraph.addEdge(4, 5, 10); // Jarak dari C ke D adalah 10
    deliveryGraph.addEdge(4, 9, 20); // Jarak dari C ke H adalah 20
    deliveryGraph.addEdge(5, 4, 10); // Jarak dari D ke C adalah 10
    deliveryGraph.addEdge(5, 8, 20); // Jarak dari D ke G adalah 20
    deliveryGraph.addEdge(6, 3, 50); // Jarak dari E ke B adalah 50
    deliveryGraph.addEdge(7, 4, 10); // Jarak dari F ke C adalah 10
    deliveryGraph.addEdge(7, 5, 40); // Jarak dari F ke D adalah 40
    deliveryGraph.addEdge(8, 2, 20); // Jarak dari G ke A adalah 20
    deliveryGraph.addEdge(8, 6, 30); // Jarak dari G ke E adalah 30

    // Membuat tree dengan root "Books"
    BookCategoryTree bookTree("Books");

    // Menambahkan kategori utama
    Tree_Node *fiction = bookTree.addCategory(bookTree.getRoot(), "Fiction");
    Tree_Node *nonFiction = bookTree.addCategory(bookTree.getRoot(), "Non-Fiction");

    // Menambahkan subkategori pada kategori Fiction
    Tree_Node *mystery = bookTree.addCategory(fiction, "Mystery");
    Tree_Node *romance = bookTree.addCategory(fiction, "Romance");
    Tree_Node *scienceFiction = bookTree.addCategory(fiction, "Science Fiction");

    // Menambahkan subkategori pada kategori Non-Fiction
    Tree_Node *history = bookTree.addCategory(nonFiction, "History");
    Tree_Node *science = bookTree.addCategory(nonFiction, "Science");
    Tree_Node *biography = bookTree.addCategory(nonFiction, "Biography");

    // Menambahkan sub-subkategori
    bookTree.addCategory(mystery, "Detective");
    bookTree.addCategory(mystery, "Thriller");
    bookTree.addCategory(romance, "Contemporary");
    bookTree.addCategory(romance, "Historical");
    bookTree.addCategory(scienceFiction, "Dystopian");
    bookTree.addCategory(scienceFiction, "Space Opera");

    // Menambahkan sub-subkategori pada Non-Fiction
    bookTree.addCategory(history, "Ancient");
    bookTree.addCategory(history, "Modern");
    bookTree.addCategory(science, "Physics");
    bookTree.addCategory(science, "Biology");
    bookTree.addCategory(biography, "Autobiography");
    bookTree.addCategory(biography, "Memoir");

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
    cout << "8. Sorting Buku " << endl;
    cout << "9. Kelompok Buku Perpustakaan" << endl;
    cout << "10. Info Jarak Antar Cabang Perpustakaan" << endl;
    cout << "11. Layanan Pencari Rute Tercepat Pengantaran Buku ke Rumah" << endl;
    cout << "12. Pengurus Perpustakaan" << endl;
    cout << "13. Informasi Kategori Buku" << endl;
    cout << "0. Keluar" << endl;

    int input;
    cout << "INPUT  : ";
    cin >> input;

    switch (input)
    {
    case 1:
        // Tambah Buku
        {
            string title, author, genre;
            int year;

            cin.ignore(); // menghapus newline dari buffer

            cout << "Judul Buku\t: ";
            getline(cin, title);

            cout << "Penulis\t\t: ";
            getline(cin, author);

            cout << "Tahun Terbit\t: ";
            cin >> year;

            cout << "Genre\t\t: ";
            cin.ignore();
            getline(cin, genre);

            // Membuat objek buku baru dengan informasi baru
            Book newbook(title, author, year, true, genre);

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
            cout << "Kamu belum terdaftar menjadi anggota. Silakan menambakan anggota baru." << endl;
            cout << endl;
            goto Main_menu;
        }

        // Menampilkan daftar buku di perpustakaan
        cout << "------------------------------------------------------------------------------------------------------------" << endl;
        cout << "\t\t\t\t\tBUKU PERPUSTAKAAN\n"
             << endl;
        cout << left
             << setw(35) << "Judul Buku"
             << setw(25) << "Penulis"
             << setw(10) << "Tahun"
             << setw(15) << "Ketersedian"
             << setw(24) << "Genre" << endl;
        cout << "------------------------------------------------------------------------------------------------------------" << endl;

        for (auto &book : books)
        {
            cout << left
                 << setw(35) << book.title
                 << setw(25) << book.author
                 << setw(10) << book.year
                 << setw(15) << (book.available ? "Ada" : "Tidak ada")
                 << setw(24) << book.genre << endl;
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
            cout << "------------------------------------------------------------------------------------------------------------" << endl;
            cout << "\t\t\t\t\tBUKU PERPUSTAKAAN\n"
                 << endl;

            cout << left
                 << setw(35) << "Judul Buku"
                 << setw(25) << "Penulis"
                 << setw(10) << "Tahun"
                 << setw(15) << "Ketersedian"
                 << setw(24) << "Genre" << endl;
            cout << "------------------------------------------------------------------------------------------------------------" << endl;

            for (const auto &book : books)
            {
                cout << left
                     << setw(35) << book.title
                     << setw(25) << book.author
                     << setw(10) << book.year
                     << setw(15) << (book.available ? "Ada" : "Tidak ada")
                     << setw(24) << book.genre << endl;
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
                    cout << "Genre\t\t: " << book.genre << endl;

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
        // Sorting Buku Berdasarkan tahun dan genre Menggunakan Quick Sort
        {
            vector<Book> booksvector(books.begin(), books.end());
            cout << "Sorting Buku" << endl;
            cout << "[1] Berdasarkan Tahun" << endl;
            cout << "[2] Berdasarkan Penulis" << endl;

            int choice;
            do
            {
                cout << "INPUT : ";
                cin >> choice;
                if (choice == 1)
                {
                    quickSortYear(booksvector, 0, books.size() - 1);
                    cout << left << setw(6) << "Year" << setw(35) << "Title" << setw(25) << "Author" << setw(15) << "Genre" << endl;
                    cout << "--------------------------------------------------------------------------------------------------" << endl;
                    for (const auto &book : booksvector)
                    {
                        cout << left << setw(6) << book.year << setw(35) << book.title << setw(25) << book.author << setw(15) << book.genre << endl;
                    }
                    cout << endl;
                    cout << "[1] Kembali [0] Keluar Program" << endl;
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
                else if (choice == 2)
                {
                    quickSortAuthor(booksvector, 0, books.size() - 1);
                    cout << left << setw(25) << "Author" << setw(35) << "Title" << setw(6) << "Year" << setw(15) << "Genre" << endl;
                    cout << "--------------------------------------------------------------------------------------------------" << endl;
                    for (const auto &book : booksvector)
                    {
                        cout << left << setw(25) << book.author << setw(35) << book.title << setw(6) << book.year << setw(15) << book.genre << endl;
                    }
                    cout << endl;
                    cout << "[1] Kembali [0] Keluar Program" << endl;
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
                else
                {
                    cout << "Silakan Masukkan [1] atau [2]" << endl;
                }
            } while (choice != 1 && choice != 2);
        }
        break;

    case 9:
        // Kelompok Buku Perpustakaan
        {
            int numPeople;

            // Meminta pengguna untuk memasukkan jumlah anggota kelompok
            cout << "Masukkan jumlah Anggota yang ingin dijadikan kelompok : ";
            cin >> numPeople;
            cin.ignore(); // Membersihkan newline di buffer

            cout << endl;
            // Meminta pengguna untuk memasukkan nama-nama anggota kelompok
            cout << "[Gunakan Nama Panggilan]" << endl;
            cout << "Masukkan nama-nama anggota kelompok: " << endl;
            for (int i = 0; i < numPeople; ++i)
            {
                string person;
                cout << "Anggota " << i + 1 << ": ";
                getline(cin, person);
                people.push_back(person);
            }

            // Meminta pengguna untuk memasukkan hubungan pertemanan antara anggota kelompok
            cout << endl;
            cout << "Masukkan pertemanan antara anggota (format: nama1 nama2, akhiri dengan titik):" << endl;
            vector<pair<string, string>> friendships;
            string friendship;
            while (getline(cin, friendship) && friendship != ".")
            {
                stringstream ss(friendship);
                string person1, person2;
                ss >> person1 >> person2;
                friendships.push_back({person1, person2});
            }

            // Membuat objek DisjointSet
            DisjointSet ds;
            ds.makeSet(people);

            // Menggabungkan kelompok berdasarkan pertemanan yang dimasukkan
            for (const auto &friendship : friendships)
            {
                ds.unionSets(friendship.first, friendship.second);
            }

            // Menampilkan kelompok-kelompok pertemanan
            cout << endl;
            cout << "=== Kelompok Perpustakaan ===" << endl;
            ds.displayGroups();

            cout << endl;
            cout << "[1] Kembali [0] Keluar Program" << endl;
            int choice;
            cin >> choice;
            if (choice == 1)
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

    case 10:
        // Pengiriman Buku Antar Cabang Perpus
        {
            libraryGraph.printMST(mst);
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

    case 11:
        // Layanan Pengantaran Buku ke Rumah
        {
            // Memilih daerah rumah yang dipilih untuk pengiriman buku ke rumah
            char homeChoice;
            int targetNode;
            
            // Keterangan Tempat 
            cout << endl;
            cout << "[A] Kawasaki [B] Yokohama   [C] Chiba "<< endl;
            cout << "[D] Saitama  [E] Kawaguchi  [F] Ichikawa" << endl;
            cout << "[G] Kawagoe  [H] Funabashi " << endl;
            cout << "Pilih daerah rumah (A-H): ";
            cin >> homeChoice;

            // Validasi pilihan daerah rumah
            if (homeChoice < 'A' || homeChoice > 'H')
            {
                cout << "Pilihan tidak valid.\n";
                return 1;
            }

            // Konversi pilihan ke indeks node (A-H diubah menjadi 2-9)
            targetNode = homeChoice - 'A' + 2;

            // Menjalankan algoritma Dijkstra untuk mencari jalur terpendek dari cabang 1 ke rumah yang dipilih
            deliveryGraph.dijkstraShortestPath(targetNode);

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

    // Melihat Pengurus Perpustakaan
    case 12:
    {
        cout << endl;
        cout << "Pengurus Perpustakaan :" << endl;
        cout << left << setw(25) << "Nama" << setw(15) << "Peran" << setw(10) << "ID" << endl;
        cout << "-------------------------------------------------" << endl;
        inorderTraversal(root);
        cout << endl;
        cout << "[1] Kembali [0] Keluar Program" << endl;
        int choice;
        cin >> choice;
        if (choice == 1)
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

    case 13:
    {
        cout << "Berikut Informasi Mengenai Category Buku : " << endl;
        // Menampilkan tree
        bookTree.printTree();
        cout << endl;
        cout << "[1] Kembali [0] Keluar Program" << endl;
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

    case 0:
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
