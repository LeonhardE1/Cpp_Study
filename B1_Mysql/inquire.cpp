/**
Created by Leonhard E on 2023/2/9.
本文件尝试编写一个考试时间的简单查询,主要是利用mysql数据库进行查询和修改操作
*/
#include <mysql.h>
#include <iostream>
#include <iomanip>
//#include <mysqlx/xdevapi>

using namespace std;

MYSQL mysql;
MYSQL_RES *res;//该结构代表返回行的一个查询结果集
MYSQL_ROW row;//一个行数据的类型安全(type-safe)的表示

void exit(){
    cout << "感谢使用本系统" << endl;
    std::system("pause");
    exit(0);
}
bool ConnectMysql() {
    mysql_init(&mysql);//初始化mysql
    mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
    if (!(mysql_real_connect(&mysql, "localhost",
                             "root", "lk666lklk", "inquire_test",
                             3306, nullptr, 0))) {
        cout << "Error connecting to database:" + (string) mysql_error(&mysql) << endl;
        return false;
    }
    return true;
}
void quire(){
    mysql_query(&mysql, "select * from time");
    res = mysql_store_result(&mysql);
    int cols = (int)mysql_num_fields(res); // 计算结果集中，列的个数
    cout << setw(30) << left << "考试时间" << setw(30) << left << "课程名称"
         << setw(30) << left << "已排地点" << setw(30) << left << "校区" << endl;
    while ((row = mysql_fetch_row(res))) {
        for (int i = 0; i < cols; ++i) {
            cout << setw(30) << left << row[i];
        }
        cout << endl;
    }
    //释放结果集合mysql句柄
    mysql_free_result(res);
    mysql_close(&mysql);
}
void quire_name(){
    mysql_query(&mysql, "select * from time");
    res = mysql_store_result(&mysql);
    int cols = (int)mysql_num_fields(res); // 计算结果集中，列的个数
    string str;
    cout << "输入要查询的科目名称(支持模糊查询)" << endl;
    cin >> str;
    int sum = 0;
    while ((row = mysql_fetch_row(res))) {
        string flag(row[1]);
        if(flag.find(str) != string::npos){
            sum++;
            if(sum == 1)
                cout << setw(30) << left << "考试时间" << setw(30) << left << "课程名称"
                     << setw(30) << left << "已排地点" << setw(30) << left << "校区" << endl;
            for (int i = 0; i < cols; ++i) {
                cout << setw(30) << left << row[i];
            }
            cout << endl;
        }
    }
    if(sum == 0){
        cout << "没有找到相关信息" << endl;
    }
    else{
        cout << "共有" << sum << "条相关记录满足条件,如上所示\n\n" << endl;
    }
    //释放结果集合mysql句柄
    mysql_free_result(res);
    mysql_close(&mysql);
}
void modify(){
    cout << "待开发" << endl;
}

int main() {
    while (ConnectMysql()){
        cout << "-----大三上学期期末考试时间查询-----" << endl;
        cout << "-----      1.打印时间表     -----" << endl;
        cout << "-----      2.按名称查询     -----" << endl;
        cout << "-----      3.修改或增删     -----" << endl;
        cout << "-----      4.退出此系统     -----" << endl;
        cout << "-----大三上学期期末考试时间查询-----" << endl;
        int flag;
        cin >> flag;
        switch (flag) {
            case 1: quire();
                break;
            case 2:quire_name();
                break;
            case 3:modify();
                break;
            default: exit();
        }
    }
}