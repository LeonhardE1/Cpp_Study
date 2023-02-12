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
}

//TODO:2/11, 1138. 字母板上的路径
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
int main() {
    string target = "leet";
    cout << alphabetBoardPath(target);
    return 0;
}