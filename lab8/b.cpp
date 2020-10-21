#include <iostream>
#include <vector>
#include <deque>

using namespace std;

vector<vector<int>> dir;
vector<vector<int>> rev;
vector<int> used;
vector<int> color;
deque<int> q;
int clr;

void dfs(int u) {
    used[u] = 1;
    for (auto v : rev[u]) {
        if (used[v] == 0) {
            dfs(v);
        }
    }
    q.push_front(u);
}

void dfs2(int u) {
    color[u] = clr;
    for (auto v : dir[u]) {
        if (color[v] == 0) {
            dfs2(v);
        }
    }
}

int main() {
//    freopen("cond.in", "r", stdin);
//    freopen("cond.out", "w", stdout);
    int n, m;
    cin >> n >> m;
    dir.resize(n);
    rev.resize(n);
    used.resize(n, 0);
    color.resize(n, 0);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        dir[u - 1].push_back(v - 1);
        rev[v - 1].push_back(u - 1);
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
    cout << n - clr << endl;
    for (int i = 0; i < n; i++) {
        cout << color[i] - clr << ' ';
    }
    return 0;
}
