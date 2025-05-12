#pragma once

namespace MY_STL{
    template<class K,class V>
    struct m_pair{
        using Self=m_pair<K,V>;
        K _first;
        V _second;
        m_pair(const K& k=K(),const V& v=V()):_first(k),_second(v){}
        m_pair(const Self& p) :_first(p._first),_second(p._second) {}
        Self& operator=(const Self& p) {
            if (this != &p) {
                _first = p._first;
                _second = p._second;
            }
            return *this;
        }
        //relational operator
    };
    template<class K,class V>
    m_pair<K,V> make_m_pair(const K& k=K(),const V& v=V()){
        return m_pair<K,V>(k,v);
    }
    //若无需访问私有成员，可重载的运算符中，除=,(),[],->外，其他运算符重载函数可声明并定义在类外
    //<,>
    template<class K,class V>
    bool operator<(const m_pair<K,V>& p1,const m_pair<K,V>& p2){
        return p1._first<p2._first;
    }

    template<class K,class V>
    bool operator>(const m_pair<K,V>& p1,const m_pair<K,V>& p2){
        return p1._first>p2._first;
    }
    //==,!=
    template<class K,class V>
    bool operator==(const m_pair<K,V>& p1,const m_pair<K,V>& p2){
        return p1._first==p2._first;
    }

    template<class K,class V>
    bool operator!=(const m_pair<K,V>& p1,const m_pair<K,V>& p2){
        return p1._first!=p2._first;
    }
}