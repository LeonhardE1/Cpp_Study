//
// Created by Leonhard E on 2023/2/6.
//
#include <bits/stdc++.h>
using namespace std;

//1604. 警告一小时内使用相同员工卡大于等于三次的人
//力扣公司的员工都使用员工卡来开办公室的门。每当一个员工使用一次他的员工卡，安保系统会记录下员工的名字和使用时间
//如果一个员工在一小时时间内使用员工卡的次数大于等于三次，这个系统会自动发布一个 警告 。
//给你字符串数组 keyName 和 keyTime ，其中 [keyName[i], keyTime[i]] 对应一个人的名字和他在
//某一天 内使用员工卡的时间。
//使用时间的格式是 24小时制 ，形如 "HH:MM" ，比方说 "23:51" 和 "09:49" 。
//请你返回去重后的收到系统警告的员工名字，将它们按 字典序升序 排序后返回。
//请注意 "10:00" - "11:00" 视为一个小时时间范围内，而 "23:51" - "00:10" 不被视为一小时内，
//因为系统记录的是某一天内的使用情况。

int getTime(const string& str) {
    return stoi(str.substr(0, 2)) * 60 + stoi(str.substr(3, 2));
}

vector<string> alertNames(vector<string> &keyName, vector<string> &keyTime) {
    unordered_map<string, vector<int>> my_Map;
    vector<string> alertNames;
    for (int i = 0; i < keyName.size(); ++i) {
        my_Map[keyName[i]].push_back(getTime(keyTime[i]));
    }
    for (auto x: my_Map) {
        sort(x.second.begin(), x.second.end());
        unsigned int length = x.second.size();
        int j = 0;
        for (int i = 0; i < length; ++i) {
            while (j < length && x.second[j] - x.second[i] <= 60)
                j++;
            if (j - i >= 3) {
                alertNames.push_back(x.first);
                break;
            }
        }
    }
    sort(alertNames.begin(), alertNames.end());
    return alertNames;
}

//1233. 删除子文件夹
//你是一位系统管理员，手里有一份文件夹列表 folder，你的任务是要删除该列表中的所有 子文件夹，并以 任意顺序 返回剩下的文件夹。
//
//如果文件夹 folder[i] 位于另一个文件夹 folder[j] 下，那么 folder[i] 就是 folder[j] 的 子文件夹 。
//
//文件夹的「路径」是由一个或多个按以下格式串联形成的字符串：'/' 后跟一个或者多个小写英文字母。
//
//例如，"/leetcode" 和 "/leetcode/problems" 都是有效的路径，而空字符串和 "/" 不是。
vector<string> removeSub_folders(vector<string>& folder) {
    sort(folder.begin(), folder.end());
    vector<string> result;
    for (auto & i : folder) {
        bool is_sub_folder = false;
        for (const auto &res : result) {
            if (i.find(res) == 0 && i[res.length()] == '/') {
                is_sub_folder = true;
                break;
            }
        }
        if (!is_sub_folder) {
            result.push_back(i);
        }
    }
    return result;
}


int main() {
    vector<string> folder = {"/ah/al/am","/ah/al"};
    vector<string> removeSub_folder = removeSub_folders(folder);
    for (auto x:removeSub_folder) {
        cout << x << endl;
    }
    return 0;
}