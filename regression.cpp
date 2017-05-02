#include "regression.h"
#include "csvreader.h"
#include <armadillo>
#include <vector>

regression::regression(){
}

regression::regression(csvReader read){
    reader = read;
    data= reader.getDataMatrix();
    n = reader.getNRows();
}

bool regression::setDataSource(csvReader read){
    reader = read;
    data= reader.getDataMatrix();
    n = reader.getNRows();
    return true;
}

std::string regression::getWarning(){
    return warning;
}

arma::mat regression::getX() {
    return X;
}

arma::mat regression::getY() {
    return Y;
}

arma::mat regression::getHat() {
    return Hat;
}

arma::mat regression::getbetaHat() {
    return betaHat;
}

arma::mat regression::getYHat() {
    return YHat;
}

arma::mat regression::getResidual() {
    return residual;
}

int regression::getK() {
    return k;
}

int regression::getN() {
    return n;
}

csvReader regression::getReader() {
    return reader;
}

bool regression::set(std::vector<int> listOfSelected,int y) {
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



arma::mat regression::CookMeasure(){
    CookResiduals.ones(n,1);
    for (int i = 0; i < n; i++) {
        double r_i = residual(i) / sqrt(MSres*(1-Hat(i,i)));
        CookResiduals(i) = r_i * r_i * Hat(i,i) /
                            ((k + 1) * (1 - Hat(i,i)));
    }
    return CookResiduals;
}
