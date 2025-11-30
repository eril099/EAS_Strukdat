#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

struct Node
{
    string judulbuku, penulis, kategori;
    int ID;
    Node *left;
    Node *right;
    int height;
};

Node *createNode(int ID, string judulbuku, string penulis, string kategori)
{
    Node *newNode = new Node();
    newNode->ID = ID;
    newNode->judulbuku = judulbuku;
    newNode->penulis = penulis;
    newNode->kategori = kategori;
    newNode->left = newNode->right = nullptr;
    newNode->height = 1;
    return newNode;
}


int height(Node *N){
    if(N == nullptr){
        return 0;
    }
    return N->height;
}

int getbalance(Node *N){
    if(N == nullptr){
        return 0;
    }
    return height(N->left) - height(N->right);
}

void updateHeight(Node *N){
    N->height = 1 + max(height(N->left), height(N->right));
}

Node * rotateleft(Node *N){
    Node *temp = N->right;
    Node *empty = temp->left;

    temp->left = N;
    N->right = empty;

    updateHeight(N);
    updateHeight(temp);

    return temp;
}

Node * rotateright(Node *N){
    Node *temp = N->left;
    Node *empty = temp->right;

    temp->right = N;
    N->left = empty;

    updateHeight(N);
    updateHeight(temp);

    return temp;
}


Node *insertNode(Node *root, int ID, string judulbuku, string penulis, string kategori)
{
    if (root == nullptr)
    {
        return createNode(ID, judulbuku, penulis, kategori);
    }
    if (ID < root->ID)
    {
        root->left = insertNode(root->left, ID, judulbuku, penulis, kategori);
    }
    else if (ID > root->ID)
    {
        root->right = insertNode(root->right, ID, judulbuku, penulis, kategori);
    }
    updateHeight(root);
    int balance = getbalance(root);

    if(balance < -1 && ID > root->right->ID){
        return rotateleft(root);
    }
    else if(balance > 1 && ID < root->left->ID){
        return rotateright(root);
    }
    else if(balance < -1 && ID < root->right->ID){
        root->right = rotateright(root->right);
        return rotateleft(root);
    }
    else if(balance > 1 && ID > root->left->ID){
        root->left = rotateleft(root->left);
        return rotateright(root);
    }

    return root;
}


Node *searchNode(Node *root, int key)
{
    if (root == nullptr || root->ID == key)
    {
        return root;
    }
    if (root->ID < key)
    {
        return searchNode(root->right, key);
    }
    return searchNode(root->left, key);
}

Node *minValue(Node *node)
{
    while(node->left != nullptr)
    {
        node = node->left;
    }
    return node;
}

Node *deleteNode(Node *root, int ID)
{
    if (root == nullptr)
        return root;

    else if (ID < root->ID)
    {
        root->left = deleteNode(root->left, ID);
    }
    else if (ID > root->ID)
    {
        root->right = deleteNode(root->right, ID);
    }
    else
    {
        if (root->left == nullptr)
        {
            Node *temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == nullptr)
        {
            Node *temp = root->left;
            delete root;
            return temp;
        }
        Node *temp = minValue(root->right);
        root->ID = temp->ID;
        root->judulbuku = temp->judulbuku;
        root->penulis = temp->penulis;
        root->kategori = temp->kategori;
        root->right = deleteNode(root->right, temp->ID);
    }
    updateHeight(root);
    int balance = getbalance(root);

    if(balance < -1 && getbalance(root->right) < 0){
        return rotateleft(root);
    }
    else if(balance > 1 && getbalance(root->left) > 0){
        return rotateright(root);
    }
    else if(balance < -1 && getbalance(root->right) > 0){
        root->right = rotateright(root->right);
        return rotateleft(root);
    }
    else if(balance > 1 && getbalance(root->left) < 0){
        root->left = rotateleft(root->left);
        return rotateright(root);
    }
    return root;
}

Node *search(Node *root, int id){
    if(root == nullptr){
        return nullptr;
    }
    else if(id == root->ID){
        return root;
    }
    else if(id <= root->ID){
        return search(root->left, id);
    }
    else{
        return search(root->right, id);
    }
}

void tampil(Node *root, int step = 0)
{
    if (root == nullptr)
    {
        if(step == 0){
            cout << "Buku Kosong";
        }
        return;
    }

    tampil(root->left, ++step);
    // cout << getbalance(root) << "=";
    // cout << root->height << "\t";
    cout << root->ID << "\t";
    cout << root->judulbuku << "\t\t";
    cout << root->penulis << "\t";
    cout << root->kategori << endl;

    tampil(root->right, ++step);
}

void savefile(Node *root, ofstream &file){
    if(root == nullptr){
        return;
    }
    savefile(root->left, file);

    file << root->judulbuku << ";" << root->penulis << ";" << root->kategori << endl;

    savefile(root->right, file);
}

void updatefile(Node *root){
    ofstream file("data.txt", ios::trunc);
    if(file.is_open()){
        savefile(root, file);
        file.close();
    }
    else{
        cout << "Gagal Menyimpan data" << endl;
    }

}

int main()
{
    Node *root = nullptr;
    int pilihan;
    int id = 1;
    ifstream file("data.txt");
    if(!file){
        cout << "Data tidak dapat dibuka";
        return 1;
    }
    string line;
    while(getline(file, line)){
        stringstream ss(line);
        string judul, penulis, kategori;

        getline(ss, judul, ';');
        getline(ss, penulis, ';');
        getline(ss, kategori, ';');

        if(!judul.empty()){
            root = insertNode(root, id++, judul, penulis, kategori);
        }
    }
    file.close();

    do{
        cout << "===========Data Base Gramedia===========" << endl;
        cout << "1. Insert\n2. Delete\n3. Search\n4. View\n0. Keluar\nPilihan: ";
        cin >> pilihan;
        cin.ignore();

        if(pilihan == 1){
            string j, p, k;
            cout << "Masukkan Judul Buku: ";
            getline(cin, j);
            cout << "Masukkan Penulis: ";
            getline(cin, p);
            cout << "Masukkan Kategori: ";
            getline(cin, k);

            root = insertNode(root, id, j, p, k);
            cout << "Berhasil Input" << endl;
            id++;
            updatefile(root);
        }
        else if(pilihan == 2){
            int targetID;
            cout << "Masukkan ID buku yang ingin dihapus: ";
            cin >> targetID;

            if(search(root, targetID) != nullptr){
                root = deleteNode(root, targetID);
                cout << "Buku dengan id: " << targetID << " Berhasil dihapus" << endl;
                updatefile(root);
            }
            else{
                cout << "ID tidak ditemukan!" << endl;
            }
        }
        else if(pilihan == 3){
            int targetID;
            cout << "Masukkan ID yang ingin dicari: ";
            cin >> targetID;
            Node *hasil = search(root, targetID);

            if(hasil){
                cout << "===DITEMUKAN===" << endl;
                cout << "ID\t\t: " << hasil->ID << endl;
                cout << "Judul\t\t: " << hasil->judulbuku << endl;
                cout << "Penulis\t\t: " << hasil->penulis << endl;
                cout << "Kategori\t: " << hasil->kategori << endl;
            }
            else{
                cout << "Buku tidak ditemukan!" << endl;
            }
        }
        else if(pilihan == 4){
            cout << "\nData Buku di Tree:" << endl;
            cout << "ID\tInfo Buku" << endl;
            cout << "-------------------------" << endl;
            tampil(root);
        }
    } while(pilihan != 0);
    return 0;
}