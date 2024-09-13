# 面试大合集

## 网络

### 1.1 网络分层

从底到上

物理层：比特流

==链路层==：封装成帧

==网络层==：==路由选择==

==传输层==：==建立可靠和不可靠的通信，建立端到端的通信；tcp传输控制协议可靠，udp不可靠==

会话层：维护会话

表示层：数据格式处理

应用层：==应用程序间的通信==

### 1.2 udp和tcp区别

udp：==无连接，尽最大可能交互，对应用程序传下来的报文不合并也不拆分，只添加udp首部==，轻量级协议，快，==无状态==，一对多，多对一；对网络通讯质量不高时用udp

tcp：==面向连接的，可靠交付，有流量控制，拥塞控制==，重量级协议；==只能一对一==

对网络通讯质量高时用tcp

### 1.3 tcp的三次握手

面向连接，所以要做好连接的准备

发送三个报文

客户端发送==**SYN   初始序号为x**==

服务端收到请求，如果==同意建立连接，发送确认报文==，发送==SYN  ACK=x+1==，同时选择一个初始序号y

客户端发送==确认序号y+1，再次确认==

**为什么不能是两次**：==必须确认客户端是否具备接收能力，防止服务端误打开==；

**为什么不能是四次**：节约资源

### 1.4 tcp的四次挥手

FIN报文，指定序列号，FIN_WAIT1

服务端ack   客户端FIN_WAIT2  服务端==CLOSE_WAIT==

==客户端中间有可能收到数据传输==

服务端发送FIN  指定序列号  

==客户端收到经过两次报文存活时间就释放了连接==

也就是==通知你关闭，你收到了==；然后你还有==一些数据没传输完==，你会==再发一个FIN==，客户端==收到等待两次报文存活时间即可==

### 1.5 http及与https的区别

超文本传输协议

### 1.6 session、cookie、token的区别

由于http是无状态的，也就是说每个客户端访问服务器资源时，服务器并不知道客户端是谁，所以需要==会话技术==识别客户端的状态。

cookie是存储在==客户端本地的==，**==安全性不好==**，相当于==会员卡==，服务器==返回cookie给客户端A，客户端A存储cookie==

session相当于==就医卡==和医院为每个人保留的==病例档案==，session是基于cookie的，如果==不设置cookie的持久化时间==，关闭客户端再次打开会取不到session的内容

单个cookie保存的数据有限

session的弊端：

- 服务器==资源占用比较大==，==session是存储在服务器的内存当中的==
- ==安全性比较低==，==基于cookie的==
- ==拓展性不强==，session是放在单节点中的

token的优势：

- 服务器资源==占用低==
- cpu计算时间换取了服务器的内存空间
- ==拓展性高==

## JAVA基础相关

### 2.1 怎么认识反射

在运行时获取类、构造类、运行方法等功能

这种动态获取信息、动态调用对象的功能称为java的反射机制

==原理：==

通常==jvm会将编译好的.class字节码加载到jvm内存中==，同时会==创建这个类的class对象到堆中==，jvm在创建类对象前，会先检查类是否加载，若加载好，则为其分配内存，然后进行初始化。==加载完一个类之后，堆内存中就产生了一个class对象，并且包含了这个类的完整结构信息，我们通过class对象看到类的结构，就好像一面镜子，我们称之为反射==

也就是说以前是先有类再有对象，现在是根据对象找到对象所属的类

==优点就是在运行时动态获取类的实例==

==反射破坏了封装机制==，通过反射可以获取并调用类的私有方法和字段

应用：动态代理、spring框架等

### 2.2 怎么认识泛型

java在1.5引入的泛型

泛型的本质就是**==参数化类型==**

就是允许在==<font color=red>定义类、接口时通过一个标识</font>表示类中某个属性的类型==或者是某个方法的返回值及参数类型

在没有泛型时，==任何类型都可以添加到集合中==，读出来的数据类型需要强转；

在集合中有泛型后，==只有指定类型才能添加到集合中，读取出来就比较安全==

泛型有三种定义方式：==泛型类、泛型接口、泛型方法==

### 2.3 怎么认识序列化和反序列化

序列化：==把对象转换为字节序列的过程==

只有实现了==Serializable==或者Externalizable接口的类的对象才能被序列化为字节序列

反序列化：==恢复为java对象的过程==

保证==对象传递的完整性和可传递性==，以便在网络上传输或者保存在本地文件中。

### 2.4 ArrayList和LinkedList有什么区别

ArrayList：底层是属组，o(1)   更适合随机查找，添加和删除比较慢

LinkedList:链表，更适合添加和删除

### 2.5 抽象类与接口的区别

==相同点，都不能实例化==

接口中的每一个方法都是抽象的

抽象类不是

抽象类可以包含构造器，但是接口不能

==只能继承一个抽象类，但能够实现多个接口==

### 2.6 String StringBuffer StringBuilder

String：适用于少量的字符串操作。

StringBuilder：适用于==单线程==下在==字符串缓冲区==进行大量操作，线程不安全

StringBuffer：适用于==多线程==下在==字符串缓冲区进行大量操作==，线程安全

### 2.7 final

- final 修饰的类叫最终类，该类不能被继承。
- final 修饰的方法==不能被重写==。
- ==final 修饰的变量叫常量，常量必须初始化，初始化之后值就不能被修改==。

### 2.8 八种基本数据类型

byte、boolean、char、==**short**==、int、float、long、double

### 2.9 动态代理

基于jdk的动态代理

复杂业务的动态扩展

==接口  实现类  代理类==

只要实现了==InvocationHandler的invoke方法==，即可实现动态代理

由于代理的是接口，访问修饰符是public，否则代理不了，这也是为什么Spring 的 @Transactional 注解只能作用于 public 方法上

日志  事务 全局性异常处理

cglib代理需要引入cglib依赖

```java
public class UserHandler implements InvocationHandler {

    private UserDao userDao;

    public UserHandler(UserDao userDao){
        this.userDao = userDao;
    }

    @Override
    public Object invoke(Object proxy, Method method, Object[] args) throws Throwable {
        saveUserStart();
        Object obj = method.invoke(userDao, args);
        saveUserDone();
        return obj;
    }

    public void saveUserStart(){
        System.out.println("---- 开始插入 ----");
    }

    public void saveUserDone(){
        System.out.println("---- 插入完成 ----");
    }


    public static void main(String[] args) {


            UserDao userDao = new UserDaoImpl();
            InvocationHandler handler = new UserHandler(userDao);

            ClassLoader loader = userDao.getClass().getClassLoader();
            Class<?>[] interfaces = userDao.getClass().getInterfaces();

        /**
         * 需要类的加载器  需要被代理的接口  需要代理类
         */
        UserDao proxy = (UserDao) Proxy.newProxyInstance(loader, interfaces, handler);
            proxy.saveUser();
        }

}
```

**Cglib动态代理**：利用ASM框架，对代理对象类生成的class文件加载进来，通过**修改其字节码生成子类来进行代理**

### 2.10 try catch finally

```java
public static int ls(int a,int b){
        a=1;
        b=1;
        try{
            // 如果finally前有return  会执行该return 并保存下来
            // 再执行finally  然后回到这个return
            // 所以如果finally中没有return，那么将会执行先前的return  而且值也是先前的
            // 此时返回的结果是2
            return a+b;
        }catch (RuntimeException e){
            return 2;
        }finally {
            a=3;
            b=3;
            // 这里既然有return了，先前尽管有return  也会被覆盖
            // 所以这里返回6
            return a+b;
        }
    }
```

### 2.11 integer89

包装类使用了缓存优化

Byte,Short,Integer,Long 这 4 种包装类默认创建了数值 ==[-128，127]==的相应类型的缓存数据，Character 创建了数值在 [0,127] 范围的缓存数据，Boolean 直接返回 True or False

### 2.12 零拷贝

==零拷贝==：就是计算机执行io操作时，cpu不需要将数据从==一个存储区域复制到另一个存储区域==，从而减少上下文切换和cpu拷贝时间，是一种io操作优化技术。

传统io操作：

read：

- 1. 切换到内核态
- - dma控制器从==磁盘==读取到==内核缓冲区==
- 2. 切换到用户态
- - cpu拷贝到==用户缓冲区==

write：

- 1. 切换到内核态

  - 用户缓冲区拷贝到socket缓冲区

- 2. 切换到用户态

  - soket缓冲区到网卡设备

零拷贝并不是没有拷贝数据，==而是减少用户态/内核态的切换次数以及CPU拷贝的次数==。零拷贝实现有多种方式，分别是

- ==**mmap+write**==
- - `mmap`利用虚拟内存，将==内核空间和用户空间的虚拟地址映射到同一个物理地址==，从而减少数据拷贝次数。`mmap`用了虚拟内存这个特点，它将内核中的读缓冲区与用户空间的缓冲区进行映射，所有的`IO`都在内核中完成。
- **sendfile**
- - `sendfile`表示在两个文件描述符之间传输数据，它是在==操作系统内核中操作的==，避免了数据从内核缓冲区和用户缓冲区之间的拷贝操作，因此可以使用它来实现零拷贝。

java中对mmap的支持

`Java NIO`有一个`MappedByteBuffer`的类，可以用来实现内存映射

`FileChannel`的`transferTo()/transferFrom()`，底层就是`sendfile()` 系统调用函数。==`Kafka` 这个开源项目就用到它，平时面试的时候，回答面试官为什么这么快，就可以提到零拷贝`sendfile`这个点。==

### 2.13 值传递 引用传递

String是没有提供改变自身方法的引用类型  ==如果传入String，实参不会改变==

==String的改变只会改变引用地址，所以和实参的地址不一样了== 所以==String类的实参不会变==

```java
public static void main(String[] args) {
    ParamTest pt = new ParamTest();
    String name = "Hollis";
    pt.pass(name);
    System.out.println("print in main , name is " + name);
}
 
public void pass(String name) {
    name = "hollischuang";
    System.out.println("print in pass , name is " + name);
}

// 结果是
// print in pass , name is hollischuang
// print in main , name is Hollis
```

但是如果==引用类型在被调用的方法中重新生成，即重新new==，那么==实参也不会被改变==

java中只有值传递，对于值类型，复制的是值，对于引用类型，复制的是地址而已

==实参是会有拷贝传给形参的，但或者是值或者是地址==

### 2.14 java的内部类

静态内部类，成员内部类，局部内部类，匿名内部类

==定义在哪，作用范围就在哪==

==外部类不能用static,private,protected,这些修饰符==

### 2.15 加与不加@override的区别

不加，多态时也会覆盖

但是如果子类定义的是重名，==参数列表不匹配==,则不会报错，但肯定覆盖不了

但是如果子类定义的是重名，==返回值不匹配==,则肯定会报错

### 2.16 static

记住static代码块加载时只执行一次

并不是==静态**块**最先初始化==,而是==静态**域**==

而静态域中包含==静态变量、静态块和静态方法==,其中需要初始化的是静态变量和静态块.而他们两个的初始化顺序是靠他们俩的位置决定的!

### 2.18 程序当中出现了一些异常，比如内存溢出，如何定位？

看看前端报几百，404地址错误、403权限、500后端问题

如果是后端问题，查看日志

jdk自带的==java visualvm，看dump信息==

配置==-XX:+HeapDumpOnOutOfMemoryError==

配置这玩意之后，oom的时候会自动jump的，到时候拿快照分析一波就好了

### 2.19 Java常用的集合有哪些

Java集合主要由Collection和Map派生出来的，Collection有三个子接口：List,Set,Queue

ArrayList的底层是数组，默认情况下新的容量会是原容量的1.5倍；

ArrayList与LinkedList的区别：

- 随机index访问的get和set方法，ArrayList的速度要优于LinkedList
- 新增和删除元素，LinkedList的速度要优于ArrayList

### 2.20 HashMap的实现原理

有一个默认的初始容量16

默认的加载因子0.75f

静态内部类Node，该静态内部类中有hash值，有key，有value，有下一个节点的指针；

map内有一个Node数组

put方法，==有一个hash函数，其hash值是hashcode前16位和后16位进行异或，减少了hash碰撞；==

该hash值与Node数组相与得到位置，如果该位置是空的就刚好可以放

如果存在hash冲突，且其==equals方法或者`==`返回true==，则**覆盖该节点**

否则放置该桶尾部

添加的过程中，如果==size大于阈值则发生扩容==，这个阈值是==负载因子*容量大小==

最好是在==初始化的时候指定容量大小==，避免==频繁扩容带来的性能上的消耗==

负载因子表示hash表填充程度，负载因子越大，意味着触发扩容的元素个数就越多，但是它的整体空间利用率会比较高，hash冲突的概率会增加；负载因子的值越小，内存浪费比较多，频繁扩容会带来性能上的消耗；

==0.75的来源与统计学的泊松分布有关系==

为了避免链表过长，==在链表长度大于8的情况下，链表长度达到8的可能性几乎为0==

### 2.21 HashMap为什么会造成死循环

Jdk1.7下多并发下扩容时会造成死循环，头插法造成的

## 三、JVM面试题

### 3.1 运行一个类时什么时候被加载

并没有进行强制约束，交给了虚拟机自己去自由实现。HotSpot虚拟机是按需加载，在需要用到该类的时候加载这个类

### 3.2 加载类的过程

加载:二进制字节流，转换为运行时数据结构

链接

- 验证：是否符合class文件
- 准备：==为静态变量分配内存并设置初始值==
- 解析：符号引用转为直接引用

初始化：==变量赋值操作，初始化方法==

### 3.3 类初始化的过程

静态代码块、类的初始化方法

一个子类要初始化需要先初始化父类；

一个类初始化就是执行 <clinit> 方法，<clinit>() 方法由静态类变量显示赋值代码和静态代码块组成；

### 3.4 什么是类加载器

在类加载阶段，通过类的==全限定名来获取二进制字节流==的动作叫类加载

==启动类加载器：==bootstrap classloader，C++实现的，jvm的一部分

其他类加载器：全部继承于java.lang.ClassLoader

- 扩展类加载器：java home\lib\ext目录
- 应用类加载器：应用程序类加载器是==ClassLoader类中的getSystem.ClassLoader()方法的返回值==
- 自定义加载器:  继承ClassLoader类

### 3.5 JVM中哪些是共享区，哪些可以作为gcroot

堆  方法区

==虚拟机栈中引用的对象==

==本地方法中引用的对象==

==静态变量（方法区）中引用的变量==

==synchronized引用的对象==

### 3.6 JVM调优常用

-Xms

-Xmx

### 3.7 Java虚拟机的组成部分有哪些？

虚拟机栈、本地方法栈、堆、程序计数器、方法区、运行时常量池

### 3.8 Java虚拟机是如何进行垃圾回收的？



## 四、mysql面试题

### 4.1 mysql事务的底层原理

innodb如何保持acid特性

从宏观方面上来讲，事务主要实现

- ==可靠性==
- - 即在数据库进行insert或者update操作时，数据库要保证抛异常或者crash时保证数据操作的前后一致性
  - 需要undolog和redolog

- ==并发==
- - 如果有多个请求，并且有其中一个是更新请求
  - 则需要对数据的==读写进行隔离==

A:atomic 原子性  ==undolog回滚日志来保证==

C：consistency 一致性  依靠业务来保障、==数据的完整性没有被破坏==，==数据库提供主键约束来保障==

I：Isolation；隔离性；RU  RC RR mvcc机制来==解决脏读和不可重复读==  Serializable

D：Durability;==一旦提交，是永久性的==，==redolog来保证==，先写日志后写磁盘

redolog不是随着事务的提交才写  而是事务开启就写入

binlog是事务提交

### 4.2 什么是死锁

争夺资源造成互相等待

行锁造成死锁

==间隙锁导致死锁，非唯一索引会锁住一段左开右闭区间==

### 4.3 mysql的主从复制原理

binlog

从库与主库建立连接

主库建立了一个binlog的dump线程  发送到从库  从库创建IO线程，讲binlog写到relay log

sql线程，relay log中读取内容  复制数据

### 4.4 mysql主从数据不一致的原因

binlog是statement，记录的是sql原文

应改为row

### 4.5 索引为什么使用b树，b树和b+树的区别

b树：

- 节点有序
- ==只适合随机查找==

b+树：

- 数据存储在叶子节点
- ==且各个叶子节点之间有指针==
- ==适合范围查找==

### 4.6 mysql如何分库分表

分库：垂直拆分、水平拆分

- ==垂直拆分==，按照业务进行拆分
- ==水平拆分==：数据库一、数据库二

分表：垂直拆分

- ==垂直拆分==：字段拆分；==单表数据量依旧很大==，维护简单，部分业务无法join；复杂事务处理
- ==水平拆分==：表一、表二；跨库事务

### 4.7 mysql的binlog和redolog的区别

### 4.8 常用的MySQL查询的优化方法

- 对查询进行优化，应尽量避免全表扫描，首先应考虑==在 where 及 order by==涉及的列上建立索引
- ==避免对字段值null进行判断==
- 尽量==避免==在 where 子句中==使用 or 来连接条件==
- ==in 和 not in 也要慎用，否则会导致全表扫描==
- 尽量==避免==在 where 子句中==对字段进行表达式操作==
- 尽量==避免函数操作==
- ==任何地方都不要使用 select * from t ，用具体的字段列表代替“*”，不要返回用不到的任何字段==
- 尽量==避免大事务操作==，提高系统并发能力

### 4.9 一些常用的sql语句

### 4.10 mysql 的explain



## 五、spring面试题

### 5.1 springmvc的原理

核心，一个==前端控制器==，dispatchServlet

1、找到**==处理器映射器==**，找到相应的==handler==，将解析后的url返回给前端控制器

2、找到**==HandlerAdapter处理器适配器==**

3、**处理器适配器**找到对应的==后端控制器==，即controller

4、controller返回**ModelAndView**

5、ModelAndView被前端控制器dispatchServlet传给==视图解析器==

6、==视图解析器返回视图==

7、dispatchServlet渲染视图，将数据填充到视图中

### 5.2 spring如何解决循环依赖问题

实例化 属性注入  初始化

两个没有创建的bean相互依赖，在bean创建时会出现循环依赖

==一级缓存==：可以解决==循环创建的死循环问题==，存放经历了完整生命周期的bean

==二级缓存==：存储早期bean，为了区分已经成熟的bean的bean

三级缓存：==解决循环依赖中的动态代理问题==，普通的bean是在初始化完成后创建循环代理

### 5.3 spring的生命周期

实例化

属性填充

初始化

销毁

### 5.4 spring事务传播行为的实现原理

一个线程只有一个事务，所以用threadlocal

### 5.5 spring的bean是否是线程安全的

默认单例，==如果不对bean的成员作查询以外的操作==，那么是线程安全的

多例，由于不存在线程共享的问题，不会存在安全问题

### 5.6 spring的事务传播机制

required，存在则加入，不存在则新建

nested：嵌套事务

### 5.7 @Controller和@Service注解可以互换吗

@Controller层是spring-mvc的注解，具有将请求进行转发，重定向的功能。

@Service层是业务逻辑层注解，这个注解只是标注该类处于业务逻辑层。

### 5.8 Spring aop的理解

面向切面编程

### 5.9 Spring IOC的加载流程



### 5.10 Spring声明式事务原理 



### 5.11 什么是Restful风格

网络应用中就是==资源定位和资源操作==的风格

资源：互联网所有的事务都可以被抽象为资源

资源操作都是统一接口的

### 5.12   byName和byType区别 

是spring自动装配的两种方式。

第一种根据参数名，通过配置文件bean标签的id进行匹配，autowire的属性被设置为byname；

第二种根据参数类型自动装配

### 5.13 @Resource和@Autowired的区别

@Autowired由spring提供，只按照byType注入

@Resource有两个重要的属性：由jdk提供，默认按照byName自动注入，name和type

## 六、Kafka面试题

### 6.1 zk的作用

注册broker：/brokers/ids

注册topic：/brokers/topics/{topic_name}

负载均衡

消费者组的关系

消费进度

消费者注册

### 6.2 什么叫ISR

副本同步队列，当ISR中的followe完成数据同步后会发送ack，如果长时间没有同步，则会被踢出

### 6.3 什么叫HW、LEO

LEO:副本的最后一个offset

HW：消费者能够见到的最小的offset

### 6.4 kafka的rebalance机制

消费者组==成员==发生了变化

订阅的==主题==发生了变化

==分区数发生了变化==

### 6.5 kafka如何避免消息重复消费

重复消费的场景：

- ==自动提交消费位移：==
- - 自动提交位移是定期提交的，默认是5s
  - 如果还没提交offset，consumer挂掉，则从上一批offset会重新消费
- 再均衡机制：
- - 会导致offset提交失败

解决方案：

- ==手动提交offset==
- ==开启消息幂等性==
- 将消息md5保存到==redis中，处理消息前检查redis==

### 6.6 如何避免消息丢失

**提交了offset，但是没消费**，消费者挂了之后，读取的是最新的offset，会丢失offset

ack=0，broker还没写入磁盘就返回ack，当broker故障，就会丢失消息

ack=1，leader落盘后就返回ack，leader挂了也会丢失消息  

手动提交

生产者端提供了同步发送消息的方法

异步回调函数

### 6.7 kafka为啥内存飙升



## 七、RabbitMQ面试题

### 7.1 什么叫AMQP协议

### 7.2 如何保证mq的消息发送和接收

发送方确认机制：

- channel设置为confirm模式，每条消息分配一个唯一的id
- 投递成功，返回ack给生产者，回调ConfirmCallback接口
- 消息丢失，发送nack，回调ReturnCallback接口
- 异步触发

接收方确认：

### 7.3 mq的四种模型及其区别

直连模式

work模式：==**让多个消费者绑定到一个队列，共同消费队列中的消息**==。队列中的消息一旦消费，就会消失，任务是不会被重复执行的。

广播模式：==每个消费者会都绑定各自的一个队列==，每个队列都需要绑定交换机

订阅模式：

### 7.4 rabbitmq的发布确认机制

https://note.oddfar.com/pages/c94906/#%E5%8F%91%E5%B8%83%E7%A1%AE%E8%AE%A4-springboot-%E7%89%88%E6%9C%AC

ConfirmCallback:保证消息生产者==确认消息是否能够到达交换机==

ReturnCallback：由于交换机是和队列绑定的，所以==当交换机没有把消息发送到队列中时==，根据returnCallback的选择，是否返回消息生产者

向生产方反馈

### 7.5 rabbitmq的交换机

### 7.6 rabbitmq的过期时间ttl

### 7.6 rabbitmq的死信队列

死信队列：保存没有被成功消费的死信的队列叫做死信队列

### 7.7 rabbitmq中的延迟队列

### 7.8 如何保证rabbitmq的幂等性

### 7.9 rabbitmq的事务机制

**多个消费者rabbitmq不保证消息的顺序  消息匹配**  

**队列   吞吐量受到限制**

延时队列  死信队列  然后一个消费者去监听死信队列。当消息超时了，监听死信队列的消费者就收到消息了。

kafka需要开发延时队列  中转消息的消费者  每秒几十万条

kafka 数据统计不要求十分精确的场景下使用kafka

RabbitMQ 呢，它由于会在消息出问题或者消费错误的时候，可以重新入队或者移动消息到死信队列，继续消费后面的，会省心很多

rq每秒几万条

必须列出业务的重要几个特点

深入到消息队列的细节中去比较







### 7.4 什么叫rabbit中的虚拟机

生产者保证百分百投递

消费者实现消费幂等性



## 八、设计模式

### 8.1 观察者模式



## 九、排序算法



## 十、redis

### 10.1 redis分布式锁的原理

### 10.2 redis底层数据结构

简单动态字符串、

双向链表、压缩列表、哈希表、跳表、整数数组

### 10.3 redis为什么这么快





## 十一、多线程

### 11.1 项目中如何使用线程池

## 十二、项目





记得画程序的框架图

### 12.1 拦截器

看看PassportInterceptor的作用



### 12.2 切面

### 12.3 RuntimeException为什么没有侵入性

### 12.4 跨域问题

### 12.5 如何自定义异常

### 12.6 @ControllerAdvice

### 12.7 一个BaseController会做什么

### 12.8 为什么继承mapper

### 12.9 org.n3r.idworker

### 12.10 脱敏工具

### 12.11 粉丝画像怎么做



## 十三、 sql

### 13.1 返回员工大于老板工资的员工

==自连接==或者==子查询==

<img src="/Users/dexlace/private-github-repository/learning-notes/自问自答/final.assets/image-20221106014053829.png" alt="image-20221106014053829" style="zoom:50%;" />

```sql
select a.name as Employee from Employee a,Employee b
      where a.managerId=b.id  and a.salary>b.salary;
```

### 13.2 having

where作用在聚合前，也就是group by前，having用在聚合后，==用于聚合后筛选==

<img src="/Users/dexlace/private-github-repository/learning-notes/自问自答/final.assets/image-20221106025541409.png" alt="image-20221106025541409" style="zoom: 50%;" />

```SQL
select  Email from Person group by Email having count(Email)>1
```

### 13.3 查找订单表中没有数据的用户

<img src="/Users/dexlace/private-github-repository/learning-notes/自问自答/final.assets/image-20221106030741769.png" alt="image-20221106030741769" style="zoom:33%;" />

```sql

SELECT Name as Customers from Customers where Id not in

(SELECT CustomerId as cd from Orders group by CustomerId)
```

### 13.4 第二高的薪水

小于最高薪的最大值就是第二高薪水

```sql
select max(Salary) SecondHighestSalary 
from Employee
where Salary < (select max(Salary) from Employee)
```

### 13.5 部门工资最高的员工

先查询部门最高的工资，要查出部门、工资

```sql
select departmentId, max(salary) from department group by departmentId
```

再用一个in

```sql
select d.departmentId,d.salary from department d where 
  (d.departmentId,d.salary) in (select departmentId, max(salary) from department group by departmentId)
```

### 13.6 分数排名与rank函数的使用

<img src="/Users/dexlace/private-github-repository/learning-notes/自问自答/final.assets/image-20221106233403526.png" alt="image-20221106233403526" style="zoom: 33%;" />

```sql
# Write your MySQL query statement below
select score, dense_rank() over (order by score desc) as 'rank'  #这个rank之所以要加引号，因为rank本身是个函数，直接写rank会报错
from scores;
```

### 13.7 部门工资前三高的员工

<img src="/Users/dexlace/private-github-repository/learning-notes/自问自答/final.assets/image-20221107000433748.png" alt="image-20221107000433748" style="zoom:33%;" />

### 13.8 按日期分组销售产品

<img src="/Users/dexlace/private-github-repository/learning-notes/自问自答/final.assets/image-20221107001611164.png" alt="image-20221107001611164" style="zoom:33%;" />

```sql
# Write your MySQL query statement below
select t.sell_date,  count(DISTINCT t.product) as num_sold,


(GROUP_CONCAT(DISTINCT t.product order by t.product)) as products 


from Activities t  group by t.sell_date
```

<img src="/Users/dexlace/private-github-repository/learning-notes/自问自答/final.assets/image-20221107001801217.png" alt="image-20221107001801217" style="zoom:33%;" />

### 13.9 上升的温度-交叉连接

<img src="/Users/dexlace/private-github-repository/learning-notes/自问自答/final.assets/image-20221107002313542.png" alt="image-20221107002313542" style="zoom:33%;" />

```sql
select a.ID, a.date
from weather as a cross join weather as b 
     on datediff(a.date, b.date) = 1
where a.temp > b.temp;
```

<img src="/Users/dexlace/private-github-repository/learning-notes/自问自答/final.assets/image-20221107002717817.png" alt="image-20221107002717817" style="zoom:33%;" />



## 十四、面经

### 14.1 新国都面经

0、自我介绍

1、Java常用的集合有哪些？

2、ArrayList和linkedlist的区别和优缺点？

3、HashMap的实现原理

4、Java虚拟机的组成部分有哪些？

5、Java虚拟机是如何进行垃圾回收的？

6、Java虚拟机如何确定这个对象需要被回收？

7、程序当中出现了一些异常，比如内存溢出，如何定位？（答得不好）

8、springmvc处理请求的机制是什么？（不知道）

9、spring的IOC和AOP的基本原理

10、数据库的事务有哪些特性？分别解释一下

11、事务的隔离级别？MySQL的默认隔离级别？

12、常用的MySQL查询的优化方法

13、手写实现线程安全的单例模式

14、有哪些项目印象比较深刻，说一下业务流程和主要用到的技术（说了在阿里独自owner的一个项目，面试官没有追问，表情也很茫然，可能没怎么仔细听）

15、在阿里实习期间有哪些收获、怎么看待加班、空闲期间怎么安排时间、如何去接手一个需求

16、反问



作者：快乐的牛牛最喜欢春天
链接：https://www.nowcoder.com/discuss/1075046
来源：牛客网



自我介绍 

 Java中的集合有哪些
 ArrayList和LinkedList区别
 JVM内存区域
 对象从创建到销毁过程
 什么时候引起full gc，有什么危害
 sql查询优化
 事物的四大特性

  事物如何保证原子性 

  事物隔离级别 

  分布式事务 

  @Transactional 如何指定隔离级别 

  Spring中IOC和AOP的理解 

  如何进行依赖注入，byName和byType区别 

 说一个自己熟悉的项目，讲讲收获（实习或简历上的项目）
 手写单例模式

 反问：
 （1）技术栈：springcloud+mq+vue等目前比较新的技术。
 （2）部门负责业务：支付相关业务，后端
 （3）什么时候有反馈：不确定，等用人部门反馈
 （4）大概几面：一般一轮技术+一轮hr



作者：李在赣神魔捏
链接：https://www.nowcoder.com/discuss/1079943
来源：牛客网



\1. Java集合类：ArrayList，LinkedList，HashMap，HashTable，ConcurrentHashMap 

  \2. SpringIOC，AOP源码 

  \3. Spring声明式事务怎么工作的 

  \4. @Transactional的使用规则，具体的属性值如何设置 

  \5. 动态代理，以及两种动态代理的适用场景 

  \6. 原生JDBC过程 

  \7. JVM：一个java文件怎么执行的?如果频繁发生FullGC，排查方案有哪些 

  \8. GC算法，垃圾回收器 

  \9. 数据库特性：ACID，具体每一个特性如何保证? 

  \10. 查询语句的优化方法有哪些 

  \11. 索引的底层结构，为什么使用索引可以加快查询速度，B+树相比于其他数据结构有什么优点 

  \12. 建立索引的一般准则有哪些 

  \13. 项目中使用的技术栈有哪些?引入这些技术栈分别解决了什么问题 

  \14. SpringCloud Nacos服务注册表结构? 微服务一上线如何在Nacos中进行注册的? Nacos的通知机制底层如何实现的？



作者：科科大爆炸
链接：https://www.nowcoder.com/discuss/810522
来源：牛客网



1.SpringBoot启动流程 （提醒@Annotation那些注解，我说就是根据注解里面那些嵌套注解启动的，具体忘了） 

  2.final finally finalize (finally 和 return返回先后答错了，其余应该没错) 

  3.SpringBoot优点（简化Xml，微服务等等。。） 

  4.SpringBoot和SpringCloud关系（共生，Cloud依托Boot，不知道对不对。。） 

  5.oracle jdbc的到执行语句的过程（不知道。。 简历没写oracle不知道为啥要问） 

  6.jvm内存分为啥 都是干啥的（堆栈方法区那些八股文） 

  7.final类有啥用（安全，效率，不可被继承，顺着说到了String为啥用final，以及常量池缓存云云。。） 

  8.常用注解 

  9.component和configuration 啥区别，能替代吗 （答的比较乱） 

  10.设计模式有哪些 （单例，工厂，策略。。） 

  11.设计模式应用场景 （巴拉巴拉） 

  12.String s = new String("123") 在jvm里怎么分配的 （堆，常量池等） 

  13.用英语来一段对话 

  最后问了下我职业规划相关的，薪酬和什么时候能去工作 （感觉就是客套话。。）







































作者：迷茫德劳伦
链接：https://www.nowcoder.com/discuss/433384
来源：牛客网



   3、Classloader作用； 

​	4、SpringMVC原理； 

​	5、Servlet生命周期； 

​	6、https原理； 

​	7、tcp/ip原理； 

​	8、Redis、IOC、AOP；  

​	9、RunTimeException VS 其他Exception； 

​	10、thread join的问题； 

​	11、ThreadLocal； 

​	12、事务隔离级别； 

​	13、是否有做过分布式架构设计？ 

​	14、POST VS GET； 

​	15、行锁；





作者：啥也不会的后端
链接：https://www.nowcoder.com/discuss/1072775
来源：牛客网



1.自我介绍 

  2.es在你的项目里面怎么用的，介绍一下 

  3.es的分页搜索怎么做？说一下查询语句？比如我想在每一页都取前1000行。 

  4.es分页优化？ 

  es我是真不会啊。。真后悔简历写了了解es 

  5.MySQL查询执行过程 

  6.Spring事务管理 

  7.有多个线程，需要线程一个一个执行完之后才能做下一步的动作，怎么实现？ 

  8.有一个定时任务，执行时间非常长，你怎么排查并进行优化？ 

  9.最后一个问题，你怎么看待"卷"这个词？





作者：一个彩鸡
链接：https://www.nowcoder.com/discuss/1008994
来源：牛客网



\1. 了解Java线程池的参数吗？ 

  \2. 了解进程线程协程？ 

  \3. CAP及其原理 

  \4. 分布式锁是怎么实现的？Redis和Zk有什么区别？ 

  \5. 了解幂等性吗？ 

  \6. Java内存模型有了解吗？ 

  \7. Java中的锁分哪几类？ 

  \8. Kafka怎么保证消费有序？ 

  \9. 了解Raft吗？ 

  \10. CAS原理？怎么解决ABA? 

  \11. 单例模式懒汉和饿汉有什么区别？ 

  \12. 讲一讲ZAB算法





作者：枫煦h
链接：https://www.nowcoder.com/discuss/996979
来源：牛客网



3.消息中间，你了解吗？具体的原理是啥？介绍一下，RocketMQ说一说 

  4.什么时候会用到消息中间件呢？使用场景是啥 

  5.消息队列数据积压的情况该怎么办？怎么解决的。消息丢失情况咋办、幂等性怎么保证 

  6.spring中常用注解？AOP的一些注解呢？ 

  7.@Controller和@Service注解可以互换吗？为什么不能呢？ 

  8.spring bean的注册有哪些方式？ 

  9.spring boot怎么实现AOP 

  10.介绍一下IOC，有什么优势 

  11.spring context和bean factory的关系是什么？ 

  12.多线程，怎么创建一个线程，怎么获取一个线程的名字。有哪些线程池？ 

  13.ThreadLocal介绍一下，它的key是什么 

  14.redis为什么是单线程？redis单线程的优势 

  15.缓存血崩介绍一下？怎么避免 

  16.职业规划？学习路线？





作者：枫煦h
链接：https://www.nowcoder.com/discuss/991202
来源：牛客网



1.讲讲你这个简历里面的秒杀项目吧？ 

  2.怎么解决的超卖问题 

  3.redis在这里的作用是什么，少卖问题怎么产生的？ 

  4.redis的数据结构你了解吗？他的数据结构的底层实现原理讲一讲 

  5.redis集群有了解吗？主从了解吗？讲讲redis的持久化的方式 

  6.spring讲讲两个特性，你的理解是什么样的 

  7.spring mvc是怎么从url解析到具体的方法的？你了解吗 

  8.spring AOP类和接口的区别（我不太会，忘记是不是这么问的了） 

  9.spring bean的生命周期 

  10.mysql事务的特性？mysql四种隔离机制？各自的问题？怎么解决的脏读幻读 

  11.java的类和抽象类的区别？ 

  12.java == 和 equals的区别 

  13.linkedlist和arraylist的区别 

  14.jvm有哪些区，各自什么作用 

  15.jvm有哪些垃圾回收算法 

  16.限流的算法有哪些？负载均衡的算法有哪些？ 

17.spring中循环依赖问题怎么解决





## 十五、原理

### 15.1 为什么需要分布式锁

跨进程跨机器节点的互斥锁

单机锁：单进程多线程

分布式锁：多进程多机器节点，排他性、可重入性

setnx expire

redission 底层通过lua脚本执行redis的指令   保证加锁和锁失效的原子性

zookeeper获取序号，临时有序节点，序号最小就是获取到锁了，否则获取上一个节点并监听之

### 15.2 分布式锁的实现方式

### 15.3 分布式锁如何选型

### 15.4 CAP理论是什么

C:一致性，数据在==多个副本中保持的节点是一致的==

A:可用性，系统对外提供服务必须一直处于可用状态，在任何故障下，客户端都能合理的获得服务端非错误性的响应

P：分区容错性

### 15.5 BAS理论是什么

### 15.6 2PC（2 Phase Commit）二阶段提交

两阶段提交的思路是：

- ==参与者==将操作成败通知==协调者==，再由协调者根据参与者的==反馈情况决定参与者是否需要提交==
- **准备阶段：**
- - ==事务协调者==给每个参与者发送prepare消息，每个参与者==要么执行返回失败==，要么==在本地执行事务（只写redolog和undolog）==，但是不提交

- **提交阶段：**
- - 如果协调者收到了==参与者的失败或者超时消息，直接给每个参与者发送回滚消息==

**两阶段提交的缺点：**

- **==同步阻塞问题==**
- - ==参与者占用公共资源时==，其他第三方节点访问公共资源不得不处于阻塞状态

- ==单点故障==：
- - 一旦协调者发生故障，参与者会一直阻塞下去。
- 数据不一致的问题：
- - 提交阶段如果有部分提交失败

### 15.7 3PC 三阶段提交





### 15.4 分布式事务的解决方案

#### 15.4.1 TCC

tcc：try、confirm、cancel

try：对各个系统资源进行锁定

confirm：==各个服务之间进行实际的操作==

cancel：补偿，即回滚操作

除非你是真的一致性要求太高，是你系统中核心之核心的场景，比如常见的就是资金类的场景，那你可以用TCC方案了，自己编写大量的业务逻辑，自己判断一个事务中的各个环节是否ok，不ok就执行补偿/回滚代码

#### 15.4.2 



