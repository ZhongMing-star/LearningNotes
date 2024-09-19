# 1. 类与函数

## 1. 函数传参

- 按地址传参(可变对象传参)
- 按值传参 （不可变对象传参）

```
# 可变对象	list, Dictionary, Set, Bytearray, 
# 不可变对象	int, string, float, tuple, 可变对象之外的就是不可变对象
```

```python
dict_data = {
    'q' : ord('q'),
    'k' : ord('k'),
    'v' : ord('v'),
}

def changeValue(dict_data):
    for key in dict_data.keys():
        dict_data[key] = ord(key.upper())

print(dict_data) # {'q': 113, 'k': 107, 'v': 118}

changeValue(dict_data)
print(dict_data) # {'q': 81, 'k': 75, 'v': 86}
```

## 2. 元类

## 3 静态方法与函数成员方法 @staticmethod和@classmethod

类内的方法划分为：

- 实例方法: 只有实例化之后才能访问的方法，可以访问类内的属性与方法
- 静态方法：基本上与类无关，不能访问内类的属性与方法
- 类方法：无需实例化就能方法内类的方法，可以访问类内的属性与方法，但是不能访问实力的属性与方法
- 特殊方法（"__"开头的方法）

## 4. 类变量与实例变量

