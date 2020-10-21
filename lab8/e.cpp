#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

vector<vector<int>> a;
vector<int> used;
int on_cycle = -1;
vector<int> cur;
vector<int> ans;

void dfs(int u) {
    cur.push_back(u);
    used[u] = 1;
    for (auto v : a[u]) {
        if (used[v] == 0) {
            dfs(v);
        } else if (used[v] == 1) {
            on_cycle = v;
            int i = static_cast<int>(cur.size() - 1);
            ans.resize(0);
            while (cur[i] != v) {
                ans.push_back(cur[i]);
                i--;
            }
            ans.push_back(v);
        }
    }
    used[u] = 2;
    cur.pop_back();
}

int main() {
    freopen("cycle.in", "r", stdin);
    freopen("cycle.out", "w", stdout);
    int n, m;
    cin >> n >> m;
    a.resize(n);
    used.resize(n, 0);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        a[u - 1].push_back(v - 1);
    }
    for (int i = 0; i < n; i++) {
        if (used[i] == 0) {
            dfs(i);
        }
    }
    if (on_cycle == -1) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
        reverse(ans.begin(), ans.end());
        for (auto i : ans) {
            cout << i + 1 << " ";
        }
    }
    return 0;
}
