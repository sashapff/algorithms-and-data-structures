#include <iostream>

using namespace std;

int *vec;
int i = 0;
int size = 1;

void push(int m) {
    if (i >= size) {
        int *new_vec = new int[size];
        for (int k = 0; k < size; k++) {
            *(new_vec + k) = *(vec + k);
        }
        size *= 2;
        vec = new int[size];
        for (int k = 0; k < size / 2; k++) {
            *(vec + k) = *(new_vec + k);
        }
        delete[] new_vec;
    }
    *(vec + i) = m;
    i++;
}

void pop() {
    cout << *(vec + i - 1) << endl;
    i--;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    char c;
    cin >> n;
    vec = new int[size];
    for (int i = 0; i < n; i++) {
        cin >> c;
        if (c == '+') {
            cin >> m;
            push(m);
        } else {
            pop();
        }
    }
    return 0;
}
