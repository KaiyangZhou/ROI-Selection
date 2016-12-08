#include "mex.h"
#include "math.h"

bool isValidBox(double *II, double thre_ratio, double w, int x1, int x2, int y1, int y2, const int nrow)
{
    // get four references
    double A = II[ (x1-1)*nrow + y1-1 ];
    double B = II[ x2*nrow + y1-1 ];
    double C = II[ (x1-1)*nrow + y2 ];
    double D = II[ x2*nrow + y2 ];
    // compute ratio
    double ratio = (D+A-B-C) / (w*w);
    if (ratio >= thre_ratio)
        return true;
    else
        return false;
}

void generateboxes(const double *roi, const int nrow, const int ncol,
        const double stride, int &numBoxes, double **boxes, double *lambda, double *depth,
        double *II, double thre_ratio)
{
    for (int j = 0; j < ncol; j+=stride) {
        for (int i = 0; i < nrow; i+=stride) {
            
            if (roi[j*nrow+i] == 1) {
                double d = depth[j*nrow+i];
                double w;
                w = 580*0.6/d;

                // constrain window size to predefined size
                //if (w < 84)
                    //w = 77;
                if (w < 103)
                    w = 92;
                else if (w >= 103 && w < 134)
                    w = 115;
                else if (w >= 134 && w < 173)
                    w = 154;
                else
                    w = 192;
                
                int hw = (int)round((w-1)/2); // half width
                // index is 0-based
                int x1 = j-hw;
                int x2 = j+hw;
                int y1 = i-hw;
                int y2 = i+hw;
                
                if (x1 > 0 && y1 > 0 && x2 < ncol-1 && y2 < nrow-1) { // check if window size exceeds image range
                    // discard window that contains mainly holes
                    if (isValidBox(II,thre_ratio,w,x1,x2,y1,y2,nrow)) {
                        // store box information
                        boxes[numBoxes][0] = double(x1+1);
                        boxes[numBoxes][1] = double(y1+1);
                        boxes[numBoxes][2] = double(x2+1);
                        boxes[numBoxes][3] = double(y2+1);
                        // store weight for depth result
                        double val;
                        if (d>1 && d<6)
                            //val = exp(-(d-1)/1.7372);
                            val = -0.2*(d-1)+1;
                        else if (d<=1)
                            val = 1;
                        else
                            val = 0;
                        lambda[numBoxes] = val;
                        numBoxes+=1;
                    }
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
    if (nrhs != 5) {
        mexErrMsgTxt("Five inputs are required");
    }
    if (nlhs != 2) {
        mexErrMsgTxt("Two outputs are expected");
    }
    if (mxGetClassID(prhs[0]) != mxDOUBLE_CLASS || mxGetClassID(prhs[1]) != mxDOUBLE_CLASS
            || mxGetClassID(prhs[2]) != mxDOUBLE_CLASS || mxGetClassID(prhs[3]) != mxDOUBLE_CLASS
            || mxGetClassID(prhs[4]) != mxDOUBLE_CLASS) {
        mexErrMsgTxt("Inputs should be of double precision");
    }
    
    int nrow = mxGetM(prhs[0]);
    int ncol = mxGetN(prhs[0]);
    
    //mexPrintf("nrow: %d, ncol: %d\n", nrow, ncol);
    
    double *roi = mxGetPr(prhs[0]);
    double stride = mxGetScalar(prhs[1]);
    double *depth = mxGetPr(prhs[2]);
    double *II = mxGetPr(prhs[3]); // integral image
    double thre_ratio = mxGetScalar(prhs[4]); // ratio threshold
    
    int numBoxes = 0;
    
    double **boxes;
    boxes = new double*[nrow*ncol];
    for (int i = 0; i < nrow*ncol; ++i) {
        boxes[i] = new double[4];
    }
    
    double *lambda;
    lambda = new double[nrow*ncol];
    
    generateboxes(roi, nrow, ncol, stride, numBoxes, boxes, lambda, depth, II, thre_ratio);
    
    plhs[0] = mxCreateNumericMatrix(numBoxes, 4, mxDOUBLE_CLASS, mxREAL); // store boxes information
    plhs[1] = mxCreateNumericMatrix(numBoxes, 1, mxDOUBLE_CLASS, mxREAL); // store weights
    double *outBox = mxGetPr(plhs[0]);
    double *outLambda = mxGetPr(plhs[1]);
    
    for (int i = 0; i < numBoxes; ++i) {
        outBox[0*numBoxes+i] = boxes[i][0];
        outBox[1*numBoxes+i] = boxes[i][1];
        outBox[2*numBoxes+i] = boxes[i][2];
        outBox[3*numBoxes+i] = boxes[i][3];
        
        outLambda[i] = lambda[i];
    }
    
    for (int i = 0; i < nrow*ncol; ++i) {
        delete [] boxes[i];
    }
    delete [] boxes;
}
