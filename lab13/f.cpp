#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

string s;

struct node {
    int prev;
    vector<int> nxt = vector<int>(26, -1);
    int l, r, link = -1;

    node(int prev, int l, int r) : prev(prev), l(l), r(r) {}
};

struct position {
    int v, m;
};

vector<node> tree;
position pos = {0, 0};

bool end(position p) {
    return p.m == tree[p.v].r - tree[p.v].l;
}

position nxt(position p, int l, int r) {
    while (l < r) {
        if (end(p)) {
            p = {tree[p.v].nxt[s[l] - 'a'], 0};
            if (p.v == -1) {
                return p;
            }
        } else {
            if (s[tree[p.v].l + p.m] != s[l]) {
                return {-1, -1};
            } else if (r - l < tree[p.v].r - tree[p.v].l - p.m) {
                return {p.v, p.m + r - l};
            } else {
                l += tree[p.v].r - tree[p.v].l - p.m;
                p.m = tree[p.v].r - tree[p.v].l;
            }
        }
    }
    return p;
}

int split(position p) {
    if (end(p)) {
        return p.v;
    }
    if (p.v == 0) {
        return tree[p.v].prev;
    }
    tree.emplace_back(tree[p.v].prev, tree[p.v].l, tree[p.v].l + p.m);
    tree[tree.size() - 1].nxt[s[tree[p.v].l + p.m] - 'a'] = p.v;
    tree[tree[p.v].prev].nxt[s[tree[p.v].l] - 'a'] = tree.size() - 1;
    tree[p.v].l += p.m;
    tree[p.v].prev = (int) tree.size() - 1;
    return (int) tree.size() - 1;
}

int getLink(int v) {
    if (tree[v].prev == -1) {
        return 0;
    }
    if (tree[v].link != -1) {
        return tree[v].link;
    }
    int u = getLink(tree[v].prev);
    tree[v].link = split(nxt({u, tree[u].r - tree[u].l},
                             tree[v].l + (tree[v].prev == 0), tree[v].r));
    return tree[v].link;
}

void build() {
    for (int i = 0; i < (int) s.size(); i++) {
        while (true) {
            position next = nxt(pos, i, i + 1);
            if (next.v != -1) {
                pos = next;
                break;
            } else {
                int v = split(pos);
                tree.emplace_back(v, i, s.size());
                tree[v].nxt[s[i] - 'a'] = tree.size() - 1;
                pos.v = getLink(v);
                pos.m = tree[pos.v].r - tree[pos.v].l;
                if (!v) {
                    break;
                }
            }
        }
    }
}

long long dfs(int u) {
    long long ans = tree[u].r - tree[u].l;
    for (int i = 0; i < 26; i++) {
        if (tree[u].nxt[i] != -1) {
            ans += dfs(tree[u].nxt[i]);
        }
    }
    return ans;
}

int main() {
    cin >> s;
    tree.emplace_back(-1, -1, -1);
    build();
    cout << dfs(0);
    return 0;
}
