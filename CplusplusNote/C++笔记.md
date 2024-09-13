# C++笔记

## 1、关于继承

### 1.1 关于访问权限

```c++
class 派生类 : 继承方式 基类
```

- 1. 继承后，各个成员变量到派生类的权限只能==缩紧或者不变==，注意对的是在==子类中缩紧==
- - 无论继承方式如何，父类的==private成员==都不能被子类==直接访问==
- - 无论继承方式如何，子类的==成员函数==都能访问父类的==public、protected成员==
- - 对于子类的对象，==父类的public成员==才能被对象==直接访问==

- 2. 理清一下public、protected、private在==类中的权限==
- - public：可以通过==对象.成员访问==
  - protected:==本类和子类==都能通过==public成员函数访问==
  - private：只能通过==类内的成员函数访问==

### 1.2 关于继承后的构造函数和析构函数

#### 1.2.1 简单派生类构造函数的定义

- 直接在派生类类内定义

```c++
派生类构造函数名（总参数列表）:基类名（参数列表）
{
    派生类中新增成员变量初始化语句
}
// 比如
class Clock:public Time
{
public:
	Clock(int h,int mi,int s,int y,int m,int d):Time(y,m,d)
	{
		hour = h;
		min = mi;
		sec = s;
		cout << "子类Clock构造函数被调用" << endl;
	}
// ....
protected:
	int hour;
	int min;
	int sec;
};
```

- 在派生类类内声明，==但不声明基类参数列表==，在类外定义

```c++
class Clock:public Time
{
public:
	Clock(int h,int mi,int s,int y,int m,int d);
// ....
protected:
	int hour;
	int min;
	int sec;
};

Clock::Clock(int h,int mi,int s,int y,int m,int d):Time(y,m,d)
{
    hour = h;
    min = mi;
    sec = s;
    cout << "子类Clock构造函数被调用" << endl;
}
```

#### 1.2.2 存在类对象的派生类的构造函数定义





## 2、关于命名空间

## 3、关于多态

## 4、生疏关键字详解

## 5、关于结构体

## 6、关于操作符重载

## 7、关于STL

