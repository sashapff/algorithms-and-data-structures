#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n;
    cin >> n;
    int size = 16;
    vector<pair<int, int>> a[12];
    for (int i = 0; i < 12; i++) {
        a[i] = vector<pair<int, int>>(0);
    }
    int cnt = 0;
    for (int i = 0; i < size; i += 2) {
        a[cnt].push_back(make_pair(i, i + 1));
    }
    cnt++;
    for (int i = 0; i < size; i += 4) {
        a[cnt].push_back(make_pair(i, i + 3));
        a[cnt].push_back(make_pair(i + 1, i + 2));
    }
    cnt++;
    for (int i = 0; i < size; i += 2) {
        a[cnt].push_back(make_pair(i, i + 1));
    }
    cnt++;
    for (int i = 0; i < size; i += 8) {
        a[cnt].push_back(make_pair(i, i + 7));
        a[cnt].push_back(make_pair(i + 1, i + 6));
        a[cnt].push_back(make_pair(i + 2, i + 5));
        a[cnt].push_back(make_pair(i + 3, i + 4));
    }
    cnt++;
    for (int i = 0; i < size; i += 8) {
        a[cnt].push_back(make_pair(i, i + 2));
        a[cnt].push_back(make_pair(i + 1, i + 3));
        a[cnt].push_back(make_pair(i + 4, i + 6));
        a[cnt].push_back(make_pair(i + 5, i + 7));
    }
    cnt++;
    for (int i = 0; i < size; i += 2) {
        a[cnt].push_back(make_pair(i, i + 1));
    }
    cnt++;
    for (int i = 0; i < size / 2; i++) {
        a[cnt].push_back(make_pair(i, size - i - 1));
    }
    cnt++;
    for (int i = 0; i < size; i += 8) {
        a[cnt].push_back(make_pair(i, i + 4));
        a[cnt].push_back(make_pair(i + 1, i + 5));
        a[cnt].push_back(make_pair(i + 2, i + 6));
        a[cnt].push_back(make_pair(i + 3, i + 7));
    }
    cnt++;
    for (int i = 0; i < size; i += 8) {
        a[cnt].push_back(make_pair(i, i + 2));
        a[cnt].push_back(make_pair(i + 1, i + 3));
        a[cnt].push_back(make_pair(i + 4, i + 6));
        a[cnt].push_back(make_pair(i + 5, i + 7));
    }
    cnt++;
    for (int i = 0; i < size; i += 2) {
        a[cnt].push_back(make_pair(i, i + 1));
    }
    cnt++;
    int m = 0;
    int k = 0;
    for (int i = 0; i < cnt; i++) {
        if (a[i].size() != 0) {
            int good = 0;
            for (auto j : a[i]) {
                if (j.first < n && j.second < n) {
                    good++;
                }
            }
            m += good;
            if (good != 0) {
                k++;
            }
        }
    }
    cout << n << " " << m << " " << k << endl;
    for (int i = 0; i < cnt; i++) {
        if (a[i].size() != 0) {
            int good = 0;
            for (auto j : a[i]) {
                if (j.first < n && j.second < n) {
                    good++;
                }
            }
            if (good > 0) {
                cout << good << " ";
                for (auto j : a[i]) {
                    if (j.first < n && j.second < n) {
                        cout << j.first + 1 << " " << j.second + 1 << " ";
                    }
                }
                cout << endl;
            }
        }
    }
    return 0;
}
