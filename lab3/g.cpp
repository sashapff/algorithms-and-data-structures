#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct point {
    int pos, number;
    long long val;
    int flag;

    bool operator<(const point &other) const {
        if (pos == other.pos) {
            if (flag == other.flag) {
                return val < other.val;
            }
            return flag < other.flag;
        }
        return pos < other.pos;
    }
};

const int size = 600000 + 3;
vector<point> a;
int pos[size];
long long maxVal = 1ll * INT32_MAX + 10;

void siftDown(int ind) {
    int left = ind * 2;
    int right = ind * 2 + 1;
    int newInd;
    int sz = (int) a.size();
    if (left >= sz && right >= sz) {
        return;
    }
    if (right >= sz) {
        newInd = left;
        if (a[ind].val <= a[newInd].val) {
            return;
        }
        swap(a[ind], a[newInd]);
        pos[a[ind].number] = ind;
        pos[a[newInd].number] = newInd;
        siftDown(newInd);
        return;
    }
    if (a[right].val < a[left].val) {
        newInd = right;
    } else {
        newInd = left;
    }
    if (a[ind].val <= a[newInd].val) {
        return;
    }
    swap(a[ind], a[newInd]);
    pos[a[ind].number] = ind;
    pos[a[newInd].number] = newInd;
    siftDown(newInd);
}

void siftUp(int ind) {
    if (ind == 1) {
        return;
    }
    if (a[ind].val >= a[ind / 2].val) {
        return;
    }
    swap(a[ind], a[ind / 2]);
    pos[a[ind].number] = ind;
    pos[a[ind / 2].number] = ind / 2;
    siftUp(ind / 2);
}

void push(point t) {
    a.push_back(t);
    pos[t.number] = (int) (a.size() - 1);
    siftUp((int) (a.size() - 1));
}

void decreaseKey(int number, long long val) {
    int ind = pos[number];
    a[ind].val = val;
    siftDown(ind);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n, m;
    cin >> n >> m;
    vector<point> b;
    b.resize(2 * m);
    for (int i = 0; i < m; i++) {
        int l, r;
        long long val;
        cin >> l >> r >> val;
        point t;
        t.pos = l - 1;
        t.val = -val;
        t.number = i;
        t.flag = 0;
        b[2 * i] = t;
        point p;
        p.pos = r - 1;
        p.val = -val;
        p.number = i;
        p.flag = 1;
        b[2 * i + 1] = p;
    }
    point sml;
    sml.val = -maxVal;
    sml.pos = m + 1;
    sml.number = 2 * m + 1;
    a.push_back(sml);
    sort(b.begin(), b.end());
    int j = 0;
    for (int i = 0; i < n; i++) {
        while (j < 2 * m && b[j].pos <= i && b[j].flag == 0) {
            push(b[j]);
            j++;
        }
        cout << (a[1].val == maxVal ? 0 : -a[1].val) << " ";
        while (j < 2 * m && b[j].pos <= i && b[j].flag == 1) {
            decreaseKey(b[j].number, maxVal);
            j++;
        }
    }
    return 0;
}
