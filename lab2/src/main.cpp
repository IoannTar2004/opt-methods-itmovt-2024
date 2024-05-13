#include <iostream>
#include <cmath>
#include "numerical_methods.hpp"
using namespace std;

inline double f(double x) {
    return exp(-pow(0.12 - x * 0.47, 2) + pow(0.4 - x * 0.03, 2) + 2*(0.12 - x * 0.47, 2)*(0.4 - x * 0.03) - (0.4 - x * 0.03));
}

inline double df(double x) {
    return -1/(x*x) + exp(x);
}

inline double ddf(double x) {
    return 2/(x*x*x) + exp(x);
}

int main() {
    system("chcp 65001 > NUL");

    cout << "\tMетод половинного деления\n";
    double x = method_of_half_division(f, 0.1, 0.5, 0.001);
    cout << "Точка минимума: x = " << x << ", y = " << f(x) << endl << endl;

//    cout << "\tMетод золотого сечения\n";
//    x = method_of_golden_ratio(f, 0.5, 1.5, 0.001);
//    cout << "Точка минимума: x = " << x << ", y = " << f(x) << endl << endl;
//
//    cout << "\tMетод хорд\n";
//    x = chord_method(df, 0.5, 1.5, 0.001);
//    cout << "Точка минимума: x = " << x << ", y = " << f(x) << endl << endl;
//
//    cout << "\tMетод Ньютона\n";
//    x = newton_method(df, ddf, 0.5, 1.5, 0.001);
//    cout << "Точка минимума: x = " << x << ", y = " << f(x) << endl;
}