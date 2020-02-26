import argparse


def forward(elements_):
    a = elements_[0]
    b = elements_[1]
    c = elements_[2]
    d = elements_[3]
    a_i = [-c[0] / b[0]]
    b_i = [d[0] / b[0]]
    for i in range(1, len(a)):
        a_i.append(-c[i] / (b[i] + a[i] * a_i[i - 1]))
        b_i.append((d[i] - a[i] * b_i[i - 1]) / (b[i] + a[i] * a_i[i - 1]))
    x = []
    for i in range(len(a) + 1):
        x.append(0)
    for i in range(1, len(a)):
        x[len(a) - i] = a_i[len(a) - i] * x[len(a) - i + 1] + b_i[len(a) - i]
    del x[len(a)]
    x = [round(e) for e in x]
    return x


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Works with matrix.')
    parser.add_argument('-d', type=int, default=0, help='0 - my numbers to compute, else your numbers in matrix')
    args = parser.parse_args()
    elements = []
    if args.d == 0:
        elements = [[0, 7, -4, 7, 4], [8, -19, 21, -23, -7], [-2, 9, -8, 9, 0], [-14, -55, 49, 86, 8]]
    else:
        num = input("Enter number element in string/column for vector's 'a', 'b', 'c', 'd' : ")
        num = int(num)
        if num != 5:
            print("There is only 5 element's for compute.")
        else:
            for i in range(num - 1):
                n_e = []
                for j in range(num):
                    n_e.append(int(input()))
                elements.append(n_e)
    print(forward(elements))
