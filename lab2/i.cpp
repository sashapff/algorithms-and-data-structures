#include <iostream>
#include <vector>

using namespace std;

struct Cashbox {
    int a, b, t;
    long long cnt;
};


vector<Cashbox> a;
int m, n, p;
long long tme;
Cashbox bffer[(int) 1e5 + 5];

void makeCnt() {
    for (int i = 0; i < m; i++) {
        if (a[i].a == 0) {
            if (a[i].b + a[i].t <= tme) {
                a[i].cnt = (long long) 1e9;
            } else {
              a[i].cnt = 0;
            }
        } else {
          a[i].cnt = max((tme - a[i].t - a[i].b) / a[i].a, 0ll);
        }
    }
}

void mergeSort(int l, int r) {
    if (r - l == 1) {
        return;
    }
    mergeSort(l, (l + r) / 2);
    mergeSort((l + r) / 2, r);
    int ll = 0;
    int rr = 0;
    int ms = (l + r) / 2;
    while (l + ll < ms && ms + rr < r) {
        if (a[l + ll].cnt > a[ms + rr].cnt) {
            bffer[ll + rr] = a[l + ll];
            ll++;
        } else {
            bffer[ll + rr] = a[ms + rr];
            rr++;
        }
    }
    while (l + ll < ms) {
        bffer[ll + rr] = a[l + ll];
        ll++;
    }
    while (ms + rr < r) {
        bffer[ll + rr] = a[ms + rr];
        rr++;
    }
    for (int i = 0; i < ll + rr; i++) {
        a[l + i] = bffer[i];
    }
}

bool check() {
    makeCnt();
    mergeSort(0, (int) a.size());
    long long cnt = 0;
    for (int i = 0; i < min(m, n); i++) {
        cnt += a[i].cnt;
    }
    if (cnt >= p) {
        return true;
    }
    return false;
}

int main() {
    cin >> m;
    for (int i = 0; i < m; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        Cashbox c;
        c.a = x;
        c.b = y;
        c.t = z;
        c.cnt = 0;
        a.push_back(c);
    }
    cin >> n >> p;
    long long l = -1;
    long long r = (long long) 1e12;
    while (r - l > 1) {
        tme = (l + r) / 2;
        if (check()) {
            r = tme;
        } else {
            l = tme;
        }
    }
    cout << r;
    return 0;
}
