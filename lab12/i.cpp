#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct node {
    vector<int> letters = vector<int>(26, -1);
    vector<int> jump = vector<int>(26, -1);
    int prev = -1;
    int link = -1;
    int prev_letter;
    int num = -1;
    int leaf_link = -1;

    node() = default;

    node(int p, int l) {
        prev = p;
        prev_letter = l;
    }
};

int n;
vector<string> a;
string s;
vector<node> bor;
vector<bool> used;


void add(string p, int index) {
    int j = 0;
    for (int i = 0; i < (int) p.size(); i++) {
        if (bor[j].letters[p[i] - 'a'] == -1) {
            bor.emplace_back(j, p[i] - 'a');
            bor[j].letters[p[i] - 'a'] = bor.size() - 1;
        }
        j = bor[j].letters[p[i] - 'a'];
    }
    bor[j].num = index;
}

int jump(int u, int c);

int get_link(int u) {
    if (bor[u].link != -1) {
        return bor[u].link;
    }
    if (u == 0 || bor[u].prev == 0) {
        return bor[u].link = 0;
    }
    return bor[u].link = jump(get_link(bor[u].prev), bor[u].prev_letter);
}

int jump(int u, int c) {
    if (bor[u].jump[c] != -1) {
        return bor[u].jump[c];
    }
    if (bor[u].letters[c] != -1) {
        return bor[u].jump[c] = bor[u].letters[c];
    }
    if (u == 0) {
        return bor[u].jump[c] = 0;
    }
    return bor[u].jump[c] = jump(get_link(u), c);
}

int get_leaf_link(int u) {
    if (bor[u].leaf_link != -1) {
        return bor[u].leaf_link;
    }
    int link = get_link(u);
    if (bor[link].num != -1) {
        return bor[u].leaf_link = link;
    }
    if (link == 0) {
        return bor[u].leaf_link = 0;
    }
    return bor[u].leaf_link = get_leaf_link(link);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> s;
    cin >> n;
    a.resize(n);
    used.resize(n, false);
    bor.emplace_back();
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        add(a[i], i);
    }
    int node = 0;
    for (int i = 0; i < (int) s.length(); i++) {
        node = jump(node, s[i] - 'a');
        int j = node;
        while (j != 0) {
            if (bor[j].num != -1) {
                used[bor[j].num] = true;
            }
            j = get_leaf_link(j);
        }
    }
    for (int i = 0; i < n; i++) {
        cout << (used[i] ? "Yes" : "No") << '\n';
    }
    return 0;
}

