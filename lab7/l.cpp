#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
const unsigned int sz = 1 << 17;
vector<unsigned int> f(sz);

unsigned int a, b;
unsigned int cur = 0;
unsigned int ans = 0;

unsigned int nextRand17() {
    cur = cur * a + b;
    return cur >> 15;
}

unsigned int nextRand24() {
    cur = cur * a + b;
    return cur >> 8;
}

#define pii pair<unsigned int, unsigned int>

vector<vector<pair<unsigned int, pii>>> mas(4 * sz);

void build(unsigned int i, unsigned int l, unsigned int r) {
    if (r == l) {
        return;
    }
    if (r - l == 1) {
        mas[i].push_back({f[l], {0, 0}});
        return;
    }
    build(i * 2 + 1, l, (l + r) / 2);
    build(i * 2 + 2, (l + r) / 2, r);
//    mas[i] = merge(mas[i * 2 + 1], mas[i * 2 + 2]);
    mas[i].resize(mas[i * 2 + 1].size() + mas[i * 2 + 2].size());
    unsigned int i1 = 0;
    unsigned int i2 = 0;
    unsigned int ind = 0;
    while (i1 < mas[i * 2 + 1].size() && i2 < mas[i * 2 + 2].size()) {
        if (mas[i * 2 + 1][i1].first < mas[i * 2 + 2][i2].first) {
            mas[i][ind].second.first = i1;
            mas[i][ind].second.second = i2;
            mas[i][ind++].first = mas[i * 2 + 1][i1++].first;
        } else {
            mas[i][ind].second.first = i1;
            mas[i][ind].second.second = i2;
            mas[i][ind++].first = mas[i * 2 + 2][i2++].first;
        }
    }
    while (i1 < mas[i * 2 + 1].size()) {
        mas[i][ind].second.first = i1;
        mas[i][ind].second.second = i2;
        mas[i][ind++].first = mas[i * 2 + 1][i1++].first;
    }
    while (i2 < mas[i * 2 + 2].size()) {
        mas[i][ind].second.first = i1;
        mas[i][ind].second.second = i2;
        mas[i][ind++].first = mas[i * 2 + 2][i2++].first;
    }
}

unsigned int get(unsigned int i, unsigned int l, unsigned int r,
        unsigned int I, unsigned int L, unsigned int R) {
    if (r <= L || R <= l) {
        return 0;
    }
    if (l <= L && r >= R) {
        int ll = -1;
        int rr = static_cast<int>(mas[I].size());
        while (rr - ll != 1) {
            int m = (rr + ll) / 2;
            if (mas[I][m].first >= i) {
                rr = m;
            } else {
                ll = m;
            }
        }
        return static_cast<unsigned int>(mas[I].size() - ll - 1);
    }
    return get(i, l, r, I * 2 + 1, L, (L + R) / 2) + get(i, l, r, I * 2 + 2, (L + R) / 2, R);
}

unsigned int get(unsigned int l, unsigned int r, unsigned int x, unsigned int y) {
    return get(x, l, r, 0, 0, sz) - get(y + 1, l, r, 0, 0, sz);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int q;
    cin >> q >> a >> b;
    for (unsigned int i = 0; i < sz; i++) {
        f[i] = nextRand24();
    }
    build(0, 0, sz);
    for (int i = 0; i < q; i++) {
        unsigned int l = nextRand17();
        unsigned int r = nextRand17();
        if (l > r) swap(l, r);
        unsigned int x = nextRand24();
        unsigned int y = nextRand24();
        if (x > y) swap(x, y);
        unsigned int c = get(l, r + 1, x, y);
        ans += c;
        b += c;
    }
    cout << ans;
    return 0;
}
