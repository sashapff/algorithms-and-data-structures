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
vector<int> edges;
int clr;
int n, m;

void dfs(int u) {
    used[u] = 1;
    for (int v = 0; v < n; v++) {
        if (v != u && used[v] == 0 && a_rev[u][v] < edges[m]) {
            dfs(v);
        }
    }
    q.push_front(u);
}

void dfs2(int u) {
    color[u] = clr;
    for (int v = 0; v < n; v++) {
        if (v != u && color[v] == 0 && a[u][v] < edges[m]) {
            dfs2(v);
        }
    }
}

bool check() {
    for (int i = 0; i < n; i++) {
        used[i] = 0;
        color[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        if (used[i] == 0) {
            dfs(i);
        }
    }
    clr = n;
    for (auto u : q) {
        if (color[u] == 0) {
            dfs2(u);
            clr--;
        }
    }
    return n - clr == 1;
}

int main() {
//    freopen("avia.in", "r", stdin);
//    freopen("avia.out", "w", stdout);
    cin >> n;
    a.resize(n, vector<int>(n));
    a_rev.resize(n, vector<int>(n));
    used.resize(n);
    color.resize(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
            a_rev[j][i] = a[i][j];
            edges.push_back(a[i][j]);
        }
    }
    sort(edges.begin(), edges.end());
    int l = 0;
    int r = n * n;
    while (r - l > 1) {
        m = (l + r) / 2;
        if (check()) {
            r = m;
        } else {
            l = m;
        }
    }
    cout << edges[l];
    return 0;
}
