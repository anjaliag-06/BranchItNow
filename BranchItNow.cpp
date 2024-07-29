#include <iostream>
#include <cmath>
#include <bits/stdc++.h>
using namespace std;

// Node structure for Binary Tree
struct Node
{
    int data;
    Node *left;
    Node *right;
    int height;
    Node(int val) : data(val), left(nullptr), right(nullptr), height(1) {}
};

// Utility function to get the height of the tree
int height(Node *N)
{
    if (N == nullptr)
        return 0;
    return N->height;
}

// Utility function to get maximum of two integers
int max(int a, int b)
{
    return (a > b) ? a : b;
}

// Class for Binary Tree Operations
class BinarySearchTree
{
public:
    Node *root;
    BinarySearchTree() : root(nullptr) {}

    virtual Node *insert(Node *node, int data);
    virtual Node *deleteNode(Node *root, int key);
    bool search(Node *root, int key);
    void inOrder(Node *node);
    void preOrder(Node *node);
    void postOrder(Node *node);
    void levelOrder(Node *root);

    int height(Node *node);
    void width(Node *node);
    int diameter(Node *root);
    void topView(Node *root);
    void bottomView(Node *root);
    void leftView(Node *root);
    void rightView(Node *root);
    void zigzagTraversal(Node *root);
    void spiralTraversal(Node *root);

    Node *getRoot() { return root; }
};

// Insert function for Binary Tree
Node *BinarySearchTree::insert(Node *node, int data)
{
    if (node == nullptr)
        return new Node(data);
    if (data < node->data)
        node->left = insert(node->left, data);
    else if (data > node->data)
        node->right = insert(node->right, data);
    return node;
}
void BinarySearchTree::width(Node *node)
{
    int max = INT_MIN;
    if (node == nullptr)
    {
        return;
    }

    queue<Node *> q;
    q.push(node);
    while (!q.empty())
    {
        int count = 0;
        for (int i = q.size() - 1; i >= 0; i--)
        {
            Node *node = q.front();
            q.pop();

            count++;
            if (node->left != nullptr)
            {
                q.push(node->left);
            }
            if (node->right != nullptr)
            {
                q.push(node->right);
            }
        }
        if (count > max)
        {
            max = count;
        }
    }
    cout <<"Width of tree : "<< max<<endl;
}
// Delete function for Binary Tree
Node *BinarySearchTree::deleteNode(Node *root, int key)
{
    if (root == nullptr)
        return root;

    if (key < root->data)
        root->left = deleteNode(root->left, key);
    else if (key > root->data)
        root->right = deleteNode(root->right, key);
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

        Node *temp = root->right;
        while (temp && temp->left != nullptr)
            temp = temp->left;

        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// Search function for Binary Tree
bool BinarySearchTree::search(Node *root, int key)
{
    if (root == nullptr)
        return false;
    if (root->data == key)
        return true;
    if (key < root->data)
        return search(root->left, key);
    return search(root->right, key);
}

// In-order traversal
void BinarySearchTree::inOrder(Node *node)
{
    if (node == nullptr)
        return;
    inOrder(node->left);
    cout << node->data << " ";
    inOrder(node->right);
}

// Pre-order traversal
void BinarySearchTree::preOrder(Node *node)
{
    if (node == nullptr)
        return;
    cout << node->data << " ";
    preOrder(node->left);
    preOrder(node->right);
}

// Post-order traversal
void BinarySearchTree::postOrder(Node *node)
{
    if (node == nullptr)
        return;
    postOrder(node->left);
    postOrder(node->right);
    cout << node->data << " ";
}

// Level-order traversal
void BinarySearchTree::levelOrder(Node *root)
{
    if (root == nullptr)
        return;
    queue<Node *> q;
    q.push(root);
    while (!q.empty())
    {
        Node *temp = q.front();
        q.pop();
        cout << temp->data << " ";
        if (temp->left != nullptr)
            q.push(temp->left);
        if (temp->right != nullptr)
            q.push(temp->right);
    }
    cout << endl;
}

// Function to find the height of the tree
int BinarySearchTree::height(Node *node)
{
    if (node == nullptr)
        return 0;
    return 1 + max(height(node->left), height(node->right));
}

// Function to find the diameter of the tree
int BinarySearchTree::diameter(Node *root)
{
    if (root == nullptr)
        return 0;
    int lHeight = height(root->left);
    int rHeight = height(root->right);

    int lDiameter = diameter(root->left);
    int rDiameter = diameter(root->right);

    return max(lHeight + rHeight + 1, max(lDiameter, rDiameter));
}

// Function to print the top view of the tree
void BinarySearchTree::topView(Node *root)
{
    if (root == nullptr)
        return;
    map<int, int> m;
    queue<pair<Node *, int>> q;
    q.push({root, 0});
    while (!q.empty())
    {
        auto p = q.front();
        q.pop();
        Node *n = p.first;
        int h = p.second;
        if (m.find(h) == m.end())
            m[h] = n->data;
        if (n->left != nullptr)
            q.push({n->left, h - 1});
        if (n->right != nullptr)
            q.push({n->right, h + 1});
    }
    for (auto it : m)
        cout << it.second << " ";
    cout << endl;
}

// Function to print the bottom view of the tree
void BinarySearchTree::bottomView(Node *root)
{
    if (root == nullptr)
        return;
    map<int, int> m;
    queue<pair<Node *, int>> q;
    q.push({root, 0});
    while (!q.empty())
    {
        auto p = q.front();
        q.pop();
        Node *n = p.first;
        int h = p.second;
        m[h] = n->data;
        if (n->left != nullptr)
            q.push({n->left, h - 1});
        if (n->right != nullptr)
            q.push({n->right, h + 1});
    }
    for (auto it : m)
        cout << it.second << " ";
    cout << endl;
}

// Function to print the left view of the tree
void BinarySearchTree::leftView(Node *root)
{
    if (root == nullptr)
        return;
    queue<Node *> q;
    q.push(root);
    while (!q.empty())
    {
        int n = q.size();
        for (int i = 1; i <= n; i++)
        {
            Node *temp = q.front();
            q.pop();
            if (i == 1)
                cout << temp->data << " ";
            if (temp->left != nullptr)
                q.push(temp->left);
            if (temp->right != nullptr)
                q.push(temp->right);
        }
    }
    cout << endl;
}

// Function to print the right view of the tree
void BinarySearchTree::rightView(Node *root)
{
    if (root == nullptr)
        return;
    queue<Node *> q;
    q.push(root);
    while (!q.empty())
    {
        int n = q.size();
        for (int i = 1; i <= n; i++)
        {
            Node *temp = q.front();
            q.pop();
            if (i == n)
                cout << temp->data << " ";
            if (temp->left != nullptr)
                q.push(temp->left);
            if (temp->right != nullptr)
                q.push(temp->right);
        }
    }
    cout << endl;
}

// Function to print zigzag traversal of the tree
void BinarySearchTree::zigzagTraversal(Node *root)
{
    if (root == nullptr)
        return;
    stack<Node *> currentLevel;
    stack<Node *> nextLevel;
    currentLevel.push(root);
    bool leftToRight = true;
    while (!currentLevel.empty())
    {
        Node *temp = currentLevel.top();
        currentLevel.pop();
        if (temp)
        {
            cout << temp->data << " ";
            if (leftToRight)
            {
                if (temp->left)
                    nextLevel.push(temp->left);
                if (temp->right)
                    nextLevel.push(temp->right);
            }
            else
            {
                if (temp->right)
                    nextLevel.push(temp->right);
                if (temp->left)
                    nextLevel.push(temp->left);
            }
        }
        if (currentLevel.empty())
        {
            leftToRight = !leftToRight;
            swap(currentLevel, nextLevel);
        }
    }
    cout << endl;
}

// Function to print spiral traversal of the tree
void BinarySearchTree::spiralTraversal(Node *root)
{
    if (root == nullptr)
        return;
    stack<Node *> s1;
    stack<Node *> s2;
    s1.push(root);
    while (!s1.empty() || !s2.empty())
    {
        while (!s1.empty())
        {
            Node *temp = s1.top();
            s1.pop();
            cout << temp->data << " ";
            if (temp->right)
                s2.push(temp->right);
            if (temp->left)
                s2.push(temp->left);
        }
        while (!s2.empty())
        {
            Node *temp = s2.top();
            s2.pop();
            cout << temp->data << " ";
            if (temp->left)
                s1.push(temp->left);
            if (temp->right)
                s1.push(temp->right);
        }
    }
    cout << endl;
}
// Class for AVL Tree (inherits BinarySearchTree)
class AVLTree : public BinarySearchTree
{
public:
    Node *insert(Node *node, int data);
    Node *deleteNode(Node *node, int data);
    int getBalance(Node *node);
    Node *rightRotate(Node *y);
    Node *leftRotate(Node *x);
};

// Right rotate utility
Node *AVLTree::rightRotate(Node *y)
{
    Node *x = y->left;
    Node *T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}


Node *AVLTree::leftRotate(Node *x)
{
    Node *y = x->right;
    Node *T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}


int AVLTree::getBalance(Node *node)
{
    if (node == nullptr)
        return 0;
    return height(node->left) - height(node->right);
}


Node *AVLTree::insert(Node *node, int data)
{
    if (node == nullptr)
        return new Node(data);
    if (data < node->data)
        node->left = insert(node->left, data);
    else if (data > node->data)
        node->right = insert(node->right, data);
    else
        return node;

    node->height = 1 + max(height(node->left), height(node->right));
    int balance = getBalance(node);

    if (balance > 1 && data < node->left->data)
        return rightRotate(node);

    if (balance < -1 && data > node->right->data)
        return leftRotate(node);

    if (balance > 1 && data > node->left->data)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && data < node->right->data)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

// Delete function for AVL Tree
Node *AVLTree::deleteNode(Node *root, int key)
{
    if (root == nullptr)
        return root;

    if (key < root->data)
        root->left = deleteNode(root->left, key);
    else if (key > root->data)
        root->right = deleteNode(root->right, key);
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

        Node *temp = root->right;
        while (temp && temp->left != nullptr)
            temp = temp->left;

        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }

    if (root == nullptr)
        return root;

    root->height = 1 + max(height(root->left), height(root->right));
    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Function Prototypes
void showMainMenu();
void showSubMenu();
void handleBST();
void handleAVLTree();

int main()
{
    int choice;
    cout<<"WELCOME TO TREE WORLD !";
    do
    {
        showMainMenu();
        cin >> choice;
        switch (choice)
        {
        case 1:
            handleBST();
            break;
        case 2:
            handleAVLTree();
            break;
        case 3:
            cout << "Exiting..." << endl;
            exit(0);
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}

// Main Menu
void showMainMenu()
{

    cout << "MENU:" << endl;
    cout<<"----------------------------------"<<endl;
    cout << "1. Binary Search Tree" << endl;
    cout << "2. AVL Tree" << endl;
    cout << "3. Exit" << endl;
    cout<<"----------------------------------"<<endl;
    cout << "Enter your choice: ";
}

// Submenu
void showSubMenu()
{
    cout << "Select operation to perform:" << endl;
    cout<<"----------------------------------"<<endl;
    cout << "1. Insert" << endl;
    cout << "2. Delete" << endl;
    cout << "3. Search" << endl;
    cout<<"----------------------------------"<<endl;
    cout<<"TRAVERSALS"<<endl;
    cout << "4. In-Order Traversal" << endl;
    cout << "5. Pre-Order Traversal" << endl;
    cout << "6. Post-Order Traversal" << endl;
    cout << "7. Level-Order Traversal" << endl;
    cout << "8. Zigzag Traversal" << endl;
    cout << "9. Spiral Traversal" << endl;
    cout<<"----------------------------------"<<endl;
    cout<<"MEASUREMENTS"<<endl;
    cout << "10. Height of Tree" << endl;
    cout << "11. Width of Tree" << endl;
    cout << "12. Diameter of Tree" << endl;
    cout<<"----------------------------------"<<endl;
    cout<<"VIEWS"<<endl;
    cout << "13. Top View" << endl;
    cout << "14. Bottom View" << endl;
    cout << "15. Left View" << endl;
    cout << "16. Right View" << endl;
    cout << "17. Return to Main Menu" << endl;
    cout<<"----------------------------------"<<endl;
    cout << "Enter your choice: ";
}

// Handle Binary Search Tree
void handleBST()
{
    BinarySearchTree bt;
    int choice, value;
    char ch='y';
    do
    {
        showSubMenu();
        cin >> choice;
        switch (choice)
        {
        case 1:
            while(ch=='y'|| ch=='Y'){
            cout << "Enter value to insert: ";
            cin >> value;
            bt.root = bt.insert(bt.getRoot(), value);
            cout<<"-------------NODE ADDED SUCCESSFULLY!-------------\n";
            cout<<"Do You Want to continue (Y/N)";
            cin>>ch;
            }
            break;
        case 2:
            cout << "Enter value to delete: ";
            cin >> value;
            bt.root = bt.deleteNode(bt.getRoot(), value);
            cout<<"-------------NODE DELETED SUCCESSFULLY!-------------\n";
            break;
        case 3:
            cout << "Enter value to search: ";
            cin >> value;
            cout << (bt.search(bt.getRoot(), value) ? "Found" : "Not Found") << endl;
            break;
        case 4:
            bt.inOrder(bt.getRoot());
            cout << endl;
            break;
        case 5:
            bt.preOrder(bt.getRoot());
            cout << endl;
            break;
        case 6:
            bt.postOrder(bt.getRoot());
            cout << endl;
            break;
        case 7:
            bt.levelOrder(bt.getRoot());
            break;
        case 8:
            bt.zigzagTraversal(bt.getRoot());
            break;
        case 9:
            bt.spiralTraversal(bt.getRoot());
            break;
        case 10:
            cout << "Height of Tree : " << bt.height(bt.getRoot()) << endl;
            break;
        case 11:
            bt.width(bt.getRoot());
            break;
        case 12:
            cout << "Diameter of Tree : " << bt.diameter(bt.getRoot()) << endl;
            break;
        case 13:
            bt.topView(bt.getRoot());
            break;
        case 14:
            bt.bottomView(bt.getRoot());
            break;
        case 15:
            bt.leftView(bt.getRoot());
            break;
        case 16:
            bt.rightView(bt.getRoot());
            break;
        case 17:
            cout << "Returning to Main Menu..." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 17);
}
// Handle AVL Tree
void handleAVLTree()
{
    AVLTree avl;
    int choice, value;
    char ch='y';
    do
    {
        showSubMenu();
        cin >> choice;
        switch (choice)
        {
        case 1:
            while(ch=='y'|| ch=='Y'){
            cout << "Enter value to insert: ";
            cin >> value;
            avl.root = avl.insert(avl.getRoot(), value);
            cout<<"-------------NODE ADDED SUCCESSFULLY!-------------\n";
            cout<<"Do You Want to continue (Y/N)";
            cin>>ch;
            }
            break;
        case 2:
            cout << "Enter value to delete: ";
            cin >> value;
            avl.root = avl.deleteNode(avl.getRoot(), value);
            cout<<"-------------NODE DELETED SUCCESSFULLY!-------------\n";
            break;
        case 3:
            cout << "Enter value to search: ";
            cin >> value;
            cout << (avl.search(avl.getRoot(), value) ? "Found" : "Not Found") << endl;
            break;
        case 4:
            avl.inOrder(avl.getRoot());
            cout << endl;
            break;
        case 5:
            avl.preOrder(avl.getRoot());
            cout << endl;
            break;
        case 6:
            avl.postOrder(avl.getRoot());
            cout << endl;
            break;
        case 7:
            avl.levelOrder(avl.getRoot());
            break;
        case 8:
            avl.zigzagTraversal(avl.getRoot());
            break;
        case 9:
            avl.spiralTraversal(avl.getRoot());
            break;
        case 10:
            cout << "Height of Tree : " << avl.height(avl.getRoot()) << endl;
            break;
        case 11:
            avl.width(avl.getRoot());
            break;
        case 12:
            cout << "Diameter of Tree : " << avl.diameter(avl.getRoot()) << endl;
            break;
        case 13:
            avl.topView(avl.getRoot());
            break;
        case 14:
            avl.bottomView(avl.getRoot());
            break;
        case 15:
            avl.leftView(avl.getRoot());
            break;
        case 16:
            avl.rightView(avl.getRoot());
            break;
        case 17:
            cout << "Returning to Main Menu..." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 17);
}