#include <iostream>
#include <vector>
#include <cmath>

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
    long long n, e, c;
    cin >> n >> e >> c;
    long long p = 1;
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) {
            p = i;
        }
    }
    long long d = obr(e, (p - 1) * (n / p - 1));
    cout << pow(c, d, n);
    return 0;
}
