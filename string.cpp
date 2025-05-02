#include "string.h"
using std::endl;
using std::cout;
using std::swap;
using std::min;
using std::move;//将左值显式转换为右值引用，标记该对象可被移动
namespace MY_STL {
    //constructor
    //默认1 用于存储'\0'
    m_string::m_string()
        :_s(new char[1]), _size(0), _capacity(0) {
        strcpy(_s, "");
        //cout << "dafault_constructor" << endl;
    }
    m_string::m_string(const char* str) {
        assert(str);
        _size = strlen(str);
        _capacity = _size;
        _s = new char[_size + 1];
        strcpy(_s, str);
        //cout << "constructor" << endl;
    }

    m_string::m_string(const m_string& s)
        //注意: new char[s._capacity + 1]而不是new char[s._size + 1],否则复制不完全，一般情况没有问题，极少数情况下：程序崩溃
        :_s(new char[s._capacity + 1]), _size(s._size), _capacity(s._capacity) {
        strcpy(_s, s._s);
        //memcpy(_s, s._s, _size + 1);
        //cout << "copy_constructor" << endl;

    }
    m_string::m_string(m_string&& s)noexcept
        :_s(s._s), _size(s._size), _capacity(s._capacity) {
        s._s = nullptr;
        //cout << "move_constructor" << endl;
    }

    m_string::m_string(size_t n, char c) :_s(new char[n + 1]), _size(n), _capacity(n) {
        int i = 0;
        while (i < n) {
            _s[i++] = c; 
        }
        _s[n] = '\0';
    }
    //destructor
    m_string::~m_string() {
        //cout << "~m_string:" << "this:" << (void*)this << " ,_s:" << (void*)_s << endl;
        delete[] _s;
        _s = nullptr;
        _size = 0;
        _capacity = 0;

        //cout<<"~m_string"<<endl;
    }
    //operator overloding
    //operator = copy+move
    m_string& m_string::operator=(const m_string& s) {
        if (this != &s) {
            char* tmp = new char[s._size + 1];
            strcpy(tmp, s._s);

            delete[] _s;
            _s = tmp;
            _size = s._size;
            _capacity = s._capacity;
        }
        //cout << "copy_assignment" << endl;

        return *this;
    }
    m_string& m_string::operator=(m_string&& s)noexcept {
        if (this != &s) {
            delete[] _s;
            _s = s._s;
            _size = s._size;
            _capacity = s._capacity;
            s._s = nullptr;
        }
        //cout << "move_assignment" << endl;
        return *this;
    }

    //relation operator
    bool m_string::operator<(const m_string& s)const {
        return strcmp(_s, s._s) < 0;
    }
    bool m_string::operator==(const m_string& s)const {
        return strcmp(_s, s._s) == 0;
    }
    bool m_string::operator>(const m_string& s)const {
        return strcmp(_s, s._s) > 0;
    }
    bool m_string::operator<=(const m_string& s)const {
        return *this < s || *this == s;
    }
    bool m_string::operator!=(const m_string& s)const {
        return !(*this == s);
    }

    bool m_string::operator>=(const m_string& s)const {
        return *this > s || *this == s;
    }
    //input and output
    ostream& operator<<(ostream& os, const m_string& s) {
        //os << "object: " << &s << ", _s:" << (void*)s._s << ", value:" << s._s << "," << s._size << "," << s._capacity << endl;
        os<<s._s;
        return os;
    }
    istream& operator>>(istream& is, m_string& s) {
        is >> s._s >> s._size >> s._capacity;
        return is;
    }

    //insert---add
    void m_string::push_back(char c) {
        //满空间增容
         if (_size == _capacity) {
             size_t len = _capacity ? (_capacity * 2) : 2;
             reserve(len);
         }
        _s[_size++] = c;
        _s[_size] = '\0';
    }
    void m_string::append(const char* str) {
        assert(str);
        size_t len = strlen(str);
        if (_capacity < _size + len) {
            reserve(_size + len);
        }
        //strcat依赖查找'\0'，再进行拼接
        strcpy(_s + _size, str);
        _size += len;
    }
    m_string& m_string::operator+=(char c) {
        push_back(c);
        return *this;
    }
    m_string& m_string::operator+=(const char* str) {
        assert(str);
        append(str);
        return *this;
    }
    m_string& m_string::operator+=(const m_string& s) {
        append(s._s);
        return *this;
    }


    //tmp局部对象
    //若有rvo和nrvo优化，可避免返值阶段的复制构造，若无优化，则触发复制构造---需注意：深复制
    //若 未深复制 将导致同一tmp._s多次delete释放 从而报错
    //可使用显示移动语义move(tmp)，直接转移资源，达成优化
    m_string m_string::operator+(char c)const {
        m_string tmp(*this);
        tmp.push_back(c);
        cout << tmp;
        return tmp;
    }
    m_string m_string::operator+(const char* str)const {
        assert(str);
        m_string tmp(*this);
        tmp.append(str);
        cout << tmp;
        return tmp;
    }
    m_string operator+(char c, const m_string& s) {
        m_string tmp;
        tmp.push_back(c);
        tmp.append(s._s);
        cout << tmp;
        return tmp;
    }
    m_string operator+(const char* str, const m_string& s) {
        assert(str);

        m_string tmp(str);
        return tmp += s;
    }
    m_string m_string::operator+(const m_string& s)const {
        m_string tmp(*this);
        tmp.append(s._s);
        return tmp;
    }

    m_string& m_string::insert(size_t pos, char c) {
        assert(pos<_size);
        if(_size==_capacity){
            size_t len=_capacity?_capacity*2:2;
            reserve(len);
        }
        for(int i=_size-1;i>pos;i--){
            _s[i+1]=_s[i];
        }
        _s[pos]=c;
        ++_size;
        return *this;
    }
    m_string& m_string::insert(size_t pos, const char* str) {
        assert(str);
        assert(pos<_size);
        size_t len=strlen(str);
        
        if(_size+len>_capacity){
            reserve(_size+len);
        }
        int j=_size;
        for(int i=_size-pos+1;i>0;i--){
            _s[j+len]=_s[j];//左右都有j，式子两侧j+len,j--求值顺序，据编译器实现而定，故结果未定义
            j--;
        }
        j=pos;
        for(int i=0;i<len;i++){
            _s[j++]=str[i];
        }
        _size+=len;
        return *this;
    }
    m_string& m_string::insert(size_t pos, const m_string& s) {
        insert(pos,s._s);
        return *this;
    }

    //erase---delete--remove
    void m_string::pop_back() {
        _s[--_size] = '\0';
    }
    m_string& m_string::erase(size_t pos, size_t len) {
        assert(pos < _size);
        int l = min(_size, pos + len);

        return *this;

    }
    //query---find
    const char& m_string::operator[](size_t pos)const {
        return _s[pos];
    }
    char& m_string::operator[](size_t pos) {
        return _s[pos];
    }

    char* m_string::find(char c)const {
        return strchr(_s, c);//指针相减为元素个数
    }
    char* m_string::find(const char* str)const {
        return strstr(_s, str);
    }
    char* m_string::find(const m_string& s)const {
        return strstr(_s, s._s);
    }

    m_string m_string::substr(size_t pos, size_t len)const {
        if (pos > _size) {
            cout << "function substr: parameter out of range";
            exit(1);
        }
        size_t l = min(_size, pos + len);
        m_string tmp;
        for (int i = pos; i < l; i++) {
            tmp.push_back(_s[i]);
        }
        return tmp;
    }

    size_t m_string::size()const {
        return _size;
    }
    size_t m_string::capacity()const {
        return _capacity;
    }
    // //modify
    //反转字串
    m_string& m_string::reverse() {
        size_t len = strlen(_s);
        for (int i = 0, j = len - 1; i < j; ++i, --j) {
            swap(_s[i], _s[j]);
        }
        return *this;
    }
    //预留空间---不可用于初始化
    void m_string::reserve(size_t len) {
        if (len <= _capacity)
            return;

        _capacity = len;
        char* tmp = new char[_capacity + 1];
        strcpy(tmp, _s);

        delete[] _s;
        _s = tmp;
    }
    void m_string::resize(size_t len, char c) {

        if (len > _size && len <= _capacity) {
            for (int i = _size; i < len; i++)
                _s[i] = c;
        }
        if (len > _capacity) {
            _capacity = len;
            reserve(_capacity);
            for (int i = _size; i < len; i++)
                _s[i] = c;
        }
        _size = len;
        _s[_size] = '\0';
    }
    //c字串
    const char* m_string::c_str(const m_string& s) {
        return s._s;
    }


     //constructor
     simple_s::simple_s(const char* str) :_s(new char[strlen(str) + 1]) {
        strcpy(_s, str);
     }
     //传统写法
     //simple_s::simple_s(const simple_s& s){}
     //现代写法
     //注意未初始化的_s 用于交换会崩溃
     simple_s::simple_s(const simple_s& s)
         :_s(nullptr){
         simple_s tmp(s._s);
         ::swap(_s,tmp._s);
     }
     
     //destructor
     simple_s::~simple_s(){
        delete[] _s;
        _s = nullptr;
        cout << "~simple_s()" << endl;
     }
     //operator =
     //传统写法
     //simple_s& simple_s::operator=(const simple_s& s){}
     //现代写法
     simple_s& simple_s::operator=(simple_s s){
         ::swap(_s,s._s);
         return *this;
     }
}