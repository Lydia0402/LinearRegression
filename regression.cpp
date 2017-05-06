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

regression::~regression(){
    clear();
}

bool regression::setDataSource(csvReader read){
    reader = read;
    data= reader.getDataMatrix();
    n = reader.getNRows();
    return true;
}

bool regression::setSignificance(double significanceLevel){
    if (0 < significanceLevel < 1) {
        this-> significanceLevel = significanceLevel;
        return true;
    }
    else {
        warning = "Significance level must lie between 0 and 1!";
        return false;
    }
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

double regression::getRSquare(){
    return RSquare;
}

double regression::getRadjSquare(){
    return RadjSquare;
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
        this->listOfSelected = listOfSelected;
        this->y = y;
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

void regression::printSummary(std::vector<std::vector<std::string>> & summary,
                  std::vector<std::string> & text) {
    summary.clear();
    text.clear();
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

void regression::ResidualAnalysis(bool cook, std::vector<std::vector<std::string>> & analysis){
    analysis.clear();
    if (cook == false) {
        std::vector<std::string> firstline = {"Index of data points", "Leverage score", "Residuals", "R-student", "Potential outliers"};
        analysis.push_back(firstline);
        RstudentResidual();
        for (int i = 0; i < n; i++) {
            std::vector<std::string> line;
            line.push_back(std::to_string(i+1));
            line.push_back(std::to_string(Hat(i,i)));
            line.push_back(std::to_string(residual(i)));
            line.push_back(std::to_string(Rstudent(i)));
            studentT T;
            T.set(n-k-2);
            if (T.pValue(Rstudent(i)) >= significanceLevel) line.push_back("No");
            else line.push_back("Yes");
            analysis.push_back(line);
        }
    }
    else {
        std::vector<std::string> firstline = {"Index of data points", "Leverage score", "Residuals", "Cook's measure", "Potential outliers"};
        analysis.push_back(firstline);
        CookMeasure();
        for (int i = 0; i < n; i++) {
            std::vector<std::string> line;
            line.push_back(std::to_string(i+1));
            line.push_back(std::to_string(Hat(i,i)));
            line.push_back(std::to_string(residual(i)));
            line.push_back(std::to_string(CookResiduals(i)));
            Fisher F;
            F.set(k+1,n-k-1);
            if (F.pValue(CookResiduals(i)) >= significanceLevel) line.push_back("No");
            else line.push_back("Yes");
            analysis.push_back(line);
        }
    }
}

// Return R-student residuals
// https://en.wikipedia.org/wiki/Studentized_residual

arma::mat regression::RstudentResidual(){
    Rstudent.ones(n,1);
    for (int i = 0; i < n; i++) {
        double Si = (((n-k-1)*MSres) - pow(residual(i),2)/(1-Hat(i,i))) / (n-k-2);
        double t_i = residual(i) / sqrt(Si*(1-Hat(i,i)));
        Rstudent(i) = t_i;
    }
    return Rstudent;
}

// Return Cook's measure:
// https://en.wikipedia.org/wiki/Cook%27s_distance

arma::mat regression::CookMeasure(){
    CookResiduals.ones(n,1);
    for (int i = 0; i < n; i++) {
        double r_i = residual(i) / sqrt(MSres*(1-Hat(i,i)));
        CookResiduals(i) = r_i * r_i * Hat(i,i) /
                            ((k + 1) * (1 - Hat(i,i)));
    }
    return CookResiduals;
}

regression & regression::operator=(const regression & src) {
    if (this != &src) {
        clear();
        deepCopy(src);
    }
    return *this;
}

void regression::deepCopy(const regression &src) {
    this->reader = src.reader;
    this->listOfSelected = src.listOfSelected;
    this->y = src.y;
    arma::mat buffer1(src.data);
    this->data = buffer1;
    arma::mat buffer2(src.X);
    arma::mat buffer3(src.Y);
    this->X = buffer2; this->Y = buffer3;
    arma::mat buffer4(src.betaHat), buffer5(src.Hat), buffer6(src.YHat), buffer7(src.residual),
            buffer8(src.CookResiduals), buffer9(src.Rstudent);
    this->betaHat = buffer4; this->Hat = buffer5; this->YHat = buffer6; this->residual = buffer7;
    this->CookResiduals = buffer8; this->Rstudent = buffer9;
    this->n = src.n; this->k = src.k;
    this->significanceLevel = src.significanceLevel;
    this->SSR = src.SSR;
    this->SSres = src.SSres;
    this->MSres = src.MSres;
    this->SStotal = src.SStotal;
    this->meanY = src.meanY;
    this->RSquare = src.RSquare;
    this->RadjSquare = src.RadjSquare;
    this->warning = src.warning;
}

void regression::clear(){
    listOfSelected.clear();
    data.clear();
    X.clear();
    Y.clear();
    betaHat.clear();
    Hat.clear();
    YHat.clear();
    residual.clear();
    CookResiduals.clear();
    Rstudent.clear();
}
