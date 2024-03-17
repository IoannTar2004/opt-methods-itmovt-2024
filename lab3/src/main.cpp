#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

double function(double x) {
    return 1 / x + exp(x);
}

double quadratic_approximation(double x_start, double delta_x, double eps1, double eps2, double (*f)(double)) {
    int iter = 0;
    double x1 = x_start;
    while (true) {
        iter++;
        double x2 = x1 + delta_x;
        double f1 = f(x1), f2 = f(x2);
        double x3 = f1 > f2 ? x1 + 2 * delta_x : x1 - delta_x, f3 = f(x3);

        while (true) {
            vector<double> fs = {f1, f2, f3}, xs = {x1, x2, x3};
            auto min_iter = min_element(fs.begin(), fs.end());
            double f_min = *min_iter, x_min = xs[min_iter - fs.begin()];

            double denominator = 2 * ((x2 - x3) * f1 + (x3 - x1) * f2 + (x1 - x2) * f3);
            if (denominator == 0) {
                x1 = x_min;
                continue;
            }
            double _x_ = ((x2 * x2 - x3 * x3) * f1 + (x3 * x3 - x1 * x1) * f2 + (x1 * x1 - x2 * x2) * f3) / denominator;
            bool less_eps1 = abs((f_min - f(_x_)) / f(_x_)) < eps1, less_eps2 = abs((x_min - _x_) / _x_) < eps2;

            if (less_eps1 && less_eps2) {
                cout << "Количество итераций: " << iter << endl;
                return _x_;
            }
            else if (!(less_eps1 && less_eps2) && _x_ >= x1 && _x_ <= x3) {
                x3 = x2;
                x2 = min(_x_, x_min);
                f2 = f(x2);
                f3 = f(x3);
                continue;
            } else {
                x1 = _x_;
                break;
            }
        }
    }
}

int main() {
    system("chcp 65001 > NUL");
    double x = quadratic_approximation(4, 0.001, 0.0001, 0.001, function);
    cout << "Точка минимума: x = " << x << ", y = " << function(x) << endl;
    return 0;
}
