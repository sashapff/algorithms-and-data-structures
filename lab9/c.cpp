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
    vector<vector<int>> d(n, vector<int>(n, 10000000));
    for (int i = 0; i < n; i++) {
        d[i][i] = 0;
    }
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        d[u - 1][v - 1] = w;
    }
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            }
        }
    }
    for (vector<int> i : d) {
        for (int j : i) {
            cout << j << " ";
        }
        cout << '\n';
    }
    return 0;
}
