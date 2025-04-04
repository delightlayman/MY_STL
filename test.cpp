#include "string.h"
using My_String::m_string;
using My_String::simple_s;
using std::cout;
using std::cin;
using std::endl;

 void test_1(){
    m_string s1;
    m_string s2("uccu");
    m_string s3(s2);

    cout<<s1;
    cout<<s2;
    cout<<s3;
    
    s1=s3;
    cout<<s1;
 }
int main(){
    size_t a=10;
    test_1();
    cout<<"hello"<<endl;
    cout<<a;
}