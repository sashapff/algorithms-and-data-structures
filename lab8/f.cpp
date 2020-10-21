#include <iostream>
#include <vector>
#include <deque>

using namespace std;

vector<vector<int>> dir;
vector<int> used;
deque<int> q;

void dfs(int u) {
    used[u] = 1;
    for (auto v : dir[u]) {
        if (used[v] == 0) {
            dfs(v);
        }
    }
    q.push_front(u);
}

int main() {
    freopen("hamiltonian.in", "r", stdin);
    freopen("hamiltonian.out", "w", stdout);
    int n, m;
    cin >> n >> m;
    dir.resize(n);
    used.resize(n, 0);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        dir[u - 1].push_back(v - 1);
    }
    for (int i = 0; i < n; i++) {
        if (used[i] == 0) {
            dfs(i);
        }
    }
    vector<int> tc;
    for (auto i : q) {
        tc.push_back(i);
    }
    bool flag = true;
    for (int i = 1; i < n; i++) {
        bool f = false;
        for (auto j : dir[tc[i - 1]]) {
            if (j == tc[i]) {
                f = true;
            }
        }
        if (!f) {
            flag = false;
        }
    }
    cout << (flag ? "YES" : "NO");
    return 0;
}

