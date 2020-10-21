#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int n, m, k;
vector<vector<int>> lft;
vector<vector<int>> rght;
vector<int> m_l;
vector<int> m_r;
vector<int> d;
vector<int> ans;

bool bfs() {
    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (m_l[i] == m) {
            d[i] = 0;
            q.push(i);
        } else {
            d[i] = INT32_MAX;
        }
    }
    d[n] = INT32_MAX;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (d[u] < d[n]) {
            for (auto v : lft[u]) {
                if (d[m_r[v]] == INT32_MAX) {
                    d[m_r[v]] = d[u] + 1;
                    q.push(m_r[v]);
                }
            }
        }
    }
    return d[n] != INT32_MAX;
}

bool dfs(int u) {
    if (u != n) {
        for (auto v : lft[u]) {
            if (d[m_r[v]] == d[u] + 1) {
                if (dfs(m_r[v])) {
                    m_r[v] = u;
                    m_l[u] = v;
                    return true;
                }
            }
        }
        d[u] = INT32_MAX;
        return false;
    }
    return true;
}

vector<bool> used;

void color_dfs(int v) {
    used[v] = true;
    ans.push_back(v);
    for (auto u : rght[v]) {
        if (m_l[u] != m && !used[m_l[u]]) {
            color_dfs(m_l[u]);
        }
    }
}

int main() {
//    freopen("test.in", "r", stdin);
//    freopen("test.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    while (cin >> n >> m >> k) {
        lft.clear();
        rght.clear();
        m_l.clear();
        m_r.clear();
        d.clear();
        ans.clear();
        used.clear();
        lft.resize(n + 1, vector<int>(0));
        rght.resize(m + 1, vector<int>(0));
        m_l.resize(n + 1, m);
        m_r.resize(m + 1, n);
        d.resize(n + 1);
        used.resize(m, false);
        for (int i = 0; i < k; i++) {
            int u, v;
            cin >> u >> v;
            lft[u - 1].push_back(v - 1);
            rght[v - 1].push_back(u - 1);
        }
        while (bfs()) {
            for (int i = 0; i < n; i++) {
                if (m_l[i] == m) {
                    if (dfs(i)) {
                    }
                }
            }
        }
        for (int i = 0; i < m; i++) {
            if (m_r[i] == n) {
                color_dfs(i);
            }
        }
        sort(ans.begin(), ans.end());
        cout << ans.size() << '\n';
        for (auto i : ans) {
            cout << i + 1 << " ";
        }
        cout << '\n';
        cout << '\n';
    }
}
