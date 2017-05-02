#include "robustregression.h"

robustregression::robustregression(csvReader read){
    reader = read;
}

robustregression::robustregression(LSregression LSR) {
    initial = LSR;
    X = LSR.getX();
    Y = LSR.getY();
}

arma::mat robustregression::solve(){
    arma::mat beta_0(initial.getbetaHat());
    arma::mat beta_n(initial.getK()+1,1);
    arma::mat beta_nplus1(initial.getK()+1,1);
    arma::mat W = generateW(beta_0);
        arma:: cout << W;
    beta_n = inv(X.t() * W * X) * X.t() * W * Y;
    W = generateW(beta_n);
    beta_nplus1 = inv(X.t() * W * X) * X.t() * W * Y;
    while ((accu(square(beta_nplus1 - beta_n))) > 0.00000001) {
        beta_n = beta_nplus1;
        W = generateW(beta_n);
        beta_nplus1 = inv(X.t() * W * X) * X.t() * W * Y;
    }
    return beta_nplus1;
}

arma::mat robustregression::generateW(arma::mat beta){

    arma::mat res(initial.getN(),1);
    for (int i = 0; i < initial.getN(); i++) {
         arma::mat resi = Y.row(i) - X.row(i) * beta;
         res(i) = resi(0);
    }
    res = arma::abs(res);
    arma::mat medi = median(res);

    double med = medi.at(0);
    for (int i = 0; i < initial.getN(); i++) {
         res(i) = res(i) - med;
    }
    res = abs(res);
    double MADN = med / 0.6745;

    arma::mat W(initial.getN(),initial.getN());
    W.zeros();
    for (int i = 0; i < initial.getN(); i++) {
        arma::mat resi = Y.row(i) - X.row(i) * beta;
        if (resi(0) == 0) {
            W(i,i) = 1;
        }
        else {
            double t = 1;
            double z = (resi(0) / MADN);
            if (std::abs(z) <= t) {
                W(i,i) = 1;
            }
            else {
                if (z > 0) W(i,i) = t / z;
                else if (z < 0 ) W(i,i) = -t / z;
                else W(i,i) = 0;
            }
        }
    }
    return W;
}
