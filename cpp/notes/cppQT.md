# CPP QT

## 1、第一个 Qt 项目

```shell
firstQt.pro
firstQt.pro.user
firstQt_zh_CN.ts
main.cpp
widget.cpp
widget.h
```

### 1.1 main.cpp 

```cpp
#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}

```

`QApplication`应用程序类，在qt项目中，只有一个`QApplication`对象。

### 1.2 widget.cpp

```cpp
#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
}

Widget::~Widget()
{
}


```

### 1.3 Widget.h

```cpp
#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
};
#endif // WIDGET_H

```

### 1.4 firstQt.pro

```shell
# 核心部件
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    widget.cpp

HEADERS += \
    widget.h

TRANSLATIONS += \
    firstQt_zh_CN.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

```

## 2、添加btn

### 2.1 修改头文件

```cpp
#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
// 添加头文件
#include <QPushButton>

class Widget : public QWidget
{
    // 如果要使用信号槽，就必须加上这个宏
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

// 添加成员
private:
    QPushButton *p_btn;
    QPushButton btn;
};
#endif // WIDGET_H

```

### 2.2 添加控件关系

```cpp
#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    // 初始化函数
    // 指定父类为 this,
    p_btn = new QPushButton(this);
    // 指定按钮显示文本
    p_btn->setText("p_btn 点击");
    // 显示控件
    p_btn->show();

    btn.setParent(this);
    btn.setText("btn 点击");
    btn.move(100, 100);
}

Widget::~Widget()
{
    // 可以不进行内存释放
    // qt 可以对 QObjest 类的子类进行自动释放内存
    // 1. 必须直接或者间接继承
    // 2. 内存释放的时候，先析构子类，再析构父类
    // delete  p_btn;
}

```

## 3. 信号槽

### 3.1 connect

在C++和Qt中，`connect`函数用于连接信号（Signal）和槽（Slot），以实现对象间的通信。以下是`connect`函数的使用方法：

```cpp
connect(sender, SIGNAL(signal()), receiver, SLOT(slot()));
```

其中，`sender`是发出信号的对象，`signal()`是发出的信号，`receiver`是接收信号的对象，`slot()`是接收信号的**槽函数**。

下面是一个示例，演示了如何使用`connect`函数连接一个按钮的点击信号和一个槽函数：

```cpp
#include <QApplication>
#include <QPushButton>
#include <QDebug>

// 槽函数
void buttonClicked()
{
    qDebug() << "Button clicked!";
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // 创建一个按钮
    QPushButton button("Click me");

    // 连接按钮的clicked信号和槽函数buttonClicked
    QObject::connect(&button, SIGNAL(clicked()), &button, SLOT(buttonClicked()));

    // 显示按钮
    button.show();

    // 运行应用程序事件循环
    return app.exec();
}
```

在上述示例中，当按钮被点击时，`buttonClicked`函数将被调用，并输出"Button clicked!"。`connect`函数用于将按钮的`clicked`信号连接到`buttonClicked`槽函数上。

### 3.2 自定义槽函数

在Qt中，可以使用自定义槽函数来响应信号。自定义槽函数是普通的C++成员函数，可以在类中声明和定义。以下是使用自定义槽函数的示例：

cpp

复制

```cpp
#include <QApplication>
#include <QPushButton>
#include <QDebug>

// 自定义槽函数
class MyObject : public QObject
{
    Q_OBJECT

public slots:
    void mySlot()
    {
        qDebug() << "Custom slot called!";
    }
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // 创建一个按钮
    QPushButton button("Click me");

    // 创建一个自定义对象
    MyObject myObject;

    // 连接按钮的clicked信号和自定义对象的槽函数
    QObject::connect(&button, SIGNAL(clicked()), &myObject, SLOT(mySlot()));

    // 显示按钮
    button.show();

    // 运行应用程序事件循环
    return app.exec();
}
```

在上述示例中，我们定义了一个名为`MyObject`的自定义类，并在其中声明了一个名为`mySlot`的槽函数。在`main`函数中，我们创建了一个`MyObject`对象`myObject`，并使用`connect`函数将按钮的`clicked`信号连接到`mySlot`槽函数。

当按钮被点击时，`mySlot`槽函数将被调用，并输出"Custom slot called!"。

需要注意的是，为了使用自定义槽函数，需要在包含自定义槽函数的类的声明中添加`Q_OBJECT`宏，并在CMake或qmake等构建系统中使用MOC（Meta-Object Compiler）来处理该类。

### 3.3 自定义信号

```cpp
#ifndef SUBWIDGET_H
#define SUBWIDGET_H

#include <QWidget>
#include <QPushButton>

class subWidget : public QWidget
{
    Q_OBJECT
public:
    explicit subWidget(QWidget *parent = nullptr);
private:
    QPushButton *btn;
    void btnClicked();

signals:
    // 自定义信号
void signSub();
    /*
        1. 可以有参数
        2. 可以重载
        3. 返回值为 void
        4. 发送信号 emit + 信号名
        5. 必须在 signals 内被包裹
    */
};

#endif // SUBWIDGET_H
```

```cpp
#include "subwidget.h"
#include "QPushButton"
#include "mainwidget.h"

subWidget::subWidget(QWidget *parent) : QWidget(parent)
{
    this->setWindowTitle("subWindos");
    btn = new QPushButton("点击", this);
    this->resize(500, 500);
	# 进行连接
    connect(btn, &QPushButton::clicked, this, &subWidget::btnClicked);
}

// 发送信号
void subWidget::btnClicked()
{
    emit signSub();
}

```

### 3.4 重载信号

#### 3.4.1 subWiget.h

```cpp
#ifndef SUBWIDGET_H
#define SUBWIDGET_H

#include <QWidget>
#include <QPushButton>

class subWidget : public QWidget
{
    Q_OBJECT
public:
    explicit subWidget(QWidget *parent = nullptr);
private:
    QPushButton *btn;
    void btnClicked();

signals:
    // 自定义重载信号
void signSub();
void signSub(int, QString);

};

#endif // SUBWIDGET_H

```

#### 3.4.2 subWiget.cpp

```cpp
#include "subwidget.h"
#include "QPushButton"
#include "mainwidget.h"

subWidget::subWidget(QWidget *parent) : QWidget(parent)
{
    this->setWindowTitle("subWindos");
    btn = new QPushButton("点击", this);

    this->resize(500, 500);

    connect(btn, &QPushButton::clicked, this, &subWidget::btnClicked);
}

// 信号可以发送多次
void subWidget::btnClicked()
{
    emit signSub();
    emit signSub(250, "发送 250");
}

```

#### 3.4.3 MainWidget.h

```cpp
#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QPushButton>
#include "subwidget.h"

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();
	// 信号槽处理函数
    void  clickedProcess();
    void  clickedsubProcess();
    void  clickedsubProcessMsg(int, QString);

public:
    subWidget *subWig;
    QPushButton *btn;
};
#endif // MAINWIDGET_H

```

#### 3.4.3 MainWidget.cpp

```cpp 
#include "mainwidget.h"
#include <QDebug>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    subWig = new subWidget();
    btn = new QPushButton("点击", this);
    this->setWindowTitle("Main Widget");
    this->resize(500, 500);

    connect(btn, &QPushButton::clicked, this, &MainWidget::clickedProcess);

    // 针对重载函数，需要使用函数指针确定函数地址
    void (subWidget:: * mySinsub)() = &subWidget::signSub;
    connect(subWig, mySinsub, this, &MainWidget::clickedsubProcess);

    void (subWidget:: * mySinsub2)(int, QString) = &subWidget::signSub;
    connect(subWig, mySinsub2, this, &MainWidget::clickedsubProcessMsg);
}

MainWidget::~MainWidget()
{
}

void MainWidget::clickedProcess(){
    subWig->show();
    this->hide();
}

void MainWidget::clickedsubProcess(){
    this->show();
    subWig->hide();
}

void MainWidget::clickedsubProcessMsg(int id, QString msg)
{
    qDebug() << id << " " << msg.toUtf8().data() << "\n" ;
}
```

### 3.5 Lamdba 表达式

C++ lambda表达式是在C++11标准中引入的一种特性，它允许我们在代码中定义匿名函数。lambda表达式的语法如下：

```
[capture-list] (parameters) -> return-type {
    // 函数体
}
```

解释一下lambda表达式的各个部分：

1. Capture List（捕获列表）：捕获列表是可选的，用于指定在lambda函数体中使用的外部变量。可以通过值捕获或引用捕获来捕获变量。捕获列表出现在方括号`[]`中，可以为空（不捕获任何变量），也可以包含一个或多个变量。

2. Parameters（参数）：参数列表是可选的，用于指定lambda函数的参数。与普通函数一样，参数可以有名称和类型。

3. Return Type（返回类型）：返回类型是可选的，用于指定lambda函数的返回类型。如果省略了返回类型，编译器会自动推断返回类型。

4. Function Body（函数体）：函数体包含了lambda函数的具体实现。

下面是一个简单的lambda表达式示例，它将两个整数相加并返回结果：

```cpp
int result = [](int a, int b) -> int {
    return a + b;
}(3, 4);
```

在上面的示例中，lambda表达式接收两个整数参数，并将它们相加后返回结果。表达式的执行是通过在lambda表达式后面添加小括号并提供参数来完成的（在这种情况下，参数是3和4）。在这个例子中，lambda表达式的返回类型被显式指定为`int`，但由于返回类型可以被自动推断，我们也可以省略返回类型的指定。

需要注意的是，lambda表达式可以作为函数对象使用，也可以作为参数传递给其他函数，这使得它们在编写函数对象或回调函数时非常方便。

**connect 使用lamdba 表达式**

```cpp
    connect(btn, &QPushButton::clicked, this, [=](){
        btn->setText("Changed by lamdba !");
    });
```

### 3.6 总结

## 4. 窗口类

### 4.1 QWidget

### 4.2 QMianWindow

### 4.3 QDialog

#### 4.3.1 模态对话框



#### 4.3.2 非模块对话框

### 4.4 Button

#### 4.4.1 QPushButton 

#### 4.4.2 QRedioButton

#### 4.4.3 QChechBox

### 4.4 QListView

### 4.5 QListWidget

#### 4.5.1 ListWidget

#### 4.5.2TableWidget

1、指定行数



2、 指定列数

### 4.6. Contener

## 5. 自定义控件

提升



## 6. 事件

鼠标按键判断

```cpp
void MyLabel::mouseReleaseEvent(QMouseEvent *ev)
{
    if (ev->button() == Qt::LeftButton)
    {
        setText("LeftButton");
    }
    if (ev->button() == Qt::RightButton)
    {
        setText("RightButton");
    }
    if (ev->button() == Qt::MidButton)
    {
        setText("MidButton");
    }
}
```

### button() 和 buttons()

`button()` 和 `buttons()` 是两个不同的函数，常用于 Qt 中的对话框类（如 QDialog）的按钮操作。它们的区别如下：

1. `button()` 函数：
   - `button()` 函数用于获取对话框中的特定按钮对象。
   - 它接受一个参数，该参数是一个枚举值或标识特定按钮的 QDialogButtonBox::ButtonRole。
   - 返回值是一个指向 QPushButton 对象的指针，表示对应的按钮。
   - 当对话框中有多个按钮时，可以使用 `button()` 函数获取特定按钮，然后对其进行操作（如设置文本、连接信号槽等）。
   - 示例用法：
     ```cpp
     QPushButton *okButton = dialog->button(QDialogButtonBox::Ok);
     okButton->setText("OK");
     connect(okButton, &QPushButton::clicked, this, &MyClass::handleOkButtonClicked);
     ```

2. `buttons()` 函数：
   - `buttons()` 函数用于获取对话框中所有按钮的列表。
   - 它不接受任何参数。
   - 返回值是一个 QList<QAbstractButton *>，包含对话框中所有的按钮。
   - 通过遍历返回的按钮列表，可以对对话框中的所有按钮进行操作（如设置文本、连接信号槽等）。
   - 示例用法：
     ```cpp
     QList<QAbstractButton *> allButtons = dialog->buttons();
     for (QAbstractButton *button : allButtons) {
         button->setText("New Text");
         connect(button, &QPushButton::clicked, this, &MyClass::handleButtonClicked);
     }
     ```

总结来说，`button()` 函数用于获取特定按钮对象，而 `buttons()` 函数用于获取所有按钮对象的列表。通过这两个函数，你可以方便地对对话框中的按钮进行操作和处理相应的信号槽。

## 定时器

### 第一种实现方式

```cpp
#include "mylabel.h"
#include <QTimerEvent>

MyLabel::MyLabel(QWidget *parent) : QLabel(parent)
{
    // 启动定时器
    id = startTimer(100);
}

void MyLabel::timerEvent(QTimerEvent *e)
{
    static int num = 0;
    QString str = QString("%1 : %2").arg("Time out: ").arg(num++);
    if (num == 100)
    {
        // 关闭定时器
        killTimer(id);
    }
    setText(str);
}

```

### 第二种实现方式

```cpp
#include "mylabel.h"
#include <QTimer>

MyLabel::MyLabel(QWidget *parent) : QLabel(parent)
{
    QTimer *timer = new QTimer(this);
    static int num = 0;
    connect(timer, &QTimer::timeout, this, [=]{
        num ++ ;
        this->setText(QString::number(num));
    });
    timer->start(100);
}

```

## 7. QString 

QString 是Qt框架中用于处理字符串的类。它提供了许多方法和功能，使字符串的处理更加方便和高效。下面是一些常见的 QString 方法和使用案例：

1. 构造函数和赋值操作符：
   - 使用默认构造函数创建一个空的 QString 对象：
     ```cpp
     QString str;
     ```
   - 使用字符串字面值或C风格字符串初始化 QString 对象：
     ```cpp
     QString str1 = "Hello";
     QString str2("World");
     ```
   - 使用赋值操作符将一个 QString 对象赋值给另一个对象：
     ```cpp
     QString str3 = str1;
     ```

2. 获取字符串的长度和判断是否为空：
   - 使用 `length()` 方法获取字符串的长度：
     ```cpp
     int length = str.length();
     ```
   - 使用 `isEmpty()` 方法判断字符串是否为空：
     ```cpp
     if (str.isEmpty()) {
         // 字符串为空
     }
     ```

3. 字符串的连接和追加：
   - 使用 `+` 运算符连接两个字符串：
     ```cpp
     QString str1 = "Hello";
     QString str2 = "World";
     QString result = str1 + str2;  // 结果为 "HelloWorld"
     ```
   - 使用 `append()` 方法追加字符串：
     ```cpp
     QString str = "Hello";
     str.append("World");  // 结果为 "HelloWorld"
     ```

4. 字符串的查找和替换：
   - 使用 `indexOf()` 方法查找子字符串的位置：
     ```cpp
     QString str = "Hello World";
     int index = str.indexOf("World");  // 结果为 6
     ```
   - 使用 `replace()` 方法替换字符串中的子字符串：
     ```cpp
     QString str = "Hello World";
     str.replace("World", "OpenAI");  // 结果为 "Hello OpenAI"
     ```

5. 字符串的转换：
   - 将 QString 转换为标准字符串：
     ```cpp
     QString str = "Hello";
     std::string stdStr = str.toStdString();
     ```
   - 将标准字符串转换为 QString：
     ```cpp
     std::string stdStr = "World";
     QString str = QString::fromStdString(stdStr);
     ```

6. 字符串的分割和拼接：
   - 使用 `split()` 方法将字符串分割成一个字符串列表：
     ```cpp
     QString str = "Hello,World,OpenAI";
     QStringList list = str.split(",");  // 结果为 ["Hello", "World", "OpenAI"]
     ```
   - 使用 `join()` 方法将字符串列表拼接成一个字符串：
     ```cpp
     QStringList list = { "Hello", "World", "OpenAI" };
     QString str = list.join(",");  // 结果为 "Hello,World,OpenAI"
     ```

7. 字符串的大小写转换：
   - 将字符串转换为全小写字母：
     ```cpp
     QString str = "Hello World";
     QString lowerCaseStr = str.toLower();  // 结果为 "hello world"
     ```
   - 将字符串转换为全大写字母：
     ```cpp
     QString str = "Hello World";
     QString upperCaseStr = str.toUpper();  // 结果为 "HELLO WORLD"
     ```

8. 字符串的截取和修剪：
   - 使用 `left()` 方法获取字符串的左侧指定长度的子字符串：
     ```cpp
     QString str = "Hello World";
     QString leftStr = str.left(5);  // 结果为 "Hello"
     ```
   - 使用 `right()` 方法获取字符串的右侧指定长度的子字符串：
     ```cpp
     QString str = "Hello World";
     QString rightStr = str.right(5);  // 结果为 "World"
     ```
   - 使用 `trimmed()` 方法修剪字符串的首尾空白字符：
     ```cpp
     QString str = "  Hello World  ";
     QString trimmedStr = str.trimmed();  // 结果为 "Hello World"
     ```

9. 字符串的比较和判断：
   - 使用 `compare()` 方法比较两个字符串的大小关系：
     ```cpp
     QString str1 = "Hello";
     QString str2 = "World";
     int result = str1.compare(str2);  // 返回一个整数，表示比较结果
     ```
   - 使用 `startsWith()` 方法判断字符串是否以指定的子字符串开头：
     ```cpp
     QString str = "Hello World";
     if (str.startsWith("Hello")) {
         // 字符串以 "Hello" 开头
     }
     ```
   - 使用 `endsWith()` 方法判断字符串是否以指定的子字符串结尾：
     ```cpp
     QString str = "Hello World";
     if (str.endsWith("World")) {
         // 字符串以 "World" 结尾
     }
     ```

10. 字符串的格式化：
    - 使用 `arg()` 方法进行字符串格式化：
      ```cpp
      QString str = "Hello %1";
      QString formattedStr = str.arg("World");  // 结果为 "Hello World"
      ```

11. 字符串的编码和解码：
    - 将 QString 转换为字节数组（默认使用 UTF-8 编码）：
      ```cpp
      QString str = "Hello";
      QByteArray byteArray = str.toUtf8();
      ```
    - 将字节数组转换为 QString：
      ```cpp
      QByteArray byteArray = "Hello";
      QString str = QString::fromUtf8(byteArray);
      ```

## 8. 画图

### 画图设备

#### QImage 

#### QPixmap

#### QPicture

#### QBitmap

### 画笔

### 画刷

### 字体

## 9. 事件

### 9.1 事件处理器 (event)

### 9.2 事件分发器 ()

### 9.3 事件过滤器 (eventFilter)

```cpp
#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->label->installEventFilter(this);
}

bool Widget::eventFilter(QObject *object, QEvent *event)
{
    if (object == ui->label)
    {
        if (event->type() == QEvent::MouseMove)
        {
            return true;
        }
    }

    return QWidget::eventFilter(object, event);
}

```

## 10. 文件操作

Qt提供了丰富的文件操作类和函数，用于在应用程序中进行文件的读取、写入和管理。以下是一些常用的Qt文件操作相关的类和函数：

1. QFile类：QFile类提供了对文件的读取和写入功能。它可以打开、关闭、读取和写入文件内容，还可以查询文件的属性和状态。常用的成员函数包括`open()`、`close()`、`read()`、`write()`等。

2. QDir类：QDir类用于操作目录和文件路径。它可以列出目录中的文件和子目录，创建和删除目录，查询文件和目录的属性等。常用的成员函数包括`entryList()`、`mkdir()`、`remove()`等。

3. QFileInfo类：QFileInfo类提供了对文件和目录的元数据的访问。它可以查询文件的名称、路径、大小、权限等属性，还可以判断文件的类型和状态。常用的成员函数包括`fileName()`、`size()`、`isDir()`、`isReadable()`等。

4. QTextStream类：QTextStream类提供了文本文件的读取和写入功能。它可以读取和写入文本数据，并且支持文本编码的转换。常用的成员函数包括`readAll()`、`write()`、`setCodec()`等。

除了上述的基本文件操作类和函数外，Qt还提供了其他一些高级的文件操作功能，例如：

1. QTemporaryFile类：QTemporaryFile类用于创建临时文件，这些文件在使用后会自动被删除。

2. QDataStream类：QDataStream类提供了二进制文件的读取和写入功能，可以方便地读写各种数据类型。

3. QFileDevice类：QFileDevice类是QFile和QTemporaryFile的基类，它提供了更底层的文件访问功能，可以进行随机访问和文件锁定等操作。

上述是一些常用的Qt文件操作类和函数的介绍，你可以根据具体的需求选择合适的类和函数来进行文件的读写和管理操作。

### 读文件

### 写文件

### 文件流

#### 文本流

在Qt中，文本流是一种方便的方式来读取、写入和处理文本数据。Qt提供了一个名为QTextStream的类，用于处理文本数据的输入和输出。

QTextStream类可以与各种设备进行交互，如文件、字符串、网络套接字等。它提供了一系列的成员函数，用于读取和写入各种数据类型，并支持文本编码的转换。

下面是一些常用的QTextStream类的成员函数：

1. setDevice()：设置与QTextStream交互的设备，如QFile或QString。

2. readLine()：从文本流中读取一行文本数据。

3. readAll()：从文本流中读取所有的文本数据。

4. atEnd()：检查是否已到达文本流的末尾。

5. seek()：在文本流中移动到指定的位置。

6. reset()：将文本流的读写位置重置为初始位置。

7. write()：将文本数据写入文本流。

8. flush()：将文本流的缓冲区内容刷新到设备中。

使用QTextStream，你可以读取和写入各种数据类型，如字符串、整数、浮点数等。它提供了重载的<<和>>运算符，使得数据的读取和写入更加方便。

下面是一个示例，展示了如何使用QTextStream读取和写入文本文件：

```cpp
#include <QFile>
#include <QTextStream>

int main() {
    QFile file("example.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            // 处理每一行文本数据
        }
        file.close();
    }

    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << "Hello, World!" << endl;
        // 写入其他数据
        file.close();
    }
    
    return 0;
}
```

在上面的示例中，首先通过`QFile`打开文本文件，然后使用`QTextStream`读取和写入文件。通过`readLine()`函数逐行读取文件内容，并通过`<<`运算符将文本数据写入文件。最后记得关闭文件。

QTextStream提供了方便的方法来处理文本数据的输入和输出，使得操作文本流更加简单和灵活。你可以根据自己的需求使用QTextStream来读写文本数据。

#### 数据流

在Qt中，数据流（Data Stream）是一种用于序列化和反序列化数据的机制。Qt提供了两个主要的数据流类：QDataStream和QTextStream。

1. QDataStream：
QDataStream类用于处理二进制数据流。它提供了一组成员函数，可以方便地将各种数据类型（如整数、浮点数、字符串、自定义类等）写入到数据流中，也可以从数据流中读取这些数据类型。QDataStream可以与QIODevice派生类一起使用，如QFile、QTcpSocket等。

下面是一个使用QDataStream读写数据的示例：

```cpp
#include <QFile>
#include <QDataStream>

int main() {
    QFile file("example.dat");
    if (file.open(QIODevice::WriteOnly)) {
        QDataStream out(&file);
        out << 42; // 写入整数
        out << 3.14; // 写入浮点数
        out << "Hello, World!"; // 写入字符串
        
        file.close();
    }

    if (file.open(QIODevice::ReadOnly)) {
        QDataStream in(&file);
        int intValue;
        double doubleValue;
        QString stringValue;
        
        in >> intValue; // 读取整数
        in >> doubleValue; // 读取浮点数
        in >> stringValue; // 读取字符串
        
        file.close();
    }
    
    return 0;
}
```

在上述示例中，首先通过`QFile`打开二进制文件，然后使用`QDataStream`进行数据的写入和读取。通过`<<`和`>>`运算符可以方便地将数据写入和读取出来。

2. QTextStream：
QTextStream类用于处理文本数据流。它提供了一组成员函数，可以方便地将QString、QByteArray等文本数据类型写入到数据流中，也可以从数据流中读取这些文本数据类型。与QDataStream不同，QTextStream是基于文本的，可以进行文本编码的转换。

下面是一个使用QTextStream读写文本数据的示例： 

```cpp
#include <QFile>
#include <QTextStream>

int main() {
    QFile file("example.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << "Hello, World!" << endl;
        out.setRealNumberPrecision(2);
        out << 3.14159 << endl;
        
        file.close();
    }

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString line = in.readLine(); // 读取一行文本数据
        double value = in.readLine().toDouble(); // 读取下一行，并转换为浮点数
        
        file.close();
    }
    
    return 0;
}
```

在上述示例中，首先通过`QFile`打开文本文件，然后使用`QTextStream`进行数据的写入和读取。通过`<<`运算符可以将文本数据写入数据流中，通过`readLine()`函数可以逐行读取文本数据。

无论是QDataStream还是QTextStream，它们都提供了方便的方法来处理数据流，使得数据的序列化和反序列化更加简单和灵活。你可以根据需要选择合适的数据流类来处理数据。

## 11 TCP & UDP
