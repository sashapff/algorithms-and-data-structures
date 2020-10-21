#include <iostream>
#include <vector>

using namespace std;

int main() {
    string a, b;
    cin >> a >> b;
    string s = a + "#" + b;
    string rev_s;
    for (int i = (int) a.length() - 1; i >= 0; i--) {
        rev_s += a[i];
    }
    rev_s += "#";
    for (int i = (int) b.length() - 1; i >= 0; i--) {
        rev_s += b[i];
    }
    vector<int> z(s.size());
    vector<int> rev_z(rev_s.size());
    int l = 0;
    z[0] = 0;
    for (int i = 1; i < (int) s.size(); i++) {
        if (i >= l + z[l]) {
            z[i] = 0;
        } else {
            z[i] = min(z[i - l], z[l] - (i - l + 1));
        }
        while (i + z[i] < (int) s.size() && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        if (i + z[i] > l + z[l]) {
            l = i;
        }
    }
    l = 0;
    rev_z[0] = 0;
    for (int i = 1; i < (int) rev_s.size(); i++) {
        if (i >= l + rev_z[l]) {
            rev_z[i] = 0;
        } else {
            rev_z[i] = min(rev_z[i - l], rev_z[l] - (i - l + 1));
        }
        while (i + rev_z[i] < (int) rev_s.size() && rev_s[rev_z[i]] == rev_s[i + rev_z[i]]) {
            rev_z[i]++;
        }
        if (i + rev_z[i] > l + rev_z[l]) {
            l = i;
        }
    }
//    cout << s << '\n' << rev_s << '\n';
//    for (int i = 0; i < (int) s.size(); i++) {
//        cout << z[i] << " ";
//    }
//    cout << '\n';
//    for (int i = 0; i < (int) rev_s.size(); i++) {
//        cout << rev_z[i] << " ";
//    }
//    cout << '\n';
    vector<int> ans;
    for (int i = a.size() + 1; i <= (int) s.size() - (int) a.size(); i++) {
//        cout << i << " " << (int) s.size() - i - (int) a.size() << '\n';
//        cout << z[i] << rev_z[(int) s.size() - i + 1] << '\n';
        if ((z[i] + rev_z[(int) s.size() - i + 1] + 1 == (int) a.size()
                || z[i] == (int) a.size())) {
            ans.push_back(i - a.size());
        }
    }
    cout << ans.size() << '\n';
    for (int i : ans) {
        cout << i << " ";
    }
    return 0;
}
