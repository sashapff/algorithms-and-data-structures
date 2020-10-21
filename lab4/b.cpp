#include <iostream>
#include <vector>

using namespace std;

vector<int> dp;
vector<int> prv;
vector<int> a;


int binarySearch(int x) {
    int l = -1;
    int r = (int) dp.size();
    while (r - l > 1) {
        int m = (l + r) / 2;
        if (x <= dp[m]) {
            r = m;
        } else {
            l = m;
        }
    }
    return r;
}

void getAns(int x) {
    if (x == -1) {
        return;
    }
    getAns(prv[x]);
    cout << a[x] << " ";
}

int main() {
    freopen("lis.in", "r", stdin);
    freopen("lis.out", "w", stdout);
    int n;
    cin >> n;
    a = vector<int>(n);
    vector<int> cur = vector<int>(n + 1);
    prv = vector<int>(n);
    dp = vector<int>(n + 1);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        dp[i] = INT32_MAX;
    }
    dp[0] = INT32_MIN;
    dp[n] = INT32_MAX;
    cur[0] = -1;
    int last = 0;
    for (int i = 0; i < n; i++) {
        int j = binarySearch(a[i]);
        if (dp[j - 1] < a[i] && dp[j] > a[i]) {
            dp[j] = a[i];
            cur[j] = i;
            prv[i] = cur[j - 1];
            last = max(last, j);
        }
    }
    cout << last << endl;
    getAns(cur[last]);
    return 0;
}
