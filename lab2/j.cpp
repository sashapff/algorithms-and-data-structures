#include <iostream>
#include <vector>

using namespace std;

long long sum = 0;
long long k;
long long bffer[(int) (3 * 1e6) + 6];
long long pref[(int) (3 * 1e6) + 6];

unsigned int A, B;
unsigned int cur = 0;

unsigned int nextRand24() {
    cur = cur * A + B;
    return (cur >> 8);
}

unsigned int nextRand32() {
    unsigned int a = nextRand24();
    unsigned int b = nextRand24();
    return ((a << 8) ^ b);
}

void mergeSort(int l, int r) {
    if (r - l == 1) {
        if (pref[l] >= k) {
            sum++;
        }
        return;
    }
    mergeSort(l, (l + r) / 2);
    mergeSort((l + r) / 2, r);
    int ll = 0;
    int rr = 0;
    int ms = (l + r) / 2;
    while (ms + rr < r) {
        while (ll + l < ms && pref[l + ll] + k <= pref[ms + rr]) {
            ll++;
        }
        sum += ll;
        rr++;
    }
    ll = 0;
    rr = 0;
    while (l + ll < ms && ms + rr < r) {
        if (pref[l + ll] <= pref[ms + rr]) {
            bffer[ll + rr] = pref[l + ll];
            ll++;
        } else {
            bffer[ll + rr] = pref[ms + rr];
            rr++;
        }
    }
    while (l + ll < ms) {
        bffer[ll + rr] = pref[l + ll];
        ll++;
    }
    while (ms + rr < r) {
        bffer[ll + rr] = pref[ms + rr];
        rr++;
    }
    for (int i = 0; i < ll + rr; i++) {
        pref[l + i] = bffer[i];
    }
}

int main() {
    int n;
    cin >> n >> k >> A >> B;
    for (int i = 0; i < n; i++) {
        int a = (int) nextRand32();
        if (i == 0) {
            pref[i] = a;
        } else {
            pref[i] = pref[i - 1] + a;
        }
    }
    mergeSort(0, n);
    cout << sum;
    return 0;
}
