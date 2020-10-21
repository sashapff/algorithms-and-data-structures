#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct point {
    int x, y, another_y;
    bool isOpen;
};

bool comp(point p1, point p2) {
    if (p1.x == p2.x) {
        return p1.isOpen > p2.isOpen;
    }
    return p1.x < p2.x;
}

int n;
vector<point> p;
vector<int> d_max;
vector<int> ind_max;
vector<int> delta;
int sz;

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
        ind_max[i] = l;
        return;
    }
    build(i * 2 + 1, l, (r + l) / 2);
    build(i * 2 + 2, (r + l) / 2, r);
    ind_max[i] = ind_max[i * 2 + 1];
}

void push(int i) {
    delta[i * 2 + 1] += delta[i];
    delta[i * 2 + 2] += delta[i];
    d_max[i] += delta[i];
    delta[i] = 0;
}

void add(int dt, int l, int r, int i, int L, int R) {
    if (r <= L || R <= l) {
        return;
    }
    if (l <= L && r >= R) {
        delta[i] += dt;
        return;
    }
    push(i);
    add(dt, l, r, i * 2 + 1, L, (R + L) / 2);
    add(dt, l, r, i * 2 + 2, (R + L) / 2, R);
    int res1 = d_max[i * 2 + 1] + delta[i * 2 + 1];
    int res2 = d_max[i * 2 + 2] + delta[i * 2 + 2];
    if (res1 >= res2) {
        d_max[i] = res1;
        ind_max[i] = ind_max[i * 2 + 1];
    } else {
        d_max[i] = res2;
        ind_max[i] = ind_max[i * 2 + 2];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> n;
    p.resize(n * 2);
    int dt = static_cast<int>(1e6);
    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        p[2 * i] = {x1 + dt, y1 + dt, y2 + dt, true};
        p[2 * i + 1] = {x2 + dt, y2 + dt, y1 + dt, false};
    }
    int m = 2 * dt + 1;
    sz = 1 << log(m);
    d_max.resize(4 * sz, 0);
    ind_max.resize(4 * sz);
    build(0, 0, sz);
    delta.resize(4 * sz, 0);
    sort(p.begin(), p.end(), comp);
    int cnt = 1;
    int x = p[0].x;
    int y = p[0].y;
    for (int i = 0; i < n * 2; i++) {
        if (p[i].isOpen) {
            add(1, p[i].y, p[i].another_y + 1, 0, 0, sz);
            auto res = d_max[0];
            if (res > cnt) {
                cnt = res;
                y = ind_max[0];
                x = p[i].x;
            }
        } else {
            add(-1, p[i].another_y, p[i].y + 1, 0, 0, sz);
        }
    }
    cout << cnt << '\n' << x - dt << " " << y - dt;
    return 0;
}
