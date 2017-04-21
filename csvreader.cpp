#include "csvreader.h"

csvReader::csvReader(){
}

std::string csvReader::getWarning() {
    return warning;
}

std::vector<std::string> csvReader::getTitleList() {
    return titleList;
}

void csvReader::clearAllInstantVariables() {
    data.clear();
    nRows = 0;
    nCols = 0;
    titleList.clear();
    warning.clear();
}

arma::mat csvReader::getDataMatrix(){
    return data;
}

int csvReader::getNCols() {
    return nCols;
}

int csvReader::getNRows() {
    return nRows;
}

bool csvReader::readData(std::string filename, bool title) {
    std::ifstream infile;
    infile.open(filename.c_str());
    if (infile.fail()) {
        warning = "Cannot open the file";
        return false;
    }
    else {
        clearAllInstantVariables();

        // If the first row of data is the titles, read them into the vector titleList

        if (title == true) {
            std::string titles;
            if (!std::getline(infile,titles,'\r')) {
                warning = "This file is empty";
                return false;
            }
            std::stringstream ss(titles);
            std::string title;

            while(getline(ss,title,',')) {
                titleList.push_back(title);
            }

            nCols = titleList.size(); // Set the number of columns as the size of titleList

            std::string firstLine;
            if (!std::getline(infile,firstLine,'\r')){
                warning = "This file doesn't contain any numerical data";
                return false;
            }
            std::stringstream ss2(firstLine);
            std::string singleValue;

            // Save the first line into a vector

            std::vector<double> firstRow;
            while(getline(ss2,singleValue,',')) {
                double element = atof(singleValue.c_str());
                firstRow.push_back(element);
            }
            int size = firstRow.size();
            if (! (nCols == size)){
                warning = "The number of attributes must match in all the rows";
                return false;
            }

            // Initialize the data with the first row

            arma::rowvec firstrowvector(firstRow);
            arma::mat buffer(firstrowvector);
            data = buffer;
            nRows = 1;

        }

        // If the first row of data is numerical data instead of titles of data

        else {
            std::string firstLine;
            if (!std::getline(infile,firstLine,'\r')){
                warning = "This file is empty";
                return false;
            }
            std::stringstream ss(firstLine);
            std::string singleValue;

            // Save the first line into a vector

            std::vector<double> firstRow;
            while(getline(ss,singleValue,',')) {
                double ele = atof(singleValue.c_str());
                firstRow.push_back(ele);
            }

            nCols = firstRow.size(); // Set the number of columns as the size of firstRow

            // Initialize the data with the first row

            arma::rowvec firstrowvector(firstRow);
            arma::mat buffer(firstrowvector);
            data = buffer;
            nRows = 1;
            for (int i = 1; i < nCols+1; i++) {
                std::stringstream buff;
                buff<<'x'<<i;
                std::string defaultTitle = buff.str();
                titleList.push_back(defaultTitle);
            }
        }

        if (nCols == 0) {
            warning = "This file is empty";
            return false;
        }

        std::string Line;
        while(std::getline(infile,Line,'\r')){
            std::stringstream ss(Line);
            std::string singleValue;
            std::vector<double> aRow;
            while(getline(ss,singleValue,',')) {
                double el = atof(singleValue.c_str());
                aRow.push_back(el);
            }
            int size2 = aRow.size();
            if (size2 == nCols) {
                arma::rowvec arowvector(aRow);
                arma::mat buffer(arowvector);
                data = join_cols(data,buffer);
                nRows ++;
            }
            else {
                warning = "Each row must have the same number of element";
                return false;
            }
        }
    }
    return true;
}
