#ifndef ROBUSTREGRESSION_H
#define ROBUSTREGRESSION_H
#include "csvreader.h"
#include <armadillo>
#include "lsregression.h"
#include "regression.h"

class robustregression: public regression
{
public:
    robustregression(csvReader read);
    robustregression(LSregression LSR);
    bool setObjective();
    bool solve();

private:
    LSregression initial;
    arma::mat generateW(arma::mat beta, double t);
};

#endif // ROBUSTREGRESSION_H
