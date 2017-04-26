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
    if (!a.readData("data3.csv",true)) std::cout <<a.getWarning();
//    for (std::string b: a.getTitleList() ) {
//        std::cout <<b<<'\n';
//    }
//    arma::cout <<a.getDataMatrix();
//    LSregression b(a);
//    std::vector<int> in = {2,3,4};
//    if (!b.set(in,1)) std::cout<<b.getWarning();
//    else {
//        arma::cout<< b.getY();
//        arma::cout<< b.getX();
//        arma::mat c = b.getX();
//        arma::cout <<c.size();
       arma::mat A(5, 5, arma::fill::randu);

       arma::mat B = A + A;
       arma::mat C = A * B;
    return 0;

    }
