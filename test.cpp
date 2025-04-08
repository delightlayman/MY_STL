#include "string.h"
using My_STL::m_string;
using My_STL::simple_s;
using std::cout;
using std::cin;
using std::endl;

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
int main(){
  test_1();
  //test_2();
  //test_3();
  //test_4();
  //test_5();
}