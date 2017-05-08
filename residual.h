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
    residualStack();

    void setInitial(regressionType *reg);

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
residualStack<regressionType>::residualStack(){
    stack = {};
    count = 0;
}

template <typename regressionType>
void residualStack<regressionType>::setInitial(regressionType* reg){
    stack = {reg};
    count = 1;
}
template <typename regressionType>
residualStack<regressionType>::residualStack(regressionType* reg){
    stack = {reg};
    count = 1;
}

template <typename regressionType>
residualStack<regressionType>::~residualStack(){
    if (count >=1) {
        int size = stack.size();
        for (int i = 1; i < size; i++) {
            delete stack[i];
        }
    }
    stack.clear();
}

// Delete the data points at rowNumber, return the new regression,
// and push the old regression into stack
template <typename regressionType>
regressionType* residualStack<regressionType>::push(std::vector<int> rowNumber){
    regressionType* newRegression = new regressionType;
    newRegression = stack[count-1];
    newRegression->shedRows(rowNumber);
    newRegression->solve();
    stack.push_back(newRegression);
    count++;
    return newRegression;

}

// Restore the state before last delation
template <typename regressionType>
regressionType* residualStack<regressionType>::pop(){
    if (count == 1) return stack[0];
    else {
        regressionType* old = stack[count-1];
        delete old;
        stack.pop_back();
        count--;
        return old;
    }
}

template <typename regressionType>
regressionType* residualStack<regressionType>::peek(){
    return stack[count-1];
}

#endif // RESIDUAL_H
