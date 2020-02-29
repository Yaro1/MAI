import array


class MyError(Exception):
    def __init__(self, text, num):
        self.txt = text
        self.n = num


class Matrix:
    def __init__(self, l_=[], str_=0, clm_=0):  # expected a list of numbers or nothing
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
            c = self.data.copy()
        else:
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
            if len(self) != len(other):
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
            if len(self) != len(other):
                raise MyError("Matrixes should be same size!", 1)
            for i in range(len(self.data)):
                for j in range(len(self.data[0])):
                    c.data[i][j] = self.data[i][j] - other.data[i][j]
        return c

    def __pow__(self, power, modulo=None):
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

    def __len__(self):
        return len(self.data), len(self.data[0])

    def determinant(self):
        pass

    def algebraic_complement(self):
        pass

    def reverse(self):
        pass

    def transpose(self):
        pass


test1 = Matrix([[2, 3], [2, 3]])
print(str(test1 ** 2))
