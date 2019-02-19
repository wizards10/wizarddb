#include <iostream>
using namespace std;
struct msg
{
    char ip[8192*1024 + 1];
};
void test()
{
    msg Msg;
    return;
}
int main()
{
    msg Msg;
    cout<<"msg is "<< sizeof(Msg)<<"bytes "<<endl;
    return 0;
}