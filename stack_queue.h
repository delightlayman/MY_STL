#pragma once
#include "MY_STL.h"

//容器适配器：基于其他容器转换实现而来，适配特定场景
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

    //FIFO
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
}
