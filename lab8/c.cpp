#include <iostream>
#include <vector>
#include <deque>

using namespace std;

vector<vector<pair<int, int>>> dir;
vector<int> used;
deque<int> q;

void dfs(int u) {
    used[u] = 1;
    for (auto v : dir[u]) {
        if (used[v.first] == 0) {
            dfs(v.first);
        }
    }
    q.push_front(u);
}

int main() {
//    freopen("shortpath.in", "r", stdin);
//    freopen("shortpath.out", "w", stdout);
    int n, m, s = 0, t = 0;
    cin >> n >> m >> s >> t;
    s--;
    t--;
    dir.resize(n);
    used.resize(n, 0);
    for (int i = 0; i < m; i++) {
        int u, v, w = 0;
        cin >> u >> v >> w;
        dir[u - 1].push_back(make_pair(v - 1, w));
    }
    for (int i = 0; i < n; i++) {
        if (used[i] == 0) {
            dfs(i);
        }
    }
    int j = 0;
    int num_s = 0;
    int num_t = 0;
    vector<int> tc;
    for (auto i : q) {
        if (i == s) {
            num_s = j;
        }
        if (i == t) {
            num_t = j;
        }
        j++;
        tc.push_back(i);
    }
    vector<long long> dp(n, INT32_MAX);
    dp[tc[num_s]] = 0;
    for (int i = num_s; i < n; i++) {
        for (auto v : dir[tc[i]]) {
            dp[v.first] = min(dp[v.first], dp[tc[i]] + v.second);
        }
    }
    if (dp[tc[num_t]] != INT32_MAX) {
        cout << dp[tc[num_t]];
    } else {
        cout << "Unreachable";
    }
    return 0;
}
