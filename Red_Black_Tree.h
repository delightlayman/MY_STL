#pragma once
#include "MY_STL.h"
#include "pair.h"
//RBSTree的五个条件
//1.节点非红即黑
//2.根节点为黑
//3.子NULL节点为黑
//4.红节点的子节点为黑
//5.对于节点到其所有子NULL的路径---黑节点数相同
namespace MY_STL{
    enum Node_Color{ Red,Black };
    template<class K,class V>
    class RBTreeNode{
        using value_type=m_pair<K,v>;
        using Self=RBTreeNode<K,V>;
        value_type _kv;
        Node_Color _color;
        Self* _parent;
        Self* _left;
        Self* _right;
        RBTreeNode(const value_type& kv=value_type()):_kv(kv),_color(Red),_parent(nullptr),_left(nullptr),_right(nullptr){}
    };
    template<class K,class V>
    class RBTree{
        public:
        using value_type=m_pair<K,V>;
        using Node=RBTreeNode<K,V>;
        using N_ptr=Node*;
        using N_ref=Node&;
        //default constructor
        RBTree():_root(nullptr),_size(0){}
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
        ~RBTree(){
            clear(_root);
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
        N_ptr BST_add(const value_type& kv){
            N_ptr newNode=new Node(kv);
            N_ptr parent=nullptr;
            N_ptr cur=_root;
            if(_root==nullptr){
                _root=newNode;
                _size++;//更新大小
                return newNode;
            }
            else{
                while(cur){
                    if(kv._first<cur->_kv._first){
                        parent=cur;
                        cur=cur->_left;
                    }
                    else if(kv._first>cur->_kv._first){
                        parent=cur;
                        cur=cur->_right;
                    }
                    else{
                        delete newNode;
                        return nullptr;//相等，无法插入
                    }
                }
            }
            if(parent->_kv._first>newNode->_kv._first)
                parent->_left=newNode;
            else
                parent->_right=newNode;
            _size++;//更新大小
            newNode->_parent=parent;//更新父节点
            return newNode;
        }
        void balance_add(N_ptr newnode){
            if(newnode!=_root){
                N_ptr parent=newnode->_parent;
                if(parent->_color==Black)//case1:新增节点为 黑节点 的子节点---包括根节点情况
                    return true;
                while(parent!=nullptr||parent->_color==Red){//父节点存在且为红，此时gp一定存在
                    N_ptr gp=parent->_parent;//祖父节点
                    
                    if(gp->_left==parent){
                        N_ptr uncle=gp->_right;//叔节点
                        if(uncle!=nullptr&&uncle->_color==Red){//case2:叔节点为红色
                            parent->_color=Black;
                            uncle->_color=Black;
                            gp->__color=Red;
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
        bool insert(const value_type& kv){
            N_ptr cur=BST_add(kv);
            if(cur==nullptr)
                return false;
            balance_add(cur);
            return true;
        }
        //delete
        void adjust_delete_node(N_ptr& d_node){
            //双子节点调整---调整后，子节点数为1或0
            if(d_node->_left&&d_node->_right){
                n_ptr substitute=d_node->_right;
                while(substitute->_left)
                    substitute=substitute->_left;
                d_node->_kv=substitute->_kv;//改变当前删除节点的值
                d_node=substitute;//删除节点改为替代节点
            }
            // //黑节点调整----若有son，则son必为红且无子节点,则删除节点改为son，即转换为删除红节点
            if(d_node->_color==Black){
                if(d_node->_right!=nullptr){
                    N_ptr child=d_node->_right;
                    d_node->_kv=child->_kv;//改变当前删除节点的值
                    d_node=child;//删除节点改为子节点
                }
                else if(d_node->_left!=nullptr){
                    N_ptr child=d_node->_left;
                    d_node->_kv=child->_kv;//改变当前删除节点的值
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
                if(parebt->_left==d_node)
                    parent->_left=d_node->_left;
                else
                    parent->_right=d_node->_left;
                if(d_node->_left)
                    d_node->_left->_parent=parent;//更新父节点
            }
            delete d_node;
            d_node=nullptr;
            _size--;//更新大小
        }
        //删除黑色节点---破坏红黑树性质,须调整
        //仅针对无子黑节点的情况
        void delete_Black(N_ptr d_node){
            if(d_node==_root){
                delete _root;
                _root=nullptr;
            }else{
                N_ptr parent=d_node->_parent;//父节点
                N_ptr cur=d_node;//用于向上更新
                //sib 兄弟姐妹节点，由RBSTree树的性质，此节点必然存在，颜色不定
                N_ptr sib=nullptr;
                N_ptr sib_son=nullptr;
                //循环中的d_node依然为黑色
                while(cur&&cur!=_root){
                    if(parent->_left==cur){
                        sib=parent->_right;
                        if(sib->_color==Red){//case1：sib为红，此时必有两个黑子节点
                            rotate_L(parent);
                            //把变色留在下一循环
                        }
                        else{//sib->_cloor==Black  sib为黑，子节点若存在，必然为红
                            if(sib->_right!=nullptr){//case2:sib右子节点为红
                                sib_son=sib->_right;
                                rotate_L(parent);
                                sib_son->_color=Black;
                                break;
                            }
                            else if(sib->_left!=nullptr){//case3:sib左子节点为红
                                sib_son=sib->_left;
                                rotate_RL(parent);
                                break;
                            }
                            else{// sib无子节点
                                sib->_color=Red;
                                if(parent->_color==Red){//case4：父节点为红
                                    parent->_color=Black;
                                    break;
                                }
                                else{//case5：父节点为黑
                                    //向上更新
                                    cur=parent;
                                    parent=cur->_parent;
                                }
                            }
                        }

                    }
                    else{
                        sib=parent->_left;
                        if(sib->_color==Red)//case1：sib为红，此时必有两个黑子节点
                            rotate_R(parent);
                        else{//sib->_cloor==Black  sib为黑，子节点若存在，必然为红
                            if(sib->_left!=nullptr){//case1:sib左子节点为红
                                sib_son=sib->_left;
                                rotate_R(parent);
                                sib_son->_color=Black;
                                break;
                            }
                            else if(sib->_right!=nullptr){//case3:sib右子节点为红
                                sib_son=sib->_right;
                                rotate_LR(parent);
                                break;
                            }
                            else{// sib无子节点
                                sib->_color=Red;
                                if(parent->_color==Red){//case4：父节点为红
                                    parent->_color=Black;
                                    break;
                                }
                                else{//case5：父节点为黑
                                    //向上更新
                                    cur=parent;
                                    parent=cur->_parent;
                                }
                            }
                        }
                    }
                }
            }
        }
        bool erase(const value_type& kv){
            N_ptr d_node=find(kv);

            if(d_node==nullptr)
                return false;
            else
                adjust_delete_node(d_node);

            if(cur->_color==Red)
                delete_Red(d_node);
            else
                delete_Black(d_node);
            return true;
        }
        //find
        N_ptr find(const value_type& kv){
            if(_root==nullptr)
                return nullptr;
            N_ptr cur=_root;
            while(cur){
                if(kv._first<cur->_kv._first)
                    cur=cur->_left;
                else if(kv._first>cur->_kv._first)
                    cur=cur->_right;
                else
                    return cur;
            }
            return nullptr;
        }
        //modify
        //traverse
        //inorder traverse
        void inorder(const N_ptr& root)const{
            if(root==nullptr)
                return;
            inorder(root->_left);
            cout<<root->_kv._first<<" "<<endl;
            inorder(root->_right);
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