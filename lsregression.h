#ifndef LSREGRESSION_H
#define LSREGRESSION_H
#include "csvreader.h"
#include "regression.h"
#include <armadillo>

class LSregression : public regression
{

public:
    LSregression();
    LSregression(csvReader read);
    bool solve();

private:

};

#endif // LSREGRESSION_H
