#pragma once
#include "MY_STL.h"

//迭代器适配器：基于迭代器转换实现而来，适配特定场景
namespace MY_STL{
    template<class Iterator,class Ptr,class Ref>
    class m_reverse_iterator{
        public:
            using Self=m_reverse_iterator<Iterator,Ptr,Ref>;
            
            m_reverse_iterator(const Iterator& it=nullptr):_rit(it){}

            //*---reverse_iterator对应的位置为--this，即上一个
            Ref operator*(){ 
                Iterator tmp=_rit;
                return *(--tmp);
            }
            Ptr operator->(){ 
                Iterator tmp=_rit;
                return &(operator*());
            }

            //++
            Self& operator++(){
                --_rit;
                return *this;
            }
            Self operator++(int){
                //iterator的默构
                Iterator tmp(_rit--);
                return tmp;
            }
            //--
            Self& operator--(){
                ++_rit;
                return *this;
            }
            Self operator--(int){
                Iterator tmp(_rit++);
                return tmp;
            }

            bool operator==(const Self& rit){
                return _rit==rit._rit;
            }
            bool operator!=(const Self& rit){
                return _rit!=rit._rit;
            }

        private:
            Iterator _rit;
    };
}