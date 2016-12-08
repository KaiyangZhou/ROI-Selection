#include "mex.h"
#include "math.h"

// Rule: numX * numZ = numCells
#define numCells 100
#define numX 10
#define numZ 10

/*------------------------------------------------------------------
 * Input description
 * XYZ: 2D array containing x,y,z information of datapoints
 * rect: 1-by-4 vector defining a rectangle region
 *------------------------------------------------------------------
 * Output description
 * density: numCells-by-1 vector describing the density of each cell
 * labels: m-by-1 vector containing a label for each datapoint
 *------------------------------------------------------------------*/
void ptsFilter(const int numPts, double *XYZ, double *rect, double *density, double *labels)
{
	const double xmin = rect[0];
	const double xmax = rect[1];
	const double zmin = rect[2];
	const double zmax = rect[3];

	const double xstep = (xmax - xmin) / numX;
	const double zstep = (zmax - zmin) / numZ;

    // suffix
    // s: start, e: end
	double xs = xmin;
	double xe = xs + xstep;
	double zs = zmin;
	double ze = zs + zstep;

	// Visit every datapoint
	for (int i = 0; i < numPts; ++i) {
		double x = XYZ[0*numPts + i];
		double z = XYZ[2*numPts + i];
		if (x == xmin) {
			x = x + xstep;
		}
		if (z == zmin) {
			z = z + zstep;
		}
		double col = ceil((x - xmin) / xstep);
		double row = ceil((z - zmin) / zstep);
		// determine the bin id
		int id = (row-1)*numX + col; // 1-based
		labels[i] = double(id);
		density[id-1] = density[id-1] + 1;
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
    if (nrhs != 2) {
    	mexErrMsgTxt("Number of input is expected to be two!");
    }
	if (nlhs != 2) {
		mexErrMsgTxt("There should be two output!");
	}

	// Validate input
	if (mxGetClassID(prhs[0]) != mxDOUBLE_CLASS) {
		mexErrMsgTxt("XYZ must be of double precision!");
	}

	if (mxGetClassID(prhs[1]) != mxDOUBLE_CLASS) {
		mexErrMsgTxt("rect must be of double precision!");
	}

	int colXYZ = (int)mxGetN(prhs[0]);
	if (colXYZ != 3) {
		mexErrMsgTxt("XYZ should have three columns!");
	}
    
    int rowRect = (int)mxGetM(prhs[1]);
	int colRect = (int)mxGetN(prhs[1]);
	if (rowRect != 1 || colRect != 4) {
		mexErrMsgTxt("rect should have one row and four columns!");
	}

    int numPts = (int)mxGetM(prhs[0]);
    //printf("numPts = %d\n", numPts);
	double *XYZ = mxGetPr(prhs[0]); // m-by-3
	double *rect = mxGetPr(prhs[1]); // 1-by-4

	// prepare output
	// density
	plhs[0] = mxCreateNumericMatrix(numCells, 1, mxDOUBLE_CLASS, mxREAL);
	// labels
	plhs[1] = mxCreateNumericMatrix(numPts, 1, mxDOUBLE_CLASS, mxREAL);

	double *density = mxGetPr(plhs[0]);
	double *labels = mxGetPr(plhs[1]);

	ptsFilter(numPts, XYZ, rect, density, labels);

}

