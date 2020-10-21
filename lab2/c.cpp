#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>

using namespace std;

int a[30000000];
int lft[30000000];
int rght[30000000];

int quickSort(int k, int n) {
    int tmp = rand() % n;
    int x = a[tmp];
    int l = 0;
    int r = 0;
    for (int i = 0; i < n; i++) {
        if (i != tmp) {
            if (a[i] == x) {
                int flag = rand() % 2;
                if (flag == 0) {
                    lft[l] = a[i];
                    l++;
                } else {
                    rght[r] = a[i];
                    r++;
                }
            } else if (a[i] < x) {
                lft[l] = a[i];
                l++;
            } else {
                rght[r] = a[i];
                r++;
            }
        }
    }
    if (l == k) {
        return x;
    }
    if (k < l) {
        for (int i = 0; i < l; i++) {
            a[i] = lft[i];
        }
        return quickSort(k, l);
    }
    for (int i = 0; i < r; i++) {
        a[i] = rght[i];
    }
    return quickSort(k - l - 1, r);
}

int main() {
    freopen("kth.in", "r", stdin);
    freopen("kth.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    srand(static_cast<unsigned int>(time(NULL)));
    int n, k;
    cin >> n >> k;
    k--;
    long long A, B, C;
    cin >> A >> B >> C >> a[0] >> a[1];
    for (int i = 2; i < n; i++) {
        a[i] = (int) (A * a[i - 2] + B * a[i - 1] + C);
    }
    cout << quickSort(k, n) << endl;
    return 0;
}
