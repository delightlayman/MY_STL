#pragma once

#include <functional>
#include <memory>

namespace mystl {

template<typename T, typename Compare = std::less<T>>
class set {
private:
    struct Node {
        T value;
        Node* left;
        Node* right;
        Node* parent;
        Node(const T& val) : value(val), left(nullptr), right(nullptr), parent(nullptr) {}
    };

    Node* root;
    size_t count;
    Compare comp;

public:
    // Constructor
    set() : root(nullptr), count(0) {}

    // Destructor
    ~set() {
        clear();
    }

    // Insert element
    bool insert(const T& value) {
        if (!root) {
            root = new Node(value);
            count++;
            return true;
        }

        Node* current = root;
        Node* parent = nullptr;

        while (current) {
            if (comp(value, current->value)) {
                parent = current;
                current = current->left;
            }
            else if (comp(current->value, value)) {
                parent = current;
                current = current->right;
            }
            else {
                return false; // Element already exists
            }
        }

        Node* newNode = new Node(value);
        newNode->parent = parent;

        if (comp(value, parent->value)) {
            parent->left = newNode;
        } else {
            parent->right = newNode;
        }

        count++;
        return true;
    }

    // Find element
    bool find(const T& value) const {
        Node* current = root;
        
        while (current) {
            if (comp(value, current->value)) {
                current = current->left;
            }
            else if (comp(current->value, value)) {
                current = current->right;
            }
            else {
                return true;
            }
        }
        return false;
    }

    // Get size
    size_t size() const {
        return count;
    }

    // Clear the set
    void clear() {
        clearRecursive(root);
        root = nullptr;
        count = 0;
    }

private:
    void clearRecursive(Node* node) {
        if (node) {
            clearRecursive(node->left);
            clearRecursive(node->right);
            delete node;
        }
    }
};

} // namespace mystl
