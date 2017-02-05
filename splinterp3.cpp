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
        double const *y;
        double const *z;
        double *result_r;
        double *result_i;
        
        const mwSize* dims   = mxGetDimensions(prhs[0]);
        const mwSize nrows   = dims[0];
        const mwSize ncols   = dims[1];
        const mwSize nlayers = dims[2];
        const size_t ncols_out = mxGetN(prhs[1]);
        const size_t nrows_out = mxGetM(prhs[1]);
        plhs[0] = mxCreateDoubleMatrix(nrows_out, ncols_out, mxCOMPLEX);
//
        Matrix_r = mxGetPr(prhs[0]);
        Matrix_i = mxGetPi(prhs[0]);
        y        = mxGetPr(prhs[1]);
        x        = mxGetPr(prhs[2]);
        z        = mxGetPr(prhs[3]);
        result_r = mxGetPr(plhs[0]);
        result_i = mxGetPi(plhs[0]);
        const size_t npoints = nrows_out * ncols_out;
      
        interp3_F_cx<double>(Matrix_r, Matrix_i, nrows, ncols, nlayers, x, y, z, npoints, result_r, result_i);

    } 
    else {

        double const *Matrix;
        double const *x;
        double const *y;
        double const *z;
        double *result;
        
        const mwSize* dims   = mxGetDimensions(prhs[0]);
        const mwSize nrows   = dims[0];
        const mwSize ncols   = dims[1];
        const mwSize nlayers = dims[2];
        const size_t ncols_out = mxGetN(prhs[1]);
        const size_t nrows_out = mxGetM(prhs[1]);
        plhs[0] = mxCreateDoubleMatrix(nrows_out, ncols_out, mxCOMPLEX);

        Matrix = mxGetPr(prhs[0]);
        y        = mxGetPr(prhs[1]);
        x        = mxGetPr(prhs[2]);
        z        = mxGetPr(prhs[3]);
        result = mxGetPr(plhs[0]);
        const size_t npoints = nrows_out * ncols_out;
     
        interp3_F<double>(Matrix, nrows, ncols, nlayers, x, y, z, npoints, result);

   }
}

