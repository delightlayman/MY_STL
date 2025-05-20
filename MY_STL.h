#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cassert>
//#include <algorithm>
//#include <utility>

#include <vector>
#include <list>
#include <ctime>
using std::vector;
using std::list;

using std::ostream;
using std::istream;

using std::cout;
using std::cin;
using std::endl;

using std::swap;
using std::min;
using std::max;
//using std::move;//将左值显式转换为右值引用，标记该对象可被移动

//namespace MY_STL{}//名称空间声明


//比较函数
//函数对象=函数指针+函数符+lambda
template<class T>
struct  less{
    bool operator()(const T& a,const T& b){ return a<b;}
};
template<class T>
struct  more{
    bool operator()(const T& a,const T& b){ return a>b;}
};

template<class T>
struct less_equal{
    bool operator()(const T& a,const T& b){ return a<=b;} 
};

template<class T>
struct more_equal{
    bool operator()(const T& a,const T& b){ return a>=b;} 
};


 //key提取函数:从数据类型T中提取，关键字key
 //适用key即是val
 template<class K>
 struct key_identity{
     const K& operator()(const K& k) { return k; }
     //const版本确保：作为被调函数存在于 其他类const成员函数的调用
     const K& operator()(const K& k)const{ return k;}
 };
 //适用pair<key,val>
 template<class K,class T>
 struct key_extract_1{
     const K& operator()(const T& t) { return t._first; }
     const K& operator()(const T& t)const{ return t._first;}
 };
