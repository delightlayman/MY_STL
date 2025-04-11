#include "vector.h"

namespace MY_STL{
    //constructor
    template<class T>
    m_vector<T>::m_vector()
        :_start(nullptr),_finish(nullptr),_end_of_storage(nullptr){}

    template<class T>
    m_vector<T>::m_vector(T* arr){
        size_t len=sizeof(arr)/sizeof(T);
        T* tmp=new T[len];
        memcpy(tmp,arr,sizeof(arr));
        _start=tmp;
        _finish=tmp+len;
        _end_of_storage=tmp+len; 
    }

    template<class T>
    m_vector<T>::m_vector(const m_vector<T>& a){}

    template<class T>
    m_vector<T>::m_vector(m_vector<T>&& a){}

    //destructor
    template<class T>
    m_vector<T>::~m_vector(){}

    //operator =
    template<class T>
    m_vector<T>& m_vector<T>::operator=(const m_vector<T>& a){}
    
    template<class T>
    m_vector<T> m_vector<T>::operator=(m_vector<T>&& a){}


    //operator []
    template< class T>
    T& m_vector<T>::operator[](size_t pos){}
    
    template< class T>
    const T& m_vector<T>::operator[](size_t pos)const{}

    //adjust size and capacity
    template< class T>
    void m_vector<T>::resize(size_t n){}
    template< class T>
    void m_vector<T>::reserve(size_t n){
        //注意：新旧数组指针间的关系
        size_t si=size();
        size_t cap=capacity();

        if(n>cap){
            T* tmp=new T[n];
            if(_start){
                memcpy(tmp,_start,sizeof(T)*si);
                delete[] _start;
            }
            _start=tmp;
            _finish=_start+si;
            _end_of_storage=_start+cap;
        }
    }
}