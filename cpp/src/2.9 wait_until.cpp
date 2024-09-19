#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

using namespace std;

mutex mtx;
condition_variable cv;
bool readed = false;

void work()
{
    this_thread::sleep_for(chrono::seconds(2));
    unique_lock<mutex> loac(mtx);
    readed = true;
    cv.notify_one();
}

int main()
{
    thread t = thread(work);

    unique_lock<mutex> loac(mtx);
    auto timeCheckpoint = chrono::system_clock::now() + chrono::seconds(3);
    if (cv.wait_until(loac, timeCheckpoint, []
                    { return readed; }))
    {
        cout << "Worker thread notified." << endl;
    }
    else
    {
        cout << "Timeout occurred." << endl;
    }

    return 0;
}