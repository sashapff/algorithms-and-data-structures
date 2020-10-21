#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<bool> prime(1001, true);
vector<int> prime_vector;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int j = 2;
    while (j < 1001) {
        while (prime[j] == false) {
            j++;
        }
        for (int i = 2 * j; i < 1001; i += j) {
            prime[i] = false;
        }
        j++;
    }
    for (int i = 2; i < 1001; i++) {
        if (prime[i]) {
            prime_vector.push_back(i);
        }
    }
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        int k = 0;
        while (k < (int) prime_vector.size() && prime_vector[k] <= sqrt(x)) {
            if (x % prime_vector[k] == 0) {
                x /= prime_vector[k];
                cout << prime_vector[k] << ' ';
                k--;
            }
            k++;
        }
        cout << x << '\n';
    }
    return 0;
}
