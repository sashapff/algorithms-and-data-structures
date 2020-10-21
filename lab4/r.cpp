#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <math.h>
#include <queue>

using namespace std;
#define ll long long
#define vec vector

struct state {
    int sum, mod;
};

int main() {
    freopen("number.in", "r", stdin);
    freopen("number.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n;
    cin >> n;
    queue<state> q;
    state cur;
    cur.sum = 0;
    cur.mod = 0;
    q.push(cur);
    vec<vec<pair<int, int>>> prev = vec<vec<pair<int, int>>>(n + 1);
    vec<vec<int>> dp = vec<vec<int>>(n + 1);
    for (int i = 0; i <= n; i++) {
        prev[i] = vec<pair<int, int>>(n);
        dp[i] = vec<int>(n);
        for (int j = 0; j < n; j++) {
            dp[i][j] = -1;
        }
    }
    dp[0][0] = 0;
    while (!q.empty() && !(q.front().sum == n && q.front().mod == 0)) {
        state cur = q.front();
        q.pop();
        state newst;
        for (int i = 0; i <= 9; i++) {
            newst.sum = cur.sum + i;
            newst.mod = (cur.mod * 10 + i) % n;
            if (newst.sum <= n && dp[newst.sum][newst.mod] == -1) {
                dp[newst.sum][newst.mod] = i;
                prev[newst.sum][newst.mod] = {cur.sum, cur.mod};
                if (newst.sum == n && newst.mod == 0) {
                    break;
                }
                q.push(newst);
            }
        }
    }
    vector<int> ans;
    int sum = n;
    int mod = 0;
    while (!(sum == 0 && mod == 0)) {
        ans.push_back(dp[sum][mod]);
        int cursum = prev[sum][mod].first;
        mod = prev[sum][mod].second;
        sum = cursum;
    }
    reverse(ans.begin(), ans.end());
    for (int i : ans) {
        cout << i;
    }
    return 0;
}
