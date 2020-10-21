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

const int sz = 5 * 1e5 + 1;
vector<int> prv(sz);
vector<int> depth(sz);
vector<vector<int>> jump(sz, vector<int>(log(sz)));

void add(int x, int y) {
    prv[y] = x;
    depth[y] = depth[x] + 1;
    jump[y][0] = prv[y];
    int len = log(depth[x]);
    for (int i = 1; i < len; i++) {
        jump[y][i] = jump[jump[y][i - 1]][i - 1];
    }
}

int get(int x, int y) {
    if (depth[x] < depth[y]) {
        swap(x, y);
    }
    for (int i = log(depth[x] - depth[y]); i >= 0; i--) {
        if (depth[jump[x][i]] >= depth[y]) {
            x = jump[x][i];
        }
        if (x == y) {
            break;
        }
    }
    int len = log(depth[x]);
    while (len >= 0 && jump[x][len] == jump[y][len]) {
        len--;
    }
    if (len >= 0) {
        x = jump[x][len];
        y = jump[y][len];
        while (x != y) {
            x = prv[x];
            y = prv[y];
        }
        return x;
    }
    if (x != y) {
        return prv[x];
    }
    return x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int k;
    cin >> k;
    for (int i = 0; i < k; i++) {
        string s;
        int x, y;
        cin >> s >> x >> y;
        if (s == "ADD") {
            add(x - 1, y - 1);
        } else {
            cout << get(x - 1, y - 1) + 1 << endl;
        }
    }
    return 0;
}
