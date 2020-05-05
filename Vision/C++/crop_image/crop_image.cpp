#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
    if( argc != 6)
    {
     cout <<" Usage: crop_image ImageToLoadAndDisplay topl_crop_h topl_crop_w botr_crop_h botr_crop_w" << endl;
     return -1;
    }

    Mat image;
    image = imread(argv[1], IMREAD_COLOR);   // Read the file

    if(! image.data )                              // Check for invalid input
    {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }

    //default values
    float topl_crop [2] = {0.03, 0.04};
    float botr_crop [2] = {0.92, 0.98};

    topl_crop[0] = stof(argv[2]);
    topl_crop[1] = stof(argv[3]);
    botr_crop[0] = stof(argv[4]);
    botr_crop[1] = stof(argv[5]);

    int range[2][2];
    range[0][0] = (int) image.rows*topl_crop[0];
    range[0][1] = (int) image.rows*botr_crop[0];
    range[1][0] = (int) image.cols*topl_crop[1];
    range[1][1] = (int) image.cols*botr_crop[1];

    Mat croppedImg = image(Range(range[0][0],range[0][1]), Range(range[1][0], range[1][1]));
    namedWindow( "Original Image", WINDOW_AUTOSIZE );     // Create a window for display.
    imshow( "Original Image", image );                   // Show our image inside it.

    imshow( "Cropped image", croppedImg );    

    waitKey(0);                                          // Wait for a keystroke in the window
    return 0;
}
