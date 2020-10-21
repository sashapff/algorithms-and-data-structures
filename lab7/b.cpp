#include <iostream>
#include <vector>

using namespace std;

unsigned int log(unsigned int a) {
    unsigned int cnt = 0;
    while (a != 0) {
        cnt++;
        a = a >> 1;
    }
    return cnt - 1;
}

int n, m;
vector<unsigned int> a;
vector<vector<unsigned int>> s;
int sz;

void build() {
    s[0].resize(n);
    for (int i = 0; i < n; i++) {
        s[0][i] = a[i];
    }
    for (int i = 1; i < sz; i++) {
        s[i].resize(n);
        for (int j = 0; j + (1 << (i - 1)) < n; j++) {
            s[i][j] = min(s[i - 1][j], s[i - 1][j + (1 << (i - 1))]);
        }
    }
}

unsigned int get(unsigned int l, unsigned int r) {
    if (l > r) {
        swap(l, r);
    }
    unsigned int len = r + 1 - l;
    unsigned int pow = log(len);
    return min(s[pow][l], s[pow][r - (1 << pow) + 1]);
}

int main() {
    cin >> n >> m;
    a.resize(n);
    sz = log(n) + 1;
    s.resize(sz);
    cin >> a[0];
    for (int i = 1; i < n; i++) {
        a[i] = (a[i - 1] * 23 + 21563) % 16714589;
    }
    build();
    unsigned int u, v, ans;
    cin >> u >> v;
    u--;
    v--;
    ans = get(u, v);
    for (int i = 1; i < m; i++) {
        u = (17 * (u + 1) + 751 + ans + 2 * (i)) % n;
        v = (13 * (v + 1) + 593 + ans + 5 * (i)) % n;
        ans = get(u, v);
    }
    cout << u + 1 << " " << v + 1 << " " << ans << endl;
    return 0;
}
