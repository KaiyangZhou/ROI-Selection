#include "mex.h"
#include "string.h"
using namespace std;

void holeFill_max_mex(int h, int w, int winsize, double*R )
{
	int k = (winsize-1)/2;

	for (int i = k; i < h-k; ++i) {
		for (int j = k; j < w-k; ++j) {
			// if value is zero, it needs to be filled
			if (R[i+j*h] == 0) {
				double maxVal = 0;
				// find max value among its neighbours
				for (int m = i-k; m <= i+k; ++m) {
					for (int n = j-k; n <= j+k; ++n) {
						double neiVal = R[m+n*h];
						if (neiVal > maxVal) {
							maxVal = neiVal;
						}
					}
				}
				R[i+j*h] = maxVal;
			}
		}
	}
}

void holeFill_avg_mex(int h, int w, int winsize, double*R )
{
	int k = (winsize-1)/2;

	for (int i = k; i < h-k; ++i) {
		for (int j = k; j < w-k; ++j) {
			// if value is zero, it needs to be filled
			if (R[i+j*h] == 0) {
				double sum = 0;
				double nz = 0; // number of non-zero elements
				// only average non-zero elements
				for (int m = i-k; m <= i+k; ++m) {
					for (int n = j-k; n <= j+k; ++n) {
						double neiVal = R[m+n*h];
						if (neiVal != 0) {
							sum = sum + neiVal;
							nz = nz + 1;
						}
					}
				}
				if (nz > 0) R[i+j*h] = sum / nz;
			}
		}
	}
}

// this function is particularly for collection of training data, not recommended for testing usage
void holeFill_left_mex(int h, int w, double*R )
{
	for (int i = 1; i < h; ++i) {
		for (int j = 1; j < w; ++j) {
			// if value is zero, it needs to be filled
			if (R[i+j*h] == 0) {
				// do something here to fill the hole
				if (R[i+(j-1)*h] != 0) {
					R[i+j*h] = R[i+(j-1)*h]; // equal to the left one
				}
			}
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
	if (nrhs != 3) {
		mexErrMsgTxt("Number of inputs should be: 3");
	}
	if (nlhs != 1) {
		mexErrMsgTxt("Number of output should be: 1");
	}

	if (mxGetClassID(prhs[0]) != mxDOUBLE_CLASS) {
		mexErrMsgTxt("Depth image must be double");
	}
	int h = (int)mxGetM(prhs[0]);
	int w = (int)mxGetN(prhs[0]);
	double *I = mxGetPr(prhs[0]);
	//printf("Height: %d, Width: %d\n", h, w);

	if (mxIsChar(prhs[1]) != 1) {
		mexErrMsgTxt("Method must be a string");
	}
	char *method = mxArrayToString(prhs[1]);
	if (method == NULL) {
		mexErrMsgTxt("string is NULL");
	}
	//printf("%s\n", method);

	int winsize = mxGetScalar(prhs[2]);
	if ((winsize-1)%2 != 0 && winsize < 3) {
		mexErrMsgTxt("winsize must be an odd number and bigger or equal to 3");
	}
	//printf("winsize: %d\n", winsize);

	plhs[0] = mxCreateNumericMatrix(h, w, mxDOUBLE_CLASS, mxREAL);
	double *R = mxGetPr(plhs[0]);

	// copy values from I to R
	for (int i = 0; i < h; ++i) {
		for (int j = 0; j < w; ++j) {
			R[i+j*h] = I[i+j*h];
		}
	}

	if (strcmp(method, "max") == 0) {
		//printf("method is max\n");
		holeFill_max_mex(h, w, winsize, R);
	}
	else if (strcmp(method, "avg") == 0) {
		//printf("method is avg\n");
		holeFill_avg_mex(h, w, winsize, R);
	}
	else if (strcmp(method, "left") == 0) {
		holeFill_left_mex(h, w, R);
	}
	else {
		mexErrMsgTxt("method should be either 'max' or 'avg'");
	}


}