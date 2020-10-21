#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <set>

using namespace std;

vector<vector<int>> a;
vector<int> used;
vector<bool> color;
bool flag = true;

void dfs(int u) {
    used[u] = 1;
    for (auto v : a[u]) {
        if (used[v] == 0) {
            color[v] = !color[u];
            dfs(v);
        } else {
            if (color[v] == color[u]) {
                flag = false;
            }
        }
    }
}

int main() {
    freopen("bipartite.in", "r", stdin);
    freopen("bipartite.out", "w", stdout);
    int n, m;
    cin >> n >> m;
    a.resize(n);
    used.resize(n, 0);
    color.resize(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        a[u - 1].push_back(v - 1);
        a[v - 1].push_back(u - 1);
    }
    for (int i = 0; i < n; i++) {
        if (used[i] == 0) {
            color[i] = 1;
            dfs(i);
        }
    }
    cout << (flag ? "YES" : "NO");
    return 0;
}

