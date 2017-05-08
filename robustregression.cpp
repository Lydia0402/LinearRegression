#include "robustregression.h"

robustregression::robustregression(){

}

robustregression::robustregression(csvReader read){
    reader = read;
}

robustregression::robustregression(LSregression LSR) {

    initial = LSR;
    X = LSR.getX();
    Y = LSR.getY();
    reader = LSR.getReader();
    listOfSelected = LSR.getlistOfSelected();
    y = LSR.gety();
    data = LSR.getData();
    n = LSR.getN();
    k = LSR.getK();
    significanceLevel = LSR.getSignificance();
    warning = LSR.getWarning();
}


// I use gradient decent to solve robust regression problem.

bool robustregression::solve(){

    // Use the result got from least square solution as the initial beta

    arma::mat beta_0(initial.getbetaHat());

    // These two matrices are used for iteration

    arma::mat beta_n(initial.getK()+1,1);
    arma::mat beta_nplus1(initial.getK()+1,1);

    // Initialize the first W matrix use beta_0. W matrix is a matrix with diagnol entris
    // that are entris of corresbonding gradient vector of beta.
    //For more details, go to textbook for reference.

    arma::mat W = generateW(beta_0,t);

    // Initialize beta_1 and beta_2

    beta_n = inv(X.t() * W * X) * X.t() * W * Y;
    W = generateW(beta_n,t);
    beta_nplus1 = inv(X.t() * W * X) * X.t() * W * Y;

    // Set the stop threshold as the sum of squares of the difference of two successive
    // interation betas is smaller than 0.00000001

    while ((accu(square(beta_nplus1 - beta_n))) > 0.00000001) {
        beta_n = beta_nplus1;
        W = generateW(beta_n,t);
        beta_nplus1 = inv(X.t() * W * X) * X.t() * W * Y;
    }

    betaHat = beta_nplus1;

    // Calculate other statistics

    Hat = X*arma::inv(X.t()*X)*X.t();
    YHat = X * betaHat;
    residual = Y - YHat;
    meanY = accu(Y) / n;
    SSR = accu(square(YHat - meanY));
    SSres = accu(square(residual));
    SStotal = SSR + SSres;
    MSres = SSres / (n- (k + 1));
    RSquare = SSR / SStotal;
    RadjSquare = 1 - (SSres / (n - (k + 1))) / (SStotal / (n - 1));
    CookMeasure();
    RstudentResidual();
    return true;
}

/* I use Huber's function as my loss function, thus I need to let the user input his choice
 * of t (the threshold) before.*/

bool robustregression::setT(double t) {
    if (t > 0) {
        this->t = t;
        return true;
    }
    else return false;
}

// This function is used to generate W matrix from last beta, robust esitimation of standard
// deviation sigma = median(|x-median(x)|) is used.
// Here I use Huber's function as the loss function, thus the user need to pass a parameter t.
// See Wikipedia for reference: https://en.wikipedia.org/wiki/Huber_loss

arma::mat robustregression::generateW(arma::mat beta, double t){

    // First calculate robust estimation for standard deviation

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

    // Then construct W matrix using Huber's function

    arma::mat W(initial.getN(),initial.getN());
    W.zeros();
    for (int i = 0; i < initial.getN(); i++) {
        arma::mat resi = Y.row(i) - X.row(i) * beta;
        if (resi(0) == 0) {
            W(i,i) = 1;
        }
        else {
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
