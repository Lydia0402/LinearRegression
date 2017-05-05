#include "distribution.h"
#include <cmath>
#include <vector>
#include <iostream>

Distribution::Distribution() {}

// For normal distribution, I use error function to calculate its pValue. For the detailed
// deduction, go to Wikipedia: https://en.wikipedia.org/wiki/Normal_distribution#Quantile_function

double sdNormal::pValue (double x){
    double pValue = (1 + erf( x / sqrt(2))) / 2;
    return 1 - pValue;
}

// For student t distribution and F distribution, since there is no direct closed form
// function that I can use, I use numerical integration (Simpson's rule) to solve it.
void studentT::set(int v){
    this->v = v;
}

double studentT::pdf (double x) {
    double pdf = tgamma((v + 1) / 2) * pow((1 + pow(x, 2) / v), -(v + 1) / 2)
                 / (sqrt(v * 3.1415926) * tgamma(v / 2));
    return pdf;
}

double studentT::integration (double lower, double upper) {
    int parts = 50;
    double x[parts + 1], y[parts + 1];
    double length = (upper - lower) / parts;
    for (int i = 0; i < parts + 1; i++) {
        x[i] = lower + i * length;
        y[i] = studentT::pdf(x[i]);
    }
    double sum = 0;
    for (int j = 1; j < parts; j += 2){
        sum = sum + 4 * y[j];
    }
    for (int j = 2; j < parts - 1; j += 2) {
        sum = sum + 2 * y[j];
    }
    double integration = (y[0] + y[parts] + sum) * length / 3;
    return integration;
}

double studentT::pValue (double x){
    double pValue = integration(0, x);
    pValue = 1 - pValue * 2;
    return pValue;
}

void Fisher::set(int v1, int v2) {
    this->v1 = v1;
    this->v2 = v2;
}

double Fisher::pdf(double x) {
    if (x==0 ) return Fisher::pdf(0.00001);
    double pdf =pow(v1,v1*0.5)*pow(v2,v2*0.5)*(tgamma(v1*0.5+v2*0.5))/((tgamma(v1*0.5)*tgamma(v2*0.5)))*(pow(x,(v1*0.5-1))/pow((v1*x+v2),(v1+v2)*0.5));
            /*sqrt(pow(v1*x, v1)*pow(v2, v2)/pow((v1*x+v2),(v1+v2))) /
                  (x * tgamma(v1/2)*tgamma(v2/2)/tgamma((v1+v2)/2));*/
//    std::cout<< x <<" is " <<pdf;
    return pdf;
}

double Fisher::pValue(double x){
    double pValue = 1 - Fisher::integration(0,x);
    return pValue;
}

double Fisher::integration (double lower, double upper) {
    int parts = 10000;
    std::vector<double> x,y;
    double length = (upper - lower) / parts;
    x.push_back(0);
    double y0 = Fisher::pdf(0);
    y.push_back(y0);
    for (int i = 1; i < parts + 1; i++) {
        x.push_back(lower + i * length);
        y.push_back(Fisher::pdf(x[i]));
    }
    double sum = 0;
    for (int j = 1; j < parts; j += 2){
        sum = sum + 4 * y[j];
    }
    for (int j = 2; j < parts - 1; j += 2) {
        sum = sum + 2 * y[j];
    }
    double integration = (y[0] + y[parts] + sum) * length / 3;
    return integration;
}
