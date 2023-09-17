#include<iostream>
#include<thread>


using namespace std;

void hello(){
    this_thread::sleep_for(chrono::seconds(5));
    cout << "Hello World!" << endl;
}
int main(int argc, char const *argv[]){
    thread t1(hello);
    thread t2(hello);
    t1.join();
    t2.join();
    return 0;
}