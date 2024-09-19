# C++ 继承

## 1. 继承语法

```cpp
#include <iostream>
#include <string>

using namespace std;

class human {
public:
    string name;
    int age;
};

class student : human {
public:
    string studentID;
};

class teacher : human {
public:
    string teacherID;
};
```

在C++中，public、protected和private是用于指定类成员访问权限的访问修饰符。

- **public**：
  - 在类的内部和外部都可以访问公有成员。
  - 公有成员可以被类的对象、派生类和其他任何能够访问类的代码访问。

- **protected**：
    - 在类的内部和派生类中可以访问受保护成员。
    - 受保护成员对类的外部是不可访问的，只有类的成员函数、友元函数和派生类的成员函数可以访问受保护成员。
    - 受保护成员用于在派生类中实现继承和封装。

- **private**：
    - 只有类的成员函数和友元函数可以访问私有成员。
    - 私有成员对于类的外部和派生类来说是不可访问的。
    - 私有成员用于实现封装，限制对类的内部实现细节的访问

```cpp
class MyClass {
public:
    int publicMember;

protected:
    int protectedMember;

private:
    int privateMember;
};
```

在上面的例子中，`publicMember`是公有成员，`protectedMember`是受保护成员，`privateMember`是私有成员。

###  1.1 继承的三种类型

在C++中，继承（Inheritance）是一种面向对象编程的重要概念，它允许一个类（称为派生类或子类）从另一个类（称为基类或父类）继承属性和行为。继承通过创建类之间的层次结构，从而实现代码的重用和扩展。

C++支持以下几种类型的继承：

- **公有继承（Public Inheritance）：**
    - 使用public关键字进行声明。
    - 基类的公有成员在派生类中仍然为公有成员，受保护成员在派生类中仍然为受保护成员。
    - 公有继承保留了基类接口的可访问性。

- **保护继承（Protected Inheritance）：**
    - 使用protected关键字进行声明。
    - 基类的公有和受保护成员在派生类中变为受保护成员。
    - 保护继承将基类的接口限制在派生类和派生类的派生类中。

- **私有继承（Private Inheritance）：**
    - 使用private关键字进行声明。
    - 基类的公有和受保护成员在派生类中变为私有成员。
    - 私有继承限制了基类的接口只能在派生类内部使用。

继承的语法如下：

```cpp
class Base {
    // 基类的定义
};

class public_Class : public Base {
    // 派生类的定义
};
class protected_Class : protected Base {
    // 派生类的定义
};
class private_Class : private  Base {
    // 派生类的定义
};
```

####  1.2.1 公有继承属性访问

```cpp
#include <iostream>
#include <string>

using namespace std;

class Base {
public:
	string public_str = "public_str";
protected:
	string protected_str = "protected_str";
private:
	string private_str = "privated_str";
};

class Public_class : public Base {
public:
	void print_Info();
};


void Public_class::print_Info() {
	cout << public_str << " " << protected_str << endl;
}


void main() {
	Public_class public_class = Public_class();
	public_class.print_Info();
	return ;
}

```

**公有继承父类不能访问私有属性；**

####  1.2.2 保护继承属性访问

```cpp
#include <iostream>
#include <string>

using namespace std;

class Base {
public:
	string public_str = "public_str";
protected:
	string protected_str = "protected_str";
private:
	string private_str = "privated_str";
};

class Protected_class : protected Base {
public:
	void print_Info();
};


void Protected_class::print_Info() {
	cout << public_str << " " << protected_str << "" << endl;
}


void main() {
	Protected_class protected_class = Protected_class();
	protected_class.print_Info();
	return ;
}
```

- **保护继承不能访问私有属性。**

- **保护继承类的实例，不能访问保护属性。**

> 保护继承在C++中存在的原因是为了实现继承和封装的一种折中方案。**通过保护继承，派生类可以继承基类的接口和实现，但对于外部代码来说，基类的接口是受保护的，只能在派生类及其派生类中使用。**
>
> 以下是一些保护继承的应用场景和优点：
>
> 1. 封装实现细节：保护继承可以帮助实现类的封装，将类的实现细节隐藏在派生类中。基类的接口对外部代码是不可见的，只有派生类及其派生类可以访问基类的受保护成员，从而实现了封装的目的。
>
> 2. 代码复用：通过保护继承，派生类可以复用基类的成员变量和成员函数。派生类可以在基类的基础上进行扩展和修改，而无需重新编写基类的代码。这样可以提高代码的重用性和开发效率。
>
> 3. 实现继承和多态性：保护继承是实现继承和多态性的基础。派生类可以继承基类的接口和行为，并且可以重写基类的虚函数来实现多态性。保护继承提供了一种限制基类接口在外部代码中的可见性的方式，同时保留了继承和多态性的特性。
>
> 4. 控制访问权限：保护继承允许派生类和其派生类访问基类的受保护成员，但对于外部代码来说是不可见的。这提供了一种灵活的方式来控制成员的访问权限，确保只有特定的类可以访问和修改相关的数据和行为。
>
> 需要注意的是，保护继承并不是所有情况下都是最佳选择。在设计类继承关系时，需要根据具体需求和设计目标来选择适当的继承方式。保护继承的合理应用可以提高代码的可维护性和可扩展性，但滥用保护继承可能导致继承层次过深、耦合度过高等问题，因此需要慎重使用。

####  1.2.3 私有继承属性访问

```cpp
#include <iostream>
#include <string>

using namespace std;

class Base {
public:
	string public_str = "public_str";
protected:
	string protected_str = "protected_str";
private:
	string private_str = "privated_str";
};

class Private_class : private Base {
public:
	void print_Info();
};


void Private_class::print_Info() {
	cout << public_str << " " << protected_str << endl;
}


void main() {
	Private_class private_class = Private_class();
	private_class.print_Info();
	return ;
}

```

##### 补充：向上转型与向下转型（dynamic_cast）

向上转型（Upcasting）和向下转型（Downcasting）是面向对象编程中的两个概念，用于描述派生类和基类之间的类型转换。

1. 向上转型（Upcasting）：
   向上转型是将派生类的指针或引用转换为基类的指针或引用的过程。这种转型是安全的，因为派生类是基类的一种特化。在向上转型中，派生类对象具有基类对象的所有成员和行为，可以直接赋值给基类的指针或引用。

   示例代码：
   ````cpp
   class Base {
       // 基类的成员和行为
   };
   
   class Derived : public Base {
       // 派生类的成员和行为
   };
   
   int main() {
       Derived derivedObj;
       Base* basePtr = &derivedObj;  // 向上转型
       return 0;
   }
   ```

2. 向下转型（Downcasting）：
   向下转型是将基类的指针或引用转换为派生类的指针或引用的过程。这种转型是有风险的，因为基类指针或引用可能指向的实际对象可能是派生类的对象，也可能是其他派生类或基类的对象。在向下转型之前，应该确保基类指针或引用实际上指向了派生类对象，否则可能导致未定义的行为。

   示例代码：
   ````cpp
   class Base {
       // 基类的成员和行为
   };
   
   class Derived : public Base {
       // 派生类的成员和行为
   };
   
   int main() {
       Base* basePtr = new Derived();  // 向上转型
       Derived* derivedPtr = dynamic_cast<Derived*>(basePtr);  // 向下转型
       if (derivedPtr != nullptr) {
           // 向下转型成功，可以使用 derivedPtr
       }
       delete basePtr;
       return 0;
   }
   ```
   
   在向下转型中，可以使用 `dynamic_cast` 运算符进行类型检查和转换。该运算符会在运行时检查基类指针或引用是否实际指向了派生类对象。如果向下转型成功，则返回指向派生类对象的指针或引用；如果向下转型失败，则返回 `nullptr`。因此，在进行向下转型之前，最好使用 `dynamic_cast` 进行类型检查，以确保安全地使用派生类的成员和行为。

需要注意的是，向上转型是隐式的，而向下转型需要显式的类型转换或使用 `dynamic_cast` 运算符进行类型检查和转换。此外，向下转型只能在具有多态性的类层次结构中使用，需要基类具有虚函数。否则，向下转型可能无法正常工作。

### * 补充 1.2 友元函数

**友元函数是在C++中的一种特殊函数，它可以访问类的私有成员和受保护成员，即使它不是类的成员函数**。通过声明一个函数为类的友元函数，可以使该函数在需要时访问类的私有和受保护成员，从而突破了访问权限的限制。

**友元函数的声明形式通常在类的定义中进行，但是在类的外部进行定义和实现。在函数声明前加上friend关键字，将其声明为类的友元函数。友元函数可以是全局函数，也可以是其他类的成员函数。**

以下是一个简单的示例，说明友元函数的用法：

```cpp
class MyClass {
private:
    int privateMember;

public:
    MyClass(int value) : privateMember(value) {}

    // 友元函数的声明
    friend void FriendFunction(const MyClass& obj);
};

// 友元函数的定义
void FriendFunction(const MyClass& obj) {
    // 可以访问类的私有成员
    std::cout << "privateMember: " << obj.privateMember << std::endl;
}

int main() {
    MyClass myObj(42);
    FriendFunction(myObj);  // 调用友元函数
    return 0;
}
```

在上面的示例中，FriendFunction被声明为MyClass的友元函数。它可以访问MyClass的私有成员privateMember，即使它不是MyClass的成员函数。在main函数中，我们通过传递一个MyClass对象给FriendFunction来调用该友元函数，并输出了私有成员的值。

需要注意的是，友元函数的声明仅仅告诉编译器该函数是类的友元函数，而实际定义和实现仍然是在类的外部进行。友元函数不继承，也不受访问修饰符的限制。因此，**友元函数的滥用可能会导致破坏封装性和类的设计原则，应该谨慎使用**。

### 1.3 装饰符

装饰符（Modifier）是一个广义的术语，它可以指代多种C++语言中的修饰符或修饰关键字。在面向对象编程中，装饰符通常用于描述类成员的特性或行为。一些常见的装饰符包括：

- **virtual（虚函数修饰符）**：用于声明虚函数，使得派生类可以通过动态绑定来重写基类的虚函数。

- **override（覆盖修饰符）**：用于明确指示派生类的成员函数将覆盖基类的虚函数，提高代码的可读性和维护性。

- **final（终结修饰符）**：用于标记类、成员函数或虚函数，阻止其被派生类继续派生或重写。

- **static（静态修饰符）**：用于声明静态成员变量或静态成员函数，它们与类的实例无关，可以通过类名直接访问。

- **const（常量修饰符）**：用于声明成员函数不会修改对象的状态，从而允许在常量对象上调用该函数。

这些装饰符可以结合在一起使用，以实现不同的语义和行为。它们在类的设计和实现中发挥着重要的作用，用于控制继承、多态性和成员的特性。

#### 1.3.1 virtual

在C++中，`virtual`是一个关键字，用于声明类的成员函数是虚函数（Virtual Function）。虚函数是实现多态性和动态绑定的重要机制。

使用`virtual`关键字来声明虚函数有以下特点：

1. 虚函数在基类中声明，并由派生类进行覆盖（重写）。
2. 虚函数可以通过基类的指针或引用来调用派生类的实现。
3. 当使用基类指针或引用指向派生类对象并调用虚函数时，实际调用的是派生类的实现，而不是基类的实现。
4. 使用`virtual`关键字声明的虚函数可以在派生类中使用`override`关键字进行显式重写，以提高代码的可读性。

以下是一个示例，展示了如何使用虚函数：

```cpp
class Shape {
public:
    virtual double getArea() const {
        return 0.0;
    }
};

class Rectangle : public Shape {
private:
    double length;
    double width;

public:
    Rectangle(double l, double w) : length(l), width(w) {}

    double getArea() const override {
        return length * width;
    }
};

class Circle : public Shape {
private:
    double radius;

public:
    Circle(double r) : radius(r) {}

    double getArea() const override {
        return 3.14 * radius * radius;
    }
};

int main() {
    Rectangle rectangle(5, 3);
    Circle circle(2);

    Shape* shapePtr1 = &rectangle;
    Shape* shapePtr2 = &circle;

    double area1 = shapePtr1->getArea();  // 调用 Rectangle 的 getArea()
    double area2 = shapePtr2->getArea();  // 调用 Circle 的 getArea()

    return 0;
}
```

在上面的示例中，`Shape`类中的`getArea()`函数被声明为虚函数。`Rectangle`和`Circle`类继承自`Shape`类，并分别重写了`getArea()`函数。在`main()`函数中，我们创建了一个`Rectangle`对象和一个`Circle`对象，并使用基类指针来调用它们的虚函数。由于虚函数的存在，实际调用的是派生类的实现。

虚函数的使用允许我们在基类中定义通用的接口，并让派生类根据自身的需要来提供具体的实现。这种特性实现了运行时多态性，使得我们可以以统一的方式处理不同的对象。

##### 补充：静态绑定与动态绑定

> C++在面向对象编程中，存在着静态绑定和动态绑定的定义，本节即是主要讲述这两点区分。
> 我是在一个类的继承体系中分析的，因此下面所说的对象一般就是指一个类的实例。
> 首先我们需要明确几个名词定义：
>
> - **静态类型**：对象在声明时采用的类型，**在编译期既已确定**；
> - **动态类型**：通常是指一个指针或引用目前所指对象的类型，是**在运行期决定的**；
> - **静态绑定**：绑定的是静态类型，所对应的函数或属性依赖于对象的静态类型，**发生在编译期**；
> - **动态绑定**：绑定的是动态类型，所对应的函数或属性依赖于对象的动态类型，**发生在运行期**；
>
> 从上面的定义也可以看出，**非虚函数一般都是静态绑定，而虚函数往往是动态绑定（如此才可实现多态性）**。
>
> 这里只给出建议：
> **绝对不要重新定义一个继承而来的virtual函数的缺省参数值，因为缺省参数值都是静态绑定（为了执行效率），而virtual函数却是动态绑定。**

```cpp
#include <iostream>
#include <string>

using namespace std;

class Human {
public:
	void setName() {
		cout << "Human:: setName()" << endl;
	}

	virtual void printInfo() {
		cout << "Human:: printInfo()" << endl;
	}
};

class Student : public Human {
public:
	void setName() {
		cout << "Student:: setName()" << endl;
	}
	void printInfo() {
		cout << "Student:: printInfo()" << endl;
	}
};

int main() {
	Student *student = new Student;
	Human *human = student;

	student->setName();
	human->setName();

	student->printInfo();
	human->printInfo();
	return 0;
}
```

执行结果为：

```cpp
Student:: setName()
Human:: setName()
Student:: printInfo()
Student:: printInfo()
```

由于`setName()`方法为静态绑定，在编译时进行绑定，故两者执行的结果不一致；但是由于`printInfo()`使用`virtual`关键字声明为虚函数，在程序运行时执行动态绑定，所以两者执行的结果一致。

##### 补充： new Student 与Student() 的区别

在C++中，new student和student()是两种不同的对象创建方式。

1. new student: 这是使用**动态内存分配运算符new创建一个student类型的对象**。动态内存分配允许在**运行时动态地分配内存空间**。使用new关键字创建对象时，**会在堆（heap）上分配一块内存**，并调用student类的构造函数来初始化对象。这种方式返回一个指向student对象的指针，因此需要使用指针来访问和操作该对象。需要注意的是，使用new创建的对象必须手动释放内存，否则可能导致内存泄漏。

   示例代码：

   ```cpp
   student* ptr = new student();  // 创建student对象，返回指针
   // 使用指针访问和操作对象
   ptr->setName("John");
   ptr->setAge(20);
   delete ptr;  // 释放内存
   ```

2. student(): 这是使用类的构造函数直接创建一个student类型的对象。这种方式称为栈上分配，对象的内存空间会在当前作用域的栈上分配，当超出作用域时，对象会自动被销毁，释放内存。通过这种方式创建的对象可以直接通过对象名访问和操作。

   示例代码：

   ```cpp
   student s;  // 创建student对象
   s.setName("John");
   s.setAge(20);
   // 对象将在当前作用域结束时自动销毁，无需手动释放内存
   ```

   总结来说，**new student创建的对象位于堆上，需要手动释放内存；而student()创建的对象位于栈上，会在作用域结束时自动销毁。使用动态内存分配时需要注意内存管理，以防止内存泄漏。**

   ###### new Student； 与 Student 对虚函数调用的影响

   new Student和Student之间的区别是，new Student创建了一个动态分配的Student对象，而Student只是创建了一个自动变量（也称为栈对象）。

   对于虚函数调用的影响：

   1. **new Student创建的对象是通过指针访问的**，因此虚函数的调用将使用动态绑定（dynamic binding）。动态绑定是指在运行时根据对象的实际类型来确定要调用的虚函数的版本。这意味着，如果Student类中有一个虚函数，并且派生类覆盖了这个函数，那么通过指针调用虚函数时将使用派生类的版本。

      示例代码：

       ```cpp
       class Student {
       public:
         virtual void display() {
           cout << "Student" << endl;
         }
       };

       class GraduateStudent : public Student {
       public:
         void display() override {
           cout << "Graduate Student" << endl;
         }
       };

       Student* ptr = new GraduateStudent();
       ptr->display();  // 输出 "Graduate Student"
       ```

   2. **Student创建的对象是一个自动变量，虚函数的调用将使用静态绑定（static binding）**。静态绑定是指在编译时根据指针或引用的静态类型来确定要调用的函数版本。即使派生类覆盖了虚函数，但如果通过Student对象调用虚函数，将始终使用基类的版本。

      实例代码：

      ```cpp
      class Student {
      public:
        virtual void display() {
          cout << "Student" << endl;
        }
      };
      
      class GraduateStudent : public Student {
      public:
        void display() override {
          cout << "Graduate Student" << endl;
        }
      };
      
      Student s;
      s.display();  // 输出 "Student"
      ```

      总结来说，**对于通过`new Student`创建的对象，虚函数调用将使用动态绑定，根据实际对象类型确定要调用的函数版本。而对于`Student`对象，无论派生类是否覆盖了虚函数，调用将始终使用基类的版本。**

##### 补充：C++ 虚函数实现多态剖析

###### 虚表结构

每个包含了虚函数的类都包含一个虚表。我们知道，当一个类（A）继承另一个类（B）时，类A会继承类B的函数的调用权。所以如果一个基类包含了虚函数，那么其继承类也可调用这些虚函数，换句话说，一个类继承了包含虚函数的基类，那么这个类也拥有自己的虚表。

我们来看以下的代码。类A包含虚函数vfunc1，vfunc2，由于类A包含虚函数，故类A拥有一个虚表：

```cpp
class A {
public:
    virtual void vfunc1();
    virtual void vfunc2();
    void func1();
    void func2();
private:
    int m_data1, m_data2;
};
```

类A的虚表如图1所示。

![img](image\v2-e864f4fe6a480b3230a5c9aebd7df996_1440w.webp)

图1：类A的虚表示意图

虚表是一个指针数组，其元素是虚函数的指针，每个元素对应一个虚函数的函数指针。需要指出的是，普通的函数即非虚函数，其调用并不需要经过虚表，所以虚表的元素并不包括普通函数的函数指针。
虚表内的条目，即虚函数指针的赋值发生在编译器的编译阶段，也就是说在代码的编译阶段，虚表就可以构造出来了。

###### 虚表指针

虚表是属于类的，而不是属于某个具体的对象，一个类只需要一个虚表即可。同一个类的所有对象都使用同一个虚表。为了指定对象的虚表，对象内部包含一个虚表的指针，来指向自己所使用的虚表。为了让每个包含虚表的类的对象都拥有一个虚表指针，编译器在类中添加了一个指针，`*__vptr`，用来指向虚表。这样，当类的对象在创建时便拥有了这个指针，且这个指针的值会自动被设置为指向类的虚表。

![img](image\v2-0fceb07713e411d48b4c361452129585_1440w.webp)

图2：对象与它的虚表

上面指出，一个继承类的基类如果包含虚函数，那个这个继承类也有拥有自己的虚表，故这个继承类的对象也包含一个虚表指针，用来指向它的虚表。

###### 动态绑定

说到这里，大家一定会好奇C++是如何利用虚表和虚表指针来实现动态绑定的。我们先看下面的代码。

```cpp
class A {
public:
    virtual void vfunc1();
    virtual void vfunc2();
    void func1();
    void func2();
private:
    int m_data1, m_data2;
};

class B : public A {
public:
    virtual void vfunc1();
    void func1();
private:
    int m_data3;
};

class C: public B {
public:
    virtual void vfunc2();
    void func2();
private:
    int m_data1, m_data4;
};
```

类A是基类，类B继承类A，类C又继承类B。类A，类B，类C，其对象模型如下图3所示。

![img](image\v2-dfe4aefdee7e06cf3151b57492ed42a2_1440w.webp)

图3：类A，类B，类C的对象模型

由于这三个类都有虚函数，故编译器为每个类都创建了一个虚表，即类A的虚表（A vtbl），类B的虚表（B vtbl），类C的虚表（C vtbl）。类A，类B，类C的对象都拥有一个虚表指针，`*__vptr`，用来指向自己所属类的虚表。

**非虚函数的调用不用经过虚表，故不需要虚表中的指针指向这些函数。**

假设我们定义一个类B的对象`bObject`。由于`bObject`是类B的一个对象，故`bObject`包含一个虚表指针，指向类B的虚表。

当我们使用`p`来调用`vfunc1()`函数时，会发生什么现象？

```cpp
int main() 
{
    B bObject;
    A *p = & bObject;
    p->vfunc1();
}
```

程序在执行`p->vfunc1()`时，会发现`p`是个指针，且**调用的函数是虚函数**，接下来便会进行以下的步骤。

首先，根据虚表指针`p->__vptr`来访问对象`bObject`对应的虚表。虽然指针`p`是基类`A*`类型，但是`*__vptr`也是基类的一部分，所以可以通过`p->__vptr`可以访问到对象对应的虚表。

然后，在虚表中查找所调用的函数对应的条目。由于虚表在编译阶段就可以构造出来了，所以可以根据所调用的函数定位到虚表中的对应条目。对于`p->vfunc1()`的调用，B vtbl的第一项即是`vfunc1`对应的条目。

最后，根据虚表中找到的函数指针，调用函数。从图3可以看到，B vtbl的第一项指向`B::vfunc1()`，所以`p->vfunc1()`实质会调用`B::vfunc1()`函数。

##### 补充：纯虚函数

纯虚函数（Pure Virtual Function）是在C++中定义在基类中的一种特殊函数。它是一种没有实际实现的函数，只在基类中声明。派生类必须实现这个函数才能被实例化为对象。

纯虚函数的特点如下：
1. 纯虚函数在基类中声明时没有函数体，使用`= 0`来标记函数为纯虚函数。例如：`virtual void func() = 0;`。
2. 如果一个类中包含了至少一个纯虚函数，那么它就是一个抽象类，不能直接实例化对象。
3. 派生类必须实现（覆盖）纯虚函数，否则派生类也会成为抽象类。

纯虚函数的主要目的是定义一个接口或协议，规定派生类必须提供某些特定的行为或功能。基类可以提供一些默认的实现，但派生类必须根据自身的需求来覆盖这些函数。

以下是一个示例，展示了如何使用纯虚函数：

```cpp
class Shape {
public:
    virtual double getArea() const = 0;  // 纯虚函数

    void printArea() const {
        double area = getArea();
        cout << "Area: " << area << endl;
    }
};

class Rectangle : public Shape {
private:
    double length;
    double width;

public:
    Rectangle(double l, double w) : length(l), width(w) {}

    double getArea() const override {
        return length * width;
    }
};

class Circle : public Shape {
private:
    double radius;

public:
    Circle(double r) : radius(r) {}

    double getArea() const override {
        return 3.14 * radius * radius;
    }
};

int main() {
    Rectangle rectangle(5, 3);
    Circle circle(2);

    rectangle.printArea();  // 输出：Area: 15
    circle.printArea();  // 输出：Area: 12.56

    return 0;
}
```

在上面的示例中，`Shape`类是一个抽象类，其中包含一个纯虚函数`getArea()`。`Rectangle`和`Circle`类继承自`Shape`类，并且必须实现`getArea()`函数。在`main()`函数中，我们创建了一个`Rectangle`对象和一个`Circle`对象，并调用它们的`printArea()`函数来打印它们的面积。

纯虚函数允许我们在基类中定义一个通用的接口，并要求派生类提供具体的实现。这种机制在面向对象的设计中非常有用，它能够实现多态性和动态绑定的特性。

##### 补充: C++ 接口的实现

在C++中，接口（Interface）是一种抽象的概念，用于定义类或对象应该具备的方法和行为，而不关注具体的实现细节。接口定义了一组纯虚函数，没有成员变量或具体的函数实现。

在C++中，由于没有专门的接口关键字，通常使用抽象基类（Abstract Base Class）来实现接口的概念。抽象基类是一个包含至少一个纯虚函数的类，不能实例化对象，只能被用作其他类的基类。

以下是一个示例，展示了如何使用抽象基类来实现接口：

```cpp
class Shape {
public:
    virtual double getArea() const = 0;
    virtual double getPerimeter() const = 0;
};

class Rectangle : public Shape {
private:
    double length;
    double width;

public:
    Rectangle(double l, double w) : length(l), width(w) {}

    double getArea() const override {
        return length * width;
    }

    double getPerimeter() const override {
        return 2 * (length + width);
    }
};

class Circle : public Shape {
private:
    double radius;

public:
    Circle(double r) : radius(r) {}

    double getArea() const override {
        return 3.14 * radius * radius;
    }

    double getPerimeter() const override {
        return 2 * 3.14 * radius;
    }
};

int main() {
    Rectangle rectangle(5, 3);
    Circle circle(2);

    double rectangleArea = rectangle.getArea();
    double rectanglePerimeter = rectangle.getPerimeter();

    double circleArea = circle.getArea();
    double circlePerimeter = circle.getPerimeter();

    return 0;
}
```

在上面的示例中，`Shape`类是一个抽象基类，定义了两个纯虚函数`getArea()`和`getPerimeter()`。`Rectangle`和`Circle`类继承自`Shape`类，并实现了这两个纯虚函数。在`main()`函数中，我们创建了一个`Rectangle`对象和一个`Circle`对象，并使用它们的接口函数来获取面积和周长。

通过使用抽象基类和纯虚函数，我们可以定义一个通用的接口，要求派生类提供具体的实现。这样的设计允许多态性和动态绑定，使得我们可以以统一的方式操作不同的对象。

#### 1.3.2 override 修饰符

`override`是C++11引入的一个关键字，用于显式地标记派生类中对基类虚函数的覆盖（重写）。它的作用是提醒编译器检查派生类中的函数是否正确地覆盖了基类的虚函数。

使用`override`修饰符有以下几个特点和用途：

1. **检查覆盖关系**：当在派生类中使用`override`修饰符时，编译器会检查该函数是否正确地覆盖了基类的虚函数。如果没有正确地覆盖，比如函数签名不匹配或者基类函数不是虚函数，编译器会产生错误。

2. 提高可读性：通过在派生类中使用`override`修饰符，可以清晰地表明该函数是对基类虚函数的覆盖，增强了代码的可读性和可维护性。

3. 防止错误的覆盖：在C++中，如果派生类中定义了一个与基类函数名称相同但函数签名不同的函数，该函数将隐藏基类的函数而不是覆盖它。这可能是由于意外的拼写错误或者函数参数不匹配导致的。使用`override`修饰符可以避免这类错误的覆盖，因为它要求函数签名与基类虚函数完全匹配。

使用示例：

```cpp
class Base {
public:
    virtual void foo() const;
};

class Derived : public Base {
public:
    void foo() const override;  // 使用override修饰符覆盖基类的虚函数
};

void Derived::foo() const {
    // 实现派生类的foo函数
}
```

在上面的示例中，派生类`Derived`通过使用`override`修饰符明确地表明它要覆盖基类`Base`的虚函数`foo`。如果`Derived`中的函数签名与`Base`的函数不匹配，编译器将报错。

需要注意的是，`override`修饰符只能用于虚函数的覆盖，不能用于非虚函数。如果在非虚函数上使用`override`修饰符，编译器将报错。此外，`override`修饰符只在编译时起作用，不会影响运行时的行为。它主要用于提供编译期的语法检查和文档说明。

##### 补充：重载与重写

在C++中，重载和重写的概念与面向对象编程中的概念相似，但有一些细微的差异。

1. 重载（Overloading）：
   - 重载指的是在**同一个作用域**中定义**具有相同名称但参数列表不同的函数或操作符**。重载函数可以有不同的参数类型、参数个数或参数顺序。
   - 重载函数可以提供不同的功能，并且根据传递的参数类型和数量来确定要调用的具体函数。
   - 重载函数是静态绑定，即在编译时根据函数调用的上下文确定要调用的函数。
   

下面是一个重载函数的示例：

```cpp
#include <iostream>

void printMessage() {
    std::cout << "Hello!" << std::endl;
}

void printMessage(const std::string& message) {
    std::cout << "Hello, " << message << std::endl;
}

void printMessage(int count) {
    for (int i = 0; i < count; i++) {
        std::cout << "Hello!" << std::endl;
    }
}

int main() {
    printMessage();
    printMessage("John");
    printMessage(3);
    return 0;
}
```

在上面的示例中，`printMessage` 函数被重载了三次，分别接受不同类型的参数。根据调用时传递的参数类型，编译器会选择合适的函数进行调用。

2. 重写（Overriding）：
   - 重写指的是在派生类中重新定义基类中已经存在的虚函数。**重写函数具有相同的函数签名（名称、返回类型和参数列表）**。
   - 通过重写函数，派生类可以改变继承自基类的虚函数的实现，以适应派生类的特定需求。
   - 重写函数是动态绑定，即在运行时根据对象的实际类型确定要调用的函数。
   

下面是一个重写虚函数的示例：

```cpp
#include <iostream>

class Base {
public:
    virtual void printMessage() {
        std::cout << "Hello from Base!" << std::endl;
    }
};

class Derived : public Base {
public:
    void printMessage() override {
        std::cout << "Hello from Derived!" << std::endl;
    }
};

int main() {
    Base* basePtr = new Derived();
    basePtr->printMessage();  // 输出 "Hello from Derived!"
    
    delete basePtr;
    return 0;
}
```

在上面的示例中，`Base` 类中的 `printMessage` 函数被声明为虚函数，并在派生类 `Derived` 中进行了重写。通过基类指针指向派生类对象，并调用虚函数 `printMessage`，实际上会在运行时根据对象的实际类型选择调用派生类中的函数，从而实现多态性。

##### 补充：重载的实现机制

在C++中，函数重载是通过函数名和参数列表来实现的。编译器根据函数调用时传递的参数类型、参数个数和参数顺序来判断要调用的具体函数。

当编译器遇到一个函数调用时，它会根据函数名和参数列表的组合来查找匹配的函数声明。编译器会使用以下步骤来解析函数重载：

- 候选函数的查找：编译器会在当前作用域中查找与函数名相同的函数声明。
  精确匹配：编译器会尝试找到与实际参数类型完全匹配的函数。如果找到了精确匹配的函数，就会选择该函数进行调用。
- 类型提升：如果没有找到精确匹配的函数，编译器会尝试进行参数类型的提升（例如，从 int 到 double）。然后，它会再次查找匹配的函数。
- 类型转换：如果仍然找不到精确匹配的函数，编译器会尝试进行标准的类型转换（例如，从 int 到 long）。然后，它会再次查找匹配的函数。
- 默认参数匹配：如果上述步骤仍然无法找到匹配的函数，编译器会尝试使用默认参数进行匹配。
  无法匹配：如果以上步骤都无法找到匹配的函数，编译器将报告错误。

#### 1.3.3 const 常量成员函数与非常量成员函数

在C++中，`const`是一个修饰符，用于声明常量或者修饰成员函数，以指示其不会修改对象的状态。

1. 声明常量：使用`const`修饰符可以声明一个常量，即一个不可修改的值。常量可以是基本数据类型、类对象或指针。

   示例代码：
   ````cpp
   const int x = 5;  // 声明一个常量整数
   const double PI = 3.14159;  // 声明一个常量浮点数
   const std::string message = "Hello";  // 声明一个常量字符串

   // 声明一个常量指针，指向一个整数
   int y = 10;
   int* const ptr = &y;
   ```

   在声明常量时，变量的值不能被修改，任何尝试修改常量的操作都会导致编译错误。

2. 修饰成员函数：使用`const`修饰符可以将成员函数标记为常量成员函数，表示该函数不会修改对象的状态。

   示例代码：
   ````cpp
   class MyClass {
   public:
     void modifyData();  // 非常量成员函数
     void readData() const;  // 常量成员函数
   };
   
   void MyClass::modifyData() {
     // 修改对象的状态
   }
   
   void MyClass::readData() const {
     // 读取对象的状态，但不能修改它
   }
   ```
   
   在常量成员函数中，不能修改对象的非`mutable`成员变量，也不能调用非常量成员函数，以确保常量成员函数不会改变对象的状态。
   
   示例代码：
   ````cpp
   class MyClass {
   public:
     int x;
     mutable int y;
   
     void readData() const {
       x = 5;  // 错误：常量成员函数不能修改非mutable成员变量
       y = 10;  // 正确：常量成员函数可以修改mutable成员变量
       // someFunction();  // 错误：常量成员函数不能调用非常量成员函数
     }
   
     void someFunction() {
       // 修改对象的状态
     }
   };
   ```

通过在变量声明或成员函数声明中使用`const`修饰符，可以提高代码的可读性，同时也可以在编译时进行一些静态检查，以确保对象状态的不变性。

> 常量成员函数（const member functions）和非常量成员函数（non-const member functions）是C++中的两种类型的成员函数，它们在对象的状态修改方面有所不同。
>
> 常量成员函数：
> - 声明时使用`const`关键字修饰，放置在成员函数的参数列表后面。
> - 常量成员函数承诺不会修改对象的状态（即成员变量），它们只能读取对象的状态或调用其他常量成员函数。
> - 在常量成员函数内部，对非`mutable`成员变量的修改操作是不允许的。
> - 常量成员函数可以被常量对象和非常量对象调用。
>
> 非常量成员函数：
> - 没有使用`const`关键字修饰的成员函数被视为非常量成员函数。
> - 非常量成员函数可以修改对象的状态（即成员变量）。
> - 非常量成员函数可以被常量对象和非常量对象调用。
>
> 示例代码：
> ```cpp
> class MyClass {
> public:
>   int x;
>   mutable int y;
> 
>   void nonConstFunc() {
>     x = 5;  // 修改成员变量 x
>     y = 10;  // 修改 mutable 成员变量 y
>   }
> 
>   void constFunc() const {
>     // x = 5;  // 错误：常量成员函数不能修改非 mutable 成员变量
>     y = 10;  // 正确：常量成员函数可以修改 mutable 成员变量
>     // nonConstFunc();  // 错误：常量成员函数不能调用非常量成员函数
>   }
> };
> 
> int main() {
>   MyClass obj;
>   obj.nonConstFunc();  // 调用非常量成员函数
>   const MyClass constObj;
>   constObj.constFunc();  // 调用常量成员函数
> }
> ```
>
> 总结：
> 常量成员函数用于访问和操作对象的状态，但不会修改状态。非常量成员函数可以修改对象的状态。通过正确使用常量成员函数和非常量成员函数，可以提高代码的可读性并确保对象的状态不会被意外修改。

### 2 构造函数

在C++中，构造函数（Constructor）是一种特殊的成员函数，用于创建和初始化对象的过程。构造函数在对象创建时自动调用，并负责初始化对象的成员变量。

以下是在C++中常见的构造函数类型：

#### 2.1.1 默认构造函数（Default Constructor）

如果类没有显式定义构造函数，编译器会自动生成一个默认构造函数。默认构造函数不接受任何参数，用于创建对象的默认初始化。例如：

```cpp
class MyClass {
public:
    MyClass() {
    	// 默认构造函数
    }
};
```

#### 2.1.2 参数化构造函数（Parameterized Constructor）

参数化构造函数接受一个或多个参数，并用于在对象创建时进行初始化。通过在构造函数中传递参数，可以提供不同的初始化选项。例如：

```cpp
class MyClass {
public:
    MyClass(int value) {
    	// 参数化构造函数
    }
};
```

#### 2.1.3 拷贝构造函数（Copy Constructor）

拷贝构造函数用于通过已存在的对象创建一个新对象，并进行成员变量的复制。拷贝构造函数通常以另一个相同类型的对象作为参数，用于初始化新对象的成员变量。例如：

```cpp
class MyClass {
public:
    MyClass(const MyClass& other) {
    	// 拷贝构造函数
    }
};
```

###### 补充： C++  深拷贝与浅拷贝

在C++中，深拷贝（deep copy）和浅拷贝（shallow copy）是与对象复制相关的概念。

浅拷贝是指仅仅复制对象的引用或指针，而不复制对象本身的内容。这意味着被复制的对象和原始对象将共享相同的内存数据。如果其中一个对象修改了共享的数据，那么另一个对象也会受到影响。浅拷贝通常涉及默认的复制构造函数和赋值操作符。例如：

```cpp
class ShallowCopyExample {
private:
    int* data;

public:
    ShallowCopyExample(const ShallowCopyExample& other) {
        data = other.data;  // 执行浅拷贝
    }

    // 其他成员函数和构造函数的定义...
};
```

在上面的例子中，复制构造函数执行了浅拷贝，将指针 `data` 从原始对象直接复制到新对象中。这样，新对象和原始对象将共享相同的 `data` 内存块。

相反，深拷贝是指复制对象本身的内容，而不仅仅是引用或指针。这意味着被复制的对象和原始对象将拥有彼此独立的内存副本，修改其中一个对象不会影响另一个对象。深拷贝通常涉及自定义的复制构造函数和赋值操作符，以确保对象的数据被逐个复制。例如：

```cpp
class DeepCopyExample {
private:
    int* data;

public:
    DeepCopyExample(const DeepCopyExample& other) {
        data = new int(*other.data);  // 执行深拷贝
    }

    DeepCopyExample& operator=(const DeepCopyExample& other) {
        if (this != &other) {
            delete data;  // 释放原有的内存
            data = new int(*other.data);  // 执行深拷贝
        }
        return *this;
    }

    // 其他成员函数和构造函数的定义...
```

#### 2.1.4  移动构造函数（Move Constructor）：

C++11 引入了移动语义和移动构造函数的概念，旨在提高对象的性能和效率。**移动构造函数允许将资源从一个对象转移到另一个对象，而无需执行深拷贝操作。**

移动构造函数通常与右值引用（R-value reference）一起使用，右值引用是用两个连续的 ampersands（&&）表示的引用类型。通过使用移动构造函数，可以有效地从临时对象或即将销毁的对象中“窃取”资源，而不是进行昂贵的数据复制。

以下是一个使用移动构造函数的示例：

```cpp
class MyObject {
private:
    int* data;

public:
    MyObject() : data(nullptr) {}

    // 移动构造函数
    MyObject(MyObject&& other) noexcept {
        data = other.data;
        other.data = nullptr;
    }

    // 其他成员函数和构造函数的定义...

    ~MyObject() {
        delete data;
    }
};
```

在上面的例子中，`MyObject` 类定义了一个移动构造函数。移动构造函数的参数类型是右值引用 `MyObject&&`。在移动构造函数内部，它将 `data` 指针从 `other` 对象窃取，并将 `other.data` 设置为 `nullptr`，以确保在 `other` 对象销毁时不会释放资源。

使用移动构造函数时，可以通过使用 `std::move` 函数将对象转换为右值引用，从而调用移动构造函数。例如：

```cpp
MyObject obj1;
// 假设 obj2 是另一个 MyObject 对象
MyObject obj3 = std::move(obj2);  // 调用移动构造函数
```

在上面的示例中，`std::move(obj2)` 将 `obj2` 转换为右值引用，并调用 `MyObject` 的移动构造函数将资源从 `obj2` 移动到 `obj3` 中。

移动构造函数对于管理大量数据或资源的类非常有用，可以避免不必要的数据复制和资源分配。它在性能和效率上提供了显著的改进。但需要注意的是，移动构造函数不会自动替代复制构造函数，因此在设计类时，仍然需要适当地定义和实现复制构造函数。

##### 补充：什么情况下会使用移动构造函数

移动构造函数（Move Constructor）在C++11中引入，用于高效地将对象的资源所有权从一个对象转移到另一个对象，而无需执行深拷贝。移动构造函数通常用于以下情况：

1. 临时对象的转移：当使用临时对象（例如函数返回的临时对象）来初始化新对象时，编译器会尝试使用移动构造函数来避免不必要的复制操作。移动构造函数将临时对象的资源所有权转移到新对象，避免了不必要的资源拷贝，提高了性能。

2. 容器的动态增长：当使用动态增长的容器（如`std::vector`）存储对象时，容器可能需要重新分配内存来容纳更多的元素。在重新分配内存时，容器会使用移动构造函数来将现有元素的资源从旧的内存位置移动到新的内存位置，而不是进行昂贵的复制操作。

3. 传递所有权的语义：在某些情况下，需要将对象的所有权从一个对象转移到另一个对象，而不是进行资源的复制。移动构造函数可以用于实现这种传递所有权的语义，例如在实现移动语义的智能指针类中。

需要注意的是，移动构造函数通常通过“右值引用”来接收参数，即使用双引号 && 来修饰参数类型。这样可以标识出传递的是一个即将被销毁的临时对象或具有右值属性的对象，从而触发移动构造函数的调用。

以下是一个使用移动构造函数的简单示例，展示了如何在移动语义下转移资源的所有权：

```cpp
#include <iostream>

class Resource {
public:
    Resource() {
        std::cout << "Resource default constructor" << std::endl;
        // 执行资源的分配操作
    }

    Resource(const Resource& other) {
        std::cout << "Resource copy constructor" << std::endl;
        // 执行资源的复制操作
    }

    Resource(Resource&& other) {
        std::cout << "Resource move constructor" << std::endl;
        // 执行资源的转移操作
    }

    ~Resource() {
        std::cout << "Resource destructor" << std::endl;
        // 执行资源的释放操作
    }
};

int main() {
    Resource r1;  // 调用默认构造函数
    Resource r2(r1);  // 调用拷贝构造函数
    Resource r3(std::move(r1));  // 调用移动构造函数

    return 0;
}
```

在上面的示例中，定义了一个 `Resource` 类，在不同的构造函数和析构函数中输出相应的信息。在 `main` 函数中，创建了三个 `Resource` 对象 `r1`、`r2` 和 `r3`，并观察构造函数和析构函数的调用顺序。

其中，`r1` 是通过默认构造函数初始化的，`r2` 是通过拷贝构造函数从 `r1` 进行复制初始化的，而 `r3` 是通过移动构造函数从 `r1` 进行移动初始化的。可以看到，在移动构造函数中，资源的所有权被转移到了 `r3`，而不是进行资源的复制操作。

移动构造函数的使用可以大大提高程序的性能，特别是在处理大型对象或具有昂贵资源的对象时。它可以避免不必要的资源复制和额外的内存分配，提高程序的效率。

### 3.  析构函数

在C++中，析构函数（Destructor）是一种特殊类型的成员函数，用于在对象的生命周期结束时进行清理和资源释放操作。析构函数的名称与类名称相同，但在名称前面加上波浪号（~）作为前缀。

析构函数在以下情况下自动调用：
- 当对象的作用域结束时，例如在函数结束时局部对象的作用域结束。
- 当使用`delete`关键字释放通过`new`关键字分配的动态内存时，析构函数会被调用。
- 当对象是类的成员，并且包含该对象的类的析构函数被调用时，该对象的析构函数也会被调用。

析构函数的特点如下：
1. 析构函数没有任何参数，包括无返回类型（包括`void`）。
2. 每个类只能有一个析构函数，不允许重载。
3. 如果没有显式定义析构函数，编译器会自动生成一个默认的析构函数。
4. 析构函数的命名规则是在类名前加上波浪号（~）。

以下是一个示例，展示了如何定义和使用析构函数：

```cpp
class MyClass {
public:
    int* data;

    // 构造函数
    MyClass() {
        data = new int[10];  // 分配动态内存
    }

    // 析构函数
    ~MyClass() {
        delete[] data;  // 释放动态内存
    }
};

int main() {
    MyClass obj;  // 创建对象

    // 在这里使用 obj 对象

    // 当 obj 对象的作用域结束时，析构函数会被自动调用，释放动态内存

    return 0;
}
```

在上面的示例中，`MyClass`类定义了一个构造函数和一个析构函数。构造函数在创建对象时分配了动态内存，而析构函数在对象的作用域结束时释放了该内存。这确保了在对象不再需要时，其相关资源得到了正确的清理和释放。

析构函数在管理资源（如动态内存、文件句柄等）方面非常有用，它允许我们在对象的生命周期结束时进行必要的清理操作，防止资源泄漏和内存泄漏。

##### 补充：只定义析构函数，会自动创建那些构造函数

如果只定义了析构函数而没有显式定义其他构造函数，编译器会根据需要自动生成以下构造函数：

1. **默认构造函数**（Default Constructor）：如果没有任何构造函数被定义，编译器会自动生成一个无参的默认构造函数。这个默认构造函数没有任何参数，并且没有执行任何特定的初始化操作。

2. **拷贝构造函数**（Copy Constructor）：当需要进行对象的拷贝初始化时（如通过值传递参数、返回对象或者进行对象的赋值操作），编译器会自动生成一个拷贝构造函数。拷贝构造函数用于创建一个新对象，并将其初始化为与现有对象相同的值。

请注意，如果您显式定义了其他构造函数（包括默认构造函数或拷贝构造函数），编译器将不会自动生成对应的构造函数。因此，如果您只定义了析构函数，并且希望使用默认构造函数或拷贝构造函数，您需要显式定义这些构造函数。

下面是一个示例，演示了当只定义析构函数时，编译器会自动生成的默认构造函数和拷贝构造函数：

```cpp
#include <iostream>

class MyClass {
public:
    ~MyClass() {
        std::cout << "Destructor called" << std::endl;
    }

    // 显式定义析构函数，并使用默认构造函数和拷贝构造函数
};

int main() {
    MyClass obj1;  // 调用默认构造函数
    MyClass obj2(obj1);  // 调用拷贝构造函数

    return 0;
}
```

在上面的示例中，只定义了析构函数，而没有显式定义其他构造函数。编译器会自动生成默认构造函数和拷贝构造函数，并在 `main` 函数中的对象创建和拷贝初始化时使用这些自动生成的构造函数。当对象超出作用域时，析构函数会被调用。

##### 补充：定义一个空类，会创建那些函数

当您定义一个空类时，即没有显式定义任何成员函数和成员变量时，编译器会为该类自动生成以下函数：

1. **默认构造函数**（Default Constructor）：编译器会自动生成一个无参的默认构造函数。这个默认构造函数没有任何参数，并且没有执行任何特定的初始化操作。

2. **拷贝构造函数**（Copy Constructor）：编译器会自动生成一个拷贝构造函数。拷贝构造函数用于创建一个新对象，并将其初始化为与现有对象相同的值。

3. **拷贝赋值运算符**（Copy Assignment Operator）：编译器会自动生成一个拷贝赋值运算符函数。拷贝赋值运算符用于将一个对象的值赋给另一个对象。

4. **析构函数**（Destructor）：编译器会自动生成一个析构函数。析构函数用于在对象被销毁时执行清理操作。

这些函数被称为"特殊成员函数"，它们在需要时由编译器自动生成，并且具有默认的行为。对于空类，这些特殊成员函数的默认实现通常是足够的。

下面是一个示例，演示了当定义一个空类时，编译器会自动生成的特殊成员函数：

```cpp
#include <iostream>

class EmptyClass {
    // 空类，没有显式定义任何成员函数和成员变量
};

int main() {
    EmptyClass obj1;  // 调用默认构造函数
    EmptyClass obj2(obj1);  // 调用拷贝构造函数
    obj2 = obj1;  // 调用拷贝赋值运算符

    return 0;
}
```

在上面的示例中，定义了一个空类 `EmptyClass`，并在 `main` 函数中创建对象、进行对象的拷贝初始化和赋值操作。编译器会根据需要自动生成默认构造函数、拷贝构造函数和拷贝赋值运算符，并在对象的创建和赋值操作时使用这些自动生成的函数。当对象超出作用域时，析构函数会被调用。

### 4.函数重载

Node/cpp 继承.md

函数重载是指在同一个作用域内定义多个具有相同名称但参数列表不同的函数。通过函数重载，可以根据不同的参数类型和数量来调用适合的函数。

函数重载的优点是可以提高代码的可读性和灵活性，使代码更加模块化和易于维护。它允许使用相同的函数名来执行类似但不完全相同的操作。

以下是一个函数重载的示例：

```cpp
#include <iostream>

// 重载的函数
void printNumber(int num) {
    std::cout << "Integer number: " << num << std::endl;
}

void printNumber(double num) {
    std::cout << "Double number: " << num << std::endl;
}

int main() {
    int integerNum = 10;
    double doubleNum = 3.14;

    printNumber(integerNum);  // 调用第一个重载的函数
    printNumber(doubleNum);   // 调用第二个重载的函数

    return 0;
}
```

在上面的示例中，定义了两个名为 `printNumber` 的函数，一个接受 `int` 类型的参数，另一个接受 `double` 类型的参数。通过重载这两个函数，可以根据传递的参数类型来选择合适的函数进行调用。

在调用 `printNumber` 函数时，编译器会根据传递的参数类型来匹配最合适的重载函数。在上述示例中，传递 `integerNum` 调用的是接受 `int` 参数的函数，而传递 `doubleNum` 调用的是接受 `double` 参数的函数。

需要注意以下几点：

1. 重载函数必须在同一个作用域内定义。
2. 重载函数的参数列表必须不同，可以通过参数的类型、顺序和数量来区分。
3. 重载函数的返回类型可以相同也可以不同，返回类型不是重载函数的区分标准。
4. 重载函数可以有不同的访问修饰符（如 `public`、`private`、`protected`）。
5. 函数重载可以应用于成员函数和非成员函数。

在设计函数重载时，应确保函数的参数列表足够明确，以避免二义性的情况。编译器将根据调用时的参数类型和数量进行最佳匹配，但如果存在多个重载函数都能匹配，就会导致重载冲突错误。因此，在设计函数重载时，需要注意参数的类型和数量，以确保函数调用的唯一性。

### 补充：内联函数

内联函数（Inline Function）是一种在编译时展开函数调用的机制。使用内联函数可以有效地减少函数调用的开销，提高程序的执行效率。内联函数通常适用于短小且频繁调用的函数。

将函数声明为内联函数的方式是在函数定义前面加上 `inline` 关键字。编译器会尝试在调用内联函数的地方将函数的代码插入到调用的位置，而不是通过跳转到函数的地址进行调用。这样可以消除函数调用的开销，因为不需要保存和恢复调用现场、传递参数等操作，从而提高程序的执行速度。

以下是一个简单的内联函数的示例：

```cpp
#include <iostream>

inline int Add(int a, int b) {
    return a + b;
}

int main() {
    int result = Add(3, 4);
    std::cout << "Result: " << result << std::endl;  // 输出: 7

    return 0;
}
```

在上面的示例中，将 `Add` 函数声明为内联函数。在 `main` 函数中，调用了 `Add` 函数进行整数相加操作，并将结果打印输出。

需要注意的是，内联函数的展开是由编译器决定的，它并不是强制要求编译器进行内联展开。编译器会根据一些因素（如函数的复杂性、函数的大小等）来决定是否展开函数调用。因此，将函数声明为内联函数并不意味着一定会进行内联展开。

一般来说，适合内联的函数应该满足以下条件：
- 函数体较小，通常只有几行代码。
- 函数的调用频率较高。
- 函数没有复杂的控制流（如循环、递归等）。
- 函数没有包含无法内联展开的代码（如虚函数、递归调用等）。

需要注意的是，过度使用内联函数可能会导致代码膨胀，增加可执行文件的大小。因此，应谨慎使用内联函数，根据实际情况进行权衡和选择。一般来说，内联函数适用于简单的、频繁调用的函数，而复杂的函数或函数体较大的函数不太适合内联。

### 5. 类继承的其他问题

#### 5.1 菱形继承

菱形继承（Diamond Inheritance）是指一个派生类通过两个不同的途径继承同一个基类，形成了一个菱形的继承结构。这种继承结构可能导致一些问题，如二义性和资源的冗余。

让我们通过一个示例来说明菱形继承的问题：

```cpp
#include <iostream>

class Base {
public:
    int value;
};

class Derived1 : public Base {
};

class Derived2 : public Base {
};

class Derived3 : public Derived1, public Derived2 {
};

int main() {
    Derived3 d3;
    d3.Derived1::value = 10;
    d3.Derived2::value = 20;

    std::cout << "d3.Derived1::value: " << d3.Derived1::value << std::endl;  // 输出: 10
    std::cout << "d3.Derived2::value: " << d3.Derived2::value << std::endl;  // 输出: 20

    // std::cout << "d3.value: " << d3.value << std::endl;  // 编译错误，二义性

    return 0;
}
```

在上面的示例中，`Base` 是一个基类，`Derived1` 和 `Derived2` 分别从 `Base` 继承。然后，`Derived3` 从 `Derived1` 和 `Derived2` 派生，形成了一个菱形继承结构。

在 `main` 函数中，我们创建了一个 `Derived3` 对象 `d3`。**由于 `Derived3` 继承了 `Derived1` 和 `Derived2`，所以它包含了两个 `Base` 子对象，即 `Derived1` 的 `Base` 子对象和 `Derived2` 的 `Base` 子对象。**

问题出现在当我们尝试访问 `d3` 的 `value` 成员时。**由于 `d3` 包含了两个 `Base` 子对象，编译器无法确定我们要访问哪一个 `Base` 子对象的 `value` 成员，从而导致了二义性。**在这个例子中，我们可以使用作用域解析运算符 `::` 来明确指定访问哪个 `Base` 子对象的 `value` 成员。

菱形继承的问题可以通过使用虚继承来解决，如前面所述。通过在 `Derived1` 和 `Derived2` 继承 `Base` 的声明中添加 `virtual` 关键字，可以确保 `Derived3` 只包含一个共享的 `Base` 实例，避免了二义性和资源冗余的问题。

#### 5.2 虚继承

虚继承（Virtual Inheritance）是C++中用于解决多重继承中的菱形继承问题的一种机制。**当一个类从多个基类派生而来，而这些基类之间存在共同的基类时，菱形继承会导致派生类中包含多个共同基类的实例，**可能引发二义性和内存浪费的问题。

虚继承通过在继承关系中使用 `virtual` 关键字来解决菱形继承问题。**当一个类通过虚继承继承自某个基类时，该基类被标记为虚基类，派生类只维护对虚基类的一个共享实例**。这样可以避免多个实例的冗余，并确保对虚基类成员的访问是一致的。

下面是一个简单的示例，演示了虚继承的使用：

```cpp
#include <iostream>

class Base {
public:
    int value;
};

class Derived1 : public virtual Base {
};

class Derived2 : public virtual Base {
};

class Derived3 : public Derived1, public Derived2 {
};

int main() {
    Derived3 d3;
    d3.value = 10;

    Derived1* d1 = &d3;
    Derived2* d2 = &d3;
    std::cout << "d1->value: " << d1->value << std::endl;  // 输出: 10
    std::cout << "d2->value: " << d2->value << std::endl;  // 输出: 10

    return 0;
}
```

在上面的示例中，**`Base` 是一个基类，`Derived1` 和 `Derived2` 分别从 `Base` 虚继承，它们都维护了对 `Base` 的共享实例。**然后，`Derived3` 从 `Derived1` 和 `Derived2` 派生，这样就避免了 `Derived3` 中包含多个 `Base` 实例。

通过虚继承，`d1` 和 `d2` 都能够访问到 `Derived3` 中的 `Base` 实例，并且它们的值保持一致。

需要注意的是，虚继承可能会引入一些运行时的开销，因为派生类需要在对象布局中维护对虚基类的指针或偏移量。另外，虚继承应该在确实需要解决菱形继承问题时使用，而不是作为默认的继承方式。

#### 5.3 虚析构与虚构造

在C++中，虚构造函数（Virtual Constructor）是一种概念，并没有直接对应的语言特性。C++中的构造函数不能被声明为虚函数，因为构造函数的调用是根据对象的静态类型确定的，而不是动态类型。

然而，C++中的虚析构函数（Virtual Destructor）是一种非常常见和有用的特性。**虚析构函数用于在基类中定义一个虚函数，并由派生类重写，以确保在删除一个指向派生类对象的基类指针时，能够正确地调用派生类的析构函数。**

虚析构函数的定义方式如下：

```cpp
class Base {
public:
    virtual ~Base() {
        // 基类析构函数的实现
    }
};

class Derived : public Base {
public:
    ~Derived() override {
        // 派生类析构函数的实现
    }
};
```

在上面的示例中，基类 `Base` 声明了一个虚析构函数 `~Base()`，并使用关键字 `virtual` 进行修饰。派生类 `Derived` 重写了基类的虚析构函数，并使用关键字 `override` 进行标记。

当通过基类指针删除一个指向派生类对象的对象时，只有在基类的析构函数被声明为虚函数时，才会调用正确的派生类析构函数。这样可以确保派生类的资源被正确地释放，避免内存泄漏。

示例代码如下所示：

```cpp
int main() {
    Base* basePtr = new Derived();  // 向上转型
    delete basePtr;  // 调用 Derived 的析构函数
    return 0;
}
```

在上面的示例中，通过基类指针 `basePtr` 创建了一个派生类对象，并使用 `delete` 运算符删除了该对象。由于基类的析构函数是虚函数，因此会正确地调用派生类 `Derived` 的析构函数，确保资源的正确释放。

需要注意的是，将基类的析构函数声明为虚函数会导致虚函数表的存在，这会增加一些运行时开销。因此，只有在需要通过基类指针删除派生类对象时，才应该将析构函数声明为虚函数。

#### 5.4 模板类

模板类（Template Class）是C++中一种可以根据类型参数生成具体类的机制。通过使用模板类，可以编写通用的代码，使其能够适用于多种数据类型，从而提高代码的重用性和灵活性。

模板类的定义以关键字 `template` 开始，后面跟着模板参数列表。模板参数可以是类型参数、非类型参数或模板参数包。然后，在类的定义中，可以使用这些模板参数来声明成员变量、成员函数和内部类型等。

下面是一个简单的模板类的示例，展示了如何定义和使用一个存储固定大小的数组的模板类：

```cpp
template <typename T, int Size>
class Array {
private:
    T elements[Size];

public:
    void Set(int index, const T& value) {
        elements[index] = value;
    }

    T Get(int index) const {
        return elements[index];
    }
};

int main() {
    Array<int, 5> intArray;
    Array<double, 10> doubleArray;

    intArray.Set(0, 1);
    intArray.Set(1, 2);
    intArray.Set(2, 3);

    doubleArray.Set(0, 1.1);
    doubleArray.Set(1, 2.2);
    doubleArray.Set(2, 3.3);

    int intValue = intArray.Get(1);
    double doubleValue = doubleArray.Get(2);

    return 0;
}
```

在上面的示例中，定义了一个模板类 `Array`，它有两个模板参数：`T` 表示数组元素的类型，`Size` 表示数组的大小。在类的定义中，使用模板参数 `T` 声明了一个私有成员变量 `elements`，它是一个固定大小的数组。然后，定义了 `Set` 和 `Get` 成员函数，用于设置和获取数组中的元素。

在 `main` 函数中，通过提供具体的类型参数和非类型参数，实例化了两个模板类对象 `intArray` 和 `doubleArray`。然后，使用这些对象调用成员函数进行数组元素的设置和获取操作。

模板类的使用不限于基本数据类型，还可以用于自定义类型、类模板的实例化等。通过模板类，可以实现泛型编程，使代码更加通用和灵活。

##### 补充：模板类与类模板

模板类（Template Class）和类模板（Class Template）是C++中用于实现通用数据结构和算法的重要特性。它们允许在定义类或类的成员时使用参数化类型，从而实现对不同类型的支持。

类模板是指定义一个通用的类框架，其中的类型或值可以通过模板参数进行参数化。类模板的定义使用关键字 `template` 和模板参数列表来指定参数化类型或值。以下是一个简单的类模板示例：

```cpp
template <typename T>
class MyContainer {
public:
    MyContainer(T value) : data(value) {}

    void print() {
        std::cout << "Value: " << data << std::endl;
    }

private:
    T data;
};

int main() {
    MyContainer<int> container1(42);
    container1.print();  // 输出: Value: 42

    MyContainer<std::string> container2("Hello");
    container2.print();  // 输出: Value: Hello

    return 0;
}
```

在上面的示例中，定义了一个类模板 `MyContainer`，其中的类型参数 `T` 用于指定数据的类型。类模板中的成员函数和成员变量可以使用类型参数 `T`，并在实例化时会根据具体的类型进行替换。在 `main` 函数中，通过提供不同的类型参数实例化了两个 `MyContainer` 对象，并调用了 `print` 函数打印输出。

模板类是指使用类模板定义的具体化的类，也称为模板类的实例化。通过为类模板提供具体的类型或值，可以生成模板类。模板类是类模板的具体化，它是一个具体的类类型，可以进行实例化、继承和实现。例如，在上面的示例中，`MyContainer<int>` 和 `MyContainer<std::string>` 就是模板类的实例。

模板类和类模板的使用使得我们可以编写通用的代码，而无需为每种类型编写重复的代码。它们广泛应用于容器类（如 `std::vector`、`std::list` 等）、算法类（如排序、查找等）、数值计算、泛型编程等领域。

需要注意的是，类模板和模板类的定义通常放在头文件中，因为编译器需要在每个使用模板的地方进行实例化和展开。这样可以确保模板的定义在使用之前可见，并避免链接错误。

#### 5.5 仿函数

**仿函数（Functor）是指重载了函数调用运算符 `operator()` 的类或结构体。**通过使用仿函数，**可以将对象像函数一样调用，实现了函数对象的概念。**仿函数可以具有状态，可以在调用期间保存和修改状态，并且可以在多次调用之间保持状态信息。

下面是一个简单的示例，展示了如何定义和使用一个加法仿函数：

```cpp
#include <iostream>

class AddFunctor {
public:
    int operator()(int a, int b) {
        return a + b;
    }
};

int main() {
    AddFunctor add;
    int result = add(3, 4);

    std::cout << "Result: " << result << std::endl;  // 输出: 7

    return 0;
}
```

在上面的示例中，定义了一个名为 `AddFunctor` 的类，它重载了函数调用运算符 `operator()`。在 `operator()` 函数中，实现了将两个整数相加的逻辑，并返回它们的和。

在 `main` 函数中，创建了一个 `AddFunctor` 对象 `add`。然后，可以像调用函数一样使用 `add` 对象，将两个整数作为参数传递给它，并获取返回的结果。

仿函数可以具有构造函数和成员变量，这使得它们可以在调用期间保存状态信息。这使得仿函数在某些情况下比函数指针更灵活，因为它们可以保持状态，并且可以通过修改成员变量来传递和共享状态。

仿函数在STL（标准模板库）中广泛使用，它们被用作算法的参数，例如`std::sort`和`std::transform`等函数。通过提供自定义的仿函数，可以根据特定的需求定制算法的行为。
