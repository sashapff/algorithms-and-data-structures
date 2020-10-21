#include <iostream>
#include <vector>

using namespace std;

unsigned int a, b;
unsigned int cur = 0;

unsigned int nextRand() {
    cur = cur * a + b;
    return cur >> 8;
}

unsigned int n = (1 << 24);
vector<unsigned int> w(n + 1);
vector<unsigned int> pref(n + 1);

int main() {
    int m, q;
    cin >> m >> q >> a >> b;
    for (int i = 0; i < m; i++) {
        unsigned int add = nextRand();
        unsigned int l = nextRand();
        unsigned int r = nextRand();
        if (l > r) swap(l, r);
        w[l] += add;
        w[r + 1] -= add;
    }
    unsigned int last = w[0];
    pref[0] = 0;
    pref[1] = w[0];
    for (unsigned int i = 1; i < n; i++) {
        pref[i + 1] = pref[i] + last + w[i];
        last = last + w[i];
    }
    unsigned int ans = 0;
    for (int i = 0; i < q; i++) {
        unsigned int l = nextRand();
        unsigned int r = nextRand();
        if (l > r) swap(l, r);
        ans += pref[r + 1] - pref[l];
    }
    cout << ans;
    return 0;
}
