#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;
int n;
vector<vector<pair<int, long long>>> a;
vector<long long> d;
vector<bool> used;
long long INF = LONG_LONG_MAX - 3 * 1000000000000000LL;

void dfs(int u) {
    used[u] = true;
    for (auto v : a[u]) {
        if (!used[v.first]) {
            dfs(v.first);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int m, s;
    cin >> n >> m >> s;
    s--;
    a.resize(n);
    used.resize(n, false);
    for (int i = 0; i < m; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        a[u - 1].push_back(make_pair(v - 1, w));
    }
    d.resize(n, INF);
    d[s] = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int u = 0; u < n; u++) {
            for (auto v : a[u]) {
                if (d[u] < INF) {
                    if (d[v.first] > d[u] + v.second) {
                        d[v.first] = max(-INF, d[u] + v.second);
                    }
                }
            }
        }
    }
    for (int u = 0; u < n; u++) {
        for (auto v : a[u]) {
            if (d[u] < INF) {
                if (d[v.first] > d[u] + v.second) {
                    d[v.first] = max(-INF, d[u] + v.second);
                    used[v.first] = true;
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (used[i]) {
            dfs(i);
        }
    }
    for (int i = 0; i < n; i++) {
        if (used[i]) {
            cout << "-\n";
        } else if (d[i] == INF) {
            cout << "*\n";
        } else {
            cout << d[i] << '\n';
        }
    }
    return 0;
}
