#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    string s;
    cin >> s;
    vector<vector<long long>> ans(s.length(), vector<long long>(s.length()));
    for (int i = 0; i < (int) s.length(); i++) {
        ans[i][i] = 1;
        string p = s.substr(0, i + 1);
        reverse(p.begin(), p.end());
        vector<int> pi(p.size());
        pi[0] = 0;
        int j = 0;
        int mx = 0;
        for (int k = 1; k < (int) p.size(); k++) {
            while (j > 0 && p[k] != p[j]) {
                j = pi[j - 1];
            }
            if (p[k] == p[j]) {
                j++;
            }
            pi[k] = j;
            mx = max(mx, pi[k]);
            ans[i - k][i] = ans[i - k][i - 1] + k - mx + 1;
        }
    }
    int k;
    cin >> k;
    for (int i = 0; i < k; i++) {
        int l, r;
        cin >> l >> r;
        cout << ans[l - 1][r - 1] << '\n';
    }
    return 0;
}
