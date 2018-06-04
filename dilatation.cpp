#include <opencv/cv.h>
#include <vector>
#include <iostream>
using namespace cv;
using namespace std;

int main( int argc, char** argv ) {
cout<<"Hiii";
Mat img=imread(argv[1],-1);
cv:: Mat img_dilate,img_erode;
cvNamedWindow("Original Image",0);
inshow("Original Image",img);

cvNamedWindow("Dilate Image",0);
dilate(img,img_dilate,Mat());
inshow("Dilete Image",img_dilate);
cvNamedWindow("Erode Image",0);
erode(img,img_erode,Mat());
inshow("Erode Image",img_erode);
waitKey(0);
return 0;
}
