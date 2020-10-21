#include<iostream>
#include<vector>

using namespace std;

int n, m;
vector<vector<int>> a;
vector<vector<int>> f;
vector<bool> used;
vector<int> nxt;

bool clean() {
    for (int i = 0; i < n; i++) {
        used[i] = false;
    }
    return true;
}

bool dfs(int u) {
    if (u == n - 1) {
        return true;
    }
    used[u] = true;
    for (int v = 0; v < n; v++) {
        if (a[u][v] - f[u][v] > 0 && !used[v] && dfs(v)) {
            nxt[u] = v;
            return true;
        }
    }
    return false;
}

int main() {
    cin >> n >> m;
    a.resize(n, vector<int>(n, 0));
    f.resize(n, vector<int>(n, 0));
    used.resize(n);
    nxt.resize(n);
    for (int i = 0; i < m; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        a[u - 1][v - 1] += c;
    }
    int ans = 0;
    while (clean() && dfs(0)) {
        int min_c = 1000000000;
        int u = 0;
        while (u != n - 1) {
            min_c = min(min_c, a[u][nxt[u]] - f[u][nxt[u]]);
            u = nxt[u];
        }
        u = 0;
        while (u != n - 1) {
            f[u][nxt[u]] += min_c;
            f[nxt[u]][u] -= min_c;
            u = nxt[u];
        }
    }
    for (auto i : f[0]) {
        ans += i;
    }
    cout << ans;
}
