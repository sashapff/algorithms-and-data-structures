#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;
#define ll long long
int dp[10005][2];
int dpRev[10005][2];


int get(string p, string s) {
    int n = (int) s.size();
    int m = (int) p.size();
    for (int i = 0; i <= n; i++) {
        dp[i][0] = 0;
        dp[i][1] = 0;
    }
    for (int j = 1; j <= m; j++) {
        dp[0][1] = 0;
        for (int i = 1; i <= n; i++) {
            dp[i][0] = dp[i][1];
            if (s[i - 1] == p[j - 1]) {
                dp[i][1] = dp[i - 1][0] + 1;
            } else {
                dp[i][1] = max(dp[i][0], dp[i - 1][1]);
            }
        }
    }
    return max(dp[n][0], dp[n][1]);
}

int getReverse(string p, string s) {
    int n = (int) s.size();
    int m = (int) p.size();
    for (int i = 0; i <= n; i++) {
        dpRev[i][0] = 0;
        dpRev[i][1] = 0;
    }
    for (int j = 1; j <= m; j++) {
        dpRev[0][1] = 0;
        for (int i = 1; i <= n; i++) {
            dpRev[i][0] = dpRev[i][1];
            if (s[n - i] == p[m - j]) {
                dpRev[i][1] = dpRev[i - 1][0] + 1;
            } else {
                dpRev[i][1] = max(dpRev[i][0], dpRev[i - 1][1]);
            }
        }
    }
    return max(dpRev[n][0], dpRev[n][1]);
}

string find(string s, string p) {
    if (s.size() == 0) {
        return "";
    }
    if (s.size() == 1) {
        for (int i = 0; i < (int) p.size(); i++) {
            if (s[0] == p[i]) {
                return s;
            }
        }
        return "";
    }
    ll len = 0;
    int ind = 0;
    get(s.substr(0, s.size() / 2), p);
    getReverse(s.substr(s.size() / 2, s.size()), p);
    for (int i = 0; i <= (int) p.size(); i++) {
        int sum = max(dp[i][0], dp[i][1]) + max(dpRev[p.size() - i][0], dpRev[p.size() - i][1]);
        if (sum > len) {
            len = sum;
            ind = i;
        }
    }
    string first = find(s.substr(0, s.size() / 2), p.substr(0, ind));
    string second = find(s.substr(s.size() / 2, s.size()), p.substr(ind, p.size()));
    return first + second;
}

int main() {
//    freopen("meetings.in", "r", stdin);
//    freopen("meetings.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    string s, p;
    getline(cin, s);
    getline(cin, p);
    cout << find(s, p);
    return 0;
}
