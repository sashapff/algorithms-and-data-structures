#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
#define ll long long

int main() {
    freopen("meetings.in", "r", stdin);
    freopen("meetings.out", "w", stdout);
    ll n, k;
    cin >> n >> k;
    vector<pair<ll, ll>> a = vector<pair<ll, ll>>(n);
    ll sz = (1ll << n);
    vector<ll> mood = vector<ll>(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second >> mood[i];
    }
    vector<ll> bal = vector<ll>(sz);
    vector<ll> cnt = vector<ll>(sz);
    vector<ll> pr = vector<ll>(sz);
    vector<bool> good = vector<bool>(sz);
    for (int mask = 0; mask < sz; mask++) {
        bal[mask] += k;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                bal[mask] += mood[i];
                cnt[mask]++;
            }
        }
    }
    good[0] = true;
    for (int mask = 0; mask < sz; mask++) {
        for (int i = 0; i < n; i++) {
            ll t = (1 << i);
            if ((mask & t) && bal[mask - t] >= a[i].first && bal[mask - t] <= a[i].second) {
                good[mask] = good[mask - t] || good[mask];
                if (good[mask - t]) {
                    pr[mask] = i;
                }
            }
        }
    }
    ll maxlen = 0;
    int cur = 0;
    for (int mask = 0; mask < sz; mask++) {
        if (cnt[mask] > maxlen && good[mask]) {
            maxlen = cnt[mask];
            cur = mask;
        }
    }
    vector<ll> ans;
    while (cur != 0) {
        ans.push_back(pr[cur]);
        cur -= (1 << pr[cur]);
    }
    reverse(ans.begin(), ans.end());
    cout << ans.size() << endl;
    for (auto i : ans) {
        cout << i + 1 << " ";
    }
    return 0;
}
