#pragma once
#include "MY_STL.h"
//模板类的成员函数声明和定义必须放在同一个头文件中，不能像普通类那样将声明（.h）和定义（.cpp）分开
namespace MY_STL{
    template <class T>
    class m_vector{
        public:
            //iterator
            typedef T* iterator;
            iterator begin(){
                return _start;
            }
            iterator end(){
                return _finish;
            }

            typedef const T* const_iterator;
            iterator begin()const {
                return _start;
            }
            iterator end()const {
                return _finish;
            }

            //constructor
            m_vector();
            m_vector(size_t size,const T& val=T());
            m_vector(T* arr,size_t size);
            m_vector(const m_vector& a);
            m_vector(m_vector&& a);
            //destructor
            ~m_vector();
            //operator =
            m_vector& operator=(const m_vector& a);
            m_vector operator=(m_vector&& a);
            //operator []
            T& operator[](size_t pos);
            const T& operator[](size_t pos)const;
            
            //size and capacity 
            size_t size(){
                return _finish-_start;
            }
            size_t capacity(){
                return _end_of_storage-_start;
            }
            size_t size()const {
                return _finish - _start;
            }
            size_t capacity()const {
                return _end_of_storage - _start;
            }

            //adjust size and capacity
            void resize(size_t n,const T& val=T());
            void reserve(size_t n);
            
            //add
            m_vector& push_back(const T& n);
            m_vector& insert(size_t pos,T& n);
            m_vector& insert(size_t pos,T* arr, size_t len);
            m_vector& insert(size_t pos,const m_vector& n);
            //delete
            m_vector& pop_back();
            m_vector& erase(size_t pos,size_t len); 

            //query

            //modify
            void swap(T& v) {
                //避免递归，用全局swap
                ::swap(_start, v._start);
                ::swap(_finish, v._finish);
                ::swap(_end_of_storage, v._end_of_storage);
            }

            
        private:
            iterator _start;
            iterator _finish;
            iterator _end_of_storage;
    };
}

namespace MY_STL {
    //constructor
    //default
    template<class T>
    m_vector<T>::m_vector()
        :_start(nullptr), _finish(nullptr), _end_of_storage(nullptr) {}
    //size+val
    template<class T>
    m_vector<T>::m_vector(size_t size,const T& val){
        T* tmp = new T[size];
        for(int i=0;i<size;++i){
            tmp[i]=val;
        }
        _start = tmp;
        _finish = tmp + size;
        _end_of_storage = tmp + size;
    }
    //array
    template<class T>
    m_vector<T>::m_vector(T* arr, size_t size) {
        T* tmp = new T[size];
        //memory系列函数都是按字节操作
        //memcpy按字节复制，执行浅拷贝，内置类型正常进行------仅对值的复制，包括指针，但不会复制指针指向内容。
        //从而，多指针指向同一块内存，若对其多次释放---程序崩溃。
        //自定义类型数据成员包括指针的同理。
        //故须用------深复制
        
        //memcpy(tmp, arr, sizeof(T) * size);
        for(int i=0;i<size;++i){
            tmp[i]=arr[i];
        }
        _start = tmp;
        _finish = tmp + size;
        _end_of_storage = tmp + size;
    }
    //copy constructor
    template<class T>
    m_vector<T>::m_vector(const m_vector<T>& a) {
        size_t si = a.size();
        size_t cap = a.capacity();

        T* tmp = new T[cap];
        for (int i = 0; i < si; i++) {
            tmp[i]=a._start[i];
        }
        _start = tmp;
        _finish = tmp + si;
        _end_of_storage = tmp + cap;
    }
    //move constructor
    template<class T>
    m_vector<T>::m_vector(m_vector<T>&& a) {
        swap(a);
    }

    //destructor
    template<class T>
    m_vector<T>::~m_vector() {
        delete[] _start;
        _start = nullptr;
        _finish = nullptr;
        _end_of_storage = nullptr;

    }

    //operator =
    template<class T>
    m_vector<T>& m_vector<T>::operator=(const m_vector<T>& a) {
        if (this != &a) {
            //资源的释放交给tmp
            m_vector<T> tmp(a);
            swap(tmp);
        }
        
        return *this;
    }
    //简洁版
    /*m_vector<T>& m_vector<T>::operator=(m_vector<T> a) { //传值---拷贝构造---副本
        swap(a);
        return *this;
    }*/

    template<class T>
    m_vector<T> m_vector<T>::operator=(m_vector<T>&& a) {
        swap(a);
        return *this;
    }


    //operator []
    template< class T>
    T& m_vector<T>::operator[](size_t pos) {
        assert(pos<size());
        return *(_start + pos);
    }

    template< class T>
    const T& m_vector<T>::operator[](size_t pos)const {
        assert(pos<size());
        return *(_start + pos);
    }

    //adjust size and capacity
    template< class T>
    void m_vector<T>::resize(size_t n,const T& val) {
        if(n==size())
            return;

        size_t si=size();
        size_t cap=capacity();
        if(n<si)
            _finish=_start+n;
        else if(n<cap){
            while(_finish<_start+n){
                *_finish=val;
                ++_finish;
            }
        }else{
            reserve(n);
            while(_finish<_start+n){
                *_finish=val;
                ++_finish;
            }
        }
    }
    template< class T>
    void m_vector<T>::reserve(size_t n) {
        if(n<=size())
            return;
        size_t si = size();
        size_t cap = capacity();

        T* tmp = new T[n];
        if (_start) {
            //memcpy为浅复制
            //memcpy(tmp, _start, sizeof(T) * si);
            for(int i=0;i<si;++i)
                tmp[i]=_start[i];
            delete[] _start;
        }
 
    }

    //add
    template<class T>
    m_vector<T>& m_vector<T>::push_back(const T& n) {
        size_t si = size();
        size_t cap = capacity();
        if (si == cap) {
            size_t new_cap = cap == 0 ? 2 : cap * 2;
            reserve(new_cap);
        }
        *_finish = n;
        _finish++;
        return *this;
    }
    template<class T>
    m_vector<T>& m_vector<T>::insert(size_t pos, T& n) {
        assert(pos <= size());
        size_t si = size();
        size_t cap = capacity();
        if (si == cap) {
            size_t new_cap = cap == 0 ? 2 : cap * 2;
            reserve(new_cap);
        }
        T* move_src = _finish;
        T* move_dest = _finish + size;
        T* insert_pos = _start + pos;

        while (move_src != insert_pos) {
            *(--move_dest) = *(--move_src);
        }
        *insert_pos = n;

        return *this;
    }
    template<class T>
    m_vector<T>& m_vector<T>::insert(size_t pos, T* arr,size_t len) {
        size_t si = size();
        assert(pos <= si);

        size_t cap = capacity();
        size_t new_size = si + len;
        
        if (new_size <= cap) {
            T* move_src = _finish;
            T* move_dest = _finish + len;
            T* insert_pos = _start + pos;

            while (move_src != insert_pos) {
                *(--move_dest) = *(--move_src);
            }
            for(int i = 0; i < len;++i) {
                *(insert_pos++) = arr[i];
            }
        }
        else {
            //reserve会更新_start,_finish,_end_of_storage
            reserve(new_size);
            T* move_src = _finish;
            T* move_dest = _finish + len;
            T* insert_pos = _start + pos;

            while (move_src != insert_pos) {
                *(--move_dest) = *(--move_src);
            }
            for (int i = 0; i < len; ++i) {
                *(insert_pos++) = arr[i];
            }
        }
        _finish = _start + new_size;
        return *this;
    }
    template<class T>
    m_vector<T>& m_vector<T>::insert(size_t pos, const m_vector<T>& a) {
        insert(pos, a._start, a.size());
    }
    //delete
    template<class T>
    m_vector<T>& m_vector<T>::pop_back() {
        if(_start<_finish)
            _finish--;
        return *this;
    }
    template<class T>
    m_vector<T>& m_vector<T>::erase(size_t pos, size_t len) {
        assert(pos <= size());
        size_t si = size();
        if (pos + len >= si)
            _finish = _start + pos;
        else {
            T* move_src = _start + pos + len;
            T* move_dest = _start + pos;
            while (move_src != _finish) {
                *(move_dest++) = *(move_src++);
            }
        }
        _finish = _start + si - len;

        return *this;
    }

    //query

    //modify
    
}