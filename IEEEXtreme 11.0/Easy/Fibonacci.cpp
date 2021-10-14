/// hhoangcpascal

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef vector<vector<int> > Matrix;

Matrix operator * (const Matrix &A, const Matrix &B) {
    Matrix C(2, vector<int>(2, 0));

    for(int i = 0; i < 2; ++i)
    for(int j = 0; j < 2; ++j)
    for(int k = 0; k < 2; ++k) (C[i][j] += A[i][k] * B[k][j]) %= 10;

    return C;
}

Matrix Zero;

Matrix power(Matrix A, int n) {
    if (n == 0) return Zero;

    Matrix tmp = power(A, n >> 1);
    tmp = tmp * tmp;

    if (n & 1) tmp = tmp * A;
    return tmp;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(NULL);

    Zero.assign(2, vector<int>(2, 0));
    Zero[1][1] = Zero[0][0] = 1;

    int t; cin >> t;
    while (t--) {
        int n; cin >> n;

        Matrix a(2, vector<int>(2, 0));
        a[0][1] = a[1][0] = a[1][1] = 1;

        Matrix res = power(a, n);
        cout << res[1][1] << '\n';
    }

    return 0;
}
