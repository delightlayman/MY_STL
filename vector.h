#pragma once
#include "MY_STL.h"

namespace MY_STL{
    template <class T>
    class m_vector{
        typedef T* iterator;

        private:
            iterator _start;
            iterator _finish;
            iterator _end_of_storage;
        public:
            //iterator
            iterator begin(){
                return _start;
            }
            iterator end(){
                return _finish;
            }
            //constructor
            m_vector();
            m_vector(size_t len,const T& val);
            explicit m_vector(T* arr);
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
            iterator find(T& n);
            //modify
            

    };
}