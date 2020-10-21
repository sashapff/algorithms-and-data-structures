#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cmath>

using namespace std;

double INF = 1000000000;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n;
    cin >> n;
    vector<pair<double, double>> points(n);
    vector<vector<double>> a(n, vector<double>(n));
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        points[i] = make_pair(x, y);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            a[i][j] = sqrt((points[i].first - points[j].first)
                    * (points[i].first - points[j].first)
                    + (points[i].second - points[j].second)
                    * (points[i].second - points[j].second));
        }
    }
    vector<bool> used(n, false);
    vector<pair<double, int>> d(n, make_pair(INF, -1));
    d[0] = make_pair(0, 0);
    double ans = 0;
    for (int i = 0; i < n; i++) {
        double min_d = INF;
        int v = -1;
        int pr = -1;
        for (int u = 0; u < n; u++) {
            if (!used[u] && d[u].first < min_d) {
                min_d = d[u].first;
                v = u;
                pr = d[u].second;
            }
        }
        used[v] = true;
        ans += a[v][pr];
        for (int u = 0; u < n; u++) {
            if (d[u].first > a[u][v]) {
                d[u].first = a[u][v];
                d[u].second = v;
            }
        }
    }
    printf("%.8lf", ans);
    return 0;
}
