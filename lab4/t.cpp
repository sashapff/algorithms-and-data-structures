#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <math.h>

using namespace std;
#define ll long long

int n;
vector<vector<pair<int, int>>> a;
vector<ll> ans;
vector<ll> sumOfLengthDown;
vector<ll> sumOfLengthUp;
vector<ll> numberOfChildren;

int dfs(int u, int pr) {
    int cnt = 1;
    for (auto v : a[u]) {
        if (v.first != pr) {
            int d = dfs(v.first, u);
            cnt += d;
        }
    }
    numberOfChildren[u] = cnt;
    return cnt;
}

ll dfs2(int u, int pr) {
    ll cnt = 0;
    for (auto v : a[u]) {
        if (v.first != pr) {
            ll d = dfs2(v.first, u);
            cnt += d;
        }
    }
    cnt += numberOfChildren[u] - 1;
    sumOfLengthDown[u] = cnt;
    return cnt;
}

void dfs3(int u, int pr) {
    for (auto v : a[u]) {
        if (v.first != pr) {
            sumOfLengthUp[v.first] = sumOfLengthUp[u] + (n - numberOfChildren[v.first])
                    + sumOfLengthDown[u] - sumOfLengthDown[v.first] - numberOfChildren[v.first];
            dfs3(v.first, u);
        }
    }
}

void dfs4(int u, int pr) {
    for (auto v : a[u]) {
        if (v.first != pr) {
            dfs4(v.first, u);
            int d = (int) numberOfChildren[v.first];
            ans[v.second] = sumOfLengthDown[v.first] * (n - d) + sumOfLengthUp[v.first] * d;
        }
    }
}

int main() {
    freopen("treedp.in", "r", stdin);
    freopen("treedp.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> n;
    a = vector<vector<pair<int, int>>>(n);
    ans = vector<ll>(n);
    sumOfLengthDown = vector<ll>(n);
    sumOfLengthUp = vector<ll>(n);
    numberOfChildren = vector<ll>(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        a[u].push_back({v, i});
        a[v].push_back({u, i});
    }
    dfs(0, -1);
    dfs2(0, -1);
    dfs3(0, -1);
    dfs4(0, -1);
    for (int i = 0; i < n - 1; i++) {
        cout << ans[i] << endl;
    }
    return 0;
}
