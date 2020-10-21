#include <iostream>

using namespace std;

int *vec_1;
int *vec_2;
int i_1 = 0;
int i_2 = 0;
int size_1 = 1;
int size_2 = 1;

void push_1(int m) {
    if (i_1 >= size_1) {
        int *new_vec = new int[size_1];
        for (int k = 0; k < size_1; k++) {
            *(new_vec + k) = *(vec_1 + k);
        }
        size_1 *= 2;
        vec_1 = new int[size_1];
        for (int k = 0; k < size_1 / 2; k++) {
            *(vec_1 + k) = *(new_vec + k);
        }
        delete[] new_vec;
    }
    *(vec_1 + i_1) = m;
    i_1++;
}

void push_2(int m) {
    if (i_2 >= size_2) {
        int *new_vec = new int[size_2];
        for (int k = 0; k < size_2; k++) {
            *(new_vec + k) = *(vec_2 + k);
        }
        size_2 *= 2;
        vec_2 = new int[size_2];
        for (int k = 0; k < size_2 / 2; k++) {
            *(vec_2 + k) = *(new_vec + k);
        }
        delete[] new_vec;
    }
    *(vec_2 + i_2) = m;
    i_2++;
}

int get_1() {
    return *(vec_1 + i_1 - 1);
}

int get_2() {
    return *(vec_2 + i_2 - 1);
}

void pop_1() {
    i_1--;
}

void pop_2() {
    if (i_2 <= 0) {
        while (i_1 > 0) {
            push_2(get_1());
            pop_1();
        }
    }
    cout << *(vec_2 + i_2 - 1) << endl;
    i_2--;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    char c;
    cin >> n;
    vec_1 = new int[size_1];
    vec_2 = new int[size_2];
    for (int i = 0; i < n; i++) {
        cin >> c;
        if (c == '+') {
            cin >> m;
            push_1(m);
        } else {
            pop_2();
        }
    }
    return 0;
}
