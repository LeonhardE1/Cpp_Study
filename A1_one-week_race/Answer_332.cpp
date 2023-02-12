//
// Created by Leonhard E on 2023/2/12.
//
#include <bits/stdc++.h>

using namespace std;

long long findTheArrayConcVal(vector<int>& nums) {
    long long result = 0;
    while(!nums.empty()){
        if(nums.size() == 1){
            result += nums[0];
            return result;
        }
        else{
            result += stoi(to_string(nums[0]) + to_string(nums[nums.size() - 1]));
            nums.erase(nums.begin() + nums.size() - 1);
            nums.erase(nums.begin());
        }
    }
    return result;
}

long long countPairs(vector<int>& nums, int lower, int upper) {
    int length = nums.size();
    sort(nums.begin(), nums.end());  // sort the array
    int j = 0;
    long long res = 0;
    for (int i = 0; i < length; ++i) {
        while (j < length && nums[j] + nums[i] < lower) j++;  // move j until the difference is >= lower
        if (j < length && nums[j] + nums[i] <= upper) res += j - i - 1;  // count the fair pairs
    }
    return res;
}

int BinStr2Dec(string binaryString){
    //在此处调用判断一个字符串有多长的函数
    int size = binaryString.size();

    //将二进制数字转换为十进制
    int parseBinary = 0;
    for (int i = 0; i < size; ++i) {
        if (binaryString[i] == '1') {
            parseBinary += pow(2.0, size - i - 1);
        }
    }

    return parseBinary;
}

bool judge(string str, int n, vector<int> res, int* flag){
    if(str[0] == '0' && str.length() > 1)
        return false;
    if((BinStr2Dec(str) ^ res[0]) == res[1]){
        *flag = 1;
        return true;
    }
    return false;
}
vector<vector<int>>  substringXorQueries(string s, vector<vector<int>>& queries) {
    int n = s.size(), m = queries.size();
    vector<vector<int>> res;
    string str;
    for (auto x: queries) {
        int i = 0;
        int j = 1;
        int flag = 0;
        while (i< n && !judge(s.substr(i, j), n, x, &flag)){
            j++;
            if(j + i > n){
                j = 1;
                i++;
            }
        }
        if(flag){
            res.push_back({i, j + i - 1});
        }
        else{
            res.push_back({-1, -1});
        }
    }
    return res;
}

void test(int* flag){
    *flag = 1;
}
int main(){
    string s = "101101010111100011001100111010001010100100110001000001001010110001";
    vector<vector<int>> queries = {{0,5},{1,2}};
    vector<vector<int>> res = substringXorQueries(s, queries);
    for (auto x: res) {
        for (auto y: x) {
            cout << y << " ";
        }
        cout << endl;
    }
    return 0;
}
