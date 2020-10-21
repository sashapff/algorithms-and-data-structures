#include <iostream>
#include <vector>

using namespace std;

long long pow(long long x, long long a, long long m) {
    if (a == 0) {
        return 1;
    }
    if (a == 1) {
        return x;
    }
    if (a % 2 == 0) {
        long long cur = pow(x, a / 2, m);
        return (cur * cur) % m;
    } else {
        long long cur = pow(x, a / 2, m);
        return (((cur * cur) % m) * x) % m;
    }
}

long long gcdex(long long a, long long b, long long &x, long long &y) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    long long x1, y1;
    long long d = gcdex(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}

long long obr(long long x, long long m) {
    long long xx, yy;
    gcdex(x, m, xx, yy);
    return (xx % m + m) % m;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        long long a1, a2, n1, n2;
        cin >> a1 >> a2 >> n1 >> n2;
        if (n2 == 1) {
            cout << a1 << '\n';
        } else {
            long long k = (((n2 * 1000000000 + a2 - a1) % n2) * obr(n1, n2)) % n2;
            cout << (a1 + n1 * k) % (n1 * n2) << '\n';
        }
    }
    return 0;
}
