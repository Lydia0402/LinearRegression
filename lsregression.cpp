#include "lsregression.h"
#include "csvreader.h"
#include <armadillo>
#include <vector>

LSregression::LSregression(){
}

LSregression::LSregression(csvReader read){
    reader = read;
    data= reader.getDataMatrix();
    n = reader.getNRows();
}

bool LSregression::solve(){
    Hat = X*arma::inv(X.t()*X)*X.t();
    betaHat = arma::inv(X.t()*X)*X.t()*Y;
    YHat = X * betaHat;
    residual = Y - YHat;
    meanY = accu(Y) / n;
    SSR = accu(square(YHat - meanY));
    SSres = accu(square(residual));
    SStotal = SSR + SSres;
    MSres = SSres / (n- (k + 1));
    return true;
}
