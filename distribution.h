#ifndef DISTRIBUTION_H
#define DISTRIBUTION_H
#include <cmath>

class Distribution
{
public:
    Distribution();
    virtual double pValue(double x) = 0;
};

class sdNormal : public Distribution {
public:
    double pValue(double x);
};

class studentT : public Distribution {
public:
    double pdf(double x);
    double pValue(double x);
    void set(int v);
    double integration(double lower, double upper);
private:
    int v; // Degree of freedom
};

class Fisher : public Distribution {
public:
    double pdf(double x);
    double pValue(double x);
    void set(int v1, int v2);
    double integration(double lower, double upper);
private:
    int v1,v2; // Degree of freedom of two chi-square distribution
};

#endif // DISTRIBUTION_H
