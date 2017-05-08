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
    // Constructor: construct with a csvReader
    regression();
    regression(csvReader read);
    virtual ~regression();
    bool setDataSource(csvReader read);

    // Set functions for X and Y, return true if successfully
    bool set(std::vector<int> listOfSelected,int y);

    // Set the significance level, return true if successfully
    bool setSignificance(double significanceLevel = 0.05);

    // solve method will be implemented in subclasses
    virtual bool solve() = 0;

    /* Users need to input an empty vector<vector<string>> and an empty vector<string> respectively,
       then the program add summaries to them.
       summary: contains the information about the prediction coefficients
       text: contains the information about the */
    void printSummary(std::vector<std::vector<std::string>> & summary,
                      std::vector<std::string> & text);
    
    
    /* Functions relavent to residual anylysis part
     * bool cook: whether use Cook's measure to analyize the residuals
     * analysis: pass an empty object into this parameter, then the function will add analysis information into it */
    void ResidualAnalysis(bool cook, std::vector<std::vector<std::string>> & analysis);
    
    /* This function will return you a (k+1)*1 matrix with prediction of coeffecients!
     * k denotes the number of features, +1 because the need of intercept
     * For example, if the regression function is y= beta1 + beta2*x
     * This function will return a matrix [beta1, beta2] */
    arma::mat getbetaHat();
    
    /* This function will return you a n*k matrix X */
    arma::mat getX();

    // For drawing pictures, only be used when k = 1!!

    double Xmax();
    double Xmin();
    /* This function will return you a n*1 matrix Y */
    arma::mat getY();

    // For drawing pictures, only be used when k = 1!!
    double Ymax();
    double Ymin();

    void shedRows(std::vector<int> rowNumber);
    
    // Series of functions that enable users to get private data
    arma::mat CookMeasure();
    arma::mat RstudentResidual();
    std::string getWarning();
    arma::mat getHat();
    arma::mat getYHat();
    arma::mat getResidual();
    arma::mat getData();
    double getSignificance();
    csvReader getReader();
    int getN();
    int getK();
    double getRSquare();
    double getRadjSquare();
    std::vector<int> getlistOfSelected();
    int gety();
    regression & operator=(const regression & src);
    void clear();

protected:
    csvReader reader;
    std::vector<int> listOfSelected;
    int y;
    arma::mat data;
    arma::mat X,Y;
    arma::mat betaHat, Hat, YHat, residual, CookResiduals, Rstudent;
    int n,k;
    double significanceLevel = 0.05;
    double SSR,SSres,MSres,SStotal,meanY,RSquare,RadjSquare;
    std::string warning;

    void deepCopy(const regression & src);
};

#endif // REGRESSION_H
