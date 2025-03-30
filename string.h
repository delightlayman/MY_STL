#pragma once
#include <iostream>
#include <cstdlib>
using std::ostream;
using std::istream;

namespace My_String{
    class string{
    private:
        char* _s;
        size_t _size;
        size_t _capacity;

    public:
        //constructor
        string();
        string(const char* str);
        string(const string& s);
        string(string&& s);
        //destructor
        ~string();
        //operator overloding
        //relation operator
        bool operator<(const string& s);
        bool operator==(const string& s);

        bool operator<=(const string& s);
        bool operator!=(const string& s);

        bool operator>(const string& s);
        bool operator>=(const string& s);
        //input and output

        friend ostream& operator<<(ostream& os,const string& s);
        friend istream& operator>>(istream& is,const string& s);
        
        //insert---add
        void push_back(char c);
        void append(const char* str);
        string& operator+=(char c);
        string& operator+=(const char* str);
        string& operator+=(const string& s);

        string& operator+(char c);
        string& operator+(const char* str);
        string& operator+(const string& s);

        string& insert(size_t pos,char c);
        string& insert(size_t pos,const char* str);
        string& insert(size_t pos,const string& s);
        
        //erase---delete--remove
        string& erse(size_t pos,size_t len);
        //query---find
        char& operator[](size_t pos);

        size_t find(char c);
        size_t find(const char* str);
        size_t find(const string& s);

        string& substr(size_t pos,size_t len);

        typedef char* iterator;
        iterator begin();
        iterator end();
        
        size_t size();
        size_t capacity();    
        //modify
        string& reverse();

        void reserve(size_t len);
        void resize(size_t len);

        const char* c_str(const string& s);

        string& operator=(const string& s);
        string& operator=(string&& s);
        
    };


    class simple_s{
        private:
            char* _s;

    
        public:
            //constructor
            simple_s();
            simple_s(const char* str);
            simple_s(const simple_s& s);
            simple_s(simple_s&& s);
            //destructor
            ~simple_s();
            //operator =
            string& operator=(const string& s);

        };

}