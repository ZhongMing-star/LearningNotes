#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;
volatile  int sharedData = 0;

void incrementData()
{
    std::unique_lock<std::mutex> lock(mtx);
    ++sharedData;
    lock.unlock(); // 手动解锁
    // 执行一些不需要互斥量保护的操作
    lock.lock(); // 手动重新锁定
    // 继续执行需要互斥量保护的操作
}

int main()
{
    std::thread ths[10];

    for (int i=0; i<10; i++) ths[i] = std::thread(incrementData);
    for (auto &th: ths) th.join();

    std::cout << "Final value of sharedData: " << sharedData << std::endl;

    return 0;
}