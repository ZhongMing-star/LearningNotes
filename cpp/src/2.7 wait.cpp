#include <iostream>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <chrono>

using namespace std;

mutex mtx;
condition_variable cv;
bool locked = false;

void processed()
{
    // 添加
    unique_lock<mutex> lock(mtx);
    cout << "sub process wait." << endl;

    while (!locked)
    {
        cv.wait(lock, (){ return locked; });
    }

    cout << "sub process Finshed !" << endl;
}

int main()
{
    thread p = thread(processed);

    // 睡眠1s
    this_thread::sleep_for(chrono::seconds(1));
    cout << "main sleep !" << endl;
    {
        unique_lock<mutex> lock(mtx);
        locked = true;

        cv.notify_one();
    }

    cout << "main processed Finshed !" << endl;
    return 0;
}