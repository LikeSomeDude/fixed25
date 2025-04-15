#include "fixed.h"
#include <iostream>
#include <string>
#include <stack>

//#define DIGITS 20
const int DIGITS = 20;

void replace(std::string& str, const std::string& old_str, const std::string& new_str) {
    size_t start = str.find(old_str);
    while (start != std::string::npos) {
        str.replace(start, old_str.length(), new_str);
        start = str.find(old_str, start + new_str.length());
    }
}

//skip whitespaces function
void remove_blanks(std::string& str) {
    size_t len = str.length();
    size_t ind = 0;
    for (size_t i = 0; i < len; ++i) {
        if (!isblank(str[i])) {
            str[ind] = str[i];
            ++ind;
        }
    }
    str.erase(str.begin() + ind, str.end());

}

void remove_unar_operators(std::string& str) {
    remove_blanks(str);
    replace(str, std::string("(-"), std::string("(0-"));
    replace(str, std::string("(+"), std::string("("));
}

void replace2operators(std::string& str) {
    replace(str, std::string("+-"), std::string("-"));
    replace(str, std::string("--"), std::string("+"));
    replace(str, std::string("-+"), std::string("-"));

}

Fixed<DIGITS> get_fixed(const std::string& formula, int& i) {
    // детектировать в строке fixed
    int begin = i;
    while (isdigit(formula[i])) ++i;
    if (formula[i] == '.') ++i;
    while (isdigit(formula[i])) ++i;
    int end = i - 1;
    std::string fixednumber = formula.substr(begin, end - begin + 1);
    //создать fixed
    return Fixed<DIGITS>(fixednumber.c_str());
}

int calc(const std::string& formula) {
    std::stack<Fixed<DIGITS>> numbers;
    std::stack<char> ops;
    for (size_t i = 0; i < formula.length(); ++i) {
        char ch = formula[i];
        if (ch == '(') {
            ops.push(ch);

        }
        else if (ch == ')') {
            char op;
            do {

                char op = ops.top();
                ops.pop();
                if (op == '+' || op == '-') {
                    Fixed<DIGITS> x2 = numbers.top();
                    numbers.pop();
                    Fixed<DIGITS> x1 = numbers.top();
                    numbers.pop();
                    numbers.push(x1 + x2);
                    (op == '+') ? numbers.push(x1 + x2) : numbers.push(x1 - x2);
                }
            } while (op != '(');
        }
        else if (ch == '+' || ch == '-') {
            char op;
            while (!ops.empty() && (ops.top() != '(')) {
                op = ops.top();
                ops.pop();
                Fixed<DIGITS> x2 = numbers.top();
                numbers.pop();
                Fixed<DIGITS> x1 = numbers.top();
                numbers.pop();
                numbers.push(x1 + x2);
                (op == '+') ? numbers.push(x1 + x2) : numbers.push(x1 - x2);
            }
            ops.push(ch);
        }
        else {
            Fixed<DIGITS> x = get_fixed(formula, i);
            numbers.push(x);
        }
    }

    return numbers.top();
}

int main() {
    //read the string with formula
    std::string formula;
    std::cout << "> ";
    std::getline(std::cin, formula); //adding to the string read data from console

    formula = "(" + formula + ")";

    //skip whitespaces
    remove_unar_operators(formula);
    replace2operators(formula);
    int ans = calc(formula);
    std::cout << formula << " = " << ans << std::endl;

    return 0;
}
