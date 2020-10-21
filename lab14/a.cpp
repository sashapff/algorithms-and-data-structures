#include <iostream>
#include <vector>

using namespace std;

vector<bool> prime(20000001, true);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int j = 2;
    while (j < 20000001) {
        while (prime[j] == false) {
            j++;
        }
        for (int i = 2 * j; i < 20000001; i += j) {
            prime[i] = false;
        }
        j++;
    }
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        cout << (prime[x] ? "YES\n" : "NO\n");
    }
    return 0;
}
