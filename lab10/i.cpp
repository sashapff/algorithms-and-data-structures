#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <stack>
#include <cmath>

using namespace std;

int n;
vector<set<int>> a;
vector<int> ans;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int d, k;
    cin >> d >> k;
    if (k == 1) {
        for (int i = 0; i < d; i++) {
            cout << i;
        }
        return 0;
    }
    n = static_cast<int>(pow(d, k - 1));
    a.resize(n);
    int mod = static_cast<int>(pow(d, k - 2));
    for (int i = 0; i < n; i++) {
        int pref = i % mod;
        for (int j = 0; j < d; j++) {
            if (!(i == 0 && (pref * d + j) % n == 0)) {
                a[i].insert((pref * d + j) % n);
            }
        }
    }
//    for (int i = 0; i < n; i++) {
//        cout << i << " ";
//        for (auto j : a[i]) {
//            cout << j << " ";
//        }
//        cout << '\n';
//    }
    stack<int> st;
    st.push(0);
    while (st.size() != 0) {
        int v = st.top();
        if (a[v].size() == 0) {
            ans.push_back(v);
            st.pop();
        } else {
            int u = 0;
            for (auto i : a[v]) {
                u = i;
                break;
            }
            a[v].erase(u);
            st.push(u);
        }
    }
    reverse(ans.begin(), ans.end());
//    for (auto i : ans) {
//        cout << i << " ";
//    }
    for (int i = 0; i < k - 1; i++) {
        cout << 0;
    }
    for (int i = 0; i < (int) ans.size(); i++) {
        cout << ans[i] % d;
    }
    return 0;
}
