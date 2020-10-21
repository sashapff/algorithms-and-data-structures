#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> last;
vector<vector<char>> c;

void getAns(int l, int r) {
    if (r - l <= 1) {
        return;
    }
    int i = last[l][r - l + 1] + 1;
    if (i - l > 1) {
        c[l].push_back('(');
        c[i].push_back(')');
    }
    if (r + 1 - i > 1) {
        c[i].push_back('(');
        c[r + 1].push_back(')');
    }
    getAns(l, i - 1);
    getAns(i, r);
}
int main() {
    freopen("matrix.in", "r", stdin);
    freopen("matrix.out", "w", stdout);
    int n;
    cin >> n;
    if (n == 1) {
        cout << 'A';
        return 0;
    }
    vector<pair<long long, long long>> a = vector<pair<long long, long long>>(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
    }
    vector<vector<long long>> dp = vector<vector<long long>>(n);
    last = vector<vector<int>>(n);
    c = vector<vector<char>>(n + 1);
    for (int i = 0; i < n; i++) {
        dp[i] = vector<long long>(n + 1);
        last[i] = vector<int>(n + 1);
    }
    for (int k = 2; k <= n; k++) {
        for (int i = 0; i + k <= n; i++) {
            dp[i][k] = (long long) 1e18;
            int index = i;
            for (int j = 1; j < k; j++) {
                long long cur = dp[i][j] + dp[i + j][k - j]
                                + a[i].first * a[i + j - 1].second * a[i + k - 1].second;
                if (dp[i][k] > cur) {
                    dp[i][k] = cur;
                    index = i + j - 1;
                }
            }
            last[i][k] = index;
        }
    }
    c[0].push_back('(');
    c[n].push_back(')');
    getAns(0, n - 1);
    for (int i = 0; i < n; i++) {
        sort(c[i].begin(), c[i].end());
        reverse(c[i].begin(), c[i].end());
        for (int j = 0; j < (int) c[i].size(); j++) {
            cout << c[i][j];
        }
        cout << 'A';
    }
    sort(c[n].begin(), c[n].end());
    reverse(c[n].begin(), c[n].end());
    for (int j = 0; j < (int) c[n].size(); j++) {
        cout << c[n][j];
    }
    return 0;
}
