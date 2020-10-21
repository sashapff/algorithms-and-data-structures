#include <iostream>
#include <vector>

using namespace std;

int main() {
    string a;
    cin >> a;
    vector<int> z(a.size());
    int l = 0;
    z[0] = 0;
    for (int i = 1; i < (int) a.size(); i++) {
        if (i >= l + z[l]) {
            z[i] = 0;
        } else {
            z[i] = min(z[i - l], z[l] - (i - l + 1));
        }
        while (i + z[i] < (int) a.size() && a[z[i]] == a[i + z[i]]) {
            z[i]++;
        }
        if (i + z[i] > l + z[l]) {
            l = i;
        }
    }
    for (int i = 1; i < (int) a.size(); i++) {
        cout << z[i] << " ";
    }
    return 0;
}
