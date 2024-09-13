# Nginx学习详解

## Nginx的优势

```markdown

俄罗斯开发的一款高性能HTTP web服务器，支持反向代理，负载均衡，资源压缩，url重写，网站跳转等功能，nginx以高效的linux网络模型，epoll,event作为网络IO模型，在高并发网站情况下，nginx能够轻松支持5W+的并发流量，并且消耗的服务器内存、cpu等资源非常低，运行非常稳定
```

- 成本低

nginx强大在于其反向代理、软件负载均衡，由于nginx支持bsd开源许可协议，bsd协议可以给用户自由的使用权限，修改源码，如果修改后发布，需要遵循bsd协议

- 配置文件更加容易懂
- nginx支持网站url地址重写（网站需要域名更换），还能够根据url的特点进行请求转发，判断（7层负载均衡，比如来自于移动端请求发给移动端服务，来自于PC端流量就发给PC端的服务器）
- nginx支持高可用配置（防止单点故障，服务器崩溃）
- nginx能够节省网络带宽，支持静态文件压缩后传输，支持gzip压缩功能
- nginx支持热部署，可以不停止nginx情况下更新代码，支持nginx 7*24小时运转

##  Nginx架构初步详解

### 进程模型

nginx在启动后，会有一个master进程和多个worker进程。

master进程主要用来==管理worker进程==，

- 包含：接收来自外界的信号，向各worker进程发送信号，
- 监控worker进程的运行状态
- 当worker进程退出后(异常情况下)，会自动重新启动新的worker进程

多个worker进程之间是对等的，他们同等竞争来自客户端的请求，各进程互相之间是独立的。

==一个请求，只可能在一个worker进程中处理==，一个worker进程，不可能处理其它进程的请求。

worker进程的个数是可以设置的，一般我们会==设置与机器cpu核数一致==<img src="/Users/dexlace/private-github-repository/learning-notes/Nginx笔记/Nginx学习详解.assets/image-20230109194251334-3264581.png" alt="image-20230109194251334" style="zoom: 50%;" />

**worker进程又是如何处理请求的呢？**

worker进程之间是平等的，每个进程，处理请求的机会也是一样的。

当我们提供80端口的http服务时，一个连接请求过来，每个进程都有可能处理这个连接，怎么做到的呢？

首先，每个worker进程都是==从master进程fork过来==，

在master进程里面，==先建立好需要listen的socket==（listenfd）之后，然后再fork出多个worker进程。

所有worker进程的listenfd会在新连接到来时变得可读，**为保证只有一个进程处理该连接**，

所有worker进程在注册listenfd读事件前==抢accept_mutex==，抢到互斥锁的那个进程==注册listenfd读事件==，

在==读事件里调用accept接受该连接==。

当一个worker进程在accept这个连接之后，就开始读取请求，解析请求，处理请求，产生数据后，再返回给客户端，最后才断开连接

**nginx是如何处理事件的**



### 网络IO

- 网络数据分到到达，复制到内核缓冲区
- 数据从内核缓冲区拷贝到用户空间的应用程序
- 网络应用主要面临两个问题，数据计算，网络IO延迟
- Nginx优势在于==优秀的网络IO处理模型==

- 常见的IO模型有
- - ==阻塞模型==
  - ==非阻塞模型==
  - ==IO多路复用==
  - ==异步IO==
- 网络IO指的就是在网络中进行数据的读、写操作，本质上就是一个socket套接字读取，socket套接字在linux系统中被抽象为流的概念，网络IO就是对数据流的处理。

​    

## 配置文件

```bash
worker_processes  1; #允许进程数量，建议设置为cpu核心数或者auto自动检测，注意Windows服务器上虽然可以启动多个processes，但是实际只会用其中一个


events {
    #单个进程最大连接数（最大连接数=连接数*进程数）
    #根据硬件调整，和前面工作进程配合起来用，尽量大，但是别把cpu跑到100%就行。
    worker_connections  1024;
}


http {
    #文件扩展名与文件类型映射表(是conf目录下的一个文件)
    include       mime.types;
    #默认文件类型，如果mime.types预先定义的类型没匹配上，默认使用二进制流的方式传输
    default_type  application/octet-stream;

    #sendfile指令指定nginx是否调用sendfile 函数（zero copy 方式）来输出文件，对于普通应用，必须设为on。如果用来进行下载等应用磁盘IO重负载应用，可设置为off，以平衡磁盘与网络IO处理速度。
    sendfile        on;
    
     #长连接超时时间，单位是秒
    keepalive_timeout  65;

 #虚拟主机的配置
    server {
    #监听端口
        listen       80;
        #域名，可以有多个，用空格隔开
        server_name  localhost;

	#配置根目录以及默认页面 uri
        location / {
            root   html; 
            index  index.html index.htm;
        }

	#出错页面配置
        error_page   500 502 503 504  /50x.html;
        #/50x.html文件所在位置
        location = /50x.html {
            root   html;
        }
        
    }

}

```



