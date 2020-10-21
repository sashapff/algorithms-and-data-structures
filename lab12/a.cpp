#include <iostream>
#include <vector>

using namespace std;

int main() {
    string a, b;
    cin >> a >> b;
    a += '$' + b;
    vector<int> pi(a.size());
    int j = 0;
    pi[0] = 0;
    for (int i = 1; i < (int) a.size(); i++) {
        while (j > 0 && a[i] != a[j]) {
            j = pi[j - 1];
        }
        if (a[i] == a[j]) {
            j++;
        }
        pi[i] = j;
    }
    vector<int> ans;
    for (int i = 0; i < (int) a.size(); i++) {
        if (pi[i] == (int) a.size() - (int) b.size() - 1) {
            ans.push_back(i - 2 * (a.size() - b.size() - 1) + 1);
        }
    }
    cout << ans.size() << '\n';
    for (auto i : ans) {
        cout << i << " ";
    }
    return 0;
}
