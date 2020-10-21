#include <iostream>
#include <vector>

using namespace std;

vector<long long> d;
vector<int> a;
int n, sz;

int log(int a) {
    int cnt = 0;
    while (a != 0) {
        cnt++;
        a = a >> 1;
    }
    return cnt;
}

void build(int i, int l, int r) {
    if (r - l == 0) {
        return;
    }
    if (r - l == 1) {
        d[i] = a[l];
        return;
    }
    build(i * 2 + 1, l, (r + l) / 2);
    build(i * 2 + 2, (r + l) / 2, r);
    d[i] = (d[i * 2 + 1] + d[i * 2 + 2]) % (long long) 1e18;
}

long long get(int l, int r, int i, int L, int R) {
    if (r <= L || R <= l) {
        return 0;
    }
    if (l <= L && r >= R) {
        return d[i];
    }
    return (get(l, r, i * 2 + 1, L, (L + R) / 2)
    + get(l, r, i * 2 + 2, (L + R) / 2, R)) % (long long) 1e18;
}

void set(int i, int ind, int l, int r) {
    if (r - l == 0) {
        return;
    }
    if (r - l == 1) {
        d[ind] = a[l];
        return;
    }
    if (i < (r + l) / 2) {
        set(i, ind * 2 + 1, l, (r + l) / 2);
    } else {
        set(i, ind * 2 + 2, (r + l) / 2, r);
    }
    d[ind] = (d[ind * 2 + 1] + d[ind * 2 + 2]) % (long long) 1e18;
}

int main() {
    cin >> n;
    sz = 1 << log(n);
    a.resize(sz);
    d.resize(4 * sz);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = n; i < sz; i++) {
        a[i] = 0;
    }
    build(0, 0, sz);
    string s;
    while (cin >> s) {
        int l, r;
        cin >> l >> r;
        if (s == "sum") {
            cout << get(l - 1, r, 0, 0, sz) << endl;
        } else {
            a[l - 1] = r;
            set(l - 1, 0, 0, sz);
        }
    }
    return 0;
}
