#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int main() {
//    freopen("avia.in", "r", stdin);
//    freopen("avia.out", "w", stdout);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n);
//    vector<pair<int, int>> edges;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        a[u - 1].push_back(v - 1);
        a[v - 1].push_back(u - 1);
//        edges.push_back(make_pair(u - 1, v - 1));
//        edges.push_back(make_pair(v - 1, u - 1));
    }
    queue<int> q;
    q.push(0);
    vector<int> d(n, 10000000);
    d[0] = 0;
    while (q.size() > 0) {
        int u = q.front();
        q.pop();
        for (auto v : a[u]) {
            if (d[v] == 10000000) {
                d[v] = d[u] + 1;
                q.push(v);
            }
        }
    }
    for (auto i : d) {
        cout << i << " ";
    }
    return 0;
}
