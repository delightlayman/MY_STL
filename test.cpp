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

    cout<<s1<<endl;
    cout<<s2<<endl;
    cout<<s3<<endl;
 }
int main(){
    test_1();
    
}