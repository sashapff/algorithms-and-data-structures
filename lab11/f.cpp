#include<iostream>
#include<vector>
#include<queue>

using namespace std;

struct edge {
    int u{}, v{}, num{};

    edge(int u, int v, int num, long long c, long long f, long long l) :
            u(u), v(v), num(num), c(c), f(f), l(l) {}

    edge() = default;

    long long c{}, f{}, l{};
};

int n, m, s, t;
vector<vector<int>> g;
vector<int> d;
vector<int> nxt;
vector<edge> edges;

bool bfs() {
    for (int i = 0; i < n; i++) {
        d[i] = -1;
    }
    queue<int> q;
    q.push(s);
    d[s] = 0;
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
    if (u == t) {
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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n >> m;
    s = n;
    t = n + 1;
    n += 2;
    d.resize(n);
    nxt.resize(n);
    g.resize(n);
    int sz = 6 * m;
    edges.resize(sz);
    for (int i = 0; i < m; i++) {
        int u, v;
        long long l, w;
        cin >> u >> v >> l >> w;
        g[u - 1].push_back(6 * i);
        g[v - 1].push_back(6 * i + 1);
        g[s].push_back(6 * i + 2);
        g[v - 1].push_back(6 * i + 3);
        g[u - 1].push_back(6 * i + 4);
        g[t].push_back(6 * i + 5);
        edges[6 * i] = edge(u - 1, v - 1, 6 * i + 1, w - l, 0, l);
        edges[6 * i + 1] = edge(v - 1, u - 1, 6 * i, 0, 0, 0);
        edges[6 * i + 2] = edge(s, v - 1, 6 * i + 3, l, 0, l);
        edges[6 * i + 3] = edge(v - 1, s, 6 * i + 2, 0, 0, 0);
        edges[6 * i + 4] = edge(u - 1, t, 6 * i + 5, l, 0, l);
        edges[6 * i + 5] = edge(t, u - 1, 6 * i + 4, 0, 0, 0);
    }
    long long max_flow = 0;
    while (bfs()) {
        for (int i = 0; i < n; i++) {
            nxt[i] = 0;
        }
        while (true) {
            long long flow = dfs(s, 1000000000000000000LL);
            if (!flow) {
                break;
            } else {
                max_flow += flow;
            }
        }
    }
    for (int i = 0; i < 6 * m; i++) {
        if (edges[i].u == s && edges[i].f < edges[i].c) {
            cout << "NO";
            return 0;
        }
    }
    cout << "YES" << '\n';
    for (int i = 0; i < 6 * m; i++) {
        if (i % 2 == 0 && !(edges[i].u == s || edges[i].v == t)) {
            cout << edges[i].f + edges[i].l << '\n';
        }
    }
    return 0;
}
