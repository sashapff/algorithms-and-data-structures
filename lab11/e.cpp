#include<iostream>
#include<vector>
#include<queue>
#include<cassert>

using namespace std;

struct edge {
    int u{}, v{}, num{};

    edge(int u, int v, int num, long long c, long long f) :
            u(u), v(v), num(num), c(c), f(f) {}

    edge() = default;

    long long c{}, f{};
};

int n, m;
vector<vector<int>> g;
vector<int> d;
vector<int> nxt;
vector<int> path;
vector<edge> edges;
vector<vector<int>> ans;
vector<long long> flows;

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
        for (int i = 0; i < (int) g[u].size(); i++) {
            auto e = edges[g[u][i]];
            if (d[e.v] == -1 && e.c - e.f > 0) {
                q.push(e.v);
                d[e.v] = d[u] + 1;
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
    for (int i = nxt[u]; i < (int) g[u].size(); i++) {
        auto e = edges[g[u][i]];
        int num = g[u][i];
        if (d[e.v] == d[u] + 1) {
            long long new_flow = dfs(e.v, min(flow, e.c - e.f));
            if (new_flow != 0) {
                edges[num].f += new_flow;
                edges[e.num].f -= new_flow;
                return new_flow;
            }
        }
        nxt[u]++;
    }
    return 0;
}

long long path_dfs(int u, long long flow) {
    if (flow == 0) {
        return 0;
    }
    if (u == n - 1) {
        flows.push_back(flow);
        ans.push_back(path);
        return flow;
    }
    bool flag = false;
    for (int i = 0; i < (int) g[u].size(); i++) {
        auto e = edges[g[u][i]];
        int num = g[u][i];
        if (min(flow, e.f) > 0) {
            assert(num < m);
            path.push_back(num + 1);
            long long new_flow = path_dfs(e.v, min(flow, e.f));
            path.pop_back();
            if (new_flow != 0) {
                edges[num].f -= min(flow, e.f);
                flow -= min(flow, e.f);
                flag = true;
            }
        }
    }
    return flag;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n >> m;
    d.resize(n);
    nxt.resize(n);
    g.resize(n);
    edges.resize(2 * m);
    for (int i = 0; i < m; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        g[u - 1].push_back(i);
        g[v - 1].push_back(i + m);
        edges[i] = edge(u - 1, v - 1, i + m, w, 0);
        edges[i + m] = edge(v - 1, u - 1, i, 0, 0);
    }
    long long q = 0;
    while (bfs()) {
        for (int i = 0; i < n; i++) {
            nxt[i] = 0;
        }
        while (true) {
            long long flow = dfs(0, 1000000000000000000LL);
            if (!flow) {
                break;
            } else {
                q += flow;
            }
        }
    }
    while (path_dfs(0, q)) {
    }
    cout << ans.size() << '\n';
    for (int i = 0; i < (int) ans.size(); i++) {
        cout << flows[i] << " ";
        cout << ans[i].size() << " ";
        for (auto j : ans[i]) {
            cout << j << " ";
        }
        cout << '\n';
    }
//    cout << q;
}
