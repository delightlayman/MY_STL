#pragma once
#include "MY_STL.h"
//ģ����ĳ�Ա���������Ͷ���������ͬһ��ͷ�ļ��У���������ͨ��������������.h���Ͷ��壨.cpp���ֿ��������� C++ ģ��ı�����ƾ����ġ�

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
            //constructor
            m_vector();
            m_vector(size_t len,const T& val);
            explicit m_vector(T* arr,size_t size);
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

            //adjust size and capacity
            void resize(size_t n);
            void reserve(size_t n);
            
            //add
            m_vector& push_back(const T& n);
            m_vector& insert(size_t pos,T& n);
            m_vector& insert(size_t pos,T* arr);
            m_vector& insert(size_t pos,const m_vector& n);
            //delete
            m_vector& pop_back();
            m_vector& erase(size_t pos,size_t len); 

            //query

            //modify
            
        private:
            iterator _start;
            iterator _finish;
            iterator _end_of_storage;
    };
}

namespace MY_STL {
    //constructor
    template<class T>
    m_vector<T>::m_vector()
        :_start(nullptr), _finish(nullptr), _end_of_storage(nullptr) {}

    template<class T>
    m_vector<T>::m_vector(T* arr, size_t size) {
        T* tmp = new T[size];
        memcpy(tmp, arr, sizeof(T) * size);
        _start = tmp;
        _finish = tmp + size;
        _end_of_storage = tmp + size;
    }

    template<class T>
    m_vector<T>::m_vector(const m_vector<T>& a) {}

    template<class T>
    m_vector<T>::m_vector(m_vector<T>&& a) {}

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
    m_vector<T>& m_vector<T>::operator=(const m_vector<T>& a) {}

    template<class T>
    m_vector<T> m_vector<T>::operator=(m_vector<T>&& a) {}


    //operator []
    template< class T>
    T& m_vector<T>::operator[](size_t pos) {}

    template< class T>
    const T& m_vector<T>::operator[](size_t pos)const {}

    //adjust size and capacity
    template< class T>
    void m_vector<T>::resize(size_t n) {

    }
    template< class T>
    void m_vector<T>::reserve(size_t n) {
        //ע�⣺�¾�����ָ���Ĺ�ϵ
        size_t si = size();
        size_t cap = capacity();

        if (n > cap) {
            T* tmp = new T[n];
            if (_start) {
                memcpy(tmp, _start, sizeof(T) * si);
                delete[] _start;
            }
            _start = tmp;
            _finish = _start + si;
            _end_of_storage = _start + n;
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
    m_vector<T>& m_vector<T>::insert(size_t pos, T& n) {}
    template<class T>
    m_vector<T>& m_vector<T>::insert(size_t pos, T* arr) {}
    template<class T>
    m_vector<T>& m_vector<T>::insert(size_t pos, const m_vector<T>& n) {}
    //delete
    template<class T>
    m_vector<T>& m_vector<T>::pop_back() {}
    template<class T>
    m_vector<T>& m_vector<T>::erase(size_t pos, size_t len) {}

    //query

    //modify
}