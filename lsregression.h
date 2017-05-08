#ifndef LSREGRESSION_H
#define LSREGRESSION_H
#include "csvreader.h"
#include "regression.h"
#include <armadillo>

// Least square regression

class LSregression : public regression
{

public:
    LSregression();

    LSregression(csvReader read);
    // Directly construct the least square regression from a csvReader to use its data fields

    bool solve();
    // After all settings are done, solve this least square problem.
    // Returns true while solved successfully

private:

};

#endif // LSREGRESSION_H
