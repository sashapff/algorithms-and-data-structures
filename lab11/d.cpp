#include<iostream>
#include<vector>
#include<queue>

using namespace std;

int n, m;
vector<vector<long long>> c;
vector<vector<long long>> f;
vector<int> d;
vector<int> nxt;

bool bfs() {
    for (int i = 0; i < n; i++) {
        d[i] = -1;
    }
    queue<int> q;
    q.push(0);
    d[0] = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v = 0; v < n; v++) {
            if (d[v] == -1 && f[u][v] < c[u][v]) {
                q.push(v);
                d[v] = d[u] + 1;
            }
        }
    }
    return d[n - 1] != -1;
}

long long dfs(int u, long long flow) {
    if (flow == 0) {
        return 0;
    }
    if (u == n - 1) {
        return flow;
    }
    for (int v = nxt[u]; v < n; v++) {
        if (d[v] == d[u] + 1) {
            long long new_flow = dfs(v, min(flow, c[u][v] - f[u][v]));
            if (new_flow != 0) {
                f[u][v] += new_flow;
                f[v][u] -= new_flow;
                return new_flow;
            }
        }
        nxt[u]++;
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> n >> m;
    c.resize(n, vector<long long>(n, 0));
    f.resize(n, vector<long long>(n, 0));
    d.resize(n);
    nxt.resize(n);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        c[u - 1][v - 1] += w;
    }
    long long ans = 0;
    while (bfs()) {
        for (int i = 0; i < n; i++) {
            nxt[i] = 0;
        }
        while (true) {
            long long flow = dfs(0, LONG_LONG_MAX);
            if (!flow) {
                break;
            } else {
                ans += flow;
            }
        }
    }
    cout << ans;
}
