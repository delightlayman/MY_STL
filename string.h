#pragma once
#include <iostream>
#include <cstdlib>
#include <cstring>
using std::ostream;
using std::istream;

namespace My_String{
    class m_string{
    private:
        char* _s;
        //有效字符数
        size_t _size;
        //容量
        size_t _capacity;

    public:
        //iterator
        typedef char* iterator;
        //iterator
        iterator begin(){
            return _s;
        }
        iterator end(){
            return _s+strlen(_s);
        }


        //constructor
        m_string();
        m_string(const char* str);
        m_string(const m_string& s);
        m_string(m_string&& s);
        //destructor
        ~m_string();
        //operator overloding
        //relation operator
        bool operator<(const m_string& s);
        bool operator==(const m_string& s);

        bool operator<=(const m_string& s);
        bool operator!=(const m_string& s);

        bool operator>(const m_string& s);
        bool operator>=(const m_string& s);
        //input and output

        friend ostream& operator<<(ostream& os,const m_string& s);
        friend istream& operator>>(istream& is,m_string& s);
        
        //insert---add
        void push_back(char c);
        void append(const char* str);
        m_string& operator+=(char c);
        m_string& operator+=(const char* str);
        m_string& operator+=(const m_string& s);

        m_string& operator+(char c);
        m_string& operator+(const char* str);
        m_string& operator+(const m_string& s);

        m_string& insert(size_t pos,char c);
        m_string& insert(size_t pos,const char* str);
        m_string& insert(size_t pos,const m_string& s);
        
        //erase---delete--remove
        m_string& erse(size_t pos,size_t len);
        //query---find
        char& operator[](size_t pos);

        size_t find(char c);
        size_t find(const char* str);
        size_t find(const m_string& s);

        m_string& substr(size_t pos,size_t len);
        
        size_t size() const;
        size_t capacity() const;    
        //modify
        m_string& reverse();

        void reserve(size_t len);
        void resize(size_t len);

        const char* c_str(const m_string& s);

        m_string& operator=(const m_string& s);
        m_string& operator=(m_string&& s);
        
    };


    class simple_s{
    private:
        char* _s;
    public:
        //constructor
        simple_s();
        simple_s(const char* str);
        //传统写法
        simple_s(const simple_s& s);
        //现代写法
        //simple_s(const simple_s& s);

        //destructor
        ~simple_s();
        //operator =
        //传统写法
        simple_s& operator=(const simple_s& s);
        //现代写法
        //simple_s& operator=(const simple_s& s);

    };

}