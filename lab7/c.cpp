#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct rectangle {
    long long x1, y1, x2, y2;
};

rectangle min(rectangle r1, rectangle r2) {
    rectangle r;
    r.x1 = max(r1.x1, r2.x1);
    r.x2 = min(r1.x2, r2.x2);
    if (r.x2 < r.x1) {
        r.x2 = r.x1;
    }
    r.y1 = max(r1.y1, r2.y1);
    r.y2 = min(r1.y2, r2.y2);
    if (r.y2 < r.y1) {
        r.y2 = r.y1;
    }
    return r;
}

long long square(rectangle r) {
    return (r.x2 - r.x1) * (r.y2 - r.y1);
}

int n, m, log_n, log_m;
vector<long long> lg;
vector<vector<vector<vector<rectangle>>>> s;
vector<vector<rectangle>> rs;
rectangle INF = {INT32_MIN, INT32_MIN, INT32_MAX, INT32_MAX};

void build() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            s[i][j][0][0] = rs[i][j];
        }
    }
    for (int k = 1; k < log_m; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (j + (1 << (k - 1)) < m) {
                    s[i][j][0][k] = min(s[i][j][0][k - 1], s[i][j + (1 << (k - 1))][0][k - 1]);
                } else {
                    s[i][j][0][k] = s[i][j][0][k - 1];
                }
            }
        }
    }
    for (int k = 1; k < log_n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (i + (1 << (k - 1)) < n) {
                    s[i][j][k][0] = min(s[i][j][k - 1][0], s[i + (1 << (k - 1))][j][k - 1][0]);
                } else {
                    s[i][j][k][0] = s[i][j][k - 1][0];
                }
            }
        }
    }
    for (int k = 1; k < log_n; k++) {
        for (int i = 0; i < n; i++) {
            for (int l = 1; l < log_m; l++) {
                for (int j = 0; j < m; j++) {
                    if (i + (1 << (k - 1)) < n) {
                        s[i][j][k][l] = min(s[i][j][k - 1][l], s[i + (1 << (k - 1))][j][k - 1][l]);
                    } else {
                        s[i][j][k][l] = s[i][j][k - 1][l];
                    }
                }
            }
        }
    }
}

rectangle get(int x1, int y1, int x2, int y2) {
    int k1 = (int) lg[(x2 - x1) + 1];
    int k2 = (int) lg[(y2 - y1) + 1];
    rectangle ans1 = s[x1][y1][k1][k2];
    rectangle ans2 = s[x2 - (1 << k1) + 1][y1][k1][k2];
    rectangle ans3 = s[x1][y2 - (1 << k2) + 1][k1][k2];
    rectangle ans4 = s[x2 - (1 << k1) + 1][y2 - (1 << k2) + 1][k1][k2];
    return min(min(ans1, ans2), min(ans3, ans4));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> n >> m;
    lg.resize(max(n, m) + 1);
    lg[1] = 0;
    for (int i = 2; i < max(n, m) + 1; i++) {
        lg[i] = lg[i / 2] + 1;
    }
    log_n = (int) lg[(n)] + 1;
    log_m = (int) lg[(m)] + 1;
    rs.resize(n, vector<rectangle>(m));
    s.resize(n, vector<vector<vector<rectangle>>>(m,
            vector<vector<rectangle>>(log_n, vector<rectangle>(log_m, INF))));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            rs[i][j].x1 = min(x1, x2);
            rs[i][j].y1 = min(y1, y2);
            rs[i][j].x2 = max(x1, x2);
            rs[i][j].y2 = max(y1, y2);
        }
    }
    build();
    long long q, a, b, v;
    cin >> q >> a >> b >> v;
    long long ans = 0;
    int mod = (int) 1e9 + 7;
    for (int i = 0; i < q; i++) {
        long long x1, y1, x2, y2;
        x1 = v = (a * v + b) % mod;
        y1 = v = (a * v + b) % mod;
        x2 = v = (a * v + b) % mod;
        y2 = v = (a * v + b) % mod;
        x1 %= n;
        x2 %= n;
        y1 %= m;
        y2 %= m;
        ans += square(get((int) min(x1, x2), (int) min(y1, y2),
                          (int) max(x1, x2), (int) max(y1, y2)));
        ans %= mod;
    }
    cout << ans;
    return 0;
}
