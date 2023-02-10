/**
Created by Leonhard E on 2023/2/9.
本文件尝试编写一个考试时间的简单查询,主要是利用mysql数据库进行查询和修改操作
*/
#include <mysql.h>
#include <iostream>
#include <iomanip>

#define SQL_MAX 256		// sql语句字符数组最大值

using namespace std;

MYSQL mysql;
MYSQL_RES *res;//该结构代表返回行的一个查询结果集
MYSQL_ROW row;//一个行数据的类型安全(type-safe)的表示

void exit(){
    cout << "感谢使用本系统" << endl;
    //释放结果集合mysql句柄
    mysql_free_result(res);
    mysql_close(&mysql);
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
    cout << "id" << "\t"
         << setw(28) << left << "考试时间" << setw(28) << left << "课程名称"
         << setw(28) << left << "已排地点" << setw(28) << left << "校区" << endl;
    while ((row = mysql_fetch_row(res))) {
        cout << row[0] << "\t";
        for (int i = 1; i < cols; ++i) {
            cout << setw(28) << left << row[i];
        }
        cout << endl;
    }
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
        string flag(row[2]);
        if(flag.find(str) != string::npos){
            sum++;
            if(sum == 1)
                cout << "id" << "\t"
                     << setw(28) << left << "考试时间" << setw(28) << left << "课程名称"
                     << setw(28) << left << "已排地点" << setw(28) << left << "校区" << endl;
            cout << row[0] << "\t";
            for (int i = 1; i < cols; ++i) {
                cout << setw(28) << left << row[i];
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
}
void modify(){
    char sql[SQL_MAX];	// sql语句
    string str1;
    string str2;
    int id;
    quire();
    cout << "输入要修改的id" << endl;
    cin >> id;
    cout << "输入要修改的项目" << endl;
    cin >> str1;
    cout << "输入要修改的值" << endl;
    cin >> str2;

    // C语言组合字符串
    snprintf(sql, SQL_MAX,
             "UPDATE time SET %s = '%s' WHERE time_id = %d;", str1.c_str(), str2.c_str(), id);
    printf("修改sql语句：%s\n", sql);

    if (mysql_query(&mysql, sql)) {
        printf("数据修改失败！失败原因：%s\n", mysql_error(&mysql));
        return;
    }
    printf("修改表数据成功！\n");
}

void addTableData() {
    char sql[SQL_MAX];		// 存储sql语句
    string str1, str2, str3, str4;
    int id;
    cout << "输入考试时间" << endl;
    cin >> str1;
    cout << "输入课程名称" << endl;
    cin >> str2;
    cout << "输入已排地点" << endl;
    cin >> str3;
    cout << "输入校区" << endl;
    cin >> str4;
    cout << "输入id" << endl;
    cin >> id;
    snprintf(sql, SQL_MAX,
             "INSERT INTO time(time_id, 考试时间, 课程名称, 已排地点, 校区) VALUES(%d, '%s', '%s', '%s', '%s');"
              , id, str1.c_str(), str2.c_str(), str3.c_str(), str4.c_str());

    if (mysql_query(&mysql, sql)) {
        printf("插入表数据失败！失败原因：%s\n", mysql_error(&mysql));
        return;
    }
    printf("插入表数据成功！\n");
}

void delTableData() {
    char sql[SQL_MAX];		// 存储sql语句
    quire();
    cout << "输入要删除数据的id" << endl;
    int id;
    cin >> id;
    // C语言字符串组合
    snprintf(sql, SQL_MAX, "DELETE FROM time WHERE time_id = %d;", id);
    printf("删除sql语句：%s\n", sql);

    if (mysql_query(&mysql, sql)) {
        printf("删除表数据失败！失败原因：%s\n", mysql_error(&mysql));
        return;
    }
    printf("删除表数据成功！\n");
}


int main() {
    while (ConnectMysql()){
        cout << "-----大三上学期期末考试时间查询-----" << endl;
        cout << "-----      1.打印时间表     -----" << endl;
        cout << "-----      2.按名称查询     -----" << endl;
        cout << "-----      3.修改旧数据     -----" << endl;
        cout << "-----      4.增加新数据     -----" << endl;
        cout << "-----      5.删除旧数据     -----" << endl;
        cout << "-----      6.退出此系统     -----" << endl;
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
            case 4:addTableData();
                break;
            case 5:delTableData();
                break;
            default: exit();
        }
    }
}