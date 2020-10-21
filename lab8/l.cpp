#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <set>

using namespace std;

vector<vector<pair<int, int>>> a;
vector<int> used;
vector<int> tin;
vector<int> up;
int t = 0;
vector<int> color;

void dfs(int u, int prev) {
    used[u] = 1;
    tin[u] = t++;
    up[u] = tin[u];
    int cnt = 0;
    for (auto v : a[u]) {
        if (v.first != prev) {
            if (used[v.first] == 0) {
                dfs(v.first, u);
                up[u] = min(up[u], up[v.first]);
                cnt++;
            } else {
                up[u] = min(up[u], tin[v.first]);
            }
        }
    }
}

int maxclr = 0;

void dfs2(int u, int prev, int clr) {
    used[u] = 1;
    for (auto v : a[u]) {
        if (v.first != prev) {
            if (used[v.first] == 0) {
                if (up[v.first] >= tin[u]) {
                    color[v.second] = maxclr++;
                    dfs2(v.first, u, color[v.second]);
                } else {
                    color[v.second] = clr;
                    dfs2(v.first, u, color[v.second]);
                }
            } else if (tin[v.first] < tin[u]) {
                color[v.second] = clr;
            }
        }
    }
}

int main() {
    freopen("biconv.in", "r", stdin);
    freopen("biconv.out", "w", stdout);
    int n, m;
    cin >> n >> m;
    a.resize(n);
    used.resize(n, 0);
    tin.resize(n);
    up.resize(n, INT32_MAX);
    color.resize(m, -1);
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
//    cout << ans.size() << endl;
//    sort(ans.begin(), ans.end());
//    for (auto i : ans) {
//        cout << i + 1 << endl;
//    }
    for (int i = 0; i < n; i++) {
        used[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        if (used[i] == 0) {
            if (a[i].size() > 0) {
                maxclr++;
            }
            dfs2(i, -1, maxclr);
        }
    }
    cout << max(maxclr - 1, 0) << '\n';
    for (auto i : color) {
        cout << i << " ";
    }
    return 0;
}
