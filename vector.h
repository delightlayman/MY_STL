#pragma once
#include "MY_STL.h"

namespace MY_STL{
    template <class T>
    class m_vector{
        private:
            iterator _start;
            iterator _finish;
            iterator _end_of_storage;
        public:
            //constructor
            m_vector();
            explicit m_vector(int *arr);
            m_vector(const m_vector& a);
            m_vector(m_vector&& a);
            //destructor
            ~m_vector();
            //operator =
            operator=(const m_vector& a);
            operator=(m_vector&& a);

    };
}