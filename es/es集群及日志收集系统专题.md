# es集群及日志收集系统专题

### 1. 安装单点中的问题

- 必须使用非root用户执行

```bash
# 所以必须创建用户
sudo adduser es
sudo passwd es
sudo mkdir /home/es
# 确保新用户的家目录已经创建。通常，adduser 命令会自动创建用户的家目录，但如果你手动创建用户，可能需要使用 mkdir 命令创建家目录：
sudo chown es:es /home/es
# 使用普通用户操作es
chown -R 普通用户名:普通用户名 /usr/local/elasticsearch
```

- X-Pack功能禁用机器学习功能

```yml
xpack.ml.enabled: false
```

- 修改config/jvm.options,默认的xms和xmx都是1g,根据内存可以更改

```bash
-Xms512m
-Xmx512m
```

- 修改es进程的最大文件描述符的数量

```bash
# 切换到root用户下
vim /etc/security/limits.conf
# 修改如下
* soft nofile 65536
* hard nofile 131072
* soft nproc 2048
* hard nproc 4096
```

- 修改systctl.conf

```bash
vm.max_map_count=262145
```

- 注册成系统服务：`elasticsearch.service`编辑完成之后`sudo systemctl daemon-reload`,设置开机启动`sudo systemctl daemon-reload`

```ini
[Unit]
Description=elasticsearch
After=network.target

[Service]
Type=forking
User=es
# 注意下面的Environment要配置ES_HOME和JAVA_HOME
Environment="ES_HOME=/usr/local/es-node"
Environment="JAVA_HOME=/usr/local/jdk8u372arm"
ExecStart=/usr/local/es-node/bin/elasticsearch -d
PrivateTmp=true
# 进程可以打开的最大文件数
LimitNOFILE=65535
# 进程可以打开的最大进程数
LimitNPROC=65535
# 最大虚拟内存
LimitAS=infinity
# 最大文件大小
LimitFSIZE=infinity
# 超时设置 0-永不超时
TimeoutStopSec=0
# SIGTERM是停止java进程的信号
KillSignal=SIGTERM
# 信号只发送给给JVM
KillMode=process
# java进程不会被杀掉
SendSIGKILL=no
# 正常退出状态
SuccessExitStatus=143
# 开机自启动
[Install]
WantedBy=multi-user.target

```

- 启动

```bash
./bin/elasticsearch
# 或者
./bin/elasticsearch -d  # 后台启动
# 注册成系统服务之后就不用如此启动了
```

- 
- 测试

``` bash
虚拟机ip:9200
curl ip:9200
```

- 需要下载jdk

### 2. 单机中的配置文件

```yml

cluster.name: es-cluster

node.name: node-1

path.data: /usr/local/es-node/data

path.logs: /es/local/es-node/logs

network.host: 0.0.0.0

http.port: 9200
xpack.ml.enabled: false

```

### 3. es-head的安装问题

`https://github.com/tradiff/elasticsearch-head-chrome/tree/master`

上面下载链接，然后直接拖到浏览器扩展中即可

### 4. 内置分词器

把==文本转换为一个个的单词==，分词称之为==analysis==。es默认只对英文语句做分词，中文不支持，==每个中文字都会被拆分为独立的个体。==

使用postman分析

分词请求路径：http://192.168.205.114:9200/_analyze

- standard:默认分词，==单词会被拆分(各个单词之间需要有空格才能)，大小会转换为小写==

> ```json
> {
>  "analyzer":"standard",
>  "text":"My name is Peter Parker, I am a Super Hero. I don't like the Criminals."
> }
> 
> ```
>
> 以上analyzer为分词器名称，text为测试的文本
>
> 其分析结果如下：
>
> ```json
> {
>  "tokens": [
>      {
>          "token": "my",
>          "start_offset": 0,
>          "end_offset": 2,
>          "type": "<ALPHANUM>",
>          "position": 0
>      },
>      {
>          "token": "name",
>          "start_offset": 3,
>          "end_offset": 7,
>          "type": "<ALPHANUM>",
>          "position": 1
>      },
>      {
>          "token": "is",
>          "start_offset": 8,
>          "end_offset": 10,
>          "type": "<ALPHANUM>",
>          "position": 2
>      },
>      {
>          "token": "peter",
>          "start_offset": 11,
>          "end_offset": 16,
>          "type": "<ALPHANUM>",
>          "position": 3
>      },
>      {
>          "token": "parker",
>          "start_offset": 17,
>          "end_offset": 23,
>          "type": "<ALPHANUM>",
>          "position": 4
>      },
>      {
>          "token": "i",
>          "start_offset": 25,
>          "end_offset": 26,
>          "type": "<ALPHANUM>",
>          "position": 5
>      },
>      {
>          "token": "am",
>          "start_offset": 27,
>          "end_offset": 29,
>          "type": "<ALPHANUM>",
>          "position": 6
>      },
>      {
>          "token": "a",
>          "start_offset": 30,
>          "end_offset": 31,
>          "type": "<ALPHANUM>",
>          "position": 7
>      },
>      {
>          "token": "super",
>          "start_offset": 32,
>          "end_offset": 37,
>          "type": "<ALPHANUM>",
>          "position": 8
>      },
>      {
>          "token": "hero",
>          "start_offset": 38,
>          "end_offset": 42,
>          "type": "<ALPHANUM>",
>          "position": 9
>      },
>      {
>          "token": "i",
>          "start_offset": 44,
>          "end_offset": 45,
>          "type": "<ALPHANUM>",
>          "position": 10
>      },
>      {
>          "token": "don't",
>          "start_offset": 46,
>          "end_offset": 51,
>          "type": "<ALPHANUM>",
>          "position": 11
>      },
>      {
>          "token": "like",
>          "start_offset": 52,
>          "end_offset": 56,
>          "type": "<ALPHANUM>",
>          "position": 12
>      },
>      {
>          "token": "the",
>          "start_offset": 57,
>          "end_offset": 60,
>          "type": "<ALPHANUM>",
>          "position": 13
>      },
>      {
>          "token": "criminals",
>          "start_offset": 61,
>          "end_offset": 70,
>          "type": "<ALPHANUM>",
>          "position": 14
>      }
>  ]
> }
> ```

- simple：==按照<font color=red>非字母</font>分词，大写转为小写。==

> ```json
> {
>  "analyzer":"simple",
>  "text":"My name is Peter Parker, I am a Super Hero. I don't like the Criminals."
> }
> ```
>
> ```json
> {
>  "tokens": [
>      {
>          "token": "my",
>          "start_offset": 0,
>          "end_offset": 2,
>          "type": "word",
>          "position": 0
>      },
>      {
>          "token": "name",
>          "start_offset": 3,
>          "end_offset": 7,
>          "type": "word",
>          "position": 1
>      },
>      {
>          "token": "is",
>          "start_offset": 8,
>          "end_offset": 10,
>          "type": "word",
>          "position": 2
>      },
>      {
>          "token": "peter",
>          "start_offset": 11,
>          "end_offset": 16,
>          "type": "word",
>          "position": 3
>      },
>      {
>          "token": "parker",
>          "start_offset": 17,
>          "end_offset": 23,
>          "type": "word",
>          "position": 4
>      },
>      {
>          "token": "i",
>          "start_offset": 25,
>          "end_offset": 26,
>          "type": "word",
>          "position": 5
>      },
>      {
>          "token": "am",
>          "start_offset": 27,
>          "end_offset": 29,
>          "type": "word",
>          "position": 6
>      },
>      {
>          "token": "a",
>          "start_offset": 30,
>          "end_offset": 31,
>          "type": "word",
>          "position": 7
>      },
>      {
>          "token": "super",
>          "start_offset": 32,
>          "end_offset": 37,
>          "type": "word",
>          "position": 8
>      },
>      {
>          "token": "hero",
>          "start_offset": 38,
>          "end_offset": 42,
>          "type": "word",
>          "position": 9
>      },
>      {
>          "token": "i",
>          "start_offset": 44,
>          "end_offset": 45,
>          "type": "word",
>          "position": 10
>      },
>      {
>          "token": "don",
>          "start_offset": 46,
>          "end_offset": 49,
>          "type": "word",
>          "position": 11
>      },
>      {
>          "token": "t",
>          "start_offset": 50,
>          "end_offset": 51,
>          "type": "word",
>          "position": 12
>      },
>      {
>          "token": "like",
>          "start_offset": 52,
>          "end_offset": 56,
>          "type": "word",
>          "position": 13
>      },
>      {
>          "token": "the",
>          "start_offset": 57,
>          "end_offset": 60,
>          "type": "word",
>          "position": 14
>      },
>      {
>          "token": "criminals",
>          "start_offset": 61,
>          "end_offset": 70,
>          "type": "word",
>          "position": 15
>      }
>  ]
> }
> ```
>
> 

- whitespace:按照==空格分词==，忽略==大小写==

> ```json
> {
>  "analyzer":"whitespace",
>  "text":"My name is Peter Parker, I am a Super Hero. I don't like the Criminals."
> }
> ```
>
> ```json
> {
>  "tokens": [
>      {
>          "token": "My",
>          "start_offset": 0,
>          "end_offset": 2,
>          "type": "word",
>          "position": 0
>      },
>      {
>          "token": "name",
>          "start_offset": 3,
>          "end_offset": 7,
>          "type": "word",
>          "position": 1
>      },
>      {
>          "token": "is",
>          "start_offset": 8,
>          "end_offset": 10,
>          "type": "word",
>          "position": 2
>      },
>      {
>          "token": "Peter",
>          "start_offset": 11,
>          "end_offset": 16,
>          "type": "word",
>          "position": 3
>      },
>      {
>          "token": "Parker,",
>          "start_offset": 17,
>          "end_offset": 24,
>          "type": "word",
>          "position": 4
>      },
>      {
>          "token": "I",
>          "start_offset": 25,
>          "end_offset": 26,
>          "type": "word",
>          "position": 5
>      },
>      {
>          "token": "am",
>          "start_offset": 27,
>          "end_offset": 29,
>          "type": "word",
>          "position": 6
>      },
>      {
>          "token": "a",
>          "start_offset": 30,
>          "end_offset": 31,
>          "type": "word",
>          "position": 7
>      },
>      {
>          "token": "Super",
>          "start_offset": 32,
>          "end_offset": 37,
>          "type": "word",
>          "position": 8
>      },
>      {
>          "token": "Hero.",
>          "start_offset": 38,
>          "end_offset": 43,
>          "type": "word",
>          "position": 9
>      },
>      {
>          "token": "I",
>          "start_offset": 44,
>          "end_offset": 45,
>          "type": "word",
>          "position": 10
>      },
>      {
>          "token": "don't",
>          "start_offset": 46,
>          "end_offset": 51,
>          "type": "word",
>          "position": 11
>      },
>      {
>          "token": "like",
>          "start_offset": 52,
>          "end_offset": 56,
>          "type": "word",
>          "position": 12
>      },
>      {
>          "token": "the",
>          "start_offset": 57,
>          "end_offset": 60,
>          "type": "word",
>          "position": 13
>      },
>      {
>          "token": "Criminals.",
>          "start_offset": 61,
>          "end_offset": 71,
>          "type": "word",
>          "position": 14
>      }
>  ]
> }
> ```

- stop:==去除无意义单词==，比如the/a/an/is

> ```json
> {
>  "analyzer":"stop",
>  "text":"My name is Peter Parker, I am a Super Hero. I don't like the Criminals."
> }
> ```
>
> ```json
> {
>  "tokens": [
>      {
>          "token": "my",
>          "start_offset": 0,
>          "end_offset": 2,
>          "type": "word",
>          "position": 0
>      },
>      {
>          "token": "name",
>          "start_offset": 3,
>          "end_offset": 7,
>          "type": "word",
>          "position": 1
>      },
>      {
>          "token": "peter",
>          "start_offset": 11,
>          "end_offset": 16,
>          "type": "word",
>          "position": 3
>      },
>      {
>          "token": "parker",
>          "start_offset": 17,
>          "end_offset": 23,
>          "type": "word",
>          "position": 4
>      },
>      {
>          "token": "i",
>          "start_offset": 25,
>          "end_offset": 26,
>          "type": "word",
>          "position": 5
>      },
>      {
>          "token": "am",
>          "start_offset": 27,
>          "end_offset": 29,
>          "type": "word",
>          "position": 6
>      },
>      {
>          "token": "super",
>          "start_offset": 32,
>          "end_offset": 37,
>          "type": "word",
>          "position": 8
>      },
>      {
>          "token": "hero",
>          "start_offset": 38,
>          "end_offset": 42,
>          "type": "word",
>          "position": 9
>      },
>      {
>          "token": "i",
>          "start_offset": 44,
>          "end_offset": 45,
>          "type": "word",
>          "position": 10
>      },
>      {
>          "token": "don",
>          "start_offset": 46,
>          "end_offset": 49,
>          "type": "word",
>          "position": 11
>      },
>      {
>          "token": "t",
>          "start_offset": 50,
>          "end_offset": 51,
>          "type": "word",
>          "position": 12
>      },
>      {
>          "token": "like",
>          "start_offset": 52,
>          "end_offset": 56,
>          "type": "word",
>          "position": 13
>      },
>      {
>          "token": "criminals",
>          "start_offset": 61,
>          "end_offset": 70,
>          "type": "word",
>          "position": 15
>      }
>  ]
> }
> ```

- keyword:不做分词。==把整个文本作为一个单独的关键词==

> ```json
> {
>  "analyzer":"keyword",
>  "text":"My name is Peter Parker, I am a Super Hero. I don't like the Criminals."
> }
> ```
>
> ```json
> {
>  "tokens": [
>      {
>          "token": "My name is Peter Parker, I am a Super Hero. I don't like the Criminals.",
>          "start_offset": 0,
>          "end_offset": 71,
>          "type": "word",
>          "position": 0
>      }
>  ]
> }
> ```
>

### 5. IK中文分词器

Github：https://github.com/medcl/elasticsearch-analysis-ik

解压该文件到`plugins`文件夹内,一定一定注意版本

重启es

`curl -X POST "localhost:9200/_analyze" -H 'Content-Type: application/json' -d'
{
  "tokenizer": "ik_smart",
  "text": "中国是一个伟大的国家"
}'`

### 6. es的数据模型

Elasticsearch 的数据模型基于文档（Document）和索引（Index）。以下是 Elasticsearch 数据模型的主要组成部分：

1. **索引（Index）**：
   - 索引是==文档的容器==，类似于关系型数据库中的表。
   - 每个索引都有一个唯一的名称，用于在 Elasticsearch 中标识和引用该索引。
   - 索引可以包含零个或多个文档，并且可以根据需要进行创建、更新和删除。
2. **文档（Document）**：
   - 文档是索引中的基本数据单元，类似于==关系型数据库中的行==。
   - 每个文档都是一个 ==JSON 格式的结构化数据==，包含了实际的数据以及元数据信息。
   - 每个文档都有一个唯一的 ID，用于在索引中标识该文档。
3. **字段（Field）**：
   - 文档由多个字段组成，每个字段都有一个名称和一个对应的值。
   - 字段可以是各种不同类型的数据，例如字符串、数字、日期、布尔值等。
   - Elasticsearch 使用映射（Mapping）来定义每个字段的数据类型、分析器、索引选项等属性。
4. **映射（Mapping）**：
   - 映射定义了索引中==文档的结构和字段类型==。
   - 映射指定了每个字段的名称、类型和属性，例如数据类型、分析器、索引选项等。
   - 映射告诉 Elasticsearch 如何解析和索引文档中的字段，并且决定了字段的搜索、排序和聚合行为。
5. **分片和副本（Shards and Replicas）**：
   - Elasticsearch 使用分片和副本来实现数据的水平扩展和高可用性。
   - 每个索引可以被分成多个分片，每个分片可以存储部分数据。
   - 分片可以被分布在集群中的不同节点上，以提高性能和容错性。
   - 每个分片可以有零个或多个副本，用于在节点故障或数据丢失时提供冗余备份。

### 7. es的索引http操作

- ==**创建索引**==

`http://127.0.0.1:9200/shopping`

```json
{
    "acknowledged": true,//响应结果
    "shards_acknowledged": true,//分片结果
    "index": "shopping"//索引名称
}
```

如果重复发 PUT 请求 ：` http://127.0.0.1:9200/shopping `添加索引，会返回错误信息 :

```json
{
    "error": {
        "root_cause": [
            {
                "type": "resource_already_exists_exception",
                "reason": "index [shopping/J0WlEhh4R7aDrfIc3AkwWQ] already exists",
                "index_uuid": "J0WlEhh4R7aDrfIc3AkwWQ",
                "index": "shopping"
            }
        ],
        "type": "resource_already_exists_exception",
        "reason": "index [shopping/J0WlEhh4R7aDrfIc3AkwWQ] already exists",
        "index_uuid": "J0WlEhh4R7aDrfIc3AkwWQ",
        "index": "shopping"
    },
    "status": 400
}

```

- ==**查看所有索引**==

`http://127.0.0.1:9200/_cat/indices?v`  GET

这里请求路径中的_cat 表示查看的意思， indices 表示索引，所以整体含义就是查看当前 ES服务器中的所有索引，就好像 MySQL 中的 show tables 的感觉，服务器响应结果如下 

```bash
health status index    uuid                   pri rep docs.count docs.deleted store.size pri.store.size
yellow open   shopping J0WlEhh4R7aDrfIc3AkwWQ   1   1          0            0       208b           208b
```

- ==**查看单个索引**==

在 Postman 中，向 ES 服务器发 GET 请求 ： `http://127.0.0.1:9200/shopping`

```json
{
    "shopping": {//索引名
        "aliases": {},//别名
        "mappings": {},//映射
        "settings": {//设置
            "index": {//设置 - 索引
                "creation_date": "1617861426847",//设置 - 索引 - 创建时间
                "number_of_shards": "1",//设置 - 索引 - 主分片数量
                "number_of_replicas": "1",//设置 - 索引 - 主分片数量
                "uuid": "J0WlEhh4R7aDrfIc3AkwWQ",//设置 - 索引 - 主分片数量
                "version": {//设置 - 索引 - 主分片数量
                    "created": "7080099"
                },
                "provided_name": "shopping"//设置 - 索引 - 主分片数量
            }
        }
    }
}
```

- **==删除索引==**

向 ES 服务器发 DELETE 请求 ： `http://127.0.0.1:9200/shopping`

```json
{
    "acknowledged": true
}
```

### 8. es的文档http操作

- **==文档创建==**

向 ES 服务器发 POST 请求 ：` http://127.0.0.1:9200/shopping/_doc`，请求体JSON内容为：

```json
{
    "title":"小米手机",
    "category":"小米",
    "images":"http://www.gulixueyuan.com/xm.jpg",
    "price":3999.00
}
```

返回结果：

```json
{
    "_index": "shopping",
    "_type": "_doc",
    "_id": "1",//<------------------自定义唯一性标识
    "_version": 1,
    "result": "created",
    "_shards": {
        "total": 2,
        "successful": 1,
        "failed": 0
    },
    "_seq_no": 1,
    "_primary_term": 1
}

```

- **==文档主键查询==**

向 ES 服务器发 GET 请求 ：` http://127.0.0.1:9200/shopping/_doc/1`

```json
{
    "_index": "shopping",
    "_type": "_doc",
    "_id": "1",
    "_version": 1,
    "_seq_no": 1,
    "_primary_term": 1,
    "found": true,
    "_source": {
        "title": "小米手机",
        "category": "小米",
        "images": "http://www.gulixueyuan.com/xm.jpg",
        "price": 3999
    }
}
```







```yml
# 允许跨域名访问
http.cors.enabled: true
# 当设置允许跨域，默认为*，表示支持所有域名
http.cors.allow-origin: "*"
# 允许所有节点访问
network.host: 0.0.0.0
# 集群的名称，同一个集群下所有节点的集群名称应该一致
cluster.name: es-cluster
# 是否存储数据
node.data: true
# 当前节点名称 每个节点不一样
node.name: node-master
# 数据的存放路径，每个节点不一样，不同es服务器对应的data和log存储的路径不能一样
path.data: /usr/local/es-node/data
# 日志的存放路径 每个节点不一样
path.logs: /usr/local/es-node/logs
# HTTP协议的对外端口，每个节点不一样，默认：9200
http.port: 9200
# TCP协议对外端口 每个节点不一样，默认：9300
transport.tcp.port: 9300
# 三个节点相互发现，包含自己，使用TCP协议的端口号
discovery.zen.ping.unicast.hosts: ["192.168.237.110:9300","192.168.237.111:9300","192.168.237.112:9300"]
# 声明大于几个的投票主节点有效，请设置为(nodes / 2) + 1
discovery.zen.minimum_master_nodes: 2
# 是否为主节点
node.master: true 
```

