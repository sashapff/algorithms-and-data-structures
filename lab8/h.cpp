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
vector<int> ans;

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
                    ans.push_back(v.second);
                }
            } else {
                up[u] = min(up[u], tin[v.first]);
            }
        }
    }
    used[u] = 2;
}

int main() {
    freopen("bridges.in", "r", stdin);
    freopen("bridges.out", "w", stdout);
    int n, m;
    cin >> n >> m;
    a.resize(n);
    used.resize(n, 0);
    tin.resize(n);
    up.resize(n, INT32_MAX);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        a[u - 1].push_back(make_pair(v - 1, i + 1));
        a[v - 1].push_back(make_pair(u - 1, i + 1));
    }
    for (int i = 0; i < n; i++) {
        if (used[i] == 0) {
            dfs(i, -1);
        }
    }
    cout << ans.size() << endl;
    sort(ans.begin(), ans.end());
    for (auto i : ans) {
        cout << i << " ";
    }
    return 0;
}

