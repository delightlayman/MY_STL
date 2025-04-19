#pragma once
#include "MY_STL.h"

namespace MY_STL{
    //带头双向循环链表
    template<class T>
    struct listnode{
        T _data;
        //注意：此处指针指向的是------实例化的listnode，即listnode<T>
        listnode<T>* _prev;
        listnode<T>* _next;
        
        //创建的每个节点------自我双向循环
        listnode(const T& d=T())
            :_data(d),_prev(this),_next(this){}

    };

    //迭代器
    template<class T>
    struct list_iterator{
        //iterator存储的值------Node* ptr
        typedef listnode<T> Node;
        Node* _ptr;

        //这里不可用const，_ptr为非const  
        list_iterator(Node* p=nullptr):_ptr(p){}

        T& operator*()const{
            return _ptr->_data;
        }
        //注意此处无第二操作数，如it->xxx，xxx为_data的数据成员，it->被转换为it.operator->()函数
        //其返值与xxx间应该还有一个->,但是编译器做了特殊处理，不用加
        T* operator->()const{
            return &_ptr->_data;
        }

        //++it
        list_iterator<T> operator++(){
            _ptr=_ptr->_next;
            return *this;
        }
        //it++
        list_iterator<T> operator++(int){
            list_iterator<T> tmp=_ptr;
            _ptr=_ptr->_next;
            return tmp; 
        }
        //--it
        list_iterator<T> operator--(){
            _ptr=_ptr->_prev;
            return *this;
        }
        //it--
        list_iterator<T> operator--(int){
            list_iterator<T> tmp=_ptr;
            _ptr=_ptr->_prev;
            return tmp;
        }
        //==
        bool operator==(const list_iterator<T>& it){
            return _ptr==it._ptr;
        }
        //!=
        bool operator!=(const list_iterator<T>& it){
            return _ptr!=it._ptr;
        }
    };
    //
    //迭代器（广义指针）------三个参数决定 list_iterator_base<T,Ptr，Ref> 
    //T：指向类型，Ptr:->返值类型,Ref:*返值类型 从而Ptr，Ref共同确定iterator的类型
    
    //const指针：指向const的指针，而非其指针本身const---有歧义但是大多都这么称呼
    //指向const使得不可通过ptr修改其指向值，即*ptr，ptr->data皆不可修改，但是ptr本身可以+-，如++ptr，--ptr
    //从而const_iterator的实现，只须保证重载运算符：*的返值const T&，->的返值const T*，即返值不可修改即可。
    //返回值有两组选择：T*,T&;const T*,const T&。分别对应iterator，const_iterator
    //后续list<T>定义中视情况 实例化iterator_base： 
    //list_const_iterator<T,T*,T&>------ iterator
    //list_const_iterator<T,const T*,const T&>------ const_iterator

    //为使iterator可构造iterator以及const_iterator，但是const_iterator不可构造iterator
    //方法：1.参数为iterator构造函数，构造各个实例化的类，iterator、const_iterator等
    //      2.分别定义+实现    
    //      3.C++11模板元编程

    template<class T,class Ptr,class Ref>
    struct list_iterator_base{
        //iterator存储的值------Node* ptr
        typedef listnode<T> Node;
        Node* _ptr;
        typedef list_iterator_base<T,T*,T&> iterator;
        //typedef llist_iterator_base<T,const T*,const T&> const_iterator;
        typedef list_iterator_base<T,Ptr,Ref> Self;

        list_iterator_base(Node* p=nullptr):_ptr(p){}
        //自身的复制构造------与下方存在定义重叠部分，冲突
        //list_iterator_base(const Self& it):_ptr(it._ptr){}
        //iterator可构造iterator以及const_iterator，但是const_iterator不可构造iterator，特性符合
        list_iterator_base(const iterator& it):_ptr(it._ptr){}

        Ref operator*()const{
            return _ptr->_data;
        }
        //注意此处无第二操作数，如it->xxx，xxx为_data的数据成员，it->被转换为it.operator->()函数
        //其返值与xxx间应该还有一个->,但是编译器做了特殊处理，不用加
        Ptr operator->()const{
            return &_ptr->_data;
        }

        //++it
        Self& operator++(){
            _ptr=_ptr->_next;
            return *this;
        }
        //it++
        Self operator++(int){
            Self tmp=_ptr;
            _ptr=_ptr->_next;
            return tmp; 
        }
        //--it
        Self& operator--(){
            _ptr=_ptr->_prev;
            return *this;
        }
        //it--
        Self operator--(int){
            Self tmp=_ptr;
            _ptr=_ptr->_prev;
            return tmp;
        }
        //==
        bool operator==(const Self& it){
            return _ptr==it._ptr;
        }
        //!=
        bool operator!=(const Self& it){
            return _ptr!=it._ptr;
        }
        //理论上应该检查+-len是否在链表有效节段内，且不可越过end
        //+
        Self operator+(size_t len){
            while(len--){
                _ptr=_ptr->_next;
            }
            return _ptr;
        }        
        //-
        Self operator-(size_t len){
            while(len--){
                _ptr=_ptr->_prev;
            }
            return _ptr;
        }


    };
    //带头双向循环链表
    template<class T>
    class m_list{
        public:
            typedef listnode<T> Node;
            //typedef list_iterator<T> iterator;
            typedef list_iterator_base<T,T*,T&> iterator;
            typedef list_iterator_base<T,const T*,const T&> const_iterator;
            
            
            iterator begin(){
                return _end->_next;
            }
            iterator end(){
                return _end;
            }

            const_iterator begin()const{
                return _end->_next;
            }
            const_iterator end()const{
                return _end;
            }
            //constructor
            //初始化为一个头结点，此节点作为超尾end
            m_list():_end(new Node){} 
            
            //用不上Node*构造，还不如直接push_back(val);
            // m_list(const Node* p)
            //     :_head(p){}
            m_list(size_t num,const T& val=T()){
                _end=new Node;

                for(int i=0;i<num;++i){
                    push_back(val);
                }
            }

            //copy constructor
            m_list(const m_list& ls){
                _end=new Node;
                const_iterator it_b=ls.begin();
                const_iterator it_e=ls.end();
                while(it_b!=it_e){
                    push_back(*it_b);
                    ++it_b;
                }
            }
            
            //清理所有数据包括头节点
            ~m_list(){
                clear();
                delete _end;
                _end=nullptr;

                cout<<"~m_list"<<endl;
            }
            //保留头节点，清理后续
            void clear(){
                Node* beg=_end->_next;
                while(beg!=_end){
                    Node* next=beg->_next;
                    delete beg;
                    beg=next;
                }
                _end->_next=_end;
                _end->_prev=_end;
            }
            
            //copy assignment
            // m_list& operator=(const m_list& ls){
            //     if(this!=&ls){
            //         clear();
            //         const_iterator it_b=ls.begin();
            //         const_iterator it_e=ls.end();
            //         while(it_b!=it_e){
            //             push_back(*it_b);
            //             ++it_b;
            //         }
            //     }
            //     return *this;
            // }
            //现代写法
            m_list& operator=(m_list ls){
                swap(ls);
                return *this;
            }
            //若需简洁---可代码复用
            //add
            void push_front(const T& val){
                Node * tmp=new Node(val);
                Node* beg=_end->_next;

                _end->_next=tmp;
                tmp->_prev=_end;

                tmp->_next=beg;
                beg->_prev=tmp;

            }
            void push_back(const T& val){
                Node* tmp=new Node(val);
                Node* rear=_end->_prev;

                _end->_prev=tmp;
                tmp->_next=_end;

                rear->_next=tmp;
                tmp->_prev=rear;
                
            }
            //返回新增节点/段后的下一节点位置
            iterator insert(const_iterator pos,const T& val){
                Node* new_node=new Node(val);
                Node* cur=pos._ptr;
                Node* pre=cur->_prev;

                pre->_next=new_node;
                new_node->_prev=pre;

                new_node->_next=cur;
                cur->_prev=new_node;
                
                return pos._ptr;
            }
            //返回新节点段的起始位置

            //注意：1.不可修改原链表，2.局部链表嵌入目标链表，其后析构导致，此段皆为悬空指针。
            iterator insert(const_iterator pos,const_iterator first,const_iterator last){
                while(first!=last){
                    insert(pos,*first);
                    ++first;
                }
                return pos._ptr;
            }

            //delete
            void pop_front(){
                Node* beg=_end->_next;
                Node* next=beg->_next;
                delete beg;
                _end->_next=next;
                next->_prev=_end;
            }
            void pop_back(){
                Node* rear=_end->_prev;
                Node* prev=rear->_prev;
                delete rear;
                _end->_prev=prev;
                prev->_next=_end;
            }
            //能否delete取决于指针是否指向有效的堆内存，而非指针的const属性
            //const表示其const部分不可更改
            //返回下一节点
            iterator erase(const_iterator pos){
                Node* cur=pos._ptr;
                Node* prev=cur->_prev;
                Node* next=cur->_next;
                delete cur;
                prev->_next=next;
                next->_prev=prev;

                return next;
            }

            iterator erase(const_iterator frist,const_iterator last){
                while(frist!=last)
                    erase(frist++);
                return last._ptr;
            }

            //query
            iterator find(const T& val){
                const_iterator it=_end->_next;
                const_iterator end=_end;
                while(it!=end){
                    if(*it==val)
                        break;
                }
                return it;

            }
            //modify
            void swap(m_list& ls){
                ::swap(_end,ls._end);
            }
            //print
            void printf_list(){
                m_list<T>::iterator it=begin();
                m_list<T>::iterator fi=end();
                while(it!=fi){
                    cout<<*it<<" ";
                    ++it;
                }
                cout<<endl;
            }
        private:
        Node* _end;
    };
}