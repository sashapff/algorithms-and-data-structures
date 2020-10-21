#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    string s;
    cin >> s;
    s += '`';
    vector<int> classes = vector<int>(s.size());
    vector<int> p = vector<int>(s.size());
    vector<int> buffer = vector<int>(27, 0);
    for (auto i : s) {
        buffer[i - '`']++;
    }
    for (int i = 1; i < 27; i++) {
        buffer[i] += buffer[i - 1];
    }
    for (int i = 0; i < (int) s.size(); i++) {
        p[--buffer[s[i] - '`']] = i;
    }
    classes[p[0]] = 0;
    int num = 1;
    for (int i = 1; i < (int) s.size(); i++) {
        if (s[p[i]] != s[p[i - 1]]) {
            num++;
        }
        classes[p[i]] = num - 1;
    }
    for (int i = 0; (1 << i) < (int) s.size(); i++) {
        vector<int> p_buf = vector<int>(s.size());
        vector<int> new_classes = vector<int>(s.size());
        buffer.clear();
        buffer.resize(num, 0);
        for (int j = 0; j < (int) s.size(); j++) {
            p_buf[j] = (p[j] + s.size() - (1 << i)) % s.size();
            buffer[classes[p_buf[j]]]++;
        }
        for (int j = 1; j < num; j++) {
            buffer[j] += buffer[j - 1];
        }
        for (int j = (int) s.size() - 1; j >= 0; j--) {
            p[--buffer[classes[p_buf[j]]]] = p_buf[j];
        }
        new_classes[p[0]] = 0;
        num = 1;
        for (int j = 1; j < (int) s.size(); j++) {
            if (classes[p[j]] != classes[p[j - 1]]
                || classes[(p[j] + (1 << i)) % s.size()]
                   != classes[(p[j - 1] + (1 << i)) % s.size()]) {
                num++;
            }
            new_classes[p[j]] = num - 1;
        }
        for (int j = 0; j < (int) s.size(); j++) {
            classes[j] = new_classes[j];
        }
    }
    for (int i = 1; i < (int) s.size(); i++) {
        cout << p[i] + 1 << ' ';
    }
    cout << '\n';
    vector<int> rev = vector<int>(s.size());
    vector<int> lcp = vector<int>(s.size());
    for (int i = 0; i < (int) s.size(); i++) {
        rev[p[i]] = i;
    }
    int k = 0;
    for (int i = 0; i < (int) s.size(); i++) {
        if (k > 0) {
            k--;
        }
        if (rev[i] == (int) s.size() - 1) {
            lcp[s.size() - 1] = -1;
            k = 0;
        } else {
            int j = p[rev[i] + 1];
            while (i + k < (int) s.size() && j + k < (int) s.size()
                   && s[i + k] == s[j + k]) {
                k++;
            }
            lcp[rev[i]] = k;
        }
    }
    for (int i = 1; i < (int) s.size() - 1; i++) {
        cout << lcp[i] << " ";
    }
    return 0;
}
