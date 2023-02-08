##  C++相关内容的学习
### 第一章:
#### 1.基本序号的介绍:
    关于本项目
    其中A开头的文档为Leetcode相关的内容(算法,每日一题或周赛的记录),
    B开头为数据库的相关使用和测试(基于mysql)
#### 2.cmake相关操作的简单介绍
    (1).cmake对于MySQL的连接方式如下所示:
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
    (2).版本号的设置以及连接等操作
```cmake
#c++的版本,当前选择了c++20
set(CMAKE_CXX_STANDARD 20)
#例如,将在2023文件夹下的2023_2的文件编写为可执行文件,在cmake中添加如下代码就可以
add_executable(Leetcode_2023_2 A3_Leetcode_2023/Leetcode_2023_2.cpp)
```
