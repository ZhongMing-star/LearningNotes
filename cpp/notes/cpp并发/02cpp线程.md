# C++  线程

# 0. 概述

C++ 是一种通用的编程语言，支持多线程编程。多线程编程是指同时执行多个线程（独立的执行路径），以提高程序的性能和响应能力。在 C++ 中，你可以使用多种方式来实现多线程编程。

以下是在 C++ 中实现多线程的两种常见方法：

1. 使用标准库的 `<thread>` 头文件：C++11 引入了 `<thread>` 头文件，其中包含了创建和管理线程的类和函数。你可以通过创建 `std::thread` 对象来启动一个新线程，并指定要执行的函数或可调用对象。下面是一个简单的示例：

```cpp
#include <iostream>
#include <thread>

// 线程执行的函数
void threadFunction() {
    // 线程执行的代码
    std::cout << "Hello from thread!" << std::endl;
}

int main() {
    // 创建并启动新线程
    std::thread t(threadFunction);
    
    // 主线程继续执行自己的代码
    std::cout << "Hello from main!" << std::endl;
    
    // 等待新线程执行完毕
    t.join();
    
    return 0;
}
```

在上面的示例中，`std::thread` 类被用来创建一个新线程，并通过 `t.join()` 等待新线程执行完毕。

2. 使用 OpenMP：OpenMP 是一个支持并行计算的开放标准，它可以在 C++ 编译器中使用。通过使用 OpenMP，你可以通过添加一些指令和注释来实现多线程并行化。下面是一个使用 OpenMP 的示例：

```cpp
#include <iostream>
#include <omp.h>

int main() {
    // 设置线程数目
    omp_set_num_threads(4);

    // 并行执行的代码块
    #pragma omp parallel
    {
        int threadID = omp_get_thread_num();
        std::cout << "Hello from thread " << threadID << "!" << std::endl;
    }

    std::cout << "Hello from main!" << std::endl;

    return 0;
}
```

在上面的示例中，`#pragma omp parallel` 告诉编译器应该并行执行接下来的代码块。`omp_get_thread_num()` 函数返回当前线程的 ID。

无论使用哪种方法，多线程编程都需要小心处理共享数据的同步和互斥访问，以避免数据竞争和其他并发问题。你可以使用互斥锁（`std::mutex`）和其他同步原语来控制对共享数据的访问。

请注意，多线程编程可以复杂且容易出错。确保你熟悉多线程编程的概念和最佳实践，并在编写多线程代码时进行充分的测试和调试。

## 1. `<thread>` 头文件摘要

`<thread>` 头文件声明了 `std::thread `线程类及 `std::swap` (交换两个线程对象)辅助函数。另外命名空间 `std::this_thread` 也声明在 `<thread>` 头文件中。下面是 C++11 标准所定义的 `<thread>` 头文件摘要：

```c++
namespace std {
    #define __STDCPP_THREADS__ __cplusplus
    class thread;
    void swap(thread& x, thread& y);
    namespace this_thread {
        thread::id get_id();
        void yield();

        template <class Clock, class Duration>
        void sleep_until(const chrono::time_point<Clock, Duration>& abs_time);

        template <class Rep, class Period>
        void sleep_for(const chrono::duration<Rep, Period>& rel_time);
    }        
}
```

`<thread>` 头文件主要声明了 `std::thread` 类，另外在 `std::this_thread` 命名空间中声明了 `get_id`，`yield`，`sleep_until` 以及 `sleep_for` 等辅助函数，本章稍微会详细介绍 `std::thread` 类及相关函数。

## 2. this_thread 相关函数

`std::this_thread` 是 C++ 标准库中的命名空间，提供了与当前线程相关的函数和工具。你可以使用 `std::this_thread` 来执行以下操作：

### get_id()

1. `std::this_thread::get_id()`：返回当前线程的唯一标识符，这个标识符可以用于区分不同的线程。

```cpp
#include <iostream>
#include <thread>

int main() {
    std::thread::id threadId = std::this_thread::get_id();
    std::cout << "Current thread ID: " << threadId << std::endl;
    
    return 0;
}
```

### sleep_for()

2. `std::this_thread::sleep_for()`：暂停当前线程的执行一段指定的时间。

```cpp
#include <iostream>
#include <thread>
#include <chrono>

int main() {
    std::cout << "Before sleep" << std::endl;
    
    std::this_thread::sleep_for(std::chrono::seconds(2)); // 暂停 2 秒
    
    std::cout << "After sleep" << std::endl;
    
    return 0;
}
```

### yield()

3. `std::this_thread::yield()`：让出当前线程的执行，给其他线程更多的执行机会。

```cpp
#include <iostream>
#include <thread>

void threadFunction() {
    std::cout << "Thread executing" << std::endl;
    std::this_thread::yield(); // 让出执行
    std::cout << "Thread resumed" << std::endl;
}

int main() {
    std::thread t(threadFunction);
    t.join();
    
    return 0;
}
```

### sleep_until()

4. `std::this_thread::sleep_until()`：暂停当前线程的执行，直到指定的时间点。

```cpp
#include <iostream>
#include <thread>
#include <chrono>

int main() {
    std::cout << "Before sleep" << std::endl;
    
    std::chrono::system_clock::time_point wakeupTime = std::chrono::system_clock::now() + std::chrono::seconds(5);
    std::this_thread::sleep_until(wakeupTime); // 暂停直到指定的时间点
    
    std::cout << "After sleep" << std::endl;
    
    return 0;
}
```

这些函数和工具可以帮助你管理当前线程的行为，包括休眠、让出执行、获取线程 ID 等等。

## 3. `std::thread` 详解

### `std::thread` 构造函数

| 默认构造函数 (1)           | thread() noexcept;                                           |
| -------------------------- | ------------------------------------------------------------ |
| 初始化构造函数 (2)         | template <class Fn, class... Args> explicit thread(Fn&& fn, Args&&... args); |
| 拷贝构造函数 [deleted] (3) | thread(const thread&) = delete;                              |
| Move 构造函数 (4)          | thread(thread&& x) noexcept;                                 |

1. 默认构造函数(1)，创建一个空的 `std::thread` 执行对象。
2. 初始化构造函数(2)，创建一个 `std::thread` 对象，该 `std::thread` 对象可被 `joinable`，新产生的线程会调用 `fn` 函数，该函数的参数由 `args` 给出。
3. 拷贝构造函数(被禁用)(3)，意味着 `std::thread` 对象不可拷贝构造。
4. Move 构造函数(4)，move 构造函数(move 语义是 C++11 新出现的概念，详见附录)，调用成功之后 `x` 不代表任何 `std::thread` 执行对象。

> 注意：可被 `joinable` 的 `std::thread` 对象必须在他们销毁之前被主线程 `join` 或者将其设置为 `detached`.

std::thread 各种构造函数例子如下（[参考](http://en.cppreference.com/w/cpp/thread/thread/thread)）：

```cpp
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
```

### `std::thread` 赋值操作

| Move 赋值操作 (1)          | thread& operator=(thread&& rhs) noexcept;  |
| -------------------------- | ------------------------------------------ |
| 拷贝赋值操作 [deleted] (2) | thread& operator=(const thread&) = delete; |

1. Move 赋值操作(1)，如果当前对象不可 `joinable`，需要传递一个右值引用(`rhs`)给 `move` 赋值操作；如果当前对象可被 `joinable`，则会调用 `terminate`() 报错。
2. 拷贝赋值操作(2)，被禁用，因此 `std::thread` 对象不可拷贝赋值。

请看下面的例子：

```cpp
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

```

## 4.其他成员函数

> 本小节例子来自 [http://en.cppreference.com](http://en.cppreference.com/w/cpp/thread/thread)

### get_id()

- `get_id`: 获取线程 ID，返回一个类型为 `std::thread::id` 的对象。请看下面例子：

  ```
    #include <iostream>
    #include <thread>
    #include <chrono>
     
    void foo()
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
     
    int main()
    {
        std::thread t1(foo);
        std::thread::id t1_id = t1.get_id();
     
        std::thread t2(foo);
        std::thread::id t2_id = t2.get_id();
     
        std::cout << "t1's id: " << t1_id << '\n';
        std::cout << "t2's id: " << t2_id << '\n';
     
        t1.join();
        t2.join();
    }
  ```

### joinable()

- `joinable`: 检查线程是否可被 join。检查当前的线程对象是否表示了一个活动的执行线程，由默认构造函数创建的线程是不能被 join 的。另外，如果某个线程 已经执行完任务，但是没有被 join 的话，该线程依然会被认为是一个活动的执行线程，因此也是可以被 join 的。

  ```cpp
    #include <iostream>
    #include <thread>
    #include <chrono>
     
    void foo()
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
     
    int main()
    {
        std::thread t;
        std::cout << "before starting, joinable: " << t.joinable() << '\n';
     
        t = std::thread(foo);
        std::cout << "after starting, joinable: " << t.joinable() << '\n';
     
        t.join();
    }
  ```

### join()

- `join`: Join 线程，调用该函数会阻塞当前线程，直到由 `*this` 所标示的线程执行完毕 join 才返回。

  ```cpp
    #include <iostream>
    #include <thread>
    #include <chrono>
     
    void foo()
    {
        // simulate expensive operation
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
     
    void bar()
    {
        // simulate expensive operation
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
     
    int main()
    {
        std::cout << "starting first helper...\n";
        std::thread helper1(foo);
     
        std::cout << "starting second helper...\n";
        std::thread helper2(bar);
     
        std::cout << "waiting for helpers to finish..." << std::endl;
        helper1.join();
        helper2.join();
     
        std::cout << "done!\n";
    }
  ```


### detach()

- `detach`: Detach 线程。 将当前线程对象所代表的执行实例与该线程对象分离，使得线程的执行可以单独进行。一旦线程执行完毕，它所分配的资源将会被释放。

调用 detach 函数之后：

1. `*this` 不再代表任何的线程执行实例。
2. joinable() == false
3. get_id() == std:🧵:id()

另外，如果出错或者 `joinable() == false`，则会抛出 `std::system_error`.

```cpp
    #include <iostream>
    #include <chrono>
    #include <thread>
     
    void independentThread() 
    {
        std::cout << "Starting concurrent thread.\n";
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::cout << "Exiting concurrent thread.\n";
    }
     
    void threadCaller() 
    {
        std::cout << "Starting thread caller.\n";
        std::thread t(independentThread);
        t.detach();
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "Exiting thread caller.\n";
    }
     
    int main() 
    {
        threadCaller();
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
```

### swap()

- `swap`: Swap 线程，交换两个线程对象所代表的底层句柄(underlying handles)。

  ```cpp
    #include <iostream>
    #include <thread>
    #include <chrono>
     
    void foo()
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
     
    void bar()
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
     
    int main()
    {
        std::thread t1(foo);
        std::thread t2(bar);
     
        std::cout << "thread 1 id: " << t1.get_id() << std::endl;
        std::cout << "thread 2 id: " << t2.get_id() << std::endl;
     
        std::swap(t1, t2);
     
        std::cout << "after std::swap(t1, t2):" << std::endl;
        std::cout << "thread 1 id: " << t1.get_id() << std::endl;
        std::cout << "thread 2 id: " << t2.get_id() << std::endl;
     
        t1.swap(t2);
     
        std::cout << "after t1.swap(t2):" << std::endl;
        std::cout << "thread 1 id: " << t1.get_id() << std::endl;
        std::cout << "thread 2 id: " << t2.get_id() << std::endl;
     
        t1.join();
        t2.join();
    }
  ```

  执行结果如下：

```
thread 1 id: 1892
thread 2 id: 2584
after std::swap(t1, t2):
thread 1 id: 2584
thread 2 id: 1892
after t1.swap(t2):
thread 1 id: 1892
thread 2 id: 2584
```

### native_handle()

- `native_handle`: 返回 native handle（由于 `std::thread` 的实现和操作系统相关，因此该函数返回与 `std::thread` 具体实现相关的线程句柄，例如在符合 Posix 标准的平台下(如 Unix/Linux)是 Pthread 库）。

  ```cpp
  #include <thread>
  #include <iostream>
  #include <chrono>
  #include <cstring>
  #include <pthread.h>
  #include <mutex>
  
  std::mutex iomutex;
  void f(int num)
  {
      std::this_thread::sleep_for(std::chrono::seconds(1));
  
      sched_param sch;
      int policy;
      pthread_getschedparam(pthread_self(), &policy, &sch);
      std::lock_guard<std::mutex> lk(iomutex);
      std::cout << "Thread " << num << " is executing at priority "
                << sch.sched_priority << '\n';
  }
  
  int main()
  {
      std::thread t1(f, 1), t2(f, 2);
  
      sched_param sch;
      int policy;
      pthread_getschedparam(t1.native_handle(), &policy, &sch);
      sch.sched_priority = 20;
      if (pthread_setschedparam(t1.native_handle(), SCHED_FIFO, &sch))
      {
          std::cout << "Failed to setschedparam: " << std::strerror(errno) << '\n';
      }
  
      t1.join();
      t2.join();
  }
  ```

  

执行结果如下：

```
Thread 2 is executing at priority 0
Thread 1 is executing at priority 20
```

### hardware_concurrency()

- `hardware_concurrency` [static]: 检测硬件并发特性，返回当前平台的线程实现所支持的线程并发数目，但返回值仅仅只作为系统提示(hint)。

  ```cpp
    #include <iostream>
    #include <thread>
     
    int main() {
        unsigned int n = std::thread::hardware_concurrency();
        std::cout << n << " concurrent threads are supported.\n";
    }
  ```

## `this_thread` 命名空间中相关辅助函数介绍

### get_id()

- get_id: 获取线程 ID。

  ```cpp
  #include <iostream>
  #include <thread>
  #include <chrono>
  #include <mutex>
  
  std::mutex g_display_mutex;
  
  void foo()
  {
      std::thread::id this_id = std::this_thread::get_id();
  
      g_display_mutex.lock();
      std::cout << "thread " << this_id << " sleeping...\n";
      g_display_mutex.unlock();
  
      std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  
  int main()
  {
      std::thread t1(foo);
      std::thread t2(foo);
  
      t1.join();
      t2.join();
  }
  ```

### yield()

- yield: 当前线程放弃执行，操作系统调度另一线程继续执行。

  ```cpp
    #include <iostream>
    #include <chrono>
    #include <thread>
     
    // "busy sleep" while suggesting that other threads run 
    // for a small amount of time
    void little_sleep(std::chrono::microseconds us)
    {
        auto start = std::chrono::high_resolution_clock::now();
        auto end = start + us;
        do {
            std::this_thread::yield();
        } while (std::chrono::high_resolution_clock::now() < end);
    }
     
    int main()
    {
        auto start = std::chrono::high_resolution_clock::now();
     
        little_sleep(std::chrono::microseconds(100));
     
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        std::cout << "waited for "
                  << std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count()
                  << " microseconds\n";
    }
  ```


### sleep_until()

- sleep_until: 线程休眠至某个指定的时刻(time point)，该线程才被重新唤醒。

  ```cpp
    template< class Clock, class Duration >
    void sleep_until( const std::chrono::time_point<Clock,Duration>& sleep_time );
  ```


### sleep_for()

- sleep_for: 线程休眠某个指定的时间片(time span)，该线程才被重新唤醒，不过由于线程调度等原因，实际休眠时间可能比 `sleep_duration` 所表示的时间片更长。

  ```cpp
    template< class Rep, class Period >
    void sleep_for( const std::chrono::duration<Rep,Period>& sleep_duration );
  
    #include <iostream>
    #include <chrono>
    #include <thread>
     
    int main()
    {
        std::cout << "Hello waiter" << std::endl;
        std::chrono::milliseconds dura( 2000 );
        std::this_thread::sleep_for( dura );
        std::cout << "Waited 2000 ms\n";
    }
  ```

  执行结果如下：

```cpp
Hello waiter
Waited 2000 ms
```
