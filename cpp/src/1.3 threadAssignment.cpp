#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include <functional>

using namespace std;

void func(int n)
{
    // 会使当前线程休眠 10 毫秒。
    // 在休眠期间，当前线程将暂时停止执行，然后在休眠时间结束后恢复执行。
    this_thread::sleep_for(chrono::milliseconds(10));

    cout << "thread id = " << this_thread::get_id()
         << " paused " << n << " seconds" << endl;
}

int main()
{

    thread threads[5];
    for (int i = 0; i<5; i++)
    {
        // 赋值操作
        threads[i] = thread(func, i);
    }

    cout << "Done spawning threads! Now wait for them to join\n" << endl;

    for(auto &t : threads)
    {
        t.join();
    }

    cout << "All programs are finished." << endl;

    return 0;
}
