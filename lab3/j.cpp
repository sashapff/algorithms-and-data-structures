#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int sz = 4 * (int) (1e5) + 5;
int prv[sz];
int cnt[sz];
int bal[sz];
int zerg = 0;
int p = 1000003;
int firstfree;
int curSum;

int get(int u) {
    if (prv[u] == u) {
        curSum += cnt[u];
        return u;
    }
    int t = get(prv[u]);
    curSum += cnt[u];
    cnt[u] = curSum - cnt[t];
    return prv[u] = t;
}

void merge(int u, int v) {
    curSum = 0;
    u = get(u);
    curSum = 0;
    v = get(v);
    if (u != v) {
        prv[u] = firstfree;
        prv[v] = firstfree;
        firstfree++;
        zerg = (int) (13ll * zerg + 11) % p;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n, m;
    cin >> n >> m;
    firstfree = n;
    for (int i = 0; i < 4 * n; i++) {
        prv[i] = i;
    }
    for (int i = 0; i < m; i++) {
        int type;
        cin >> type;
        if (type == 1) {
            int x;
            cin >> x;
            curSum = 0;
            cnt[get((x + zerg) % n)]++;
            zerg = (int) (30ll * zerg + 239) % p;
        }
        if (type == 2) {
            int x, y;
            cin >> x >> y;
            merge((x + zerg) % n, (y + zerg) % n);
        }
        if (type == 3) {
            int x;
            cin >> x;
            int u = (x + zerg) % n;
            curSum = 0;
            get(u);
            int q = curSum - bal[u];
            cout << q << endl;
            bal[u] = curSum;
            zerg = (int) ((100500ll * zerg + q) % p);
        }
    }
    return 0;
}
