#ifndef RESIDUAL_H
#define RESIDUAL_H
#include "regression.h"
#include "lsregression.h"
#include "robustregression.h"
#include <vector>
#include <armadillo>

template <typename regressionType>
class residualStack
{
public:
    // Constructor   
    residualStack(regressionType* reg);

    ~residualStack();
    
    // Delete the data points at rowNumber, return the new regression,
    // and push the old regression into stack
    virtual regressionType* push(std::vector<int> rowNumber) ;
    
    // Restore the state before last delation and return the deleted regression
    virtual regressionType* pop();

    // Return the regression on the surface
    virtual regressionType* peek();

protected:
    
    std::vector<regressionType*> stack;
    
    int count;
    
};

template <typename regressionType>
residualStack::residualStack(regressionType* reg){
    stack = {reg};
    count = 1;
}

template <typename regressionType>
residualStack::~residualStack(){
    for (regressionType* i: stack) {
        delete *i;
    }
    stack.clear();
}

// Delete the data points at rowNumber, return the new regression,
// and push the old regression into stack
template <typename regressionType>
regressionType* residualStack::push(std::vector<int> rowNumber){
    regressionType* newRegression = new regressionType;
    newRegression = stack[count-1];
    std::sort(rowNumber.begin(),rowNumber.end());
    std::reverse(rowNumber.begin(),rowNumber.end());
    int size = rowNumber.size();
    for (int i = 0; i < size; i++) {
        newRegression->X.shed_rows(rowNumber[i]);
    }
    newRegression->solve();
    stack.push_back(newRegression);
    count++;
    return newRegression;

}

// Restore the state before last delation
template <typename regressionType>
regressionType* residualStack::pop(){
    if (count == 1) return *stack[0];
    else {
        regressionType* old = stack[count-1];
        stack.pop_back();
        count--;
        return old;
    }
}

template <typename regressionType>
regressionType* residualStack::peek(){
    return stack[count-1];
}

#endif // RESIDUAL_H
