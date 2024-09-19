# Cpp 互斥量与锁

## 1 `<mutex>` 头文件摘要

`<mutex>` 头文件摘要如下：

```cpp
namespace std {
    
    class mutex;
    class recursive_mutex;
    class timed_mutex;
    class recursive_timed_mutex;

    struct defer_lock_t { };
    struct try_to_lock_t { };
    struct adopt_lock_t { };

    constexpr defer_lock_t defer_lock { };
    constexpr try_to_lock_t try_to_lock { };
    constexpr adopt_lock_t adopt_lock { };

    template <class Mutex> class lock_guard;
    template <class Mutex> class unique_lock;

    template <class Mutex>
    void swap(unique_lock<Mutex>& x, unique_lock<Mutex>& y);

    template <class L1, class L2, class... L3> int try_lock(L1&, L2&, L3&...);
    template <class L1, class L2, class... L3> void lock(L1&, L2&, L3&...);

    struct once_flag {
        constexpr once_flag() noexcept;
        once_flag(const once_flag&) = delete;
        once_flag& operator=(const once_flag&) = delete;
    };

    template<class Callable, class ...Args>
    void call_once(once_flag& flag, Callable func, Args&&... args);
}
```



### 1.1 `std::mutex` 类摘要

```cpp
namespace std {
    class mutex {
        public:
            constexpr mutex();
            ~mutex();
            mutex(const mutex&) = delete;
            mutex& operator=(const mutex&) = delete;

            void lock();
            bool try_lock() noexcept;
            void unlock() noexcept;

            typedef implementation-defined native_handle_type;
            native_handle_type native_handle();
    };
}
```



### 1.2 `std::recursive_mutex` 类摘要

```
namespace std {
    class recursive_mutex {
        public:
            recursive_mutex();
            ~recursive_mutex();
            recursive_mutex(const recursive_mutex&) = delete;
            recursive_mutex& operator=(const recursive_mutex&) = delete;

            void lock();
            bool try_lock() noexcept;
            void unlock() noexcept;

            typedef implementation-defined native_handle_type;
            native_handle_type native_handle();
    };
}
```



### 1.3 `std::timed_mutex` 类摘要

```
namespace std {
    class timed_mutex {
        public:
            timed_mutex();
            ~timed_mutex();
            timed_mutex(const timed_mutex&) = delete;
            timed_mutex& operator=(const timed_mutex&) = delete;

            void lock();
            bool try_lock();
            template <class Rep, class Period>
            bool try_lock_for(const chrono::duration<Rep, Period>& rel_time) noexcept;
            template <class Clock, class Duration>
            bool try_lock_until(const chrono::time_point<Clock, Duration>& abs_time) noexcept;
            void unlock();

            typedef implementation-defined native_handle_type; 
            native_handle_type native_handle();    
    };
}
```



### 1.4 `std::recursive_timed_mutex` 类摘要

```
namespace std {
    class recursive_timed_mutex {
        public:
            recursive_timed_mutex();
            ~recursive_timed_mutex();
            recursive_timed_mutex(const recursive_timed_mutex&) = delete;
            recursive_timed_mutex& operator=(const recursive_timed_mutex&) = delete;

            void lock();
            bool try_lock();
            template <class Rep, class Period>
            bool try_lock_for(const chrono::duration<Rep, Period>& rel_time) noexcept;
            template <class Clock, class Duration>
            bool try_lock_until(const chrono::time_point<Clock, Duration>& abs_time) noexcept;
            void unlock();

            typedef implementation-defined native_handle_type; 
            native_handle_type native_handle();
    };
}
```



### 1.5 `std::lock_guard` 类摘要

```
namespace std {
    template <class Mutex>
    class lock_guard {
        public:
            typedef Mutex mutex_type;
            explicit lock_guard(mutex_type& m);
            lock_guard(mutex_type& m, adopt_lock_t) noexcept;
            ~lock_guard();
            lock_guard(lock_guard const&) = delete;
            lock_guard& operator=(lock_guard const&) = delete;
        private:
            mutex_type& pm; // exposition only
    };
}
```



### 1.6 `std::unique_lock` 类摘要

```
namespace std {
    template <class Mutex>
    class unique_lock {
        public:
            typedef Mutex mutex_type;
            // 构造/拷贝/析构:
            unique_lock() noexcept;
            explicit unique_lock(mutex_type& m);
            unique_lock(mutex_type& m, defer_lock_t) noexcept;
            unique_lock(mutex_type& m, try_to_lock_t) noexcept;
            unique_lock(mutex_type& m, adopt_lock_t) noexcept;
            template <class Clock, class Duration>
            unique_lock(mutex_type& m, const chrono::time_point<Clock, Duration>& abs_time) noexcept;
            template <class Rep, class Period>
            unique_lock(mutex_type& m, const chrono::duration<Rep, Period>& rel_time) noexcept;
            ~unique_lock();
            unique_lock(unique_lock const&) = delete;
            unique_lock& operator=(unique_lock const&) = delete;
            unique_lock(unique    _lock&& u) noexcept;
            unique_lock& operator=(unique_lock&& u) noexcept;

            // 上锁操作:
            void lock();
            bool try_lock();
            template <class Rep, class Period>
            bool try_lock_for(const chrono::duration<Rep, Period>& rel_time);
            template <class Clock, class Duration>
            bool try_lock_until(const chrono::time_point<Clock, Duration>& abs_time);
            void unlock();

            // 修改操作
            void swap(unique_lock& u) noexcept;
            mutex_type *release() noexcept;

            // observers:
            bool owns_lock() const noexcept;
            explicit operator bool () const noexcept;
            mutex_type* mutex() const noexcept;
        private:
            mutex_type *pm; // exposition only
            bool owns; // exposition only
    };
    
    template <class Mutex>
    void swap(unique_lock<Mutex>& x, unique_lock<Mutex>& y) noexcept;
}
```

## 2 互斥量详解

### 2.1 `std::mutex` 介绍

`std::mutex` 是 C++11 中最基本的互斥量，`std::mutex` 对象提供了独占所有权的特性——即不支持递归地对 `std::mutex` 对象上锁，而 `std::recursive_lock` 则可以递归地对互斥量对象上锁。

#### `std::mutex` 的成员函数

- 构造函数，std::mutex不允许拷贝构造，也不允许 move 拷贝，最初产生的 mutex 对象是处于 unlocked 状态的。
- lock()，调用线程将锁住该互斥量。线程调用该函数会发生下面 3 种情况：
  1. 如果该互斥量当前没有被锁住，则调用线程将该互斥量锁住，直到调用 unlock之前，该线程一直拥有该锁。
  2. 如果当前互斥量被其他线程锁住，则当前的调用线程被阻塞住。
  3. 如果当前互斥量被当前调用线程锁住，则会**产生死锁(deadlock)**。
- unlock()， 解锁，释放对互斥量的所有权。
- try_lock()，尝试锁住互斥量，如果互斥量被其他线程占有，则当前线程也不会被阻塞。线程调用该函数也会出现下面 3 种情况，
  1. 如果当前互斥量没有被其他线程占有，则该线程锁住互斥量，直到该线程调用 unlock 释放互斥量。
  2. 如果当前互斥量被其他线程锁住，则当前调用线程返回 false，而并不会被阻塞掉。
  3. 如果当前互斥量被当前调用线程锁住，则会产生死锁(deadlock)。

```cpp
#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

volatile int count(0);
mutex mtx;

void func()
{
    cout << "thread id " << this_thread::get_id() << " begin" << endl;

    if (mtx.try_lock())
    {
        for (int i = 0; i < 10; i++)
        {
            ++count;
        }
    }

    cout << "thread id " << this_thread::get_id() << " end" << endl;
    mtx.unlock();
}

int main()
{
    thread th[10];
    for (int i = 0; i < 10; i++)
    {
        th[i] = thread(func);
    }

    for (auto &t : th)
        t.join();

    cout << "funal count = " << count << endl;
}
```

补充:	

> `volatile int counter(0);` 声明了一个名为 `counter` 的变量，其类型为 `int`，并且使用 `volatile` 修饰符进行修饰。
>
> `volatile` 是一个C++关键字，用于告知编译器在优化代码时不要对变量进行优化。它用于指示某个变量可能会在程序的其他地方被修改，因此编译器不应该对该变量进行优化，以确保对变量的读写操作都是按照程序的原始意图执行的。`volatile` 变量通常用于以下情况：
>
> 1. 多线程环境下的共享变量：当一个变量被多个线程访问时，如果不使用 `volatile` 修饰符，编译器可能会对变量的读取和写入进行优化，例如使用寄存器进行缓存，这可能导致线程之间的可见性问题。通过使用 `volatile` 修饰符，可以告知编译器不要进行优化，从而确保变量的读写操作都是直接访问内存的。
>
> 2. 内存映射IO：当与硬件设备进行通信时，使用 `volatile` 修饰符可以确保对设备寄存器的读写操作按照程序的要求执行，而不会被编译器优化掉。
>
> 需要注意的是，`volatile` 关键字只能保证对变量的单个读写操作的顺序性，而不能保证多个读写操作之间的原子性。在多线程环境下，如果需要保证原子性和同步，通常需要使用其他同步机制，如互斥量（`std::mutex`）或原子操作（`std::atomic`）。
>
> 在你提供的例子中，`volatile int counter(0);` 声明了一个 `volatile` 的整型变量 `counter`，初始值为 0。这样，编译器会在每次访问 `counter` 变量时都从内存中读取，并且不会对其进行优化。这对于在多线程环境下对 `counter` 进行读写操作或与硬件设备进行通信的情况可能是有用的。

#### `std::recursive_mutex` 介绍

`std::recursive_mutex` 与 `std::mutex `一样，也是一种可以被上锁的对象，但是和 `std::mutex` 不同的是，`std::recursive_mutex` 允许同一个线程对互斥量多次上锁（即递归上锁），来获得对互斥量对象的多层所有权，`std::recursive_mutex` 释放互斥量时需要调用与该锁层次深度相同次数的 `unlock()`，可理解为 `lock()` 次数和 `unlock()` 次数相同，除此之外，`std::recursive_mutex` 的特性和 `std::mutex` 大致相同。

```cpp
#include <iostream>
#include <thread>
#include <mutex> 

std::recursive_mutex mtx;           

void print_block (int n, char c) {
  mtx.lock();
  
  for (int i=0; i<n; ++i) { std::cout << c; }
  std::cout << '\n';
  
  mtx.unlock();
}

int main ()
{
  std::thread th1 (print_block,50,'*');
  std::thread th2 (print_block,50,'$');

  th1.join();
  th2.join();

  return 0;
}
```

### 2.2 std::time_mutex 介绍

`std::time_mutex` 比 `std::mutex` 多了两个成员函数，`try_lock_for()`，`try_lock_until()`。

`try_lock_for` 函数接受一个时间范围，表示在这一段时间范围之内线程如果没有获得锁则被阻塞住（与 `std::mutex` 的 `try_lock()` 不同，try_lock 如果被调用时没有获得锁则直接返回 `false`），如果在此期间其他线程释放了锁，则该线程可以获得对互斥量的锁，如果超时（即在指定时间内还是没有获得锁），则返回 `false`。

`try_lock_until` 函数则接受一个时间点作为参数，在指定时间点未到来之前线程如果没有获得锁则被阻塞住，如果在此期间其他线程释放了锁，则该线程可以获得对互斥量的锁，如果超时（即在指定时间内还是没有获得锁），则返回 `false`。

```cpp
#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>

using namespace std;

timed_mutex mtx;

void func()
{
    while (mtx.try_lock_for(chrono::milliseconds(200)))
    {
        cout << this_thread::get_id() << " :--\n"; 
    }
    
    this_thread::sleep_for(chrono::milliseconds(400));
    cout << "*" << this_thread::get_id() << "*\n";
    mtx.unlock();
}

int main()
{
    thread ths[10];
    for (int i=0; i<10; i++) ths[i] = thread(func);

    for (auto &th : ths) th.join();

    return 0;
}
```

### 2.3 `std::recursive_timed_mutex` 介绍

和 `std:recursive_mutex` 与 `std::mutex` 的关系一样，`std::recursive_timed_mutex` 的特性也可以从 `std::timed_mutex` 推导出来，感兴趣的同鞋可以自行查阅。;-)

### 2.4 std::lock_guard 介绍

`std::lock_guard`是C++标准库中的一个模板类，用于自动管理互斥量（`std::mutex`）的锁定和解锁操作。它实现了一种称为"资源获取即初始化（Resource Acquisition Is Initialization，RAII）"的技术，该技术可以确保在对象的构造函数中获取资源，在对象的析构函数中释放资源，从而保证资源的正确使用和释放。

`std::lock_guard`的头文件是`<mutex>`。

使用`std::lock_guard`的一般流程如下：

1. 创建一个互斥量对象（`std::mutex`）。
2. 在需要保护共享资源的代码段之前，创建一个`std::lock_guard`对象，并将互斥量对象作为构造函数的参数传入。
3. `std::lock_guard`对象的构造函数会自动调用互斥量的`lock()`成员函数，从而锁定互斥量。
4. 执行共享资源的代码段。
5. `std::lock_guard`对象的析构函数会自动调用互斥量的`unlock()`成员函数，从而释放互斥量。
6. 当`std::lock_guard`对象超出作用域时，会自动被销毁，从而触发析构函数的调用。

使用`std::lock_guard`可以避免在代码中显式地调用`lock()`和`unlock()`函数，从而减少了因忘记解锁而导致的死锁和资源泄漏的风险。此外，由于`std::lock_guard`对象是在栈上分配的，所以在函数退出时会自动销毁，保证了资源的正确释放。

下面是一个使用`std::lock_guard`的简单示例代码：

```cpp
#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

mutex mtx;


void func()
{
    if (mtx.try_lock()) /* 这句代码会被替换掉 */
    {
        cout << this_thread::get_id() << "lock !\n";
    }
}

int main()
{
    thread threads[10];

    for (int i=0; i<10; i++) threads[i] = thread(func);

    for (auto &th : threads) th.join();

    if(mtx.try_lock())
    {
        cout << " main proces lock ! ";
    }
    else
    {
        cout << "lock filed !";
    }

    return 0;
}
```

输出：

```shell
(base) PS C:\Files\code\CppProject\src\output> & .\'2.4 lock_guard.exe'
2lock !
lock filed !
```

**使用`lock_guard`**

```cpp
#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

mutex mtx;


void func()
{
    lock_guard<mutex> lgc(mtx); // 阻塞之后，后面的代码不会被执行
    {
        cout << this_thread::get_id() << "lock !\n";
    }
}

int main()
{
    thread threads[10];

    for (int i=0; i<10; i++) threads[i] = thread(func);

    for (auto &th : threads) th.join();

    if(mtx.try_lock())
    {
        cout << "main proces lock ! ";
    }
    else
    {
        cout << "lock filed !";
    }

    return 0;
}
```

输出

```shell
(base) PS C:\Files\code\CppProject\src\output> & .\'2.4 lock_guard.exe'
3lock !
7lock !
5lock !
2lock !
6lock !
4lock !
8lock !
9lock !
10lock !
11lock !
main proces lock !
```

### 2.5 `std::unique_lock` 介绍

```cpp
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
```

