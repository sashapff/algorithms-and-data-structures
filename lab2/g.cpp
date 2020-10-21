#include <iostream>
#include <vector>

using namespace std;

unsigned int A, B;
unsigned int cur = 0;

unsigned int nextRand24() {
    cur = cur * A + B;
    return cur >> 8;
}

unsigned int nextRand32() {
    unsigned int A = nextRand24();
    unsigned int B = nextRand24();
    return (B ^ (A << 8));
}

unsigned int a[(int) 1e5 + 5];
unsigned int b[(int) 1e5 + 5];
int n;
int k = 2;
int size = 1 << 16;
unsigned int cnt[1 << 16];

int get(unsigned int aa, int i) {
    if (i == 1) {
        return (aa & 0x0000ffff);
    }
    return ((aa >> 16) & 0x0000ffff);
}

void radixSort(int d) {
    for (int i = 0; i < size; i++) {
        cnt[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        cnt[get(a[i], d)]++;
    }
    unsigned int l = 0;
    for (int i = 0; i < size; i++) {
        int r = cnt[i];
        cnt[i] = l;
        l += r;
    }
    for (int i = 0; i < n; i++) {
        b[cnt[get(a[i], d)]] = a[i];
        cnt[get(a[i], d)]++;
    }
    for (int i = 0; i < n; i++) {
        a[i] = b[i];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int t;
    cin >> t >> n >> A >> B;
    for (int j = 0; j < t; j++) {
        for (int i = 0; i < n; i++) {
            a[i] = nextRand32();
        }
        for (int i = 0; i < k; i++) {
            radixSort(k - i - 1);
        }
        unsigned long long sum = 0;
        for (int i = 0; i < n; i++) {
            sum += 1ll * a[i] * (i + 1);
        }
        cout << sum << endl;
    }
    return 0;
}
