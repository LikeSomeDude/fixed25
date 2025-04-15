#ifndef MYFIXED__for_h__
#define MYFIXED__for_h__

#include <string>

template <int MAX_DIGITS>
class Fixed {
private:
    signed char sign;
    unsigned int integer;
    char digits[MAX_DIGITS];


    void normalize() {
        if (integer == 0 && sign < 0) {
            bool isZERO = true;
            for (int i = 0; i < MAX_DIGITS; ++i) {
                if (digits[i] != 0) {
                    isZERO = false;
                    break;
                }
            }
            if (isZERO) {
                sign = 1;
            }
        }
    }


    Fixed& minus_min_abs(const Fixed& other) {
        char carry = 0;
        for (int i = MAX_DIGITS - 1; i >= 0; --i) {
            digits[i] -= other.digits[i] + carry;
            if (digits[i] < 0) {
                digits[i] += 10;
                carry = 1;
            }
            else {
                carry = 0;
            }
            integer -= other.integer + carry;
        }
        return *this;
    }


public:
    Fixed() : sign(1), integer(0) {
        for (int i = 0; i < MAX_DIGITS; ++i) {
            digits[i] = 0;
        }
    }
    Fixed(int num, unsigned int fr = 0) {
        if (num < 0) {
            sign = -1;
            integer = static_cast<unsigned int>(-num);
        }
        else {
            sign = 1;
            integer = static_cast<unsigned int>(num);
        }
        for (int i = MAX_DIGITS - 1; i >= 0; --i) {
            digits[i] = fr % 10;
            fr /= 10;
        }
    }
    Fixed(unsigned int num) : sign(1), integer(num) {
        for (int i = 0; i < MAX_DIGITS; ++i) {
            digits[i] = 0;
        }
    }
    Fixed(double num) : sign(1) {
        if (num < 0) {
            sign = -1;
            num = -num;
        }
        integer = static_cast<unsigned int>(num);
        num -= integer;
        for (int i = 0; i < MAX_DIGITS; ++i) {
            num *= 10.0;
            int intnum = static_cast<unsigned int>(num);
            digits[i] = static_cast<char>(intnum);
            num -= intnum;
        }
        normalize();
    }
    Fixed(char const str[]) : sign(1), integer(0) {
        int index = 0;
        while (str[index] == ' ') ++index;
        if (str[index] == '-') {
            sign = -1;
        }
        else {
            sign = 1;
        }
        while (str[index] != '\0' && str[index] != '.') {
            if (!isdigit(str[index])) {
                throw "wrang format";
            }
            integer = integer * 10 + (str[index] - '0');
            ++index;
        }
        if (str[index] == '.') {
            ++index;

        }
        for (int i = 0; i < MAX_DIGITS; ++i) {
            digits[i] = 0;
        }
        int i = 0;
        while (str[index] != '\0' && i < MAX_DIGITS) {
            if (!isdigit(str[index])) {
                throw "wrang format";
            }
            digits[i] = str[index] - '0';
            ++index;
            ++i;
        }

        normalize();
    }

    friend class Fixed;

    template<int XXX>
    Fixed(const Fixed<XXX>& other) : sign(other.sign), integer(other.integer) {
        int i = 0;
        for (; i < MAX_DIGITS && i < XXX; ++i) {
            digits[i] = other.digits[i];
        }
        for (; i < MAX_DIGITS; ++i) {
            digits[i] = 0;
        }
    }

    std::string to_string() const {
        std::string result;
        if (sign < 0) {
            result = "-";
        }
        result += std::to_string(integer) + '.';
        for (int i = 0; i < MAX_DIGITS; ++i) {
            result += (digits[i] + '0');
        }
        return result;
    }

    Fixed abs() const {
        return sign < 0 ? -*this : *this;
    }


    Fixed& operator+=(const Fixed& other) {
        if (sign = other.sign) {
            char carry = 0;
            for (int i = MAX_DIGITS - 1; i >= 0; --i) {
                digits[i] += other.digits[i] + carry;
                if (digits[i] > 9) {
                    digits[i] -= 10;
                    carry = 1;
                }
                else {
                    carry = 0;
                }
            }
            integer += other.integer + carry;
        }
        else {
            if (this->abs() >= other.abs()) {
                minus_min_abs(other);
            }
            else {
                //other константный
                Fixed tmp(other);
                *this = tmp.minus_min_abs(*this);
            }
        }
        normalize();
        return *this;
    }

    Fixed& operator-=(const Fixed& other) {
        *this += -other;
        return *this;
    }

    Fixed& operator*=(const Fixed& other) {

        if (x < 0) {
            sign *= -1;
            x *= -1;
        }
        int carry = 0;
        for (int i = MAX_DIGITS - 1; i >= 0; --i) {
            int tmp = digits[i];
            tmp *= x;
            tmp += carry;
            digits[i] = tmp % 10;
            carry = tmp / 10;
        }
        integer *= x;
        integer += carry;

        return *this;//почему возвращаем ссылку на самого себя?
    }
    //почему не просто *? Так как мы возвращаем сслылку фиксед амперсант, а не новый объект
    Fixed& operator*=(const Fixed& other) {
        Fixed x1(integer * other.integer);
        Fixed x2(other);
        x2.integer = 0;
        x2.sign = 1;
        x2 *= integer;

        Fixed x3(*this);
        x3.integer = 0;
        x3.sign = 1;
        x3 *= other.integer;

        Fixed x4(*this) {
            x4.integer = 0;
            x4.sign = 1;
            Fixed result;
            for (int i = 0; i < MAX_DIGITS; ++i) {
                Fixed tmp(x4);
                tmp *= other.digits[i];
                tmp <<= (i + 1);
            }
        }
        //result += x1 + x2 + x3; //операция красивая, но дорогая

        result += x1;
        result += x2;
        result += x3;
        result.sign = sign * other.sign;
        *this = result
            return *this;

    }

    Fixed operator*(const Fixed& other) {
        Fixed result(*this);
        result *= other;
        return result;
    }


    Fixed& operator <<=(int shift) {
        if (shift <= 0) return *this;
        for (int i = MAX_DIGITS - 1; i >= shift; --i) {
            digits[i] = digits[i - shift];
        }
        for (int i = shift - 1; i >= 0; --i) {
            digits[i] = integer % 10;
            integer /= 10;
        }
        return *this;
    }

    bool is_equal(const Fixed& other) const {
        bool answer = (sign == other.sign) && (integer == other.integer);
        for (int i = 0; i < MAX_DIGITS; ++i) {
            if (digits[i] != other.digits[i]) {
                answer = false;
                break;
            }
        }
        return answer;
    }
    bool is_less(const Fixed& other) const {
        if (sign < other.sign) return true;
        if (other.sign < sign) return false;
        if (sign < 0) {
            return (-other).is_less(-(*this));
        }
        if (integer < other.integer) return true;
        if (other.integer < integer) return false;
        for (int i = 0; i < MAX_DIGITS; ++i) {
            if (digits[i] < other.digits[i]) return true;
            if (other.digits[i] < digits[i]) return false;
        }
        return false;
    }

    Fixed operator-() const {
        Fixed result(*this);
        result.sign = -result.sign;
        result.normalize();
        return result;
    }

};


template <int DIGITS_1, int DIGITS_2>
Fixed<(DIGITS_1 < DIGITS_2) ? DIGITS_2 : DIGITS_1>
    operator+(const Fixed<DIGITS_1>& left, const Fixed<DIGITS_2>& right) {
    if (DIGITS_1 < DIGITS_2) {
        Fixed<DIGITS_2> result(left);
        result += right;
        return result;
    }
    else {
        Fixed<DIGITS_1> result(left);
        result += Fixed<DIGITS_1>(right);
    }
}


template <int DIGITS_1, int DIGITS_2>
Fixed<(DIGITS_1 < DIGITS_2) ? DIGITS_2 : DIGITS_1>
    operator-(const Fixed<DIGITS_1>& left, const Fixed<DIGITS_2>& right) {
    return left + (-right);
}

template <int DIGITS_1, int DIGITS_2>
Fixed<(DIGITS_1 < DIGITS_2) ? DIGITS_2 : DIGITS_1>
    operator*(const Fixed<DIGITS_1>& left, const Fixed<DIGITS_2>& right) {
    if (DIGITS_1 < DIGITS_2) {
        Fixed<DIGITS_2> result(left);
        result *= right;
        return result;
    }
    else {
        Fixed<DIGITS_1> result(left);
        result *= Fixed<DIGITS_1>(right);
    }
}

template <int DIGITS_1>
inline bool operator<(const Fixed<DIGITS_1>& left, const Fixed<DIGITS_1>& right) {
    return left.is_less(right);
}

template <int DIGITS_1>
inline bool operator<=(const Fixed<DIGITS_1>& left, const Fixed<DIGITS_1>& right) {
    return !(right < left);
}

template <int DIGITS_1>
inline bool operator>(const Fixed<DIGITS_1>& left, const Fixed<DIGITS_1>& right) {
    return right < left;
}

template <int DIGITS_1>
inline bool operator>=(const Fixed<DIGITS_1>& left, const Fixed<DIGITS_1>& right) {
    return !(left < right);
}

template <int DIGITS_1>
inline bool operator==(const Fixed<DIGITS_1>& left, const Fixed<DIGITS_1>& right) {
    return left.is_equal(right);
}

template <int DIGITS_1>
inline bool operator!=(const Fixed<DIGITS_1>& left, const Fixed<DIGITS_1>& right) {
    return !(left == right);
}

#endif
