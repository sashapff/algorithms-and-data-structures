#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

struct node {
    int prev;
    int c;
    vector<int> nxt = vector<int>(26, -1);

    node(int prev, char c) : prev(prev), c(c) {}
};

vector<node> bor;

void dfs(int u) {
    if (u != 0) {
        cout << bor[u].prev + 1 << " " << u + 1 << " " << (char) ('a' + bor[u].c) << '\n';
    }
    for (int i = 0; i < 26; i++) {
        if (bor[u].nxt[i] != -1) {
            dfs(bor[u].nxt[i]);
        }
    }
}

int main() {
    string s;
    cin >> s;
    bor.emplace_back(0, 0);
    for (int start = 0; start < (int) s.size(); start++) {
        int v = 0;
        for (int i = start; i < (int) s.size(); i++) {
            if (bor[v].nxt[s[i] - 'a'] != -1) {
                v = bor[v].nxt[s[i] - 'a'];
            } else {
                bor.emplace_back(v, s[i] - 'a');
                v = bor[v].nxt[s[i] - 'a'] = bor.size() - 1;
            }
        }
    }
    cout << bor.size() << " " << bor.size() - 1 << '\n';
    dfs(0);
    return 0;
}
