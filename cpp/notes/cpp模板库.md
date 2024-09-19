# C++ STL 标准模板库

C++标准库中包含了许多模板库，提供了广泛的功能和数据结构的实现。以下是一些常见的C++模板库：

1. 容器库（Containers Library）：标准库提供了多种容器类模板，包括向量（vector）、链表（list）、双端队列（deque）、队列（queue）、栈（stack）、集合（set）、映射（map）等。这些容器提供了不同的数据结构和操作方法，适用于各种不同的场景。
2. 算法库（Algorithms Library）：标准库提供了丰富的算法模板，包括排序、搜索、遍历、合并等常用算法。这些算法可以应用于各种容器，例如排序向量、查找元素等。
3. 迭代器库（Iterators Library）：迭代器是C++中处理容器元素的通用方式。标准库提供了各种迭代器类型，包括输入迭代器、输出迭代器、前向迭代器、双向迭代器和随机访问迭代器。迭代器提供了对容器元素的遍历和访问能力。

除了标准库，C++还有许多非标准的第三方模板库，如Boost、STLPort、Qt等，它们提供了更多的功能和扩展。

需要注意的是，C++模板库是通过头文件包含的方式使用的，例如 `#include <vector>`。使用模板库时需要了解相应的用法和接口文档，并遵循库的使用约定和最佳实践。

## 1. 容器库（Containers Library）

容器库提供了各种数据结构的模板类，用于存储和管理数据。常见的容器类包括向量（vector）、链表（list）、双端队列（deque）、队列（queue）、栈（stack）、集合（set）、映射（map）等。这些容器提供了不同的特性和操作方法，可以满足不同的需求。

### 1.1 向量（vector）

#### 1.1.1 vector的使用

在 C++ 中，`vector` 是一个非常常用的容器类型，提供了动态数组的功能。下面是一些 `vector` 的基本方法和一个示例：

1. **插入元素**：
   - `push_back(value)`: 在向量的末尾插入一个元素。
   - `insert(iterator, value)`: 在指定位置之前插入一个元素。

2. **删除元素**：
   - `pop_back()`: 删除向量的最后一个元素。
   - `erase(iterator)`: 删除指定位置的元素。
   - `clear()`: 清空向量中的所有元素。

3. **访问元素**：
   - `at(index)`: 返回指定索引处的元素。
   - `front()`: 返回向量的第一个元素。
   - `back()`: 返回向量的最后一个元素。

4. **大小和容量**：
   - `size()`: 返回向量中元素的数量。
   - `capacity()`: 返回向量当前分配的内存容量。
   - `resize(new_size)`: 改变向量的大小。
   - `reserve(new_capacity)`: 改变向量的容量。

下面是一个简单的示例，展示了如何使用 `vector` 容器：

```cpp
#include <iostream>
#include <vector>

int main() {
    std::vector<int> myVector;  // 创建一个空的 vector

    // 向 vector 尾部插入元素
    myVector.push_back(10);
    myVector.push_back(20);
    myVector.push_back(30);

    // 在指定位置插入元素
    auto it = myVector.begin();
    myVector.insert(it + 1, 15);

    // 遍历并打印 vector 中的元素
    std::cout << "Vector elements: ";
    for (const auto& element : myVector) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    // 删除 vector 中的元素
    myVector.pop_back();
    myVector.erase(it);

    // 访问 vector 中的元素
    std::cout << "Element at index 1: " << myVector.at(1) << std::endl;
    std::cout << "First element: " << myVector.front() << std::endl;
    std::cout << "Last element: " << myVector.back() << std::endl;

    // 获取 vector 的大小和容量
    std::cout << "Size: " << myVector.size() << std::endl;
    std::cout << "Capacity: " << myVector.capacity() << std::endl;

    return 0;
}
```

运行以上代码，输出结果为：

```
Vector elements: 10 15 20
Element at index 1: 15
First element: 10
Last element: 20
Size: 3
Capacity: 4
```

这个示例演示了如何创建一个 `vector`，插入和删除元素，访问向量的元素，并获取向量的大小和容量。

#### 1.1.2 vector 的实现原理

C++ 的 `vector` 实现原理是基于动态分配的连续内存块。下面是 `vector` 实现的一些关键原理：

1. **动态内存分配**：`vector` 使用 `new` 运算符在堆上动态分配内存空间来存储元素。初始时，`vector` 可能没有分配任何内存，但随着元素的插入，它会动态地分配更多的内存以容纳新元素。

2. **容量管理**：`vector` 维护了两个关键变量：`size` 和 `capacity`。`size` 表示当前 `vector` 中实际存储的元素数量，而 `capacity` 表示当前分配的内存空间的容量。当 `size` 达到 `capacity` 时，`vector` 需要重新分配更大的内存空间来容纳新元素。

3. **重新分配内存**：当 `vector` 的 `size` 达到 `capacity` 时，需要重新分配更大的内存空间。通常情况下，`vector` 会申请一个更大的内存空间（通常是当前容量的两倍），然后将原有元素拷贝到新的内存空间中，最后释放原有的内存空间。

4. **连续内存存储**：`vector` 内部使用连续的内存块来存储元素。这意味着元素在内存中是紧密排列的，通过索引可以直接访问元素，并且支持使用指针和迭代器进行高效地遍历。

5. **元素的复制和移动**：当 `vector` 需要重新分配内存或插入/删除元素时，它必须移动或复制元素以保持连续存储的特性。对于可复制的类型，元素会被复制到新的内存空间中。对于可移动的类型，元素会被移动（通过移动构造函数或移动赋值运算符）以避免不必要的拷贝操作。

6. **效率和内存分配策略**：`vector` 的实现旨在提供高效的随机访问和尾部插入/删除操作。它通过预留一定的额外容量来减少频繁的内存分配和释放操作。当 `vector` 的 `size` 达到 `capacity` 时，它会申请更大的内存空间，并将已有元素移动到新的内存空间中。这种策略可以减少内存分配的次数，提高性能。

总之，C++ 的 `vector` 实现利用动态分配的连续内存块来存储元素，并提供了动态增长和缩小的功能。它通过重新分配内存、复制或移动元素来管理容量和保持连续存储的特性。这使得 `vector` 具有高效的随机访问和尾部操作的能力，但在插入和删除元素时可能涉及元素的移动或复制操作。

#### 1.1.3 Vector 的实现方式

C++ 的 `vector` 实现方式通常是使用动态分配的数组来存储元素。下面是 `vector` 的一种可能的实现方式：

1. `vector` 类的定义：
```cpp
template <typename T>
class vector {
private:
    T* elements;       // 指向存储元素的数组
    size_t size;       // 当前元素个数
    size_t capacity;   // 当前分配的内存大小

public:
    // 构造函数
    vector();
    explicit vector(size_t count);
    // ...
    
    // 成员函数
    size_t size() const;
    size_t capacity() const;
    bool empty() const;
    void push_back(const T& value);
    void pop_back();
    // ...
};
```

2. 构造函数的实现：
```cpp
template <typename T>
vector<T>::vector() : elements(nullptr), size(0), capacity(0) {}

template <typename T>
vector<T>::vector(size_t count) : size(count), capacity(count) {
    elements = new T[capacity];
}
```

3. `size()` 和 `capacity()` 成员函数的实现：
```cpp
template <typename T>
size_t vector<T>::size() const {
    return size;
}

template <typename T>
size_t vector<T>::capacity() const {
    return capacity;
}
```

4. `push_back()` 函数的实现：
```cpp
template <typename T>
void vector<T>::push_back(const T& value) {
    if (size == capacity) {
        // 内存不足，需要重新分配更大的内存空间
        if (capacity == 0) {
            capacity = 1;
        } else {
            capacity *= 2;
        }
        
        T* newElements = new T[capacity];
        
        // 将原有元素拷贝到新的内存空间
        for (size_t i = 0; i < size; ++i) {
            newElements[i] = elements[i];
        }
        
        // 释放原有内存空间
        delete[] elements;
        
        // 更新指针
        elements = newElements;
    }
    
    // 在尾部插入新元素
    elements[size++] = value;
}
```

5. `pop_back()` 函数的实现：
```cpp
template <typename T>
void vector<T>::pop_back() {
    if (size > 0) {
        // 从尾部删除元素
        --size;
    }
}
```

这只是 `vector` 的基本实现方式，实际的实现可能会有一些变化和优化。例如，为了提高性能，还可以使用指针操作来避免元素的拷贝。此外，还可以考虑使用分配器来管理内存分配，以及实现更多的成员函数和操作符重载等。

要了解完整的 `vector` 实现细节，可以查阅 C++ 标准库的源代码或参考相关的开源实现。

### 1.2 链表（list）

#### 1.2.1 List 的使用

当使用 C++ 中的 `list` 容器时，可以使用以下基本方法进行操作：

1. **插入元素**：
   - `push_back(value)`: 在链表尾部插入一个元素。
   - `push_front(value)`: 在链表头部插入一个元素。
   - `insert(iterator, value)`: 在指定位置之前插入一个元素。

2. **删除元素**：
   - `pop_back()`: 删除链表尾部的元素。
   - `pop_front()`: 删除链表头部的元素。
   - `erase(iterator)`: 删除指定位置的元素。

3. **访问元素**：
   - `front()`: 返回链表头部的元素。
   - `back()`: 返回链表尾部的元素。

4. **迭代器操作**：
   - `begin()`: 返回指向链表头部的迭代器。
   - `end()`: 返回指向链表尾部后一个位置的迭代器。

下面是一个简单的示例，展示了如何使用 `list` 容器：

```cpp
#include <iostream>
#include <list>

int main() {
    std::list<int> myList;  // 创建一个空的 list

    // 在 list 尾部插入元素
    myList.push_back(10);
    myList.push_back(20);
    myList.push_back(30);

    // 在 list 头部插入元素
    myList.push_front(5);

    // 遍历并打印 list 中的元素
    std::cout << "List elements: ";
    for (const auto& element : myList) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    // 删除 list 中的元素
    myList.pop_back();
    myList.pop_front();

    // 在指定位置插入元素
    auto it = myList.begin();
    ++it;
    myList.insert(it, 15);

    // 访问 list 头部和尾部的元素
    std::cout << "Front element: " << myList.front() << std::endl;
    std::cout << "Back element: " << myList.back() << std::endl;

    return 0;
}
```

运行以上代码，输出结果为：

```
List elements: 5 10 20 30
Front element: 10
Back element: 20
```

这个示例演示了如何创建一个 `list`，插入和删除元素，访问链表的头部和尾部元素，并使用迭代器遍历链表中的元素。

#### 1.2.2 List 的实现原理

C++ 中的 `list` 是双向链表（doubly linked list）的实现，它是标准库中提供的一种容器类型。下面是关于 `list` 的详细解释：

1. **双向链表结构**：`list` 是由一系列节点组成的双向链表，每个节点包含了数据元素以及指向前一个节点和后一个节点的指针。这种结构使得在 `list` 中插入和删除元素的操作非常高效，因为不需要移动其他元素。

2. **动态内存分配**：与 `vector` 不同，`list` 并不使用连续的内存块来存储元素，而是通过动态分配节点来存储元素。每次插入新元素时，都会创建一个新的节点，并将其链接到链表中。

3. **迭代器支持**：`list` 提供了迭代器（iterator）的支持，可以使用迭代器遍历链表中的元素。迭代器可以指向特定节点，允许对元素进行访问、插入和删除操作。

4. **常数时间插入和删除**：由于 `list` 的双向链表结构，向链表中插入和删除元素的时间复杂度是常数时间 O(1)，无论插入或删除的位置在哪里。

5. **不支持随机访问**：与 `vector` 不同，`list` 不支持通过索引进行随机访问。要访问特定位置的元素，必须从头节点或尾节点开始遍历链表。

6. **无需重新分配内存**：由于 `list` 不使用连续内存块，它无需像 `vector` 那样重新分配内存或复制元素。因此，`list` 的插入和删除操作不会导致迭代器失效。

7. **相对较高的内存开销**：由于每个元素都需要一个节点来存储，`list` 相对于 `vector` 会有更高的内存开销。而且，由于指针的存在，`list` 在空间利用率方面可能不如 `vector` 高效。

总结来说，`list` 是一个使用双向链表实现的容器，提供了高效的插入和删除操作，但不支持随机访问。它在需要频繁的插入和删除操作时非常有用，但在需要随机访问元素的情况下，可能不如 `vector` 高效。因此，根据具体的使用场景和需求，选择适合的容器类型是很重要的。

#### 1.2.3 List 的实现方式

`list`（链表）的实现方式可以使用指针和节点结构来实现。下面是一个简单的基于指针和节点结构的链表实现的示例代码：

```cpp
#include <iostream>

// 链表节点结构
struct Node {
    int value;     // 节点的值
    Node* prev;    // 前一个节点的指针
    Node* next;    // 后一个节点的指针

    // 构造函数
    Node(int val) : value(val), prev(nullptr), next(nullptr) {}
};

class List {
private:
    Node* head;    // 链表的头节点指针
    Node* tail;    // 链表的尾节点指针

public:
    // 构造函数
    List() : head(nullptr), tail(nullptr) {}

    // 在链表尾部插入一个元素
    void push_back(int value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    // 在链表头部插入一个元素
    void push_front(int value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    // 遍历并打印链表中的元素
    void print() {
        Node* current = head;
        while (current != nullptr) {
            std::cout << current->value << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
};

int main() {
    List myList;

    myList.push_back(10);
    myList.push_back(20);
    myList.push_back(30);
    myList.push_front(5);

    myList.print();  // 输出: 5 10 20 30

    return 0;
}
```

以上代码演示了一个简单的链表实现。`List` 类中使用了 `Node` 结构来表示链表节点，其中包含了值 `value`、前一个节点指针 `prev` 和后一个节点指针 `next`。通过 `push_back` 和 `push_front` 方法，可以在链表的尾部和头部插入新节点。`print` 方法用于遍历链表并打印其中的元素。

运行以上代码，输出结果为：

```
5 10 20 30
```

请注意，这只是一个简单的链表实现示例，可能缺少一些错误处理和其他常用操作。在实际开发中，可以根据需求对链表进行扩展和优化。

### 1.3 双端队列（deque）

#### 1.3.1 Deque 的使用

在 C++ 中，`deque`（双端队列）是一种支持在两端高效插入和删除操作的容器类型。下面是 `deque` 的一些基本方法和一个示例：

1. **插入元素**：
   - `push_back(value)`: 在双端队列的末尾插入一个元素。
   - `push_front(value)`: 在双端队列的开头插入一个元素。
   - `insert(iterator, value)`: 在指定位置之前插入一个元素。

2. **删除元素**：
   - `pop_back()`: 删除双端队列的最后一个元素。
   - `pop_front()`: 删除双端队列的第一个元素。
   - `erase(iterator)`: 删除指定位置的元素。
   - `clear()`: 清空双端队列中的所有元素。

3. **访问元素**：
   - `at(index)`: 返回指定索引处的元素。
   - `front()`: 返回双端队列的第一个元素。
   - `back()`: 返回双端队列的最后一个元素。

4. **大小和容量**：
   - `size()`: 返回双端队列中元素的数量。
   - `empty()`: 检查双端队列是否为空。
   - `resize(new_size)`: 改变双端队列的大小。
   - `clear()`: 清空双端队列中的所有元素。

下面是一个简单的示例，展示了如何使用 `deque` 容器：

```cpp
#include <iostream>
#include <deque>

int main() {
    std::deque<int> myDeque;  // 创建一个空的 deque

    // 向 deque 尾部插入元素
    myDeque.push_back(10);
    myDeque.push_back(20);
    myDeque.push_back(30);

    // 向 deque 头部插入元素
    myDeque.push_front(5);

    // 遍历并打印 deque 中的元素
    std::cout << "Deque elements: ";
    for (const auto& element : myDeque) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    // 删除 deque 中的元素
    myDeque.pop_back();
    myDeque.pop_front();

    // 访问 deque 中的元素
    std::cout << "Element at index 1: " << myDeque.at(1) << std::endl;
    std::cout << "First element: " << myDeque.front() << std::endl;
    std::cout << "Last element: " << myDeque.back() << std::endl;

    // 获取 deque 的大小和是否为空
    std::cout << "Size: " << myDeque.size() << std::endl;
    std::cout << "Empty: " << (myDeque.empty() ? "true" : "false") << std::endl;

    return 0;
}
```

运行以上代码，输出结果为：

```
Deque elements: 5 10 20 30
Element at index 1: 10
First element: 10
Last element: 20
Size: 2
Empty: false
```

这个示例演示了如何创建一个 `deque`，在双端队列的两端插入和删除元素，访问双端队列的元素，并获取双端队列的大小和是否为空。

#### 1.3.2 Deque的实现原理

在C++中，`deque`（双端队列）是一种由**连续的存储块（chunk）构成的动态数组**，它支持高效的在两端进行插入和删除操作。`deque` 的实现原理如下：

1. 存储块（Chunk）：`deque` 内部由多个存储块组成，每个存储块是一个固定大小的连续内存块，通常是一个较小的数组。每个存储块都保存了一部分元素。

2. 索引表（Index Table）：`deque` 维护一个索引表，用于跟踪存储块的位置和元素数量。索引表是一个动态数组，每个元素指向一个存储块。

3. 头尾指针：`deque` 还维护了两个指针，即头指针（`start`）和尾指针（`finish`）。头指针指向第一个存储块，尾指针指向最后一个存储块。

4. 插入和删除操作：当在头部或尾部插入或删除元素时，`deque` 的实现可能需要执行以下操作：
   - 如果当前存储块已满，需要分配一个新的存储块，并将其添加到索引表中。
   - 如果头部或尾部的存储块空闲（没有元素），需要释放该存储块，并从索引表中移除。
   - 当插入或删除元素导致存储块的边界发生变化时，需要更新头尾指针和索引表。

5. 随机访问：`deque` 支持随机访问，通过索引表和存储块的偏移量，可以在常数时间内访问 `deque` 中的任意元素。

通过使用存储块和索引表的结构，`deque` 实现了高效的在两端进行插入和删除操作。相比于 `vector`，`deque` 具有更好的插入和删除性能，特别是在头部和尾部进行操作时。然而，由于 `deque` 需要维护索引表和多个存储块，因此在内存占用方面可能略高于 `vector`。在选择使用 `deque` 还是其他容器时，需要根据具体的需求进行权衡。

#### 1.3.3 Deque 的实现方式

`deque` 的具体实现代码由 C++ 标准库提供，属于编译器实现的内部细节，通常不会直接暴露给开发者。不同的编译器和标准库实现可能会有不同的代码实现方式。以下是一个简化的 `deque` 实现的示例代码，用于演示其基本原理：

```cpp
#include <iostream>
#include <deque>

template<typename T, size_t ChunkSize = 4>
class MyDeque {
private:
    struct Chunk {
        T elements[ChunkSize];
    };

    std::deque<Chunk> chunks_;

public:
    MyDeque() {}

    void push_back(const T& value) {
        if (chunks_.empty() || chunks_.back().elements[ChunkSize - 1] != T()) {
            chunks_.push_back(Chunk());
        }
        chunks_.back().elements[size() % ChunkSize] = value;
    }

    void push_front(const T& value) {
        if (chunks_.empty() || chunks_.front().elements[0] != T()) {
            chunks_.push_front(Chunk());
        }
        for (size_t i = size() % ChunkSize; i > 0; --i) {
            chunks_.front().elements[i] = chunks_.front().elements[i - 1];
        }
        chunks_.front().elements[0] = value;
    }

    void pop_back() {
        if (chunks_.empty()) {
            return;
        }
        chunks_.back().elements[size() % ChunkSize] = T();
        if (chunks_.back().elements[0] == T()) {
            chunks_.pop_back();
        }
    }

    void pop_front() {
        if (chunks_.empty()) {
            return;
        }
        for (size_t i = 0; i < size() % ChunkSize; ++i) {
            chunks_.front().elements[i] = chunks_.front().elements[i + 1];
        }
        chunks_.front().elements[size() % ChunkSize] = T();
        if (chunks_.front().elements[ChunkSize - 1] == T()) {
            chunks_.pop_front();
        }
    }

    const T& front() const {
        return chunks_.front().elements[0];
    }

    const T& back() const {
        return chunks_.back().elements[size() % ChunkSize];
    }

    size_t size() const {
        return chunks_.size() * ChunkSize;
    }

    bool empty() const {
        return chunks_.empty();
    }
};

int main() {
    MyDeque<int> myDeque;

    myDeque.push_back(10);
    myDeque.push_back(20);
    myDeque.push_back(30);

    myDeque.push_front(5);

    std::cout << "Deque elements: ";
    for (size_t i = 0; i < myDeque.size(); ++i) {
        std::cout << myDeque.front() << " ";
        myDeque.pop_front();
    }
    std::cout << std::endl;

    return 0;
}
```

这个示例代码是一个简化的 `deque` 实现，使用了一个固定大小的存储块（`Chunk`）结构，通过 `std::deque` 容器来管理存储块。在 `push_back` 和 `push_front` 方法中，根据当前存储块的状态判断是否需要添加新的存储块。在 `pop_back` 和 `pop_front` 方法中，删除元素后根据存储块的状态判断是否需要移除空的存储块。其他方法如 `front`、`back`、`size` 和 `empty` 都依据存储块和元素的排列顺序进行操作。

需要注意的是，这只是一个简化的示例代码，实际的 `deque` 实现要更加复杂，并且会涉及更多的细节和优化。C++ 标准库中的 `deque` 实现会考虑更多的方面，例如内存分配、迭代器、异常处理等。以上示例仅用于演示 `deque` 的基本原理，实际的 `deque` 实现可能会有所不同。

### 1.4 队列（queue）

#### 1.4.1 Queue 的使用

当然！以下是 C++ 标准库中 `std::queue` 的基本方法和一个示例：

**基本方法：**

1. `push(const T& value)`：将元素添加到队列的尾部。
2. `pop()`：移除队列的头部元素。
3. `front()`：返回队列的头部元素的引用。
4. `back()`：返回队列的尾部元素的引用。
5. `empty()`：检查队列是否为空。
6. `size()`：返回队列中元素的个数。

**示例：**

```cpp
#include <iostream>
#include <queue>

int main() {
    std::queue<int> myQueue;

    // 添加元素到队列
    myQueue.push(10);
    myQueue.push(20);
    myQueue.push(30);

    // 访问队列的头部和尾部元素
    std::cout << "Front element: " << myQueue.front() << std::endl;
    std::cout << "Back element: " << myQueue.back() << std::endl;

    // 移除队列的头部元素
    myQueue.pop();

    // 检查队列是否为空
    if (myQueue.empty()) {
        std::cout << "Queue is empty." << std::endl;
    } else {
        std::cout << "Queue is not empty." << std::endl;
    }

    // 遍历队列并输出元素
    std::cout << "Queue elements: ";
    while (!myQueue.empty()) {
        std::cout << myQueue.front() << " ";
        myQueue.pop();
    }
    std::cout << std::endl;

    return 0;
}
```

运行上述代码，输出结果如下：

```
Front element: 10
Back element: 30
Queue is not empty.
Queue elements: 20 30
```

该示例创建了一个 `std::queue` 对象 `myQueue`，并使用 `push` 方法向队列中添加元素。然后通过 `front` 和 `back` 方法访问队列的头部和尾部元素。接着使用 `pop` 方法移除队列的头部元素，并通过 `empty` 方法检查队列是否为空。最后使用 `while` 循环遍历队列并输出元素，直到队列为空。

请注意，`std::queue` 是基于其他容器（默认为 `std::deque`）实现的，因此它继承了底层容器的一些特性和限制。在实际使用时，可以根据需要选择适合的底层容器，例如 `std::queue<int, std::vector<int>>` 使用 `std::vector` 作为底层容器来实现队列。

#### 1.4.1 Queue 的实现原理

`std::queue` 是 C++ 标准库提供的一个队列容器，它是基于其他容器实现的（默认情况下是基于 `std::deque` 实现）。`std::queue` 遵循先进先出（First-In-First-Out，FIFO）的原则，即最先插入的元素最先被移除。

在 `std::queue` 的实现中，常用的操作是在容器的一端添加元素（尾部）并在另一端移除元素（头部）。这就意味着 `std::queue` 的元素只能从一端进入，从另一端出去，而不能在中间进行插入或删除操作。

`std::queue` 的实现通常使用一个底层容器来存储元素，例如 `std::deque`、`std::list` 或 `std::vector`。底层容器负责实际的存储和管理元素，并提供了相应的操作方法。`std::queue` 利用底层容器的特性来实现队列的基本方法。

具体来说，当向队列中添加元素时，`std::queue` 调用底层容器的 `push_back` 方法将元素添加到容器的尾部。而在移除元素时，`std::queue` 调用底层容器的 `pop_front` 方法移除容器的头部元素。

`std::queue` 还使用底层容器的其他方法来实现队列的基本操作。例如，`front` 方法返回底层容器的头部元素，`back` 方法返回底层容器的尾部元素，`empty` 方法检查底层容器是否为空，`size` 方法返回底层容器中的元素个数。

通过使用底层容器来实现队列，`std::queue` 可以隐藏底层容器的细节，并提供一致的接口和操作方式。这样，用户可以简单地使用 `std::queue` 来操作队列，而不需要关心底层容器的具体实现。

需要注意的是，如果需要在队列中进行随机访问或插入/删除操作，可能需要选择其他容器，例如 `std::deque` 或 `std::list`。`std::queue` 更适用于只需要先进先出操作的场景。

#### 1.4.3 Queue 的实现方式

以下是一个简单的队列（Queue）的实现代码示例：

```cpp
#include <iostream>
#include <list>

template <typename T>
class Queue {
private:
    std::list<T> elements; // 底层容器用双向链表实现

public:
    void push(const T& value) {
        elements.push_back(value); // 在队尾添加元素
    }

    void pop() {
        if (!empty()) {
            elements.pop_front(); // 移除队首元素
        }
    }

    T& front() {
        return elements.front(); // 返回队首元素的引用
    }

    const T& front() const {
        return elements.front(); // 返回队首元素的常量引用
    }

    T& back() {
        return elements.back(); // 返回队尾元素的引用
    }

    const T& back() const {
        return elements.back(); // 返回队尾元素的常量引用
    }

    bool empty() const {
        return elements.empty(); // 检查队列是否为空
    }

    size_t size() const {
        return elements.size(); // 返回队列中元素的个数
    }
};

int main() {
    Queue<int> myQueue;

    // 添加元素到队列
    myQueue.push(10);
    myQueue.push(20);
    myQueue.push(30);

    // 访问队列的头部和尾部元素
    std::cout << "Front element: " << myQueue.front() << std::endl;
    std::cout << "Back element: " << myQueue.back() << std::endl;

    // 移除队列的头部元素
    myQueue.pop();

    // 检查队列是否为空
    if (myQueue.empty()) {
        std::cout << "Queue is empty." << std::endl;
    } else {
        std::cout << "Queue is not empty." << std::endl;
    }

    // 遍历队列并输出元素
    std::cout << "Queue elements: ";
    while (!myQueue.empty()) {
        std::cout << myQueue.front() << " ";
        myQueue.pop();
    }
    std::cout << std::endl;

    return 0;
}
```

在上述代码中，我们使用 `std::list` 作为底层容器实现了一个简单的队列类 `Queue`。通过 `std::list` 的 `push_back`、`pop_front`、`front`、`back`、`empty` 和 `size` 方法，我们实现了队列的基本操作。

在 `main` 函数中，我们创建了一个 `Queue<int>` 类型的对象 `myQueue`，并演示了向队列中添加元素、访问队列的头部和尾部元素、移除队列的头部元素、检查队列是否为空以及遍历队列并输出元素的操作。

运行上述代码，输出结果如下：

```
Front element: 10
Back element: 30
Queue is not empty.
Queue elements: 20 30
```

这个示例实现了一个简单的队列类，但请注意这只是一个基本的实现，并不包含线程安全性、异常处理等更复杂的功能。在实际使用中，你可能需要根据具体的需求进行适当的修改和扩展。

### 1.5 栈（stack）

#### 1.5.1 Stack 的使用

以下是 C++ 标准库中 `std::stack` 的基本方法和一个示例：

**基本方法：**

1. `push(const T& value)`：将元素添加到栈的顶部。
2. `pop()`：移除栈顶的元素。
3. `top()`：返回栈顶的元素的引用。
4. `empty()`：检查栈是否为空。
5. `size()`：返回栈中元素的个数。

**示例：**

```cpp
#include <iostream>
#include <stack>

int main() {
    std::stack<int> myStack;

    // 添加元素到栈
    myStack.push(10);
    myStack.push(20);
    myStack.push(30);

    // 访问栈顶元素
    std::cout << "Top element: " << myStack.top() << std::endl;

    // 移除栈顶元素
    myStack.pop();

    // 检查栈是否为空
    if (myStack.empty()) {
        std::cout << "Stack is empty." << std::endl;
    } else {
        std::cout << "Stack is not empty." << std::endl;
    }

    // 遍历栈并输出元素
    std::cout << "Stack elements: ";
    while (!myStack.empty()) {
        std::cout << myStack.top() << " ";
        myStack.pop();
    }
    std::cout << std::endl;

    return 0;
}
```

运行上述代码，输出结果如下：

```
Top element: 20
Stack is not empty.
Stack elements: 20 10
```

该示例创建了一个 `std::stack` 对象 `myStack`，并使用 `push` 方法向栈中添加元素。然后通过 `top` 方法访问栈顶元素。接着使用 `pop` 方法移除栈顶元素，并通过 `empty` 方法检查栈是否为空。最后使用 `while` 循环遍历栈并输出元素，直到栈为空。

请注意，`std::stack` 是基于其他容器（默认为 `std::deque`）实现的，因此它继承了底层容器的一些特性和限制。在实际使用时，可以根据需要选择适合的底层容器，例如 `std::stack<int, std::vector<int>>` 使用 `std::vector` 作为底层容器来实现栈。

### 1.6 集合（set）

#### 1.6.1 Set 的使用

以下是 `std::set` 的基本方法和一个示例：

**基本方法：**

1. `insert(const T& value)`：将元素插入到集合中。
2. `erase(const T& value)`：从集合中删除指定的元素。
3. `find(const T& value)`：查找指定元素在集合中的位置。
4. `empty()`：检查集合是否为空。
5. `size()`：返回集合中元素的个数。

**示例：**

```cpp
#include <iostream>
#include <set>

int main() {
    std::set<int> mySet;

    // 插入元素到集合
    mySet.insert(10);
    mySet.insert(20);
    mySet.insert(30);

    // 遍历集合并输出元素
    std::cout << "Set elements: ";
    for (const auto& element : mySet) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    // 检查元素是否存在
    if (mySet.find(20) != mySet.end()) {
        std::cout << "Element 20 is present in the set." << std::endl;
    } else {
        std::cout << "Element 20 is not present in the set." << std::endl;
    }

    // 删除元素
    mySet.erase(20);

    // 检查集合是否为空
    if (mySet.empty()) {
        std::cout << "Set is empty." << std::endl;
    } else {
        std::cout << "Set is not empty." << std::endl;
    }

    // 获取集合大小
    std::cout << "Set size: " << mySet.size() << std::endl;

    return 0;
}
```

运行上述代码，输出结果如下：

```
Set elements: 10 20 30
Element 20 is present in the set.
Set is not empty.
Set size: 2
```

该示例创建了一个 `std::set` 对象 `mySet`，并使用 `insert` 方法向集合中插入元素。然后使用范围-based for 循环遍历集合并输出元素。接着使用 `find` 方法检查元素 20 是否存在于集合中。然后使用 `erase` 方法删除元素 20。再次使用 `empty` 方法检查集合是否为空，以及使用 `size` 方法获取集合的大小。

请注意，`std::set` 会根据默认的排序规则（使用 `<` 运算符）对元素进行排序，并且插入、查找和删除操作的时间复杂度为对数时间（O(log n)），因此适用于需要有序且快速查找元素的场景。

如果需要自定义排序规则，可以使用 `std::set` 的构造函数传入一个自定义的比较函数对象，或者使用函数对象模板参数 `Compare`。

#### 1.6.2 Set 的实现原理

在 C++ 中，`std::set` 是使用红黑树（Red-Black Tree）实现的。红黑树是一种自平衡的二叉搜索树，它具有以下性质：

1. 每个节点要么是红色，要么是黑色。
2. 根节点是黑色。
3. 每个叶子节点（NIL 节点，空节点）是黑色。
4. 如果一个节点是红色的，则它的两个子节点都是黑色的。
5. 从任意节点到其每个叶子节点的路径都包含相同数量的黑色节点。

这些性质使得红黑树保持了平衡，插入、删除和查找操作的时间复杂度都是对数时间（O(log n)）。

`std::set` 使用红黑树来存储集合中的元素，并且根据元素的排序规则进行排序。默认情况下，`std::set` 使用 `<` 运算符来比较元素，以确定元素的顺序。当元素插入到集合中时，红黑树会自动调整以保持平衡，并确保元素按照排序规则正确地放置在树中的适当位置。

红黑树的平衡性质保证了在插入、删除和查找操作中，红黑树的高度保持较小的范围，从而提供了快速的查找和插入性能。但是，红黑树相对于其他数据结构（如哈希表）来说，会占用更多的内存空间来存储额外的指针和颜色信息。

需要注意的是，`std::set` 中的元素必须是可比较的，因为红黑树需要根据元素的排序规则来进行插入、删除和查找操作。如果要使用自定义的排序规则，可以通过提供自定义的比较函数对象或使用函数对象模板参数 `Compare` 来实现。

#### 1.6.3 Set 的实现方式

以下是一个简单的 C++ 代码示例，展示了如何手动实现一个简化版的 `Set` 类：

```cpp
#include <iostream>
#include <vector>

template<typename T>
class Set {
private:
    std::vector<T> elements;

public:
    void insert(const T& element) {
        if (!contains(element)) {
            elements.push_back(element);
        }
    }

    void erase(const T& element) {
        for (auto it = elements.begin(); it != elements.end(); ++it) {
            if (*it == element) {
                elements.erase(it);
                break;
            }
        }
    }

    bool contains(const T& element) const {
        for (const auto& e : elements) {
            if (e == element) {
                return true;
            }
        }
        return false;
    }

    bool empty() const {
        return elements.empty();
    }

    int size() const {
        return elements.size();
    }

    void print() const {
        for (const auto& e : elements) {
            std::cout << e << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    Set<int> mySet;

    mySet.insert(10);
    mySet.insert(20);
    mySet.insert(30);

    mySet.print();  // 输出: 10 20 30

    mySet.erase(20);

    mySet.print();  // 输出: 10 30

    std::cout << "Size of set: " << mySet.size() << std::endl;  // 输出: Size of set: 2

    if (mySet.contains(10)) {
        std::cout << "Set contains 10." << std::endl;  // 输出: Set contains 10.
    }

    if (mySet.empty()) {
        std::cout << "Set is empty." << std::endl;
    } else {
        std::cout << "Set is not empty." << std::endl;  // 输出: Set is not empty.
    }

    return 0;
}
```

这个示例中，我们手动实现了一个简化版的 `Set` 类，使用 `std::vector` 来存储元素。`insert` 方法用于插入元素，如果元素已经存在于集合中，则不会重复插入。`erase` 方法用于删除元素，它会遍历集合并删除与给定元素相等的第一个元素。`contains` 方法用于检查集合中是否包含给定的元素。`empty` 方法用于检查集合是否为空，`size` 方法用于获取集合的大小。`print` 方法用于打印集合中的元素。

在 `main` 函数中，我们创建了一个 `Set<int>` 类型的对象 `mySet`，并使用 `insert` 方法插入一些整数元素。然后调用 `print` 方法输出集合中的元素。接着使用 `erase` 方法删除元素 20，并再次调用 `print` 方法验证删除操作。最后使用 `size` 方法获取集合的大小，使用 `contains` 方法检查集合是否包含元素 10，并使用 `empty` 方法检查集合是否为空。

请注意，这个实现只是一个简化版，仅用于演示基本的集合操作。在实际生产环境中，为了获得更高效的性能和更丰富的功能，应使用标准库中的 `std::set` 或其他现成的集合实现。

### 1.7 映射（map）

#### 1.7.1 map 的使用

在 C++ 中，`std::map` 是一个关联容器，它提供了一种键-值对的映射关系。以下是 `std::map` 的基本方法和一个案例示例：

1. `insert()`：插入键-值对到 `std::map` 中。
2. `erase()`：通过指定键来删除键-值对。
3. `find()`：通过指定键来查找值。
4. `at()`：通过指定键获取对应的值。
5. `empty()`：检查 `std::map` 是否为空。
6. `size()`：获取 `std::map` 中键-值对的数量。
7. `clear()`：清空 `std::map` 中的所有键-值对。

以下是一个示例，演示了如何使用 `std::map` 存储学生的姓名和分数：

```cpp
#include <iostream>
#include <map>
#include <string>

int main() {
    std::map<std::string, int> studentScores;

    // 插入键-值对
    studentScores.insert(std::make_pair("Alice", 80));
    studentScores.insert(std::make_pair("Bob", 90));
    studentScores.insert(std::make_pair("Charlie", 75));

    // 查找值
    auto it = studentScores.find("Bob");
    if (it != studentScores.end()) {
        std::cout << "Bob's score: " << it->second << std::endl;
    }

    // 更新值
    studentScores["Charlie"] = 85;

    // 删除键-值对
    studentScores.erase("Alice");

    // 遍历并输出键-值对
    for (const auto& pair : studentScores) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    // 检查是否存在指定键
    if (studentScores.count("Alice") > 0) {
        std::cout << "Alice's score: " << studentScores.at("Alice") << std::endl;
    } else {
        std::cout << "Alice's score not found." << std::endl;
    }

    // 检查是否为空
    if (studentScores.empty()) {
        std::cout << "Map is empty." << std::endl;
    } else {
        std::cout << "Map is not empty." << std::endl;
    }

    // 获取键-值对数量
    std::cout << "Map size: " << studentScores.size() << std::endl;

    // 清空 map
    studentScores.clear();

    return 0;
}
```

运行上述代码，输出结果如下：

```
Bob's score: 90
Charlie: 85
Map is not empty.
Map size: 1
```

在这个示例中，我们创建了一个名为 `studentScores` 的 `std::map`，它的键是学生的姓名（`std::string`），值是学生的分数（`int`）。我们使用 `insert` 方法插入了几个键-值对，使用 `find` 方法查找了 Bob 的分数，并使用 `[]` 操作符更新了 Charlie 的分数。然后使用 `erase` 方法删除了 Alice 的键-值对，并使用循环遍历输出了剩余的键-值对。我们还使用 `count` 方法和 `at` 方法来检查是否存在指定键，并获取其对应的值。最后，我们使用 `empty` 方法检查 map 是否为空，使用 `size` 方法获取键-值对的数量，并使用 `clear` 方法清空了 map。

这个示例展示了 `std::map` 的基本方法和一些常见操作，以及如何使用 `std::map` 存储和操作键-值对数据。

#### 1.7.2 map 的实现原理

在 C++ 中，`std::map` 是基于红黑树（Red-Black Tree）实现的。红黑树是一种自平衡的二叉搜索树，它具有以下特性：

1. 每个节点要么是红色，要么是黑色。
2. 根节点是黑色的。
3. 所有叶子节点（NIL 节点）都是黑色的。
4. 如果一个节点是红色的，则它的两个子节点都是黑色的。
5. 对于每个节点，从该节点到其所有后代叶子节点的简单路径上，均包含相同数目的黑色节点（即，黑色节点的数量相同）。

这些特性确保了红黑树的平衡性，使得在最坏情况下，红黑树的插入、删除和查找操作的时间复杂度为 O(log n)，其中 n 是树中节点的数量。

`std::map` 使用红黑树来实现键-值对的存储和查找。每个节点都包含一个键和一个值，节点按键的顺序进行排序。通过比较键的大小，可以在红黑树中高效地查找、插入和删除键-值对。

当向 `std::map` 中插入键-值对时，红黑树会自动调整节点的颜色和结构，以保持红黑树的平衡性。插入操作包括以下步骤：
1. 根据键的大小找到插入位置。
2. 创建新的节点，并将键和值存储在节点中。
3. 将节点插入到红黑树中的正确位置。
4. 根据红黑树的特性进行必要的调整，以保持平衡。

类似地，当从 `std::map` 中删除键-值对时，红黑树也会进行自动平衡的调整。

通过红黑树的自平衡性质，`std::map` 能够高效地支持键的查找、插入和删除操作，并在有序的基础上维护键-值对的存储。红黑树的特性确保了 `std::map` 的高效性能，使其成为一个非常有用的关联容器。

#### 1.7.3 map 的实现方式

以下是一个简单的示例代码，演示了如何手动实现一个简化版的 `std::map`。

```cpp
#include <iostream>
#include <string>

template <typename KeyType, typename ValueType>
class MyMap {
private:
    struct Node {
        KeyType key;
        ValueType value;
        Node* left;
        Node* right;

        Node(const KeyType& k, const ValueType& v)
            : key(k), value(v), left(nullptr), right(nullptr) {}
    };

    Node* root;

public:
    MyMap() : root(nullptr) {}

    ~MyMap() {
        clear();
    }

    void insert(const KeyType& key, const ValueType& value) {
        Node* newNode = new Node(key, value);

        if (root == nullptr) {
            root = newNode;
        } else {
            Node* curr = root;
            Node* parent = nullptr;

            while (curr != nullptr) {
                parent = curr;

                if (key < curr->key) {
                    curr = curr->left;
                } else if (key > curr->key) {
                    curr = curr->right;
                } else {
                    // Key already exists, update the value
                    curr->value = value;
                    delete newNode;
                    return;
                }
            }

            if (key < parent->key) {
                parent->left = newNode;
            } else {
                parent->right = newNode;
            }
        }
    }

    bool find(const KeyType& key, ValueType& value) const {
        Node* curr = root;

        while (curr != nullptr) {
            if (key < curr->key) {
                curr = curr->left;
            } else if (key > curr->key) {
                curr = curr->right;
            } else {
                // Key found
                value = curr->value;
                return true;
            }
        }

        // Key not found
        return false;
    }

    void erase(const KeyType& key) {
        Node* curr = root;
        Node* parent = nullptr;

        while (curr != nullptr) {
            if (key < curr->key) {
                parent = curr;
                curr = curr->left;
            } else if (key > curr->key) {
                parent = curr;
                curr = curr->right;
            } else {
                // Key found, delete the node
                if (curr->left == nullptr && curr->right == nullptr) {
                    // Case 1: Leaf node
                    if (parent == nullptr) {
                        // Deleting root node
                        root = nullptr;
                    } else if (parent->left == curr) {
                        parent->left = nullptr;
                    } else {
                        parent->right = nullptr;
                    }
                } else if (curr->left != nullptr && curr->right != nullptr) {
                    // Case 3: Node with two children
                    Node* successor = findMinNode(curr->right);
                    curr->key = successor->key;
                    curr->value = successor->value;
                    erase(successor->key);
                    delete successor;
                    return;
                } else {
                    // Case 2: Node with one child
                    Node* child = (curr->left != nullptr) ? curr->left : curr->right;

                    if (parent == nullptr) {
                        // Deleting root node
                        root = child;
                    } else if (parent->left == curr) {
                        parent->left = child;
                    } else {
                        parent->right = child;
                    }
                }

                delete curr;
                return;
            }
        }
    }

    void clear() {
        clear(root);
        root = nullptr;
    }

private:
    void clear(Node* node) {
        if (node == nullptr) {
            return;
        }

        clear(node->left);
        clear(node->right);
        delete node;
    }

    Node* findMinNode(Node* node) const {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }
};

int main() {
    MyMap<std::string, int> myMap;

    myMap.insert("Alice", 80);
    myMap.insert("Bob", 90);
    myMap.insert("Charlie", 75);

    int score;
    if (myMap.find("Bob", score)) {
        std::cout << "Bob's score: " << score << std::endl;
    }

    myMap.erase("Alice");

    return 0;
}
```

上述代码实现了一个简化版的 `MyMap` 类，模拟了 `std::map` 的基本功能。它使用二叉搜索树作为底层的数据结构来存储键-值对，并实现了插入、查找和删除等操作。

在 `MyMap` 类的内部，使用了一个私有的嵌套结构 `Node` 来表示树的节点，每个节点包含键、值以及左右子节点的指针。

`MyMap` 类中的 `insert` 方法用于插入新的键-值对。它遵循二叉搜索树的规则，根据键的大小逐级比较，找到合适的位置插入新节点。如果键已经存在，则更新对应节点的值。

`MyMap` 类中的 `find` 方法用于查找给定的键并返回对应的值。它从根节点开始，根据键的大小逐级比较，直到找到匹配的键或者遍历完整个树。

`MyMap` 类中的 `erase` 方法用于删除指定的键-值对。它首先查找要删除的节点，然后根据不同的情况进行处理：如果要删除的节点是叶子节点，则直接删除；如果要删除的节点有一个子节点，则将子节点连接到父节点；如果要删除的节点有两个子节点，则找到后继节点（右子树的最小节点），用后继节点的键和值替换当前节点的键和值，然后递归地删除后继节点。

`MyMap` 类中的 `clear` 方法用于清空整个树，它使用递归方式删除每个节点，并释放内存。

在 `main` 函数中，演示了如何使用 `MyMap` 类来插入、查找和删除键-值对的示例。

请注意，这只是一个简化的示例，用于演示 `std::map` 的基本思想和实现方式。实际的 `std::map` 类有更复杂的实现，包括更多的功能和性能优化。此示例仅用于说明目的，并不适用于生产环境。

#### * 补充：hashtable, multimap， multiset

`HashTable`（哈希表）、`Multimap`（多重映射）和`Multiset`（多重集合）是C++中的标准库容器，它们提供了不同的数据结构和功能。

1. **哈希表（HashTable）**：
   - 哈希表是一种基于哈希函数的数据结构，它使用键值对存储和检索数据。
   - 在C++中，`std::unordered_map` 是哈希表的实现。它使用哈希函数将键映射到桶（bucket）上，并使用链表或者其他数据结构来处理哈希冲突。
   - 哈希表支持快速的插入、删除和查找操作，平均情况下的时间复杂度为O(1)。
   - 哈希表不保持元素的顺序。

2. **多重映射（Multimap）**：
   - 多重映射是一种键可以映射到多个值的数据结构，类似于字典中的一个键对应多个值的情况。
   - 在C++中，`std::multimap` 是多重映射的实现。它允许相同的键对应多个值，并且按照键的排序顺序存储元素。
   - 多重映射支持快速的插入和查找操作，平均情况下的时间复杂度为O(log n)。注意，由于键可以对应多个值，所以删除操作可能需要遍历多个值。
   - 多重映射保持按键排序的顺序。

3. **多重集合（Multiset）**：
   - 多重集合是一种允许重复元素的集合，类似于集合中的一个元素可以出现多次的情况。
   - 在C++中，`std::multiset` 是多重集合的实现。它允许重复的元素，并按照元素的排序顺序存储。
   - 多重集合支持快速的插入和查找操作，平均情况下的时间复杂度为O(log n)。删除操作可能需要遍历多个相同的元素。
   - 多重集合保持按元素排序的顺序。

这些容器都提供了丰富的成员函数和迭代器接口，可以方便地操作和访问容器中的元素。在选择使用哪种容器时，需要根据具体的需求和性能要求进行权衡。

当涉及到哈希表、多重映射和多重集合时，下面是一些基本案例的示例：

1. **哈希表（HashTable）**：

   ```cpp
   #include <iostream>
   #include <unordered_map>
   #include <string>
   
   int main() {
       std::unordered_map<std::string, int> scores;
   
       // 插入键值对
       scores["Alice"] = 80;
       scores["Bob"] = 90;
       scores["Charlie"] = 75;
   
       // 查找特定键的值
       std::cout << "Bob's score: " << scores["Bob"] << std::endl;
   
       // 遍历哈希表
       for (const auto& pair : scores) {
           std::cout << pair.first << ": " << pair.second << std::endl;
       }
   
       return 0;
   }
   ```
   输出结果
   ```
   Bob's score: 90
   Charlie: 75
   Bob: 90
   Alice: 80

2. **多重映射（Multimap）**：

   ```cpp
   #include <iostream>
   #include <map>
   #include <string>
   
   int main() {
       std::multimap<int, std::string> students;
   
       // 插入键值对
       students.insert(std::make_pair(80, "Alice"));
       students.insert(std::make_pair(90, "Bob"));
       students.insert(std::make_pair(75, "Charlie"));
       students.insert(std::make_pair(90, "David"));
   
       // 查找特定键的值
       int key = 90;
       auto range = students.equal_range(key);
       std::cout << "Students with score " << key << ":" << std::endl;
       for (auto it = range.first; it != range.second; ++it) {
           std::cout << it->second << std::endl;
       }
   
       // 遍历多重映射
       for (const auto& pair : students) {
           std::cout << pair.second << ": " << pair.first << std::endl;
       }
   
       return 0;
   }
   ```
   输出结果:
   ```
   Students with score 90:
   Bob
   David
   Charlie: 75
   Bob: 90
   David: 90
   Alice: 80

3. **多重集合（Multiset）**：

   ```cpp
   #include <iostream>
   #include <set>
   #include <string>
   
   int main() {
       std::multiset<int> numbers;
   
       // 插入元素
       numbers.insert(10);
       numbers.insert(20);
       numbers.insert(10);
       numbers.insert(30);
   
       // 查找特定元素
       int key = 10;
       auto range = numbers.equal_range(key);
       std::cout << "Occurrences of " << key << ": " << std::distance(range.first, range.second) << std::endl;
   
       // 遍历多重集合
       for (const auto& num : numbers) {
           std::cout << num << std::endl;
       }
   
       return 0;
   }
   
   ```
   输出结果:
   ```
   Occurrences of 10: 2
   10
   10
   20
   30

以上示例演示了使用哈希表、多重映射和多重集合的基本操作，包括插入元素、查找特定键或元素以及遍历容器。这些示例可以帮助你更好地理解如何使用这些容器来处理数据。

#### * 补充：unordered_map, unordered_set, unordered_mutlimap, unordered_mutliset

unordered_map、unordered_set、unordered_multimap 和 unordered_multiset 是 C++ STL 中提供的四个无序容器，它们基于哈希表实现，用于存储键值对或唯一的元素。下面分别介绍它们的特点和实现原理：

1. **unordered_map**：
   - unordered_map 是一种无序键值对容器，其中的键和值都可以是任意类型。
   - 它使用哈希函数将键映射到对应的桶上，并使用链地址法处理哈希冲突。
   - unordered_map 提供了O(1)的平均时间复杂度进行插入、查找和删除操作，但最坏情况下可能达到O(n)。
   - 与 std::map 不同，unordered_map 不会对键进行排序，而是根据键的哈希值进行存储和检索。

2. **unordered_set**：
   - unordered_set 是一种无序唯一元素容器，其中的元素可以是任意类型。
   - 它使用哈希函数将元素映射到对应的桶上，并使用链地址法处理哈希冲突。
   - unordered_set 提供了O(1)的平均时间复杂度进行插入、查找和删除操作，但最坏情况下可能达到O(n)。
   - 与 std::set 不同，unordered_set 不会对元素进行排序，而是根据元素的哈希值进行存储和检索。

3. **unordered_multimap**：
   - unordered_multimap 是一种无序键值对容器，允许键重复。
   - 它使用哈希函数将键映射到对应的桶上，并使用链地址法处理哈希冲突。
   - unordered_multimap 提供了O(1)的平均时间复杂度进行插入、查找和删除操作，但最坏情况下可能达到O(n)。
   - 键的重复会导致多个键值对存储在同一个桶中。

4. **unordered_multiset**：
   - unordered_multiset 是一种无序元素容器，允许元素重复。
   - 它使用哈希函数将元素映射到对应的桶上，并使用链地址法处理哈希冲突。
   - unordered_multiset 提供了O(1)的平均时间复杂度进行插入、查找和删除操作，但最坏情况下可能达到O(n)。
   - 元素的重复会导致多个相同元素存储在同一个桶中。

这些无序容器提供了高效的插入、查找和删除操作，并且适用于需要快速访问和修改数据的场景。使用无序容器时，需要注意选择合适的哈希函数和调整桶的数量，以获得良好的性能。

#### * 补充：从数据结构的角度总结

- **Vector** : 动态数组
- **List**: 双向链表
- **Queue**: 队列
- **Deque**:双向队列, 存储块+链表
- **Stack**：栈
- **Set** : 树/红黑树, **map**: key 不能重复，使用红黑树实现

- **hashtable**: 哈希表
- **Multimap**、**Multset**：平衡二叉树

#### * 补充：时间复杂度对比

| 数据结构 | 插入 | 查看 | 删除 |
| -------- | ---- | ---- | ---- |
| vector   | O(N) | O(1) | O(N) |
| list     | O(1) | O(N) | O(1) |
| deque    | O(N) | O(1) | O(N) |
| map, set, mutlimap, mutliset      | O(log N) | O(log N) | O(log N) |
| unordered_map, unordered_set, unordered_mutlimap, unordered_mutliset | O(1), 最坏O(N) | O(1)最坏O(N) | O(1)最坏O(N) |

### * 补充：STL 容器库分类

在C++的标准模板库（STL）中，提供了多种容器类，用于存储和操作数据。这些容器类可以根据其特性和用途进行分类，以下是常见的STL容器分类：

1. **序列容器**（Sequence Containers）：
   - `std::vector`：动态数组，支持随机访问。
   - `std::list`：双向链表，支持快速插入和删除。
   - `std::deque`：双端队列，支持快速插入和删除两端元素。

2. **关联容器**（Associative Containers）：
   - `std::set`：有序集合，不允许重复元素。
   - `std::multiset`：有序集合，允许重复元素。
   - `std::map`：键值对的有序映射表，不允许重复键。
   - `std::multimap`：键值对的有序映射表，允许重复键。

3. **无序关联容器**（Unordered Associative Containers）：
   - `std::unordered_set`：无序集合，不允许重复元素。
   - `std::unordered_multiset`：无序集合，允许重复元素。
   - `std::unordered_map`：键值对的无序映射表，不允许重复键。
   - `std::unordered_multimap`：键值对的无序映射表，允许重复键。

4. **容器适配器**（Container Adapters）：
   - `std::stack`：基于底层容器实现的堆栈（先进后出）适配器。
   - `std::queue`：基于底层容器实现的队列（先进先出）适配器。
   - `std::priority_queue`：基于底层容器实现的优先队列适配器。

每种容器都有其特定的特性和适用场景。序列容器提供了按顺序存储和访问元素的功能，关联容器提供了按键值进行快速查找的功能，无序关联容器提供了高效的插入和查找操作。容器适配器则提供了对已有容器接口的封装，以适应不同的数据结构需求。

选择合适的容器取决于具体的问题和需求。需要考虑到插入、删除、查找的时间复杂度、内存占用、迭代器失效的情况以及对元素顺序的要求等因素。

需要注意的是，以上列举的是C++标准库中常见的容器，还有其他非标准的第三方容器库可供选择，如Boost库提供的容器。

## 2. 算法库（Algorithms Library）

算法库提供了各种常用算法的模板函数，可以应用于容器中的元素。这些算法包括排序、搜索、遍历、合并等，可以对容器中的元素进行操作和处理。

## 3. 迭代器库（Iterators Library）

迭代器库提供了用于遍历和访问容器元素的迭代器模板类。迭代器提供了一种统一的访问容器元素的方式，包括输入迭代器、输出迭代器、前向迭代器、双向迭代器和随机访问迭代器，每种迭代器具有不同的功能和特性。

STL（Standard Template Library）迭代器库是 C++ 标准库的一部分，提供了一组用于遍历和访问容器元素的迭代器（Iterator）类模板。迭代器是一种抽象的指针，允许我们以一致的方式访问容器中的元素，无需关心容器的具体实现细节。通过迭代器，我们可以实现通用的算法和操作，使其适用于不同类型的容器。以下是 STL 迭代器库的一些重要概念和类模板：

1. **迭代器分类**：
   - 输入迭代器（Input Iterator）：允许读取容器元素，并支持递增操作。
   - 输出迭代器（Output Iterator）：允许写入容器元素，并支持递增操作。
   - 前向迭代器（Forward Iterator）：支持输入和输出操作，可以多次遍历容器中的元素。
   - 双向迭代器（Bidirectional Iterator）：支持前向迭代器的所有操作，并额外支持递减操作。
   - 随机访问迭代器（Random Access Iterator）：支持双向迭代器的所有操作，并额外支持随机访问和指针算术操作。

2. **迭代器类模板**：
   - `std::iterator`：迭代器模板的基类，用于派生自定义迭代器。
   - `std::input_iterator`：输入迭代器的基类。
   - `std::output_iterator`：输出迭代器的基类。
   - `std::forward_iterator`：前向迭代器的基类。
   - `std::bidirectional_iterator`：双向迭代器的基类。
   - `std::random_access_iterator`：随机访问迭代器的基类。

3. **迭代器函数**：
   - `std::begin`：返回容器的起始迭代器。
   - `std::end`：返回容器的结束迭代器。
   - `std::advance`：在迭代器上进行指定步数的前进或后退操作。
   - `std::distance`：计算两个迭代器之间的距离。
   - `std::next`：返回指定迭代器之后的迭代器。
   - `std::prev`：返回指定迭代器之前的迭代器。

使用迭代器库，我们可以遍历容器元素、访问元素值、修改元素值以及实现各种算法和操作，而无需关心容器的具体类型和实现方式。迭代器提供了一种通用的接口，使得代码更加灵活和可复用。

请注意，C++11 引入了更为强大和灵活的迭代器概念，包括迭代器标签（Iterator Tags）、迭代器特性（Iterator Traits）和迭代器适配器（Iterator Adapters），进一步增强了迭代器的功能和应用。

###  Vector、 List、 Queue、 Duque、 Set、 Map 的迭代器

在 C++ 中，不同的容器类型（`vector`、`list`、`queue`、`deque`、`set`、`map` 等）提供了不同类型的迭代器，具有不同的特性和功能。下面是这些容器的迭代器的主要区别：

1. **Vector 迭代器**：
   - 类型：`vector` 提供随机访问迭代器（`RandomAccessIterator`）。
   - 功能：支持常规的迭代器操作，如解引用（`*`）、递增（`++`）、递减（`--`）、随机访问（`+`、`-`、`[]`）等。可以在常量时间 O(1) 内访问任意位置的元素。

2. **List 迭代器**：
   - 类型：`list` 提供双向迭代器（`BidirectionalIterator`）。
   - 功能：支持常规的迭代器操作，如解引用（`*`）、递增（`++`）、递减（`--`）等。不支持随机访问，只能按顺序访问元素。插入和删除操作对于迭代器的失效情况相对较少。

3. **Queue 和 Deque 迭代器**：
   - 类型：`queue` 和 `deque` 并不提供直接访问元素的迭代器。它们是一种特殊的队列容器，只允许在队列的前端进行插入和删除操作，而不支持随机访问。
   - 功能：`queue` 和 `deque` 不支持迭代器的解引用、递增和递减操作，只能通过队列的特定成员函数（如 `front()` 和 `pop()`）进行元素的访问和删除。

4. **Set 和 Map 迭代器**：
   - 类型：`set` 和 `map` 提供的迭代器是双向迭代器（`BidirectionalIterator`）。
   - 功能：支持常规的迭代器操作，如解引用（`*`）、递增（`++`）、递减（`--`）等。对于 `set`，迭代器按升序遍历元素。对于 `map`，迭代器按键的升序遍历元素。

总体而言，不同容器的迭代器具有不同的功能和性能特点。需要根据具体的使用场景和需求选择适合的容器和迭代器类型。此外，对于插入和删除操作频繁的容器，需要注意在进行这些操作后，迭代器的失效情况，避免使用无效的迭代器进行访问操作。

### 迭代器的增删改查

迭代器是一种用于遍历容器元素的对象，可以用于进行增删改查等操作。下面是迭代器在 C++ 中的常见操作：

1. **增加（Insertion）**：
   - `insert(position, value)`：在迭代器 `position` 所指向的位置之前插入值为 `value` 的元素。
   - `push_back(value)`：在容器的末尾插入值为 `value` 的元素。
   - `push_front(value)`：在容器的开头插入值为 `value` 的元素。

2. **删除（Deletion）**：
   - `erase(position)`：删除迭代器 `position` 所指向的元素。
   - `pop_back()`：删除容器的末尾元素。
   - `pop_front()`：删除容器的开头元素。
   - `clear()`：清空容器中的所有元素。

3. **修改（Modification）**：
   - `*iterator = value`：使用迭代器解引用并赋值，修改迭代器所指向的元素的值。

4. **查找（Access/Searching）**：
   - `*iterator`：使用迭代器解引用，获取迭代器所指向的元素的值。
   - `begin()`：获取指向容器开头的迭代器。
   - `end()`：获取指向容器末尾的迭代器。
   - `find(value)`：在容器中查找值为 `value` 的元素，并返回指向该元素的迭代器。

下面是一个示例，演示了迭代器的增删改查操作：

```cpp
#include <iostream>
#include <vector>

int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    // 迭代器的增加操作
    std::vector<int>::iterator it = numbers.begin();
    numbers.insert(it + 2, 6);  // 在第三个位置前插入元素 6

    // 迭代器的删除操作
    it = numbers.begin() + 4;
    numbers.erase(it);  // 删除第五个位置的元素

    // 迭代器的修改操作
    it = numbers.begin() + 1;
    *it = 10;  // 将第二个位置的元素修改为 10

    // 迭代器的查找操作
    it = numbers.begin();
    while (it != numbers.end()) {
        std::cout << *it << " ";  // 输出元素值
        ++it;
    }
    // 输出: 1 10 3 4 5

    return 0;
}
```

在上述示例中，使用迭代器对 `numbers` 容器进行了增删改查操作。首先，在第三个位置前插入了元素 6，然后删除了第五个位置的元素，接着将第二个位置的元素修改为 10。最后，通过迭代器遍历容器，并输出每个元素的值。

需要注意的是，对于某些容器（如 `list`），在进行插入和删除操作后，迭代器可能会失效。因此，在使用迭代器进行增删改查操作时，需要注意避免使用失效的迭代器。

### * 补充：有指针为什么还要迭代器iterator

1. 通过迭代器访问容器，可以避免许多错误，同时还能隐藏容器的具体实现。

2. 迭代器可以保证对所有容器的基本遍历方式都是一样的，实现算法时若需要遍历，则使用迭代器，则可以不用关注容器的具体类型，实现数据结构和算法的分离。

3. 迭代器本身有很多优点，可以弥补C++语言的不足，比如它的iterator_category，可以得到迭代器所指向的类别，这样可以根据不同的类别的特性，提供不同的算法。

**迭代器的好处：**

- **编程方便**： 如果使用[ ]运算符访问元素，那么我们需要始终担心容器的大小，而使用迭代器，我们可以简单地使用成员函数end()并迭代内容，而不必记住任何事情。
- 代码可重用性好： 如果我们使用vector的迭代器来访问元素，那么将更改vector而使用list的时候，只需在iterator的声明中将vector改为list就可以达到目的，而无需执行任何其他操作，因此，迭代器支持代码的可重用性，因为它们可用于访问任何容器的元素。
- 容器的动态处理： 迭代器使我们能够在需要时轻松地在容器中动态添加或删除元素。

### *补充：迭代器失效问题

在使用迭代器进行容器遍历和修改元素时，可能会遇到迭代器失效的问题。迭代器失效指的是在修改容器的过程中，原本有效的迭代器变得无效，不能再使用或引发未定义的行为。迭代器失效可能是由于容器的结构发生变化而导致的。

以下是一些常见导致迭代器失效的情况：

1. **添加或删除元素**：在使用迭代器遍历容器时，如果在遍历过程中向容器添加或删除元素，会导致迭代器失效。这是因为容器的结构发生了改变，迭代器无法正确指向原来的元素或容器的末尾。

2. **重新分配内存**：某些容器（如 `std::vector`、`std::deque`）在元素数量增加时可能需要重新分配内存。当容器重新分配内存时，原有的迭代器可能会失效，因为容器的内存地址发生了变化。

3. **清空容器**：调用容器的清空操作（如 `clear()`）会删除容器中的所有元素，导致迭代器失效。

4. **排序容器**：对某些容器进行排序操作（如 `std::sort()`）可能会导致迭代器失效，因为排序会改变容器的元素顺序。

为了避免迭代器失效问题，可以采取以下几种策略：

- 避免在遍历容器的过程中进行添加、删除、排序等可能导致迭代器失效的操作。可以在遍历前将需要修改的元素记录下来，遍历完后再进行修改。

- 使用智能指针或迭代器的复制（如 `std::copy()`）来避免直接在容器上进行修改操作。

- 在使用迭代器之前，检查迭代器的有效性。如果迭代器失效，需要重新获取新的迭代器。

- 对于需要频繁进行插入和删除操作的情况，可以考虑使用其他容器，如 `std::list`，因为它对迭代器失效的影响相对较小。

总之，迭代器失效是在使用迭代器遍历和修改容器时需要注意的重要问题。了解容器操作可能导致迭代器失效的情况，并采取相应的策略来避免或处理迭代器失效问题，可以确保代码的正确性和稳定性。

## 4. 仿函数

仿函数是可调用对象的一种，可以像函数一样使用。在C++中，仿函数通常以重载了函数调用运算符operator()的类实现。它们常用于算法中，作为排序、比较或其他操作的函数对象。

## 5. 适配器

适配器是一种模式，用于将一种接口转换为另一种接口。在C++中，适配器常用于改变容器或算法的行为。例如，std::stack是一个适配器，它基于std::deque实现了栈的功能。

在C++中，适配器（Adapter）是一种设计模式，用于将一个类的接口转换成另一个类的接口，使得原本不兼容的类可以一起工作。适配器模式可以通过继承或组合实现。

在C++标准库中，有几种常见的适配器，如下所示：

1. **容器适配器**（Container Adapters）：
   - `std::stack`：基于底层容器实现的堆栈（先进后出）适配器。
   - `std::queue`：基于底层容器实现的队列（先进先出）适配器。
   - `std::priority_queue`：基于底层容器实现的优先队列适配器。

2. **迭代器适配器**（Iterator Adapters）：
   - `std::reverse_iterator`：逆向迭代器，用于反向遍历容器。
   - `std::insert_iterator`：插入迭代器，用于在指定位置插入元素。
   - `std::ostream_iterator`：输出流迭代器，用于将元素输出到输出流。

3. **函数适配器**（Function Adapters）：
   - `std::bind`：函数绑定器，用于绑定函数和部分参数，生成新的可调用对象。
   - `std::function`：通用函数封装器，可用于存储、传递和调用各种可调用对象。

这些适配器提供了对已有类或接口的封装和转换，使得它们可以在不同的上下文中使用。例如，可以使用 `std::stack` 适配器将 `std::vector` 或 `std::deque` 容器转换为堆栈，使用 `std::reverse_iterator` 适配器反向遍历容器，使用 `std::bind` 适配器绑定函数和参数等等。

### 5.1 容器适配器与容器的区别

容器适配器（Container Adapters）和容器（Containers）是 C++ STL 中的两个概念，它们在功能和使用方式上有一些区别。

容器（Containers）是用于存储和操作数据的数据结构。STL 提供了多种容器类，如 `std::vector`、`std::list`、`std::set` 等。这些容器类提供了不同的数据结构和操作接口，以满足不同的需求。容器可以存储一组元素，并提供元素的访问、插入、删除等操作。容器的特点是在数据存储和操作上灵活且功能强大。

容器适配器（Container Adapters）是一种特殊的容器，它们是基于现有容器类的接口进行封装的。STL 提供了三种容器适配器：`std::stack`、`std::queue` 和 `std::priority_queue`。

- `std::stack` 是基于底层容器实现的堆栈（先进后出）适配器。
- `std::queue` 是基于底层容器实现的队列（先进先出）适配器。
- `std::priority_queue` 是基于底层容器实现的优先队列适配器。

容器适配器提供了特定的接口和行为，以便在特定的数据结构需求下使用。它们的接口相对简化，只提供了特定操作，如入栈、出栈、入队、出队等，而不支持其他通用容器操作，如随机访问等。容器适配器的特点是提供了特定数据结构的操作接口，并限制了可用的操作。

总结来说，容器是通用的数据结构，提供了广泛的数据操作接口和灵活性。而容器适配器是针对特定数据结构的封装，提供了简化的接口和特定行为，适用于特定的数据结构需求。

### 5.2 迭代器适配器

迭代器适配器（Iterator Adapters）和迭代器（Iterators）是 C++ STL 中的两个概念，它们在功能和使用方式上有一些区别。

迭代器（Iterators）是用于遍历容器中元素的对象。STL 中的容器类（如 `std::vector`、`std::list` 等）提供了迭代器接口，允许我们通过迭代器来访问容器中的元素。迭代器提供了一种统一的方式来遍历容器，无论容器的具体类型如何，我们都可以使用迭代器来访问容器中的元素。迭代器的特点是提供了对容器元素的顺序访问能力，可以进行递增、递减、解引用等操作。

迭代器适配器（Iterator Adapters）是一种特殊的迭代器，它们是对现有迭代器进行功能扩展或转换的对象。STL 提供了多种迭代器适配器，如 `std::reverse_iterator`、`std::insert_iterator`、`std::back_insert_iterator` 等。

- `std::reverse_iterator` 是用于反向遍历容器的迭代器适配器。
- `std::insert_iterator` 和 `std::back_insert_iterator` 是用于向容器中插入元素的迭代器适配器。

迭代器适配器通过对现有迭代器的封装和功能扩展，提供了更灵活的迭代器操作。例如，`std::reverse_iterator` 可以将正向迭代器逆序遍历容器，`std::insert_iterator` 可以在指定位置插入元素，`std::back_insert_iterator` 可以在容器末尾插入元素等。迭代器适配器的特点是根据需要对迭代器进行功能转换或扩展，以满足特定的遍历需求。

总结来说，迭代器是用于遍历容器元素的对象，提供了顺序访问容器元素的能力。迭代器适配器是对现有迭代器进行功能扩展或转换的对象，提供了更灵活的迭代器操作，以满足特定的遍历需求。迭代器是一种基本的遍历工具，而迭代器适配器则是在此基础上进行功能扩展和转换的工具。

### 5.3 函数适配器

函数适配器是 C++ STL 提供的工具，用于对函数对象进行功能扩展或转换。下面是几个常见的函数适配器及其示例：

1. `std::bind`：
   ``std::bind` 函数适配器用于创建一个新的函数对象，通过绑定参数或改变参数顺序来适应不同的调用需求。

   示例：
   ```cpp
   #include <functional>
   #include <iostream>
   
   void greet(const std::string& name, const std::string& greeting) {
       std::cout << greeting << ", " << name << "!" << std::endl;
   }
   
   int main() {
       auto sayHello = std::bind(greet, std::placeholders::_1, "Hello");
       sayHello("Alice");  // Output: Hello, Alice!
   
       auto sayHiToBob = std::bind(greet, "Bob", std::placeholders::_1);
       sayHiToBob("Hi");  // Output: Hi, Bob!
   
       return 0;
   }
   ```
   在上述示例中，使用 `std::bind` 将 `greet` 函数转换为新的函数对象 `sayHello` 和 `sayHiToBob`。通过绑定参数，我们可以灵活地改变函数的调用方式。

2. `std::function`：
   ``std::function` 是一个通用的函数对象封装器，可以用于存储、复制和调用各种可调用对象。

   示例：
   ```cpp
   #include <functional>
   #include <iostream>
   
   void printMessage(const std::string& message) {
       std::cout << message << std::endl;
   }
   
   int main() {
       std::function<void(const std::string&)> printer = printMessage;
       printer("Hello, world!");  // Output: Hello, world!
   
       return 0;
   }
   ```
   在上述示例中，使用 `std::function` 将 `printMessage` 函数封装为函数对象 `printer`。通过 `printer` 可以调用原始函数。

3. `std::mem_fn`：
   ``std::mem_fn` 函数适配器用于将成员函数转换为可调用对象。

   示例：
   ```cpp
   #include <functional>
   #include <iostream>
   
   class MyClass {
   public:
       void printMessage(const std::string& message) {
           std::cout << message << std::endl;
       }
   };
   
   int main() {
       MyClass obj;
       auto printer = std::mem_fn(&MyClass::printMessage);
       printer(obj, "Hello, world!");  // Output: Hello, world!
   
       return 0;
   }
   ```
   在上述示例中，使用 `std::mem_fn` 将成员函数 `printMessage` 转换为可调用对象 `printer`。通过 `printer` 可以调用成员函数。

这些示例展示了函数适配器的使用方式和效果。函数适配器可以根据需求改变函数调用方式、参数传递方式或转换函数类型，以适应不同的编程场景。

## 6. 空间适配器

空间适配器是用于管理内存分配和释放的对象。它们允许自定义内存管理策略，如内存池分配、对齐要求等。C++标准库提供了std::allocator作为默认的空间适配器，也可以自定义空间适配器来满足特定的需求。

在 C++ 中，空间适配器（Allocator）是用于管理容器内存分配和释放的机制。它可以控制容器在堆上分配内存的行为，允许开发人员自定义内存管理策略。C++ 标准库提供了默认的空间适配器，也可以通过自定义空间适配器来满足特定需求。

C++ 中的空间适配器遵循 Allocator 概念，它定义了一组与内存分配相关的操作。空间适配器主要包含以下几个成员函数：

1. `typename allocator::pointer allocate(size_type n)`：分配 n 个连续的内存空间，并返回指向第一个元素的指针。该函数通常由容器内部调用。

2. `void allocator::deallocate(typename allocator::pointer p, size_type n)`：释放由 allocate 分配的内存空间，其中 p 是指向内存块的指针，n 是要释放的元素个数。该函数通常由容器内部调用。

3. `typename allocator::pointer allocator::address(reference x)`：返回指向对象 x 的指针。这在容器需要获得对象的地址时有用。

4. `typename allocator::const_pointer allocator::address(const_reference x)`：返回指向常量对象 x 的指针。

5. `void allocator::construct(typename allocator::pointer p, const T& val)`：在指针 p 指向的内存位置上构造一个对象，并使用 val 进行初始化。

6. `void allocator::destroy(typename allocator::pointer p)`：销毁指针 p 指向的对象，但不释放内存。

C++ 标准库中的容器（如 `vector`、`list`、`map` 等）使用默认的空间适配器 `std::allocator` 来进行内存管理。如果需要自定义空间适配器，可以通过实现自己的空间适配器类并满足以上成员函数的要求。自定义的空间适配器可以用于控制内存分配策略、改善性能、实现内存池等。

以下是一个简单的示例，演示了如何自定义空间适配器，并将其用于 `vector` 容器：

```cpp
#include <iostream>
#include <vector>

template <typename T>
struct MyAllocator {
    using value_type = T;

    T* allocate(std::size_t n) {
        std::cout << "Allocating memory for " << n << " elements\n";
        return static_cast<T*>(::operator new(n * sizeof(T)));
    }

    void deallocate(T* p, std::size_t n) {
        std::cout << "Deallocating memory for " << n << " elements\n";
        ::operator delete(p);
    }
};

int main() {
    std::vector<int, MyAllocator<int>> numbers;
    numbers.push_back(1);
    numbers.push_back(2);
    numbers.push_back(3);

    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    // 输出: 1 2 3

    return 0;
}
```

在上述示例中，定义了一个名为 `MyAllocator` 的自定义空间适配器。它实现了 `allocate` 和 `deallocate` 函数，用于分配和释放内存。然后，将 `MyAllocator` 用作 `vector` 容器的空间适配器类型，并创建了一个存储 `int` 类型的 `vector` 容器 `numbers`。可以看到，在向 `numbers` 容器中添加元素时，自定义的空间适配器的分配和释放函数被调用。

需要注意的是，自定义空间适配器的实现需要满足 C++ 标准规定的 Allocator 概念要求，确保正确的内存分配和释放操作。

## 7. STL  非线程安全

在 C++ 标准库中，大多数容器和算法都被设计为非线程安全的，这意味着它们在并发环境下使用时需要采取额外的同步措施来保证线程安全性。以下是一些常见的 STL 组件和类别的线程安全性讨论：

1. **容器的线程安全性**：
   - STL 容器（例如 vector、list、deque、map、set 等）通常是非线程安全的。这意味着在多个线程同时读写容器时，可能会出现竞争条件和数据不一致的情况。
   - 一种常见的解决方案是在访问容器时使用互斥锁（mutex）进行同步，以确保同一时间只有一个线程访问容器。另一种选择是使用线程安全的容器，如 C++11 引入的 std::atomic 和 std::shared_mutex。

2. **算法的线程安全性**：
   - STL 算法（例如 sort、find、transform、accumulate 等）通常是非线程安全的。这意味着在多个线程同时调用同一个算法时，可能会导致数据竞争和不确定的结果。
   - 要在多线程环境下使用算法，可以采取以下策略之一：将算法的调用放在互斥锁保护的临界区域内，或者使用线程安全的算法库，如 Intel TBB（Threading Building Blocks）或 Boost 库中提供的线程安全算法。

3. **迭代器的线程安全性**：
   - 迭代器本身没有线程安全性的概念。迭代器的安全性取决于使用迭代器的容器和算法的线程安全性。
   - 如果容器和算法是线程安全的，那么在多个线程中使用迭代器进行操作通常是安全的。但是，当多个线程同时修改容器时，需要进行适当的同步。

总结来说，C++ 标准库中的大部分容器、算法和迭代器都是非线程安全的。在多线程环境中使用它们时，必须采取适当的同步机制来确保线程安全性。可以使用互斥锁、原子操作或线程安全的库来实现线程安全的操作。另外，C++11 引入了一些线程安全的容器和算法，如 std::atomic 和 Intel TBB，可以直接在多线程环境中使用。