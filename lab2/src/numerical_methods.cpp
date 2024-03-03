#include <cmath>
#include <iostream>
using namespace std;

double method_of_half_division(double(*f)(double), double a, double b, double eps) {
    int iter = 0;
    while (fabs(b - a) > 2 * eps) {
        double x1 = (a + b - eps) / 2, x2 = (a + b + eps) / 2;
        double y1 = f(x1), y2 = f(x2);

        y1 > y2 ? a = x1 : b = x2;
        iter++;
    }
    cout << "Количество итераций: " << iter << endl;
    return (a + b) / 2;
}

double method_of_golden_ratio(double(*f)(double), double a, double b, double eps) {
    int iter = 0;

    double x1 = a + .382 * (b - a), x2 = a + .618 * (b - a);
    double y1 = f(x1), y2 = f(x2);
    while (fabs(b - a) > 2 * eps) {
        if (y1 < y2) {
            b = x2;
            x2 = x1;
            y2 = y1;
            x1 = a + .382 * (b - a);
            y1 = f(x1);
        } else {
            a = x1;
            x1 = x2;
            y1 = y2;
            x2 = a + .618 * (b - a);
            y2 = f(x2);
        }
        iter++;
    }
    cout << "Количество итераций:  " << iter << endl;
    return (a + b) / 2;
}

double chord_method(double(*df)(double), double a, double b, double eps) {
    int iter = 0;
    double xm;
    do {
        xm = a - (a - b) * df(a) / (df(a) - df(b));
        df(xm) > 0 ? b = xm : a = xm;

        iter++;
    } while (fabs(df(xm)) > eps);
    cout << "Количество итераций:  " << iter << endl;
    return xm;
}

double newton_method(double(*df)(double), double(*ddf)(double), double a, double b, double eps) {
    double xk = (a + b) / 2;

    int iter = 0;
    while (fabs(df(xk)) > eps) {
        xk = xk - df(xk) / ddf(xk);
        iter++;
    }
    cout << "Количество итераций:  " << iter << endl;
    return xk;
}