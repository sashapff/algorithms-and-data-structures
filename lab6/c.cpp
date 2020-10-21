#include <iostream>
#include <list>
#include <vector>
#include <random>
#include <ctime>

using namespace std;
#define ll long long

struct Node {
    string x, y;
    Node *next, *prev;

    Node(string x, string y, Node *next, Node *prev) :
            x(x), y(y), next(next), prev(prev) {}
};

ll p = 1111111111111111111ll;
ll a;
int sz = 10;
vector<list<Node *>> vec = vector<list<Node *>>(sz);
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
        vector<list<Node *>> vec2;
        vec2.resize(sz *= 2);
        for (auto i : vec) {
            for (auto j : i) {
                int hash = myHash(j->x);
                vec2[hash].push_front(j);
            }
        }
        vec = vec2;
    }
}

string get(string x, int hash) {
    for (auto it = vec[hash].begin(); it != vec[hash].end(); it++) {
        if ((*it)->x == x) {
            return (*it)->y;
        }
    }
    return "none";
}

Node *insert(string x, int hash, string y, Node *l) {
    for (auto it = vec[hash].begin(); it != vec[hash].end(); it++) {
        if ((*it)->x == x) {
            (*it)->y = y;
            return l;
        }
    }
    Node *p = new Node(x, y, nullptr, l);
    if (l != nullptr) {
        l->next = p;
    }
    vec[hash].push_front(p);
    numberOfElements++;
    if (numberOfElements > sz) {
        rehash();
    }
    return p;
}

void erase(string x, int hash) {
    for (auto it = vec[hash].begin(); it != vec[hash].end(); it++) {
        if ((*it)->x == x) {
            auto t = (*it);
            if (t->prev != nullptr) {
                t->prev->next = t->next;
            }
            if (t->next != nullptr) {
                t->next->prev = t->prev;
            }
            vec[hash].erase(it);
            numberOfElements--;
            break;
        }
    }
}

string next(string x, int hash) {
    for (auto it = vec[hash].begin(); it != vec[hash].end(); it++) {
        if ((*it)->x == x) {
            if ((*it)->next == nullptr) {
                return "none";
            }
            return (*it)->next->y;
        }
    }
    return "none";
}

string prev(string x, int hash) {
    for (auto it = vec[hash].begin(); it != vec[hash].end(); it++) {
        if ((*it)->x == x) {
            if ((*it)->prev == nullptr) {
                return "none";
            }
            return (*it)->prev->y;
        }
    }
    return "none";
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    freopen("linkedmap.in", "r", stdin);
    freopen("linkedmap.out", "w", stdout);
    string s;
    string x, y;
    build();
    Node *last = nullptr;
    while (cin >> s) {
        cin >> x;
        int hash = myHash(x);
        if (s[0] == 'p' && s[1] == 'u') {
            cin >> y;
            last = insert(x, hash, y, last);
        } else if (s[0] == 'g') {
            cout << get(x, hash) << endl;
        } else if (s[0] == 'n') {
            cout << next(x, hash) << endl;
        } else if (s[0] == 'p') {
            cout << prev(x, hash) << endl;
        } else {
            if (last != nullptr && last->x == x) {
                last = last->prev;
                if (last != nullptr) {
                    last->next = nullptr;
                }
            }
            erase(x, hash);
        }
    }
    return 0;
}
