#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

mutex mtx;


void func()
{
    lock_guard<mutex> lgc(mtx);

    // if (mtx.try_lock())
    {
        cout << this_thread::get_id() << "lock !\n";
    }
}

int main()
{
    thread threads[10];

    for (int i=0; i<10; i++) threads[i] = thread(func);

    for (auto &th : threads) th.join();

    if(mtx.try_lock())
    {
        cout << " main proces lock ! ";
    }
    else
    {
        cout << "lock filed !";
    }

    return 0;
}