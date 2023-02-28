#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> mergeArrays(vector<vector<int>>& nums1, vector<vector<int>>& nums2) {
    std::sort(nums1.begin(), nums1.end());
    std::sort(nums2.begin(), nums2.end());
    vector<vector<int>> mergeArrays;
    int i = 0;
    int j = 0;
    int flag = -1;
    while (i < nums1.size() || j < nums2.size()){
        if(j >= nums2.size())
            mergeArrays.push_back(nums1[i++]);
        else if (i >= nums1.size())
            mergeArrays.push_back(nums2[j++]);
        else if(nums1[i][0] < nums2[j][0])
            mergeArrays.push_back(nums1[i++]);
        else
            mergeArrays.push_back(nums2[j++]);
        flag++;
        //合并
        if(flag > 0 && (mergeArrays[flag][0] == mergeArrays[flag - 1][0]) ){
            mergeArrays[flag - 1][1] += mergeArrays[flag][1];
            mergeArrays.erase(mergeArrays.end());
            flag--;
        }
    }

    return mergeArrays;
}

int main(){
    vector<vector<int>> nums1 = {{1,2},{2,3},{4,5}}, nums2 = {{1,4},{3,2},{4,1}};
    mergeArrays(nums1, nums2);

    return 0;
}