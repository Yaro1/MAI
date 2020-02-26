//
// Created by yar on 30.08.2019.
//

#include <iostream>
#include <iomanip>
#include <stdio.h>
#include "TLongNum.h"


TLongNum::TLongNum(std::string &strNum) {
    std::string tmpStr;
    int numeral = 0;
    for (int i = static_cast<int>(strNum.size()); i > 0; i -= BASE_SIZE) {

        if (i < BASE_SIZE) { // last numeral
            // if str.size()%BASE_SIZE != 0
            tmpStr = strNum.substr(0, static_cast<unsigned>(i));
        } else {
            tmpStr = strNum.substr(static_cast<unsigned>(i - BASE_SIZE), BASE_SIZE);
        }
        for (auto j : tmpStr) { //from str to int
            numeral = numeral * 10 + (j - '0');
        }
        number.push_back(numeral);
        numeral = 0;
    }
    while (number.size() > 1 && number.back() == 0)
        number.pop_back();
}

TLongNum::TLongNum(size_t size) : number(size) {}

TLongNum::TLongNum(size_t size, int num) : number(size, num) {}

TLongNum::TLongNum() {}


void TLongNum::operator+=(TLongNum &rhs) {
    int i = 0;
    int remainder = 0;
    while ((i < std::max(number.size(), rhs.number.size())) || remainder) {
        if (i == number.size()) {
            number.push_back(0);
        }
        number[i] += (i < rhs.number.size() ? rhs.number[i] : 0) + remainder;
        remainder = number[i] >= BASE;
        if (remainder)
            number[i] -= BASE;
        ++i;
    }
}
void TLongNum::operator+=(TLongNum &&rhs) {
    int i = 0;
    int remainder = 0;
    while ((i < std::max(number.size(), rhs.number.size())) || remainder) {
        if (i == number.size()) {
            number.push_back(0);
        }
        number[i] += (i < rhs.number.size() ? rhs.number[i] : 0) + remainder;
        remainder = number[i] >= BASE;
        if (remainder)
            number[i] -= BASE;
        ++i;
    }
}

TLongNum TLongNum::operator+(TLongNum &rhs) {
    TLongNum ans = *this;

    int i = 0;
    int remainder = 0;
    while ((i < std::max(ans.number.size(), rhs.number.size())) || remainder) {
        if (i == ans.number.size()) {
            ans.number.push_back(0);
        }
        ans.number[i] += (i < rhs.number.size() ? rhs.number[i] : 0) + remainder;
        remainder = ans.number[i] >= BASE;
        if (remainder)
            ans.number[i] -= BASE;
        ++i;
    }
    return ans;
}
TLongNum TLongNum::operator+(TLongNum &&rhs) {
    TLongNum ans = *this;

    int i = 0;
    int remainder = 0;
    while ((i < std::max(ans.number.size(), rhs.number.size())) || remainder) {
        if (i == ans.number.size()) {
            ans.number.push_back(0);
        }
        ans.number[i] += (i < rhs.number.size() ? rhs.number[i] : 0) + remainder;
        remainder = ans.number[i] >= BASE;
        if (remainder)
            ans.number[i] -= BASE;
        ++i;
    }
    return ans;
}

void TLongNum::operator-=(TLongNum &rhs) {
    int i = 0;
    int remainder = 0;
    while ((i < std::max(number.size(), rhs.number.size())) || remainder) {

        number[i] -= ((i < rhs.number.size() ? rhs.number[i] : 0) + remainder);
        remainder = number[i] < 0;
        if (remainder)
            number[i] += BASE;
        ++i;
    }
    while (number.size() > 1 && number.back() == 0)
        number.pop_back();

}
void TLongNum::operator-=(TLongNum &&rhs) {
    int i = 0;
    int remainder = 0;
    while ((i < std::max(number.size(), rhs.number.size())) || remainder) {

        number[i] -= ((i < rhs.number.size() ? rhs.number[i] : 0) + remainder);
        remainder = number[i] < 0;
        if (remainder)
            number[i] += BASE;
        ++i;
    }
    while (number.size() > 1 && number.back() == 0)
        number.pop_back();
}

TLongNum TLongNum::operator-(TLongNum &rhs) {
    TLongNum ans = *this;

    int i = 0;
    int remainder = 0;
    while ((i < std::max(ans.number.size(), rhs.number.size())) || remainder) {

        ans.number[i] -= ((i < rhs.number.size() ? rhs.number[i] : 0) + remainder);
        remainder = ans.number[i] < 0;
        if (remainder)
            ans.number[i] += BASE;
        ++i;
    }
    while (ans.number.size() > 1 && ans.number.back() == 0)
        ans.number.pop_back();
    return ans;
}
TLongNum TLongNum::operator-(TLongNum &&rhs) {
    TLongNum ans = *this;

    int i = 0;
    int remainder = 0;
    while ((i < std::max(ans.number.size(), rhs.number.size())) || remainder) {

        ans.number[i] -= ((i < rhs.number.size() ? rhs.number[i] : 0) + remainder);
        remainder = ans.number[i] < 0;
        if (remainder)
            ans.number[i] += BASE;
        ++i;
    }
    while (ans.number.size() > 1 && ans.number.back() == 0)
        ans.number.pop_back();
    return ans;
}




TLongNum TLongNum::operator*(TLongNum &rhs) {
    TLongNum ans(this->Size() + rhs.Size());
    int remainder = 0;

    for (size_t i = 0; i < this->Size(); ++i) {
        for (size_t j = 0; j < rhs.Size() || remainder; ++j) {
            long long cur = ans.number[i + j] + static_cast<long long>(this->number[i]) *
                                                (j < rhs.Size() ? static_cast<long long>(rhs.number[j]) : 0) +
                            remainder;
            ans.number[i + j] = static_cast<int> (cur % BASE);
            remainder = static_cast<int> (cur / BASE);
        }
    }
    while (ans.number.size() > 1 && ans.number.back() == 0)
        ans.number.pop_back();
    return ans;
}





TLongNum TLongNum::operator*(TLongNum &&rhs) {
    TLongNum ans(this->Size() + rhs.Size());
    int remainder = 0;

    for (size_t i = 0; i < this->Size(); ++i) {
        for (size_t j = 0; j < rhs.Size() || remainder; ++j) {
            long long cur = ans.number[i + j] + static_cast<long long>(this->number[i]) *
                                                (j < rhs.Size() ? static_cast<long long>(rhs.number[j]) : 0) +
                            remainder;
            ans.number[i + j] = static_cast<int> (cur % BASE);
            remainder = static_cast<int> (cur / BASE);
        }
    }
    while (ans.number.size() > 1 && ans.number.back() == 0)
        ans.number.pop_back();
    return ans;
}

TLongNum TLongNum::operator/(TLongNum &rhs) {
    TLongNum ans(this->Size());
    TLongNum curDivident;

    for (int i = static_cast<int>(Size()) - 1; i >= 0; --i) {
        curDivident.number.insert(curDivident.number.begin(), number[i]);
        if (!curDivident.number.back())
            curDivident.number.pop_back();
        //find divider
        int divider = 0;
        int l = 0, r = BASE;
        int m = 0;
        while (l <= r) {
            m = (r + l) / 2;
            TLongNum curDivider = rhs * TLongNum(1,m);
            if(curDivider <= curDivident) {
                divider = m;
                l = m + 1;
            }
            else {
                r = m - 1;
            }
        }
        ans.number[i] = divider;
        curDivident -= (TLongNum(1,divider) * rhs);
    }
    return ans;
}

TLongNum TLongNum::operator^(int num) {
    TLongNum res(1,1);
    while (num) {
        if (num % 2)
            res = res * (*this);

        (*this) = (*this) * (*this);
        num /= 2;
    }
    return res;
}

bool TLongNum::operator<(TLongNum &rhs) {
    if(number.size() != rhs.number.size())
        return number.size() < rhs.number.size();

    for (int i = (int)(number.size()-1); i >= 0; --i) {
        if (number[i] > rhs.number[i]) { // fault a > b
            return false;
        }
        else if (number[i] == rhs.number[i]) { // ?
            continue;
        }
        else{ // success a < b
            return true;
        }
    }

    //a == b
    return false;
}
bool TLongNum::operator<(TLongNum &&rhs) {
    if(number.size() != rhs.number.size())
        return number.size() < rhs.number.size();

    for (int i = (int)(number.size()-1); i >= 0; --i) {
        if (number[i] > rhs.number[i]) { // fault a > b
            return false;
        }
        else if (number[i] == rhs.number[i]) { // ?
            continue;
        }
        else{ // success a < b
            return true;
        }
    }

    //a == b
    return false;
}
bool TLongNum::operator<=(TLongNum &rhs) {
    if(number.size() != rhs.number.size())
        return number.size() < rhs.number.size();

    for (int i = (int)(number.size()-1); i >= 0; --i) {
        if (number[i] > rhs.number[i]) { // fault a > b
            return false;
        }
        else if (number[i] == rhs.number[i]) { // ?
            continue;
        }
        else{ // success a < b
            return true;
        }
    }

    //a == b
    return true;
}
bool TLongNum::operator<=(TLongNum &&rhs) {
    if(number.size() != rhs.number.size())
        return number.size() < rhs.number.size();

    for (int i = (int)(number.size()-1); i >= 0; --i) {
        if (number[i] > rhs.number[i]) { // fault a > b
            return false;
        }
        else if (number[i] == rhs.number[i]) { // ?
            continue;
        }
        else{ // success a < b
            return true;
        }
    }

    //a == b
    return true;
}
bool TLongNum::operator>(TLongNum &rhs) {
    if(number.size() != rhs.number.size())
        return number.size() > rhs.number.size();

    for (int i = (int)(number.size()-1); i >= 0; --i) {
        if (number[i] < rhs.number[i]) { // fault a < b
            return false;
        }
        else if (number[i] == rhs.number[i]) { // ?
            continue;
        }
        else{ // success a > b
            return true;
        }
    }

    //a == b
    return false;
}
bool TLongNum::operator>(TLongNum &&rhs) {
    if(number.size() != rhs.number.size())
        return number.size() > rhs.number.size();

    for (int i = (int)(number.size()-1); i >= 0; --i) {
        if (number[i] < rhs.number[i]) { // fault a < b
            return false;
        }
        else if (number[i] == rhs.number[i]) { // ?
            continue;
        }
        else{ // success a > b
            return true;
        }
    }

    //a == b
    return false;
}
bool TLongNum::operator>=(TLongNum &rhs) {
    if(number.size() != rhs.number.size())
        return number.size() > rhs.number.size();

    for (int i = (int)(number.size()-1); i >= 0; --i) {
        if (number[i] < rhs.number[i]) { // fault
            return false;
        }
        else if (number[i] == rhs.number[i]) { // ?
            continue;
        }
        else{ // success
            return true;
        }
    }
    //a == b
    return true;
}
bool TLongNum::operator>=(TLongNum &&rhs) {
    if(number.size() != rhs.number.size())
        return number.size() > rhs.number.size();

    for (int i = (int)(number.size()-1); i >= 0; --i) {
        if (number[i] < rhs.number[i]) { // fault
            return false;
        }
        else if (number[i] == rhs.number[i]) { // ?
            continue;
        }
        else{ // success
            return true;
        }
    }
    //a == b
    return true;
}
bool TLongNum::operator==(TLongNum &&rhs) {
    return this->number == rhs.number;
}
bool TLongNum::operator==(TLongNum &rhs) {
    return this->number == rhs.number;
}
bool TLongNum::operator!=(TLongNum &&rhs) {
    return this->number != rhs.number;
}
bool TLongNum::operator!=(TLongNum &rhs) {
    return this->number != rhs.number;
}

size_t TLongNum::Size() const {
    return number.size();
}

std::ostream &
operator<<(std::ostream &stream, TLongNum &number) {
    if (number.Size() == 0) {
        stream << 0;
        return stream;
    }

    while (number.number.size() > 1 && number.number.back() == 0)
        number.number.pop_back();
    stream << number.number[number.Size() - 1];
    for (int i = static_cast<int>(number.Size()) - 2; i >= 0; --i) {
        stream << std::setfill('0') << std::setw(TLongNum::BASE_SIZE) << number.number[i];
    }
    return stream;
}

std::ostream &
operator<<(std::ostream &stream, TLongNum &&number) {
    if (number.Size() == 0) {
        stream << 0;
        return stream;
    }

    while (number.number.size() > 1 && number.number.back() == 0)
        number.number.pop_back();
    stream << number.number[number.Size() - 1];
    for (int i = static_cast<int>(number.Size()) - 2; i >= 0; --i) {
        stream << std::setfill('0') << std::setw(TLongNum::BASE_SIZE) << number.number[i];
    }
    return stream;
}