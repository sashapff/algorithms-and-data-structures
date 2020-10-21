#include <iostream>
#include <vector>
#include <time.h>

using namespace std;

struct Treap {
    long long x, y, sum;
    Treap *left, *right;

    Treap(long long x) : x(x), y(rand()), sum(x), left(nullptr), right(nullptr) {}
};

void updateSum(Treap *u) {
    if (u == nullptr) {
        return;
    }
    u->sum = u->x;
    if (u->left != nullptr) {
        u->sum += u->left->sum;
    }
    if (u->right != nullptr) {
        u->sum += u->right->sum;
    }
}

pair<Treap *, Treap *> split(Treap *u, long long key) {
    if (u == nullptr) {
        return {nullptr, nullptr};
    }
    if (u->x >= key) {
        auto pv = split(u->left, key);
        u->left = pv.second;
        updateSum(u);
        return {pv.first, u};
    }
    auto pv = split(u->right, key);
    u->right = pv.first;
    updateSum(u);
    return {u, pv.second};
}

Treap *merge(Treap *u, Treap *v) {
    if (u == nullptr) {
        updateSum(v);
        return v;
    }
    if (v == nullptr) {
        updateSum(u);
        return u;
    }
    if (u->y > v->y) {
        u->right = merge(u->right, v);
        updateSum(u);
        return u;
    }
    v->left = merge(u, v->left);
    updateSum(v);
    return v;
}

Treap *insert(Treap *u, Treap *v) {
    if (u == nullptr) {
        return v;
    }
    if (v->y > u->y) {
        auto pv = split(u, v->x);
        v->left = pv.first;
        v->right = pv.second;
        updateSum(v);
        return v;
    }
    if (u->x > v->x) {
        u->left = insert(u->left, v);
        updateSum(u);
        return u;
    }
    u->right = insert(u->right, v);
    updateSum(u);
    return u;
}

bool exist(Treap *u, long long key) {
    if (u == nullptr) {
        return false;
    }
    if (u->x == key) {
        return true;
    }
    if (u->x < key) {
        return exist(u->right, key);
    }
    return exist(u->left, key);
}

int main() {
    int n;
    cin >> n;
    Treap *root = nullptr;
    long long lastAns = 0;
    for (int i = 0; i < n; i++) {
        char c;
        cin >> c;
        if (c == '+') {
            long long k;
            cin >> k;
            if (!exist(root, (k + lastAns) % 1000000000)) {
                root = insert(root, new Treap((k + lastAns) % 1000000000));
            }
            lastAns = 0;
        }
        if (c == '?') {
            long long l, r;
            cin >> l >> r;
            auto pv = split(root, l);
            auto pw = split(pv.second, r + 1);
            lastAns = 0;
            if (pw.first != nullptr) {
                lastAns = pw.first->sum;
            }
            cout << lastAns << endl;
            root = merge(pv.first, merge(pw.first, pw.second));
        }
    }
    return 0;
}
