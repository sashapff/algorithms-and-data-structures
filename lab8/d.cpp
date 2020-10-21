#include <iostream>
#include <vector>
#include <deque>

using namespace std;

vector<vector<int>> a;
vector<int> used;
vector<bool> wol;

void dfs(int u) {
    used[u] = 1;
    bool flag = false;
    for (auto v : a[u]) {
        if (used[v] == 0) {
            dfs(v);
        }
        if (!wol[v]) {
            flag = true;
        }
    }
    if (flag) {
        wol[u] = true;
    }
}

int main() {
    freopen("game.in", "r", stdin);
    freopen("game.out", "w", stdout);
    int n, m, s;
    cin >> n >> m >> s;
    a.resize(n);
    used.resize(n, 0);
    wol.resize(n, false);
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
    if (wol[s - 1]) {
        cout << "First player wins";
    } else {
        cout << "Second player wins";
    }
    return 0;
}
