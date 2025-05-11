#pragma once
#include "MY_STL.h"
#include "pair.h"
namespace MY_STL{
    enum Node_Color{ Red,Black };
    template<class K,class V>
    class RBTreeNode{
        using value_type=m_pair<K,v>;
        using Self=RBTreeNode<K,V>;
        value_type _kv;
        Node_olor _color;
        Self* _parent;
        Self* _left;
        Self* _right;
        RBTreeNode(const value_type& kv=value_type()):_kv(kv),_color(Red),_parent(nullptr),_left(nullptr),_right(nullptr){}
    };
    template<class K,class V>
    class RBTree{
        using value_type=m_pair<K,V>;
        using Node=RBTreeNode<K,V>;
        using Self=RBTreeNode<K,V>;
        using N_ptr=Node*;
        using N_ref=Node&;
        public:
        RBTree():_root(nullptr),_size(0){}
        //高度
        size_t height(N_ptr root)const{
            if(root==nullptr)
                return 0;
            return 1+max(height(root->_left),height(root->_right));
        }
    };
}