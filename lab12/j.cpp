#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    string s;
    cin >> s;
    vector<int> pi(s.size());
    long long ans = 0;
    for (int i = 1; i <= (int) s.size(); i++) {
        string p = s.substr(0, i);
        reverse(p.begin(), p.end());
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
        }
        ans += (int) p.size() - mx;
        cout << ans << '\n';
    }
    return 0;
}
