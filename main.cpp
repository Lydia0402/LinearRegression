#include <armadillo>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "csvreader.h"
#include "lsregression.h"

int main()
  {
    csvReader a;
    if (!a.readData("/Users/lydia/Documents/LinearRegression/res/data3.csv",true)) std::cout <<a.getWarning();
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
        arma::cout <<b.getbetaHat();
        b.CookMeasure().raw_print(std::cout);
    return 0;
    }
}
