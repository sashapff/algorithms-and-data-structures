#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <math.h>

using namespace std;
#define ll long long
#define vec vector

vec<vec<int>> prv;
vec<char> ans;

void dfs(int l, int r, int pos) {
    if (r == l) {
        for (int i = 0; i < pos; i++) {
            cout << ans[i];
        }
        cout << endl;
        return;
    }
    ans[pos] = '0';
    dfs(l, prv[l][r], pos + 1);
    ans[pos] = '1';
    dfs(prv[l][r] + 1, r, pos + 1);
}

int main() {
    freopen("optimalcode.in", "r", stdin);
    freopen("optimalcode.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n;
    cin >> n;
    vec<int> a = vec<int>(n);
    vec<int> pref = vec<int>(n + 1);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        pref[i + 1] = pref[i] + a[i];
    }
    if (n == 1) {
        cout << a[0] << endl << 0;
        return 0;
    }
    vec<vec<ll>> dp = vec<vec<ll>>(n);
    prv = vec<vec<int>>(n);
    for (int i = 0; i < n; i++) {
        dp[i] = vec<ll>(n);
        prv[i] = vec<int>(n);
        for (int j = 0; j < n; j++) {
            dp[i][j] = LONG_LONG_MAX;
        }
        dp[i][i] = 0;
        prv[i][i] = i;
    }
    ans = vec<char>(1e6);
    for (int len = 1; len < n; len++) {
        for (int i = 0; i + len < n; i++) {
        for (int k = prv[i][i + len - 1]; k <= min(prv[i + 1][i + len], i + len - 1); k++) {
                if (dp[i][k] + dp[k + 1][i + len] + pref[i + len + 1] - pref[i] < dp[i][i + len]) {
                    dp[i][i + len] = dp[i][k] + dp[k + 1][i + len] + pref[i + len + 1] - pref[i];
                    prv[i][i + len] = k;
                }
            }
        }
    }
    cout << dp[0][n - 1] << endl;
    dfs(0, n - 1, 0);
    return 0;
}
