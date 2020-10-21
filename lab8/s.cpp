#include <iostream>
#include <vector>
#include <set>

using namespace std;

vector<vector<int>> a;
vector<int> nxt;

int main() {
    freopen("dfs.in", "r", stdin);
    freopen("dfs.out", "w", stdout);
    int n, l;
    cin >> n >> l;
    vector<int> inpt;
    nxt.resize(n, -1);
    a.resize(n, vector<int>(n));
    for (int i = 0; i < l; i++) {
        int u;
        cin >> u;
        inpt.push_back(u - 1);
        if (i > 0) {
            a[inpt[i - 1]][inpt[i]] = 1;
        }
    }
    set<pair<int, int>> ans;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (a[i][j] == 1 && a[j][i] == 1) {
                ans.insert(make_pair(i, j));
            }
        }
    }
    vector<vector<int>> comps;
    vector<int> color(n);
    int ii = 0;
    while (ii < l) {
        int jj = l - 1;
        while (jj > 0 && inpt[jj] != inpt[ii]) {
            jj--;
        }
        vector<int> buf;
        for (int i = ii; i <= jj; i++) {
            buf.push_back(inpt[i]);
            color[inpt[i]] = static_cast<int>(comps.size());
        }
        comps.push_back(buf);
        ii = jj + 1;
    }
    vector<int> used(n, 0);
    for (int i = 0; i < (int) comps.size(); i++) {
        for (int j = 0; j < (int) comps[i].size() - 1; j++) {
            if (used[comps[i][j]] == 0) {
                used[comps[i][j]] = 1;
                if (used[comps[i][j + 1]] == 0) {
                    nxt[comps[i][j]] = comps[i][j + 1];
                } else {
                    for (int k = 0; k < n; k++) {
                        if (k != comps[i][j] && color[k] == color[comps[i][j]] && used[k] == 1 &&
                            nxt[k] < comps[i][j]) {
                            ans.insert(make_pair(comps[i][j], k));
                        }
                    }
                    used[comps[i][j]] = 2;
                }
            } else if (used[comps[i][j]] == 1) {
                if (used[comps[i][j + 1]] == 0) {
                    nxt[comps[i][j]] = comps[i][j + 1];
                } else {
                    for (int k = 0; k < n; k++) {
                        if (k != comps[i][j] && color[k] == color[comps[i][j]] && used[k] == 1 &&
                            nxt[k] < comps[i][j]) {
                            ans.insert(make_pair(comps[i][j], k));
                        }
                    }
                    used[comps[i][j]] = 2;
                }
            }
        }
    }
    cout << ans.size() << '\n';
    for (auto i : ans) {
        cout << i.first + 1 << " " << i.second + 1 << '\n';
    }
    return 0;
}
