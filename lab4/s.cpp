#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
vector<vector<long long>> matrix;

vector<vector<long long>> mul(vector<vector<long long>> a, vector<vector<long long>> b) {
    vector<vector<long long>> c = vector<vector<long long>>(a.size());
    for (int i = 0; i < (int) a.size(); i++) {
        c[i] = vector<long long>(b[0].size());
    }
    for (int i = 0; i < (int) a.size(); i++) {
        for (int j = 0; j < (int) a[0].size(); j++) {
            for (int k = 0; k < (int) b[0].size(); k++) {
                c[i][k] += a[i][j] * b[j][k];
                c[i][k] %=  999999937;
            }
        }
    }
    return c;
}

vector<vector<long long>> pow(vector<vector<long long>> a, long long n) {
    if (n == 1) {
        return a;
    }
    vector<vector<long long>> cur = pow(a, n / 2);
    if (n % 2 == 0) {
        return mul(cur, cur);
    }
    return mul(mul(cur, cur), a);
}

int main() {
    freopen("sequences.in", "r", stdin);
    freopen("sequences.out", "w", stdout);
    long long n;
    cin >> n;
    vector<vector<long long>> matrix = vector<vector<long long>>(5);
    matrix[0] = {1, 1, 1, 1, 1};
    matrix[1] = {1, 1, 1, 1, 1};
    matrix[2] = {1, 1, 1, 1, 1};
    matrix[3] = {1, 1, 0, 1, 0};
    matrix[4] = {1, 1, 0, 1, 0};
    vector<vector<long long>> beg = vector<vector<long long>>(5);
    beg[0] = {1};
    beg[1] = {1};
    beg[2] = {1};
    beg[3] = {1};
    beg[4] = {1};
    while (n != 0) {
        long long s = 0;
        vector<vector<long long>> ans = mul(pow(matrix, n), beg);
        for (int i = 0; i < (int) ans[0].size(); i++) {
            s += ans[0][i];
            s %= 999999937;
        }
        cout << s << endl;
        cin >> n;
    }
    return 0;
}
