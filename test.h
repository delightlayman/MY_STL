#include "string.h"
#include "vector.h"
#include "list.h"
//my string
using MY_STL::m_string;
using MY_STL::simple_s;

using MY_STL::m_vector;

using MY_STL::m_list;
//my vector

void test_1(){
  m_string s1(10);
  m_string s2("hello");
  m_string s3 = s2 + s1 + "' '+'w'"+" sda "+" aadd "+'b';
  cout<<s3;
  s1+=s2;
  cout<<s1;
  s1+='c';
  cout<<s1;
  s1.pop_back();
  cout<<s1;

  s1.reverse();
  cout<<s1;
  s1.resize(5);
  cout<<s1;
  s1.resize(10);
  cout<<s1;
  //  s1.insert(5,'k' );
  //  cout<<s1;
  //  s1.insert(9,'a' );
  //  cout<<s1;
  //  s1.insert(15,'p' );
  //  cout<<s1;
  s1.insert(0,"wahaha");
  cout<<s1;
  s1.insert(0," heiheihei ");
  cout<<s1;
  //s1.insert(5," wahaha");
  //  cout<<s1;
  //  s1.insert(5," heiheihei ");
  //  cout<<s1;
  //  s1.insert(5," heiheihei ");
  //  cout<<s1;
  //  s1.insert(5," heiheihei ");
  s1.insert(0,m_string("sadada "));
  cout<<s1;
}
void test_2(){
  m_string s1(" world");
  m_string s2("hello");
  m_string s3('c'+ s2);//返回值rvo优化
  m_string s4;

  //s3=s2;
  s4=s3+s2;
  //强制触发移动构造
  m_string s5=m_string("aniya ")+"wakuwaku";
  m_string s6="wakuwaku "+m_string("aniya");
  m_string s7='a'+m_string(" aniya");

  s1=s2=s7;
  cout<<s1;
  cout<<s2;
  cout<<s3;
  cout<<s4;
  cout<<s5;
  cout<<s6;
  cout<<s7;
    
}
void test_3(){
  m_string firstlevel ("com");
  m_string secondlevel ("cplusplus");
  //m_string scheme ("http://");
  m_string hostname;
  //m_string url;

  cout<< firstlevel;
  cout<< secondlevel;
  //cout<< scheme;
  cout<< hostname;
  //cout<< url;

  //hostname = "www." + secondlevel+".com"+".call"+"waho"+secondlevel;------可行
  //问题在m_string与多个单字符相加
  //等价于：operator+(operator+(operator+('w', secondlevel), '.'), "com");
  hostname = 'w' + secondlevel + '.'+'a' +'c' + firstlevel;
  cout << hostname<<endl;
  //url = scheme + hostname;

  //cout << url;
}

void test_4(){
  std::string firstlevel ("com");
  std::string secondlevel ("cplusplus");
  std::string scheme ("http://");
  std::string hostname;
  std::string url;

  hostname = "www." + secondlevel + '.'+'a' +'c'+ firstlevel;
  url = scheme + hostname;

  std::cout << url << '\n';
}
void test_5(){
  m_string s1;
  s1.push_back('z');
  s1.push_back('a');
  s1.push_back(' ');
  s1.push_back('w');
  s1.push_back('a');
  s1.push_back('l');
  s1.push_back('u');
  s1.push_back('d');
  s1.push_back('0');
  cout<<s1;
   
}


void vector_test_1(){
    m_vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    v.push_back(6);
    v.push_back(6);
    v.push_back(6);
    v.push_back(6);

    v.resize(20);
    size_t cnt = 0;
    for (int a : v) {
        cout << a << " ";
        cnt++;
    }
    cout << endl << "count:" << cnt <<"size: " << v.size()<<"capacity: "<<v.capacity() << endl;

    
    cnt = 0;
    v.resize(50,'a');
    for (int a : v) {
        cout << a << " ";
        cnt++;
    }
    cout << endl << "count:" << cnt << " size: " << v.size() << " capacity: " << v.capacity() << endl;



    cnt = 0;
    v.resize(200,88);
    for (int a : v) {
        cout << a << " ";
        cnt++;
    }
    cout << endl << "count:" << cnt << " size: " << v.size() << " capacity: " << v.capacity() << endl;



    cnt = 0;
    v.resize(355,55);
    for (int a : v) {
        cout << a << " ";
        cnt++;
    }
    cout << endl << "count:" << cnt << " size: " << v.size() << " capacity: " << v.capacity() << endl;
    cnt = 0;
    v.resize(100, 55);
    for (int a : v) {
        cout << a << " ";
        cnt++;
    }
    cout << endl << "count:" << cnt << " size: " << v.size() << " capacity: " << v.capacity() << endl;


    v.reserve(100);
    cout << endl << "count:" << cnt << " size: " << v.size() << " capacity: " << v.capacity() << endl;
    v.reserve(1000);
    cout << endl << "count:" << cnt << " size: " << v.size() << " capacity: " << v.capacity() << endl;
    v.reserve(10000);
    cout << endl << "count:" << cnt << " size: " << v.size() << " capacity: " << v.capacity() << endl;
}


void vector_test_2() {
    m_vector<int> v(10, 1);
    v.reserve(100);
    int arr[] = { 1,2,3,4,5,6,7,8,9,10 };
    m_vector<int> v1(arr, 10);

    m_vector<int> v2(v1);

    m_vector<int> v3 = v2;
    m_vector<int> v4 = v3;


    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;
    cout <<v.size()<<" " << v.capacity() << endl;

    for (int i = 0; i < v1.size(); i++) {
        cout << v1[i] << " ";
    }
    cout << endl;
    cout << v1.size() << " " << v1.capacity() << endl;

    for (int i = 0; i < v2.size(); i++) {
        cout << v2[i] << " ";
    }
    cout << endl;
    cout << v2.size() << " " << v2.capacity() << endl;

    for (int i = 0; i < v3.size(); i++) {
        cout << v3[i] << " ";
    }
    cout << endl;
    cout << v3.size() << " " << v3.capacity() << endl;
}

void vector_test_3() {
    int arr[] = { 1,2,3,4,5,6,7,8,9,10 };
    int arr1[] = { 11,12,13,14,15,16,17,18,19,20 };
    m_vector<int> v1(arr, 10);
    v1.pop_back();
    v1.pop_back();
    v1.pop_back();
    v1.pop_back();
    v1.pop_back();
    v1.pop_back();

    v1.insert(1, arr1, 5);
    v1.insert(1, arr1, 5);
    v1.insert(1, arr1, 5);
    v1.insert(1,arr1,5);

    v1.erase(1, 5);
    v1.erase(1, 5);
    v1.erase(1, 5);


    m_vector<int>::iterator it = v1.begin();
    while (it != v1.end()) {
        cout << *it << " ";
        ++it;
    }
    cout << endl;


}

void simple_s_test() {
    const char* s = "you can really code";
    simple_s s1(s);
    simple_s s2(s1);
    simple_s s3;
    s3=s2;

    cout << s1 << endl;
    cout << s2 << endl;
    cout << s3 << endl;

}

class date{
    private:
    // size_t _y=1;
    // size_t _m=1;
    // size_t _d=1;
    size_t _y;
    size_t _m;
    size_t _d;
    public:
    date(size_t y=0,size_t m=1,size_t d=1):_y(y),_m(m),_d(d){}

    friend ostream& operator<<(ostream& os,const date& d){
        cout<<d._y<<" "<<d._m<<" "<<d._d<<" ";
        return os;
    }

};

void list_test1(){


    m_list<int> ls;

    ls.push_back(1);
    ls.push_back(2);
    ls.push_back(3);
    ls.push_back(4);
    ls.push_back(5);
    ls.push_front(6);
    ls.push_front(7);
    ls.push_front(8);
    ls.push_front(9);


    ls.printf_list();


    m_list<int> a(ls);
    a.printf_list();

    m_list<int> b;
    b=a;
    b.printf_list();

    m_list<int> c(10);
    c.printf_list();
    m_list<int> d(10,10);
    d.printf_list();

    c.swap(d);
    c.printf_list();
    d.printf_list();



    // m_list<date> ls_1;
    // ls_1.push_back(date());
    // ls_1.push_back(date(1,2,3));
    // ls_1.push_back(date(4,5,6));
    // ls_1.push_back(date(7,8,9));

    // ls_1.printf_list();

    // ls_1.clear();

    // ls_1.printf_list();
    //for(){}

}

void list_test2(){
    m_list<int> e(5,5);
    e.printf_list();
    
    e.insert(e.begin(),2);
    e.insert(e.begin(),2);
    e.insert(e.begin(),2);
    e.insert(e.begin(),2);
    e.insert(e.begin(),2);
    e.printf_list();

    e.erase(e.begin(),e.begin()+2);
    e.printf_list();

    e.pop_back();
    e.pop_front();
    e.printf_list();
    e.insert(e.begin()+2,3);
    e.insert(e.begin()+2,3);
    e.insert(e.begin()+2,3);

    e.pop_back();
    e.pop_front();
    e.printf_list();

    m_list<int> f;
    f.push_back(1);
    f.push_back(2);
    f.push_back(3);
    f.push_back(4);
    f.push_back(5);
    f.push_back(6);
    cout<<*e.insert(e.begin(),f.begin(),f.end())<<endl;
    e.printf_list();
    e.erase(e.begin()+1,e.begin()+3);
    e.printf_list();
}