#include <iostream>
#include <list>
#include <vector>
#include <random>
#include <ctime>

using namespace std;

uint32_t p = 2971215073;
uint32_t szX = 10;
vector<uint32_t> szY = vector<uint32_t>(1e6);
vector<list<pair<string, vector<list<string>>>>> vec
        = vector<list<pair<string, vector<list<string>>>>>(szX);
uint32_t cntX = 0;
vector<uint32_t> cntY = vector<uint32_t>(1e6);


uint32_t myHashX(string x) {
    uint32_t hash = 0;
    for (char i : x) {
        hash *= p;
        hash += i;
    }
    hash %= p;
    hash %= szX;
    return (uint32_t) hash;
}

uint32_t myHashY(string y, uint32_t sz) {
    uint32_t hash = 0;
    for (char i : y) {
        hash *= p;
        hash += i;
    }
    hash %= p;
    hash %= sz;
    return (uint32_t) hash;
}

void rehash() {
    if (cntX > szX * 10 && szX < 1e6) {
        szX *= 2;
        vector<list<pair<string, vector<list<string>>>>> vec2;
        vec2.resize(szX);

        for (uint32_t i = 0; i < szX / 2; i++) {
            for (auto it = vec[i].begin(); it != vec[i].end(); it++) {
                uint32_t hashX = myHashX((*it).first);
                vec2[hashX].push_front({(*it).first, (*it).second});
                szY[hashX] = szY[i];
            }
        }

        vec.swap(vec2);
    }
}


void get(const string &x, uint32_t hashX) {
    uint32_t cnt = 0;
    for (auto &it : vec[hashX]) {
        if (it.first == x) {
            for (uint32_t hashY = 0; hashY < szY[hashX]; hashY++) {
                for (auto it2 = (it.second)[hashY].begin();
                     it2 != (it.second)[hashY].end(); it2++) {
                    cnt++;
                }
            }
        }
    }
    cout << cnt << " ";
    for (auto &it : vec[hashX]) {
        if (it.first == x) {
            for (uint32_t hashY = 0; hashY < szY[hashX]; hashY++) {
                for (auto &it2 : (it.second)[hashY]) {
                    cout << it2 << " ";
                }
            }
        }
    }
    cout << '\n';
}

void insert(string x, uint32_t hashX, const string &y, uint32_t hashY) {
    for (auto &it : vec[hashX]) {
        if (it.first == x) {
            for (auto &it2 : (it.second)[hashY]) {
                if (it2 == y) {
                    return;
                }
            }
            (it.second)[hashY].push_front(y);
            cntY[hashX]++;
            if (cntY[hashX] > szY[hashX] * 10) {
                szY[hashX] *= 2;
                for (auto it = vec[hashX].begin(); it != vec[hashX].end(); it++) {
                    vector<list<string>> v = vector<list<string>>(szY[hashX]);
                    for (uint32_t j = 0; j < szY[hashX] / 2; j++) {
                        for (auto it2 = ((*it).second)[j].begin();
                             it2 != ((*it).second)[j].end(); it2++) {
                            uint32_t hashY = myHashY((*it2), szY[hashX]);
                            v[hashY].push_front(*it2);
                        }
                    }
                    (*it).second.swap(v);
                }
            }
            return;
        }
    }

    vec[hashX].push_front({x, vector<list<string>>(szY[hashX])});
    (*vec[hashX].begin()).second[hashY].push_front(y);
    cntX++;
    cntY[hashX]++;
    rehash();
}

void erase(const string &x, uint32_t hashX, const string &y, uint32_t hashY) {
    for (auto &it : vec[hashX]) {
        if (it.first == x) {
            for (auto it2 = (it.second)[hashY].begin();
                 it2 != (it.second)[hashY].end(); it2++) {
                if ((*it2) == y) {
                    it.second[hashY].erase(it2);
                    cntY[hashX]--;
                    return;
                }
            }
        }
    }
}

void deleteAll(const string &x, uint32_t hashX) {
    for (auto it = vec[hashX].begin(); it != vec[hashX].end(); it++) {
        if ((*it).first == x) {
            cntY[hashX] -= (uint32_t) vec[hashX].size();
            vec[hashX].erase(it);
            cntX--;
            return;
        }
    }
}

int main() {
    freopen("multimap.in", "r", stdin);
    freopen("multimap.out", "w", stdout);
    string s;
    string x, y;
    for (int i = 0; i < 1e6; i++) {
        szY[i] = 10;
    }
    while (cin >> s) {
        cin >> x;
        uint32_t hashX = myHashX(x);
        if (s[0] == 'p') {
            cin >> y;
            uint32_t hashY = myHashY(y, szY[hashX]);
            insert(x, hashX, y, hashY);
        } else if (s[0] == 'g') {
            get(x, hashX);
            cout << endl;
        } else if (s == "delete") {
            cin >> y;
            uint32_t hashY = myHashY(y, szY[hashX]);
            erase(x, hashX, y, hashY);
        } else {
            deleteAll(x, hashX);
        }
    }
    return 0;
}
