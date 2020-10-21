#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n, c;
    cin >> n >> c;
    vector<int> pi(n);
    pi[0] = 0;
    for (int i = 1; i < n; i++) {
        cin >> pi[i];
    }
    long long ans = c;
    for (int i = 1; i < n; i++) {
        if (pi[i] == 0) {
            int j = pi[i - 1];
            int num = 1;
            while (j != 0) {
                if (pi[j] == 0) {
                    num++;
                }
                j = pi[j - 1];
            }
            ans *= (c - num);
            ans %= 1000000007;
        }
    }
    cout << ans;
    return 0;
}
