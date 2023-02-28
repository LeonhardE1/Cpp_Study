/**
Created by Leonhard E on 2023/2/6.
Leetcode 2023/2月的每日一题记录
*/
#include <bits/stdc++.h>
using namespace std;

//TODO:2/7, 1604. 警告一小时内使用相同员工卡大于等于三次的人:
/**力扣公司的员工都使用员工卡来开办公室的门。每当一个员工使用一次他的员工卡，安保系统会记录下员工的名字和使用时间
如果一个员工在一小时时间内使用员工卡的次数大于等于三次，这个系统会自动发布一个 警告 。
给你字符串数组 keyName 和 keyTime ，其中 [keyName[i], keyTime[i]] 对应一个人的名字和他在
某一天 内使用员工卡的时间。
使用时间的格式是 24小时制 ，形如 "HH:MM" ，比方说 "23:51" 和 "09:49" 。
请你返回去重后的收到系统警告的员工名字，将它们按 字典序升序 排序后返回。
请注意 "10:00" - "11:00" 视为一个小时时间范围内，而 "23:51" - "00:10" 不被视为一小时内，
因为系统记录的是某一天内的使用情况。
 */
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
//TODO:2/8, 1233. 删除子文件夹:
/**
你是一位系统管理员，手里有一份文件夹列表 folder，你的任务是要删除该列表中的所有 子文件夹，并以 任意顺序 返回剩下的文件夹。
如果文件夹 folder[i] 位于另一个文件夹 folder[j] 下，那么 folder[i] 就是 folder[j] 的 子文件夹 。
文件夹的「路径」是由一个或多个按以下格式串联形成的字符串：'/' 后跟一个或者多个小写英文字母。
例如，"/leetcode" 和 "/leetcode/problems" 都是有效的路径，而空字符串和 "/" 不是。
 */
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
//TODO:2/9, 1797. 设计一个验证系统:
/**你需要设计一个包含验证码的验证系统。每一次验证中，用户会收到一个新的验证码，这个验证码在 currentTime 时刻之后
 timeToLive 秒过期。如果验证码被更新了，那么它会在 currentTime （可能与之前的 currentTime 不同）
 时刻延长 timeToLive 秒。
请你实现 AuthenticationManager 类：
AuthenticationManager(int timeToLive) 构造 AuthenticationManager 并设置 timeToLive 参数。
generate(string tokenId, int currentTime) 给定 tokenId ，在当前时间 currentTime 生成一个新的验证码。
renew(string tokenId, int currentTime) 将给定 tokenId 且 未过期 的验证码在 currentTime 时刻更新。
如果给定 tokenId 对应的验证码不存在或已过期，请你忽略该操作，不会有任何更新操作发生。
countUnexpiredTokens(int currentTime) 请返回在给定 currentTime 时刻，未过期 的验证码数目。
如果一个验证码在时刻 t 过期，且另一个操作恰好在时刻 t 发生（renew 或者 countUnexpiredTokens 操作），
过期事件 优先于 其他操作。
 */
class AuthenticationManager {
private:
    int timeToLive;
    unordered_map<string, int> my_Map;
public:
    AuthenticationManager(int timeToLive) {
        this->timeToLive = timeToLive;
    }

    void generate(string tokenId, int currentTime) {
        my_Map[tokenId] = currentTime;
    }

    void renew(string tokenId, int currentTime) {
        if(my_Map.find(tokenId) == my_Map.end() || my_Map[tokenId]  > currentTime)
            return;
        if(currentTime-my_Map[tokenId]<timeToLive)
            my_Map[tokenId] = currentTime;
    }

    int countUnexpiredTokens(int currentTime) {
        int count = 0;
        for (auto x: my_Map) {
            if(x.second + timeToLive > currentTime)
                count++;
        }
        return count;
    }
};
//TODO:2/10, 1223. 掷骰子模拟, (不会写)
/**有一个骰子模拟器会每次投掷的时候生成一个 1 到 6 的随机数。
不过我们在使用它时有个约束，就是使得投掷骰子时，连续 掷出数字 i 的次数不能超过 rollMax[i]（i 从 1 开始编号）。
现在，给你一个整数数组 rollMax 和一个整数 n，请你来计算掷 n 次骰子可得到的不同点数序列的数量。
假如两个序列中至少存在一个元素不同，就认为这两个序列是不同的。由于答案可能很大，所以请返回 模 10^9 + 7 之后的结果。
*/
int dieSimulator(int n, vector<int>& rollMax) {
    const int MOD = 1e9 + 7;
    typedef long long LL;
    vector<vector<LL> > dp(n+1, vector<LL>(7));
    // 初始化
    for (int j = 1; j <= 6; j++) {
        dp[1][j] = 1;
    }
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= 6; j++) {
            // 加入第 i-1 次得所有可能序列总数
            LL ans = accumulate(dp[i-1].begin(), dp[i-1].end(), 0LL);
            int idx = i - 1 - rollMax[j-1];
            if (idx >= 1) {
                // 减去 i - 1 - rollMax[j-1]次掷出1，2，3，4，5 的所有序列总数
                ans = accumulate(dp[idx].begin(), dp[idx].end(), ans, [&](LL init, LL e) {
                    return init + MOD - e;
                });
                ans += dp[idx][j];
            }else if (idx == 0) {
                // 特殊情况处理
                ans -= 1;
            }
            dp[i][j] = ans % MOD;
        }
    }
    return accumulate(dp[n].begin(), dp[n].end(), 0LL) % MOD;
}
//TODO:2/11, 2335. 装满杯子需要的最短总时长
/**现有一台饮水机，可以制备冷水、温水和热水。每秒钟，可以装满 2 杯 不同 类型的水或者 1 杯任意类型的水。给你一个下标从 0 开始、长度为 3 的整数数组 amount ，
其中 amount[0]、amount[1] 和 amount[2] 分别表示需要装满冷水、温水和热水的杯子数量。返回装满所有杯子所需的 最少 秒数。
 */
int fillCups(vector<int>& amount) {
    int sum = 0;
    while (!amount.empty()){
        sort(amount.begin(), amount.end());
        if(amount[0] == 0)
            amount.erase(amount.begin());
        else{
            int length = amount.size();
            if(length == 1)
                return amount[0] + sum;
            amount[0]--;
            amount[length -1 ]--;
            sum++;
        }
    }
    return sum;
}
//TODO:2/12, 1138. 字母板上的路径
/**我们从一块字母板上的位置 (0, 0) 出发，该坐标对应的字符为 board[0][0]。
在本题里，字母板为board = ["abcde", "fghij", "klmno", "pqrst", "uvwxy", "z"]，如下所示。
我们可以按下面的指令规则行动：
如果方格存在，'U' 意味着将我们的位置上移一行；
如果方格存在，'D' 意味着将我们的位置下移一行；
如果方格存在，'L' 意味着将我们的位置左移一列；
如果方格存在，'R' 意味着将我们的位置右移一列；
'!' 会把在我们当前位置 (r, c) 的字符 board[r][c] 添加到答案中。
（注意，字母板上只存在有字母的位置。）
返回指令序列，用最小的行动次数让答案和目标 target 相同。你可以返回任何达成目标的路径。
*/
string alphabetBoardPath(string target) {
    string ans;
    int i = 0, j = 0;
    for (char& c : target) {
        int v = c - 'a';
        int x = v / 5, y = v % 5;
        while (j > y) {
            --j;
            ans += 'L';
        }
        while (i > x) {
            --i;
            ans += 'U';
        }
        while (j < y) {
            ++j;
            ans += 'R';
        }
        while (i < x) {
            ++i;
            ans += 'D';
        }
        ans += '!';
    }
    return ans;
}
//TODO:2/13, 1234. 替换子串得到平衡字符串
/**有一个只含有 'Q', 'W', 'E', 'R' 四种字符，且长度为 n 的字符串。
假如在该字符串中，这四个字符都恰好出现 n/4 次，那么它就是一个「平衡字符串」。
给你一个这样的字符串 s，请通过「替换一个子串」的方式，使原字符串 s 变成一个「平衡字符串」。
你可以用和「待替换子串」长度相同的 任何 其他字符串来完成替换。
请返回待替换子串的最小可能长度。
如果原字符串自身就是一个平衡字符串，则返回 0。
 */
int count_char(const std::string &str, char c) {
    int count = 0;
    for (char ch : str) {
        if (ch == c) {
            ++count;
        }
    }
    return count;
}

bool judge(string str, unordered_map<char, int> my_Map, int flag){
    for (auto x : my_Map) {
        if(count_char(str, x.first) != x.second - flag)
            return false;
    }
    return true;
}

int balancedString(string s) {
    unordered_map<char, int> my_Map;
    for (char ch : s) {
       my_Map[ch]++;
    }
    int flag = s.length()/4;
    int sum = 0;
    // List of keys to delete
    vector<char> keysToDelete;

    for (auto x : my_Map) {
        if(x.second > flag){
            sum += (x.second - flag);
        }
        else{
            keysToDelete.push_back(x.first);
        }
    }
    // Deleting elements using a loop
    for (int key : keysToDelete) {
        auto it = my_Map.find(key);
        if (it != my_Map.end()) {
            my_Map.erase(it);
        }
    }
    if(sum == 0)
        return sum;
    sum--;
    while (sum++){
        int i = 0;
//        string str = s.substr(i, sum);
        while (i + sum <= s.length()){
            if(judge(s.substr(i, sum), my_Map, flag)){
                return sum;
            }
            i++;
        }
    }
    return sum;
}
//TODO:2//14, 1124. 表现良好的最长时间段
/**给你一份工作时间表 hours，上面记录着某一位员工每天的工作小时数。
我们认为当员工一天中的工作小时数大于 8 小时的时候，那么这一天就是「劳累的一天」。
所谓「表现良好的时间段」，意味在这段时间内，「劳累的天数」是严格 大于「不劳累的天数」。
请你返回「表现良好时间段」的最大长度。
*/
int longestWPI(vector<int>& hours) {
    int n = hours.size();
    int ans = 0;
    //计算前缀和
    for (int i = 0; i < hours.size(); ++i) {
        if(hours[i] > 8)
            hours[i] = 1;
        else
            hours[i] = -1;
    }
    vector<int> par_sum(n+1, 0);
    partial_sum(hours.begin(), hours.end(), par_sum.begin() + 1);
    //利用单调栈计算
    stack<int> st;
    st.push(par_sum[0]);
    for (int j = 1; j <= n; ++j) {
        if (par_sum[j] < par_sum[st.top()]) st.push(j); // 感兴趣的 j
    }
    for (int i = n; i; --i)
        while (!st.empty() && par_sum[i] > par_sum[st.top()]) {
            ans = max(ans, i - st.top()); // [栈顶,i) 可能是最长子数组
            st.pop();
        }
    return ans;
}

//TODO: 2/15, 1250. 检查「好数组」
/**给你一个正整数数组 nums，你需要从中任选一些子集，然后将子集中每一个数乘以一个 任意整数，并求出他们的和。
假如该和结果为 1，那么原数组就是一个「好数组」，则返回 True；否则请返回 False。
*/
bool isGoodArray(vector<int>& nums) {
    int max_gcd = nums[0];
    for (int num : nums) {
        max_gcd = gcd(max_gcd, num);
    }
    return max_gcd == 1;
}
//TODO: 2/16, 2341. 数组能形成多少数对
/**给你一个下标从 0 开始的整数数组 nums 。在一步操作中，你可以执行以下步骤：
//
//从 nums 选出 两个 相等的 整数
//从 nums 中移除这两个整数，形成一个 数对
//请你在 nums 上多次执行此操作直到无法继续执行。
//
//返回一个下标从 0 开始、长度为 2 的整数数组 answer 作为答案，其中 answer[0] 是形成的数对数目，answer[1] 是对 nums 尽可能执行上述操作后剩下的整数数目。
*/
vector<int> numberOfPairs(vector<int>& nums) {
    unordered_map<int ,int> my_Map;
    vector<int> ans(2, 0);
    for (auto x : nums) {
        my_Map[x]++;
        if(my_Map[x] == 1)
            ans[1]++;
        else{
            ans[0]++;
            ans[1]--;
            my_Map[x] = 0;
        }
    }
    return ans;
}
//TODO: 2/20, 2347. 最好的扑克手牌
/**给你一个整数数组 ranks 和一个字符数组 suit 。你有 5 张扑克牌，第 i 张牌大小为 ranks[i] ，花色为 suits[i] 。
//
//下述是从好到坏你可能持有的 手牌类型 ：
//
//"Flush"：同花，五张相同花色的扑克牌。
//"Three of a Kind"：三条，有 3 张大小相同的扑克牌。
//"Pair"：对子，两张大小一样的扑克牌。
//"High Card"：高牌，五张大小互不相同的扑克牌。
//请你返回一个字符串，表示给定的 5 张牌中，你能组成的 最好手牌类型 。
//
//注意：返回的字符串 大小写 需与题目描述相同。
*/
string bestHand(vector<int>& ranks, vector<char>& suits) {
    set<char> set_;
    unordered_map<int,int> my_Map;
    string ans;
    for (char ch : suits) {
        set_.emplace(ch);
    }
    if(set_.size() == 1)
        return "Flush";
    for(int rank : ranks) {
        ++my_Map[rank];
        if(my_Map[rank] == 2 && ans != "Three of a Kind") ans = "Pair";
        if(my_Map[rank] >= 3) ans = "Three of a Kind";
    }
    return (ans.empty() ? "High Card" : ans);
}
//TODO: 2/21, 1326. 灌溉花园的最少水龙头数目
/**在 x 轴上有一个一维的花园。花园长度为 n，从点 0 开始，到点 n 结束。
花园里总共有 n + 1 个水龙头，分别位于 [0, 1, ..., n] 。
给你一个整数 n 和一个长度为 n + 1 的整数数组 ranges ，其中 ranges[i] （下标从 0 开始）表示：如果打开点 i 处的水龙头，可以灌溉的区域为 [i -  ranges[i], i + ranges[i]] 。
请你返回可以灌溉整个花园的 最少水龙头数目 。如果花园始终存在无法灌溉到的地方，请你返回 -1 。
*/
int minTaps(int n, vector<int>& ranges) {
    int right_most[n + 1]; memset(right_most, 0, sizeof(right_most));
    for (int i = 0; i <= n; ++i) {
        int r = ranges[i];
        if (i > r) right_most[i - r] = i + r; 
        else right_most[0] = max(right_most[0], i + r);
    }

    int ans = 0;
    int cur_right = 0; // 已建造的桥的右端点
    int next_right = 0; // 下一座桥的右端点的最大值
    for (int i = 0; i < n; ++i) { // 注意这里没有遍历到 n，因为它已经是终点了
        next_right = max(next_right, right_most[i]);
        if (i == cur_right) { // 到达已建造的桥的右端点
            if (i == next_right) return -1; // 无论怎么造桥，都无法从 i 到 i+1
            cur_right = next_right; // 造一座桥
            ++ans;
        }
    }
    return ans;
}
//TODO: 2/23 ,1238. 循环码排列
/**给你两个整数 n 和 start。你的任务是返回任意 (0,1,2,,...,2^n-1) 的排列 p，并且满足：

p[0] = start
p[i] 和 p[i+1] 的二进制表示形式只有一位不同
p[0] 和 p[2^n -1] 的二进制表示形式也只有一位不同
*/
vector<int> circularPermutation(int n, int start) {
    int g[1 << n];
    int j = 0;
    for (int i = 0; i < 1 << n; ++i) {
        g[i] = i ^ (i >> 1);
        if (g[i] == start) {
            j = i;
        }
    }
    vector<int> ans;
    for (int i = j; i < j + (1 << n); ++i) {
        ans.push_back(g[i % (1 << n)]);
    }
    return ans;
}
//TODO: 2/24, 2357. 使数组中所有元素都等于零
/**给你一个非负整数数组 nums 。在一步操作中，你必须：
选出一个正整数 x ，x 需要小于或等于 nums 中 最小 的 非零 元素。
nums 中的每个正整数都减去 x。
返回使 nums 中所有元素都等于 0 需要的 最少 操作数。
*/
int minimumOperations(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    int sum = 0;
    int i = 0;
    while(nums[nums.size() - 1] != 0){
        sort(nums.begin(), nums.end());
        i = 0;
        int x = nums[i];
        while(x == 0){
            i++;
            x = nums[i];
        }
        for (int & num : nums) {
            if(num != 0)
            num -= x;
        }
        sum++;
    }
    return sum;
}
//TODO: 2/25 ,1247. 交换字符使得字符串相同
/**有两个长度相同的字符串 s1 和 s2，且它们其中 只含有 字符 "x" 和 "y"，你需要通过「交换字符」的方式使这两个字符串相同。

每次「交换字符」的时候，你都可以在两个字符串中各选一个字符进行交换。

交换只能发生在两个不同的字符串之间，绝对不能发生在同一个字符串内部。也就是说，我们可以交换 s1[i] 和 s2[j]，但不能交换 s1[i] 和 s1[j]。

最后，请你返回使 s1 和 s2 相同的最小交换次数，如果没有方法能够使得这两个字符串相同，则返回 -1 。
 */
int minimumSwap(string s1, string s2) {
    int cnt[2]{};
    for (int i = 0, n = s1.length(); i < n; ++i)
        if (s1[i] != s2[i])
            ++cnt[s1[i] % 2]; // x 和 y ASCII 值的二进制最低位不同
    int d = cnt[0] + cnt[1];
    return d % 2 != 0 ? -1 : d / 2 + cnt[0] % 2;
}
//TODO: 2/27 ,1144. 递减元素使数组呈锯齿状
/**给你一个整数数组 nums，每次 操作 会从中选择一个元素并 将该元素的值减少 1。

如果符合下列情况之一，则数组 A 就是 锯齿数组：

每个偶数索引对应的元素都大于相邻的元素，即 A[0] > A[1] < A[2] > A[3] < A[4] > ...
或者，每个奇数索引对应的元素都大于相邻的元素，即 A[0] < A[1] > A[2] < A[3] > A[4] < ...
返回将数组 nums 转换为锯齿数组所需的最小操作次数。
*/
int movesToMakeZigzag(vector<int>& nums) {
    vector<int> copy=nums;
    int cnt1=0;
    int cnt2=0;
    for(int i=0;i<nums.size();++i)
        if(i%2)
        {
            if(i+1<nums.size()&&nums[i]>=nums[i+1])
                cnt1+=nums[i]-(nums[i+1]-1),nums[i]=nums[i+1]-1;
            if(i>0&&nums[i]>=nums[i-1])
                cnt1+=nums[i]-(nums[i-1]-1),nums[i]=nums[i-1]-1;
        }
    nums=copy;
    for(int i=0;i<nums.size();++i)
        if(i%2==0)
        {
            if(i+1<nums.size()&&nums[i]>=nums[i+1])
                cnt2+=nums[i]-(nums[i+1]-1),nums[i]=nums[i+1]-1;
            if(i>0&&nums[i]>=nums[i-1])
                cnt2+=nums[i]-(nums[i-1]-1),nums[i]=nums[i-1]-1;
        }
    return min(cnt1,cnt2);
}
int main() {
    vector <int> nums = {9,6,1,6,2};
    cout << movesToMakeZigzag(nums);
    return 0;
}