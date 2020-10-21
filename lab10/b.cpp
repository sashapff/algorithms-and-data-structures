#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int n, m;
vector<vector<int>> _left;
vector<vector<int>> _right;
vector<int> mt;
vector<bool> used;

bool try_kuhn(int u) {
    if (used[u]) {
        return false;
    }
    used[u] = true;
    for (auto v : _left[u]) {
        if (mt[v] == -1 || try_kuhn(mt[v])) {
            mt[v] = u;
            return true;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> n >> m;
    _left.resize(n);
    _right.resize(n);
    mt.resize(n, -1);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        _left[u - 1].push_back(v - 1);
        _right[v - 1].push_back(u - 1);
    }

    used.resize(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            used[j] = false;
        }
        try_kuhn(i);
    }
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (mt[i] != -1) {
            cnt++;
        }
    }
    cout << n - cnt;
    return 0;
}
