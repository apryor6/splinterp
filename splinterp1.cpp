//
// Created by Alan Pryor on 2/2/17.
//
#include <vector>
#include "mex.h"
#include "splinter.h"
using namespace splinter;

void mexFunction(int nlhs, mxArray *plhs[],int nrhs, const mxArray *prhs[]) {
    if (mxIsComplex(prhs[0])){
        double const *Matrix_r; 
        double const *Matrix_i;
        double const *x;
        double *result_r;
        double *result_i;
        
        size_t nrows   = mxGetM(prhs[0]);
        size_t npoints = mxGetM(prhs[1])*mxGetN(prhs[1]);
        plhs[0] = mxCreateDoubleMatrix(npoints, 1, mxCOMPLEX);

        Matrix_r = mxGetPr(prhs[0]);
        Matrix_i = mxGetPi(prhs[0]);
        x        = mxGetPr(prhs[1]);
        result_r = mxGetPr(plhs[0]);
        result_i = mxGetPi(plhs[0]);
        
        interp1_F_cx<double>(Matrix_r,Matrix_i, nrows, x, npoints, result_r, result_i);

    } else {

        double const *Matrix; 
        double const *x;
        double *result;
        
        size_t nrows   = mxGetM(prhs[0]);
        size_t npoints = mxGetM(prhs[1])*mxGetN(prhs[1]);
        plhs[0] = mxCreateDoubleMatrix(npoints, 1, mxREAL);

        Matrix = mxGetPr(prhs[0]);
        x      = mxGetPr(prhs[1]);
        result = mxGetPr(plhs[0]);
        
        interp1_F<double>(Matrix, nrows, x, npoints, result);

    }
}

