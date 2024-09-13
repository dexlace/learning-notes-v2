# Prometheus学习

## 一、为什么要学习Prometheus

<img src="/Users/dexlace/private-github-repository/learning-notes/Prometheus/Prometheus学习.assets/image-20230924121242801.png" alt="image-20230924121242801" style="zoom: 50%;" />

优点：

- 基于时间序列模型：时间序列（time series X,Y）是一系列有序的数据，通常是等时间间隔的采样数据。
- 基于K/V的数据模型：数据格式简单、速度快、易于维护
- 有两种数据采集方式：pull/push，其中push的方式十分灵活

- 监控数据的精细程度，绝对的第⼀ ，可以精确到 1～5秒的采集精度
- 集群部署的速度 监控脚本的制作 （指的是熟练之后） ⾮常快速 ⼤⼤缩短监控的搭建时间成本
- 周边插件很丰富 exporter pushgateway ⼤多数都不需要⾃⼰开发了
- 本⾝基于数学计算模型，⼤量的实⽤函数 可以实现很复杂规则的业务逻辑监控（例如QPS的曲线弯曲 凸起 下跌的 ⽐例等等模糊概念）
- 可以嵌⼊很多开源⼯具的内部 进⾏监控 数据更准时 更可信（其他监控很难做到这⼀点）
- 本⾝是开源的，更新速度快，bug修复快。⽀持N多种语⾔做本⾝和插件的⼆次开发
- 图形很⾼⼤上 很美观 ⽼板特别喜欢看这种业务图 （主要是指跟Grafana的结合）

不足之处：

- 因其数据采集的精度 如果集群数量太⼤，那么单点的监控有性能瓶颈 ⽬前尚不⽀持集群 只能workaround
- 学习成本太⼤，尤其是其独有的数学命令⾏
- 对磁盘资源也是耗费的较⼤，这个具体要看 监控的集群量 和 监控项的多少 和保存时间的长短
- 本⾝的使⽤ 需要使⽤者的数学不能太差 要有⼀定的数学头脑

<img src="/Users/dexlace/private-github-repository/learning-notes/Prometheus/Prometheus学习.assets/image-20230924155750588.png" alt="image-20230924155750588" style="zoom: 50%;" />

**监控系统设计**

1. ==业务监控==可以包含 ⽤户访问QPS，DAU⽇活，访问状态（http code）， 业务接⼜(登陆，注册，聊天，上传，留⾔，短信，搜索)，产品转化率，充值额度，⽤户投诉 等等这些很宏观的概念（上层）
2. ==系统监控== 主要是跟操作系统相关的 基本监控项 CPU/ 内存 / 硬盘 / IO / TCP链接 / 流量 等等(Nagios - plugins, prometheus)
3. ==⽹络监控== （IDC）对⽹络状态的监控（交换机，路由器，防⽕墙，VPN） 互联⽹公司必不可少 但是很多时候又被忽略 例如：内⽹之间（物理内⽹，逻辑内⽹ 可⽤区 创建虚拟机 内⽹IP ）外⽹ 丢包率 延迟 等等
4. ==⽇志监控== 监控中的重头戏（Splunk,ELK），往往单独设计和搭建， 全部种类的⽇志都有需要采集 (syslog, soft, ⽹络设备，⽤户⾏为)
5. 程序监控 ⼀般需要和开发⼈员配合，程序中嵌⼊各种接⼜ 直接获取数据 或者特质的⽇志格式

**监控系统搭建**

1. 单点服务端的搭建(prometheus)
2. 单点客户端的部署
3. 单点客户端服务器测试
4. 采集程序单点部署
5. 采集程序批量部署
6. 监控服务端HA / cloud (⾃⼰定制) 
7. 监控数据图形化搭建（Grafana）
8. 报警系统测试(Pagerduty)
9. 报警规则测试
10. 监控+报警联合测试
11. 正式上线监控

**数据采集的编写**

1. shell ： 运维的⼊门脚本，任何和性能/后台/界⾯⽆关的逻辑 都可以实现最快速的开发
2. python: 各种扩展功能 扩展库 功能丰富 ，伴随各种程序的展⽰+开发框架（如django）等 可以实现快速的中⾼档次的平台逻辑开发. ⽬前在运维届 除去shell这个所有⼈必须会的脚本之外，⽕爆程度就属python了
3. awk: 本⾝是⼀个实⽤命令 也是⼀门庞⼤的编程语⾔. 结合shell脚本 或者独⽴ 都可以使⽤。在⽂本和标准输出处理上 有很⼤的优势
4. lua: 多⽤于nginx的模块结合 是⽐较新型的⼀个语⾔
5. php：⽼牌⼦的开发语⾔，在⼤型互联⽹开发中，⽬前有退潮的趋势 （PHP语⾔，php-fpm）不过在运维中 ⼯具开发还是很依赖PHP
6. perl: 传说中 对⽂本处理最快的脚本语⾔ （但是代码可读性不强）
7. go: 新型的语⾔ ⽬前在开发和运维中 炒的很热 ⼯资也⾼ C语⾔ 在各种后端服务逻辑的编写上 开发速度快 成⾏早

**监控数据分析和算法**：监控的数据分析和算法 其实⾮常依赖 运维架构师对Linux操作系统的各种底层知识的掌握

**监控稳定测试**

**监控⾃动化**

监控客户端的批量部署，监控服务端的HA再安装，监控项⽬的修改，监控项⽬的监控集群变化

**监控图形化⼯作**

### 二、Prometheus入门

### 2.1 prometheus metrics概念

对采集数据的总称，并不代表某一种具体的数据格式，是一种对于度量计算单位的抽象。

- Gauges :最简单的度量指标，只有一个简单的返回值，或者叫瞬时状态，该类型的数据没有规律，是多少就是多少，比如硬盘的容量或者内存的使用量，是随时间的推移不短变化的，瞬时的。
- Counters:计数器，从数据量从0开始计算，在理想状态下，只能永远增长，不会下降，比如对用户访问量的采样数据
- Historgrams:统计数据的分布情况，比如最大值，最小值，中间值，中位数等，比如http响应时间

### 2.2 k/v数据格式

### 

### 2.3 Prometheus的下载和安装

```bash
FROM centos
MAINTAINER 1799076485@qq.com


# 添加到容器中 会解压
ADD prometheus-2.1.0.linux-amd64.tar.gz   /usr/local/



# 设置工作访问时候的WORKDIR路径，登录落脚点
ENV MYPATH /usr/local
WORKDIR $MYPATH


# 容器运行时监听的端口
EXPOSE 9090


CMD ["/usr/local/prometheus-2.1.0.linux-amd64/prometheus","--config.file=/usr/local/prometheus-2.1.0.linux-amd64/prometheus.yml"]
```

```bash
docker build -f prometheusDockerfile -t dexlace/prometheus ./context 
```

```bash
docker run -it  -p 9090:9090 --name prometheus -v /Users/dexlace/docker/prometheus/prometheus.yml:/usr/local/prometheus-2.1.0.linux-amd64/prometheus.yml dexlace/prometheus
```

```yaml
# global是一些常规的全局配置，这里只列出了两个参数：
global:
  scrape_interval:     15s # 每15s采集一次数据
  evaluation_interval: 15s # 每15s做一次告警检测 默认不填写是 1分钟
  # scrape_timeout is set to the global default (10s).
  external_labels:
    environment: production # 定义 Prometheus 实例应用于所有接收的指标的标签列表。这些标签可用于识别不同的 Prometheus 实例，或标识集群、环境等信息


# Alertmanager相关的配置
# 定义了告警管理器的地址，触发告警后会委托给管理器处理。在上这里的例子中，告警管理器的地址是 localhost:9093，并且这个地址是静态配置的，也就是说 Prometheus 不会动态地发现新的告警管理器
alerting:
  alertmanagers:
  - static_configs:
    - targets:
      # - alertmanager:9093

# 告警规则。 按照设定参数进行扫描加载，用于自定义报警规则，其报警媒介和route路由由alertmanager插件实现。
rule_files:
  - "/opt/bitnami/prometheus/rules/*rule.yml"
  - "/etc/prometheus/rules/memory_usage.yml"
  - "/etc/prometheus/rules/disk_usage.yml"

# A scrape configuration containing exactly one endpoint to scrape:
# Here it's Prometheus itself.
scrape_configs:
  - job_name: "prometheus"
    static_configs:
      - targets: ["localhost:9090"]

  - job_name: "centosCheck"
    metrics_path: '/metrics'
    static_configs:
      - targets: ["ip:9100"]
    
  - job_name: "JVM"
    metrics_path: '/actuator/prometheus'
    static_configs:
      - targets: ["ip1:8209","ip2:6208"]
        labels:
          env: 'test'
          app: 'app1'
          appName: 'JVM平台'
      - targets: ["ip3:8208","ip4:8209"]
        labels:
          env: 'onLine'
          app: 'app2'
          appName: 'JVM平台'

```

- scrape_config: 定义数据抓取目标的配置
  - job_name: 用于==定义要抓取的目标的名称，可以是单个目标或者多个目标。这些目标可以是HTTP、HTTPS、DNS、SNMP、JMX等协议==。Prometheus会使用这个名称进行区分，当一个目标被成功抓取时，Prometheus会给它一个时间戳并存储相应的指标。在查询时，可以使用job_name来选择要查询的指标源
  - metrics_path: 用于==指定指标数据的路径==，上面的例子中的 JVM 是从 /actuator/prometheus 路径获取对应的指标。如果没有可以去掉或者注释掉 #metrics_path: '/actuator/prometheus'
  - static_configs: 是一种配置方式，用于定义一组静态的目标列表
    - targets: 用于==定义需要抓取指标的目标的列表。它指定了要监控的目标的IP地址和端口号==，让Prometheus定期去访问这些地址，抓取相应的指标数据
    - labels: 可以为每个job_name和target添加一些labels，以便更好地描述和区分指标数据,可以通过这些labels来==查询和过滤指标数据==，并在报警规则中使用这些labels来进行更加精准的报警。在上述例子的 JVM 则是用于标识各类环境或分组。
      注意 : labels 如果要使用中文，必须确认文件格式是否为 UTF-8，可以的话尽量使用 vscode 查看一下，不然可能会导致 Prometheus 启动失败

### 2.4 Prometheus exporter的使用

在Prometheus的架构设计中，==Prometheus Server并不直接服务监控特定的目标，其主要任务负责数据的收集==，存储并且对外提供数据查询支持。因此为了能够能够监控到某些东西，如主机的CPU使用率，==我们需要使用到Exporter==。Prometheus==周期性的从Exporter暴露的HTTP服务地址（通常是/metrics）拉取监控样本数据==。

==Exporter可以是一个相对开放的概念，其可以是一个独立运行的程序独立于监控目标以外，也可以是直接内置在监控目标中==。只要能够向Prometheus提供==标准格式的监控样本数据即可==。

这里为了能够采集到主机的运行指标如CPU, 内存，磁盘等信息。我们可以使用[Node Exporter](https://github.com/prometheus/node_exporter)。

Node Exporter同样采用Golang编写，并且不存在任何的第三方依赖，只需要下载，解压即可运行。可以从https://prometheus.io/download/获取最新的node exporter版本的二进制包。



### 2.5 Prometheus pushgateway的入门

