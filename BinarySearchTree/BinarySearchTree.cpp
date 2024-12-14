#include <iostream>
#include <queue>
#include <vector>

// Public Node struct
template<typename T>
struct Node {
    T data;
    Node<T>* left;
    Node<T>* right;

    Node(const T& value) : data(value), left(nullptr), right(nullptr) {}
};  

template<typename T>
class BinarySearchTree {
private:
    Node<T>* root;

    void destroyTree(Node<T>* node) {
        if (node) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

    void preOrderHelper(Node<T>* node) const {
        if (node) {
            std::cout << node->data << " ";
            preOrderHelper(node->left);
            preOrderHelper(node->right);
        }
    }

    void inOrderHelper(Node<T>* node) const {
        if (node) {
            inOrderHelper(node->left);
            std::cout << node->data << " ";
            inOrderHelper(node->right);
        }
    }

    void postOrderHelper(Node<T>* node) const {
        if (node) {
            postOrderHelper(node->left);
            postOrderHelper(node->right);
            std::cout << node->data << " ";
        }
    }

    int heightHelper(Node<T>* node) const {
        if (!node) return -1;
        return 1 + std::max(heightHelper(node->left), heightHelper(node->right));
    }

    bool searchNodeHelper(Node<T>* node, const T& value) {
        if (!node) return false;
        if (value == node->data) return true;
        if (value < node->data) return searchNodeHelper(node->left, value);
        return searchNodeHelper(node->right, value);
    }

public:
    BinarySearchTree() : root(nullptr) {}

    ~BinarySearchTree() {
        destroyTree(root);
    }

    bool searchNode(const T& value) {
        return searchNodeHelper(root, value);
    }

    void insert(const T& value) {
        if (!root) {
            root = new Node<T>(value);
            return;
        }

        Node<T>* current = root;
        while (true) {
            if (value < current->data) {
                if (!current->left) {
                    current->left = new Node<T>(value);
                    return;
                }
                current = current->left;
            }
            else if (value > current->data) {
                if (!current->right) {
                    current->right = new Node<T>(value);
                    return;
                }
                current = current->right;
            }
            else {
                // Duplicate value, do nothing
                return;
            }
        }
    }

    void printLevelByLevel() const {
        if (!root) {
            std::cout << "Tree is empty\n";
            return;
        }

        std::queue<Node<T>*> q;
        q.push(root);
        int level = 0;

        while (!q.empty()) {
            size_t levelSize = q.size();  // Number of nodes at current level
            std::cout << "depth " << level << ": ";

            // Process all nodes at current level
            for (int i = 0; i < levelSize; i++) {
                Node<T>* current = q.front();
                q.pop();

                std::cout << current->data;
                if (i < levelSize - 1) {
                    std::cout << " ";
                }

                if (current->left) {
                    q.push(current->left);
                }
                if (current->right) {
                    q.push(current->right);
                }
            }
            std::cout << '\n';
            level++;
        }
    }

    void preOrder() const {
        preOrderHelper(root);
        std::cout << '\n';
    }

    void inOrder() const {
        inOrderHelper(root);
        std::cout << '\n';
    }

    void postOrder() const {
        postOrderHelper(root);
        std::cout << '\n';
    }

    void levelOrder() const {
        if (!root) return;

        std::queue<Node<T>*> q;
        q.push(root);

        while (!q.empty()) {
            Node<T>* current = q.front();
            q.pop();

            std::cout << current->data << " ";

            if (current->left) q.push(current->left);
            if (current->right) q.push(current->right);
        }
        std::cout << '\n';
    }

    bool isEmpty() const {
        return root == nullptr;
    }

    int height() const {
        return heightHelper(root);
    }

    // Provide read-only access to the root node
    const Node<T>* getRoot() const {
        return root;
    }
};

// Function to check if two trees are equal in shape and structure
template<typename T>
bool areTreesEqual(const BinarySearchTree<T>& tree1, const BinarySearchTree<T>& tree2) {
    return areTreesEqualHelper(tree1.getRoot(), tree2.getRoot());
}

// Helper function to recursively compare nodes
template<typename T>
bool areTreesEqualHelper(const Node<T>* node1, const Node<T>* node2) {
    if (!node1 && !node2) return true;  // Both nodes are null, trees are equal so far
    if (!node1 || !node2) return false;  // One node is null, the other is not, trees are not equal
    if (node1->data != node2->data) return false;  // Node values are different, trees are not equal

    // Recursively check left and right subtrees
    return areTreesEqualHelper(node1->left, node2->left) && areTreesEqualHelper(node1->right, node2->right);
}

int main() {
    BinarySearchTree<int> tree1;

    // Creating a sample tree
    //       8
    //     /    \
    //   5      10
    //  / \     /
    // 1   6  9
    //

    tree1.insert(8);    // depth 0
    tree1.insert(5);    // depth 1
    tree1.insert(10);   // depth 1
    tree1.insert(1);    // depth 2
    tree1.insert(6);    // depth 2
    tree1.insert(9);    // depth 2

    BinarySearchTree<int> tree2;
    // Creating a sample tree
    //       8
    //     /    \
    //   5      10
    //  / \     /
    // 1   6  9
    //
    tree2.insert(8);    // depth 0
    tree2.insert(5);    // depth 1
    tree2.insert(10);   // depth 1
    tree2.insert(1);    // depth 2
    tree2.insert(6);    // depth 2
    tree2.insert(9);    // depth 2

    BinarySearchTree<int> tree3;
    // Creating a sample tree
    //       8
    //     /    \
    //   5      10
    //  / \     /
    // 1   6  7
    //
    tree3.insert(8);    // depth 0
    tree3.insert(5);    // depth 1
    tree3.insert(10);   // depth 1
    tree3.insert(1);    // depth 2
    tree3.insert(6);    // depth 2
    tree3.insert(7);   // depth 2


    std::cout << "Tree 1 traversals:\n";
    std::cout << "Pre-order: ";
    tree1.preOrder();

    std::cout << "In-order: ";
    tree1.inOrder();

    std::cout << "Post-order: ";
    tree1.postOrder();

    std::cout << "\nTree 1: \n";
    tree1.printLevelByLevel();
    std::cout << "\nTree 2: \n";
    tree2.printLevelByLevel();
    std::cout << "\nTree 3: \n";
    tree3.printLevelByLevel();

    
    int targetValue1{ 6 };
    std::cout << "\nNode with value " << targetValue1 << (tree1.searchNode(targetValue1) ? " in Tree 1 found.\n" : " in Tree 1 not found.\n");
    int targetValue2{ 13 };
    std::cout << "\nNode with value " << targetValue2 << (tree2.searchNode(targetValue2) ? " in Tree 2 found.\n" : " in Tree 2 not found.\n");

    std::cout << "\nAre tree1 and tree2 equal? " << (areTreesEqual(tree1, tree2) ? "Yes" : "No") << '\n';
    std::cout << "Are tree1 and tree3 equal? " << (areTreesEqual(tree1, tree3) ? "Yes" : "No") << '\n';

    return 0;
}