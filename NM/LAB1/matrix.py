import array


# TO DO
# automatic tests
# good exception

class MyError(Exception):
    def __init__(self, text, num):
        self.txt = text
        self.n = num


def algebraic_complement(m_, str_, clm_):
    n_m = []
    size = len(m_)
    for i in range(size):
        n_s = array.array('d')
        for j in range(size):
            if i != str_ and j != clm_:
                n_s.append(m_[i][j])
        if len(n_s) != 0:
            n_m.append(n_s)
    return n_m


def ones(number):
    answer = Matrix([], number, number)
    for i in range(number):
        answer.data[i][i] = 1
    return answer


class Matrix:
    def __init__(self, l_=[], str_=0, clm_=0):  # expected a list of numbers or size or nothing
        self.data = []
        if not len(l_):
            if str_ == 0 or clm_ == 0:
                self.data = []
            else:
                element = []
                for _ in range(clm_):
                    element.append(0)
                for _ in range(str_):
                    self.data.append(array.array('d', element))
        else:
            try:
                self.data = [array.array('d', x) for x in l_]
            except TypeError:
                self.data = [array.array('d', l_)]

    def __mul__(self, other):
        if not isinstance(other, Matrix):
            for i in range(len(self.data)):
                for j in range(len(self.data[0])):
                    self.data[i][j] *= other
            c = Matrix()
            c.data = self.data.copy()
        else:  # TO DO Test, that matrixes have good size for mul ( like (a, b) and (b, c) )
            if self.size()[1] != other.size()[0]:
                raise MyError("Matrixes should be good size! For mul like (a, b) and (b, c)!", 1)
            c = Matrix([], len(self.data), len(other.data[0]))
            for i in range(len(self.data)):
                for j in range(len(other.data[0])):
                    for k in range(len(self.data[0])):
                        c.data[i][j] += self.data[i][k] * other.data[k][j]
        return c

    def __add__(self, other):
        c = Matrix([], len(self.data), len(self.data[0]))
        if not isinstance(other, Matrix):
            for i in range(len(self.data)):
                for j in range(len(self.data[0])):
                    c.data[i][j] = self.data[i][j] + other
        else:
            if self.size() != other.size():
                raise MyError("Matrixes should be same size!", 1)
            for i in range(len(self.data)):
                for j in range(len(self.data[0])):
                    c.data[i][j] = self.data[i][j] + other.data[i][j]
        return c

    def __sub__(self, other):
        c = Matrix([], len(self.data), len(self.data[0]))
        if not isinstance(other, Matrix):
            for i in range(len(self.data)):
                for j in range(len(self.data[0])):
                    c.data[i][j] = self.data[i][j] - other
        else:
            if self.size() != other.size():
                raise MyError("Matrixes should be same size!", 1)
            for i in range(len(self.data)):
                for j in range(len(self.data[0])):
                    c.data[i][j] = self.data[i][j] - other.data[i][j]
        return c

    def __pow__(self, power, modulo=None):
        if power <= 0:
            raise MyError("Can calculate only power >= 0", 1)
        if modulo is not None:
            raise MyError("Can't do this!", modulo)
        if len(self.data) != len(self.data[0]):
            raise MyError("Matrix should be square!", modulo)
        answer = Matrix()
        an = self.data.copy()
        answer.data = an
        for _ in range(power - 1):
            answer = answer * self
        return answer

    def __str__(self):
        answer = ""
        for i in range(len(self.data)):
            for j in range(len(self.data[i])):
                answer += str(self.data[i][j]) + " "
            answer += "\n"
        return answer

    def size(self):
        return len(self.data), len(self.data[0])

    def determinant(self, m):
        n = len(m)
        if n == 1:
            return m[0][0]
        if n == 2:
            return m[0][0] * m[1][1] - m[0][1] * m[1][0]
        s = 0
        for i in range(n):
            s += m[0][i] * (-1) ** i * self.determinant(algebraic_complement(m, 0, i))
        return round(s, 5)

    def reverse(self):
        try:
            divider = 1 / self.determinant(self.data)
        except ZeroDivisionError:
            raise MyError("Can't calculate reverse matrix!\nZeroDivision!\n", 1)
        m = self.transpose()
        n_m = []
        for i in range(len(m)):
            n_s = []
            for j in range(len(m)):
                if (i + j) % 2 == 0:
                    n_e = self.determinant(algebraic_complement(m, i, j))
                else:
                    n_e = -self.determinant(algebraic_complement(m, i, j))
                n_s.append(n_e)
            n_m.append(n_s)
        for i in range(len(m)):
            for j in range(len(m)):
                n_m[i][j] *= divider
        n_m = [[round(o, 3) for o in e] for e in n_m]
        return n_m

    def transpose(self):
        n_m = []
        for i in range(self.size()[1]):
            n_s = array.array('d',)
            for j in range(self.size()[0]):
                n_s.append(self.data[j][i])
            n_m.append(n_s)
        return n_m


if __name__ == '__main__':
    test1 = Matrix([[1, 2, 3], [5, 3, 2], [0, 1, 9]])
    print(str(Matrix(test1.reverse())))
    print(str(test1 ** 2))
    print(test1.determinant(test1.data))
