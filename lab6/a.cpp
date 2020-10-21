#include <iostream>
#include <list>
#include <vector>
#include <random>
#include <ctime>

using namespace std;
#define ll long long

ll p = 1111111111111111111ll;
ll a, b;
int sz = 10;
vector<list<int>> vec = vector<list<int>>(sz);
ll numberOfElements = 0;

ll myRand() {
    mt19937 gen(static_cast<unsigned int>(time(NULL)));
    return (ll) uniform_int_distribution<unsigned int>(1, 1e9)(gen);
}

void build() {
    a = myRand();
    b = myRand();
}

void rehash() {
    if (sz < 1e6) {
        build();
        vector<list<int>> vec2;
        vec2.resize(sz *= 2);
        for (auto i : vec) {
            for (auto j : i) {
                int hash = (int) ((a * abs(j) + b) % p % sz);
                vec2[hash].push_front(j);
            }
        }
        vec = vec2;
    }
}

bool exist(int n, int hash) {
    for (auto it = vec[hash].begin(); it != vec[hash].end(); it++) {
        if (*it == n) {
            return true;
        }
    }
    return false;
}

void insert(int n, int hash) {
    if (!exist(n, hash)) {
        vec[hash].push_front(n);
        numberOfElements++;
        if (numberOfElements > sz) {
            rehash();
        }
    }
}

void erase(int n, int hash) {
    for (auto it = vec[hash].begin(); it != vec[hash].end(); it++) {
        if (*it == n) {
            vec[hash].erase(it);
            numberOfElements--;
            break;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("set.in", "r", stdin);
    freopen("set.out", "w", stdout);
    string s;
    int n;
    build();
    while (cin >> s) {
        cin >> n;
        int hash = (int) ((a * abs(n) + b) % p % sz);
        if (s[0] == 'i') {
            insert(n, hash);
        } else if (s[0] == 'e') {
            cout << (exist(n, hash) ? "true" : "false") << endl;
        } else {
            erase(n, hash);
        }
    }
    return 0;
}
