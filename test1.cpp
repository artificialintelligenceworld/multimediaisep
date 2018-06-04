#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "highgui.h"
#include <stdlib.h>
#include <stdio.h>

using namespace cv;


Mat src, erosion_dst, dilation_dst, img_converted;
 
//erosion/dilation
int erosion_elem = 0;
int erosion_size = 0;
int dilation_elem = 0;
int dilation_size = 0;
int const max_elem = 2;
int const max_kernel_size = 100;

//resizing
const int slider_max = 100;
int slider;
Mat img;

//brightness
Mat image;
int alpha = 1, beta = 0;
int alpha_MAX = 100; 
int beta_MAX = 100; 

//unncanny edges
Mat src_gray;
Mat dst, detected_edges;

int edgeThresh = 1;
int lowThreshold;
int const max_lowThreshold = 100;
int ratio = 3;
int kernel_size = 3;
 


/** Function Headers */
void Erosion( int, void* );
void Dilation( int, void* );
void on_trackbar(int , void *);
void onTrackbar(int, void*);
void CannyThreshold(int, void*);
void manuplation (int, void*);



int main( int argc, char** argv )
{
  // image
  src = imread("cam.jpg");
img = imread("cam.jpg");
image = imread("cam.jpg");

  if( !src.data )
  { return -1; }

  ///  windows
  namedWindow( "Erosion Demo", CV_WINDOW_AUTOSIZE );
  namedWindow( "Dilation Demo", CV_WINDOW_AUTOSIZE );
  cvMoveWindow( "Dilation Demo", src.cols, 0 );
namedWindow( "resizing", CV_WINDOW_AUTOSIZE );
 namedWindow("image", CV_WINDOW_AUTOSIZE);
namedWindow( "canny", CV_WINDOW_AUTOSIZE );
namedWindow( "video", CV_WINDOW_AUTOSIZE );

  /// Create Erosion Trackbar
  createTrackbar( "Element:\n 0: Rect \n 1: Cross \n 2: Ellipse", "Erosion Demo",
                  &erosion_elem, max_elem,
                  Erosion );

  createTrackbar( "Kernel size:\n 2n +1", "Erosion Demo",
                  &erosion_size, max_kernel_size,
                  Erosion );

  /// Create Dilation Trackbar
  createTrackbar( "Element:\n 0: Rect \n 1: Cross \n 2: Ellipse", "Dilation Demo",
                  &dilation_elem, max_elem,
                  Dilation );

  createTrackbar( "Kernel size:\n 2n +1", "Dilation Demo",
                  &dilation_size, max_kernel_size,
                  Dilation );
/// Creating resizing Trackbar
createTrackbar("Size", "resizing", &slider, slider_max, on_trackbar);


 

    //Create 'Contrast' & 'Brightness' trackbars
    createTrackbar("Contrast", "image", &alpha, alpha_MAX, onTrackbar);
    createTrackbar("Brightness", "image", &beta, beta_MAX, onTrackbar);
 
//Create uncanny edge detectors
 
 createTrackbar( "Min Threshold:", "canny", &lowThreshold, max_lowThreshold, CannyThreshold ); 

/// Create a matrix of the same type and size as src (for dst)
  dst.create( src.size(), src.type() );

  /// Convert the image to grayscale
  cvtColor( src, src_gray, CV_BGR2GRAY );

 
  /// Default start
  Erosion( 0, 0 );
  Dilation( 0, 0 );
on_trackbar(0,0);
onTrackbar(0,0);
CannyThreshold(0, 0);
  waitKey(0);
  return 0;
}

/**  @function Erosion  */
void Erosion( int, void* )
{
  int erosion_type;
  if( erosion_elem == 0 ){ erosion_type = MORPH_RECT; }
  else if( erosion_elem == 1 ){ erosion_type = MORPH_CROSS; }
  else if( erosion_elem == 2) { erosion_type = MORPH_ELLIPSE; }

  Mat element = getStructuringElement( erosion_type,
                                       Size( 2*erosion_size + 1, 2*erosion_size+1 ),
                                       Point( erosion_size, erosion_size ) );

  /// Apply the erosion operation
  erode( src, erosion_dst, element );
  imshow( "Erosion Demo", erosion_dst );
 imwrite("ero.jpg" ,erosion_dst);
}

/** @function Dilation */
void Dilation( int, void* )
{
  int dilation_type;
  if( dilation_elem == 0 ){ dilation_type = MORPH_RECT; }
  else if( dilation_elem == 1 ){ dilation_type = MORPH_CROSS; }
  else if( dilation_elem == 2) { dilation_type = MORPH_ELLIPSE; }

  Mat element = getStructuringElement( dilation_type,
                                       Size( 2*dilation_size + 1, 2*dilation_size+1 ),
                                       Point( dilation_size, dilation_size ) );
  /// Apply the dilation operation
  dilate( src, dilation_dst, element );
  imshow( "Dilation Demo", dilation_dst );
 imwrite("dilla.jpg" ,dilation_dst);
}

void on_trackbar(int , void *)
{
    
    float scale = float(slider+50)/100;

     
    Size s(img.size().width*scale, img.size().height*scale);
    resize(img, img_converted, s);
    imshow("resizing", img_converted);
    imwrite("resized.jpg" ,img_converted);
}

void onTrackbar(int, void*)
{
    Mat new_image;
   
    image.convertTo(new_image, -1, alpha, beta);
 
    imshow("image", new_image); //Update the image
imwrite("light effectes image.jpg" , new_image);
}

void CannyThreshold(int, void*)
{

  blur( src_gray, detected_edges, Size(3,3) );
\
  Canny( detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size );

  
  dst = Scalar::all(20);

  src.copyTo( dst, detected_edges);
imshow( "canny", dst );
imwrite("edge.jpg" , image);
 }


    

