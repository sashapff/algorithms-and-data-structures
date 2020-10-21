#include <iostream>
#include <vector>

using namespace std;

int main() {
    string a;
    cin >> a;
    vector<int> pi(a.size());
    int j = 0;
    pi[0] = 0;
    for (int i = 1; i < (int) a.size(); i++) {
        while (j > 0 && a[i] != a[j]) {
            j = pi[j - 1];
        }
        if (a[i] == a[j]) {
            j++;
        }
        pi[i] = j;
    }
    for (auto i : pi) {
        cout << i << " ";
    }
    return 0;
}
