#include "string.h"
using std::endl;
using std::cout;
namespace My_String{
//constructor
//默认1 用于存储'\0'
m_string::m_string():_s(new char[1]),_size(1),_capacity(1){
    strcpy(_s,"\0");
}
m_string::m_string(const char* str):_s(new char[strlen(str)+1]),_size(strlen(str)),_capacity(strlen(str)){
    strcpy(_s,str);
}

m_string::m_string(const m_string& s):_s(new char[s.size()+1]),_size(s.size()),_capacity(s.size()){
    strcpy(_s,s._s);
}
m_string::m_string(m_string&& s):_s(new char[s.size()+1]),_size(s.size()),_capacity(s.size()){
    delete [] s._s;
    s._s=nullptr;
}
//destructor
m_string::~m_string(){
    delete [] _s;
    _s=nullptr;
    _size=0;
    _capacity=0;

    //cout<<"~m_string"<<endl;
}
// //operator overloding
// //relation operator
// bool m_string::operator<(const m_string& s){}
// bool m_string::operator==(const m_string& s){}

// bool m_string::operator<=(const m_string& s){}
// bool m_string::operator!=(const m_string& s){}

// bool m_string::operator>(const m_string& s){}
// bool m_string::operator>=(const m_string& s){}
//input and output

ostream& operator<<(ostream& os,const m_string& s){
    os<<s._s<<" "<<s._size<<" "<<s._capacity<<endl;
    return os;
}
istream& operator>>(istream& is,m_string& s){
    is>>s._s>>s._size>>s._capacity;
    return is;
}

// //insert---add
// void m_string::push_back(char c){}
// void m_string::append(const char* str){}
// m_string& m_string::operator+=(char c){}
// m_string& m_string::operator+=(const char* str){}
// m_string& m_string::operator+=(const m_string& s){}

// m_string& m_string::operator+(char c){}
// m_string& m_string::operator+(const char* str){}
// m_string& m_string::operator+(const m_string& s){}

// m_string& m_string::insert(size_t pos,char c){}
// m_string& m_string::insert(size_t pos,const char* str){}
// m_string& m_string::insert(size_t pos,const m_string& s){}

// //erase---delete--remove
// m_string& m_string::erse(size_t pos,size_t len){}
// //query---find
// char& m_string::operator[](size_t pos){}

// size_t m_string::find(char c){}
// size_t m_string::find(const char* str){}
// size_t m_string::find(const m_string& s){}

// m_string& m_string::substr(size_t pos,size_t len){}


size_t m_string::size()const{
    return _size;
}
size_t m_string::capacity()const{
    return _capacity;
}    
// //modify
// m_string& m_string::reverse(){}

// void m_string::reserve(size_t len){}
// void m_string::resize(size_t len){}

// const char* m_string::c_str(const m_string& s){}

m_string& m_string::operator=(const m_string& s){
    if(this!=&s){
        char* tmp=new char[s.size()+1];
        strcpy(tmp,s._s);

        delete [] _s;
        _s=tmp;
        _size=s.size();
        _capacity=s.size();
    }
    return *this;
}
m_string& m_string::operator=(m_string&& s){
    delete [] _s;
    _s=s._s;
    s._s=nullptr;
    _size=strlen(_s);
    _capacity=strlen(_s);
    
    return *this;
}


// //constructor
// simple_s::simple_s(){}
// simple_s::simple_s(const char* str){}
// //传统写法
// simple_s::simple_s(const simple_s& s){}
// //现代写法
// //simple_s::simple_s(const simple_s& s){}

// //destructor
// simple_s::~simple_s(){}
// //operator =
// //传统写法
// simple_s& simple_s::operator=(const simple_s& s){}
// //现代写法
// //simple_s& simple_s::operator=(const simple_s& s){}
}