#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <set>

using namespace std;
vector<int> s;
int m;
vector<vector<int>> classes;

int lcp(int i, int j) {
    int ans = 0;
    for (int k = (int) log2(s.size()); k >= 0; k--) {
        if (classes[k][i] == classes[k][j]) {
            int delta = 1 << k;
            ans += delta;
            i += delta;
            j += delta;
        }
    }
    return ans;
}

int main() {
    int n;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        s.push_back(x);
    }
    s.push_back(0);
    m++;
    classes =
            vector<vector<int>>((int) log2(s.size()) + 2, vector<int>(s.size()));
    vector<int> p = vector<int>(s.size());
    vector<int> buffer = vector<int>(m, 0);
    for (auto i : s) {
        buffer[i]++;
    }
    for (int i = 1; i < m; i++) {
        buffer[i] += buffer[i - 1];
    }
    for (int i = 0; i < (int) s.size(); i++) {
        p[--buffer[s[i]]] = i;
    }
    classes[0][p[0]] = 0;
    int num = 1;
    for (int i = 1; i < (int) s.size(); i++) {
        if (s[p[i]] != s[p[i - 1]]) {
            num++;
        }
        classes[0][p[i]] = num - 1;
    }
    for (int i = 0; (1 << i) < (int) s.size(); i++) {
        vector<int> p_buf = vector<int>(s.size());
        buffer.clear();
        buffer.resize(num, 0);
        for (int j = 0; j < (int) s.size(); j++) {
            p_buf[j] = (p[j] + s.size() - (1 << i)) % s.size();
            buffer[classes[i][p_buf[j]]]++;
        }
        for (int j = 1; j < num; j++) {
            buffer[j] += buffer[j - 1];
        }
        for (int j = (int) s.size() - 1; j >= 0; j--) {
            p[--buffer[classes[i][p_buf[j]]]] = p_buf[j];
        }
        classes[i + 1][p[0]] = 0;
        num = 1;
        for (int j = 1; j < (int) s.size(); j++) {
            if (classes[i][p[j]] != classes[i][p[j - 1]]
                || classes[i][(p[j] + (1 << i)) % s.size()]
                   != classes[i][(p[j - 1] + (1 << i)) % s.size()]) {
                num++;
            }
            classes[i + 1][p[j]] = num - 1;
        }
    }
    vector<pair<long long, pair<int, int>>> lcps
            = vector<pair<long long, pair<int, int>>>(s.size() - 1);
    for (int i = 1; i < (int) s.size(); i++) {
        lcps[i - 1] = {lcp(p[i - 1], p[i]), {i - 1, p[i - 1]}};
    }
    sort(lcps.begin(), lcps.end());
    set<int> taken;
    set<int> rev_taken;
    long long ans = 0;
    int len = 0;
    int start = 0;
    for (auto &lcp : lcps) {
        int r, l;
        if (taken.upper_bound(lcp.second.first) != taken.end()) {
            r = *taken.upper_bound(lcp.second.first);
        } else {
            r = s.size() - 1;
        }
        if (rev_taken.upper_bound(-lcp.second.first) != rev_taken.end()) {
            l = -(*rev_taken.upper_bound(-lcp.second.first));
        } else {
            l = -1;
        }
        if (ans < lcp.first * (r - l)) {
            ans = lcp.first * (r - l);
            len = (int) lcp.first;
            start = lcp.second.second;
        }
        taken.insert(lcp.second.first);
        rev_taken.insert(-lcp.second.first);
    }
    if (ans < s.size() - 1) {
        ans = s.size() - 1;
        len = s.size() - 1;
        start = 0;
    }
    cout << ans << '\n' << len << '\n';
    for (int i = start; i < start + len; i++) {
        cout << s[i] << " ";
    }
    return 0;
}
