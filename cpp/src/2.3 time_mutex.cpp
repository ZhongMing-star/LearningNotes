#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>

using namespace std;

timed_mutex mtx;

void func()
{
    while (mtx.try_lock_for(chrono::milliseconds(200)))
    {
        cout << this_thread::get_id() << " :--\n"; 
    }
    
    this_thread::sleep_for(chrono::milliseconds(400));
    cout << "*" << this_thread::get_id() << "*\n";
    mtx.unlock();
}

int main()
{
    thread ths[10];
    for (int i=0; i<10; i++) ths[i] = thread(func);

    for (auto &th : ths) th.join();

    return 0;
}