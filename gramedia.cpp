#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>

using namespace std;

struct Node {
    string judulbuku, penulis, kategori;
    int ID;
    Node *left;
    Node *right;
    int height;
};

Node *createNode(int ID, string judulbuku, string penulis, string kategori) {
    Node *newNode = new Node();
    newNode->ID = ID;
    newNode->judulbuku = judulbuku;
    newNode->penulis = penulis;
    newNode->kategori = kategori;
    newNode->left = newNode->right = nullptr;
    newNode->height = 1;
    return newNode;
}

string limitString(string str, int width) {
    if (str.length() > width) {
        return str.substr(0, width - 3) + "...";
    }
    return str;
}

int height(Node *N) {
    if (N == nullptr) return 0;
    return N->height;
}

int getbalance(Node *N) {
    if (N == nullptr) return 0;
    return height(N->left) - height(N->right);
}

void updateHeight(Node *N) {
    N->height = 1 + max(height(N->left), height(N->right));
}

Node *rotateleft(Node *N) {
    Node *temp = N->right;
    Node *empty = temp->left;
    temp->left = N;
    N->right = empty;
    updateHeight(N);
    updateHeight(temp);
    return temp;
}

Node *rotateright(Node *N) {
    Node *temp = N->left;
    Node *empty = temp->right;
    temp->right = N;
    N->left = empty;
    updateHeight(N);
    updateHeight(temp);
    return temp;
}

Node *minValue(Node *node) {
    while (node->left != nullptr) node = node->left;
    return node;
}

Node *insertBST(Node *root, int ID, string judulbuku, string penulis, string kategori) {
    if (root == nullptr) return createNode(ID, judulbuku, penulis, kategori);
    if (ID < root->ID) root->left = insertBST(root->left, ID, judulbuku, penulis, kategori);
    else if (ID > root->ID) root->right = insertBST(root->right, ID, judulbuku, penulis, kategori);
    return root;
}

Node *deleteBST(Node *root, int ID) {
    if (root == nullptr) return root;
    if (ID < root->ID) root->left = deleteBST(root->left, ID);
    else if (ID > root->ID) root->right = deleteBST(root->right, ID);
    else {
        if (root->left == nullptr) {
            Node *temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            Node *temp = root->left;
            delete root;
            return temp;
        }
        Node *temp = minValue(root->right);
        root->ID = temp->ID;
        root->judulbuku = temp->judulbuku;
        root->penulis = temp->penulis;
        root->kategori = temp->kategori;
        root->right = deleteBST(root->right, temp->ID);
    }
    return root;
}

Node *insertAVL(Node *root, int ID, string judulbuku, string penulis, string kategori) {
    if (root == nullptr) return createNode(ID, judulbuku, penulis, kategori);
    if (ID < root->ID) root->left = insertAVL(root->left, ID, judulbuku, penulis, kategori);
    else if (ID > root->ID) root->right = insertAVL(root->right, ID, judulbuku, penulis, kategori);

    updateHeight(root);
    int balance = getbalance(root);

    if (balance > 1 && ID < root->left->ID) return rotateright(root);
    if (balance < -1 && ID > root->right->ID) return rotateleft(root);
    if (balance > 1 && ID > root->left->ID) {
        root->left = rotateleft(root->left);
        return rotateright(root);
    }
    if (balance < -1 && ID < root->right->ID) {
        root->right = rotateright(root->right);
        return rotateleft(root);
    }
    return root;
}

Node *deleteAVL(Node *root, int ID) {
    if (root == nullptr) return root;
    if (ID < root->ID) root->left = deleteAVL(root->left, ID);
    else if (ID > root->ID) root->right = deleteAVL(root->right, ID);
    else {
        if (root->left == nullptr) {
            Node *temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            Node *temp = root->left;
            delete root;
            return temp;
        }
        Node *temp = minValue(root->right);
        root->ID = temp->ID;
        root->judulbuku = temp->judulbuku;
        root->penulis = temp->penulis;
        root->kategori = temp->kategori;
        root->right = deleteAVL(root->right, temp->ID);
    }
    if (root == nullptr) return root;
    updateHeight(root);
    int balance = getbalance(root);

    if (balance > 1 && getbalance(root->left) >= 0) return rotateright(root);
    if (balance > 1 && getbalance(root->left) < 0) {
        root->left = rotateleft(root->left);
        return rotateright(root);
    }
    if (balance < -1 && getbalance(root->right) <= 0) return rotateleft(root);
    if (balance < -1 && getbalance(root->right) > 0) {
        root->right = rotateright(root->right);
        return rotateleft(root);
    }
    return root;
}

Node *search(Node *root, int id) {
    if (root == nullptr) return nullptr;
    else if (id == root->ID) return root;
    else if (id < root->ID) return search(root->left, id);
    else return search(root->right, id);
}

void tampilList(Node *root) {
    if (root == nullptr) return;
    tampilList(root->left);
    cout << "| " << left << setw(5) << root->ID
         << "| " << left << setw(30) << limitString(root->judulbuku, 30)
         << "| " << left << setw(20) << limitString(root->penulis, 20)
         << "| " << left << setw(15) << limitString(root->kategori, 15)
         << "|" << endl;
    tampilList(root->right);
}

void printTreeStructure(Node *root, int space = 0) {
    int COUNT = 8;
    if (root == nullptr) return;
    space += COUNT;
    printTreeStructure(root->right, space);
    cout << endl;
    for (int i = COUNT; i < space; i++) cout << " ";
    cout << "[" << root->ID << "]\n";
    printTreeStructure(root->left, space);
}

void savefile(Node *root, ofstream &file) {
    if (root == nullptr) return;
    savefile(root->left, file);
    file << root->judulbuku << ";" << root->penulis << ";" << root->kategori << endl;
    savefile(root->right, file);
}

void updatefile(Node *root) {
    ofstream file("data.txt", ios::trunc);
    if (file.is_open()) {
        savefile(root, file);
        file.close();
    } else {
        cout << "Gagal Menyimpan data" << endl;
    }
}

void subMenu(Node* &root, int &nextID, bool isAVL) {
    int pilihan;
    string jenis = isAVL ? "AVL Tree" : "Binary Search Tree (BST)";

    do {
        cout << "\n=== Kelola dengan " << jenis << " ===" << endl;
        cout << "1. Insert\n2. Delete\n3. Search\n4. View (List)\n5. View (Structure Tree)\n0. Kembali\nPilihan: ";
        cin >> pilihan;
        cin.ignore();

        if (pilihan == 1) {
            string j, p, k;
            cout << "Masukkan Judul Buku: "; getline(cin, j);
            cout << "Masukkan Penulis: "; getline(cin, p);
            cout << "Masukkan Kategori: "; getline(cin, k);

            if (isAVL) root = insertAVL(root, nextID, j, p, k);
            else root = insertBST(root, nextID, j, p, k);

            cout << "Berhasil Input (ID: " << nextID << ")" << endl;
            nextID++;
            updatefile(root);
        } else if (pilihan == 2) {
            int targetID;
            cout << "Masukkan ID buku yang ingin dihapus: "; cin >> targetID;
            if (search(root, targetID) != nullptr) {
                if (isAVL) root = deleteAVL(root, targetID);
                else root = deleteBST(root, targetID);
                cout << "Buku ID " << targetID << " dihapus" << endl;
                updatefile(root);
            } else cout << "ID tidak ditemukan!" << endl;
        } else if (pilihan == 3) {
            int targetID;
            cout << "Masukkan ID dicari: "; cin >> targetID;
            Node *hasil = search(root, targetID);
            if (hasil) {
                cout << "=== DITEMUKAN ===\nID: " << hasil->ID << "\nJudul: " << hasil->judulbuku << "\nPenulis: " << hasil->penulis << "\nKategori: " << hasil->kategori << endl;
            } else cout << "Buku tidak ditemukan!" << endl;
        } else if (pilihan == 4) {
            cout << "\nData Buku (List View):" << endl;
            cout << "+" << string(7, '-') << "+" << string(32, '-') << "+" << string(22, '-') << "+" << string(17, '-') << "+" << endl;
            cout << "| " << left << setw(5) << "ID"
                 << "| " << left << setw(30) << "Judul Buku"
                 << "| " << left << setw(20) << "Penulis"
                 << "| " << left << setw(15) << "Kategori"
                 << "|" << endl;
            cout << "+" << string(7, '-') << "+" << string(32, '-') << "+" << string(22, '-') << "+" << string(17, '-') << "+" << endl;
            if (root == nullptr) {
                cout << "| " << setw(76) << "Data Kosong" << " |" << endl;
            } else {
                tampilList(root);
            }
            cout << "+" << string(7, '-') << "+" << string(32, '-') << "+" << string(22, '-') << "+" << string(17, '-') << "+" << endl;
        } else if (pilihan == 5) {
            cout << "\nVisualisasi Struktur " << jenis << ":" << endl;
            if (root == nullptr) cout << "Tree Kosong" << endl;
            else printTreeStructure(root);
        }

    } while (pilihan != 0);
}

int main() {
    Node *rootAVL = nullptr;
    Node *rootBST = nullptr;
    int id = 1;

    ifstream file("data.txt");
    if (!file) {
        ofstream createFile("data.txt");
        createFile.close();
    } else {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string judul, penulis, kategori;
            getline(ss, judul, ';');
            getline(ss, penulis, ';');
            getline(ss, kategori, ';');
            if (!judul.empty()) {
                rootAVL = insertAVL(rootAVL, id, judul, penulis, kategori);
                rootBST = insertBST(rootBST, id, judul, penulis, kategori);
                id++;
            }
        }
        file.close();
    }

    int menuUtama;
    do {
        cout << "\n=========== Main Menu Gramedia ===========" << endl;
        cout << "1. Kelola dengan BST" << endl;
        cout << "2. Kelola dengan AVL" << endl;
        cout << "3. Keluar" << endl;
        cout << "Pilihan: ";
        cin >> menuUtama;
        cin.ignore();

        if (menuUtama == 1) subMenu(rootBST, id, false);
        else if (menuUtama == 2) subMenu(rootAVL, id, true);

    } while (menuUtama != 3);

    return 0;
}