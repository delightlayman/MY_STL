#pragma once
#include "MY_STL.h"

namespace MY_STL{
    class m_string{
    private:
        char* _s;
        //有效字符数
        size_t _size;
        //有效字符容量
        size_t _capacity;
        
    public:
        static const size_t npos = -1;
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
        //explicit仅可用于声明 
        explicit m_string(const char* str);
        m_string(const m_string& s);
        m_string(m_string&& s)noexcept;

        m_string(size_t n,char c='0');
        //destructor
        ~m_string();
        //operator overloding
        //assignment operator
        m_string& operator=(const m_string& s);
        m_string& operator=(m_string&& s)noexcept;
        //relation operator
        bool operator<(const m_string& s)const;
        bool operator==(const m_string& s)const;

        bool operator<=(const m_string& s)const;
        bool operator!=(const m_string& s)const;

        bool operator>(const m_string& s)const;
        bool operator>=(const m_string& s)const;
        //input and output

        friend ostream& operator<<(ostream& os,const m_string& s);
        friend istream& operator>>(istream& is,m_string& s);
        
        //insert---add
        void push_back(char c);
        void append(const char* str);
        m_string& operator+=(char c);
        m_string& operator+=(const char* str);
        m_string& operator+=(const m_string& s);

        m_string operator+(char c)const;
        m_string operator+(const char* str)const;
        friend m_string operator+(char c,const m_string& s);
        friend m_string operator+(const char* str,const m_string& s);
        m_string operator+(const m_string& s)const;

        m_string& insert(size_t pos,char c);
        m_string& insert(size_t pos,const char* str);
        m_string& insert(size_t pos,const m_string& s);
        
        //erase---delete--remove
        void pop_back();
        m_string& erase(size_t pos,size_t len);
        //query---find
        const char& operator[](size_t pos)const;
        char& operator[](size_t pos);

        char* find(char c)const;
        char* find(const char* str)const;
        char* find(const m_string& s)const;

        m_string substr(size_t pos,size_t len)const;
        
        size_t size() const;
        size_t capacity() const;    
        //modify
        m_string& reverse();

        void reserve(size_t len);
        void resize(size_t len,char c = '0');

        const char* c_str(const m_string& s);
        
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