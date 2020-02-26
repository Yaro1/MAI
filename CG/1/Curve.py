from math import sin, cos

class Curve:
    """
    Класс кривой
    """

    def __init__(self, qp, width, height, parameter, step):
        # Место рисования
        self.__qp = qp

# Параметры для перемещения
        # for X
        self.height = height
        self.width = width
        self.__b = width / 2
        self.__m = 5 * width / 50
        # for Y
        self.__k = -5 * height / 50
        self.__a = height / 2 - self.__k * parameter

# изменяющиеся параметры кривой
        self.__parameter = parameter

        self.phi = []
        i = 0.0
        while i < 6.28319:
            self.phi.append(i)
            i += 0.001


        self.x = []
        i = 0.0
        while i < width:
            self.x.append(i)
            i += 1
        self.y = []
        i = 0.0
        while i < height:
            self.y.append(i)
            i += 1



        self.p = []
        for i in self.phi:
            self.p.append(self.__parameter * (1 - cos(i)))

        self.true_x = []
        self.true_y = []
        for i in range(len(self.p)):
            self.true_x.append(self.p[i]*cos(self.phi[i]))
            self.true_y.append(self.p[i] * sin(self.phi[i]))


# Рисование кривой
    def draw(self):

        for i in range(len(self.y) - 1):
            self.__qp.drawLine(self.__b, self.y[i], self.__b, self.y[i + 1])

        for i in range(len(self.x) - 1):
            self.__qp.drawLine(self.x[i], self.height / 2, self.x[i], self.height / 2)

        self.__qp.drawLine(self.width, self.height / 2, self.width - 10, (self.height / 2) + 10)
        self.__qp.drawLine(self.width, self.height / 2, self.width - 10, (self.height / 2) - 10)

        self.__qp.drawLine(self.width / 2, 0, (self.width / 2) - 10, 10)
        self.__qp.drawLine(self.width / 2, 0, (self.width / 2) + 10, 10)

        num = 10
        distance_x = self.width / num
        distance_y = self.height / num

        i = 0
        y = []
        while i < self.height:
            self.__qp.drawLine(self.width / 2 + 5, i, self.width / 2 - 5, i)
            y.append(i)
            i += distance_y

        i = 0
        x = []
        while i < self.width:
            self.__qp.drawLine(i, self.height / 2 + 5, i, self.height / 2 - 5)
            x.append(i)
            i += distance_x

        self.__qp.drawText(x[len(x) // 2 + 1], self.height / 2 + 20, "1")
        self.__qp.drawText(self.width / 2 + 20, y[len(y) // 2 - 1], "1")

        self.__qp.drawText(self.width - distance_x / 4, self.height / 2 - distance_y / 4, "x")
        self.__qp.drawText(self.width / 2 - distance_x / 4, distance_y / 4, "y")

        for i in range(len(self.true_x) - 1):
            self.__qp.drawLine(self.__m * self.true_x[i] + self.__b, self.__k * self.true_y[i] + self.height / 2,
                       self.__m * self.true_x[i + 1] + self.__b, self.__k * self.true_y[i + 1] + self.height / 2)


