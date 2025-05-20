#pragma once
#include "MY_STL.h"
//Binary Search Tree
//key模型：参数仅有Key，由于搜索查找
//key/value模型：参数有Key和Value，由于查找和计数
//注意：key不可修改，value可修改
namespace MY_STL{
    template <class K,class V=int>
    struct BSTNode {
        K _key;//关键字---实际为某一类值，用作标记
        V _val;
        BSTNode<K>* _left;
        BSTNode<K>* _right;

        BSTNode(const K& key = K(),const V& val=V()) : _key(key),_val(val), _left(nullptr), _right(nullptr) {}
    };
    template <class K,class V=int>
    class BSTree {
        public:
        using Node = BSTNode<K,V>;
        using Self = BSTree<K,V>;
        using N_ptr= Node*;
        using N_ref= Node&;
        //constructor
        BSTree() :_root(nullptr) {}
        // BSTNode(const Self& bstree) { }
        //destructor
        ~BSTree() {

        }
        //递归，需要有一个递推的参数，则不能只用this指针
        //insert---bool值检查是否插入成功
        bool insert(const K& key,const V& val) {
            Node* newNode = new Node(key,val);
            if (_root == nullptr) {
                _root = newNode;
                return true;
            }
            //BST非空，则找空位插入
            Node* parent = nullptr;
            Node* cur = _root;
            while (cur) {
                if (key < cur->_key) {
                    parent = cur;
                    cur = cur->_left;
                }
                else if (key > cur->_key) {
                    parent = cur;
                    cur = cur->_right;
                }
                else {//相等，无法插入
                    delete newNode;
                    return false;
                }
            }
            if (key < parent->_key) {
                parent->_left = newNode;
            }
            else {
                parent->_right = newNode;
            }
            return true;
        }
        //插入并保留bstree---须深拷贝
        // bool insert(const Self& bstree) {}
        //erase---bool值检查是否删除成功
        //三种情况合为两种：
        //1.无子树或单子树 删除并把后续接入到父节点上
        //2.双子树 
        //a.寻找一个中间key：左子树最大值或右子树最小值，替换将删除的key
        //b.直接把子树I接入到子树II的某一个节点上
        bool erase(const K& key) {
            if (_root == nullptr) {
                cout << "empty tree" << endl;
                return false;
            }
            Node* parent = nullptr;
            Node* cur = _root;
            //来到删除节点处
            while (cur) {
                if (key < cur->_key) {
                    parent = cur;
                    cur = cur->_left;
                }
                else if (key > cur->_key) {
                    parent = cur;
                    cur = cur->_right;
                }
                else {
                    break;
                }
            }
            if (cur == nullptr) {
                cout << "not found" << endl;
                return false;
            }
            else {
                if (!cur->_left) {
                    //cur为root
                    if (cur == _root) {
                        _root = cur->_right;
                    }else{
                        if (cur == parent->_left)
                            parent->_left = cur->_left;
                        else
                            parent->_right = cur->_left;
                    }
                    delete cur;
                }
                else if (!cur->_right) {
                    if(cur==_root){
                        _root = cur->_left;
                    }else{
                        if (cur == parent->_left)
                            parent->_left = cur->_right;
                        else
                            parent->_right = cur->_right;
                    }
                    delete cur;
                }
                else {
                    //本质：用 中序遍历的 前驱或后继节点替换cur
                    //用右子树的最小值---最左节点替换cur
                    //case1：最左节点无子树
                    //case2：最左节点有右子树
                    Node* min_parent = cur;
                    Node* min = cur-> _right;
                    while (min->_left) {
                        min_parent=min;
                        min = min->_left;
                    }
                    cur->_key=min->_key;
                    if(min==min_parent->_right) 
                        min_parent->_right = min->_right;
                    else 
                        min_parent->_left = min->_right;
                    delete min;
                    min = nullptr;
                     
                }

            }
            return true;
        }
        //find---是否找到
        Node* find(const K& key) {
            if (_root == nullptr) {
                cout << "empty tree" << endl;
                return nullptr;
            }
            Node* cur = _root;
            while (cur) {
                if (key < cur->_key) {
                    cur = cur->_left;
                }
                else if (key > cur->_key) {
                    cur = cur->_right;
                }
                else {
                    return cur;
                }
            }
            return nullptr;
        }
        //clear---清空树
        void clear(N_ptr root){
            if(root==nullptr)
                return;
            else{
                clear(root->_left);
                clear(root->_right);
                delete root;
                root = nullptr;
            }    
        }
        //去右边
        N_ptr& to_right(N_ptr& cur) {
            return cur = cur->_right;
        }
        //去左边
        N_ptr& to_left(N_ptr& cur) {
            return cur = cur->_left;
        }
        //root
        Node* root() {
            return _root;
        }
        //frontorder traverse
        //inorder traverse
        void inorder(const Node* root) {
            if(root==nullptr)
                return;
            inorder(root->_left);
            cout << root->_key << ":"<< root->_val <<" ";
            inorder(root->_right);
        }
        //postorder traverse
        //levelorder traverse

        private:
            Node* _root;
    };
}
