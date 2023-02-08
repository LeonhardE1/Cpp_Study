//
// Created by Leonhard E on 2023/2/5.
//
#include <bits/stdc++.h>

using namespace std;

long long pickGifts(vector<int>& gifts, int k) {
    while (k--) {
        int max_gift = 0, max_index = 0;
        for (int i = 0; i < gifts.size(); i++) {
            if (gifts[i] > max_gift) {
                max_gift = gifts[i];
                max_index = i;
            }
        }
        int gift_left = floor(sqrt(max_gift));
        gifts[max_index] = gift_left;
    }
    long long sum = 0;
    for (long long gift : gifts) {
        sum += gift;
    }
    return sum;
}


//vector<int> vowelStrings(vector<string>& words, vector<vector<int>>& queries) {
//    vector<int> flag;
//    for (auto & word : words) {
//        int length = word.length();
//        char ch = word[0];
//        if(ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u' ){
//            ch = word[length-1];
//            if(ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u')
//            flag.push_back(1);
//        }
//        else{
//            flag.push_back(0);
//        }
//    }
//    vector<int> answer;
//    int sum = 0;
//    for (auto & querie : queries) {
//        for (int i = querie[0]; i <= querie[1]; ++i) {
//            if (flag[i] == 1)
//                sum++;
//        }
//        answer.push_back(sum);
//        sum = 0;
//    }
//    return answer;
//}

vector<int> vowelStrings(vector<string>& words, vector<vector<int>>& queries) {
    vector<int> prefixSum(words.size());
    for (int i = 0; i < words.size(); ++i) {
        if (words[i][0] == 'a' || words[i][0] == 'e' || words[i][0] == 'i' || words[i][0] == 'o' || words[i][0] == 'u') {
            if (words[i][words[i].size() - 1] == 'a' || words[i][words[i].size() - 1] == 'e' || words[i][words[i].size() - 1] == 'i' || words[i][words[i].size() - 1] == 'o' || words[i][words[i].size() - 1] == 'u') {
                prefixSum[i] = 1;
            }
        }
    }
    for (int i = 1; i < words.size(); ++i) {
        prefixSum[i] += prefixSum[i - 1];
    }
    vector<int> result(queries.size());
    for (int i = 0; i < queries.size(); ++i) {
        if (queries[i][0] == 0) {
            result[i] = prefixSum[queries[i][1]];
        } else {
            result[i] = prefixSum[queries[i][1]] - prefixSum[queries[i][0] - 1];
        }
    }
    return result;
}

int minCapability(vector<int>& nums, int k) {
    vector<int> flag;
    for (int i = 0; i < k; ++i) {
        auto result = std::min_element(nums.begin(), nums.end());
        int index = (int)distance(nums.begin(), result);
        flag.push_back(nums[index]);
        if(index - 1 >= 0 && index + 1 < nums.size()){
            nums.erase(nums.begin() + index - 1);
            nums.erase(nums.begin() + index - 1);
            nums.erase(nums.begin() + index - 1);
        }
        else if(index - 1 < 0){
            if(index + 1 >= nums.size()){
                nums.erase(nums.begin() + index);
            } else{
                nums.erase(nums.begin() + index);
                nums.erase(nums.begin() + index);
            }
        }
        else{
            if(index - 1 < 0){
                nums.erase(nums.begin() + index);
            } else{
                nums.erase(nums.begin() + index - 1);
                nums.erase(nums.begin() + index - 1);
            }
        }
    }
    for (auto i:flag) {
        cout << i << endl;
    }
    sort(flag.begin(), flag.end());
    int length = flag.size();
    return flag[length - 1];
}

int main(){
    vector<int> nums = {2,7,9,3,1};
    int k = 2;
    cout << minCapability(nums, k);
    return 0;
}