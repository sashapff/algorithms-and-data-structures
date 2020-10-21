#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int log(int a) {
    int cnt = 0;
    while (a != 0) {
        cnt++;
        a = a >> 1;
    }
    return cnt;
}

vector<int> prv;
vector<int> depth;
vector<int> used;
vector<vector<int>> jump;
vector<vector<int>> children;


int get(int x, int y) {
    if (depth[x] < depth[y]) {
        swap(x, y);
    }
    for (int i = log(depth[x] - depth[y]); i >= 0; i--) {
        if (depth[jump[x][i]] >= depth[y]) {
            x = jump[x][i];
        }
        if (depth[x] == depth[y]) {
            break;
        }
    }
    int len = log(depth[x]);
    while (len >= 0 && x != y) {
        while (len >= 0 && jump[x][len] == jump[y][len]) {
            len--;
        }
        if (len >= 0) {
            x = jump[x][len];
            y = jump[y][len];
        }
    }
    if (x != y) {
        return prv[x];
    }
    return x;
}

int n;

void dfs(int u, int dep) {
    used[u] = 1;
    depth[u] = dep;
    jump[u][0] = prv[u];
    int len = log(n) + 1;
    for (int i = 1; i < len; i++) {
        jump[u][i] = jump[jump[u][i - 1]][i - 1];
    }
    for (int v : children[u]) {
        if (used[v] != 1) {
            prv[v] = u;
            dfs(v, dep + 1);
        }
    }
}

int root = 0;

int lca(int u, int v) {
    int a = get(u, v);
    int b = get(root, u);
    int c = get(root, v);
    if (depth[a] >= depth[b] && depth[a] >= depth[c]) {
        return a;
    }
    if (depth[b] >= depth[a] && depth[b] >= depth[c]) {
        return b;
    }
    return c;
}


void chroot(int u) {
    root = u;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> n;
    while (n > 0) {
        root = 0;
        children.resize(n);
        prv.resize(n);
        depth.resize(n);
        jump.resize(n);
        used.resize(n);
        for (int i = 0; i < n; i++) {
            children[i].resize(0);
            jump[i].resize(log(n) + 1);
            used[i] = 0;
        }
        for (int i = 1; i < n; i++) {
            int u, v;
            cin >> u >> v;
            u--;
            v--;
            children[u].push_back(v);
            children[v].push_back(u);
        }
        dfs(0, 0);
        int m;
        cin >> m;
        for (int i = 0; i < m; i++) {
            char c;
            cin >> c;
            if (c == '?') {
                int u, v;
                cin >> u >> v;
                u--;
                v--;
                cout << lca(u, v) + 1 << '\n';
            } else {
                int u;
                cin >> u;
                u--;
                chroot(u);
            }
        }
        cin >> n;
    }
    return 0;
}
