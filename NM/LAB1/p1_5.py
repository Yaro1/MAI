import matrix
import argparse
import array
import math
import numpy as np


def sign(num):
    if num > 0:
        return 1
    elif num < 0:
        return -1
    else:
        return 0


def householder(m, i):
    v = matrix.Matrix([], m.size()[0], 1)
    for j in range(i):
        v.data[j][0] = 0
    sum_ = 0
    for count in range(i, m.size()[0]):
        sum_ += m.data[count][i] ** 2
    v.data[i][0] = m.data[i][i] + sign(m.data[i][i]) * sum_ ** 0.5
    for count in range(i + 1, m.size()[0]):
        v.data[count][0] = m.data[count][i]
    v_t = matrix.Matrix()
    v_t.data = v.transpose()
    ones = matrix.ones(m.size()[0])
    return ones - (v * v_t) * (2 * (1 / ((v_t * v).data[0][0])))


def find_Q_R(m):
    h_matrix = []
    for i in range(m.size()[0] - 1):
        h = householder(m, i)
        h_matrix.append(h)
        m = h * m
    q = h_matrix[0]
    for i in range(1, len(h_matrix)):
        q = q * h_matrix[i]
    return [q, m]


def accuracy(m_, eps, l):
    for i in range(m_.size()[0]):
        sum_ = 0
        for j in range(i + 1, m_.size()[0]):
            sum_ += m_.data[j][i] ** 2
        sum_ = sum_ ** 0.5
        if sum_ < eps:
            continue
        else:
            try:
                b = complex(m_.data[i][i] + m_.data[i + 1][i + 1], 0)
                c = complex(m_.data[i][i] * m_.data[i + 1][i + 1] - m_.data[i][i + 1] * m_.data[i + 1][i], 0)
                l1 = (b + (b ** 2 - 4 * c) ** 0.5) / 2
                l2 = (b - (b ** 2 - 4 * c) ** 0.5) / 2
                if l1.conjugate() == l2:
                    if abs(l1 - l[0]) < eps and abs(l2 - l[1]) < eps:
                        l[0], l[1] = l1, l2
                        i += 1
                        continue
                    l[0], l[1] = l1, l2
                else:
                    return [True, l]
            except IndexError:
                return [True, l]
    return [False, l]


def matrix_eigenvalues(m_, eps):
    l = [complex(0, 0), complex(0, 0)]
    while accuracy(m_, eps, l)[0]:
        l_ = find_Q_R(m_)
        m_ = l_[1] * l_[0]
        # print(str(m_))
    return [m_.data[0][0], l[0], l[1]]


def main():
    m = matrix.Matrix([[1, 3, 1], [1, 1, 4], [4, 3, 1]])
    ans = find_Q_R(m)
    # print(str(ans[0]), "\n\n")
    # print(str(ans[1]))
    answer = matrix_eigenvalues(m, 0.01)
    print("Answer: ")
    for i in range(len(answer)):
        print("Eigenvalues {0} is: ".format(i), answer[i])


if __name__ == '__main__':
    matrix__ = matrix.Matrix()
    parser = argparse.ArgumentParser(description='Works with matrix.')
    parser.add_argument('-d', type=int, default=0, help='0 - my numbers in matrix, else your numbers in matrix')
    args = parser.parse_args()
    if args.d == 0:
        matrix__ = matrix.Matrix([[1, 3, 1], [1, 1, 4], [4, 3, 1]])
        eps = 0.01
    else:
        num = input("Enter number element in string/column: ")
        num = int(num)
        print("Enter matrix A")
        for i in range(num):
            next_str = array.array('d')
            for j in range(num):
                next_str.append(int(input()))
            matrix__.data.append(next_str)
        eps = input("Enter the epsilon : ")
    answer = matrix_eigenvalues(matrix__, eps)
    print("Answer: ")
    for i in range(len(answer)):
        print("Eigenvalues {0} is: ".format(i), answer[i])