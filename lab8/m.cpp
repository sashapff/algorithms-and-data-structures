#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("tiv.in", "r", stdin);
    freopen("tiv.out", "w", stdout);
    int n = 26;
    int k;
    cin >> k;
    vector<string> s(k);
    for (int i = 0; i < k; i++) {
        cin >> s[i];
    }
    vector<vector<int>> a(n);
    vector<int> b(n);
    vector<bool> can_be_zero(n, true);
    int ii = 0;
    int len = 1;
    while (ii < k) {
        if (ii > 0 && s[ii].size() < s[ii - 1].size()) {
            cout << "No\n";
            return 0;
        }
        while (ii < k && (int) s[ii].size() == len) {
            if (len > 1) {
                can_be_zero[s[ii][0] - 'a'] = false;
            }
            if (ii > 0 && s[ii - 1].size() == s[ii].size()) {
                int j = 0;
                while (j < len && s[ii - 1][j] == s[ii][j]) {
                    j++;
                }
                if (j == len) {
                    cout << "No\n";
                    return 0;
                }
                a[s[ii - 1][j] - 'a'].push_back(s[ii][j] - 'a');
                b[s[ii][j] - 'a']++;
            }
            ii++;
        }
        len++;
    }
    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (b[i] == 0 && can_be_zero[i]) {
            q.push(i);
        }
    }
    for (int i = 0; i < n; i++) {
        if (b[i] == 0 && !can_be_zero[i]) {
            if (q.size() == 0) {
                cout << "No\n";
                return 0;
            }
            q.push(i);
        }
    }
    vector<int> ans;
    while (q.size() > 0) {
        int u = q.front();
        q.pop();
        for (int v : a[u]) {
            b[v]--;
            if (b[v] == 0) {
                q.push(v);
            }
        }
        ans.push_back(u);
    }
    if ((int) ans.size() != n) {
        cout << "No\n";
    } else {
        cout << "Yes\n";
        vector<int> d(n);
        int cnt = 0;
        for (auto i : ans) {
            d[i] = cnt++;
        }
        for (auto i : d) {
            cout << i << " ";
        }
    }
    return 0;
}
