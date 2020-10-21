#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>

using namespace std;

vector<int> pr;
vector<vector<pair<int, int>>> a;

int get(int u) {
    if (pr[u] == u) {
        return u;
    }
    int prev = get(pr[u]);
    pr[u] = prev;
    return prev;
}

void _union(int u, int v) {
    u = get(u);
    v = get(v);
    pr[v] = u;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n, m;
    cin >> n >> m;
    vector<pair<int, pair<int, int>>> edges;
    pr.resize(n);
    a.resize(n);
    for (int i = 0; i < m; i++) {
        int x, y, w;
        cin >> x >> y >> w;
        a[x - 1].push_back(make_pair(y - 1, w));
        a[y - 1].push_back(make_pair(x - 1, w));
        edges.emplace_back(w, make_pair(x - 1, y - 1));
    }
    sort(edges.begin(), edges.end());
    vector<int> index;
    int min_delta = 2000000001;
    for (int j = 0; j < m; j++) {
        for (int i = 0; i < n; i++) {
            pr[i] = i;
        }
        index.resize(0);
        for (int i = j; i < m; i++) {
            if (get(edges[i].second.first) != get(edges[i].second.second)) {
                _union(edges[i].second.first, edges[i].second.second);
                index.push_back(i);
            }
        }
        if ((int) index.size() == n - 1) {
            min_delta = min(min_delta, edges[index[index.size() - 1]].first
            - edges[index[0]].first);
        }
    }
    if (min_delta == 2000000001) {
        cout << "NO";
        return 0;
    }
    cout << "YES\n" << min_delta;
    return 0;
}
