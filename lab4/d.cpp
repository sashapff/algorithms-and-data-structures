#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    freopen("knapsack.in", "r", stdin);
    freopen("knapsack.out", "w", stdout);
    int n, k;
    cin >> n >> k;
    vector<int> m = vector<int>(n);
    vector<int> c = vector<int>(n);
    for (int i = 0; i < n; i++) {
        cin >> m[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }
    vector<vector<int>> dp = vector<vector<int>>(n + 1);
    for (int i = 0; i <= n; i++) {
        dp[i] = vector<int>(k + 1);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= k; j++) {
            if (j >= m[i - 1] && dp[i - 1][j - m[i - 1]] + c[i - 1] > dp[i - 1][j]) {
                dp[i][j] = dp[i - 1][j - m[i - 1]] + c[i - 1];
            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }
//    cout << dp[n][k];
    vector<int> ans;
    while (dp[n][k] != 0) {
        if (dp[n][k] == dp[n - 1][k]) {
            n--;
        } else {
            ans.push_back(n - 1);
            n--;
            k -= m[n];
        }
    }
    cout << ans.size() << endl;
    reverse(ans.begin(), ans.end());
    for (int i : ans) {
        cout << i + 1 << " ";
    }
    return 0;
}
