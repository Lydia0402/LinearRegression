#include <armadillo>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "csvreader.h"
#include "lsregression.h"
#include "robustregression.h"
#include "distribution.h"

int main()
  {
    csvReader a;
    if (!a.readData("data.csv",true)) std::cout <<a.getWarning();
    for (std::string b: a.getTitleList() ) {
        std::cout <<b<<'\n';
    }
    arma::cout <<a.getDataMatrix();
    LSregression b(a);
    std::vector<int> in = {1};
    if (!b.set(in,0)) std::cout<<b.getWarning();
    else {
//        arma::cout<< b.getY();
//        arma::cout<< b.getX();
//        arma::mat c = b.getX();
//        arma::cout <<c.size();
        b.solve();
        arma::cout <<median(b.getbetaHat()) <<"Yes";
        b.CookMeasure().raw_print(std::cout);
        robustregression c(b);
        c.setT(1);
        arma::cout << c.solve();
    sdNormal n;
    std::cout<< n.pValue(3)<<std::endl;
    studentT t;
    t.set(10);
    std::cout<< t.pdf(2);

    return 0;
    }
}
