# splinter
SPLINTER is a fast C++ template library for parallel calculation of linear, bilinear, and trilinear interpolation. SPLINTER also contains MEX extension files that allow its routines to be called from MATLAB/Octave.

## Usage
SPLINTER consists of a single header file `splinter.h`, which contains a number of different functions for various types of linear interpolation. Each interpolation function name is of the form `interp#[\_cx][\_F]` where # is either 1,2, or 3, indicating linear, bilinear, or trilinear interpolation, respectively. The addition of "`_cx`" indicates that it is intended for complex-valued inputs. Note: complex arrays are to be provided as two separate arrays, one representing the real part and another representing imaginary, rather than interleaved complex format such as in `std::complex`. The addition of `_F` indicate the arrays are assumed to be in column-major (Fortran) order. 

### Parameters
All function parameters for the lower-dimensional routines are a subset of those for the higher equivalents. Therefore, we choose to document all parameters here just once.

  - const T* const data_r 
  - const T* const data_i,
  - const size_t& nrows,
  - const size_t& ncols, 
  - const size_t& nlayers,
  - const T* const x, 
  - const T* const y, 
  - const T* const z, 
  - const size_t& N, 
  - T* result_r, T* 
  - result_i,
  - const long long& origin_offset=0
