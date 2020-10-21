#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <stack>

using namespace std;

int m, n;
vector<vector<int>> left_(150);
vector<vector<int>> left_r(150, vector<int>(150));
vector<vector<int>> right_(150);
vector<vector<int>> right_r(150, vector<int>(150));
vector<int> mt_right(150);
vector<int> mt_left(150);
vector<bool> used(150);
vector<bool> usedd(150);
vector<bool> used_left(150);
vector<bool> used_right(150);

bool try_kuhn(int u) {
    if (used[u]) {
        return false;
    }
    used[u] = true;
    for (auto v : left_[u]) {
        if (mt_right[v] == -1 || try_kuhn(mt_right[v])) {
            mt_right[v] = u;
            mt_left[u] = v;
            usedd[u] = true;
            return true;
        }
    }
    return false;
}

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
    int k;
    cin >> k;
    for (int kk = 0; kk < k; kk++) {
        cin >> m >> n;
        for (int i = 0; i < m; i++) {
            left_[i].resize(0);
            used_left[i] = false;
            mt_left[i] = -1;
            usedd[i] = false;
            for (int j = 0; j < n; j++) {
                left_r[i][j] = 0;
            }
        }
        for (int i = 0; i < n; i++) {
            right_[i].resize(0);
            used_right[i] = false;
            mt_right[i] = -1;
            for (int j = 0; j < m; j++) {
                right_r[i][j] = 0;
            }
        }
        for (int i = 0; i < m; i++) {
            while (true) {
                int j;
                cin >> j;
                if (j == 0) {
                    break;
                }
                left_r[i][j - 1] = 1;
                right_r[j - 1][i] = 1;
            }
        }
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (left_r[i][j] == 0) {
                    left_[i].push_back(j);
                    right_[j].push_back(i);
                }
            }
        }
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < m; j++) {
                used[j] = false;
            }
            try_kuhn(i);
        }
        for (int i = 0; i < m; i++) {
            if (!usedd[i]) {
                dfs(i, 0);
            }
        }
        int ans_left = 0;
        int ans_right = 0;
        for (int i = 0; i < m; i++) {
            if (used_left[i]) {
                ans_left++;
            }
        }
        for (int i = 0; i < n; i++) {
            if (!used_right[i]) {
                ans_right++;
            }
        }
        cout << ans_left + ans_right << '\n';
        cout << ans_left << " " << ans_right << '\n';
        for (int i = 0; i < m; i++) {
            if (used_left[i]) {
                cout << i + 1 << " ";
            }
        }
        cout << '\n';
        for (int i = 0; i < n; i++) {
            if (!used_right[i]) {
                cout << i + 1 << " ";
            }
        }
        cout << '\n';
        cout << '\n';
    }
    return 0;
}
