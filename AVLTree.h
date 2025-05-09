#pragma once
#include "MY_STL.h"
//AVLtree树---平衡二叉树
//平衡二叉树：任意节点的左右子树高度差不超过1的特殊搜索二叉树

namespace MY_STL{
    template<class K,class V>
    struct m_pair{
        using Self=m_pair<K,V>;
        K _first;
        V _second;
        m_pair(const K& t=K(),const V& v=V()):_first(t),_second(v){}
        m_pair(const Self& p) :_first(p._first),_second(p._second) {}
        Self& operator=(const Self& p) {
            if (this != &p) {
                _first = p._first;
                _second = p._second;
            }
            return *this;
        }
        //relational operator
    };
    template<class K,class V>
    struct AVLTreeNode{
        using value_type=m_pair<K,V>;
        value_type _kv;//关键字---实际为某一类值，用作标记
        //旋转操作需要父节点
        AVLTreeNode* _parent;
        //左右子节点
        AVLTreeNode* _left;
        AVLTreeNode* _right;
        //平衡因子 balance factor：右子树高度-左子树高度 即：bf=hr-hl ---树高度 h=max(hr,hl)+1
        //平衡因子有三种情况： 
        //case1:bf=0,左右高度相等---平衡
        //case2:bf=+-1,左右高度相差1---平衡
        //case3:bf=+-2,即bf>1或bf<-1，左右高度相差大于1---不平衡

        //新增节点其父节点平衡因子变化情况：---平衡因子：bf=hr-hl
        //case1：newnode==>左子树：若hl=hl+1,由bf=hr-hl 有bf=bf-1（--）
        //case2：newnode==>右子树：若hr=hr+1,由bf=hr-hl 有bf=bf+1（++）
        //父节点平衡因子变化的影响：
        //case1:bf=0,则前bf=+-1,即newnode插入到较低子树，从而此树高度未变，无须向上更新祖先bf
        //case2:bf=+-1，则前bf=0,无论newnode插入左/右子树，此树都会高度+1，须向上更新祖先bf
        //case3:bf=+-2,则前bf=+-1，即new插入到较高子树，从而此树出现不平衡，须旋转调整

        //删除节点其父节点平衡因子变化情况：
        //case1：左子树==>delete：若hl=hl-1,由bf=hr-hl 有bf=bf+1（++）
        //case2：右子树==>delete：若hr=hr-1,由bf=hr-hl 有bf=bf-1（--）
        //父节点平衡因子变化的影响：
        //case1:bf=0,则前bf=+-1,即delete较高子树，从而此树高度-1，须向上更新祖先bf
        //case2:bf=+-1，则前bf=0,无论delete左/右子树，此树都会高度不变，无须向上更新祖先bf
        //case3:bf=+-2,则前bf=+-1，即delete较低子树，从而此树出现不平衡，须旋转调整
        int _bf;//平衡因子
        AVLTreeNode(const value_type& kv=value_type()):_kv(kv),_parent(nullptr),_left(nullptr),_right(nullptr),_bf(0){}
    };
    template<class K,class V>
    class AVLTree{
        public:
        using value_type=m_pair<K,V>; 
        using Node=AVLTreeNode<K,V>;
        using N_ptr=Node*;
        using N_ref=Node&;

        AVLTree():_root(nullptr){}
        //高度
        size_t height(N_ptr root)const{
            if(root==nullptr)
                return 0;
            return 1+max(height(root->_left),height(root->_right));
        }
        //新增节点的位置判断
        // bool is_left(N_ptr parent,N_ptr son){
        //     if(!parent||!son){
        //         cout<<"error: parent or son is nullptr"<<endl;
        //         return false;
        //     }
        //     if(son->_kv._first<parent->_kv._first)
        //         return true;
        //     else if(son->_kv._first>parent->_kv._first)
        //         return false;
        //     else{
        //         cout<<"error: son is same as parent"<<endl;
        //         return false;
        //     }

        // }
        //旋转---rotate 须更新：1.父节点 2.子节点 3.平衡因子
        //左单旋---此处特指newnode---parent---gf三点一线的情况，折线情况属于双旋
        void rotate_L(N_ptr parent){
            N_ptr son_r=parent->_right;//右子节点
            N_ptr son_rl=son_r->_left;//右子节点的左子节点
            
            //更新左右子节点
            parent->_right=son_rl;
            son_r->_left=parent;
            //更新父节点
            N_ptr gf=parent->_parent;//父节点的父节点
            if(gf==nullptr){
                son_r->_parent=nullptr;
                _root=son_r;
            }
            else{
                son_r->_parent=gf;
                if(gf->_left==parent)
                    gf->_left=son_r;
                else
                    gf->_right=son_r;
            }
            parent->_parent=son_r;
            if(son_rl!=nullptr)
                son_rl->_parent=parent;
            //update balance factor
            parent->_bf=0;
            son_r->_bf=0;

        }
        //右单旋---此处特指newnode---parent---gf三点一线的情况，折线情况属于双旋
        void rotate_R(N_ptr parent){
            N_ptr son_l=parent->_left;//左子节点
            N_ptr son_lr=son_l->_right;//左子节点的右子节点
            
            //更新左右子节点
            parent->_left=son_lr;
            son_l->_right=parent;
            //更新父节点
            N_ptr gf=parent->_parent;//父节点的父节点
            if(gf==nullptr){
                son_l->_parent=nullptr;
                _root=son_l;
            }
            else{
                son_l->_parent=gf;
                if(gf->_left==parent)
                    gf->_left=son_l;
                else
                    gf->_right=son_l;
            }
            parent->_parent=son_l;
            if(son_lr!=nullptr)
                son_lr->_parent=parent;
            //update balance factor
            parent->_bf=0;
            son_l->_bf=0;
        }
        //左右双旋
        void rotate_LR(N_ptr parent){
            N_ptr son_l=parent->_left;//左子节点
            N_ptr son_lr=son_l->_right;//左子节点的右子节点

            //保存son_lr的bf，用于后续更新其他节点bf
            int bf=son_lr->_bf;

            rotate_L(son_l);//左单旋
            rotate_R(parent);//右单旋

            //更新平衡因子---若bf=0，即son_lr本身为newnode，双旋过后，三节点的bf均为0，无须更新
            if(bf==1)
                son_l->_bf=-1;
            else if(bf==-1)
                parent->_bf=1;

        } 
        //右左双旋
        void rotate_RL(N_ptr parent){
            N_ptr son_r=parent->_right;//右子节点
            N_ptr son_rl=son_r->_left;//右子节点的左子节点

            //保存son_rl的bf，用于后续更新其他节点bf
            int bf=son_rl->_bf;

            rotate_R(son_r);//右单旋
            rotate_L(parent);//左单旋

            //更新平衡因子---若bf=0，即son_rl本身为newnode，双旋过后，三节点的bf均为0，无须更新
            if(bf==1)
                parent->_bf=-1;
            else if(bf==-1)
                son_r->_bf=1;
        }
        //增---add
        //按BSTree插入+更新parent+更新bf+不平衡调整
        bool insert(const value_type& kv){
           //按BSTree插入+更新parent+更新bf
            N_ptr newNode=new Node(kv);

            N_ptr parent=nullptr;
            N_ptr cur=_root;
            if(_root==nullptr){
                _root=newNode;
                return true;
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
                        return false;//相等，无法插入
                    }
                }
            }
            if(parent->_kv._first>newNode->_kv._first){
                parent->_left=newNode;
                parent->_bf--;//更新平衡因子
            }
            else{
                parent->_right=newNode;
                parent->_bf++;//更新平衡因子
            }
            newNode->_parent=parent;//更新父节点

            //继续跟新bf+不平衡调整
            cur=parent;
            parent=cur->_parent;
            while(cur){
                //bf=0,则前bf=+-1,即newnode插入到较低子树，从而此树高度未变，无须向上更新祖先bf
                if(cur->_bf==0)
                    break;
                //bf=+-1，则前bf=0,无论newnode插入左/右子树，此树都会高度+1，须向上更新祖先bf
                else if(cur->_bf==1||cur->_bf==-1){
                    if (parent == nullptr)
                        break;
                    if(parent->_left==cur)
                        parent->_bf--;
                    else
                        parent->_bf++;
                    cur=parent;
                    parent=cur->_parent;
                //bf=+-2,则前bf=+-1，即new插入到较高子树，从而此树出现不平衡，须旋转调整
                }else if(cur->_bf==2||cur->_bf==-2){
                    //不平衡调整
                    if(cur->_bf==2){
                        if(cur->_right->_bf==1)
                            rotate_L(cur);//左单旋
                        else if(cur->_right->_bf==-1)
                            rotate_RL(cur);//右左双旋
                    }
                    if(cur->_bf==-2){
                        if(cur->_left->_bf==-1)
                            rotate_R(cur);//右单旋
                        else if(cur->_left->_bf==1)
                            rotate_LR(cur);//左右双旋
                    }
                    break;
                }
            }
        }   
        //删---delete
        //按BSTree删除+更新parent+更新bf+不平衡调整
         bool erase(const value_type& kv){
            //查找待删除节点
            N_ptr cur=find(kv);
        
            //按BSTree删除+更新parent
            N_ptr parent=cur->_parent;
            if (cur == nullptr)
                return false;
            else {
                if (cur->_left == nullptr) {
                    if(cur==_root)
                        _root=cur->_right;
                    else {
                        if (parent->_left == cur){
                            parent->_left = cur->_right;
                            parent->_bf++;//更新平衡因子
                        }
                        else{
                            parent->_right = cur->_right;
                            parent->_bf--;//更新平衡因子
                        }
                    }
                    cur->_right->_parent=parent;//更新父节点
                    delete cur;
                }
                else if (cur->_right == nullptr) {
                    if (cur == _root)
                        _root = cur->_left;
                    else {
                        if (parent->_left == cur){
                            parent->_left = cur->_left;
                            parent->_bf++;//更新平衡因子
                        }
                        else{
                            parent->_right = cur->_left;
                            parent->_bf--;//更新平衡因子
                        }
                    }
                    cur->_left->_parent = parent;//更新父节点
                    delete cur;
                }
                else {
                    //找到右子树最小值
                    N_ptr right_min = cur->_right;
                    N_ptr rm_parent = cur;
                    while (right_min->_left) {
                        rm_parent = right_min;
                        right_min=right_min->_left;
                    }
                    //更改cur---从而删除节点转换为right_min
                    cur->_kv = right_min->_kv;
                    
                    parent=rm_parent;//用于后续更新bf
                    if(rm_parent->_left==right_min){
                        rm_parent->_left=right_min->_right;
                        parent->_bf++;//更新平衡因子

                    }
                    else{
                        rm_parent->_right=right_min->_right;//极端情况：right_min在rm_parent
                        parent->_bf--;//更新平衡因子
                    }
                    right_min->_right->_parent=rm_parent;//更新父节点
                    delete right_min;
                }
            }

            //继续更新bf+不平衡调整
            cur=parent;
            parent=cur->_parent;
            while(cur){
                //bf=0,则前bf=+-1,即delete较高子树，从而此树高度-1，须向上更新祖先bf
                if(cur->_bf==0){
                    if(parent==nullptr)
                        break;
                    if(parent->_left==cur)
                        parent->_bf++;
                    else
                        parent->_bf--;
                    cur=parent;
                    parent=cur->_parent;

                }
                //bf=+-1，则前bf=0,无论delete左/右子树，此树都会高度不变，无须向上更新祖先bf
                else if(cur->_bf==1||cur->_bf==-1){
                    break;
                }
                //bf=+-2,则前bf=+-1，即delete较低子树，从而此树出现不平衡，须旋转调整
                else if(cur->_bf==2||cur->_bf==-2){
                    //不平衡调整
                    if(cur->_bf==2){
                        if(cur->_right->_bf==1)
                            rotate_L(cur);//左单旋
                        else if(cur->_right->_bf==-1)
                            rotate_RL(cur);//右左双旋
                    }
                    if(cur->_bf==-2){
                        if(cur->_left->_bf==-1)
                            rotate_R(cur);//右单旋
                        else if(cur->_left->_bf==1)
                            rotate_LR(cur);//左右双旋
                    }
                    break;
                }
            }

         }
        //查---find
        N_ptr find(const value_type& kv){
            if(_root==nullptr){
                return nullptr;
            }
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
        //改---modify,传递pair对象，pair.first为key---不可改，pair.second为val---可改

        //traverse
        //inorder traverse
        void inorder(N_ptr root)const{
            if(root==nullptr)
                return;
            inorder(root->_left);
            cout<<root->_kv._first<<":"<<root->_bf<<endl;
            inorder(root->_right);
        }
        //preorder traverse
        //postorder traverse
        //根节点获取
        N_ptr root()const{
            return _root;
        }
        private:
            N_ptr _root;
    };
}