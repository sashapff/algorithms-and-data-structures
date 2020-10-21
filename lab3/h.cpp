#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int prv[200000 + 2];
bool color[200000 + 2];

int get(int u) {
    if (u == prv[u]) {
        return u;
    }
    int top_u = get(prv[u]);
    color[u] = !color[prv[u]];
    if (color[u] != color[top_u]) {
        prv[u] = top_u;
    }
    return top_u;
}

void merge(int u, int v) {
    int top_u = get(u);
    int top_v = get(v);
    if (top_u != top_v) {
        if ((color[u] ^ color[v]) == (color[top_u] ^ color[top_v])) {
            prv[top_u] = top_v;
            color[top_u] = !color[top_v];
        } else {
            if (color[u] ^ color[top_u]) {
                prv[top_v] = u;
            } else {
                prv[top_u] = v;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n, m;
    int shift = 0;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        prv[i] = i;
    }
    for (int i = 0; i < m; i++) {
        int type, a, b;
        cin >> type >> a >> b;
        if (type == 0) {
            merge((a + shift) % n, (b + shift) % n);
        } else {
            get((a + shift) % n);
            get((b + shift) % n);
            if (color[(a + shift) % n] == color[(b + shift) % n]) {
                cout << "YES" << endl;
                shift++;
            } else {
                cout << "NO" << endl;
            }
        }
    }
    return 0;
}
