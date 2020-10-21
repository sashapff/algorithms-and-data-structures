#include <iostream>
#include <vector>

using namespace std;

int k;
int i = 2;
int cnt = 1;
vector<string> a;
vector<int> b;

void printAnswer(int n) {
    if (k <= 0) {
        return;
    }
    if (k > 0 && n == cnt) {
        for (int j = 0; j < n; j++) {
            cout << a[b[j]];
        }
        cout << endl;
        k--;
        return;
    }
    b[n] = 0;
    printAnswer(n + 1);
    b[n] = 1;
    printAnswer(n + 1);
}

int main() {
    // Aa == BB
    // AaAa == BBBB == AaBB == BBAa
    // AaAaAa == AaAaBB == AaBBAa == BBAaAa == ...
    cin >> k;
    a = {"Aa", "BB"};
    while (i < k) {
        i *= 2;
        cnt++;
    }
    b.resize(cnt);
    printAnswer(0);
    return 0;
}
