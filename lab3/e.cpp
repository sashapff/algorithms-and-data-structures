#include <iostream>

using namespace std;

int a[2 * (int) (1e5) + 5];
int sizes[2 * (int) (1e5) + 5];
int nxt[2 * (int) (1e5) + 5];

int get(int u) {
    if (a[u] == u) {
        return u;
    }
    int prev = get(a[u]);
    a[u] = prev;
    return prev;
}

int getNext(int u) {
    if (nxt[u] == u) {
        return u;
    }
    int cur = getNext(nxt[u]);
    nxt[u] = cur;
    return cur;
}


void merge(int u, int v) {
    u = get(u);
    v = get(v);
    if (u != v) {
        a[v] = u;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        a[i] = i;
        nxt[i] = i;
        sizes[i] = 1;
    }
    for (int i = 0; i < q; i++) {
        int number, u, v;
        cin >> number >> u >> v;
        u--;
        v--;
        if (number == 1) {
            merge(u, v);
        }
        if (number == 2) {
            u = getNext(u);
            while (u < v) {
                merge(u, u + 1);
                nxt[u] = getNext(u + 1);
                u = nxt[u];
            }
        }
        if (number == 3) {
            if (get(u) == get(v)) {
                cout << "YES" << endl;
            } else {
                cout << "NO" << endl;
            }
        }
    }
    return 0;
}
