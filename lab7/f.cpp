#include <iostream>
#include <vector>

using namespace std;

struct matrix {
    int d00, d01, d10, d11;
};

int r, m;

matrix mul(matrix x, matrix y) {
    matrix ans;
    ans.d00 = (x.d00 * y.d00 + x.d01 * y.d10) % r;
    ans.d01 = (x.d00 * y.d01 + x.d01 * y.d11) % r;
    ans.d10 = (x.d10 * y.d00 + x.d11 * y.d10) % r;
    ans.d11 = (x.d10 * y.d01 + x.d11 * y.d11) % r;
    return ans;
}

vector<matrix> d;
vector<matrix> a;
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
    d[i] = mul(d[i * 2 + 1], d[i * 2 + 2]);
}

matrix get(int l, int r, int i, int L, int R) {
    if (r <= L || R <= l) {
        return {1, 0, 0, 1};
    }
    if (l <= L && r >= R) {
        return d[i];
    }
    return mul(get(l, r, i * 2 + 1, L, (L + R) / 2), get(l, r, i * 2 + 2, (L + R) / 2, R));
}

// void set(int i, int ind, int l, int r) {
//    if (r - l == 0) {
//        return;
//    }
//    if (r - l == 1) {
//        d[ind] = a[l];
//        return;
//    }
//    if (i < (r + l) / 2) {
//        set(i, ind * 2 + 1, l, (r + l) / 2);
//    } else {
//        set(i, ind * 2 + 2, (r + l) / 2, r);
//    }
//    d[ind] = (d[ind * 2 + 1] + d[ind * 2 + 2]) % (long long) 1e18;
//}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> r >> n >> m;
    sz = 1 << log(n);
    a.resize(sz);
    d.resize(4 * sz);
    for (int i = 0; i < n; i++) {
        cin >> a[i].d00 >> a[i].d01 >> a[i].d10 >> a[i].d11;
    }
    for (int i = n; i < sz; i++) {
        a[i] = {1, 0, 0, 1};
    }
    build(0, 0, sz);
    for (int i = 0; i < m; i++) {
        int l, r;
        cin >> l >> r;
        auto ans = get(l - 1, r, 0, 0, sz);
        cout << ans.d00 << " " << ans.d01 << '\n';
        cout << ans.d10 << " " << ans.d11 << '\n';
        cout << '\n';
    }
    return 0;
}
