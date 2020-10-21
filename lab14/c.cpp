#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, x, h;
    cin >> n >> x;
    int size = (n + 1) / 2;
    vector<bool> prime(size, true);
    h = 0;
    if (2 <= n) {
        h = h * x + 2;
    }
    int j = 3;
    while (j <= n) {
        while (j <= n && !prime[j / 2]) {
            j += 2;
        }
        for (int i = 2 * j; i <= n; i += j) {
            if (i % 2 != 0) {
                prime[i / 2] = false;
            }
        }
        j += 2;
    }
    for (int i = 1; i < size; i++) {
        if (prime[i]) {
            h = h * x + i * 2 + 1;
        }
    }
    cout << h;
    return 0;
}
