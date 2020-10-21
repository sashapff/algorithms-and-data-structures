#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    freopen("salesman.in", "r", stdin);
    freopen("salesman.out", "w", stdout);
    int n, m;
    cin >> n >> m;
    vector<vector<long long>> a = vector<vector<long long>>(n);
    for (int i = 0; i < n; i++) {
        a[i] = vector<long long>(n);
        for (int j = 0; j < n; j++) {
            a[i][j] = (long long) 1e18;
        }
    }
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--;
        v--;
        a[u][v] = w;
        a[v][u] = w;
    }
    vector<vector<long long>> dp = vector<vector<long long>>(n);
    int size = (1 << (n)) - 1;
    for (int i = 0; i < n; i++) {
        dp[i] = vector<long long>(size + 1);
        for (int j = 0; j <= size; j++) {
            dp[i][j] = (long long) 1e18;
        }
        dp[i][1 << i] = 0;
        dp[i][0] = 0;
    }
    for (int mask = 0; mask <= size; mask++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j && (mask & (1 << i)) && (mask & (1 << j))) {
                    dp[i][mask] = min(dp[i][mask], dp[j][mask - (1 << i)] + a[i][j]);
                }
            }
        }
    }
    long long ans = (long long) 1e18;
    for (int i = 0; i < n; i++) {
        ans = min(ans, dp[i][size]);
    }
    cout << (ans < (long long) 1e18 ? ans : -1);
    return 0;
}
