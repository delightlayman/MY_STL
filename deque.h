#pragma once
#include "MY_STL.h"

//double ended queue
namespace MY_STL{
    //buffer_size选择
    // inline size_t set_buffer_size(size_t type_size){
    //     return type_size<512?512/type_size:1;
    // }
    template<class T,class Ptr,class Ref>
    class iterator_base{
        public:
            using iterator=iterator_base<T,T*,T&>;
            using const_iterator=iterator_base<T,const T*,const T&>;
            using Self=iterator_base<T,Ptr,Ref>;
            // size_t buffer_size(){
            //     return set_buffer_size(sizeof(T));
            // }
            //类内初始化
            static const inline size_t buffer_size=sizeof(T)<512?(512/sizeof(T)):1;
            //constructor & default constructor---不可用const，否则出现const转换为非const
            iterator_base(Ptr p,Ptr* mp):_b_cur(p),_b_first(*mp),_b_last(*mp+buffer_size),_map_buffer(mp){};
            iterator_base():_b_cur(0),_b_first(0),_b_last(0),_map_buffer(0){};
            //iterator==>iterator,const_iterator,const_iterator!=>iterator  类型转换
            iterator_base(const iterator& it):_b_cur(it._b_cur),_b_first(it._b_first),_b_last(it._b_last),_map_buffer(it._map_buffer){}


            //*
            Ref operator*(){return *_b_cur;}//T&
            //->
            Ptr operator->(){return _b_cur;}//T*

            //iterator间的距离---ptrdiff_t:通常long int，由于其正负皆可，故须转换size_t的buffer_size:c风格()或static_cast
            ptrdiff_t operator-(const Self& it)const{
                return static<ptrdiff_t>(buffer_size)*(_map_buffer-it._map_buffer-1)+(_b_cur-_b_first)+(it._b_last-it._b_cur);
            }
            //更新_map_buffer
            void _set_map_buffer(Ptr* _new_buffer){
                _map_buffer=_new_buffer;
                _b_first=*_new_buffer;
                _b_last=_new_buffer+buffer_size;
            }
            //++it
            Self& operator++(){
                ++_b_cur;
                if(_b_cur==_b_last){
                    _set_map_buffer(_map_buffer+1);
                    _b_cur=_b_first;
                }
                return *this;
            }
            //it++
            Self operator++(int){
                Self it=*this;
                operator++();
                return it;
            }
            //--it
            Self& operator--(){
                if(_b_cur==_b_first ){
                    _set_map_buffer(_map_buffer-1);
                    _b_cur=_b_last;
                }
                --_b_cur;
                return *this;
            }
            //it--
            Self operator--(int){
                Self it=*this;
                operator--();
                return it;
            }
            
            //+=
            Self& operator+=(ptrdiff_t n){
                ptrdiff_t _offset=
                return *this;
            }
            //+
            Self operator+(ptrdiff_t n){
                return *this;
            }
            //-=
            Self& operator-=(ptrdiff_t n){
                return *this;
            }
            //-
            Self operator+(ptrdiff_t n){
                return *this;
            }

            //random access---以当前iterator作为头部，随机访问左右n节点，ptrdiff:long int有符号
            Ref operator[](ptrdiff_t n){}
            //relational operator
            bool operator==(){}
            bool operator!=(){}
            bool operator>(){}
            bool operator<(){}
            bool operator<=(){}
            bool operator>=(){}


        private:
            //当前buffer中 iterator 指向位置
            Ptr _b_cur;
            //当前buffer头
            Ptr _b_first;
            //当前buffer尾
            Ptr _b_last;
            //map中指向当前buffer的指针
            Ptr* _map_buffer;//T**
    };

    template<class T>
    class m_deque{
        public:
            //STL取_initial_map_buffer_size和实际需求的较大值
            static const inline _initial_map_buffer_size=8;
            using iterator_base::buffer_size;

            using iterator=iterator_base<T,T*,T&>;
            using const_iterator=iterator_base<T,const T*,const T&>;

//源码           
template <class _Tp, class _Alloc>
void
_Deque_base<_Tp,_Alloc>::_M_initialize_map(size_t __num_elements)
{
    //所需buffer数
  size_t __num_nodes = 
    __num_elements / __deque_buf_size(sizeof(_Tp)) + 1;
    //多开两个 
  _M_map_size = max((size_t) _S_initial_map_size, __num_nodes + 2);
  _M_map = _M_allocate_map(_M_map_size);
    //设置map 的起始和结束位置
  _Tp** __nstart = _M_map + (_M_map_size - __num_nodes) / 2;
  _Tp** __nfinish = __nstart + __num_nodes;
    //buffer创建
  __STL_TRY {
    _M_create_nodes(__nstart, __nfinish);
  }
  __STL_UNWIND((_M_deallocate_map(_M_map, _M_map_size), 
                _M_map = 0, _M_map_size = 0));
  _M_start._M_set_node(__nstart);
  _M_finish._M_set_node(__nfinish - 1);
  _M_start._M_cur = _M_start._M_first;
  _M_finish._M_cur = _M_finish._M_first +
               __num_elements % __deque_buf_size(sizeof(_Tp));
}
//依次创建buffer
template <class _Tp, class _Alloc>
void _Deque_base<_Tp,_Alloc>::_M_create_nodes(_Tp** __nstart, _Tp** __nfinish)
{
  _Tp** __cur;
  __STL_TRY {
    for (__cur = __nstart; __cur < __nfinish; ++__cur)
      *__cur = _M_allocate_node();
  }
  __STL_UNWIND(_M_destroy_nodes(__nstart, __cur));
}
//依次释放buffer
template <class _Tp, class _Alloc>
void
_Deque_base<_Tp,_Alloc>::_M_destroy_nodes(_Tp** __nstart, _Tp** __nfinish)
{
  for (_Tp** __n = __nstart; __n < __nfinish; ++__n)
    _M_deallocate_node(*__n);
}




        private:
            iterator _start;
            iterator _finish;
            T** map;//中控
            size_t map_size;
        

    };
}