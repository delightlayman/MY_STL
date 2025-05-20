#pragma once
#include "MY_STL.h"
#include "pair.h"

//pair
using MY_STL::m_pair;
using MY_STL::make_m_pair;

//RBSTree的五个条件
//1.节点非红即黑
//2.根节点为黑
//3.子NULL节点为黑
//4.红节点的子节点为黑
//5.对于节点到其所有子NULL的路径---黑节点数相同
namespace MY_STL{

    enum Node_Color{ Red,Black };
    //存储键值对<key,val>
    //set为<key,key>---key即是val，故只需存储key值
    //map为<key,val>---存储为pair<key,val>
    template<class T>
    struct RBTreeNode{
        using Self=RBTreeNode<T>;
        T _t;
        Node_Color _color;
        Self* _parent;
        Self* _left;
        Self* _right;
        RBTreeNode(const T& t=T()):_t(t),_color(Red),_parent(nullptr),_left(nullptr),_right(nullptr){}
        RBTreeNode(const Self& n):_t(n._t),_color(n._color),_parent(nullptr),_left(nullptr),_right(nullptr){}
        //Self& operator=(const Self& n) {
        //    if (this != &n) {
        //        _t = n._t;
        //        _color = n._color;
        //        _parent = n._parent;
        //        _left = n._left;
        //        _right = n._right;
        //        return *this;
        //    }
        //}
    };

    template<class T,class Ref,class Ptr>
    struct RBT_iterator{
        using Node=RBTreeNode<T>;
        using N_ptr=Node*;
        //data members
        N_ptr _pnode;

        using iterator=RBT_iterator<T,T&,T*>;
        using const_iterator=RBT_iterator<T,const T&,const T*>;
        using Self=RBT_iterator<T,Ref,Ptr>;

        //constructor
        RBT_iterator():_pnode(nullptr){}
        RBT_iterator(const N_ptr pn):_pnode(pn){}
        //iterator==>const_iterator,const_iterator!=>iterator
        RBT_iterator(const iterator& it):_pnode(it._pnode){}

        Ref operator*(){ return _pnode->_t;}  
        Ptr operator->(){return &(_pnode->_t);}


        //基于中序遍历------iterator前往前驱---顺序：右根左
        void to_front(){
            if(_pnode->_left){  //左子节点非空
                _pnode=_pnode->_left;
                while(_pnode->_right){
                    _pnode=_pnode->_right;
                }
            }else{
                N_ptr parent=_pnode->_parent;
                while(parent!=nullptr&&parent->_right!=_pnode){
                    _pnode=parent;
                    parent=_pnode->_parent;
                }
                _pnode=parent;
            }
        }

        //基于中序遍历------iterator前往后继---顺序：左根右
        void to_back(){
            if(_pnode->_right){    //右子节点非空
                _pnode=_pnode->_right;
                while(_pnode->_left){
                    _pnode=_pnode->_left;
                }
            }else{  //右子节点为空
                N_ptr parent=_pnode->_parent;
                while(parent!=nullptr&&parent->_left!=_pnode){
                    _pnode=parent;
                    parent=_pnode->_parent;
                }
                //parent为空：1.pn为根节点 2.pn在最右，循环到根节点
                //parent非空：pn在任意左子树，parent必然非空
                _pnode=parent;
            }
        }

        //++it
        Self& operator++(){
            to_back();
            return *this;
        }
        //it++
        Self& operator++(int){
            N_ptr tmp=_pnode;
            to_back();
            return tmp;
        }
        //--it
        Self& operator--(){
            to_front();
            return *this;
        }
        //it--
        Self& operator--(int){
            N_ptr tmp=_pnode;
            to_front();
            return tmp;
        }
        //relational operator
        bool operator==(const iterator& it)const {
            return _pnode==it._pnode;
        }
        bool operator!=(const iterator& it)const {
            return _pnode != it._pnode;
        }
    };


    //K---key
    //T---数据类型
    template<class K,class T,class KOfT,class Key_compare=less<K>>
    class RBTree_base{
        public:
        using key_type=K;
        using value_type=T;

        using Node=RBTreeNode<T>;
        using N_ptr=Node*;
        using N_ref=Node&;

        using Self=RBTree_base<K,T,KOfT,Key_compare>;
        //auxiliary function---辅助函数K_
        KOfT ext;
        Key_compare cmp;

        N_ptr leftmost(N_ptr root){
             while(root&&root->_left)
                root=root->_left;
             return root;
        }
        N_ptr rightmost(N_ptr root) {
            while (root&& root->_right)
                root = root->_right;
            return root;
        }
        //iterator
        using iterator=RBT_iterator<T,T&,T*>;
        using const_iterator=RBT_iterator<T,const T&,const T*>;

        iterator begin() {
            return leftmost(_root);
        }
        iterator end() {
            return nullptr;
        }
        const_iterator begin()const {
            return leftmost(_root);
        }
        const_iterator end()const {
            return nullptr;
        }
        //default constructor
        RBTree_base():_root(nullptr),_size(0){}
        //constructor
        //若数据较多，由于需要平衡调整，这个构造函数无法满足需求，若单独插入一个节点，不入直接insert
        //RBTree_base(const N_ptr& node = nullptr, const size_t& size = 0) : _root(node), _size(size){}
        template<class InputIterator>
        RBTree_base(InputIterator first,InputIterator last){
            while (first!=last){
                insert(*first);
                ++first;
            }
        }
        //copy constructor
        void copy_tree(N_ptr& des_root,const N_ptr& src_root){
            if(src_root==nullptr)
                return;
            des_root =new Node(*src_root);
            copy_tree(des_root->_left,src_root->_left);
            copy_tree(des_root->_right,src_root->_right);

            if(des_root->_left)
                des_root->_left->_parent= des_root;
            if(des_root->_right)
                des_root->_right->_parent= des_root;
        }
        RBTree_base(const Self& rb){
            copy_tree(_root,rb._root);
            _size=rb._size;
        }
        //operator=
        Self& operator=(const Self& rb) {
            if (this != &rb) {
                clear(_root);//清空数据
                copy_tree(_root,rb._root);
                _size = rb._size;
            }
            return *this;
        }
        //destructor
        void clear(N_ptr root){
            if(root==nullptr)
                return;
            if(root->_left)
                clear(root->_left);
            if(root->_right)
                clear(root->_right);
            delete root;
            root=nullptr;
        }
        ~RBTree_base(){
            clear(_root);
            _size = 0;
        }
        //rotate
        //rotate left
        void rotate_L(N_ptr parent){
            N_ptr gp=parent->_parent;
            N_ptr son_r=parent->_right;//右子节点
            N_ptr son_rl=son_r->_left;//右子节点的左子节点
            //gp & son_r
            if(gp==nullptr){
                son_r->_parent=nullptr;
                _root=son_r;
            }
            else{
                son_r->_parent=gp;
                if(gp->_left==parent)
                    gp->_left=son_r;
                else
                    gp->_right=son_r;
            }
            //parent & son_rl
            parent->_right=son_rl;
            if(son_rl!=nullptr)
                son_rl->_parent=parent;
            //son_r & parent
            son_r->_left=parent;
            parent->_parent=son_r;

            //update color
            ::swap(parent->_color,son_r->_color);
        }
        //rotate right
        void rotate_R(N_ptr parent){
            N_ptr gp=parent->_parent;
            N_ptr son_l=parent->_left;//左子节点
            N_ptr son_lr=son_l->_right;//左子节点的右子节点
            //gp & son_l
            if(gp==nullptr){
                son_l->_parent=nullptr;
                _root=son_l;
            }
            else{
                son_l->_parent=gp;
                if(gp->_left==parent)
                    gp->_left=son_l;
                else
                    gp->_right=son_l;
            }
            //parent & son_lr
            parent->_left=son_lr;
            if(son_lr!=nullptr)
                son_lr->_parent=parent;
            //son_l & parent
            son_l->_right=parent;
            parent->_parent=son_l;
            //update color
            ::swap(parent->_color,son_l->_color); 
        }
        //rotate left_right
        void rotate_LR(N_ptr parent){
            N_ptr son_l=parent->_left;//左子节点
            N_ptr son_lr=son_l->_right;//左子节点的右子节点
            
            rotate_L(son_l);
            rotate_R(parent);
        }
        //rotate right_left
        void rotate_RL(N_ptr parent){
            N_ptr son_r=parent->_right;//右子节点
            N_ptr son_rl=son_r->_left;//右子节点的左子节点
            
            rotate_R(son_r);
            rotate_L(parent);
        }
        //add
        //按BST插入---返回newnode,且不做颜色调整
        m_pair<iterator,bool> BST_add(const value_type& t){
            N_ptr newNode=new Node(t);
            N_ptr parent=nullptr;
            N_ptr cur=_root;
            if(_root==nullptr){
                _root=newNode;
                _size++;//更新大小
                return m_pair(iterator(newNode),true);
            }
            else{
                while(cur){
                    if(cmp(ext(t),ext(cur->_t))){//提取key后---t中key小
                        parent=cur;
                        cur=cur->_left;
                    }
                    else if(cmp(ext(cur->_t),ext(t))){//提取key后---cur->_kv中key小
                        parent=cur;
                        cur=cur->_right;
                    }
                    else{
                        delete newNode;
                        return m_pair(iterator(cur),false);//相等，无法插入,返回相等位置
                    }
                }
            }
            if(cmp(ext(newNode->_t),ext(parent->_t)))
                parent->_left=newNode;
            else
                parent->_right=newNode;
            _size++;//更新大小
            newNode->_parent=parent;//更新父节点
            return m_pair(iterator(newNode),true);
        }
        void balance_add(N_ptr newnode){
            if(newnode!=_root){
                N_ptr parent=newnode->_parent;
                if(parent->_color==Black)//case1:新增节点为 黑节点 的子节点---包括根节点情况
                    return;
                while(parent!=nullptr&&parent->_color==Red){//父节点存在且为红，此时gp一定存在
                    N_ptr gp=parent->_parent;//祖父节点
                    
                    if(gp->_left==parent){
                        N_ptr uncle=gp->_right;//叔节点
                        if(uncle!=nullptr&&uncle->_color==Red){//case2:叔节点为红色
                            parent->_color=Black;
                            uncle->_color=Black;
                            gp->_color=Red;
                            //更新cur，parent，继续向上调整
                            newnode=gp;
                            parent=newnode->_parent;
                        }
                        else{//case3:uncle不存在或为黑
                            if(parent->_left==newnode)//cur为左子节点
                                rotate_R(gp);
                            else//cur为右子节点
                                rotate_LR(gp);
                            break;
                        }
                    }
                    else{
                        N_ptr uncle=gp->_left;//叔节点
                        if(uncle!=nullptr&&uncle->_color==Red){//case2:叔节点为红色
                            parent->_color=Black;
                            uncle->_color=Black;
                            gp->_color=Red;
                            //更新cur，parent，继续向上调整
                            newnode=gp;
                            parent=newnode->_parent;
                        }
                        else{//case3:uncle不存在或为黑
                            if(parent->_right==newnode)//cur为右子节点
                                rotate_L(gp);
                            else//cur为左子节点
                                rotate_RL(gp);
                            break;
                        }
                    }
                }
            }
            _root->_color=Black;//根节点为黑色---包括newnode为根节点情况
        }
        m_pair<iterator,bool> insert(const value_type& t){
            m_pair<iterator,bool> cur=BST_add(t);
            if(cur._second==true)//cur为相等位置
                balance_add(cur._first._pnode);
            return cur;
        }

        template<class InputIterator>
        void insert(InputIterator first, InputIterator last) {
            while (first != last) {
                insert(*first);
                ++first;
            }
        }
        //delete
        void adjust_delete_node(N_ptr& d_node){
            //双子节点调整---删除节点替换为后继节点
            //调整后，子节点数为1或0
            if(d_node->_left&&d_node->_right){
                N_ptr substitute=d_node->_right;
                while(substitute->_left)
                    substitute=substitute->_left;
                d_node->_t=substitute->_t;//改变当前删除节点的值
                d_node=substitute;//删除节点改为替代节点
            }
            //双子节点调整后---进行黑子节点调整
            //黑节点调整----若有son，则son必为红且无子节点,则删除节点替换为son，即转换为删除红节点
            if(d_node->_color==Black){
                if(d_node->_right!=nullptr){
                    N_ptr child=d_node->_right;
                    d_node->_t=child->_t;//改变当前删除节点的值
                    d_node=child;//删除节点改为子节点
                }
                else if(d_node->_left!=nullptr){
                    N_ptr child=d_node->_left;
                    d_node->_t=child->_t;//改变当前删除节点的值
                    d_node=child;//删除节点改为子节点
                }
            }
        }
        //删除红色节点---不会破坏红黑树性质
        //红色节点---非根节点
        void delete_Red(N_ptr d_node){
            N_ptr parent=d_node->_parent;
            if(d_node->_left==nullptr){
                if(parent->_left==d_node)
                    parent->_left=d_node->_right;
                else
                    parent->_right=d_node->_right;
                if(d_node->_right)
                    d_node->_right->_parent=parent;//更新父节点
            }
            else if(d_node->_right==nullptr){
                if(parent->_left==d_node)
                    parent->_left=d_node->_left;
                else
                    parent->_right=d_node->_left;
                if(d_node->_left)
                    d_node->_left->_parent=parent;//更新父节点
            }
            delete d_node;
            --_size;//更新大小
        }
        //删除黑色节点---破坏红黑树性质,须调整
        //仅针对无子黑节点的情况
        void delete_Black(N_ptr d_node){
            
            if (d_node == _root) {//删除节点为根节点
                delete _root;
                _root = nullptr;
                _size = 0;
                return;
            }

            N_ptr parent = d_node->_parent;//父节点
            N_ptr cur = d_node;//用于向上更新
            //sib 兄弟姐妹节点，由RBSTree树的性质，此节点必然存在，颜色不定
            N_ptr sib = nullptr;
            //循环中的d_node依然为黑色
            while (cur != _root) {
                if (parent->_left == cur) {
                    sib = parent->_right;
                    if (sib->_color == Red) {//case1：sib为红，此时必有两个黑子节点
                        rotate_L(parent);
                        //把变色留在下一循环
                    }
                    else {//sib->_cloor==Black
                        if (sib->_right != nullptr && sib->_right->_color == Red) {//case2:sib右子节点存在且为红
                            rotate_L(parent);
                            sib->_right->_color = Black;//此处为sib_son颜色
                            break;
                        }
                        else if (sib->_left != nullptr && sib->_left->_color == Red) {//case3:sib左子节点存在且为红
                            rotate_RL(parent);
                            sib->_color = Black;//注意此处为sib颜色
                            break;
                        }
                        else {// sib无子节点或双黑子节点
                            sib->_color = Red;
                            if (parent->_color == Red) {//case4：父节点为红
                                parent->_color = Black;
                                break;
                            }
                            else {//case5：父节点为黑
                                //向上更新
                                cur = parent;
                                parent = cur->_parent;
                            }
                        }
                    }
                }
                else {
                    sib = parent->_left;
                    if (sib->_color == Red)//case1：sib为红，此时必有两个黑子节点
                        rotate_R(parent);
                    else {//sib->_cloor==Black  
                        if (sib->_left != nullptr && sib->_left->_color == Red) {//case1:sib左子节点存在且为红
                            rotate_R(parent);
                            sib->_left->_color = Black;//此处为sib_son颜色
                            break;
                        }
                        else if (sib->_right != nullptr && sib->_right->_color == Red) {//case3:sib右子节点存在且为红
                            rotate_LR(parent);
                            sib->_color = Black;//注意此处为sib颜色
                            break;
                        }
                        else {// sib无子节点或双黑子节点
                            sib->_color = Red;
                            if (parent->_color == Red) {//case4：父节点为红
                                parent->_color = Black;
                                break;
                            }
                            else {//case5：父节点为黑
                                //向上更新
                                cur = parent;
                                parent = cur->_parent;
                            }
                        }
                    }
                }
            }

            parent=d_node->_parent;
            if (parent != nullptr) {//父节点非空，则更新父节点中d_node所在位置
                if(parent->_left==d_node)
                    parent->_left=nullptr;
                else
                    parent->_right=nullptr;
            }
            delete d_node;//删除节点
            --_size;//更新大小
        }
        bool erase(const key_type& k){
            iterator it=find(k);
            N_ptr d_node=it._pnode;
            if(d_node==nullptr)
                return false;
            else
                adjust_delete_node(d_node);

            if(d_node->_color==Red)
                delete_Red(d_node);
            else
                delete_Black(d_node);
            return true;
        }
        //find
        iterator find(const key_type& k){
            if(_root==nullptr)
                return nullptr;
            N_ptr cur=_root;
            while(cur){
                if(cmp(k,ext(cur->_t)))
                    cur=cur->_left;
                else if(cmp(ext(cur->_t),k))
                    cur=cur->_right;
                else
                    return cur;
            }
            return nullptr;
        }
        const_iterator find(const key_type& k)const{
            if(_root==nullptr)
                return nullptr;
            N_ptr cur=_root;
            while(cur){
                if(cmp(k,ext(cur->_t)))
                    cur=cur->_left;
                else if(cmp(ext(cur->_t),k))
                    cur=cur->_right;
                else
                    return cur;
            }
            return nullptr;
        }
        //modify
        void swap(Self& rbt) {
            ::swap(_root, rbt._root);
            ::swap(_size, rbt._size);
        }
        //traverse
        //inorder traverse
        void inorder(const N_ptr& root)const{
            if(root==nullptr)
                return;
            inorder(root->_left);
            cout<<ext(root->_t)<<":"<<root->_color<<endl;
            inorder(root->_right);
        }
        //重载inorder 无参数版本
        void inorder()const {
            inorder(_root);
        }
        //preorder traverse
        //postorder traverse

        //root
        N_ptr root(){
            return _root;
        }
        //size
        size_t size(){
            return _size;
        }        
        private:
            N_ptr _root;
            size_t _size;
    };
}