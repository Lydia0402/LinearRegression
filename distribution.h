#ifndef DISTRIBUTION_H
#define DISTRIBUTION_H
#include <cmath>

// This is the superclass for all distributions.

class Distribution {
public:

    Distribution();

    virtual double pValue(double x) = 0;
};


// This is standard normal distribution N(0,1).

class sdNormal : public Distribution {
public:

    double pValue(double x);
    // pValue returns the probability that the random variable is larger than x.

};


// This is student t distribution.

class studentT : public Distribution {
public:

    double pdf(double x);
    // returns the probability that the random variable is equal to x.

    double pValue(double x);
    // pValue returns the probability that the random variable is larger than x.

    void set(int v);
    // Set the degree of freedom of t distribution.

    double integration(double lower, double upper);
    // returns the integration of t distribution from lower to upper.

private:

    int v; // Degree of freedom
};


// This is Fisher distribution.

class Fisher : public Distribution {

public:

    double pdf(double x);
    // returns the probability that the random variable is equal to x.

    double pValue(double x);
    // pValue returns the probability that the random variable is larger than x.

    void set(int v1, int v2);
    // Set the degree of freedom of F distribution.

    double integration(double lower, double upper);
    // returns the integration of F distribution from lower to upper.

private:
    int v1,v2; // Degree of freedom of two chi-square distribution
};

#endif // DISTRIBUTION_H
