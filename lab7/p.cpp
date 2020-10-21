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

vector<int> depth;
vector<vector<int>> jump;

int n;

vector<vector<int>> children;
vector<int> prv;
vector<int> number;
vector<int> reverse_number;
vector<int> number_hld;
vector<bool> used;
vector<int> weight;
vector<int> ind_max_weight;
vector<int> begin_;
vector<int> size_;
vector<vector<long long>> delta;
int cnt_number = 0;
int hld_number = 0;

int lca(int x, int y) {
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

void dfs_weight(int u) {
    used[u] = true;
    weight[u] = 1;
    for (int v : children[u]) {
        if (!used[v]) {
            prv[v] = u;

            depth[v] = depth[u] + 1;
            jump[v][0] = prv[v];
            int len = log(depth[u]);
            for (int i = 1; i < len; i++) {
                jump[v][i] = jump[jump[v][i - 1]][i - 1];
            }

            dfs_weight(v);
            weight[u] += weight[v];
        }
    }
    for (int v : children[u]) {
        if (v != prv[u]) {
            if (weight[v] * 2 > weight[u]) {
                ind_max_weight[u] = v;
            }
        }
    }
}

void dfs_hld(int u) {
    used[u] = true;
    reverse_number[cnt_number] = u;
    number[u] = cnt_number++;
    number_hld[u] = hld_number;
    begin_[hld_number] = min(begin_[hld_number], number[u]);
    size_[hld_number]++;
    if (ind_max_weight[u] != -1) {
        dfs_hld(ind_max_weight[u]);
    }
    hld_number++;
    begin_.push_back(n + 1);
    size_.push_back(0);
    for (int v : children[u]) {
        if (!used[v]) {
            dfs_hld(v);
        }
    }
}

long long get(int num, int ind, int i, int l, int r) {
    if (l == r) {
        return 0;
    }
    if (l + 1 == r) {
        return delta[num][i];
    }
    if (ind < (l + r) / 2) {
        return (get(num, ind, i * 2 + 1, l, (l + r) / 2) + delta[num][i]);
    } else {
        return (get(num, ind, i * 2 + 2, (l + r) / 2, r) + delta[num][i]);
    }
}

void add(int num, int l, int r, int dt, int i, int L, int R) {
    if (l >= R || L >= r) {
        return;
    }
    if (l <= L && R <= r) {
        delta[num][i] += dt;
        return;
    }
    add(num, l, r, dt, i * 2 + 1, L, (R + L) / 2);
    add(num, l, r, dt, i * 2 + 2, (R + L) / 2, R);
}

void add(int u, int v, int dt) {
    while (begin_[number_hld[u]] > number[v]) {
        add(number_hld[u], 0, number[u] - begin_[number_hld[u]] + 1, dt,
            0, 0, size_[number_hld[u]]);
        u = prv[reverse_number[begin_[number_hld[u]]]];
    }
    add(number_hld[u], number[v] - begin_[number_hld[u]],
        number[u] - begin_[number_hld[u]] + 1, dt, 0, 0,
        size_[number_hld[u]]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cnt_number = 0;
    hld_number = 0;
    cin >> n;
    depth.resize(n);
    int k = log(n) + 1;
    children.resize(n);
    used.resize(n);
    weight.resize(n);
    jump.resize(n, vector<int>(k));
    prv.resize(n);
    number.resize(n);
    reverse_number.resize(n);
    number_hld.resize(n);
    ind_max_weight.resize(n, -1);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        children[u].push_back(v);
        children[v].push_back(u);
    }
    prv[0] = 0;
    dfs_weight(0);
    begin_.push_back(n + 1);
    size_.push_back(0);
    fill(used.begin(), used.end(), false);
    dfs_hld(0);
    delta.resize(hld_number);
    for (int i = 0; i < hld_number; i++) {
        delta[i].resize(size_[i] * 4);
    }
    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        char c;
        cin >> c;
        if (c == '?') {
            int u;
            cin >> u;
            u--;
            cout << get(number_hld[u], number[u] - begin_[number_hld[u]],
                        0, 0, size_[number_hld[u]]) << '\n';
        } else {
            int v, u, dt;
            cin >> v >> u >> dt;
            v--;
            u--;
            int w = lca(v, u);
            add(u, w, dt);
            add(v, w, dt);
            add(w, w, -dt);
        }
    }
    return 0;
}
