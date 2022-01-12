#include <math.h>

double valueOfFunction(double x){
    return (pow((x-3),2));
}

double analyticDerivation(double x){
    return (2*(x-3));
}

double numericDerivation(double x){
    return ((valueOfFunction(x+pow(10,-8))-valueOfFunction(x))/pow(10,-8));
}