#include <iostream>
#include <cmath>
#include <functional>
using namespace std;

double quadratic_approximation(double x_start, double delta_x, double eps1, double eps2, const function<double(double)>& f);

inline double f(double x, double y) {
    return pow(x,3) + pow(y,3) - 3*x*y;
}
inline double grad_x(double x, double y) {
    return 3*x*x - 3*y;
}
inline double grad_y(double x, double y) {
    return 3*y*y - 3*x;
}

pair<double, double> gradient_descent(double eps, double l, double x0, double y0) {
    int iter = 1;
    while (true) {
        double gr_x = grad_x(x0, y0), gr_y = grad_y(x0, y0);
        double x1 = x0 - l * gr_x, y1 = y0 - l * gr_y;

        if (abs(f(x1, y1) - f(x0, y0)) <= eps) {
            cout << "Итераций: " << iter << endl;
            return {x1, y1};
        }
        else {
            x0 = x1;
            y0 = y1;
        }
        iter++;
    }
}

pair<double, double> fastest_descent(double eps, double x, double y) {
    int iter = 1;
    while (true) {
        double gr_x = grad_x(x, y);
        double gr_y = grad_y(x, y);
        if (sqrt(gr_x * gr_x + gr_y * gr_y) <= eps) {
            cout << "Итераций: " << iter << endl;
            return {x, y};
        }
        double h = quadratic_approximation(2, 0.01, eps, eps / 50, [&gr_x, &gr_y, &x, &y](double xh) -> double {
            return pow(x - xh * gr_x, 3) + pow(y - xh * gr_y, 3) - 3*(x - xh * gr_x)*(y - xh * gr_y);
        });

        x = x - h * gr_x;
        y = y - h * gr_y;
        iter++;
    }
}

int main() {
    system("chcp 65001 > NUL");
    cout << "\tМетод градиентного спуска" << endl;
    auto p = gradient_descent(0.001, 0.1, 0.5, 0.5);
    cout << "x = " << p.first << ", y = " << p.second << ", z = " << f(p.first, p.second) << endl << endl;

    cout << "\tМетод наискорейшего спуска" << endl;
    p = fastest_descent(0.001, 0.9, 0.91);
    cout << "x = " << p.first << ", y = " << p.second << ", z = " << f(p.first, p.second) << endl << endl;
    return 0;
}
