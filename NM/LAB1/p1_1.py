# var 18
import argparse


def print_(l_):
    for i in range(len(l_)):
        print(l_[i])


def l_u_factor(a, l, u):
    for i in range(len(a)):
        l[i][i] = 1
    for k in range(len(a)):
        u[k][k] = a[k][k]
        for i in range(k + 1, len(a), 1):
            l[i][k] = a[i][k] / u[k][k]
            u[k][i] = a[k][i]
        for i in range(k + 1, len(a), 1):
            for j in range(k + 1, len(a), 1):
                a[i][j] = a[i][j] - l[i][k] * u[k][j]
    return [a, l, u]


def forward(l, b):
    y = []
    for i in range(len(l)):
        prom_sum = 0
        for j in range(i):
            prom_sum += l[i][j] * y[j]
        y.append(b[i] - prom_sum)
    return y


def back(u, y):
    n = len(u) - 1
    x = []
    for i in range(len(u)):
        x.append(0)
    for i in range(len(u)):
        prom_sum = 0
        for p in range(i):
            prom_sum += u[n - i][n - p] * x[n - p]
        x[n - i] = 1 / u[n - i][n - i] * (y[n - i] - prom_sum)
    return x


def transpose_matrix(m):
    n_m = []
    for i in range(len(m)):
        n_s = []
        for j in range(len(m)):
            n_s.append(m[j][i])
        n_m.append(n_s)
    return n_m


def reverse_matrix(m):
    divider = 1 / determinant(m)
    m = transpose_matrix(m)
    n_m = []
    for i in range(len(m)):
        n_s = []
        for j in range(len(m)):
            if (i + j) % 2 == 0:
                n_e = determinant(algebraic_complement(m, i, j))
            else:
                n_e = -determinant(algebraic_complement(m, i, j))
            n_s.append(n_e)
        n_m.append(n_s)
    for i in range(len(m)):
        for j in range(len(m)):
            n_m[i][j] *= divider
    n_m = [[round(o, 3) for o in e] for e in n_m]
    return n_m


def algebraic_complement(m, str_, clm_):
    n_m = []
    for i in range(len(m)):
        n_s = []
        for j in range(len(m)):
            if i != str_ and j != clm_:
                n_s.append(m[i][j])
        if len(n_s) != 0:
            n_m.append(n_s)
    return n_m


def determinant(m):
    n = len(m)
    if n == 1:
        return m[0][0]
    if n == 2:
        return m[0][0] * m[1][1] - m[0][1] * m[1][0]
    s = 0
    for i in range(n):
        s += m[0][i] * (-1) ** i * determinant(algebraic_complement(m, 0, i))
    return round(s, 5)


def LUP_Decomposition(A):
    n = len(A)
    k_ = 0
    pi = []
    for i in range(n):
        pi.append(i)
    for k in range(0, n):
        p = 0
        for i in range(k, n):
            if abs(A[i][k]) > p:
                p = abs(A[i][k])
                k_ = i
        if p == 0:
            return 'ERROR'
        pi[k], pi[k_] = pi[k_], pi[k]
        for i in range(n):
            A[k][i], A[k_][i] = A[k_][i], A[k][i]
        for i in range(k + 1, n):
            A[i][k] = A[i][k] / A[k][k]
            for j in range(k + 1, n):
                A[i][j] = A[i][j] - A[i][k] * A[k][j]
    return [A, pi]


def forward_back(data):
    A = data[0]
    n = len(A)
    pi = data[1]
    b = data[2]
    y = []
    x = []
    for i in range(n):
        y.append(0)
    for i in range(n):
        x.append(0)
    for i in range(n):
        s = 0
        for j in range(i):
            if i == j:
                s = s + y[i]
            else:
                s = s + A[i][j] * y[j]
        y[i] = b[pi[i]] - s
    for i in range(n - 1, -1, -1):
        s = 0
        for j in range(i + 1, n):
            s = s + A[i][j] * x[j]
        x[i] = (y[i] - s) / A[i][i]
    x = [round(e) for e in x]
    return x


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Works with matrix.')
    parser.add_argument('-d', type=int, default=0, help='0 - my numbers in matrix, else your numbers in matrix')
    args = parser.parse_args()
    A = []
    B = []
    if args.d == 0:
        A = [[1, -1, 1, -2], [-9, -1, 1, 8], [-7, 0, 8, -6], [3, -5, 1, -6]]
        B = [-20, 60, -60, -44]
    else:
        num = input("Enter number element in string/column: ")
        num = int(num)
        print("Enter matrix A")
        for i in range(num):
            next_str = []
            for j in range(num):
                next_str.append(int(input()))
            A.append(next_str)
        print("Enter vector B")
        for i in range(num):
            B.append(int(input()))

    print_(A)
    print("Reverse matrix.")
    print_(reverse_matrix(A))
    print('LUP')
    l_ = LUP_Decomposition(A)
    l_.append(B)
    print(forward_back(l_))
    print("Determinant is : ", determinant(A))
