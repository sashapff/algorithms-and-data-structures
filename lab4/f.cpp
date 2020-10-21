#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    string s, p;
    getline(cin, s);
    getline(cin, p);
    s += '~';
    p += '~';
    vector<vector<bool>> dp = vector<vector<bool>>(s.length() + 1);
    for (int i = 0; i <= (int) s.length(); i++) {
        dp[i] = vector<bool>(p.length() + 1);
    }
    dp[0][0] = 1;
    for (int j = 1; j <= (int) p.length(); j++) {
        for (int i = 1; i <= (int) s.length(); i++) {
            if (s[i - 1] == p[j - 1] || s[i - 1] == '?') {
                dp[i][j] = dp[i - 1][j - 1];
                if (i - 2 >= 0 && s[i - 2] == '*') {
                    dp[i][j] = dp[i][j] | dp[i - 1][j];
                }
            }
            if (s[i - 1] == '*') {
                if (i - 2 >= 0 && s[i - 2] == '*') {
                    dp[i][j] = dp[i][j] | dp[i - 1][j];
                }
                dp[i][j] = dp[i][j] | dp[i - 1][j - 1] | dp[i][j - 1];
            }
        }
    }
    cout << (dp[s.length()][p.length()] ? "YES" : "NO");
    return 0;
}
