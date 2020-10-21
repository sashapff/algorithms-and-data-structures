#include <iostream>
#include <vector>

using namespace std;

vector<long long> d_min;
vector<long long> val;
vector<long long> delta;
vector<long long> a;
int n, sz;
long long INF = 1e18;

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
        d_min[i] = a[l];
        return;
    }
    build(i * 2 + 1, l, (r + l) / 2);
    build(i * 2 + 2, (r + l) / 2, r);
    d_min[i] = min(d_min[i * 2 + 1], d_min[i * 2 + 2]);
}

void push(int i) {
    delta[i * 2 + 1] += delta[i];
    delta[i * 2 + 2] += delta[i];
    if (val[i] != INF) val[i] += delta[i];
    d_min[i] += delta[i];
    delta[i] = 0;
}

void push_val(int i) {
    d_min[i] = val[i];
    val[i * 2 + 1] = val[i];
    val[i * 2 + 2] = val[i];
    delta[i * 2 + 1] = 0;
    delta[i * 2 + 2] = 0;
    val[i] = INF;
}

long long get(int l, int r, int i, int L, int R) {
    if (r <= L || R <= l) {
        return INF;
    }
    if (l <= L && r >= R) {
        return (val[i] != INF ? val[i] : d_min[i]) + delta[i];
    }
    push(i);
    if (val[i] != INF) {
        push_val(i);
    }
    return min(get(l, r, i * 2 + 1, L, (L + R) / 2), get(l, r, i * 2 + 2, (L + R) / 2, R));
}

void set(long long x, int l, int r, int i, int L, int R) {
    if (r <= L || R <= l) {
        return;
    }
    if (l <= L && r >= R) {
        delta[i] = 0;
        val[i] = x;
        return;
    }
    push(i);
    if (val[i] != INF) {
        push_val(i);
    }
    set(x, l, r, i * 2 + 1, L, (R + L) / 2);
    set(x, l, r, i * 2 + 2, (R + L) / 2, R);
    d_min[i] = min((val[i * 2 + 1] != INF ? val[i * 2 + 1] : d_min[i * 2 + 1]) + delta[i * 2 + 1],
            (val[i * 2 + 2] != INF ? val[i * 2 + 2] : d_min[i * 2 + 2]) + delta[i * 2 + 2]);
}

void add(long long dt, int l, int r, int i, int L, int R) {
    if (r <= L || R <= l) {
        return;
    }
    if (l <= L && r >= R) {
        delta[i] += dt;
        return;
    }
    push(i);
    if (val[i] != INF) {
        push_val(i);
    }
    add(dt, l, r, i * 2 + 1, L, (R + L) / 2);
    add(dt, l, r, i * 2 + 2, (R + L) / 2, R);
    d_min[i] = min((val[i * 2 + 1] != INF ? val[i * 2 + 1] : d_min[i * 2 + 1]) + delta[i * 2 + 1],
            (val[i * 2 + 2] != INF ? val[i * 2 + 2] : d_min[i * 2 + 2]) + delta[i * 2 + 2]);
}

int main() {
    cin >> n;
    sz = 1 << log(n);
    a.resize(sz);
    d_min.resize(4 * sz);
    val.resize(4 * sz, INF);
    delta.resize(4 * sz, 0);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = n; i < sz; i++) {
        a[i] = INF;
    }
    build(0, 0, sz);
    string s;
    while (cin >> s) {
        int l, r;
        cin >> l >> r;
        if (s == "min") {
            cout << get(l - 1, r, 0, 0, sz) << endl;
        } else if (s == "set") {
            long long x;
            cin >> x;
            set(x, l - 1, r, 0, 0, sz);
        } else {
            long long x;
            cin >> x;
            if (x == 20) {
                cerr << "kek" << endl;
            }
            add(x, l - 1, r, 0, 0, sz);
        }
    }
    return 0;
}
