#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

vector<vector<int>> a;
vector<int> used;
vector<int> color;
int clr = 1;

void dfs(int u) {
    used[u] = 1;
    color[u] = clr;
    for (auto v : a[u]) {
        if (used[v] == 0) {
            dfs(v);
        }
    }
}

int main() {
    freopen("components.in", "r", stdin);
    freopen("components.out", "w", stdout);
    int n, m;
    cin >> n >> m;
    a.resize(n);
    used.resize(n, 0);
    color.resize(n, -1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        a[u - 1].push_back(v - 1);
        a[v - 1].push_back(u - 1);
    }
    for (int i = 0; i < n; i++) {
        if (used[i] == 0) {
            dfs(i);
            clr++;
        }
    }
    cout << clr - 1 << endl;
    for (auto i : color) {
        cout << i << " ";
    }
    return 0;
}
