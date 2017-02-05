//
// Created by Alan Pryor on 2/1/17.
//

#ifndef SPLINTER_H
#define SPLINTER_H


#include <cmath>
#include "mex.h"


// Interpolate position x,y from 2D array stored in data, which is assumed to lie on an integer coordinate system.
// Values of x and y that lie outside of the dimensions of data are set to 0.
namespace splinter{
        
    template <typename T>
    void interp1_F(const T* const data, 
                   const size_t& nrows,
                   const double* const x,
                   const size_t& N, T* result){

        for (auto i = 0; i < N; ++i) { 
           // get coordinates of bounding grid locations
           int x_1 = (int) std::floor(x[i]);
           // handle special case where x is the last element
           if (x_1 == (nrows-1)){x_1 -= 1;}
           // return 0 for target values that are out of bounds
              if (x_1 < 0 | (x_1+1) > (nrows - 1)){
                result[i] = 0; 
            } 
            else {
                // get the array values
                const T& f_1 = data[x_1];
                const T& f_2 = data[x_1+1];
                // compute weights
               T w_x1 = x_1+1 - x[i];
               result[i] = f_1 * w_x1 +f_2 - f_2*w_x1;

            }
        }
    }

    template <typename T>
    void interp1_F_cx(const T* const data_r, const T* const data_i,
                      const size_t& nrows, const double* const x, 
                      const size_t& N, T* result_r, T* result_i){

        for (auto i = 0; i < N; ++i) { 
           // get coordinates of bounding grid locations
           int x_1 = (int) std::floor(x[i]);
           // handle special case where x is the last element
           if (x_1 == (nrows-1)){x_1 -= 1;}
           // return 0 for target values that are out of bounds
              if (x_1 < 0 | (x_1+1) > (nrows - 1)){
                result_r[i] = 0;
                result_i[i] = 0;
            } 
            else {
                // get the array values
               const T& f_1_r = data_r[x_1];
               const T& f_2_r = data_r[x_1+1];
                // compute weights
               T w_x1 = x_1+1 - x[i];
               result_r[i] = f_1_r * w_x1 +f_2_r - f_2_r*w_x1;
               
               const T& f_1_i = data_i[x_1];
               const T& f_2_i = data_i[x_1+1];
               result_i[i] = f_1_i * w_x1 +f_2_i - f_2_i*w_x1;

            }
        }
    }
    
    template <typename T>
    void interp2_F_cx(const T* const data,
                      const size_t& nrows, const size_t& ncols,
                      const double* const x, const double* const y,
                      const size_t& N, T* result){

        for (auto i = 0; i < N; ++i) {

           // get coordinates of bounding grid locations
           int x_1 = (int) std::floor(x[i]);
           int x_2 = x_1 + 1;
           int y_1 = (int) std::floor(y[i]);
           int y_2 = y_1 + 1;

           // handle special case where x/y is the last element
           if (x_1 == (nrows-1) )   { x_2 -= 1; x_1 -= 1;}
           if (y_1 == (ncols-1) )   { y_2 -= 1; y_1 -= 1;}

           // return 0 for target values that are out of bounds
           if (x_1 < 0 | x_2 > (nrows - 1) |  y_1 < 0 | y_2 > (ncols - 1)){
                result[i] = 0;

            } 
            else {
                
                // get the array values
                const T& f_11 = data[x_1 + y_1*nrows];
                const T& f_12 = data[x_1 + y_2*nrows];
                const T& f_21 = data[x_2 + y_1*nrows];
                const T& f_22 = data[x_2 + y_2*nrows];

                // compute weights
                T w_x1 = x_2 - x[i];
                T w_x2 = x[i] - x_1;
                T w_y1 = y_2 - y[i];
                T w_y2 = y[i] - y_1;

                double a,b;
                a = f_11 * w_x1 + f_21 * w_x2;
                b = f_12 * w_x1 + f_22 * w_x2;
                result[i] = a * w_y1 + b * w_y2;
            }
        }
    }


    template <typename T>
    void interp2_F_cx(const T* const data_r, const T* const data_i,
                      const size_t& nrows, const size_t& ncols, 
                      const double* const x, const double* const y,
                      const size_t& N, T* result_r, T* result_i){

        for (auto i = 0; i < N; ++i) {

           // get coordinates of bounding grid locations
           int x_1 = (int) std::floor(x[i]);
           int x_2 = x_1 + 1;
           int y_1 = (int) std::floor(y[i]);
           int y_2 = y_1 + 1;
           
           // handle special case where x/y is the last element
           if (x_1 == (nrows-1) )   { x_2 -= 1; x_1 -= 1;}
           if (y_1 == (ncols-1) )   { y_2 -= 1; y_1 -= 1;}

           // return 0 for target values that are out of bounds
           if (x_1 < 0 | x_2 > (nrows - 1) |  y_1 < 0 | y_2 > (ncols -1)){
                result_r[i] = 0;
                result_i[i] = 0;

            } 
            else {
            
                // get the array values
                const T& f_11_r = data_r[x_1 + y_1*nrows];
                const T& f_12_r = data_r[x_1 + y_2*nrows];
                const T& f_21_r = data_r[x_2 + y_1*nrows];
                const T& f_22_r = data_r[x_2 + y_2*nrows];

                // compute weights
                T w_x1 = x_2 - x[i];
                T w_x2 = x[i] - x_1;
                T w_y1 = y_2 - y[i];
                T w_y2 = y[i] - y_1;

                double a,b;
                a = f_11_r * w_x1 + f_21_r * w_x2;
                b = f_12_r * w_x1 + f_22_r * w_x2;
                result_r[i] = a * w_y1 + b * w_y2;

                const T& f_11_i = data_i[x_1 + y_1*nrows];
                const T& f_12_i = data_i[x_1 + y_2*nrows];
                const T& f_21_i = data_i[x_2 + y_1*nrows];
                const T& f_22_i = data_i[x_2 + y_2*nrows];

                a = f_11_i * w_x1 + f_21_i * w_x2;
                b = f_12_i * w_x1 + f_22_i * w_x2;
                result_i[i] = a * w_y1 + b * w_y2;
            }
        }
    }


    template <typename T>
    void interp3_F(const T* data, 
                   const size_t& nrows, const size_t& ncols, const size_t& nlayers,
                   const double* x, const double* y, const double* z, 
                   const size_t N, T* result){
        
        // Assumes Fortran style ordering for data
        for (auto i = 0; i < N; ++i) {

            // get coordinates of bounding grid locations
            int x_1 = (int) std::floor(x[i]);
            int x_2 = x_1 + 1;
            int y_1 = (int) std::floor(y[i]);
            int y_2 = y_1 + 1;
            int z_1 = (int) std::floor(z[i]);
            int z_2 = z_1 + 1;

            // handle special case where x,x, or z is the last element
            if (x_1 == (nrows-1) )   { x_2 -= 1; x_1 -= 1;}
            if (y_1 == (ncols-1) )   { y_2 -= 1; y_1 -= 1;}
            if (z_1 == (nlayers-1) ) { z_2 -= 1; z_1 -= 1;}

            // return 0 for target values that are out of bounds
            if (x_1 < 0 | x_2 > (nrows - 1) |  y_1 < 0 | y_2 > (ncols - 1) | z_1 < 0 | z_2 > (nlayers - 1)){
                result[i] = 0;

            } 
            else {
                
                // precompute some stride-related constants that are reused
                const size_t layer_size = ncols * nrows;
                auto z_stride = z_1*layer_size;
                auto y_1_stride = y_1*nrows;
                auto y_2_stride = y_2*nrows;
                
                // get the array values for the lower z slice
                const T& f_11_1 = data[z_stride + y_1_stride + x_1];
                const T& f_12_1 = data[z_stride + y_2_stride + x_1];
                const T& f_21_1 = data[z_stride + y_1_stride + x_2];
                const T& f_22_1 = data[z_stride + y_2_stride + x_2];

                // compute weights
                T w_x1 = x_2  - x[i];
                T w_x2 = x[i] - x_1;
                T w_y1 = y_2  - y[i];
                T w_y2 = y[i] - y_1;

                double a_1, b_1;
                a_1 = f_11_1 * w_x1 + f_21_1 * w_x2;
                b_1 = f_12_1 * w_x1 + f_22_1 * w_x2;

                const T F_1 = a_1 * w_y1 + b_1 * w_y2;

                // update some stride-related constants that are reused
                z_stride = z_2*layer_size;
                
                // get the array values for the upper z slice
                const T& f_11_2 = data[z_stride + y_1_stride + x_1];
                const T& f_12_2 = data[z_stride + y_2_stride + x_1];
                const T& f_21_2 = data[z_stride + y_1_stride + x_2];
                const T& f_22_2 = data[z_stride + y_2_stride + x_2];

                double a_2, b_2;
                a_2 = f_11_2 * w_x1 + f_21_2 * w_x2;
                b_2 = f_12_2 * w_x1 + f_22_2 * w_x2;

                const T F_2 = a_2 * w_y1 + b_2 * w_y2;

                T w_z1 = z_2 - z[i];
                T w_z2 = z[i] - z_1;

               result[i] = F_1 * w_z1 + F_2*w_z2;
            }
        }
    }

        
    template <typename T>
    void interp3_F_cx(const T* const data_r,  const T* const data_i, 
                      const size_t& nrows, const size_t& ncols, const size_t& nlayers, 
                      const double* const x, const double* const y, const double* const z, const size_t N, 
                      T* result_r, T* result_i){
        
        // Fortran style ordering for trilinear interpolation of complex data
        for (auto i = 0; i < N; ++i) {

            // get coordinates of bounding grid locations
            int x_1 = (int) std::floor(x[i]);
            int x_2 = x_1 + 1;
            int y_1 = (int) std::floor(y[i]);
            int y_2 = y_1 + 1;
            int z_1 = (int) std::floor(z[i]);
            int z_2 = z_1 + 1;
            
            // handle special case where x, y, or z is the last element
            if (x_1 == (nrows-1) )   { x_2 -= 1; x_1 -= 1;}
            if (y_1 == (ncols-1) )   { y_2 -= 1; y_1 -= 1;}
            if (z_1 == (nlayers-1) ) { z_2 -= 1; z_1 -= 1;}

            // return 0 for target values that are out of bounds
            if (x_1 < 0 | x_2 > (nrows - 1) |  y_1 < 0 | y_2 > (ncols - 1) | z_1 < 0 | z_2 > (nlayers - 1)){
                result_r[i] = 0;
                result_i[i] = 0;

            } 
            else {
                    const size_t layer_size = ncols * nrows;
                    auto z_stride = z_1*layer_size;
                    auto y_1_stride = y_1*nrows;
                    auto y_2_stride = y_2*nrows;
                    
                    // compute weights
                    T w_x1 = x_2  - x[i];
                    T w_x2 = x[i] - x_1;
                    T w_y1 = y_2  - y[i];
                    T w_y2 = y[i] - y_1;

                {
                    
                    // lower Z plane, real part

                    const T& f_11_1 = data_r[z_stride + y_1_stride + x_1];
                    const T& f_12_1 = data_r[z_stride + y_2_stride + x_1];
                    const T& f_21_1 = data_r[z_stride + y_1_stride + x_2];
                    const T& f_22_1 = data_r[z_stride + y_2_stride + x_2];

                    double a_1, b_1;
                    a_1 = f_11_1 * w_x1 + f_21_1 * w_x2;
                    b_1 = f_12_1 * w_x1 + f_22_1 * w_x2;

                    const T F_1 = a_1 * w_y1 + b_1 * w_y2;

                    // upper Z plane, real part

                    z_stride = z_2*layer_size;
                    const T& f_11_2 = data_r[z_stride + y_1_stride + x_1];
                    const T& f_12_2 = data_r[z_stride + y_2_stride + x_1];
                    const T& f_21_2 = data_r[z_stride + y_1_stride + x_2];
                    const T& f_22_2 = data_r[z_stride + y_2_stride + x_2];

                    double a_2, b_2;
                    a_2 = f_11_2 * w_x1 + f_21_2 * w_x2;
                    b_2 = f_12_2 * w_x1 + f_22_2 * w_x2;

                    const T F_2 = a_2 * w_y1 + b_2 * w_y2;

                    // compute weights
                    T w_z1 = z_2 - z[i];
                    T w_z2 = z[i] - z_1;

                   result_r[i] = F_1 * w_z1 + F_2*w_z2;
                }
                
                {
                    // lower Z plane, imaginary part
                    
                    auto z_stride = z_1*layer_size;
                    const T& f_11_1 = data_i[z_stride + y_1_stride + x_1];
                    const T& f_12_1 = data_i[z_stride + y_2_stride + x_1];
                    const T& f_21_1 = data_i[z_stride + y_1_stride + x_2];
                    const T& f_22_1 = data_i[z_stride + y_2_stride + x_2];

                    double a_1, b_1;
                    a_1 = f_11_1 * w_x1 + f_21_1 * w_x2;
                    b_1 = f_12_1 * w_x1 + f_22_1 * w_x2;

                    const T F_1 = a_1 * w_y1 + b_1 * w_y2;

                    // upper Z plane, imaginary part

                    z_stride = z_2*layer_size;
                    const T& f_11_2 = data_i[z_stride + y_1_stride + x_1];
                    const T& f_12_2 = data_i[z_stride + y_2_stride + x_1];
                    const T& f_21_2 = data_i[z_stride + y_1_stride + x_2];
                    const T& f_22_2 = data_i[z_stride + y_2_stride + x_2];

                    double a_2, b_2;
                    a_2 = f_11_2 * w_x1 + f_21_2 * w_x2;
                    b_2 = f_12_2 * w_x1 + f_22_2 * w_x2;

                    const T F_2 = a_2 * w_y1 + b_2 * w_y2;

                    T w_z1 = z_2 - z[i];
                    T w_z2 = z[i] - z_1;

                   result_i[i] = F_1 * w_z1 + F_2*w_z2;
                }                        
            }
        }
    }
}
#endif //SPLINTER_H
