#include<iostream>
#include<vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin >> n;
    vector<vector<int>> a(n + 1, vector<int>(n + 1));
    vector<int> u(n + 1);
    vector<int> v(n + 1);
    vector<int> p(n + 1);
    vector<int> minv(n + 1);
    vector<bool> used(n + 1);
    vector<int> way(n + 1);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i + 1][j + 1];
        }
    }
    for (int i = 1; i <= n; i++) {
        p[0] = i;
        for (int j = 0; j <= n; j++) {
            minv[j] = INT32_MAX;
            used[j] = false;
        }
        int j0 = 0;
        while (true) {
            used[j0] = true;
            int i0 = p[j0];
            int j1 = 0;
            int delta = INT32_MAX;
            for (int j = 1; j <= n; j++) {
                if (!used[j]) {
                    if (a[i0][j] - u[i0] - v[j] < minv[j]) {
                        minv[j] = a[i0][j] - u[i0] - v[j];
                        way[j] = j0;
                    }
                    if (minv[j] < delta) {
                        delta = minv[j];
                        j1 = j;
                    }
                }
            }
            for (int j = 0; j <= n; j++) {
                if (used[j]) {
                    u[p[j]] += delta;
                    v[j] -= delta;
                } else {
                    minv[j] -= delta;
                }
            }
            j0 = j1;
            if (p[j0] == 0) {
                break;
            }
        }
        while (true) {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
            if (j0 == 0) {
                break;
            }
        }
    }
    cout << -v[0] << '\n';
    for (int j = 1; j <= n; j++) {
        cout << p[j] << " " << j << '\n';
    }
    return 0;
}
