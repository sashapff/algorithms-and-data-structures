#include <iostream>
#include <list>
#include <vector>
#include <random>
#include <ctime>

using namespace std;
#define ll long long
#define pss pair<string, string>

ll p = 1111111111111111111ll;
ll a;
int sz = 10;
vector<list<pss>> vec = vector<list<pss>>(sz);
ll numberOfElements = 0;

ll myRand() {
    mt19937 gen(static_cast<unsigned int>(time(NULL)));
    return (ll) uniform_int_distribution<unsigned int>(1, 1e9)(gen);
}

void build() {
    a = myRand();
}

int myHash(string x) {
    ll hash = 0;
    for (int i = 0; i < (int) x.length(); i++) {
        hash *= a;
        hash += x[i];
        hash %= p;
        hash %= sz;
    }
    return (int) hash;
}

void rehash() {
    if (sz < 1e6) {
        build();
        vector<list<pss>> vec2;
        vec2.resize(sz *= 2);
        for (auto i : vec) {
            for (auto j : i) {
                int hash = myHash(j.first);
                vec2[hash].push_front(j);
            }
        }
        vec = vec2;
    }
}

bool exist(string x, int hash) {
    for (auto it = vec[hash].begin(); it != vec[hash].end(); it++) {
        if ((*it).first == x) {
            return true;
        }
    }
    return false;
}

string get(string x, int hash) {
    for (auto it = vec[hash].begin(); it != vec[hash].end(); it++) {
        if ((*it).first == x) {
            return (*it).second;
        }
    }
    return "none";
}

void insert(string x, int hash, string y) {
    for (auto it = vec[hash].begin(); it != vec[hash].end(); it++) {
        if ((*it).first == x) {
            (*it).second = y;
            return;
        }
    }
    vec[hash].push_front({x, y});
    numberOfElements++;
    if (numberOfElements > sz) {
        rehash();
    }
}

void erase(string x, int hash) {
    for (auto it = vec[hash].begin(); it != vec[hash].end(); it++) {
        if ((*it).first == x) {
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
    freopen("map.in", "r", stdin);
    freopen("map.out", "w", stdout);
    string s;
    string x, y;
    build();
    while (cin >> s) {
        cin >> x;
        int hash = myHash(x);
        if (s[0] == 'p') {
            cin >> y;
            insert(x, hash, y);
        } else if (s[0] == 'g') {
            cout << get(x, hash) << endl;
        } else {
            erase(x, hash);
        }
    }
    return 0;
}
