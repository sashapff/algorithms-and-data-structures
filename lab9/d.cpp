#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

int main() {
//    freopen("avia.in", "r", stdin);
//    freopen("avia.out", "w", stdout);
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> a(n);
    vector<int> d(n, INT32_MAX);
    d[0] = 0;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        a[u - 1].push_back(make_pair(v - 1, w));
        a[v - 1].push_back(make_pair(u - 1, w));
    }
    set<pair<int, int>> s;
    s.insert(make_pair(0, 0));
    while (!s.empty()) {
        int u = s.begin()->second;
        s.erase(s.begin());
        for (auto v : a[u]) {
            if (d[u] + v.second < d[v.first]) {
                s.erase(make_pair(d[v.first], v.first));
                d[v.first] = d[u] + v.second;
                s.insert(make_pair(d[v.first], v.first));
            }
        }
    }
    for (auto i : d) {
        cout << i << " ";
    }
    return 0;
}
