#include <iostream>
#include <vector>

using namespace std;
#define ll long long

int main() {
    int n;
    cin >> n;
    ll mod = (ll) 1e9;
    vector<ll> a = vector<ll>(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<vector<ll>> dp = vector<vector<ll>>(n + 1);
    for (int i = 0; i <= n; i++) {
        dp[i] = vector<ll>(n + 1);
    }
    for (int len = 1; len <= n; len++) {
        for (int i = 0; i + len <= n; i++) {
            dp[i][len] = dp[i][len - 1] + dp[i + 1][len - 1];
            if (len >= 2) {
                dp[i][len] -= dp[i + 1][len - 2];
            }
            if (a[i] == a[i + len - 1]) {
                if (len >= 2) {
                    dp[i][len] += dp[i + 1][len - 2];
                }
                dp[i][len]++;
            }
            dp[i][len] = (dp[i][len] + mod) % mod;
        }
    }
    cout << dp[0][n];
    return 0;
}
