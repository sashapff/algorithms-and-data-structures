#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    freopen("levenshtein.in", "r", stdin);
    freopen("levenshtein.out", "w", stdout);
    string s, p;
    cin >> s >> p;
    int n = (int) s.length();
    int m = (int) p.length();
    vector<vector<long long>> dp = vector<vector<long long>>(n + 1);
    for (int i = 0; i <= n; i++) {
        dp[i] =  vector<long long>(m + 1);
        dp[i][0] = i;
    }
    for (int i = 0; i <= m; i++) {
        dp[0][i] = i;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            dp[i][j] = (long long) 1e18;
            dp[i][j] = min(dp[i][j], dp[i][j - 1] + 1);
            if (s[i - 1] == p[j - 1]) {
                dp[i][j] = min(dp[i][j], dp[i - 1][j - 1]);
            } else {
                dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + 1);
            }
            dp[i][j] = min(dp[i][j], dp[i - 1][j] + 1);
        }
    }
    cout << dp[n][m];
    return 0;
}
