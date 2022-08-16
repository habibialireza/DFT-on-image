#include <opencv2/core.hpp>
#include<iostream>
#include<cmath>
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

using namespace cv;
using namespace std;

void main() {
    Mat src = imread("inpot.PNG");
    cvtColor(src, src, COLOR_BGR2GRAY, 0);
    Mat real(src.rows, src.cols, CV_64F);
    
    double** area = new double* [src.rows];
    double** brea = new double* [src.rows];
    double** bimg = new double* [src.rows];

    for (int i = 0; i < src.rows; i++) {

        brea[i] = new double[src.cols];
    }
    for (int i = 0; i < src.rows; i++) {
        bimg[i] = new double[src.cols];
    }
    for (int i = 0; i < src.rows; i++) {
        area[i] = new double[src.cols];

    }

    MatIterator_<uchar> it, end;
    int j = 0, k = 0;
    for (it = src.begin<uchar>(), end = src.end<uchar>(); it != end; ++it) {
        area[j][k] = (double)(*it);
        k++;
        if (k >= src.cols) {
            k = 0;
            j++;
        }
    }
    
    double pi = 3.1415926536;
    double mt = -2.0;
    for (int u = 0; u < src.rows; u++)
        for (int v = 0; v < src.cols; v++) {
            brea[u][v] = 0;
            bimg[u][v] = 0;
            for (int x = 0; x < src.rows; x++)
                for (int y = 0; y < src.cols; y++) {
                    brea[u][v] += area[x][y] * sin(mt * pi * ((double)u * (double)x/ (double)src.rows+ (double)v * (double)y/ (double)src.cols) );
                    bimg[u][v] += area[x][y] * cos(mt * pi * ((double)u * (double)x / (double)src.rows + (double)v * (double)y / (double)src.cols));

                }
        }

    k = 0, j = 0;
    MatIterator_<double> it1, end1;
    for (it1 = real.begin<double>(), end1 = real.end<double>(); it1 != end1; ++it1) {

        *it1 = sqrt(pow(brea[j][k], 2.0) + pow(bimg[j][k], 2.0));
        k++;
        if (k >= src.cols) {
            k = 0;
            j++;
        }
    }
    k = 0, j = 0;

    Mat m1 = Mat::ones(real.rows, real.cols, real.type());
    add(real, m1, real);
    log(real, real);
    normalize(real, real, 0, 1, NORM_MINMAX);

    Rect rect = Rect(0, 0, real.cols & -2, real.rows & -2);
    real = Mat(real, rect);
    int cx = real.cols / 2;
    int cy = real.rows / 2;
    Mat tmp;

    Rect rect0 = Rect(0, 0, cx, cy);
    Rect rect1 = Rect(cx, 0, cx, cy);
    Rect rect2 = Rect(0, cy, cx, cy);
    Rect rect3 = Rect(cx, cy, cx, cy);

    Mat q0 = Mat(real, rect0);
    Mat q1 = Mat(real, rect1);
    Mat q2 = Mat(real, rect2);
    Mat q3 = Mat(real, rect3);

    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);

    q1.copyTo(tmp);
    q2.copyTo(q1);
    tmp.copyTo(q2);

    imshow("1", real);
    imwrite("out.PNG", real*255);
    waitKey(0);

}


