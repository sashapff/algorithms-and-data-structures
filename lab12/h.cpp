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
    vector<long long> hash(s.size() + 1);
    vector<long long> deg(s.size() + 1);
    hash[0] = 0;
    deg[0] = 1;
    for (int i = 0; i < (int) s.size(); i++) {
        deg[i + 1] = deg[i] * 29;
        deg[i + 1] %= 1000000007;
        hash[i + 1] = hash[i] + (s[i] - 'a' + 1) * deg[i + 1];
        hash[i + 1] %= 1000000007;
    }
    int k;
    cin >> k;
    for (int i = 0; i < k; i++) {
        int l1, r1, l2, r2;
        cin >> l1 >> r1 >> l2 >> r2;
        cout << (((hash[r1] - hash[l1 - 1] + 1000000007) * deg[l2]) % 1000000007
        == ((hash[r2] - hash[l2 - 1] + 1000000007) * deg[l1]) % 1000000007 ? "Yes" : "No") << '\n';
    }
    return 0;
}
