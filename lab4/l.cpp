#include <iostream>
#include <vector>
#include <algorithm>


#define ll long long
using namespace std;

vector<vector<ll>> dp;
vector<vector<pair<int, ll>>> a;
vector<bool> used;

void dfs(int u) {
    used[u] = true;
    ll delta = 0;
    for (auto v : a[u]) {
        if (!used[v.first]) {
            dfs(v.first);
            dp[u][0] += max(dp[v.first][0], dp[v.first][1]);
            dp[u][1] += max(dp[v.first][0], dp[v.first][1]);
            if (v.second - max(dp[v.first][0], dp[v.first][1]) + dp[v.first][0] > delta) {
                delta = v.second - max(dp[v.first][0], dp[v.first][1]) + dp[v.first][0];
            }
        }
    }
    dp[u][1] += delta;
    used[u] = false;
}

int main() {
    freopen("matching.in", "r", stdin);
    freopen("matching.out", "w", stdout);
    int n;
    cin >> n;
    a = vector<vector<pair<int, ll>>>(n);
    dp = vector<vector<ll>>(n);
    used = vector<bool>(n);
    for (int i = 0; i < n; i++) {
        dp[i] = vector<ll>(2);
        used[i] = false;
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--;
        v--;
        a[u].push_back(make_pair(v, w));
        a[v].push_back(make_pair(u, w));
    }
    dfs(0);
    cout << max(dp[0][0], dp[0][1]);
    return 0;
}
