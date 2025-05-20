#pragma once
#include "MY_STL.h"
#include "RBT_to_map_set.h"
#include "pair.h"
using MY_STL::RBTree_base;
using MY_STL::m_pair;
using MY_STL::make_m_pair;

namespace MY_STL{
    template<class K,class T,class compare=less<K>>
    class m_map{
        public:
            using Self=m_map<K,T,compare>;

            using key_type=K;
            using value_type=m_pair<K,T>;//值存储类型
            using map_key=key_extract_1<key_type,value_type>;

            using rbtree=RBTree_base<key_type,value_type,map_key,compare>;
            //iterator类型依赖rbtree模板参数的确定而确定---依赖类型，需要加typename告诉编译器其为类型，而非变量
            using iterator=typename rbtree::iterator;
            using const_iterator= typename rbtree::const_iterator;

            iterator begin() {
                return _rb.begin();
            }
            const_iterator begin()const {
                return _rb.begin();//实际调用其const版本
            }
            iterator end() {
                return _rb.end();
            }
            const_iterator end()const {
                return _rb.end();//实际调用其const版本
            }
            //constructor
            m_map(){}

            template<class InputIterator>
            m_map(InputIterator first, InputIterator last) {
                _rb.insert(first, last);
            }
            //copy constructor
            m_map(const Self& map){
                rbtree tmp(map._rb);
                _rb.swap(tmp);
            }
            //operator =
            Self& operator=(const Self& map){
                if (this != &map) 
                    _rb=map._rb;
                return *this;
            }
            //destructor

            //add
            m_pair<iterator,bool> insert(const value_type& t){
                return _rb.insert(t);
            }
            template<class InputIterator>
            void insert(InputIterator first, InputIterator last) {
                _rb.insert(first, last);
            }
            //delete
            bool erase(const key_type& k){
                return _rb.erase(k);
            }
            //query
            iterator find(const key_type& k){
                return _rb.find(k);
            }
            const_iterator find(const key_type& k)const{
                return _rb.find(k);//实际调用其const版本
            }

            //按照key，访问val
            T& operator[](const K& k){
                m_pair<iterator,bool> tmp=_rb.insert(make_m_pair(k,T()));
                return tmp._first->_second;
            }
            //modify---key不可修改，val可改
        private:
            rbtree _rb;
    };
}