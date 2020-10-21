#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <stack>

using namespace std;

int n;
vector<set<int>> a;
vector<int> ans;
vector<vector<int>> edges;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> n;
    a.resize(n);
    ans.reserve(1000000);
    edges.resize(n, vector<int>(n, 0));
    int beg = -1;
    int beg1 = -1;
    int end = -1;
    for (int i = 0; i < n; i++) {
        int k;
        cin >> k;
        for (int j = 0; j < k; j++) {
            int v;
            cin >> v;
            v--;
            a[i].insert(v);
            edges[i][v]++;
            edges[v][i]++;
            if (k > 0) {
                beg1 = i;
            }
        }
        if (k % 2 == 1) {
            if (beg == -1) {
                beg = i;
            } else {
                end = i;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            edges[i][j] /= 2;
        }
    }
    if (beg == -1) {
        beg = beg1;
    } else {
        a[beg].insert(end);
        a[end].insert(beg);
        edges[beg][end]++;
        edges[end][beg]++;
    }
//    findEulerPath(beg);
    stack<int> st;
    st.push(beg);
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
            edges[u][v]--;
            edges[v][u]--;
            if (edges[u][v] == 0) {
                a[u].erase(v);
                a[v].erase(u);
            }
            st.push(u);
        }
    }
    if (end == -1) {
        cout << ans.size() - 1 << '\n';
        for (auto i : ans) {
            cout << i + 1 << " ";
        }
    } else {
        cout << ans.size() - 2 << '\n';
        int ind = 0;
        for (int i = 0; i < (int) ans.size() - 1; i++) {
            if ((ans[i] == end && ans[i + 1] == beg) || (ans[i] == beg && ans[i + 1] == end)) {
                ind = i;
                break;
            }
        }
        for (int i = ind + 1; i < (int) ans.size() - 1; i++) {
            cout << ans[i] + 1 << " ";
        }
        for (int i = 0; i <= ind; i++) {
            cout << ans[i] + 1 << " ";
        }
    }
    return 0;
}
