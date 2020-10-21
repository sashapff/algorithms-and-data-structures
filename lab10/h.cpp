#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <stack>

using namespace std;

int n, m;
vector<multiset<int>> a;
vector<int> ans;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> n >> m;
    a.resize(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        a[u].insert(v);
        a[v].insert(u);
    }
    vector<int> odd;
    vector<bool> is_odd(n, false);
    vector<int> extra(n, -1);
    for (int i = 0; i < n; i++) {
        if (a[i].size() % 2 == 1) {
            odd.push_back(i);
            is_odd[i] = true;
        }
    }
    for (int i = 0; i < (int) odd.size(); i += 2) {
        a[odd[i]].insert(odd[i + 1]);
        a[odd[i + 1]].insert(odd[i]);
        extra[odd[i]] = odd[i + 1];
        extra[odd[i + 1]] = odd[i];
    }
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
            a[u].erase(a[u].find(v));
            a[v].erase(a[v].find(u));
            st.push(u);
        }
    }
    if (odd.size() > 0) {
        cout << odd.size() / 2 << '\n';
        vector<int> buff;
        int j = 0;
        while (extra[ans[j]] != ans[j + 1]) {
            buff.push_back(ans[j + 1]);
            j++;
        }
        extra[ans[j]] = -1;
        extra[ans[j + 1]] = -1;
        j++;
        for (int k = 1; k < (int) odd.size() / 2; k++) {
            while (extra[ans[j]] != ans[j + 1]) {
                cout << ans[j] + 1 << " ";
                j++;
            }
            extra[ans[j]] = -1;
            extra[ans[j + 1]] = -1;
            cout << ans[j] + 1 << " ";
            j++;
            cout << '\n';
        }
        while (j < (int) ans.size()) {
            cout << ans[j] + 1 << " ";
            j++;
        }
        for (auto i : buff) {
            cout << i + 1 << " ";
        }
//        cout << '\n';
//        for (auto i : ans) {
//            cout << i + 1 << " ";
//        }
    } else {
        cout << 1 << '\n';
        for (auto i : ans) {
            cout << i + 1 << " ";
        }
    }
    return 0;
}
