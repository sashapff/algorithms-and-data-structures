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
    if (u == nullptr) {
        return;
    }
    u->size = 1;
    if (u->left != nullptr) {
        u->size += u->left->size;
    }
    if (u->right != nullptr) {
        u->size += u->right->size;
    }
}

pair<Treap *, Treap *> split(Treap *u, int key) {
    if (u == nullptr) {
        return {nullptr, nullptr};
    }
    if (u->x >= key) {
        auto pv = split(u->left, key);
        u->left = pv.second;
        updateSize(u);
        return {pv.first, u};
    }
    auto pv = split(u->right, key);
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

Treap *insert(Treap *u, Treap *v) {
    if (u == nullptr) {
        return v;
    }
    if (v->y > u->y) {
        auto pv = split(u, v->x);
        return merge(merge(pv.first, v), pv.second);
    }
    if (u->x > v->x) {
        u->left = insert(u->left, v);
        updateSize(u->left);
        updateSize(u);
        return u;
    }
    u->right = insert(u->right, v);
    updateSize(u->right);
    updateSize(u);
    return u;
}

Treap *dlt(Treap *u, int key) {
    if (u->x == key) {
        return merge(u->left, u->right);
    }
    if (u->x > key) {
        u->left = dlt(u->left, key);
        updateSize(u->left);
        updateSize(u);
        return u;
    }
    u->right = dlt(u->right, key);
    updateSize(u->right);
    updateSize(u);
    return u;
}

int find(Treap *u, int key) {
    if (key == (u->right == nullptr ? 0 : u->right->size) + 1) {
        return u->x;
    }
    if (u->right != nullptr && u->right->size >= key) {
        return find(u->right, key);
    }
    return find(u->left, key - (u->right == nullptr ? 0 : u->right->size) - 1);
}

int main() {
    srand(static_cast<unsigned int>(time(NULL)));
    int n;
    cin >> n;
    Treap *root = nullptr;
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        int f, k;
        cin >> f >> k;
        if (f == 1) {
            root = insert(root, new Treap(k));
            cnt++;
        } else if (f == -1) {
            root = dlt(root, k);
            cnt--;
        } else {
            cout << find(root, k) << endl;
        }
    }
    return 0;
}
