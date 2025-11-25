#include <iostream>
using namespace std;

struct Node{
    string judulbuku;
    int ID;
    Node* left;
    Node* right;
};

Node *createNode(int ID, string judulbuku)
{
    Node* newNode = new Node();
    newNode->ID = ID;
    newNode->judulbuku = judulbuku;
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

void inorderTraversal(Node* root)
{
    if (root !=nullptr){
        inorderTraversal(root->left);
        cout << root->ID, << " ";
        inorderTraversal(root->right);
    }
}
Node* searchNode(Node* root, int key)
{
    if(root == nullptr || root->ID == key){
        return root;
    }
    if (root->ID < key){
        return searchNode(root->right, key);
    }
    return searchNode(root->left, key);
}

Node* minValueNode(Node* node)
{
    Node* current = node;
    while (current && current->left != nullptr){
        current = current->left;
    }
    return current;
}

Node* deleteNode(Node* root, int ID, string judulbuku)
{
    if (root == nullptr)
    return root;

    if (ID < root->ID){
        root->left = Node deleteNode(Node* root->left, int ID, string judulbuku);
    }
    else if (ID > root->ID){
        root->right = deleteNode(root->right, ID);
    }
    else{
        if (root->left == nullptr){
            Node* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == nullptr){
            Node* temp = root->left;
            delete root;
            return temp;
        }
        Node* temp = minValueNode(root->right);
        root->ID - temp->ID;
        root->right = deleteNode(root->right, ID);
    }
    return root;
}

int main()
{
    Node* root = nullptr;

    root = insertNode(root, 10);
    root = insertNode(root, 20);
    root = insertNode(root, 30);
    root = insertNode(root, 40);
    root = insertNode(root, 50);

    cout << "In-order Traversal (sorted): ";
    inorderTraversal(root);
    cout << endl;
}