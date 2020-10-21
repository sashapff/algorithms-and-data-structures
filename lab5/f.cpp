#include <iostream>
#include <vector>
#include <time.h>

using namespace std;

struct Treap {
    int x, y, size;
    bool hasNull;
    Treap *left, *right;

    Treap(int x, bool hasNull) : x(x), y(rand()), size(1),
    hasNull(hasNull), left(nullptr), right(nullptr) {}
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

void updateHasNull(Treap *u) {
    if (u == nullptr) {
        return;
    }
    if (u->x == -1) {
        u->hasNull = true;
    } else {
        u->hasNull = false;
    }
    if (u->left != nullptr) {
        u->hasNull |= u->left->hasNull;
    }
    if (u->right != nullptr) {
        u->hasNull |= u->right->hasNull;
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
        updateSize(pv.first);
        updateHasNull(pv.first);
        updateSize(pv.second);
        updateHasNull(pv.second);
        u->left = pv.second;
        updateSize(u->left);
        updateHasNull(u->left);
        updateSize(u);
        updateHasNull(u);
        return {pv.first, u};
    }
    auto pv = split(u->right, k - l - 1);
    updateSize(pv.first);
    updateHasNull(pv.first);
    updateSize(pv.second);
    updateHasNull(pv.second);
    u->right = pv.first;
    updateSize(u->right);
    updateHasNull(u->right);
    updateSize(u);
    updateHasNull(u);
    return {u, pv.second};
}

Treap *merge(Treap *u, Treap *v) {
    if (u == nullptr) {
        updateSize(v);
        updateHasNull(v);
        return v;
    }
    if (v == nullptr) {
        updateSize(u);
        updateHasNull(u);
        return u;
    }
    if (u->y > v->y) {
        u->right = merge(u->right, v);
        updateSize(u->right);
        updateHasNull(u->right);
        updateSize(u);
        updateHasNull(u);
        return u;
    }
    v->left = merge(u, v->left);
    updateSize(v->left);
    updateHasNull(v->left);
    updateSize(v);
    updateHasNull(v);
    return v;
}

Treap *deleteNull(Treap *u) {
    if (u->left != nullptr && u->left->hasNull) {
        u->left = deleteNull(u->left);
        updateSize(u->left);
        updateHasNull(u->left);
        updateSize(u);
        updateHasNull(u);
        return u;
    }
    if (u->x == -1) {
        return merge(u->left, u->right);
    }
    if (u->right != nullptr) {
        u->right = deleteNull(u->right);
        updateSize(u->right);
        updateHasNull(u->right);
        updateSize(u);
        updateHasNull(u);
    }
    return u;
}

Treap *insert(Treap *u, Treap *v, int place) {
    auto pv = split(u, place - 1);
    updateSize(pv.first);
    updateHasNull(pv.first);
    updateSize(pv.second);
    updateHasNull(pv.second);
    pv.second = deleteNull(pv.second);
    return merge(pv.first, merge(v, pv.second));
}

vector<int> ans;

void dfs(Treap *u) {
    if (u == nullptr) {
        return;
    }
    dfs(u->left);
    ans.push_back(u->x + 1);
    dfs(u->right);
}

int main() {
    int n, m;
    cin >> n >> m;
    Treap *root = nullptr;
    for (int i = 0; i < m; i++) {
        root = merge(root, new Treap(-1, true));
    }
    for (int i = 0; i < n; i++) {
        int l;
        cin >> l;
        root = insert(root, new Treap(i, false), l);
    }
    dfs(root);
    int i = static_cast<int>(ans.size() - 1);
    while (ans[i] == 0) {
        ans.pop_back();
        i--;
    }
    cout << ans.size() << endl;
    for (auto t : ans) {
        cout << t << " ";
    }
    return 0;
}
