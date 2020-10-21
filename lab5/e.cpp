#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Treap {
    int x, y, num;
    Treap *left, *right, *prev;

    Treap(int x, int y, int num) : x(x), y(y), num(num),
                                   left(nullptr), right(nullptr), prev(nullptr) {}
};

bool comp(Treap *a, Treap *b) {
    return a->x < b->x;
}

struct Answer {
    int prev, left, right;

    Answer(int prev, int left, int right) : prev(prev), left(left), right(right) {}
};

vector<Answer *> ans;

void dfs(Treap *u, int prev) {
    if (u == nullptr) {
        return;
    }
    ans[u->num - 1] = new Answer(prev, (u->left != nullptr ? u->left->num : 0),
                                 (u->right != nullptr ? u->right->num : 0));
    dfs(u->left, u->num);
    dfs(u->right, u->num);
}

int main() {
    int n;
    cin >> n;
    vector<Treap *> a = vector<Treap *>(n);
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        a[i] = new Treap(x, y, i + 1);
    }
    sort(a.begin(), a.end(), comp);


    for (int i = 1; i < n; i++) {
        if (a[i]->y > a[i - 1]->y) {
            a[i - 1]->right = a[i];
            a[i]->prev = a[i - 1];
        } else {
            auto v = a[i - 1];
            while (v->prev != nullptr && v->prev->y > a[i]->y) {
                v = v->prev;
            }
            if (v->prev != nullptr) {
                v->prev->right = a[i];
                a[i]->prev = v->prev;
            }
            a[i]->left = v;
            v->prev = a[i];
        }
    }

    auto root = a[0];
    while (root->prev != nullptr) {
        root = root->prev;
    }
    ans = vector<Answer *>(n);
    cout << "YES" << endl;
    dfs(root, 0);
    for (auto i : ans) {
        cout << i->prev << " " << i->left << " " << i->right << endl;
    }
    return 0;
}
