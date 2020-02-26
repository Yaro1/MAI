//
// Created by yar on 30.08.2019.
//

#ifndef CALCULATION_TLONGNUM_H
#define CALCULATION_TLONGNUM_H
#include <vector>
#include <algorithm>
#include <string>

class TLongNum {
public:

    TLongNum(std::string &strNum);

    TLongNum(size_t size);


    TLongNum(size_t size, int num);

    TLongNum();

    void operator+=(TLongNum &rhs);
    void operator+=(TLongNum &&rhs);

    void operator-=(TLongNum &rhs);
    void operator-=(TLongNum &&rhs);

    bool operator<(TLongNum &&rhs);
    bool operator<=(TLongNum &&rhs);
    bool operator>(TLongNum &&rhs);
    bool operator>=(TLongNum &&rhs);
    bool operator!=(TLongNum &&rhs);
    bool operator==(TLongNum &&rhs);

    bool operator<(TLongNum &rhs);
    bool operator<=(TLongNum &rhs);
    bool operator>(TLongNum &rhs);
    bool operator>=(TLongNum &rhs);
    bool operator!=(TLongNum &rhs);
    bool operator==(TLongNum &rhs);

    TLongNum operator+(TLongNum &rhs);
    TLongNum operator+(TLongNum &&rhs);

    TLongNum operator-(TLongNum &rhs);
    TLongNum operator-(TLongNum &&rhs);

    TLongNum operator*(TLongNum &rhs);
    TLongNum operator*(TLongNum &&rhs);

    TLongNum operator/(TLongNum &rhs);

    TLongNum operator^(int num);

    size_t Size() const;


    friend std::ostream &operator<<(std::ostream &stream, TLongNum &number);
    friend std::ostream &operator<<(std::ostream &stream, TLongNum &&number);

    static const int BASE = 1000000000;
    static const int BASE_SIZE = 9;
private:

    std::vector<int> number;


};

#endif //CALCULATION_TLONGNUM_H
