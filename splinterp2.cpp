// -- splinterp2.cpp --
// Created by AJ Pryor on 2/2/17.
//
#include <vector>
#include "mex.h"
#include "splinterp.h"

void mexFunction(int nlhs, mxArray *plhs[],int nrhs, const mxArray *prhs[]) {
    if (mxIsComplex(prhs[0])){
        double const *Matrix_r; 
        double const *Matrix_i;
        double const *x;
        double const *y;
        double *result_r;
        double *result_i;
        
        size_t nrows   = mxGetM(prhs[0]);
        size_t ncols   = mxGetN(prhs[0]);
        mexPrintf("ncols = %i\n",ncols);
        mexPrintf("nrows = %i\n",nrows);
        const mwSize ndims  = mxGetNumberOfDimensions(prhs[1]);
        const mwSize *dims  = mxGetDimensions(prhs[1]);
        size_t npoints = 1;
        for (auto i = 0; i < ndims; ++i) npoints*=dims[i];
        plhs[0] = mxCreateNumericArray(ndims, dims, mxDOUBLE_CLASS, mxCOMPLEX);
    mexPrintf("npoints = %i\n",npoints);
        Matrix_r = mxGetPr(prhs[0]);
        Matrix_i = mxGetPi(prhs[0]);
        y        = mxGetPr(prhs[1]);
        x        = mxGetPr(prhs[2]);
        result_r = mxGetPr(plhs[0]);
        result_i = mxGetPi(plhs[0]);
        splinterp::parallel_interp2_cx(splinterp::interp2_F_cx<double>,Matrix_r,Matrix_i, nrows, ncols, x, y, npoints, result_r, result_i, 1);

    } else {

        double const *Matrix; 
        double const *x;
        double const *y;
        double *result;
        
        size_t nrows   = mxGetM(prhs[0]);
        size_t ncols   = mxGetN(prhs[0]);
        
        const mwSize ndims  = mxGetNumberOfDimensions(prhs[1]);
        const mwSize *dims  = mxGetDimensions(prhs[1]);
        size_t npoints = 1;
        for (auto i = 0; i < ndims; ++i) npoints*=dims[i];
        plhs[0] = mxCreateNumericArray(ndims, dims, mxDOUBLE_CLASS, mxREAL);

        Matrix = mxGetPr(prhs[0]);
        y      = mxGetPr(prhs[1]);
        x      = mxGetPr(prhs[2]);
        result = mxGetPr(plhs[0]);
        splinterp::parallel_interp2(splinterp::interp2_F<double>,Matrix, nrows, ncols, x, y, npoints, result, 1);

    }
}

