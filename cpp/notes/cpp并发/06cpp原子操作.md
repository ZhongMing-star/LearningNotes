## 1 `<atomic>` 头文件摘要

### 1.1 std::atomic_flag 类摘要

```cpp
namespace std {
    typedef struct atomic_flag {
        bool test_and_set(memory_order = memory_order_seq_cst) volatile;
        bool test_and_set(memory_order = memory_order_seq_cst);

        void clear(memory_order = memory_order_seq_cst) volatile;
        void clear(memory_order = memory_order_seq_cst);

        atomic_flag() = default;
        atomic_flag(const atomic_flag&) = delete;

        atomic_flag& operator=(const atomic_flag&) = delete;
        atomic_flag& operator=(const atomic_flag&) volatile = delete;
    } atomic_flag;

    bool atomic_flag_test_and_set(volatile atomic_flag*);
    bool atomic_flag_test_and_set(atomic_flag*);

    bool atomic_flag_test_and_set_explicit(volatile atomic_flag*, memory_order);
    bool atomic_flag_test_and_set_explicit(atomic_flag*, memory_order);

    void atomic_flag_clear(volatile atomic_flag*);
    void atomic_flag_clear(atomic_flag*);

    void atomic_flag_clear_explicit(volatile atomic_flag*, memory_order);
    void atomic_flag_clear_explicit(atomic_flag*, memory_order);

    #define ATOMIC_FLAG_INIT see below
}
```



### 1.2 std::atomic 基本类型摘要

```cpp
template <class T> struct atomic {
    bool is_lock_free() const volatile;
    bool is_lock_free() const;

    void store(T, memory_order = memory_order_seq_cst) volatile;
    void store(T, memory_order = memory_order_seq_cst);

    T load(memory_order = memory_order_seq_cst) const volatile;
    T load(memory_order = memory_order_seq_cst) const;

    operator T() const volatile;
    operator T() const;

    T exchange(T, memory_order = memory_order_seq_cst) volatile;
    T exchange(T, memory_order = memory_order_seq_cst);

    bool compare_exchange_weak(T&, T, memory_order, memory_order) volatile;
    bool compare_exchange_weak(T&, T, memory_order, memory_order);

    bool compare_exchange_strong(T&, T, memory_order, memory_order) volatile;
    bool compare_exchange_strong(T&, T, memory_order, memory_order);

    bool compare_exchange_weak(T&, T, memory_order = memory_order_seq_cst) volatile;
    bool compare_exchange_weak(T&, T, memory_order = memory_order_seq_cst);

    bool compare_exchange_strong(T&, T, memory_order = memory_order_seq_cst) volatile;
    bool compare_exchange_strong(T&, T, memory_order = memory_order_seq_cst);

    atomic() = default;
    constexpr atomic(T);
    atomic(const atomic&) = delete;

    atomic& operator=(const atomic&) = delete;
    atomic& operator=(const atomic&) volatile = delete;
    T operator=(T) volatile;
    T operator=(T);
};
```



### 1.3 std::atomic 整型特化摘要

```cpp
template <> struct atomic<integral> {
    bool is_lock_free() const volatile;
    bool is_lock_free() const;

    void store(integral, memory_order = memory_order_seq_cst) volatile;
    void store(integral, memory_order = memory_order_seq_cst);

    integral load(memory_order = memory_order_seq_cst) const volatile;
    integral load(memory_order = memory_order_seq_cst) const;

    operator integral() const volatile;
    operator integral() const;

    integral exchange(integral, memory_order = memory_order_seq_cst) volatile;
    integral exchange(integral, memory_order = memory_order_seq_cst);

    bool compare_exchange_weak(integral&, integral, memory_order, memory_order) volatile;
    bool compare_exchange_weak(integral&, integral, memory_order, memory_order);

    bool compare_exchange_strong(integral&, integral, memory_order, memory_order) volatile;
    bool compare_exchange_strong(integral&, integral, memory_order, memory_order);

    bool compare_exchange_weak(integral&, integral, memory_order = memory_order_seq_cst) volatile;
    bool compare_exchange_weak(integral&, integral, memory_order = memory_order_seq_cst);

    bool compare_exchange_strong(integral&, integral, memory_order = memory_order_seq_cst) volatile;
    bool compare_exchange_strong(integral&, integral, memory_order = memory_order_seq_cst);

    integral fetch_add(integral, memory_order = memory_order_seq_cst) volatile;
    integral fetch_add(integral, memory_order = memory_order_seq_cst);
    integral fetch_sub(integral, memory_order = memory_order_seq_cst) volatile;
    integral fetch_sub(integral, memory_order = memory_order_seq_cst);
    integral fetch_and(integral, memory_order = memory_order_seq_cst) volatile;
    integral fetch_and(integral, memory_order = memory_order_seq_cst);
    integral fetch_or(integral, memory_order = memory_order_seq_cst) volatile;
    integral fetch_or(integral, memory_order = memory_order_seq_cst);
    integral fetch_xor(integral, memory_order = memory_order_seq_cst) volatile;
    integral fetch_xor(integral, memory_order = memory_order_seq_cst);

    atomic() = default;
    constexpr atomic(integral);
    atomic(const atomic&) = delete;

    atomic& operator=(const atomic&) = delete;
    atomic& operator=(const atomic&) volatile = delete;
    integral operator=(integral) volatile;
    integral operator=(integral);
    integral operator++(int) volatile;
    integral operator++(int);
    integral operator--(int) volatile;
    integral operator--(int);
    integral operator++() volatile;
    integral operator++();
    integral operator--() volatile;
    integral operator--();
    integral operator+=(integral) volatile;
    integral operator+=(integral);
    integral operator-=(integral) volatile;
    integral operator-=(integral);
    integral operator&=(integral) volatile;
    integral operator&=(integral);
    integral operator|=(integral) volatile;
    integral operator|=(integral);
    integral operator^=(integral) volatile;
    integral operator^=(integral);
};
```



### 1.4 std::atomic 指针特化摘要

```cpp
template <class T> struct atomic<T*> {
    bool is_lock_free() const volatile;
    bool is_lock_free() const;

    void store(T*, memory_order = memory_order_seq_cst) volatile;
    void store(T*, memory_order = memory_order_seq_cst);

    T* load(memory_order = memory_order_seq_cst) const volatile;
    T* load(memory_order = memory_order_seq_cst) const;

    operator T*() const volatile;
    operator T*() const;

    T* exchange(T*, memory_order = memory_order_seq_cst) volatile;
    T* exchange(T*, memory_order = memory_order_seq_cst);

    bool compare_exchange_weak(T*&, T*, memory_order, memory_order) volatile;
    bool compare_exchange_weak(T*&, T*, memory_order, memory_order);

    bool compare_exchange_strong(T*&, T*, memory_order, memory_order) volatile;
    bool compare_exchange_strong(T*&, T*, memory_order, memory_order);

    bool compare_exchange_weak(T*&, T*, memory_order = memory_order_seq_cst) volatile;
    bool compare_exchange_weak(T*&, T*, memory_order = memory_order_seq_cst);

    bool compare_exchange_strong(T*&, T*, memory_order = memory_order_seq_cst) volatile;
    bool compare_exchange_strong(T*&, T*, memory_order = memory_order_seq_cst);

    T* fetch_add(ptrdiff_t, memory_order = memory_order_seq_cst) volatile;
    T* fetch_add(ptrdiff_t, memory_order = memory_order_seq_cst);
    T* fetch_sub(ptrdiff_t, memory_order = memory_order_seq_cst) volatile;
    T* fetch_sub(ptrdiff_t, memory_order = memory_order_seq_cst);

    atomic() = default;
    constexpr atomic(T*);
    atomic(const atomic&) = delete;
    atomic& operator=(const atomic&) = delete;
    atomic& operator=(const atomic&) volatile = delete;
    
    T* operator=(T*) volatile;
    T* operator=(T*);
    T* operator++(int) volatile;
    T* operator++(int);
    T* operator--(int) volatile;
    T* operator--(int);
    T* operator++() volatile;
    T* operator++();
    T* operator--() volatile;
    T* operator--();
    T* operator+=(ptrdiff_t) volatile;
    T* operator+=(ptrdiff_t);
    T* operator-=(ptrdiff_t) volatile;
    T* operator-=(ptrdiff_t);
};
```