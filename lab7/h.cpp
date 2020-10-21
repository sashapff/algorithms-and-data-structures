#include <iostream>
#include <vector>
#include <set>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    set<int> set;
    for (int i = 0; i < n; i++) {
        set.insert(i + 1);
    }
    for (int i = 0; i < m; i++) {
        string s;
        int x;
        cin >> s >> x;
        if (s == "enter") {
            int next;
            if (set.upper_bound(x - 1) == set.end()) {
                next = *set.upper_bound(0);
            } else {
                next = *set.upper_bound(x - 1);
            }
            cout << next << endl;
            set.erase(next);
        } else {
            set.insert(x);
        }
    }
    return 0;
}
