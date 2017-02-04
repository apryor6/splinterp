//
// Created by Alan Pryor on 2/2/17.
//
#include <vector>
#include "mex.h"
#include "interp.h"

void mexFunction(int nlhs, mxArray *plhs[],int nrhs, const mxArray *prhs[]) {
    if (mxIsComplex(prhs[0])){
        double const *Matrix_r; 
        double const *Matrix_i;
        double const *x;
        double const *y;
        double *result_r;
        double *result_i;
        
        size_t nrows   = mxGetN(prhs[0]);
        size_t ncols   = mxGetM(prhs[0]);
        size_t npoints = mxGetN(prhs[1]);
        plhs[0] = mxCreateDoubleMatrix(npoints, 1, mxCOMPLEX);

        Matrix_r = mxGetPr(prhs[0]);
        Matrix_i = mxGetPi(prhs[0]);
        y        = mxGetPr(prhs[1]);
        x        = mxGetPr(prhs[2]);
        result_r = mxGetPr(plhs[0]);
        result_i = mxGetPi(plhs[0]);

//         interp2<double>(Matrix_r, nrows, ncols, x, y, npoints, result_r);
//         interp2<double>(Matrix_i, nrows, ncols, x, y, npoints, result_i);
        interp2_cx<double>(Matrix_r,Matrix_i, nrows, ncols, x, y, npoints, result_r, result_i);

    } else {

        double const *Matrix; 
        double const *x;
        double const *y;
        double *result;
        
        size_t nrows   = mxGetN(prhs[0]);
        size_t ncols   = mxGetM(prhs[0]);
        size_t npoints = mxGetN(prhs[1]);
        plhs[0] = mxCreateDoubleMatrix(npoints, 1, mxREAL);

        Matrix = mxGetPr(prhs[0]);
        y      = mxGetPr(prhs[1]);
        x      = mxGetPr(prhs[2]);
        result = mxGetPr(plhs[0]);

        interp2<double>(Matrix, nrows, ncols, x, y, npoints, result);

    }
}

