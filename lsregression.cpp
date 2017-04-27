#include "lsregression.h"
#include "csvreader.h"
#include <armadillo>
#include <vector>

LSregression::LSregression(csvReader read){
    reader = read;
    data= reader.getDataMatrix();
    n = reader.getNRows();
}

std::string LSregression::getWarning(){
    return warning;
}

arma::mat LSregression::getX() {
    return X;
}

arma::mat LSregression::getY() {
    return Y;
}

arma::mat LSregression::getHat() {
    return Hat;
}

arma::mat LSregression::getbetaHat() {
    return betaHat;
}

arma::mat LSregression::getYHat() {
    return YHat;
}

arma::mat LSregression::getResidual() {
    return residual;
}
bool LSregression::set(std::vector<int> listOfSelected,int y) {
    X.clear();

    if (listOfSelected.size() == 0 ){
        warning = "Please at least select one column.";
        return false;
    }

    else {
        k = listOfSelected.size();
        X =data.col(listOfSelected[0]);
        if (k > 1) {
            for (int i = 1; i < k; i++) {
                if (listOfSelected[i] >=0 and listOfSelected[i]< reader.getNCols()) {
                    X = join_rows(X,data.col(listOfSelected[i]));
                }
                else {
                    warning = "Selected column number exceeds the boundary.";
                    return false;
                }
            }
        }
        arma::mat One(n,1); One.ones(); X=join_rows(One,X);

        // Check whether the list contains two identical numbers
        sort(listOfSelected.begin(),listOfSelected.end());
        for (int j = 0; j < k - 1; j++) {
            if (listOfSelected[j] == listOfSelected[j+1]) {
                warning = "It is illegal to select the same column twice.";
                X.clear();
                k = 0;
                return false;
            }
        }
    }

    Y.clear();
    if (y >=0 and y< reader.getNCols()) {
        for (int q: listOfSelected){
            if (y == q) {
                warning = "It is illegal to select the same column as x and y simultaneously.";
                return false;
            }
        }
        Y = data.col(y);
        return true;
    }
    else {
        warning = "Selected column number exceeds the boundary.";
        return false;
    }
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

arma::mat LSregression::CookMeasure(){
    CookResiduals.ones(n,1);
    for (int i = 0; i < n; i++) {
        double r_i = residual(i) / sqrt(MSres*(1-Hat(i,i)));
        CookResiduals(i) = r_i * r_i * Hat(i,i) /
                            ((k + 1) * (1 - Hat(i,i)));
    }
    return CookResiduals;
}

// Private:
