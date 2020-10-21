#include <iostream>
#include <vector>

using namespace std;

int main() {
    string a, b;
    cin >> a >> b;
    a += '$' + b;
    vector<int> z(a.size());
    int l = 0;
    z[0] = 0;
    for (int i = 1; i < (int) a.size(); i++) {
        if (i >= l + z[l]) {
            z[i] = 0;
        } else {
            z[i] = min(z[i - l], z[l] - (i - l + 1));
        }
        while (i + z[i] < (int) a.size() && a[z[i]] == a[i + z[i]]) {
            z[i]++;
        }
        if (i + z[i] > l + z[l]) {
            l = i;
        }
    }
    vector<int> ans;
    for (int i = 0; i < (int) a.size(); i++) {
        if (z[i] == (int) a.size() - (int) b.size() - 1) {
            ans.push_back(i - (a.size() - b.size() - 1));
        }
    }
    cout << ans.size() << '\n';
    for (auto i : ans) {
        cout << i << " ";
    }
    return 0;
}
