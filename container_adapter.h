#pragma once
#include "MY_STL.h"

//容器适配器：基于其他容器转换实现而来，适配特定场景
//适配器：stack，queue，priority_queue
//STL的satck和queue底层实现使用的是：deque
namespace MY_STL{
    //LIFO
    template<class T,class Container>
    class m_stack{
        public:
            void push(const T& val){_con.push_back(val);}
            void pop(){_con.pop_back();}
            bool empty(){ return _con.empty();}
            size_t size(){ return _con.size();}
            T& top(){ return _con.back();}
        private:
            Container _con;

    };

    //FIFO---适用list
    template<class T,class Container>
    class m_queue{
        public:
            void push(const T& val){_con.push_back(val);}
            void pop(){_con.pop_front();}
            bool empty(){ return _con.empty();}
            size_t size(){ return _con.size();}
            T& front(){ return _con.front();}
            T& back(){ return _con.back();}
        private:
            Container _con;

    };
        
    //适用---vector
    //默认---建大堆
    template<class T,class Container=vector<T>,class Compare=less<T>>//stl建大堆用的less，比较反直觉
    class m_priority_queue{
        public:
            Compare cmp;
            //logN
            void adjust_down(size_t parent){;//root
                size_t child=2*parent+1;
                size_t si=_con.size();
                while(child<si){
                    //if(child+1<si&&_con[child]<_con[child+1])
                    if(child+1<si&&cmp(_con[child],_con[child+1]))
                        ++child;
                    //if(_con[parent]<_con[child]){
                    if(cmp(_con[parent],_con[child])){
                        swap(_con[parent],_con[child]);
                        parent=child;
                        child=2*parent+1;
                    }
                    else
                        break;
                }
            }
            //logN
            void adjust_up(size_t child){//leaf
                size_t parent=(child-1)/2;
                while(child>0){
                    //if(_con[parent]<_con[child]){
                    if(cmp(_con[parent],_con[child])){
                        swap(_con[parent],_con[child]);
                        child=parent;
                        parent=(child-1)/2;
                    }
                    else
                        break;
                }

            }
            void push(const T& val){
                _con.push_back(val);
                adjust_up(_con.size()-1);
            }
            void pop(){
                //堆顶堆底交换，删除堆底，调整堆顶
                swap(_con.front(),_con.back());
                _con.pop_back();
                adjust_down(0);
            }
            size_t size(){return _con.size();}
            bool empty(){return _con.empty();}
            T& top(){return _con.front();}

        private:
            Container _con;
    };
    
}

