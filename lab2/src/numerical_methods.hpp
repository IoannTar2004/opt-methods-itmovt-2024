#ifndef LAB2_NUMERICAL_METHODS_HPP
#define LAB2_NUMERICAL_METHODS_HPP

double method_of_half_division(double(*f)(double), double a, double b, double eps);
double method_of_golden_ratio(double(*f)(double), double a, double b, double eps);
double chord_method(double(*df)(double), double a, double b, double eps);
double newton_method(double(*df)(double), double(*ddf)(double), double a, double b, double eps);

#endif
