#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

vector<vector<pair<int, int>>> a;
vector<int> used;
vector<int> tin;
vector<int> up;
int t = 0;
vector<bool> is_bridge;
int c = 1;
vector<int> color;

void dfs(int u, int prev) {
    used[u] = 1;
    tin[u] = t++;
    up[u] = tin[u];
    for (auto v : a[u]) {
        if (v.first != prev) {
            if (used[v.first] == 0) {
                dfs(v.first, u);
                up[u] = min(up[u], up[v.first]);
                if (up[v.first] > tin[u]) {
                    is_bridge[v.second] = true;
                }
            } else {
                up[u] = min(up[u], tin[v.first]);
            }
        }
    }
    used[u] = 2;
}

void dfs2(int u) {
    used[u] = c;
    for (auto v : a[u]) {
        if (used[v.first] == 0 && !is_bridge[v.second]) {
            dfs2(v.first);
        }
    }
}

int main() {
    freopen("bicone.in", "r", stdin);
    freopen("bicone.out", "w", stdout);
    int n, m;
    cin >> n >> m;
    a.resize(n);
    used.resize(n, 0);
    tin.resize(n);
    up.resize(n, INT32_MAX);
    is_bridge.resize(m, false);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        a[u - 1].push_back(make_pair(v - 1, i));
        a[v - 1].push_back(make_pair(u - 1, i));
    }
    for (int i = 0; i < n; i++) {
        if (used[i] == 0) {
            dfs(i, -1);
        }
    }
    for (int i = 0; i < n; i++) {
        used[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        if (used[i] == 0) {
            dfs2(i);
            c++;
        }
    }
    cout << c - 1 << endl;
    for (auto i : used) {
        cout << i << " ";
    }
    return 0;
}
