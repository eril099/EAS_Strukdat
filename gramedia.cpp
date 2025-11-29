#include <iostream>
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

    // cout << balance << endl;
    // cout << root->height <<"-" << root->judulbuku << endl;

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
    cout << getbalance(root) << "=";
    cout << root->height << "\t";
    cout << root->ID << "\t";
    cout << root->judulbuku << "\t";
    cout << root->penulis << "\t";
    cout << root->kategori << endl;

    tampil(root->right, ++step);
}

int main()
{
    Node *root = nullptr;

    root = insertNode(root, 10, "One Piece Volume 32", "Eril", "Manga");
    root = insertNode(root, 20, "Cinta ini membunuhku", "Bozu", "Novel");
    root = insertNode(root, 30, "Resep Dapur Ibu", "Erad", "Resep Masakan");
    root = insertNode(root, 40, "Life is like a dih", "Bagas", "Motivasi");
    root = insertNode(root, 50, "5 menit paham rotasi jungle", "Impi", "Pelajaran");
    tampil(root);
    // cout << endl;
    // root = deleteNode(root, 40);
    // tampil(root);
}