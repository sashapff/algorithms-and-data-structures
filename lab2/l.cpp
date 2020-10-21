#include <iostream>

using namespace std;

struct Jewel {
    int u, w, number;
    long double cnt;
};

Jewel a[(int) 1e5 + 5];
Jewel bffer[(int) 1e5 + 5];
int k, n;
long double tme;

void makeCnt() {
    for (int i = 0; i < n; i++) {
        a[i].cnt = tme * a[i].w - a[i].u;
    }
}

template<typename Comparator>
void mergeSort(int l, int r, Comparator comp) {
    if (r - l == 1) {
        return;
    }
    mergeSort(l, (l + r) / 2, comp);
    mergeSort((l + r) / 2, r, comp);
    int ll = 0;
    int rr = 0;
    int ms = (l + r) / 2;
    while (l + ll < ms && ms + rr < r) {
        if (comp(a[l + ll], a[ms + rr])) {
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
    mergeSort(0, n, [](Jewel const &l, Jewel const &r) { return l.cnt <= r.cnt; });
    long double ans = 0;
    for (int i = 0; i < k; i++) {
        ans += a[i].cnt;
    }
    return ans < 1e-7;
}

int main() {
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        a[i].u = x;
        a[i].w = y;
        a[i].number = i + 1;
    }
    long double l = 0;
    long double r = 1e12;
    while (r - l > 1e-7) {
        tme = (l + r) / 2;
        if (check()) {
            l = tme;
        } else {
            r = tme;
        }
    }
    tme = 0;
    mergeSort(0, k, [](Jewel const &l, Jewel const &r) { return l.number <= r.number; });
    for (int i = 0; i < k; i++) {
        cout << a[i].number << " ";
    }
    return 0;
}
