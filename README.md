##  C++相关内容的学习
### 第一章，基本信息介绍:
#### 1.基本序号的介绍:
    关于本项目
    其中A开头的文档为Leetcode相关的内容(算法,每日一题或周赛的记录),
    B开头为数据库的相关使用和测试(基于mysql)
#### 2.cmake相关操作的简单介绍
1)  cmake对于MySQL的连接方式如下所示:
```cmake
#添加include的路径
include_directories("C:/Program Files/MySQL/MySQL Server 8.0/include")  
#添加lib路径
link_directories("C:/Program Files/MySQL/MySQL Server 8.0/lib")   
#lib下dll文件名
link_libraries(libmysql)  
#主要配置第一个参数为项目名
target_link_libraries(mysql_test libmysql)
```
2)  版本号的设置以及连接等操作:
```cmake
#c++的版本,当前选择了c++20
set(CMAKE_CXX_STANDARD 20)
#例如,将在2023文件夹下的2023_2的文件编写为可执行文件,在cmake中添加如下代码就可以
add_executable(Leetcode_2023_2 A3_Leetcode_2023/Leetcode_2023_2.cpp)
```
### 第二章，mysql与c/c++连接的简单操作:
#### 1.mysql和c/c++的连接调用:
1)  与mysql连接，可以使用头文件<mysql.h>对相应数据进行操作
相关内容可以参考[mysql.h](https://dev.mysql.com/doc/dev/mysql-server/latest/mysql_8h.html)
2)  也可以使用mysql connector c++链接操作，但是我在这里没有将
connector c++ 导入clion中，因此不对其介绍
#### 2.inquire的简单介绍
本文件是将mysql与c/c++进行了简单的链接使用，实现了一些基本的操作
例如：增删改除等操作,调用了一些基本的mysql.h中的函数

    mysql_num_fields()
    mysql_store_result()
    mysql_query()
    mysql_real_connect()
    mysql_options()
    mysql_init()
具体内容可以参看inquire.cpp。