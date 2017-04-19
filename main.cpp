#include <armadillo>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "csvreader.h"


int main()
  {
    csvReader a;
    if (!a.readData("/Users/lydia/Downloads/B4.csv",true)) std::cout <<a.getWarning();
    for (std::string b: a.getTitleList() ) {
        std::cout <<b<<'\n';
    }
    arma::cout <<a.displaydata();
  return 0;

  }
