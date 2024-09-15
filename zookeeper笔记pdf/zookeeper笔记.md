# zookeeper-分布式协调者

## 1、zookeeper的选举机制

1. ==半数机制：集群中半数以上机器存活，集群可用。所以zookeeper适合装在<font color=red>奇数台机器上</font>==
2. Zookeeper虽然在配置文件中并没有指定master和slave。但是，zookeeper工作时，是有一个节点为leader，其他则为follower，Leader是通过内部的选举机制临时产生的。

>  以一个简单的例子来说明整个选举的过程。

假设有五台服务器组成的zookeeper集群，它们的id从1-5，同时它们都是最新启动的，也就是没有历史数据，在存放数据量这一点上，都是一样的。假设这些服务器依序启动，来看看会发生什么。

<img src="zookeeper%E7%AC%94%E8%AE%B0.assets/image-20210228095434812.png" alt="image-20210228095434812" style="zoom:80%;" />

（1）==服务器1启动==，此时只有它一台服务器启动了，它发出去的信息没有任何响应，所以它的选举状态==一直是LOOKING状态==。

（2）==服务器2启动==，它与最开始启动的服务器1进行通信，互相交换自己的选举结果，由于两者都没有历史数据，所以id值较大的服务器2胜出，但是由于==没有达到超过半数以上==的服务器都同意选举它(这个例子中的半数以上是3)，所以==服务器1、2还是继续保持LOOKING状态==。

（3）==服务器3启动==，根据前面的理论分析，==服务器3成为服务器1、2、3中的老大==，而与上面不同的是，此时有三台服务器选举了它，所以==它成为了这次选举的leader==。

（4）==服务器4启动==，根据前面的分析，理论上服务器4应该是服务器1、2、3、4中最大的，但是==由于前面已经有半数以上的服务器选举了服务器3==，所以它只能接收当小弟的命了。

（5）==服务器5启动，同4一样当小弟==。

### 1.1 首先比较什么

> 谁的数据比较新，即比较==更新的日志zxid的序号==，==谁的大谁当老大==，但是==跟启动顺序有很大的关系==
>
> 比如三台zookeeper服务器，前两台比较zxid比较小的已经选出了老大，你最后启动也得不到老大的位置

### 1.2 然后比较什么

>当然是==myid==，谁的myid大，就沟通最后投给谁，==当前情况下==就投给谁

### 1.3 实时的老大如何成为最终的老大

> 选票过半

## 2、zookeeper的节点类型

1. Znode有两种类型：

>  ==短暂（ephemeral）==：客户端和服务器端断开连接后，创建的节点自动删除
>
> ==持久（persistent）==：客户端和服务器端断开连接后，创建的节点不删除

2. Znode有四种形式的目录节点（默认是persistent ）

> ==持久化目录节点（PERSISTENT）==

​    客户端与zookeeper断开连接后，该节点依旧存在,直接的==create命令==

> ==持久化顺序编号目录节点（PERSISTENT_SEQUENTIAL）==

​    客户端与zookeeper断开连接后，该节点依旧存在，只是Zookeeper给该节点名称进行顺序编号，直接的==create -s命令==

> ==临时目录节点（EPHEMERAL）==

客户端与zookeeper断开连接后，该节点被删除，==create -e命令==

> ==临时顺序编号目录节点（EPHEMERAL_SEQUENTIAL）==

客户端与zookeeper断开连接后，该节点被删除，只是Zookeeper给该节点名称进行顺序编号，==create -e -s命令==

## 3、zookeeper监听器原理

> 其实很简单，就是zookeeper客户端开了两个线程，==一个负责监听==，==一个负责通信==，==通信的线程==传递要监听的事件到zookeeper服务器去注册，==监听的事件有变化则发给监听线程去处理==

<img src="zookeeper%E7%AC%94%E8%AE%B0.assets/image-20210228101725427.png" alt="image-20210228101725427" style="zoom:80%;" />

>  ==监听原理详解：==

1）首先要有一个main()线程

2）在main线程中创建Zookeeper客户端，这时就会创建两个线程，==一个负责网络连接通信（connet），一个负责监听（listener）==。

3）通过==connect线程==将注册的监听事件==发送给Zookeeper==。

4）在Zookeeper的注册监听器列表中将注册的监听事件添加到列表中。

5）Zookeeper监听到有==数据或路径变化==，就会将这个==消息发送给listener线程==。

6）listener线程内部调用了==process（）方法==。

> 常见的监听

1. ==监听节点数据的变化：==

> get path [watch]

2. ==监听子节点增减的变化==

> ls path [watch]

## 4、写数据流程

![image-20210228102228257](zookeeper%E7%AC%94%E8%AE%B0.assets/image-20210228102228257.png)

其实也很简单，就是==客户端告诉话事人（<font color=red>可能被转达到话事人，不是直接找到的话事人</font>），话事人通知小弟干活，半数以上人干好了，通知客户端ok==

## 5、打打基础

### 5.1 启动命令

```bash
# 在前台运行 
bin/zkServer.sh start-foreground /root/software_run/zookeeper3.4.10_2811/conf/zoo.cfg
# 后台运行
bin/zkServer.sh start
# 查看状态
bin/zkServer.sh status
# 客户端连接命令
bin/zkCli.sh -server 127.0.0.1:2181
# 退出客户端命令
quit
# 连接集群
bin/zkCli.sh -server 192.168.1.101:2181,192.168.1.102:2181,192.168.1.103:2181
```

### 5.2 基础节点操作

#### 5.2.1 新增节点

```bash
create [-s] [-e] /节点 data # 其中-s为有序节点  -e为临时节点  不加其他参数则默认为持久化节点但没有自增序号
```

##### 5.2.1.1 持久化和临时节点

- 创建持久化节点

  ```bash
  create /node1 "nihao"
  ```

- 创建临时节点

  ```bash
  create  -e /node "nihao"
  ```

##### 5.2.1.2 有序节点

- 创建有序持久化节点

  ```bash
  create -s /node2 "nihao"
  ```

- 创建有序临时节点

  ``` bash
  create -e -s /node3 "nihao"
  ```

#### 5.2.2 查看节点

##### 5.2.2.1 查看节点

- 查看节点

  ```bash
  get path
  ```

节点各个属性如下表。其中一个重要的概念是 Zxid(ZooKeeper Transaction Id)，ZooKeeper 节点的每一次更改都具有唯一的 Zxid，如果 Zxid1 小于 Zxid2，则 Zxid1 的更改发生在 Zxid2 更改之前。

| 状态属性       | 说明                                                        |
| -------------- | ----------------------------------------------------------- |
| cZxid          | 数据节点创建时的事务 ID                                     |
| ctime          | 数据节点创建时的时间                                        |
| mZxid          | 数据节点最后一次更新时的事务ID                              |
| mtime          | 数据节点最后一次更新时间                                    |
| pZxid          | 数据节点的子节点最后一次被修改时的事务 ID                   |
| cversion       | 子节点的更改次数                                            |
| dataVersion    | 节点数据的更改次数                                          |
| aclVersion     | 节点的 ACL 的更改次数                                       |
| ephemeralOwner | 如果节点是临时节点，则表示创建该节点的会话的                |
| dataLength     | SessionID；如果节点是持久节点，则该属性值为 0数据内容的长度 |
| numChildren    | 数据节点当前的子节点个数                                    |

##### 5.2.2.2 查看节点状态

```bash
stat /node #可以使用 stat 命令查看节点状态，它的返回值和 get 命令类似，但不会返回 节点数据
```

##### 5.2.2.3 查看节点列表

```bash
ls path #查看指定路径下的所有节点
ls2 path #查看指定路径下的所有节点，还可以查看当前节点的信息
```

#### 5.2.3 更新节点

##### 5.2.3.1 不根据版本号更新

```bash
set /node "data" # 直接更新
```

#####  5.2.3.2 根据版本号更新

```bash
set /node "data"  version # 根据版本号更新
```

#### 5.2.4 删除节点

##### 5.2.4.1 不根据版本号删除

```bash
delete /node
```

##### 5.2.4.2 根据版本号删除

```bash
delete /node version
```

##### 5.2.4.3 递归删除某节点及其后代节点

```bash
rmr /node
```

### 5.3 监听器

#### 5.3.1  一次性监听本节点

``` bash
get path watch # 使用 get path [watch] 注册的监听器能够在节点内容发生改变的时候，向客 户端发出通知。需要注意的是 zookeeper 的触发器是一次性的 (One-time trigger)，即 触发一次后就会立即失效。
[zk: localhost:2181(CONNECTED) 4] get /hadoop watch 
[zk: localhost:2181(CONNECTED) 5] set /hadoop 45678 
WATCHER:: WatchedEvent state:SyncConnected type:NodeDataChanged path:/hadoop #节点 值改变
```

#### 5.3.2  非一次性监听本节点

```bash
stat path watch  #注册的监听器能够在节点状态发生改变的时候，向客 户端发出通知
```

#### 5.3.3 监听子节点的增删

```bash
ls path watch
或
ls2 path watch #注册的监听器能够监听该节点下 所有子节点的增加和删除操作。
```

### 5.4 权限控制

zookeeper 类似文件系统，client 可以创建节点、更新节点、删除节点，那么 如何做到节点的权限的控制呢？zookeeper的access control list 访问控制列表可以做到这一点

acl 权限控制，使用==scheme：id：permission==来标识，主要涵盖 3 个方面： 

- ==权限模式（scheme）==：授权的策略 

- ==授权对象（id）==：授权的对象 

- ==权限（permission）==：授予的权限 

其特性如下： 

zooKeeper的权限控制是==基于每个znode节点的，需要对每个节点设置权限==

每个znode==支持设置多种权限控制方案和多个权限==

子节点==不会继承父节点的权限，客户端无权访问某节点，但可能可以访问它的子节点==

 ```bash
 set  /node scheme:id:permission
 ```

#### 5.4.1 权限模式scheme

| 方案   | 描述                                                 |
| ------ | ---------------------------------------------------- |
| world  | 只有一个用户：anyone，代表登录zokeeper所有人（默认） |
| ip     | 对客户端使用IP地址认证                               |
| auth   | 使用已添加认证的用户认证                             |
| digest | 使用“用户名:密码”方式认证                            |

#### 5.4.2 授权对象id

给谁授予权限 

授权对象ID是指，权限赋予的实体，例如：IP 地址或用户

#### 5.4.3 权限permission

授予什么权限 

create、delete、read、writer、admin也就是 增、删、改、查、管理权限， 

这5种权限简写为==cdrwa==，注意:这5种权限中，==delete是指对子节点的删除权限==，

其它4种 权限==指对自身节点的操作权限==

| 权限   | ACL简写 | 描述                           |
| ------ | ------- | ------------------------------ |
| create | c       | 可以创建子节点                 |
| delete | d       | 可以删除子节点                 |
| read   | r       | 可以读取节点数据及其子节点列表 |
| write  | w       | 可以设置节点数据               |
| admin  | a       | 可以设置节点访问控制列表权限   |

#### 5.4.4 设置权限

##### 5.4.4.1 world授权权限

```bash
setAcl /node world:anyone:权限 #world只有一个对象 就是anyone  
```

##### 5.4.4.2 ip授权权限

```bash
setAcl /node ip:地址:权限
```

##### 5.4.4.3 auth授权权限

```bash
# 首先添加认证用户
addauth digest user:password
# 比如
addauth digest xiaoming:123456 # 添加了小明用户  密码为123456
# 第二步 给用户添加
setAcl /node auth:xiaoming:权限 # 给小明用户在/node上添加了权限
```

##### 5.4.4.4 digest授权权限

```bash
setAcl path digest:用户:密码:quanxian
# 比如
setAcl /node2 digest:xiaoming:123456:crdwa
```

##### 5.4.4.5 多种授权模式

```bash
setAcl /node 模式1,模式2,模式3 # 使用了多种模式授权
```

#### 5.4.5 超级管理员权限

##### 5.4.5.1 生成密码

```bash
echo -n <user>:<password> | openssl dgst -binary -sha1 | openssl base64
# 以上会生成一个密钥
echo -n xiaoming:123456 | openssl dgst -binary -sha1 | openssl base64
# 为xiaoming生成123456的秘文
# xQJmxLMiHGwaqBv st5y6rkB6HQs=
```

##### 5.4.5.2 修改zkServer脚本

原来的：

```bash
nohup $JAVA "-Dzookeeper.log.dir=${ZOO_LOG_DIR}" 
"- Dzookeeper.root.logger=${ZOO_LOG4J_PROP}"
```

加入一行

```bash
"-Dzookeeper.DigestAuthenticationProvider.superDigest=super:xQJmxLMiHGwaqBv st5y6rkB6HQs="
```

完整的

```bash
nohup $JAVA "-Dzookeeper.log.dir=${ZOO_LOG_DIR}" "- Dzookeeper.root.logger=${ZOO_LOG4J_PROP}" "- Dzookeeper.DigestAuthenticationProvider.superDigest=super:xQJmxLMiHGwaqBv st5y6rkB6HQs="\ -cp "$CLASSPATH" $JVMFLAGS $ZOOMAIN "$ZOOCFG" > "$_ZOO_DAEMON_OUT" 2>&1 < /dev/null &
```

之后启动zookeeper，然后给用户添加super权限了

```bash
addauth digest super:admin #添加认证用户
```



