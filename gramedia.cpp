#include <iostream>
using namespace std;

struct Node{
    string judulbuku;
    int ID;
    Node* left;
    Node* right;
}

Node *createNode(int ID, string judulbuku)
{
    Node* newNode = new Node();
    newNode->ID = ID;
    newNode->left = newNode->right = nullptr;
    return newNode;
}

Node *insertNode(Node* root, int ID, string judulbuku)
{
    if (root == nullptr){
        return createNode(ID, judulbuku);
    }
    if (ID < root->ID){
        root->left = insertNode(root->left, ID, judulbuku);
    }
    else if (ID > root->ID){
        root->right = insertNode(root->right, ID, judulbuku);
    }
    return root;
}