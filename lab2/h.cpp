#include <iostream>
#include <vector>

using namespace std;

long long inv = 0;

vector<int> mergeSort(vector<int> a) {
    if (a.size() == 1) {
        return a;
    }
    vector<int> lft = vector<int>(a.size() / 2);
    vector<int> rght = vector<int>(a.size() - a.size() / 2);
    for (int i = 0; i < (int) a.size() / 2; i++) {
        lft[i] = a[i];
    }
    for (int i = (int) a.size() / 2; i < (int) a.size(); i++) {
        rght[i - a.size() / 2] = a[i];
    }
    lft = mergeSort(lft);
    rght = mergeSort(rght);
    int l = 0;
    int r = 0;
    int cnt = 0;
    while (l < (int) lft.size() && r < (int) rght.size()) {
        if (lft[l] <= rght[r]) {
            a[cnt] = lft[l];
            l++;
        } else {
            a[cnt] = rght[r];
            r++;
            inv += lft.size() - l;
        }
        cnt++;
    }
    for (int i = l; i < (int) lft.size(); i++) {
        a[cnt] = lft[i];
        cnt++;
    }
    for (int i = r; i < (int) rght.size(); i++) {
        a[cnt] = rght[i];
        cnt++;
    }
    return a;
}

int n, m, A, B;
unsigned int cur = 0;

unsigned int nextRand24() {
    cur = cur * A + B;
    return cur >> 8;
}

int main() {
    cin >> n >> m >> A >> B;
    vector<int> a;
    for (int i = 0; i < n; i++) {
        a.push_back(nextRand24() % m);
    }
    a = mergeSort(a);
    cout << inv;
    return 0;
}
