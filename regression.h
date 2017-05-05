#ifndef REGRESSION_H
#define REGRESSION_H
#include "csvreader.h"
#include <armadillo>
#include <sstream>
#include <cmath>
#include "distribution.h"
#include <string>

class regression
{
public:
    regression();
    regression(csvReader read);
    bool setDataSource(csvReader read);
    bool set(std::vector<int> listOfSelected,int y);
    arma::mat CookMeasure();
    std::string getSummary();
    std::string getWarning();
    arma::mat getX();
    arma::mat getY();
    arma::mat getHat();
    arma::mat getbetaHat();
    arma::mat getYHat();
    arma::mat getResidual();
    csvReader getReader();
    int getN();
    int getK();
    double getRSquare();
    double getRadjSquare();
    virtual bool solve() = 0;
    void printSummary(std::vector<std::vector<std::string>> & summary,
                      std::vector<std::string> & text) {
        std::vector<std::string> titles = reader.getTitleList();
        arma::mat C = inv(X.t() * X);
        std::vector<std::string> firstline= {"name", "prediction", "t-statistic", "p-value", "Acceptance of null hypothesis"};
        summary.push_back(firstline);
        studentT::studentT T;
        T.set(n-k-1);
        int size = betaHat.size();
        for (int i =0; i< size; i++) {
            std::vector<std::string> line;
            if (i == 0) line.push_back("intercept");
            else line.push_back(titles[listOfSelected[i-1]]);
            double prediction = betaHat(i);
            line.push_back(std::to_string(prediction));
            double t = betaHat(i) / sqrt(MSres*C(i,i));
            line.push_back(std::to_string(t));
            double pValue = T.pValue(std::abs(t));
            line.push_back(std::to_string(pValue));
            if (pValue >= significanceLevel) line.push_back("Reject");
            else line.push_back("Accept");
            summary.push_back(line);
        }
        std::string line1 = "";
        line1 = line1 + "R^2: " + std::to_string(RSquare) + ", ";
        line1 = line1 + "Radj^2: " + std::to_string(RadjSquare);
        text.push_back(line1);
        std::string line2 = "";
        line2 = line2 + "F statistic: ";
        double f = (SSR / k) / (SSres / (n - k - 1));
        line2 += std::to_string(f);
        line2 += " (v1 = ";
        line2 += std::to_string(k);
        line2 += ", v2 = ";
        line2 += std::to_string(n - k - 1);
        line2 += "), p-value = ";
        Fisher::Fisher F;
        F.set(k, n - k - 1);
        double pValue = F.pValue(f);
        line2 += std::to_string(pValue);
        text.push_back(line2);
        std::string line3 = "";
        line3 += "Number of data points n = ";
        line3 += std::to_string(n);
        line3 += ", Number of features k = ";
        line3 += std::to_string(k);
        text.push_back(line3);
    }

//        std::vector<std::string> titles = reader.getTitleList();
//        std::string line = "You choose ";
//        std::string space = " ";
//        for (int i: listOfSelected) line = line + titles[i] + space;
//        line += "as your input X, and ";
//        line = line + titles[y] + "as your output Y.";
//        summary.push_back(line);
//        arma::mat C = inv(X.t() * X);
//        studentT::studentT T;
//        T.set(n-k-1);
//        int size = betaHat.size();
//        for (int i = 0; i< size; i++) {
//            line.clear();
//            line += "Prediction value for the coefficient of ";
//            line += titles[listOfSelected[i]];
//            line += " is ";
//            double prediction = betaHat(i);
//            line += std::to_string(prediction);
//            line += ". Its t-statistic is ";
//            double t = betaHat(i) / sqrt(MSres*C(i,i));
//            line += std::to_string(t);
//            line += ". Its p-value is ";
//            double pValue = T.pValue(t);
//            line += std::to_string(pValue);
//            if (pValue >= significanceLevel) {
//                line += ". Reject the null hypothesis. ";
//            }
//            else {
//                line += ". Do not reject the null hypothesis. ";
//            }
//            summary.push_back(line);
//        }
//    }

protected:
    csvReader reader;
    std::vector<int> listOfSelected;
    int y;
    arma::mat data;
    arma::mat X,Y;
    arma::mat betaHat, Hat, YHat, residual, CookResiduals;
    int n,k;
    double significanceLevel;

    double SSR,SSres,MSres,SStotal,meanY,RSquare,RadjSquare;
    std::string warning;
};

#endif // REGRESSION_H
