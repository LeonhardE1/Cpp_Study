cmake_minimum_required(VERSION 3.24)
project(Cpp_Study)

set(CMAKE_CXX_STANDARD 23)


#数据库的添加
include_directories("C:/Program Files/MySQL/MySQL Server 8.0/include")  #添加include的路径
link_directories("C:/Program Files/MySQL/MySQL Server 8.0/lib")     #添加lib路径
link_libraries(libmysql)  #lib下dll文件名
#c++相关内容测试或题目撰写

#力扣周赛
add_executable(Answer_331 A1_one-week_race/Answer_331.cpp)
#力扣每日一题
#2023年
add_executable(Leetcode_2023_2 A3_Leetcode_2023/Leetcode_2023_2.cpp)


#数据库相关
add_executable(mysql_test B1_Mysql/mysql_test.cpp)
#主要配置第一个参数为项目名
target_link_libraries(mysql_test libmysql)