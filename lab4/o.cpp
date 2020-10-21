#include <iostream>
#include <vector>

using namespace std;
#define ll long long

int main() {
    freopen("bridge.in", "r", stdin);
    freopen("bridge.out", "w", stdout);
    ll a, x, b, y, len;
    cin >> x >> a >> y >> b >> len;
    vector<vector<pair<ll, ll>>> dp = vector<vector<pair<ll, ll>>>(x + 1);
    for (ll i = 0; i <= x; i++) {
        dp[i] = vector<pair<ll, ll>>(y + 1);
    }
    ll l = 0;
    ll r = x * a + y * b + 1;
    while (r - l > 1) {
        ll m = (l + r) / 2;
        for (ll i = 0; i <= x; i++) {
            for (ll j = 0; j <= y; j++) {
                dp[i][j] = make_pair(0, 0);
            }
        }
        for (ll i = 0; i <= x; i++) {
            for (ll j = 0; j <= y; j++) {
                if (i > 0 && dp[i - 1][j].second + a >= m) {
                    dp[i][j].first = dp[i - 1][j].first + 1;
                    dp[i][j].second = 0;
                } else if (i > 0) {
                    dp[i][j].first = dp[i - 1][j].first;
                    dp[i][j].second = dp[i - 1][j].second + a;
                }
                if (j > 0 && dp[i][j - 1].second + b >= m
                    && (dp[i][j - 1].first + 1 > dp[i][j].first
                        || (dp[i][j - 1].first + 1 == dp[i][j].first && dp[i][j].second < b))) {
                    dp[i][j].first = dp[i][j - 1].first + 1;
                    dp[i][j].second = 0;
                } else if (j > 0 && (dp[i][j - 1].first > dp[i][j].first
                                     || (dp[i][j - 1].first == dp[i][j].first
                                        && dp[i][j].second < dp[i][j - 1].second + b))) {
                    dp[i][j].first = dp[i][j - 1].first;
                    dp[i][j].second = dp[i][j - 1].second + b;
                }
            }
        }
        if (dp[x][y].first >= len) {
            l = m;
        } else {
            r = m;
        }
    }
    cout << l;
    return 0;
}
