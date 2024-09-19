# 异步线程

[TOC]

C++11 标准中与异步任务系相关的类型主要是以下四种 `std::promise`，`std::packaged_task`（`std::promise`，`std::packaged_task` 也称为异步任务的提供者 Provider，此外 `std::async` 也可以作为异步任务的提供者，不过 `std::async` 并不是类，而是函数，本章后面会详细介绍异步任务的提供者 Provider），`std::future`，`std::shared_future`。另外 `<future>` 中还定义一些辅助的类，例如： `std::future_error`，`std::future_errc`，`std::status`，`std::launch`。

下面我们看看 C++11 标准中是怎么声明以上类型和函数的。

## 1 `<future>` 头文件摘要

### 1.1 `<future>` 头文件摘要

```cpp
namespace std {
    enum class future_errc {
        broken_promise,
        future_already_retrieved,
        promise_already_satisfied,
        no_state    
    };
    
    enum class launch : unspecified {
        async = unspecified,
        deferred = unspecified,
        implementation-defined
    };
    
    enum class future_status {
        ready,
        timeout,
        deferred
    };
    
    template <> struct is_error_code_enum<future_errc> : public true_type { };
    error_code make_error_code(future_errc e);
    error_condition make_error_condition(future_errc e);

    const error_category& future_category();

    class future_error;

    template <class R> class promise;
    template <class R> class promise<R&>;
    template <> class promise<void>;

    template <class R>
    void swap(promise<R>& x, promise<R>& y);

    template <class R, class Alloc>
    struct uses_allocator<promise<R>, Alloc>;

    template <class R> class future;
    template <class R> class future<R&>;
    template <> class future<void>;
    
    template <class R> class shared_future;
    template <class R> class shared_future<R&>;
    template <> class shared_future<void>;

    template <class> class packaged_task; // undefined
    template <class R, class... ArgTypes>
    class packaged_task<R(ArgTypes...)>;

    template <class R>
    void swap(packaged_task<R(ArgTypes...)&, packaged_task<R(ArgTypes...)>&);

    template <class R, class Alloc>
    struct uses_allocator<packaged_task<R>, Alloc>;

    template <class F, class... Args>
    future<typename result_of<F(Args...)>::type>
    async(F&& f, Args&&... args);

    template <class F, class... Args>
    future<typename result_of<F(Args...)>::type>
    async(launch policy, F&& f, Args&&... args);
}
```

### 1.2 `std::future_error` 类摘要

```cpp
namespace std {
    class future_error : public logic_error {
        public:
            future_error(error_code ec); // exposition only
            const error_code& code() const noexcept;
            const char* what() const noexcept;
    };
}
```

### 1.3 `std::promise` 类摘要

```cpp
namespace std {
    template <class R>
    class promise {
        public:
            promise();
            template <class Allocator>
            promise(allocator_arg_t, const Allocator& a);
            promise(promise&& rhs) noexcept;
            promise(const promise& rhs) = delete;
            ~promise();

            // assignment
            promise& operator=(promise&& rhs) noexcept;
            promise& operator=(const promise& rhs) = delete;

            void swap(promise& other) noexcept;

            // retrieving the result
            future<R> get_future();

            // setting the result
            void set_value(see below);
            void set_exception(exception_ptr p);

            // setting the result with deferred notification
            void set_value_at_thread_exit(const R& r);
            void set_value_at_thread_exit(see below);
            void set_exception_at_thread_exit(exception_ptr p);
    };
    template <class R>
    void swap(promise<R>& x, promise<R>& y);
    template <class R, class Alloc>
    struct uses_allocator<promise<R>, Alloc>;
}
```

### 1.4 `std::future` 类摘要

```cpp
namespace std {
    template <class R>
    class future {
        public:
            future();
            future(future &&);
            future(const future& rhs) = delete;
            ~future();

            future& operator=(const future& rhs) = delete;
            future& operator=(future&&) noexcept;
            shared_future<R> share() &&;

            // retrieving the value
            see below get();

            // functions to check state
            bool valid() const;
            void wait() const;
            template <class Rep, class Period>
            future_status wait_for(const chrono::duration<Rep, Period>& rel_time) const;
            template <class Clock, class Duration>
            future_status wait_until(const chrono::time_point<Clock, Duration>& abs_time) const;
    };
}
```

### 1.5 `std::shared_future` 类摘要

```cpp
namespace std {
    template <class R>
    class shared_future {
        public:
            shared_future() noexcept;
            shared_future(const shared_future& rhs);
            shared_future(future<R>&&) noexcept;
            shared_future(shared_future&& rhs) noexcept;
            ~shared_future();

            shared_future& operator=(const shared_future& rhs);
            shared_future& operator=(shared_future&& rhs);

            // retrieving the value
            see below get() const;

            // functions to check state
            bool valid() const;
            void wait() const;
            template <class Rep, class Period>
            future_status wait_for(const chrono::duration<Rep, Period>& rel_time) const;
            template <class Clock, class Duration>
            future_status wait_until(const chrono::time_point<Clock, Duration>& abs_time) const;
    };
}
```

### 1.6 `std::async` 函数摘要

```cpp
namespace std {
    template <class F, class... Args>
    future<typename result_of<F(Args...)>::type>
    async(F&& f, Args&&... args);

    template <class F, class... Args>
    future<typename result_of<F(Args...)>::type>
    async(launch policy, F&& f, Args&&... args);
}
```

### 1.7 `std::packaged_task` 类摘要

```cpp
namespace std {
    template<class> class packaged_task; // undefined

    template<class R, class... ArgTypes>
    class packaged_task<R(ArgTypes...)> {
        public:
            typedef R result_type;

            // construction and destruction
            packaged_task() noexcept;
            template <class F>
            explicit packaged_task(F f);
            template <class F, class Allocator>
            explicit packaged_task(allocator_arg_t, const Allocator& a, F f);
            explicit packaged_task(R(*f)(ArgTypes...));
            template <class F>
            explicit packaged_task(F&& f);
            template <class F, class Allocator>
            explicit packaged_task(allocator_arg_t, const Allocator& a, F&& f);
            ~packaged_task();

            // no copy
            packaged_task(packaged_task&) = delete;
            packaged_task& operator=(packaged_task&) = delete;

            // move support
            packaged_task(packaged_task&& other) noexcept;
            packaged_task& operator=(packaged_task&& other);
            void swap(packaged_task& other) noexcept;
            bool valid() const noexcept;

            // result retrieval
            future<R> get_future();
            
            // execution
            void operator()(ArgTypes... );
            void make_ready_at_thread_exit(ArgTypes...);
            void reset();
    };

    template <class R, class... ArgTypes>
    void swap(packaged_task<R(ArgTypes...)>& x, packaged_task<R(ArgTypes...)>& y) noexcept;
    template <class R, class Alloc>
    struct uses_allocator<packaged_task<R>, Alloc>;
}
```

## 2.  基本案例

### 获取结果 async

在C++中，`<future>`头文件提供了一组函数和类，用于处理异步操作和并发编程。以下是一些常见的`<future>`头文件中的函数及其案例：

1. `std::async`: 通过创建一个异步任务来在后台执行函数，并返回一个`std::future`对象，表示异步操作的结果。
```cpp
#include <iostream>
#include <future>

int sum(int a, int b) {
    return a + b;
}

int main() {
    std::future<int> fut = std::async(sum, 1, 2);
    int result = fut.get();  // 等待异步任务完成并获取结果
    std::cout << "Result: " << result << std::endl;
    return 0;
}
```

### 捕获异常 promise

2. `std::promise`和`std::future`: `std::promise`用于在一个线程中设置值或异常，然后通过`std::future`在另一个线程中获取这个值或异常。

```cpp
#include <iostream>
#include <future>

using namespace std;

int divide(promise<double> &&prom, int a, int b)
{
    try{
        if (b == 0)
            throw std::runtime_error("Divide by zero exception");
        double result = 1.0 * a / b;
        prom.set_value(result);
    }
    catch(...){
        prom.set_exception(current_exception());
    }
}

int main()
{
    promise<double> prom;
    future<double> fut = prom.get_future();

    thread t(divide, move(prom), 3, 0);
    t.join();

    try{
        double result = fut.get();
        cout << "Result = " << result ;
    }
    catch(const std::exception& e){
        cout << "Exception :" << e.what();
    }
}
```

### 对象包装 packaged_task

3. `std::packaged_task`: 将函数包装为可调用对象，并返回一个与之关联的`std::future`对象，可以在需要时获取函数的结果。

```cpp
#include <iostream>
#include <future>

using namespace std;

int sum(int a, int b){ return a + b; }

int main()
{
    packaged_task<int(int, int)> task(sum);
    future<int> fut = task.get_future();

    thread t(move(task), 1, 2);
    t.join();

    int result = fut.get();
    cout << "Result = " << result ;
}
```

这些只是`<future>`头文件中的一些常见函数的示例。还有其他函数和类可以用于处理异步操作和并发编程，如`std::future_status`、`std::shared_future`等。请根据具体需求查阅C++的文档来了解更多详细信息和用法。

## 3. future 的使用及其案例

在C++中，`std::future`是一个模板类，用于表示异步操作的结果。它允许您在一个线程中启动一个任务，并在需要时获取其结果。以下是`std::future`的使用及其案例：

1. 启动异步任务并获取结果：
```cpp
#include <iostream>
#include <future>

int sum(int a, int b) {
    return a + b;
}

int main() {
    std::future<int> fut = std::async(sum, 1, 2);
    int result = fut.get();  // 等待异步任务完成并获取结果
    std::cout << "Result: " << result << std::endl;
    return 0;
}
```
在这个示例中，`std::async`函数启动了一个异步任务，该任务调用`sum`函数来计算两个整数的和。返回的`std::future`对象用于获取异步任务的结果。通过调用`get`函数，程序将等待异步任务完成并返回结果。

2. 使用`std::promise`和`std::future`进行线程间通信：
```cpp
#include <iostream>
#include <future>

void divide(std::promise<double>&& prom, double a, double b) {
    try {
        if (b == 0)
            throw std::runtime_error("Divide by zero exception");
        prom.set_value(a / b);
    } catch (...) {
        prom.set_exception(std::current_exception());
    }
}

int main() {
    std::promise<double> prom;
    std::future<double> fut = prom.get_future();

    std::thread t(divide, std::move(prom), 10.0, 2.0);
    t.join();

    try {
        double result = fut.get();
        std::cout << "Result: " << result << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
```
在这个示例中，`std::promise`用于在一个线程中设置值或异常，然后通过与之关联的`std::future`在另一个线程中获取这个值或异常。`divide`函数被启动为一个线程，并使用`std::promise`设置除法的结果。主线程通过调用`fut.get()`来等待线程完成并获取结果。

3. 使用`std::packaged_task`包装函数并获取结果：
```cpp
#include <iostream>
#include <future>

int sum(int a, int b) {
    return a + b;
}

int main() {
    std::packaged_task<int(int, int)> task(sum);
    std::future<int> fut = task.get_future();

    std::thread t(std::move(task), 1, 2);
    t.join();

    int result = fut.get();
    std::cout << "Result: " << result << std::endl;

    return 0;
}
```
在这个示例中，`std::packaged_task`将`sum`函数包装为可调用对象，并返回与之关联的`std::future`对象。通过调用`fut.get()`，程序等待线程完成并获取结果。

这些示例演示了`std::future`的基本用法，用于启动异步任务并获取其结果。根据需要，您还可以使用`std::future`的其他成员函数，如`wait`、`wait_for`和`wait_until`来控制异步操作的等待时间。请根据具体需求查阅C++的文档以获取更多详细信息和用法。

## 4. shared_future 的使用及其案例

在C++中，`std::shared_future`是一个模板类，类似于`std::future`，用于表示异步操作的结果。与`std::future`不同的是，`std::shared_future`可以被多个线程共享，允许多个线程同时等待异步操作的结果。以下是`std::shared_future`的使用及其案例：

1. 启动异步任务并共享结果：
```cpp
#include <iostream>
#include <future>

int sum(int a, int b) {
    return a + b;
}

int main() {
    std::shared_future<int> fut = std::async(sum, 1, 2);
    std::cout << "Result 1: " << fut.get() << std::endl;
    std::cout << "Result 2: " << fut.get() << std::endl;
    return 0;
}
```
在这个示例中，`std::async`函数启动了一个异步任务，该任务调用`sum`函数来计算两个整数的和，并返回一个`std::shared_future`对象。由于`std::shared_future`可以被多个线程共享，我们可以多次调用`fut.get()`来获取异步任务的结果。

2. 使用`std::shared_future`进行线程间通信：
```cpp
#include <iostream>
#include <future>
#include <thread>

void printResult(std::shared_future<int> fut) {
    int result = fut.get();
    std::cout << "Result: " << result << std::endl;
}

int main() {
    std::promise<int> prom;
    std::shared_future<int> fut = prom.get_future();

    std::thread t1(printResult, fut);
    std::thread t2(printResult, fut);

    prom.set_value(42);

    t1.join();
    t2.join();

    return 0;
}
```
在这个示例中，我们使用`std::promise`和`std::shared_future`进行线程间通信。`printResult`函数被启动为两个线程，并共享同一个`std::shared_future`对象。当`std::promise`设置值后，两个线程都能够通过`fut.get()`获取结果。

3. 使用`std::async`和`std::shared_future`启动多个异步任务：
```cpp
#include <iostream>
#include <future>

int sum(int a, int b) {
    return a + b;
}

int main() {
    std::shared_future<int> fut1 = std::async(sum, 1, 2);
    std::shared_future<int> fut2 = std::async(sum, 3, 4);

    std::cout << "Result 1: " << fut1.get() << std::endl;
    std::cout << "Result 2: " << fut2.get() << std::endl;

    return 0;
}
```
在这个示例中，我们使用`std::async`函数启动了两个异步任务，并返回两个`std::shared_future`对象。这两个任务可以并行执行，我们可以通过多次调用`fut.get()`来获取它们的结果。

这些示例演示了`std::shared_future`的基本用法，用于启动异步任务并共享结果。与`std::future`相比，`std::shared_future`允许多个线程同时等待异步操作的结果，提供了更灵活的线程间通信和并发编程的方式。请根据具体需求查阅C++的文档以获取更多详细信息和用法。

## 5. async 的使用及其案例

在C++中，`std::async`是一个函数模板，用于启动异步任务。它返回一个`std::future`对象，可以用于获取异步任务的结果。以下是`std::async`的使用及其案例：

1. 启动异步任务并获取结果：
```cpp
#include <iostream>
#include <future>

int sum(int a, int b) {
    return a + b;
}

int main() {
    std::future<int> fut = std::async(sum, 1, 2);
    int result = fut.get();  // 等待异步任务完成并获取结果
    std::cout << "Result: " << result << std::endl;
    return 0;
}
```
在这个示例中，`std::async`函数启动了一个异步任务，该任务调用`sum`函数来计算两个整数的和。返回的`std::future`对象用于获取异步任务的结果。通过调用`get`函数，程序将等待异步任务完成并返回结果。

2. 使用`std::launch`指定启动策略：
```cpp
#include <iostream>
#include <future>

int sum(int a, int b) {
    return a + b;
}

int main() {
    std::future<int> fut = std::async(std::launch::async, sum, 1, 2);
    int result = fut.get();  // 等待异步任务完成并获取结果
    std::cout << "Result: " << result << std::endl;
    return 0;
}
```
在这个示例中，我们使用`std::launch::async`作为第一个参数，指定了异步任务的启动策略为异步执行。这样可以确保异步任务立即在新的线程中执行。

3. 指定启动策略为延迟执行：
```cpp
#include <iostream>
#include <future>

int sum(int a, int b) {
    return a + b;
}

int main() {
    std::future<int> fut = std::async(std::launch::deferred, sum, 1, 2);
    int result = fut.get();  // 等待异步任务完成并获取结果
    std::cout << "Result: " << result << std::endl;
    return 0;
}
```
在这个示例中，我们使用`std::launch::deferred`作为第一个参数，指定了异步任务的启动策略为延迟执行。这意味着异步任务将在调用`get`函数时才会执行，而不是立即执行。

4. 使用`std::async`启动多个异步任务：
```cpp
#include <iostream>
#include <future>

int sum(int a, int b) {
    return a + b;
}

int main() {
    std::future<int> fut1 = std::async(sum, 1, 2);
    std::future<int> fut2 = std::async(sum, 3, 4);

    int result1 = fut1.get();
    int result2 = fut2.get();

    std::cout << "Result 1: " << result1 << std::endl;
    std::cout << "Result 2: " << result2 << std::endl;

    return 0;
}
```
在这个示例中，我们使用`std::async`函数分别启动了两个异步任务，并返回两个`std::future`对象。这两个任务可以并行执行，我们可以通过调用各自的`get`函数来获取它们的结果。

当使用`std::async`启动异步任务时，可以通过不同的参数和选项来控制任务的行为和执行方式。以下是一些更多的用法和选项：

1. 指定启动策略：
   - `std::launch::async`：异步任务立即在新线程中执行。
   - `std::launch::deferred`：异步任务在调用`get`函数时才会执行，可能在同一线程中延迟执行。

2. 指定执行器（Executor）：
   - `std::launch::async | std::launch::deferred`：指定异步任务可以根据实现选择在新线程中执行或者延迟执行。
   - `std::launch::any`：异步任务的执行方式由实现决定。

3. 指定任务的调度策略：
   - `std::launch::async | std::launch::deferred` 和 `std::launch::async`：异步任务按照FIFO顺序执行。
   - `std::launch::async | std::launch::deferred` 和 `std::launch::deferred`：异步任务按照LIFO顺序执行。

4. 指定线程池执行器：
   - C++17引入了`std::experimental::thread_pool`和`std::experimental::use_future`来指定线程池执行器和返回`std::future`。

以下是一个示例，展示了在`std::async`中使用这些选项的情况：
```cpp
#include <iostream>
#include <future>

int sum(int a, int b) {
    return a + b;
}

int main() {
    std::future<int> fut1 = std::async(std::launch::async, sum, 1, 2);
    std::future<int> fut2 = std::async(std::launch::async | std::launch::deferred, sum, 3, 4);
    std::future<int> fut3 = std::async(std::launch::deferred, sum, 5, 6);

    int result1 = fut1.get();
    int result2 = fut2.get();
    int result3 = fut3.get();

    std::cout << "Result 1: " << result1 << std::endl;
    std::cout << "Result 2: " << result2 << std::endl;
    std::cout << "Result 3: " << result3 << std::endl;

    return 0;
}
```
在这个示例中，我们使用不同的启动策略和选项来启动异步任务。`fut1`使用`std::launch::async`启动，即立即在新线程中执行。`fut2`使用`std::launch::async | std::launch::deferred`启动，根据实现决定是立即执行还是延迟执行。`fut3`使用`std::launch::deferred`启动，即延迟执行。通过调用各自的`get`函数，我们可以获取每个异步任务的结果。

需要注意的是，`std::async`的行为可能因实现而异，具体的执行方式可能取决于编译器和运行时环境。因此，在使用`std::async`时，建议查阅C++标准和特定编译器的文档，以了解具体的行为和支持的选项。

## 6. packaged_task

在C++中，std::packaged_task是一个类模板，用于封装可调用对象（函数、函数对象或Lambda表达式）并生成一个std::future对象，用于获取异步任务的结果。以下是std::packaged_task的使用及其案例：

封装函数并使用std::future获取结果：
```cpp
#include <iostream>
#include <future>

int sum(int a, int b) {
    return a + b;
}

int main() {
    std::packaged_task<int(int, int)> task(sum);
    std::future<int> fut = task.get_future();

    task(1, 2);  // 启动异步任务
    
    int result = fut.get();  // 等待异步任务完成并获取结果
    std::cout << "Result: " << result << std::endl;
    
    return 0;
}
```
在这个示例中，我们创建了一个std::packaged_task对象，将sum函数作为可调用对象进行封装。通过调用get_future函数，我们获取了一个std::future对象，用于获取异步任务的结果。通过调用task(1, 2)，我们启动了异步任务，然后通过调用fut.get()等待异步任务完成并获取结果。

封装Lambda表达式并使用std::future获取结果：
cpp
复制

```cpp
#include <iostream>
#include <future>

int main() {
    std::packaged_task<int()> task([]() {
        return 42;
    });
    std::future<int> fut = task.get_future();

    std::thread t(std::move(task));  // 在新线程中启动异步任务

    int result = fut.get();  // 等待异步任务完成并获取结果
    std::cout << "Result: " << result << std::endl;

    t.join();  // 等待新线程执行完毕

    return 0;
}
```

在这个示例中，我们创建了一个std::packaged_task对象，将一个Lambda表达式作为可调用对象进行封装。通过调用get_future函数，我们获取了一个std::future对象，用于获取异步任务的结果。通过将task对象移动到新线程中，我们启动了异步任务。然后通过调用fut.get()等待异步任务完成并获取结果。

这些示例演示了std::packaged_task的基本用法，用于封装可调用对象并生成与之关联的std::future对象。通过启动异步任务并调用get函数，我们可以获取异步任务的结果。请注意，在使用std::packaged_task时，需要确保启动异步任务的线程或者调用operator()来执行任务。