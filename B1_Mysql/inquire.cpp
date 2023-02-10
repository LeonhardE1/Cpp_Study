/**
Created by Leonhard E on 2023/2/9.
���ļ����Ա�дһ������ʱ��ļ򵥲�ѯ,��Ҫ������mysql���ݿ���в�ѯ���޸Ĳ���
*/
#include <mysql.h>
#include <iostream>
#include <iomanip>
//#include <mysqlx/xdevapi>

using namespace std;

MYSQL mysql;
MYSQL_RES *res;//�ýṹ�������е�һ����ѯ�����
MYSQL_ROW row;//һ�������ݵ����Ͱ�ȫ(type-safe)�ı�ʾ

void exit(){
    cout << "��лʹ�ñ�ϵͳ" << endl;
    std::system("pause");
    exit(0);
}
bool ConnectMysql() {
    mysql_init(&mysql);//��ʼ��mysql
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
    int cols = (int)mysql_num_fields(res); // ���������У��еĸ���
    cout << setw(30) << left << "����ʱ��" << setw(30) << left << "�γ�����"
         << setw(30) << left << "���ŵص�" << setw(30) << left << "У��" << endl;
    while ((row = mysql_fetch_row(res))) {
        for (int i = 0; i < cols; ++i) {
            cout << setw(30) << left << row[i];
        }
        cout << endl;
    }
    //�ͷŽ������mysql���
    mysql_free_result(res);
    mysql_close(&mysql);
}
void quire_name(){
    mysql_query(&mysql, "select * from time");
    res = mysql_store_result(&mysql);
    int cols = (int)mysql_num_fields(res); // ���������У��еĸ���
    string str;
    cout << "����Ҫ��ѯ�Ŀ�Ŀ����(֧��ģ����ѯ)" << endl;
    cin >> str;
    int sum = 0;
    while ((row = mysql_fetch_row(res))) {
        string flag(row[1]);
        if(flag.find(str) != string::npos){
            sum++;
            if(sum == 1)
                cout << setw(30) << left << "����ʱ��" << setw(30) << left << "�γ�����"
                     << setw(30) << left << "���ŵص�" << setw(30) << left << "У��" << endl;
            for (int i = 0; i < cols; ++i) {
                cout << setw(30) << left << row[i];
            }
            cout << endl;
        }
    }
    if(sum == 0){
        cout << "û���ҵ������Ϣ" << endl;
    }
    else{
        cout << "����" << sum << "����ؼ�¼��������,������ʾ\n\n" << endl;
    }
    //�ͷŽ������mysql���
    mysql_free_result(res);
    mysql_close(&mysql);
}
void modify(){
    cout << "������" << endl;
}

int main() {
    while (ConnectMysql()){
        cout << "-----������ѧ����ĩ����ʱ���ѯ-----" << endl;
        cout << "-----      1.��ӡʱ���     -----" << endl;
        cout << "-----      2.�����Ʋ�ѯ     -----" << endl;
        cout << "-----      3.�޸Ļ���ɾ     -----" << endl;
        cout << "-----      4.�˳���ϵͳ     -----" << endl;
        cout << "-----������ѧ����ĩ����ʱ���ѯ-----" << endl;
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