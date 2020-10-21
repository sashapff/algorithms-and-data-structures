#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;
int m, n;
vector<vector<int>> right_;
vector<vector<int>> left_;
vector<int> mt_left;
vector<int> mt_right;
vector<bool> used;
vector<bool> used_left;
vector<bool> used_right;

void dfs(int u, int f) {
    if (f % 2 == 0) {
        used_left[u] = true;
        for (auto v : left_[u]) {
            if (!used_right[v]) {
                dfs(v, f + 1);
            }
        }
    } else {
        used_right[u] = true;
        if (mt_right[u] != -1 && !used_left[mt_right[u]]) {
            dfs(mt_right[u], f + 1);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> m >> n;
    right_.resize(n);
    left_.resize(m);
    mt_left.resize(m);
    mt_right.resize(n, -1);
    used.resize(m, false);
    used_left.resize(m, false);
    used_right.resize(n, false);
    for (int i = 0; i < m; i++) {
        int k;
        cin >> k;
        for (int j = 0; j < k; j++) {
            int u;
            cin >> u;
            right_[u - 1].push_back(i);
            left_[i].push_back(u - 1);
        }
    }
    for (int i = 0; i < m; i++) {
        int u;
        cin >> u;
        mt_left[i] = u - 1;
        if (u - 1 != -1) {
            mt_right[u - 1] = i;
            used[i] = true;
        }
    }
    for (int i = 0; i < m; i++) {
        if (!used[i]) {
            dfs(i, 0);
        }
    }
    int ans_left = 0;
    int ans_right = 0;
    for (int i = 0; i < m; i++) {
        if (!used_left[i]) {
            ans_left++;
        }
    }
    for (int i = 0; i < n; i++) {
        if (used_right[i]) {
            ans_right++;
        }
    }
    cout << ans_left + ans_right << '\n';
    cout << ans_left << " ";
    for (int i = 0; i < m; i++) {
        if (!used_left[i]) {
            cout << i + 1 << " ";
        }
    }
    cout << '\n' << ans_right << " ";
    for (int i = 0; i < n; i++) {
        if (used_right[i]) {
            cout << i + 1 << " ";
        }
    }
    return 0;
}
