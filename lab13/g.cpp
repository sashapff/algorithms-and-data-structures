#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <set>

using namespace std;
string s;
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
    cin >> s;
    int k = s.length();
    string t;
    cin >> t;
    s += '{';
    s += t;
    s += '`';
    classes =
            vector<vector<int>>((int) log2(s.size()) + 2, vector<int>(s.size()));
    vector<int> p = vector<int>(s.size());
    vector<int> buffer = vector<int>(28, 0);
    for (auto i : s) {
        buffer[i - '`']++;
    }
    for (int i = 1; i < 28; i++) {
        buffer[i] += buffer[i - 1];
    }
    for (int i = 0; i < (int) s.size(); i++) {
        p[--buffer[s[i] - '`']] = i;
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
    int len = 0;
    int start = 0;
    for (int i = 1; i < (int) s.size(); i++) {
        lcps[i - 1] = {lcp(p[i - 1], p[i]), {i - 1, p[i - 1]}};
        if (lcps[i - 1].first > len && ((p[i - 1] < k && p[i] > k) || (p[i - 1] > k && p[i] < k))) {
            len = (int) lcps[i - 1].first;
            start = p[i];
        }
    }
    for (int i = start; i < start + len; i++) {
        cout << s[i];
    }
    return 0;
}
