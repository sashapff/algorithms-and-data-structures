#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;
int n;
vector<vector<int>> a;
vector<long long> d;
long long INF = 1000000000;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> n;
    a.resize(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }
    d.resize(n, INF);
    vector<int> p(n, -1);
    for (int i = 0; i < n - 1; i++) {
        for (int u = 0; u < n; u++) {
            for (int v = 0; v < n; v++) {
                if (d[v] > d[u] + a[u][v]) {
                    d[v] = max(-INF, d[u] + a[u][v]);
                    p[v] = u;
                }
            }
        }
    }
    int e = -1;
    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
            if (d[v] > d[u] + a[u][v]) {
                d[v] = max(-INF, d[u] + a[u][v]);
                e = v;
                p[v] = u;
            }
        }
    }
    if (e == -1) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
        int q = e;
        for (int i = 0; i < n; i++) {
            q = p[q];
        }
        vector<int> ans;
        ans.push_back(q);
        int t = p[q];
        while (t != q) {
            ans.push_back(t);
            t = p[t];
        }
        ans.push_back(q);
        reverse(ans.begin(), ans.end());
        cout << ans.size() << '\n';
        for (auto i : ans) {
            cout << i + 1 << " ";
        }
    }
    return 0;
}
