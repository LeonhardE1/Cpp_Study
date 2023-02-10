/**
Created by Leonhard E on 2023/2/9.
���ļ����Ա�дһ������ʱ��ļ򵥲�ѯ,��Ҫ������mysql���ݿ���в�ѯ���޸Ĳ���
*/
#include <mysql.h>
#include <iostream>
#include <iomanip>

#define SQL_MAX 256		// sql����ַ��������ֵ

using namespace std;

MYSQL mysql;
MYSQL_RES *res;//�ýṹ�������е�һ����ѯ�����
MYSQL_ROW row;//һ�������ݵ����Ͱ�ȫ(type-safe)�ı�ʾ

void exit(){
    cout << "��лʹ�ñ�ϵͳ" << endl;
    //�ͷŽ������mysql���
    mysql_free_result(res);
    mysql_close(&mysql);
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
    cout << "id" << "\t"
         << setw(28) << left << "����ʱ��" << setw(28) << left << "�γ�����"
         << setw(28) << left << "���ŵص�" << setw(28) << left << "У��" << endl;
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
    int cols = (int)mysql_num_fields(res); // ���������У��еĸ���
    string str;
    cout << "����Ҫ��ѯ�Ŀ�Ŀ����(֧��ģ����ѯ)" << endl;
    cin >> str;
    int sum = 0;
    while ((row = mysql_fetch_row(res))) {
        string flag(row[2]);
        if(flag.find(str) != string::npos){
            sum++;
            if(sum == 1)
                cout << "id" << "\t"
                     << setw(28) << left << "����ʱ��" << setw(28) << left << "�γ�����"
                     << setw(28) << left << "���ŵص�" << setw(28) << left << "У��" << endl;
            cout << row[0] << "\t";
            for (int i = 1; i < cols; ++i) {
                cout << setw(28) << left << row[i];
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
}
void modify(){
    char sql[SQL_MAX];	// sql���
    string str1;
    string str2;
    int id;
    quire();
    cout << "����Ҫ�޸ĵ�id" << endl;
    cin >> id;
    cout << "����Ҫ�޸ĵ���Ŀ" << endl;
    cin >> str1;
    cout << "����Ҫ�޸ĵ�ֵ" << endl;
    cin >> str2;

    // C��������ַ���
    snprintf(sql, SQL_MAX,
             "UPDATE time SET %s = '%s' WHERE time_id = %d;", str1.c_str(), str2.c_str(), id);
    printf("�޸�sql��䣺%s\n", sql);

    if (mysql_query(&mysql, sql)) {
        printf("�����޸�ʧ�ܣ�ʧ��ԭ��%s\n", mysql_error(&mysql));
        return;
    }
    printf("�޸ı����ݳɹ���\n");
}

void addTableData() {
    char sql[SQL_MAX];		// �洢sql���
    string str1, str2, str3, str4;
    int id;
    cout << "���뿼��ʱ��" << endl;
    cin >> str1;
    cout << "����γ�����" << endl;
    cin >> str2;
    cout << "�������ŵص�" << endl;
    cin >> str3;
    cout << "����У��" << endl;
    cin >> str4;
    cout << "����id" << endl;
    cin >> id;
    snprintf(sql, SQL_MAX,
             "INSERT INTO time(time_id, ����ʱ��, �γ�����, ���ŵص�, У��) VALUES(%d, '%s', '%s', '%s', '%s');"
              , id, str1.c_str(), str2.c_str(), str3.c_str(), str4.c_str());

    if (mysql_query(&mysql, sql)) {
        printf("���������ʧ�ܣ�ʧ��ԭ��%s\n", mysql_error(&mysql));
        return;
    }
    printf("��������ݳɹ���\n");
}

void delTableData() {
    char sql[SQL_MAX];		// �洢sql���
    quire();
    cout << "����Ҫɾ�����ݵ�id" << endl;
    int id;
    cin >> id;
    // C�����ַ������
    snprintf(sql, SQL_MAX, "DELETE FROM time WHERE time_id = %d;", id);
    printf("ɾ��sql��䣺%s\n", sql);

    if (mysql_query(&mysql, sql)) {
        printf("ɾ��������ʧ�ܣ�ʧ��ԭ��%s\n", mysql_error(&mysql));
        return;
    }
    printf("ɾ�������ݳɹ���\n");
}


int main() {
    while (ConnectMysql()){
        cout << "-----������ѧ����ĩ����ʱ���ѯ-----" << endl;
        cout << "-----      1.��ӡʱ���     -----" << endl;
        cout << "-----      2.�����Ʋ�ѯ     -----" << endl;
        cout << "-----      3.�޸ľ�����     -----" << endl;
        cout << "-----      4.����������     -----" << endl;
        cout << "-----      5.ɾ��������     -----" << endl;
        cout << "-----      6.�˳���ϵͳ     -----" << endl;
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
            case 4:addTableData();
                break;
            case 5:delTableData();
                break;
            default: exit();
        }
    }
}