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
    return cnt + 1;
}

int n;
vector<int> prv;
vector<int> depth;
vector<vector<pair<int, int>>> jump;

void add(int x, int y, int weight) {
    prv[y] = x;
    depth[y] = depth[x] + 1;
    jump[y][0].first = prv[y];
    jump[y][0].second = weight;
    int len = log(n) + 1;
    for (int i = 1; i < len; i++) {
        jump[y][i].first = jump[jump[y][i - 1].first][i - 1].first;
        jump[y][i].second = min(jump[jump[y][i - 1].first][i - 1].second, jump[y][i - 1].second);
    }
}

pair<int, int> get(int x, int y) {
    int min_weight = INT32_MAX;
    if (depth[x] < depth[y]) {
        swap(x, y);
    }
    for (int i = log(depth[x] - depth[y]); i >= 0; i--) {
        if (depth[jump[x][i].first] >= depth[y]) {
            min_weight = min(min_weight, jump[x][i].second);
            x = jump[x][i].first;
        }
    }
    int len = log(depth[x]);
    while (len >= 0 && x != y) {
        while (len >= 0 && jump[x][len] == jump[y][len]) {
            len--;
        }
        if (len >= 0) {
            min_weight = min(min_weight, jump[x][len].second);
            min_weight = min(min_weight, jump[y][len].second);
            x = jump[x][len].first;
            y = jump[y][len].first;
        }
    }
    if (x != y) {
        min_weight = min(min_weight, jump[x][0].second);
        min_weight = min(min_weight, jump[y][0].second);
        return {prv[x], min_weight};
    }
    return {x, min_weight};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> n;
    prv.resize(n);
    depth.resize(n);
    jump.resize(n, vector<pair<int, int>>(log(n) + 10, {0, INT32_MAX}));
    for (int i = 1; i < n; i++) {
        int pr, w;
        cin >> pr >> w;
        add(pr - 1, i, w);
    }
    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        int l, r;
        cin >> l >> r;
        cout << get(l - 1, r - 1).second << '\n';
    }
    return 0;
}
