#include<iostream>
#include<thread>

using namespace std;

void test()
{
    cout << "test thread ... " << endl;
    this_thread::sleep_for(chrono::seconds(4));
}
int main(int argc, char * argv[])
{
    cout << "test thread pour UCE prog paralelle" << endl;
    thread t(test);
    t.join();
    return 0;
}