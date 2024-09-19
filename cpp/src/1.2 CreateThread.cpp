/*
<iostream>：这个头文件提供了对输入和输出流的支持，包括 std::cout 和 std::cin。你可以使用它来进行基本的输入和输出操作。

<utility>：这个头文件提供了一些实用工具，包括一些模板类和函数，例如 std::pair，用于存储一对值；std::move，用于将对象转移的函数；以及其他一些辅助函数。

<thread>：这个头文件提供了多线程编程所需的类和函数。其中包括 std::thread 类，用于创建和管理线程；std::this_thread 命名空间，包含了与当前线程相关的函数；以及其他一些与线程相关的工具。

<chrono>：这个头文件定义了一些与时间和时间间隔相关的类和函数。你可以使用它来进行时间的测量和计算，例如计时操作，暂停线程一段时间等。

<functional>：这个头文件提供了一些与函数对象和函数指针相关的类和函数。其中包括 std::function 类，用于封装可调用对象；std::bind 函数，用于绑定参数到函数对象；以及其他一些操作函数对象的工具。

<atomic>：这个头文件提供了一些原子操作的支持。原子操作是指在执行过程中不会被中断的操作，可以用于实现线程安全的访问和修改共享数据。std::atomic 类模板是该头文件中的一个重要类，用于创建原子类型的对象。
*/
#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>

using namespace std;

void func1(int repate_nums)
{
    for (int i = 0; i < 5; i++)
    {
        cout << "Thread " << this_thread::get_id() << ", get repate_nums = " << repate_nums << endl;
        this_thread::sleep_for(chrono::milliseconds(10));
    }
}

void func2(int &repate_nums)
{
    for (int i = 0; i < 5; i++)
    {
        cout << "Thread " << this_thread::get_id() << ", get repate_nums = " << repate_nums << endl;
        ++ repate_nums;
        this_thread::sleep_for(chrono::milliseconds(10));
    }
}


int main()
{
    int repate_nums = 0;
    // 创建四个进程
    thread t1;
    thread t2(func1, repate_nums + 1);
    thread t3(func2, std::ref(repate_nums));
    thread t4(std::move(t3));

    t2.join();
    t4.join();

    cout << "Final repate_nums = " << repate_nums << endl;

    return 0;
}
