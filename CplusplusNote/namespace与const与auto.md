# namespace与const与auto

## 一、namespace

用namespace关键字来定义一个命名空间，后紧跟空间名，大括号是本空间的代码块。空间内全局变量、函数资源共享。

### 1.1 定义

```c++
namespace nameA{//名字空间的定义 
	int x;
	void func(){
	cout<<"nameA"<<endl;
	}
}
namespace nameB{
	int x;
	void func(){
	cout<<"nameB"<<endl;
	}
} 
```

### 1.2 使用

- 方法一：使用域作用符

```c++
nameA::func();
```

- 方法二：用using关键字对空间内的元素进行声明，这种声明在代码块内有效。using关键字有点类似于include关键字

```c++
using namespace nameA::func;  // 单独声明命名空间中的func函数
func();
using namespace nameB::x;  

// 将整个命名空间进行声明
using namespace nameA;
// 直接使用就好
func();
```



