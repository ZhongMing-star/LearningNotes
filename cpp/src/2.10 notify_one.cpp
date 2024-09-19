#include <iostream>
#include <condition_variable>
#include <mutex>
#include <thread>

std::condition_variable cv;
std::mutex mtx;
bool ready = false;

void worker(int id)
{
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [] { return ready; });
    std::cout << "Worker " << id << " is awake." << std::endl;
}

int main()
{
    std::thread t1(worker, 1);
    std::thread t2(worker, 2);
    std::thread t3(worker, 3);

    std::this_thread::sleep_for(std::chrono::seconds(2));

    {
        std::lock_guard<std::mutex> lock(mtx);
        ready = true;
        // 唤醒一个线程
        // cv.notify_all();
        cv.notify_one();
    }

    t1.join();
    t2.join();
    t3.join();

    return 0;
}