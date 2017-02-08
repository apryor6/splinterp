// -- splinterp3.cpp --
// Created by AJ Pryor on 2/2/17.
//
#include <vector>
#include "mex.h"
#include "splinterp.h"

void mexFunction(int nlhs, mxArray *plhs[],int nrhs, const mxArray *prhs[]) {
    if (nrhs != 4) mexErrMsgTxt("Incorrect number of arguments. Syntax is Vq = splinterp3(V,Xq,Yq,Zq)");
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
        if ( nrows==1 | ncols==1 | nlayers==1 )mexErrMsgTxt("Input data is not 3D.");

        const size_t ncols_out = mxGetN(prhs[1]);
        const size_t nrows_out = mxGetM(prhs[1]);
        
        
        const mwSize ndims_out  = mxGetNumberOfDimensions(prhs[1]);
        const mwSize *dims_out  = mxGetDimensions(prhs[1]);
        size_t npoints = 1;
        for (auto i = 0; i < ndims_out; ++i) npoints*=dims_out[i];
        plhs[0] = mxCreateNumericArray(ndims_out, dims_out, mxDOUBLE_CLASS, mxCOMPLEX);
//
        Matrix_r = mxGetPr(prhs[0]);
        Matrix_i = mxGetPi(prhs[0]);
        y        = mxGetPr(prhs[1]);
        x        = mxGetPr(prhs[2]);
        z        = mxGetPr(prhs[3]);
        result_r = mxGetPr(plhs[0]);
        result_i = mxGetPi(plhs[0]);
      
        splinterp::parallel_interp3_cx(splinterp::interp3_F_cx<double>,Matrix_r, Matrix_i, nrows, ncols, nlayers, x, y, z, npoints, result_r, result_i, 1);

    } 
    else {

        double const *Matrix;
        double const *x;
        double const *y;
        double const *z;
        double *result;
        
        const mwSize ndims   = mxGetNumberOfDimensions(prhs[0]);
        const mwSize* dims   = mxGetDimensions(prhs[0]);
        const mwSize nrows   = dims[0];
        const mwSize ncols   = dims[1];
        const mwSize nlayers = dims[2];
        if ( nrows==1 | ncols==1 | nlayers==1 )mexErrMsgTxt("Input data is not 3D.");
        
        const size_t ncols_out = mxGetN(prhs[1]);
        const size_t nrows_out = mxGetM(prhs[1]);
        
        const mwSize ndims_out  = mxGetNumberOfDimensions(prhs[1]);
        const mwSize *dims_out  = mxGetDimensions(prhs[1]);
        size_t npoints = 1;
        for (auto i = 0; i < ndims_out; ++i) npoints*=dims_out[i];
        plhs[0] = mxCreateNumericArray(ndims_out, dims_out, mxDOUBLE_CLASS, mxREAL);
        
        Matrix = mxGetPr(prhs[0]);
        y        = mxGetPr(prhs[1]);
        x        = mxGetPr(prhs[2]);
        z        = mxGetPr(prhs[3]);
        result = mxGetPr(plhs[0]);
     
        splinterp::parallel_interp3(splinterp::interp3_F<double>,Matrix, nrows, ncols, nlayers, x, y, z, npoints, result, 1);

   }
}

