#include <iostream>
using namespace std;

class Node {
public:
    int key;
    Node* left;
    Node* right;

    Node(int value) {
        key = value;
        left = right = NULL;
    }
};

class BST {
private:
    Node* root;

    Node* insert(Node* node, int key) {
        if (node == NULL)
            return new Node(key);

        if (key < node->key)
            node->left = insert(node->left, key);
        else if (key > node->key)
            node->right = insert(node->right, key);

        return node;
    }

    bool search(Node* node, int key) {
        if (node == NULL)
            return false;

        if (node->key == key)
            return true;

        if (key < node->key)
            return search(node->left, key);

        return search(node->right, key);
    }

    Node* findMinNode(Node* node) {
        while (node->left != NULL)
            node = node->left;
        return node;
    }

    Node* deleteNode(Node* node, int key) {

        if (node == NULL)
            return NULL;

        if (key < node->key)
            node->left = deleteNode(node->left, key);

        else if (key > node->key)
            node->right = deleteNode(node->right, key);

        else {

            // Case 1: Leaf
            if (node->left == NULL && node->right == NULL) {
                delete node;
                return NULL;
            }

            // Case 2: One Child
            else if (node->left == NULL) {
                Node* temp = node->right;
                delete node;
                return temp;
            }

            else if (node->right == NULL) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            // Case 3: Two Children
            else {
                Node* temp = findMinNode(node->right);
                node->key = temp->key;
                node->right = deleteNode(node->right, temp->key);
            }
        }

        return node;
    }

    int height(Node* node) {

        if (node == NULL)
            return -1;

        int leftHeight = height(node->left);
        int rightHeight = height(node->right);

        return max(leftHeight, rightHeight) + 1;
    }

    void inorder(Node* node) {

        if (node == NULL)
            return;

        inorder(node->left);
        cout << node->key << " ";
        inorder(node->right);
    }

public:

    BST() {
        root = NULL;
    }

    void insert(int key) {
        root = insert(root, key);
    }

    bool search(int key) {
        return search(root, key);
    }

    void deleteKey(int key) {
        root = deleteNode(root, key);
    }

    int findMin() {

        if (root == NULL)
            return -1;

        Node* temp = root;

        while (temp->left != NULL)
            temp = temp->left;

        return temp->key;
    }

    int findMax() {

        if (root == NULL)
            return -1;

        Node* temp = root;

        while (temp->right != NULL)
            temp = temp->right;

        return temp->key;
    }

    int height() {
        return height(root);
    }

    void inorderTraversal() {
        inorder(root);
        cout << endl;
    }

    int inorderSuccessor(int key) {

        Node* current = root;

        while (current != NULL && current->key != key) {

            if (key < current->key)
                current = current->left;
            else
                current = current->right;
        }

        if (current == NULL)
            return -1;

        if (current->right != NULL)
            return findMinNode(current->right)->key;

        Node* successor = NULL;
        Node* ancestor = root;

        while (ancestor != current) {

            if (key < ancestor->key) {
                successor = ancestor;
                ancestor = ancestor->left;
            }
            else {
                ancestor = ancestor->right;
            }
        }

        if (successor == NULL)
            return -1;

        return successor->key;
    }
};

int main() {

    BST tree;

    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);
    tree.insert(25);

    cout << "Inorder Traversal: ";
    tree.inorderTraversal();

    cout << "Minimum: " << tree.findMin() << endl;
    cout << "Maximum: " << tree.findMax() << endl;
    cout << "Height: " << tree.height() << endl;

    cout << "Search 30: ";

    if (tree.search(30))
        cout << "Found\n";
    else
        cout << "Not Found\n";

    cout << "Inorder Successor of 25: ";
    cout << tree.inorderSuccessor(25) << endl;

    tree.deleteKey(30);

    cout << "After deleting 30:\n";
    tree.inorderTraversal();

    return 0;
}
