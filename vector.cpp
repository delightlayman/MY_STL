#include "vector.h"

namespace MY_STL{
    //constructor
    template<class T>
    m_vector<T>::m_vector(){}

    template<class T>
    m_vector<T>::m_vector(T *arr){}

    template<class T>
    m_vector<T>::m_vector(const m_vector<T>& a){}

    template<class T>
    m_vector<T>::m_vector(m_vector<T>&& a){}

    //destructor
    template<class T>
    m_vector<T>::~m_vector(){}

    //operator =
    template<class T>
    const m_vector<T>& m_vector<T>::operator=(const m_vector<T>& a){}
    
    template<class T>
    const m_vector<T>& m_vector<T>::operator=(m_vector<T>&& a){}
}