#ifndef MYFIXED_25_sdfghjk_
#define MYFIXED_25_sdfghjk_
#include <string>

template <int MAX_DIGITS>
class Fixed {
    signed char sign;
    unsigned int integer;
    char digits[MAX_DIGITS];

public:
    Fixed(): sign(1), integer(0){
        for (int i = 0; i < MAX_DIGITS; i++) {
            digits[i]=0;
        }
    }
    Fixed(int num, unsigned int fr = 0) {
        if(num < 0) {
            sign = -1;
            integer = static_cast<unsigned int>(-num);
        } else {
            sign = 1;
            integer = static_cast<unsigned int>(num);
        }
        for (int i = MAX_DIGITS - 1; i >= 0; --i) {
            digits[i] = fr%10;
            fr/=10;
        }
    }
    Fixed(unsigned int num) : sign(1), integer(num) {
        for (int i = 0; i < MAX_DIGITS; i++) {
            digits[i] = 0;
        }
    }
    Fixed(double num) : sign(1) {
        if (num < 0) {
            sign = -1;
            num = -num;
        }
        //����� ����� �����
        integer = static_cast<unsigned int>(num);
        num -= integer;
        //������������ ����� �����
        for (int i = 0; i < MAX_DIGITS; ++i) {
            num *=10;
            int intnum = static_cast<int>(num);
            digits[i] = static_cast<char>(intnum);
            num -= intnum;
        }
    }
   // Fixed(char const str[]);

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
        result += std::to_string(integer);
        result += ".";
        for (int i = 0; i < MAX_DIGITS; ++i) {
            result += (digits[i] + '0');
        }
        return result;
    }

    Fixed& operator+= (const Fixed&) {
        return *this;
    }

    bool is_equal(const Fixed& other) const { 
        bool answer = ((sign==other.sign)&&(integer==other.integer));
        if (answer) {
            for (int i = 0; i < MAX_DIGITS; ++i) {
                if (digits[i] != other.digits[i]) {
                    answer = false;
                    break;
                }
            }
        }
        return answer;
    }

    Fixed operator-() const{
        Fixed reault(*this);
        result.sign = -result.sign;
        return result;
    }

    bool is_less(const Fixed& other)const{
        if(sign < other.sign){return true;}
        if(other.sign < sign){return false;}
        if(sign<0){
            return (-other)is_less(-(*this));
        }
        if(integer < other.integer){return true;}
        if(other.integer < integer){return false;}
        for(int i=0; i < MAX_DIGITS; ++i){
            if (digits[i] < other.digits[i]) {return true;}
            if (other.digits[i] < digits[i]) {return false;}
        }
        return false;
    }
};

template <int DIGITS1, int DIGITS2>
Fixed<((DIGITS1<DIGITS2) ? DIGITS2 : DIGITS1)> operator+(const Fixed<DIGITS1>& left, const Fixed<DIGITS2>& right){
    if (DIGITS1 < DIGITS2) {
        Fixed<DIGITS2> result(left);
        result += right;
        return result;
    } else {
        FIxed<DIGITS1> result(left);
        result += Fixed<DIGITS1>(right);
        return result;
    }
};

//template<int DIGITS1, int DIGITS2>
//Fixed<((DIGITS1<DIGITS2) ? DIGITS2 : DIGITS1)> operator-(const Fixed<DIGITS1>&, const Fixed<DIGITS2>&);
//
//template <int DIGITS1, int DIGITS2>
//Fixed<((DIGITS1 < DIGITS2) ? DIGITS2 : DIGITS1)> operator*(const Fixed<DIGITS1>&, const Fixed<DIGITS2>&);

template <int MAX_DIGITS>
bool operator<(const Fixed<MAX_DIGITS>& left, const Fixed<MAX_DIGITS>& right){
    return left.is_less(right);
};

template <int MAX_DIGITS>
bool operator>(const Fixed<MAX_DIGITS>& left, const Fixed<MAX_DIGITS>& right){
    return right.is_less(left);
};

template <int MAX_DIGITS>
bool operator<=(const Fixed<MAX_DIGITS>& left, const Fixed<MAX_DIGITS>& right){
    return !(right<left);
};

template <int MAX_DIGITS>
bool operator>=(const Fixed<MAX_DIGITS>& left, const Fixed<MAX_DIGITS>& right){
    return !(left<right);
};

template <int MAX_DIGITS>
bool operator==(const Fixed<MAX_DIGITS>& left, const Fixed<MAX_DIGITS>& right){
    return left.is_equal(right);
};

template <int MAX_DIGITS>
bool operator!=(const Fixed<MAX_DIGITS>&, const Fixed<MAX_DIGITS>&){
    return !(left==right);
};



#endif // !MYFIXED_25_sdfghjk_
