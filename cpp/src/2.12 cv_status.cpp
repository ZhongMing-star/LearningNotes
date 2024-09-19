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
    auto timeout_time = chrono::system_clock::now() + chrono::seconds(1);
    auto status = cv.wait_until(loac, timeout_time, []
                                { return readed; });
    if (status)
    {
        std::cout << "Worker thread notified." << std::endl;
    }
    else
    {
        std::cout << "Timeout occurred." << std::endl;
    }
    return 0;
}