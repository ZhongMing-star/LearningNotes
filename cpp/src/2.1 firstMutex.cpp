#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

volatile int count(0);
mutex mtx;

void func()
{
    cout << "thread id " << this_thread::get_id() << " begin" << endl;

    if (mtx.try_lock())
    {
        for (int i = 0; i < 10; i++)
        {
            ++count;
        }
    }

    cout << "thread id " << this_thread::get_id() << " end" << endl;
    mtx.unlock();
}

int main()
{
    thread th[10];
    for (int i = 0; i < 10; i++)
    {
        th[i] = thread(func);
    }

    for (auto &t : th)
        t.join();

    cout << "final count = " << count << endl;
}