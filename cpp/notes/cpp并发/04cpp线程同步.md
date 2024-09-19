# 线程同步

[TOC]

# 条件变量与线程同步

本小节将介绍 C++11 标准中 `<condition_variable>` 头文件里面的类和函数。

`<condition_variable >` 头文件主要包含了与条件变量相关的类和函数。与条件变量相关的类包括 `condition_variable` 和 `condition_variable_any`，还有枚举类型`cv_status`。另外还包括函数 `notify_all_at_thread_exit()`。

条件变量（Condition Variable）是一种线程同步机制，用于在线程之间进行通信和协调。它通常与互斥锁（Mutex）结合使用，用于实现复杂的线程同步逻辑。

在多线程编程中，条件变量用于允许一个或多个线程等待某个特定条件的发生。当某个线程等待条件时，它会挂起自己的执行，直到其他线程通过特定操作（通常是修改共享变量的值）发出信号，通知条件已满足。一旦条件满足，被挂起的线程将被唤醒，可以继续执行。

条件变量通常与互斥锁一起使用，以确保多个线程之间的操作是线程安全的。互斥锁用于保护共享数据，而条件变量用于在特定条件下等待和通知线程。

条件变量提供了以下两个基本操作：

> 1. 等待（wait）：线程在条件变量上等待，直到条件满足。等待操作会自动释放关联的互斥锁，并将线程挂起。
> 2. 通知（notify）：线程发送通知信号，通知等待在条件变量上的某个线程条件已满足。通知操作会唤醒等待的线程，并重新获取关联的互斥锁。

通常，等待操作应该在循环中使用，以防止虚假唤醒（spurious wakeups）。虚假唤醒是指在条件未满足的情况下，等待的线程被唤醒。循环检查条件的状态，直到条件满足，可以确保避免虚假唤醒。

条件变量的使用可以帮助线程有效地等待和协调共享资源的访问，以避免竞争条件和提高多线程程序的性能和可靠性。然而，使用条件变量需要仔细考虑线程同步和并发访问的问题，以避免潜在的死锁和竞态条件等线程安全问题。

## 1 `<condition_variable>` 头文件摘要

```cpp
namespace std {
    class condition_variable;
    class condition_variable_any;
    void notify_all_at_thread_exit(condition_variable& cond, unique_lock<mutex> lk);
    enum class cv_status { no_timeout, timeout };
}    
```

### 2 condition_variable 类摘要

```cpp
namespace std {
    class condition_variable {
        public:    
            condition_variable();
            ~condition_variable();
            condition_variable(const condition_variable&) = delete;
            condition_variable& operator=(const condition_variable&) = delete;

            void notify_one() noexcept;
            void notify_all() noexcept;
            void wait(unique_lock<mutex>& lock);
            template <class Predicate>
            void wait(unique_lock<mutex>& lock, Predicate pred);

            template <class Clock, class Duration>
            cv_status wait_until(unique_lock<mutex>& lock,
                const chrono::time_point<Clock, Duration>& abs_time);

            template <class Clock, class Duration, class Predicate>
            bool wait_until(unique_lock<mutex>& lock,
                const chrono::time_point<Clock, Duration>& abs_time,
                Predicate pred);

            template <class Rep, class Period>
            cv_status wait_for(unique_lock<mutex>& lock,
                const chrono::duration<Rep, Period>& rel_time);

            template <class Rep, class Period, class Predicate>
            bool wait_for(unique_lock<mutex>& lock,
                const chrono::duration<Rep, Period>& rel_time,
                Predicate pred);
                
            typedef implementation-defined native_handle_type;
            native_handle_type native_handle();
    };
}
```

### 3 condition_variable_any 类摘要

```cpp
namespace std {
    class condition_variable_any {
        public:
            condition_variable_any();
            ~condition_variable_any();
            condition_variable_any(const condition_variable_any&) = delete;
            condition_variable_any& operator=(const condition_variable_any&) = delete;

            void notify_one() noexcept;
            void notify_all() noexcept;
            template <class Lock>
            void wait(Lock& lock);
            template <class Lock, class Predicate>
            void wait(Lock& lock, Predicate pred);

            template <class Lock, class Clock, class Duration>
            cv_status wait_until(Lock& lock, const chrono::time_point<Clock, Duration>& abs_time);

            template <class Lock, class Clock, class Duration, class Predicate>
            bool wait_until(Lock& lock, const chrono::time_point<Clock, Duration>& abs_time, Predicate pred);

            template <class Lock, class Rep, class Period>
            cv_status wait_for(Lock& lock, const chrono::duration<Rep, Period>& rel_time);

            template <class Lock, class Rep, class Period, class Predicate>
            bool wait_for(Lock& lock, const chrono::duration<Rep, Period>& rel_time, Predicate pred);
    };
}
```

## 2 条件变量详解

### 2.1 `condition_variable` 类介绍

`std::condition_variable`是C++标准库中的条件变量类，用于线程间的同步和通信。它提供了一种机制，允许一个或多个线程等待某个特定条件的发生，从而实现线程间的协调和同步。

条件变量是基于互斥锁（`std::mutex`）和通知机制实现的。通常，它与互斥锁一起使用，以确保线程安全。以下是`std::condition_variable`的一些重要特性和用法：

1. 等待和通知：
   - `wait()`: 线程调用`wait()`函数时，它会在条件变量上等待，同时释放与之关联的互斥锁。线程将一直等待，直到其他线程通过`notify_one()`或`notify_all()`函数发出通知信号，或者超时发生。
   - `notify_one()`: 通知等待在条件变量上的一个线程，使其从`wait()`函数中唤醒并继续执行。
   - `notify_all()`: 通知等待在条件变量上的所有线程，使它们从`wait()`函数中唤醒并继续执行。
2. 谓词函数：
   - `wait(lock, pred)`: 可以指定一个谓词函数作为第二个参数，用于检查等待条件是否满足。当谓词函数返回`false`时，`wait()`函数会继续等待。只有当谓词函数返回`true`时，线程才会从`wait()`函数中唤醒。
3. 超时等待：
   - `wait_for()`: 可以指定一个超时时间，使线程在等待一段时间后自动唤醒。如果超时时间到达而条件未满足，线程将从`wait_for()`函数中返回，并可以根据需要执行相应的逻辑。
   - `wait_until()`: 可以指定一个绝对时间点，使线程在指定时间点之前等待。如果指定的时间点到达而条件未满足，线程将从`wait_until()`函数中返回。
4. 使用注意事项：
   - 在使用条件变量时，通常需要与互斥锁一起使用，以保护共享数据的访问和修改。
   - 等待操作应该在循环中使用，以防止虚假唤醒（spurious wakeups）。
   - 在调用`wait()`函数之前，必须先获取互斥锁，否则会导致未定义的行为。
   - 线程在等待期间会自动释放互斥锁，并在被唤醒后重新获取互斥锁。

一个常见的案例是生产者-消费者问题，其中多个生产者线程和多个消费者线程共享一个缓冲区。生产者线程将数据放入缓冲区，而消费者线程从缓冲区中取出数据进行处理。

在这个案例中，可以使用条件变量来实现生产者线程和消费者线程之间的同步和通信。以下是一个简化的示例：

```cpp
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
        cout << "produced : " << i 
            << "; buffer size : " << buffer.size() << endl;

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

        cout << "consumed : " << buffer.front() 
            << "; buffer size : " << buffer.size() << endl;
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
```

在上述示例中，生产者线程负责生成数据并放入缓冲区，而消费者线程负责从缓冲区中取出数据进行处理。生产者线程和消费者线程通过互斥锁`mtx`和条件变量`cv`进行同步和通信。

生产者线程在生产数据之前，会先获取互斥锁`mtx`的所有权，然后检查缓冲区是否已满。如果缓冲区已满，生产者线程调用`cv.wait()`等待，直到消费者线程取走数据并通知它继续生产。一旦条件满足（缓冲区未满），生产者线程生成数据并放入缓冲区，然后通过`cv.notify_one()`通知消费者线程可以取数据了。

消费者线程在消费数据之前，也会先获取互斥锁`mtx`的所有权，然后检查缓冲区是否为空。如果缓冲区为空，消费者线程调用`cv.wait()`等待，直到生产者线程放入数据并通知它可以继续消费。一旦条件满足（缓冲区非空），消费者线程从缓冲区取出数据进行处理，然后通过`cv.notify_one()`通知生产者线程可以继续生产。

通过使用条件变量，生产者线程和消费者线程之间实现了有效的同步和通信，避免了过度的轮询和资源浪费。

### 2.2 `wati() `函数

在C++中，`wait()`函数是`std::condition_variable`类的成员函数，用于在线程中等待条件满足。

`std::condition_variable`是C++标准库中的条件变量类，用于线程间的同步和通信。`wait()`函数用于在条件变量上等待，并释放与之关联的互斥锁。

> `std::condition_variable`的`wait()`函数有两个重载版本，下面将逐个解释其参数的含义：
>
> 1. `wait(lock)`
>
>    - `lock`: 一个`std::unique_lock`对象或`std::lock_guard`对象，用于在等待期间保持互斥锁的所有权，并在等待期间自动释放互斥锁。在调用`wait()`函数之前，必须先获取互斥锁。
>    
>    这个版本的`wait()`函数等待条件变量的通知，并在等待期间释放互斥锁。当线程调用`wait(lock)`时，它会释放`lock`所关联的互斥锁，并进入等待状态，直到其他线程调用相应的`notify_one()`或`notify_all()`函数来通知等待线程。
>
> 2. `wait(lock, pred)`
>
>    - `lock`: 与第一个版本相同，一个`std::unique_lock`对象或`std::lock_guard`对象，用于在等待期间保持互斥锁的所有权。
>    - `pred`: 一个可调用的谓词函数（比如lambda函数、函数对象等），**用于检查等待条件是否满足。谓词函数的返回类型必须是`bool`**。
>    
>    这个版本的`wait()`函数在等待之前首先调用`pred`，并检查其返回值。**只有当谓词函数返回`false`时，线程才会进入等待状态。这样可以避免虚假唤醒（spurious wakeups）的问题。**<span style="color:blue">**当谓词函数返回`true`时，线程会继续执行后续的代码，而不会进入等待状态。**</span>
>
> 在使用`wait()`函数时，需要注意以下几点：
> - 在调用`wait()`函数之前，必须先获取互斥锁，否则会导致未定义的行为。
> - 线程在等待期间会自动释放互斥锁，并在被唤醒后重新获取互斥锁。
> - 为了避免虚假唤醒，通常将等待操作放在一个循环中，并使用谓词函数来检查等待条件是否满足。
> - 当条件变量的通知发生时，等待线程从`wait()`函数中返回，并重新获取互斥锁，继续执行后续代码。
>
> 通过合理使用`wait()`函数的参数，可以实现灵活而高效的线程同步和通信。

以下是`wait()`函数的常见用法：

```cpp
#include <iostream>
#include <thread>
#include <condition_variable>

std::condition_variable cv;
std::mutex mtx;
bool condition = false;

void workerThread()
{
    std::unique_lock<std::mutex> lock(mtx);
    while(!condition)
    {
        // 等待条件满足
        cv.wait(lock, []{ return condition; });
    }
    // 条件满足后执行的代码
    std::cout << "Condition is satisfied. Continuing execution." << std::endl;
}

int main()
{
    // 创建工作线程
    std::thread worker(workerThread);

    // 模拟一些操作
    std::this_thread::sleep_for(std::chrono::seconds(2));
    {
        std::lock_guard<std::mutex> lock(mtx);
        // 设置条件为真
        condition = true;
    }
    // 通知等待的线程条件已满足
    cv.notify_one();
    // 等待工作线程完成
    worker.join();
    return 0;
}
```

在上面的示例中，`workerThread()`函数是工作线程的入口点。它首先获取互斥锁`mtx`的所有权，然后使用`wait()`函数在条件变量`cv`上等待。`wait()`函数的第一个参数是互斥锁，用于保护条件变量和共享数据的访问。第二个参数是可调用对象，用于检查等待条件是否满足。当条件变量的`notify_one()`或`notify_all()`函数被调用时，线程将从`wait()`函数中唤醒，并继续执行。

在主线程中，我们模拟一些操作，然后设置条件为真，并通过`notify_one()`函数通知等待的线程条件已满足。最后，我们等待工作线程完成并加入（join）它。

需要注意的是，在使用`wait()`函数时，必须始终与互斥锁一起使用，以确保线程安全。`wait()`函数在等待期间会自动释放互斥锁，并在线程被唤醒后重新获取互斥锁。

此外，`wait()`函数还有其他重载形式，可以接受自定义的超时时间或等待条件的谓词函数。有关更多详细信息，请参阅C++的条件变量文档。

### 2.3 `wait_for() `函数

`wait_for` 是 `std::condition_variable` 类的一个成员函数，用于在指定时间段内等待条件变量的通知。

`wait_for` 函数有两个参数：

1. `std::chrono::duration` 类型的参数 `duration`：表示等待的时间段，可以是一个时间间隔，比如 `std::chrono::milliseconds(500)` 表示等待时间为 500 毫秒。
2. 可选的谓词函数 `pred`：用于在等待期间检查条件是否满足。如果提供了 `pred`，`wait_for` 函数会在等待期间周期性地调用 `pred`，直到 `pred` 返回 `true` 或者超过指定的等待时间。

`wait_for` 函数的行为如下：

1. 在调用 `wait_for` 函数之前，必须先获取互斥锁，因为 `wait_for` 函数会在等待期间自动释放互斥锁，并在等待结束后重新获取。
2. 线程调用 `wait_for` 函数后，会进入等待状态，并等待条件变量的通知，或者等待时间到达。
3. 如果在等待时间到达之前，收到了条件变量的通知，或者谓词函数 `pred` 返回 `true`，则线程从等待状态返回，并重新获取互斥锁，继续执行后续代码。
4. 如果等待时间到达而没有收到条件变量的通知，或者谓词函数 `pred` 在等待时间内一直返回 `false`，则线程从等待状态返回，并重新获取互斥锁，继续执行后续代码。

下面是一个使用 `wait_for` 函数的简单示例：

```cpp
#include <iostream>
#include <condition_variable>
#include <mutex>
#include <chrono>

std::condition_variable cv;
std::mutex mtx;
bool ready = false;

void worker()
{
    std::this_thread::sleep_for(std::chrono::seconds(2));

    std::unique_lock<std::mutex> lock(mtx);
    ready = true;
    cv.notify_one();
}

int main()
{
    std::thread t(worker);

    std::unique_lock<std::mutex> lock(mtx);
    if (cv.wait_for(lock, std::chrono::seconds(3), [] { return ready; })) {
        std::cout << "Worker thread notified." << std::endl;
    } else {
        std::cout << "Timeout occurred." << std::endl;
    }

    t.join();

    return 0;
}
```

在上述示例中，主线程等待工作线程的通知，最多等待 3 秒钟。工作线程在等待 2 秒钟后发送通知。如果在 3 秒钟内收到通知，主线程输出 "Worker thread notified."；如果超过 3 秒钟仍然未收到通知，则输出 "Timeout occurred."。

通过使用 `wait_for` 函数，我们可以在指定的时间段内等待条件变量的通知，并根据需要在等待超时时采取相应的操作。

### 2.4 `wait_until () `函数

`wait_until` 是 `std::condition_variable` 类的一个成员函数，用于在指定的时间点之前等待条件变量的通知。

`wait_until` 函数有两个参数：

1. `std::chrono::time_point` 类型的参数 `timeout_time`：表示等待的时间点，可以是一个具体的时间点，比如 `std::chrono::system_clock::now() + std::chrono::seconds(10)` 表示当前时间加上 10 秒。
2. 可选的谓词函数 `pred`：用于在等待期间检查条件是否满足。如果提供了 `pred`，`wait_until` 函数会在等待期间周期性地调用 `pred`，直到 `pred` 返回 `true` 或者超过指定的等待时间点。

`wait_until` 函数的行为如下：

1. 在调用 `wait_until` 函数之前，必须先获取互斥锁，因为 `wait_until` 函数会在等待期间自动释放互斥锁，并在等待结束后重新获取。
2. 线程调用 `wait_until` 函数后，会进入等待状态，并等待条件变量的通知，或者等待时间点到达。
3. 如果在等待时间点到达之前，收到了条件变量的通知，或者谓词函数 `pred` 返回 `true`，则线程从等待状态返回，并重新获取互斥锁，继续执行后续代码。
4. 如果等待时间点到达而没有收到条件变量的通知，或者谓词函数 `pred` 在等待时间内一直返回 `false`，则线程从等待状态返回，并重新获取互斥锁，继续执行后续代码。

下面是一个使用 `wait_until` 函数的简单示例：

```cpp
#include <iostream>
#include <condition_variable>
#include <mutex>
#include <chrono>

std::condition_variable cv;
std::mutex mtx;
bool ready = false;

void worker()
{
    std::this_thread::sleep_for(std::chrono::seconds(2));

    std::unique_lock<std::mutex> lock(mtx);
    ready = true;
    cv.notify_one();
}

int main()
{
    std::thread t(worker);

    std::unique_lock<std::mutex> lock(mtx);
    auto timeout_time = std::chrono::system_clock::now() + std::chrono::seconds(3);
    if (cv.wait_until(lock, timeout_time, [] { return ready; })) {
        std::cout << "Worker thread notified." << std::endl;
    } else {
        std::cout << "Timeout occurred." << std::endl;
    }

    t.join();

    return 0;
}
```

在上述示例中，主线程等待工作线程的通知，直到指定的时间点之前。工作线程在等待 2 秒钟后发送通知。如果在指定时间点之前收到通知，主线程输出 "Worker thread notified."；如果超过指定时间点仍然未收到通知，则输出 "Timeout occurred."。通过使用 `wait_until` 函数，我们可以在指定的时间点之前等待条件变量的通知，并根据需要在等待超时时采取相应的操作。

### 2.5 `notify_one() ` 和`notify_all() `函数

`notify_one` 和 `notify_all` 是 `std::condition_variable` 类的成员函数，用于唤醒等待在条件变量上的线程。

- `notify_one` 函数用于唤醒一个等待在条件变量上的线程。如果有多个线程在条件变量上等待，那么只会唤醒其中的一个线程。选择哪个线程被唤醒是不确定的，取决于操作系统的调度策略。

- `notify_all` 函数用于唤醒所有等待在条件变量上的线程。如果有多个线程在条件变量上等待，那么所有等待的线程都会被唤醒。

这两个函数的调用必须在拥有与条件变量关联的互斥锁的情况下进行。通常的使用方式是：

1. 获取与条件变量关联的互斥锁。
2. 在互斥锁的保护下，对共享数据进行修改。
3. 调用 `notify_one` 或 `notify_all` 唤醒等待在条件变量上的线程。
4. 释放互斥锁。

下面是一个简单的示例，演示了如何使用 `notify_one` 和 `notify_all`：

```cpp
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

    tjoin();
    t2.join();
    t3.join();

    return 0;
}
```

在上述示例中，三个工作线程等待条件变量 `ready` 为真的通知。在主线程中，通过修改共享变量 `ready` 的值，并调用 `notify_one` 函数来唤醒一个线程。由于我们无法确定唤醒哪个线程，因此可能会有任意一个线程被唤醒。

如果我们将 `notify_one` 替换为 `notify_all`，则会唤醒所有等待的线程。

总结来说，`notify_one` 和 `notify_all` 用于唤醒等待在条件变量上的线程，`notify_one` 唤醒一个线程，`notify_all` 唤醒所有线程。这些函数的调用必须在互斥锁的保护下进行。

### 2.6 `condition_variable_any() `函数

`std::condition_variable_any` 是 C++ 标准库提供的一个通用条件变量类，它允许与任何互斥量类型一起使用。

`std::condition_variable_any` 类提供了与 `std::condition_variable` 类类似的功能，但可以与任何满足特定要求的互斥量一起使用，而不仅限于 `std::mutex`。这使得 `std::condition_variable_any` 更加通用，可以与自定义的互斥量类型一起使用。

使用 `std::condition_variable_any` 类时，需要注意以下几点：

1. `std::condition_variable_any` 的成员函数 `wait`、`notify_one` 和 `notify_all` 使用一个可调用的等待条件（predicate）来替代 `std::condition_variable` 中的谓词函数。等待条件是一个返回 `bool` 值的可调用对象，它用于在等待期间检查条件是否满足。
2. 在调用 `wait`、`notify_one` 或 `notify_all` 之前，必须先获取与条件变量关联的互斥量。
3. 等待期间，互斥量会被自动释放，并在等待结束后重新获取。
4. `std::condition_variable_any` 的成员函数 `wait` 可以接受一个可调用的等待条件，并将其与等待时间点（通过 `std::chrono::time_point` 表示）一起使用，以支持有超时的等待。

以下是一个示例，演示了如何使用 `std::condition_variable_any`：

```cpp
#include <iostream>
#include <condition_variable>
#include <mutex>
#include <thread>

std::condition_variable_any cv;
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
        cv.notify_all();
    }

    tjoin();
    t2.join();
    t3.join();

    return 0;
}
```

在上述示例中，我们使用 `std::condition_variable_any` 类创建了一个条件变量 `cv`。三个工作线程等待条件变量 `ready` 为真的通知。在主线程中，通过修改共享变量 `ready` 的值，并调用 `notify_all` 函数来唤醒所有等待的线程。

通过使用 `std::condition_variable_any`，我们可以更灵活地选择互斥量类型，并与任何满足要求的互斥量一起使用条件变量。

### 2.8 `cv_status () `函数

`cv_status` 是 `std::cv_status` 枚举类型，用于表示条件变量等待的状态。

`std::cv_status` 定义了以下两个枚举值：

1. `std::cv_status::no_timeout`：表示等待期间没有超时发生，条件变量的通知被收到。
2. `std::cv_status::timeout`：表示等待期间发生了超时，条件变量的通知未被收到。

这两个枚举值用于表示条件变量在等待期间的不同状态，以便在等待结束后进行相应的处理。

在条件变量的等待函数中，比如 `wait()` 或 `wait_for()`，可以通过检查等待返回的状态来确定等待期间是否发生了超时。例如，可以使用 `std::cv_status` 枚举类型来检查 `wait_for()` 函数是否由于超时而返回。

以下是一个示例，演示了如何使用 `std::cv_status`：

```cpp
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
```

在上述示例中，主线程使用 `wait_until()` 函数等待条件变量的通知，超时时间为 3 秒。等待结束后，通过检查返回的 `std::cv_status` 枚举值，可以确定等待期间是否发生了超时。

如果返回的状态为 `std::cv_status::no_timeout`，表示等待期间没有超时发生，条件变量的通知被收到；如果返回的状态为 `std::cv_status::timeout`，表示发生了超时，条件变量的通知未被收到。

使用 `std::cv_status` 枚举类型可以根据等待的状态采取不同的处理逻辑，以满足特定的需求。

# 3. notify_all_at_thread_exit

`notify_all_at_thread_exit` 是一个 C++23 中引入的新函数，用于在线程退出时自动发送条件变量的通知。

在之前的 C++ 标准中，当一个线程退出时，如果有其他线程在等待与之关联的条件变量，它们将永远无法被唤醒，因为已经没有线程能够通过通知来唤醒它们。

C++23 引入了 `notify_all_at_thread_exit` 函数来解决这个问题。这个函数允许在线程退出时自动发送条件变量的通知，确保所有等待的线程可以被唤醒。

`notify_all_at_thread_exit` 函数需要以条件变量和互斥量作为参数，并且在与之关联的线程退出时调用。它会发送一个特殊的通知，告诉等待的线程条件变量的相关事件已经发生。

以下是一个示例，演示了如何使用 `notify_all_at_thread_exit`：

```cpp
#include <iostream>
#include <condition_variable>
#include <mutex>
#include <thread>

std::condition_variable cv;
std::mutex mtx;
bool ready = false;

void worker()
{
    std::unique_lock<std::mutex> lock(mtx);
    std::notify_all_at_thread_exit(cv, std::move(lock));

    // 模拟一些工作
    std::this_thread::sleep_for(std::chrono::seconds(2));

    // 完成工作，设置 ready 为 true
    ready = true;
}

int main()
{
    std::thread t(worker);

    // 等待 worker 线程退出，并在退出时自动发送通知
    t.detach();

    // 等待条件变量的通知
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [] { return ready; });

    std::cout << "Worker thread finished its work." << std::endl;

    return 0;
}
```

在上述示例中，我们通过调用 `std::notify_all_at_thread_exit` 函数，在 `worker` 线程退出时自动发送条件变量 `cv` 的通知。这样，即使 `worker` 线程在主线程等待之前退出，主线程仍然能够在等待条件变量时收到通知并继续执行。

需要注意的是，`notify_all_at_thread_exit` 函数必须在持有互斥量的情况下调用，以确保线程安全。此外，被通知的线程必须使用互斥量来保护对共享数据的访问，以避免竞争条件。