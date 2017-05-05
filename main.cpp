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
    b.set(in,0);
    b.solve();
    std::vector<std::vector<std::string>> summary;
    std::vector<std::string> text;
    b.printSummary(summary,text);
    int n_Cols = summary.size();
    for (int i = 0; i < n_Cols; i++) {
        int n_Rows = summary[i].size();
        for (int j = 0; j < n_Rows; j++ ) std::cout << summary[i][j];
//    else {
////        arma::cout<< b.ge
/// tY();
////        arma::cout<< b.getX();
////        arma::mat c = b.getX();
////        arma::cout <<c.size();
//        if (!b.solve()) std::cout << b.getWarning();
//        std::string line;
//        std::vector<std::string> summary;
//        b.printSummary(summary);
//        for (std::string i : summary) std::cout << i;
//        arma::cout <<median(b.getbetaHat()) <<"Yes";
//        b.CookMeasure().raw_print(std::cout);
//        robustregression c(b);
//        c.setT(1);
//        arma::cout << c.solve();
//    sdNormal n;
//    std::cout<< n.pValue(3)<<std::endl;
//    studentT t;
//    t.set(10);
//    std::cout<< t.pdf(2);

//    return 0;
//        }}
}
}
