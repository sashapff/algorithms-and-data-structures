#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n, beg, end;
    cin >> n >> beg >> end;
    beg--; end--;
    vector<vector<long long>> a(n, vector<long long>(n));
    vector<long long> d(n, LONG_LONG_MAX - 1);
    d[beg] = 0;
    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
            cin >> a[u][v];
        }
    }
    vector<int> used(n, 0);
    d[beg] = 0;
    for (int i = 0; i < n - 1; i++) {
        int u = -1;
        long long min = LONG_LONG_MAX;
        for (int j = 0; j < n; j++) {
            if (used[j] == 0 && d[j] < min) {
                min = d[j];
                u = j;
            }
        }
        if (u != -1) {
            used[u] = 1;
            for (int v = 0; v < n; v++) {
                if (v != u && a[u][v] != -1) {
                    if (used[v] == 0 && d[u] + a[u][v] < d[v]) {
                        d[v] = d[u] + a[u][v];
                    }
                }
            }
        }
    }
    cout << (d[end] == LONG_LONG_MAX - 1 ? -1 : d[end]);
    return 0;
}
