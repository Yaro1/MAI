import p1_1
import argparse
from math import sqrt
import numpy as np


def method_seidel(_matrix_, eps):
    _matrix = []
    b = [_matrix_[i][len(_matrix_[0]) - 1] for i in range(len(_matrix_)) ]
    for i in range(len(_matrix_)):
        n = []
        for j in range(len(_matrix_[0]) - 1):
            n.append(_matrix_[i][j])
        _matrix.append(n)
    n = len(_matrix)
    x = [.0 for i in range(n)]
    iteration = 0
    converge = False
    while not converge:
        iteration += 1
        x_new = np.copy(x)
        for i in range(n):
            s1 = sum(_matrix[i][j] * x_new[j] for j in range(i))
            s2 = sum(_matrix[i][j] * x[j] for j in range(i + 1, n))
            x_new[i] = (b[i] - s1 - s2) / _matrix[i][i]

        converge = sqrt(sum((x_new[i] - x[i]) ** 2 for i in range(n))) <= eps
        x = x_new
    x = [round(e) for e in x]
    return [x, iteration]


def norm_euclid(vector):
    ans = 0
    for i in vector:
        ans += i ** 2
    return ans ** 0.5


def distance(a, b):
    return [b[i] - a[i] for i in range(len(a))]


def my_sum(a, b):
    return [b[i] + a[i] for i in range(len(a))]


def mull_iteration(x, alpha):
    ans = []
    for i in range(len(alpha)):
        element = 0
        for j in range(len(alpha)):
            element += alpha[i][j] * x[j]
        ans.append(element)
    return ans


def method_iteration(_matrix, precision):
    alpha = []
    number_of_iteration = 0
    for i in range(len(_matrix)):
        n_e = [-_matrix[i][j] / _matrix[i][i] if i != j else 0 for j in range(len(_matrix))]
        alpha.append(n_e)
    b_i = [_matrix[i][len(_matrix)] / _matrix[i][i] for i in range(len(_matrix))]
    x = [i for i in b_i]
    while norm_euclid(distance(x, my_sum(b_i, mull_iteration(x, alpha)))) > precision:
        x = my_sum(b_i, mull_iteration(x, alpha))
        number_of_iteration += 1
    x = my_sum(b_i, mull_iteration(x, alpha))
    x = [round(e) for e in x]
    return [x, number_of_iteration]


if __name__ == '__main__':
    matrix = []
    parser = argparse.ArgumentParser(description='Works with matrix.')
    parser.add_argument('-d', type=int, default=0, help='0 - my numbers in matrix, else your numbers in matrix')
    args = parser.parse_args()
    if args.d == 0:
        matrix = [[18, 8, -3, 4, -84], [-7, 15, -5, -2, -5], [-4, 0, 13, 4, -38], [-8, -8, -6, 31, 263]]
        # matrix = [[10, 1, 1, 12], [2, 10, 1, 13], [2, 2, 10, 14]]
    else:
        num = input("Enter number element in string/column: ")
        num = int(num)
        print("Enter matrix A")
        for i in range(num):
            next_str = []
            for j in range(num):
                next_str.append(int(input()))
            matrix.append(next_str)
    answer = method_iteration(matrix, 0.01)
    print("Method iteration ", "Answer is : ", answer[0], "Number of iteration : ", answer[1])
    answer = method_seidel(matrix, 0.01)
    print("Method seidel    ", "Answer is : ", answer[0], "Number of iteration : ", answer[1])
