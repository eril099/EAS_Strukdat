#include <iostream>
using namespace std;

struct Node
{
    string judulbuku;
    int ID;
    Node *left;
    Node *right;
    int height;
};

Node *createNode(int ID, string judulbuku)
{
    Node *newNode = new Node();
    newNode->ID = ID;
    newNode->judulbuku = judulbuku;
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


Node *insertNode(Node *root, int ID, string judulbuku)
{
    if (root == nullptr)
    {
        return createNode(ID, judulbuku);
    }
    if (ID < root->ID)
    {
        root->left = insertNode(root->left, ID, judulbuku);
    }
    else if (ID > root->ID)
    {
        root->right = insertNode(root->right, ID, judulbuku);
    }
    updateHeight(root);
    int balance = getbalance(root);
    return root;
}

void inorderTraversal(Node *root)
{
    if (root != nullptr)
    {
        inorderTraversal(root->left);
        cout << root->ID << " ";
        inorderTraversal(root->right);
    }
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

Node *minValueNode(Node *node)
{
    Node *current = node;
    while (current && current->left != nullptr)
    {
        current = current->left;
    }
    return current;
}

Node *deleteNode(Node *root, int ID)
{
    if (root == nullptr)
        return root;

    if (ID < root->ID)
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
        Node *temp = minValueNode(root->right);
        root->ID - temp->ID;
        root->right = deleteNode(root->right, ID);
    }
    return root;
}

int main()
{
    Node *root = nullptr;

    root = insertNode(root, 10, "Gelo dor dor 1");
    root = insertNode(root, 20, "Gelo dor dor 2");
    root = insertNode(root, 50, "Gelo dor dor 3");
    root = insertNode(root, 40, "Gelo dor dor 4");
    root = insertNode(root, 30, "Gelo dor dor 5");
    root = insertNode(root, 60, "Gelo dor dor Limited edition");
    root = deleteNode(root, 60);

    cout << "In-order Traversal (sorted): ";
    inorderTraversal(root);
    Node *found = searchNode(root, 30);
    cout << endl
         << found->ID << " " << found->judulbuku;
    cout << endl;
}