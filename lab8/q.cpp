#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>

using namespace std;

vector<vector<int>> a;
vector<vector<int>> a_rev;
vector<int> used;
vector<int> color;
deque<int> q;
int clr;
int n, m;

void dfs(int u) {
    used[u] = 1;
    for (int v = 0; v < 2 * n; v++) {
        if (v != u && used[v] == 0 && a_rev[u][v] <= m) {
            dfs(v);
        }
    }
    q.push_front(u);
}

void dfs2(int u) {
    color[u] = clr;
    for (int v = 0; v < 2 * n; v++) {
        if (v != u && color[v] == 0 && a[u][v] <= m) {
            dfs2(v);
        }
    }
}

bool check() {
    for (int i = 0; i < 2 * n; i++) {
        used[i] = 0;
        color[i] = 0;
    }
    for (int i = 0; i < 2 * n; i++) {
        if (used[i] == 0) {
            dfs(i);
        }
    }
    clr = 2 * n;
    for (auto u : q) {
        if (color[u] == 0) {
            dfs2(u);
            clr--;
        }
    }
    for (int i = 0; i < n; i++) {
        if (color[i] == color[i + n]) {
            return false;
        }
    }
    return true;
}

int main() {
    freopen("truth.in", "r", stdin);
    freopen("truth.out", "w", stdout);
    int k;
    cin >> n >> k;
    a.resize(2 * n, vector<int>(2 * n, INT32_MAX));
    a_rev.resize(2 * n, vector<int>(2 * n, INT32_MAX));
    used.resize(2 * n);
    color.resize(2 * n);
    for (int i = 0; i < k; i++) {
        int u, v;
        char c;
        cin >> u >> v >> c;
        u--;
        v--;
        if (c == 'T') {
            a[u][v] = i;
            a[u + n][v + n] = i;
            a_rev[v][u] = i;
            a_rev[v + n][u + n] = i;
            a[v][u] = i;
            a[v + n][u + n] = i;
            a_rev[u][v] = i;
            a_rev[u + n][v + n] = i;
        } else {
            a[u][v + n] = i;
            a[u + n][v] = i;
            a_rev[v + n][u] = i;
            a_rev[v][u + n] = i;
            a[v][u + n] = i;
            a[v + n][u] = i;
            a_rev[u][v + n] = i;
            a_rev[u + n][v] = i;
        }
    }
    int l = 0;
    int r = k;
    while (r - l > 1) {
        m = (l + r) / 2;
        if (check()) {
            l = m;
        } else {
            r = m;
        }
    }
    cout << l + 1;
    return 0;
}
