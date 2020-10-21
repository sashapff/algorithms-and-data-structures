#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct edge {
    int u, v, num, rev_num;
    long long c, price, f;

    edge(int u, int v, int num, int revNum, long long int c,
         long long int price, long long int f) : u(u), v(v),
                                                 num(num),
                                                 rev_num(revNum),
                                                 c(c), price(price),
                                                 f(f) {}

    edge() = default;
};

int n, m;
vector<edge> edges;
vector<vector<int>> g;
vector<long long> p, d;
vector<int> prv;
vector<bool> used;

bool ford_bellman() {
    for (int i = 0; i < n; i++) {
        p[i] = LONG_LONG_MAX;
    }
    p[0] = 0;
    prv[0] = -1;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < 2 * m; j++) {
            if (p[edges[j].u] != LONG_LONG_MAX && edges[j].c - edges[j].f > 0
            && p[edges[j].v] > p[edges[j].u] + edges[j].price) {
                p[edges[j].v] = p[edges[j].u] + edges[j].price;
                prv[edges[j].v] = j;
            }
        }
    }
    return p[n - 1] != LONG_LONG_MAX;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n >> m;
    edges.resize(2 * m);
    g.resize(n);
    p.resize(n, LONG_LONG_MAX);
    d.resize(n);
    prv.resize(n);
    used.resize(n);
    for (int i = 0; i < m; i++) {
        int u, v, c, price;
        cin >> u >> v >> c >> price;
        edges[i] = edge(u - 1, v - 1, i, i + m, c, price, 0);
        edges[i + m] = edge(v - 1, u - 1, i + m, i, 0, -price, 0);
        g[u - 1].push_back(i);
        g[v - 1].push_back(i + m);
    }

//    d[n - 1] = p[n - 1];
    long long ans = 0;
    while (ford_bellman()) {
        vector<int> path;
        int e = prv[n - 1];
        long long flow = LONG_LONG_MAX;
        while (e != -1) {
            path.push_back(e);
            flow = min(flow, edges[e].c - edges[e].f);
            e = prv[edges[e].u];
        }
        reverse(path.begin(), path.end());
        for (auto i : path) {
            ans += flow * edges[i].price;
            edges[i].f += flow;
            edges[edges[i].rev_num].f -= flow;
        }
//        for (int i = 0; i < n; i++) {
//            d[i] = LONG_LONG_MAX;
//            used[i] = false;
//        }
//        d[0] = 0;
//        for (int i = 0; i < n; i++) {
//            int v = -1;
//            for (int j = 0; j < n; j++) {
//                if (!used[j] && (v == -1 || d[j] < d[v])) {
//                    v = j;
//                }
//            }
//            if (v == -1 || d[v] == LONG_LONG_MAX) {
//                break;
//            }
//            used[v] = true;
//            for (int j : g[v]) {
//                auto edge = edges[j];
//                if (d[v] != LONG_LONG_MAX && edge.c - edge.f > 0
//                && d[v] + edge.price + p[v] - p[edge.v] < d[edge.v]) {
//                    d[edge.v] = d[v] + edge.price + p[v] - p[edge.v];
//                    prv[edge.v] = edge.num;
//                }
//            }
//        }
//        for (int i = 0; i < n; i++) {
//            if (d[i] != LONG_LONG_MAX) {
//                p[i] += d[i];
//            } else {
//                p[i] = LONG_LONG_MAX;
//            }
//        }
    }
    cout << ans;
}
