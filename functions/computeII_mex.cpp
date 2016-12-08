#include "mex.h"

void computeII(double *I, double *II, int nrow, int ncol) 
{
	double s[nrow][ncol];
	for (int x = 0; x < nrow; x++) {
		for (int y = 0; y < ncol; y++) {
			// compute s(x,y)
			double s_prev = 0; 
			if (y-1 != -1) s_prev = s[x][y-1];
			s[x][y] = s_prev + I[y*nrow+x];
			// compute ii(x,y)
			double II_prev = 0;
			if (x-1 != -1) II_prev = II[y*nrow+x-1];
			II[y*nrow+x] = II_prev + s[x][y];
		}
	}
}

/*------------------------------------------------------------------
 * Arguments description
 * nlhs: number of expected output
 * plhs: array of pointers to the expected output mxArrays
 * nrhs: number of expected input
 * prhs: array of pointers to the input mxArrays
 *------------------------------------------------------------------*/
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	// check input arguments and output arguments
	if (nrhs != 1) {
		mexErrMsgTxt("Only one input argument is requried, which is a binary map");
	}
	if (nlhs != 1) {
		mexErrMsgTxt("There is only one output, which is the integral image (II)");
	}
	if (mxGetClassID(prhs[0]) != mxDOUBLE_CLASS) {
		mexErrMsgTxt("Input should be of double precision");
	}

	int nrow = mxGetM(prhs[0]); // number of rows
	int ncol = mxGetN(prhs[0]); // number of columns
	double *I = mxGetPr(prhs[0]); // input depth image

	// prepare output
	plhs[0] = mxCreateNumericMatrix(nrow, ncol, mxDOUBLE_CLASS, mxREAL);
	double *II = mxGetPr(plhs[0]); // output integral image

	computeII(I,II,nrow,ncol);

}