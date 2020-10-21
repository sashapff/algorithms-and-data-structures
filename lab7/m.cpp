#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
vector<vector<int>> tree;
vector<pair<int, int>> b;
vector<vector<pair<int, int>>> s;
vector<int> enter;
int cnt = 0;
int sz;
int n, m;

int log(int a) {
    int cnt_ = 0;
    while (a != 1) {
        cnt_++;
        a = a >> 1;
    }
    return cnt_;
}

void dfs(int u, int depth) {
    enter[u] = cnt;
    b.push_back({depth, u});
    cnt++;
    for (int v : tree[u]) {
        dfs(v, depth + 1);
        b.push_back({depth, u});
        cnt++;
    }
}

void build() {
    s[0].resize(cnt);
    for (int i = 0; i < cnt; i++) {
        s[0][i] = b[i];
    }
    for (int i = 1; i < sz; i++) {
        s[i].resize(cnt);
        for (int j = 0; j + (1 << (i - 1)) < cnt; j++) {
            s[i][j] = min(s[i - 1][j], s[i - 1][j + (1 << (i - 1))]);
        }
    }
}

int get(unsigned int l, unsigned int r) {
    if (l > r) {
        swap(l, r);
    }
    unsigned int len = r - l;
    unsigned int pow = log(len);
    return min(s[pow][l], s[pow][r - (1 << pow)]).second;
}

int lca(int u, int v) {
    return get(min(enter[u], enter[v]), max(enter[v], enter[u]) + 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> n >> m;
    tree.resize(n);
    enter.resize(n);
    for (int i = 1; i < n; i++) {
        int x;
        cin >> x;
        tree[x].push_back(i);
    }
    dfs(0, 0);
    sz = log(cnt) + 1;
    s.resize(sz);
    build();
    long long a1, a2, x, y, z;
    cin >> a1 >> a2 >> x >> y >> z;
    unsigned long long ans = 0;
    int v = 0;
    for (int i = 0; i < m; i++) {
        v = lca((int) (a1 + v) % n, (int) a2);
        ans += v;
        a1 = (x * a1 + y * a2 + z) % n;
        a2 = (x * a2 + y * a1 + z) % n;
    }
    cout << ans;
    return 0;
}
