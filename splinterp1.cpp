// -- splinterp1.cpp --
// Created by AJ Pryor on 2/2/17.
//
#include <vector>
#include "mex.h"
#include "splinterp.h"

void mexFunction(int nlhs, mxArray *plhs[],int nrhs, const mxArray *prhs[]) {
    if (nrhs != 2) mexErrMsgTxt("Incorrect number of arguments. Syntax is Vq = splinterp1(V,Xq)");
    if (mxIsComplex(prhs[0])){
        double const *Matrix_r; 
        double const *Matrix_i;
        double const *x;
        double *result_r;
        double *result_i;
        
        // allow for vectors to be Nx1 or 1xN
        size_t nrows   = std::max(mxGetM(prhs[0]),mxGetN(prhs[0])); 

        const mwSize ndims_out  = mxGetNumberOfDimensions(prhs[1]);
        const mwSize *dims_out  = mxGetDimensions(prhs[1]);
        size_t npoints = 1;
        for (auto i = 0; i < ndims_out; ++i) npoints*=dims_out[i];
        plhs[0] = mxCreateNumericArray(ndims_out, dims_out, mxDOUBLE_CLASS, mxCOMPLEX);

        Matrix_r = mxGetPr(prhs[0]);
        Matrix_i = mxGetPi(prhs[0]);
        x        = mxGetPr(prhs[1]);
        result_r = mxGetPr(plhs[0]);
        result_i = mxGetPi(plhs[0]);
        
        splinterp::parallel_interp1_cx(splinterp::interp1_F_cx<double>, Matrix_r,Matrix_i, nrows, x, npoints, result_r, result_i, 1);

    } else {
        double const *Matrix; 
        double const *x;
        double *result;
        
        // allow for vectors to be Nx1 or 1xN
        size_t nrows   = std::max(mxGetM(prhs[0]),mxGetN(prhs[0]));
        
        const mwSize ndims_out  = mxGetNumberOfDimensions(prhs[1]);
        const mwSize *dims_out  = mxGetDimensions(prhs[1]);
        size_t npoints = 1;
        for (auto i = 0; i < ndims_out; ++i) npoints*=dims_out[i];
        plhs[0] = mxCreateNumericArray(ndims_out, dims_out, mxDOUBLE_CLASS, mxREAL);

        Matrix = mxGetPr(prhs[0]);
        x      = mxGetPr(prhs[1]);
        result = mxGetPr(plhs[0]);
        
        splinterp::parallel_interp1(splinterp::interp1_F<double>, Matrix, nrows, x, npoints, result, 1);

    }
}

