#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct query {
    int l, r, number, block;
    long long ans;
};
bool comp1(query p1, query p2) {
    if (p1.block == p2.block) {
        if (p1.r == p2.r) {
            return p1.number < p2.number;
        }
        return p1.r < p2.r;
    }
    return p1.block < p2.block;
}
bool comp2(query p1, query p2) {
    return p1.number < p2.number;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    vector<query> q(m);
    int p = (int) sqrt(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        q[i].l = x - 1;
        q[i].r = y - 1;
        q[i].number = i;
        q[i].block = q[i].l / p;
    }
    sort(q.begin(), q.end(), comp1);
    int l = q[0].l;
    int r = q[0].r;
    vector<int> cnt(1e6 + 1, 0);
    long long ans = 0;
    for (int i = l; i <= r; i++) {
        ans -= 1ll * a[i] * cnt[a[i]] * cnt[a[i]];
        cnt[a[i]]++;
        ans += 1ll * a[i] * cnt[a[i]] * cnt[a[i]];
    }
    q[0].ans = ans;
    for (int i = 1; i < m; i++) {
        int new_l = q[i].l;
        int new_r = q[i].r;
        if (l < new_l) {
            for (int j = l; j < new_l; j++) {
                ans -= 1ll * a[j] * cnt[a[j]] * cnt[a[j]];
                cnt[a[j]]--;
                ans += 1ll * a[j] * cnt[a[j]] * cnt[a[j]];
            }
        } else {
            for (int j = l - 1; j >= new_l; j--) {
                ans -= 1ll * a[j] * cnt[a[j]] * cnt[a[j]];
                cnt[a[j]]++;
                ans += 1ll * a[j] * cnt[a[j]] * cnt[a[j]];
            }
        }
        if (new_r > r) {
            for (int j = r + 1; j <= new_r; j++) {
                ans -= 1ll * a[j] * cnt[a[j]] * cnt[a[j]];
                cnt[a[j]]++;
                ans += 1ll * a[j] * cnt[a[j]] * cnt[a[j]];
            }
        } else {
            for (int j = r; j > new_r; j--) {
                ans -= 1ll * a[j] * cnt[a[j]] * cnt[a[j]];
                cnt[a[j]]--;
                ans += 1ll * a[j] * cnt[a[j]] * cnt[a[j]];
            }
        }
        q[i].ans = ans;
        l = new_l;
        r = new_r;
    }
    sort(q.begin(), q.end(), comp2);
    for (auto i : q) {
        cout << i.ans << '\n';
    }
    return 0;
}
