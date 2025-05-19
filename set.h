#pragma once
#include "MY_STL.h"

namespace MY_STL{
    //key提取函数:从数据类型T中提取，关键字key
    //适用key即是val
    template<class K>
    struct key_identity{
        K& operator()(const K& k){ return k;}
    };
}