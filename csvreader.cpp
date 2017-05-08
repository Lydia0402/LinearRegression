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
    address.clear();
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

bool csvReader::hasTitle() {
    return hastitle;
}

std::string csvReader::filePath(){
    return address;
}

bool csvReader::readData(std::string filename, bool title) {
    hastitle = title;
    address = filename;
    if (tryLineBreak(filename,title,'\r') == true) return true;
    else if (tryLineBreak(filename,title,'\n') == true) return true;
    else return false;
}


bool csvReader::tryLineBreak(std::string filename, bool title, char lineBreak) {
    std::ifstream infile;
    infile.open(filename.c_str());
    if (infile.fail()) {
        try {
            infile.exceptions(infile.failbit);
        } catch (const std::ios_base::failure & e)
        {
            warning = e.what();
            infile.clear();
            infile.close();
            return false;
        }
    }
    else {
        clearAllInstantVariables();

        // If the first row of data is the titles, read them into the vector titleList

        if (title == true) {
            std::string titles;
            if (!std::getline(infile,titles,lineBreak)) {
                warning = "This file is empty";
                infile.clear();
                infile.close();
                return false;
            }
            std::stringstream ss(titles);
            std::string title;

            while(getline(ss,title,',')) {
                titleList.push_back(title);
            }

            nCols = titleList.size(); // Set the number of columns as the size of titleList

            std::string firstLine;
            if (!std::getline(infile,firstLine,lineBreak)){
                warning = "This file doesn't contain any numerical data";
                infile.clear();
                infile.close();
                return false;
            }
            std::stringstream ss2(firstLine);
            std::string singleValue;

            // Save the first line into a vector

            std::vector<double> firstRow;
            while(getline(ss2,singleValue,',')) {
                std::string save = singleValue;
                double element = atof(singleValue.c_str());
                if ((element == 0) and (save != "0")) {
                    warning = "Contains non-numeric data!";
                    return false;
                }
                firstRow.push_back(element);
            }
            int size = firstRow.size();
            if (! (nCols == size)){
                warning = "The number of attributes must match in all the rows";
                infile.clear();
                infile.close();
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
            if (!std::getline(infile,firstLine,lineBreak)){
                warning = "This file is empty";
                infile.clear();
                infile.close();
                return false;
            }
            std::stringstream ss(firstLine);
            std::string singleValue;

            // Save the first line into a vector

            std::vector<double> firstRow;
            while(getline(ss,singleValue,',')) {
                std::string save = singleValue;
                double ele = atof(singleValue.c_str());
                if ((ele == 0) and (save != "0")) {
                    warning = "Contains non-numeric data!";
                    return false;
                }
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
            infile.clear();
            infile.close();
            return false;
        }

        std::string Line;
        while(std::getline(infile,Line,lineBreak)){
            std::stringstream ss(Line);
            std::string singleValue;
            std::vector<double> aRow;
            while(getline(ss,singleValue,',')) {
                std::string save = singleValue;
                double el = atof(singleValue.c_str());
                if ((el == 0) and (save != "0")) {
                    warning = "Contains non-numeric data!";
                    return false;
                }
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
                infile.clear();
                infile.close();
                return false;
            }
        }
    }
    infile.close();
    return true;
}

csvReader & csvReader::operator=(const csvReader & src) {
    if (this != &src) {
        this->clearAllInstantVariables();
        deepCopy(src);
    }
    return *this;
}


void csvReader::deepCopy(const csvReader & src) {
    address = src.address;
    hastitle = src.hastitle;
    arma::mat buffer(src.data);
    data = buffer;
    nRows = src.nRows;
    nCols = src.nCols;
    titleList = src.titleList;
    warning = src.warning;
}
