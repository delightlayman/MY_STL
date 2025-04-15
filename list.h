#pragma once
#include "MY_STL.h"

namespace MY_STL{
    template<class T>
    class m_list{
        public:
            typedef struct listnode{
                T data;
                pre_node;
                next_node;
            }node;
            typedef node* iterator;
            

        private:
    };
}