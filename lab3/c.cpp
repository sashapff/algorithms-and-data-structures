#include <iostream>

using namespace std;

pair<int, int> a[5000000];
int len = 1;

void siftDown(int ind) {
    int left = ind * 2;
    int right = ind * 2 + 1;
    int newInd;
    if (a[right].first < a[left].first) {
        newInd = right;
    } else {
        newInd = left;
    }
    if (a[ind].first <= a[newInd].first) {
        return;
    }
    swap(a[ind], a[newInd]);
    siftDown(newInd);
}

void siftUp(int ind) {
    if (a[ind].first >= a[ind / 2].first) {
        return;
    }
    swap(a[ind], a[ind / 2]);
    siftUp(ind / 2);
}

void push(int x, int number) {
    a[len] = make_pair(x, number);
    siftUp(len);
    len++;
}

void extractMin() {
    if (len == 1) {
        cout << "*\n";
        return;
    }
    cout << a[1].first << " " << a[1].second << endl;
    len--;
    a[1] = a[len];
    a[len].first = INT32_MAX;
    siftDown(1);
}

void decreaseKey(int number, int val) {
    int ind = -1;
    for (int i = 1; i < len; i++) {
        if (a[i].second == number) {
            ind = i;
        }
    }
    if (ind == -1) {
        return;
    }
    a[ind].first = val;
    siftUp(ind);
    siftDown(ind);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    string s;
    int n, m;
    int cnt = 1;
    for (int i = 0; i < 1000000; i++) {
        a[i].first = INT32_MAX;
    }
    a[0].first = INT32_MIN;
    while (cin >> s) {
        if (s == "push") {
            cin >> n;
            push(n, cnt);
        }
        if (s == "extract-min") {
            extractMin();
        }
        if (s == "decrease-key") {
            cin >> n >> m;
            decreaseKey(n, m);
        }
        cnt++;
    }
    return 0;
}
