#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

using namespace std;

// 全局线程锁
mutex mtx;
// 条件信号
condition_variable cv;
// 最大buffer_size
const int MAX_BUFFER_SIZE = 3;
// 设置缓存区
queue<int> buffer;

void producerThread()
{
    unique_lock<mutex> lock(mtx);
    for (int i = 0; i < 10; i++)
    {
        /*
            wait(unique_lock<mutex>& __lock, _Predicate __p)
            {
                while (!__p()) wait(__lock);
            }
        */
        // 满足谓词函数的条件，才加锁
        cv.wait(lock, []
                { return buffer.size() < MAX_BUFFER_SIZE; });

        buffer.push(i);
        cout << "produced : " << i << "; buffer size : " << buffer.size() << endl;

        cv.notify_one();
    }
}

void consumerThread()
{
    unique_lock<mutex> lock(mtx);
    for (int i = 0; i < 10; i++)
    {
        cv.wait(lock, []
                { return !buffer.empty(); });

        cout << "consumed : " << buffer.front() << "; buffer size : " << buffer.size() << endl;
        buffer.pop();

        cv.notify_one();
    }
}

int main()
{
    thread producer = thread(producerThread);
    thread consumer = thread(consumerThread);

    producer.join();
    consumer.join();
}