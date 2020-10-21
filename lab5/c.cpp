#include <iostream>
#include <vector>
#include <time.h>

using namespace std;

struct Treap {
    int x, y, size;
    Treap *left, *right;

    Treap(int x) : x(x), y(rand()), size(1), left(nullptr), right(nullptr) {}
};

void updateSize(Treap *u) {
    u->size = 1;
    if (u->left != nullptr) {
        u->size += u->left->size;
    }
    if (u->right != nullptr) {
        u->size += u->right->size;
    }
}

pair<Treap *, Treap *> split(Treap *u, int k) {
    if (u == nullptr) {
        return {nullptr, nullptr};
    }
    int l = 0;
    if (u->left != nullptr) {
        l = u->left->size;
    }
    if (l >= k) {
        auto pv = split(u->left, k);
        u->left = pv.second;
        updateSize(u);
        return {pv.first, u};
    }
    auto pv = split(u->right, k - l - 1);
    u->right = pv.first;
    updateSize(u);
    return {u, pv.second};
}

Treap *merge(Treap *u, Treap *v) {
    if (u == nullptr) {
        return v;
    }
    if (v == nullptr) {
        return u;
    }
    if (u->y > v->y) {
        u->right = merge(u->right, v);
        updateSize(u);
        return u;
    }
    v->left = merge(u, v->left);
    updateSize(v);
    return v;
}

void dfs(Treap *u) {
    if (u == nullptr) {
        return;
    }
    dfs(u->left);
    cout << u->x << " ";
    dfs(u->right);
}

int main() {
    srand(static_cast<unsigned int>(time(NULL)));
    int n, m;
    cin >> n >> m;
    auto *root = new Treap(1);
    for (int i = 1; i < n; i++) {
        root = merge(root, new Treap(i + 1));
    }
    for (int i = 0; i < m; i++) {
        int l, r;
        cin >> l >> r;
        auto pv = split(root, l - 1);
        auto pw = split(pv.second, r - l + 1);
        root = merge(pw.first, pv.first);
        root = merge(root, pw.second);
    }
    dfs(root);
    return 0;
}
