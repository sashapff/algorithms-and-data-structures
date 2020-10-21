#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <math.h>

using namespace std;
#define ll long long
int n, k;
ll m;
ll curmask = 0;

int get(int x, int y) {
    if (y % x == 0) {
        return x;
    }
    if (x == 1) {
        return y;
    }
    int a = x;
    int b = y - (y / x) * x;
    return get(b, a);
}

bool check(int x, int y) {
    if (x > y) {
        swap(x, y);
    }
    return get(x, y) >= k;
}

int main() {
    freopen("perm.in", "r", stdin);
    freopen("perm.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> n >> m >> k;
    m--;
    vector<int> a = vector<int>(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    ll size = 1 << n;
    vector<vector<ll>> dp = vector<vector<ll>>(size);
    for (int i = 0; i < size; i++) {
        dp[i] = vector<ll>(n);
    }
    for (int i = 0; i < n; i++) {
        dp[1 << i][i] = 1;
    }
    for (int mask = 0; mask < size; mask++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i != j && (mask & (1 << i)) && (mask & (1 << j)) && check(a[i], a[j])) {
                    dp[mask][i] += dp[mask - (1 << i)][j];
                }
            }
        }
    }
    vector<int> ans;
    int last = -1;
    for (int i = 0; i < n; i++) {
        ll cnt = 0;
        for (int j = 0; j < n; j++) {
            if (!(curmask & (1 << j))) {
                if (last == -1 || check(a[j], a[last])) {
                    cnt += dp[(size - 1) ^ (curmask)][j];
                }
            }
            if (cnt > m) {
                last = j;
                break;
            }
        }
        m -= cnt;
        m += dp[(size - 1) ^ (curmask)][last];
        if (last == -1) {
            cout << -1;
            return 0;
        }
        ans.push_back(last);
        curmask += (1 << last);
    }
    for (int i = 0; i < n; i++) {
        cout << a[ans[i]] << " ";
    }
    return 0;
}
