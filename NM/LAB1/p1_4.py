import p1_1
import argparse
import math


def find_max(mat):
    max_matrix = 1e-10
    index_i = 0
    index_j = 0
    for i in range(len(mat)):
        for j in range(i, len(mat)):
            if i == j:
                continue
            if mat[i][j] > max_matrix:
                max_matrix = mat[i][j]
                index_i = i
                index_j = j
    return [int(index_i), int(index_j)]


def find_phi(mat, index_i, index_j):
    try:
        return (1 / 2) * math.atan(2 * mat[index_i][index_j] / (mat[index_i][index_i] - mat[index_j][index_j]))
    except ZeroDivisionError:
        return math.pi / 4


def mul_matrix_square(a, b):
    c = [[0 for i in range(len(a))] for j in range(len(a))]
    for i in range(len(a)):
        for j in range(len(a)):
            for k in range(len(a)):
                c[i][j] += a[i][k] * b[k][j]
    return c


def exit_condition(m):
    answer = 0
    for i in range(len(m)):
        for j in range(len(m)):
            if i < j:
                answer += m[i][j] ** 2
    return answer ** 0.5


def method_rotation(l_):
    number_iteration = 0
    m = l_[0]
    eps = l_[1]
    answer_list = []
    while exit_condition(m) > eps:
        matrix_rotation = [[0 if i != j else 1 for i in range(len(m))] for j in range(len(m))]
        ret = find_max(m)
        phi = find_phi(m, ret[0], ret[1])
        matrix_rotation[ret[0]][ret[0]] = math.cos(phi)
        matrix_rotation[ret[1]][ret[1]] = math.cos(phi)
        matrix_rotation[ret[1]][ret[0]] = math.sin(phi)
        matrix_rotation[ret[0]][ret[1]] = -math.sin(phi)
        answer_list.append(matrix_rotation)
        matrix_rotation_tr = p1_1.transpose_matrix(matrix_rotation)
        m = mul_matrix_square(mul_matrix_square(matrix_rotation_tr, m), matrix_rotation)
        number_iteration += 1

    #  print("\n")
    #  p1_1.print_(m)
    #  print("\n")
    #  print(exit_condition(m))
    #  print("\n")

    if len(answer_list) > 1:
        answer = mul_matrix_square(answer_list[0], answer_list[1])
        for i in range(1, len(answer_list)):
            answer = mul_matrix_square(answer, answer_list[i])
    answer = [[round(e, 5) for e in k] for k in answer]
    return [answer, number_iteration]


if __name__ == '__main__':
    matrix = []
    parser = argparse.ArgumentParser(description='Works with matrix.')
    parser.add_argument('-d', type=int, default=0, help='0 - my numbers in matrix, else your numbers in matrix')
    args = parser.parse_args()
    if args.d == 0:
        matrix = [[2, 8, 7], [8, 2, 7], [7, 7, -8]]
        eps = 0.5
    else:
        num = input("Enter number element in string/column: ")
        num = int(num)
        print("Enter matrix A")
        for i in range(num):
            next_str = []
            for j in range(num):
                next_str.append(int(input()))
            matrix.append(next_str)
        eps = input("Enter the epsilon : ")
    a = method_rotation([matrix, eps])
    print("Method rotation ", "Answer is : ")
    p1_1.print_(a[0])
    print("Number of iteration : ", a[1])
