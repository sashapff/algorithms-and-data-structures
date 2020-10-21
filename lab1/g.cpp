#include <iostream>
#include <algorithm>
#include <math.h>

using namespace std;

pair<int, int> *vec_1;
pair<int, int> *vec_2;
int i_1 = 0;
int i_2 = 0;
int size_1 = 1;
int size_2 = 1;
int const INF = INT_MAX;

pair<int, int> get_1() {
    if (i_1 != 0) {
        return (*(vec_1 + i_1 - 1));
    }
    return make_pair(INF, INF);
}

pair<int, int> get_2() {
    if (i_2 != 0) {
        return (*(vec_2 + i_2 - 1));
    }
    return make_pair(INF, INF);
}

void push_1(int m) {
    if (i_1 >= size_1) {
        pair<int, int> *new_vec = new pair<int, int>[size_1];
        for (int k = 0; k < i_1; k++) {
            *(new_vec + k) = *(vec_1 + k);
        }
        size_1 *= 2;
        delete[] vec_1;
        vec_1 = new pair<int, int>[size_1];
        for (int k = 0; k < i_1; k++) {
            *(vec_1 + k) = *(new_vec + k);
        }
        delete[] new_vec;
    }
    (*(vec_1 + i_1)).first = m;
    (*(vec_1 + i_1)).second = min(m, get_1().second);
    i_1++;
}

void swap_vec() {
    delete[] vec_2;
    vec_2 = new pair<int, int>[i_1];
    (*(vec_2)).first = (*(vec_1 + i_1 - 1)).first;
    (*(vec_2)).second = (*(vec_2)).first;
    for (int k = 1; k < i_1; k++) {
        (*(vec_2 + k)).first = (*(vec_1 + i_1 - k - 1)).first;
        (*(vec_2 + k)).second = min((*(vec_2 + k)).first, (*(vec_2 + k - 1)).second);
    }
    i_2 = i_1;
    size_2 = size_1;
    delete[] vec_1;
    i_1 = 0;
    size_1 = 1;
    vec_1 = new pair<int, int>[size_1];
}

void pop_2() {
    if (i_2 <= 0) {
        swap_vec();
    }
    i_2--;
    
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m, k;
    long long a, b, c;
    cin >> n >> m >> k >> a >> b >> c;
    vec_1 = new pair<int, int>[size_1];
    vec_2 = new pair<int, int>[size_2];
    int cnt = 0;
    long long sum = 0;
    int last = 0;
    int last_last = 0;
    for (int i = 0; i < k; i++) {
        int x;
        cin >> x;
        push_1(x);
        cnt++;
        if (cnt == m) {
            if (min(get_1().second, get_2().second) != INF) {
                sum += (long long) min(get_1().second, get_2().second);
            }
            pop_2();
            cnt--;
        }
        last_last = last;
        last = x;
    }
    for (int i = k; i < n; i++) {
        int x = (int) (a * last_last + b * last + c);
        push_1(x);
        cnt++;
        if (cnt == m) {
            if (min(get_1().second, get_2().second) != INF) {
                sum += (long long) min(get_1().second, get_2().second);
            }
            pop_2();
            cnt--;
        }
        last_last = last;
        last = x;
    }
    cout << sum;
    return 0;
}