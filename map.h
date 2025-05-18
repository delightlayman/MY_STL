#ifndef MAP_H
#define MAP_H

#include <functional>
#include <utility>
#include <memory>

namespace mystl {

enum class Color { Red, Black };

template<typename Key, typename Value>
struct MapNode {
    std::pair<const Key, Value> data;
    Color color;
    MapNode* parent;
    MapNode* left;
    MapNode* right;

    MapNode(const std::pair<const Key, Value>& d)
        : data(d), color(Color::Red), parent(nullptr), left(nullptr), right(nullptr) {}
};

template<typename Key, typename Value, typename Compare = std::less<Key>>
class map {
private:
    using Node = MapNode<Key, Value>;
    Node* root;
    size_t nodeCount;
    Compare comp;

public:
    map() : root(nullptr), nodeCount(0) {}

    // Basic operations
    std::pair<Node*, bool> insert(const std::pair<const Key, Value>& value) {
        if (!root) {
            root = new Node(value);
            root->color = Color::Black;
            nodeCount++;
            return {root, true};
        }

        Node* parent = nullptr;
        Node* current = root;
        
        while (current) {
            if (value.first == current->data.first)
                return {current, false};
                
            parent = current;
            if (comp(value.first, current->data.first))
                current = current->left;
            else
                current = current->right;
        }

        Node* newNode = new Node(value);
        newNode->parent = parent;

        if (comp(value.first, parent->data.first))
            parent->left = newNode;
        else
            parent->right = newNode;

        insertFixup(newNode);
        nodeCount++;
        return {newNode, true};
    }

    Value& operator[](const Key& key) {
        Node* node = find(key);
        if (node)
            return node->data.second;
        
        auto result = insert({key, Value()});
        return result.first->data.second;
    }

    Node* find(const Key& key) const {
        Node* current = root;
        while (current) {
            if (key == current->data.first)
                return current;
            
            if (comp(key, current->data.first))
                current = current->left;
            else
                current = current->right;
        }
        return nullptr;
    }

    size_t size() const { return nodeCount; }
    bool empty() const { return nodeCount == 0; }

private:
    void leftRotate(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        
        if (y->left)
            y->left->parent = x;
            
        y->parent = x->parent;
        
        if (!x->parent)
            root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
            
        y->left = x;
        x->parent = y;
    }

    void rightRotate(Node* y) {
        Node* x = y->left;
        y->left = x->right;
        
        if (x->right)
            x->right->parent = y;
            
        x->parent = y->parent;
        
        if (!y->parent)
            root = x;
        else if (y == y->parent->left)
            y->parent->left = x;
        else
            y->parent->right = x;
            
        x->right = y;
        y->parent = x;
    }

    void insertFixup(Node* z) {
        while (z->parent && z->parent->color == Color::Red) {
            if (z->parent == z->parent->parent->left) {
                Node* y = z->parent->parent->right;
                if (y && y->color == Color::Red) {
                    z->parent->color = Color::Black;
                    y->color = Color::Black;
                    z->parent->parent->color = Color::Red;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->right) {
                        z = z->parent;
                        leftRotate(z);
                    }
                    z->parent->color = Color::Black;
                    z->parent->parent->color = Color::Red;
                    rightRotate(z->parent->parent);
                }
            } else {
                Node* y = z->parent->parent->left;
                if (y && y->color == Color::Red) {
                    z->parent->color = Color::Black;
                    y->color = Color::Black;
                    z->parent->parent->color = Color::Red;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        rightRotate(z);
                    }
                    z->parent->color = Color::Black;
                    z->parent->parent->color = Color::Red;
                    leftRotate(z->parent->parent);
                }
            }
        }
        root->color = Color::Black;
    }

    // Add destructor and cleanup functions as needed
};

} // namespace mystl

#endif // MAP_H