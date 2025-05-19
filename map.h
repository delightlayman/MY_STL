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
            using value_type=m_pair<K,T>;
            using map_key=key_extract_1;

            using rbtree=RBTree_base<key_type,value_type,map_key,compare>;
            using iterator=rbtree::iterator;
            using const_iterator=rbtree::const_iterator;


            //constructor
            m_map():_rb(nullptr){}
            //copy constructor
            m_map(const Self& map){}
            //operator =
            Self& operator(const Self& map){}
            m_map(const Self& map){}
            //destructor
            ~m_map(){}

            //add
            m_pair<iterator,bool> insert(const value_type& t){
                return _rb.insert(t);
            }
            //delete
            bool erase(const key_type& k){
                return erase(k);
            }
            //query
            iterator find(const key_type& k){
                return _rb.find(k);
            }
            const_iterator find(const key_type& k)const{
                return _rb.find(k)const;
            }

            //按照key，访问val
            value_type& operator[](const key_type& k){
                m_pair<iterator,bool> tmp=_rb.insert(make_m_pair(k,T()));
                return tmp._first->_second;
            }
            //modify---key不可修改，val可改

        previte:
            rbtree _rb;
    };
}