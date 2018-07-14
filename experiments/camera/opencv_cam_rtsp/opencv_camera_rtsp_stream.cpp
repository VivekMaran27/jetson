#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>

/** Preprocessor Defines **/
#define EXPECTED_NUM_OF_ARGS    (2)
#define SUCCESS  	        (0)
#define FAILURE         	(-1)

using namespace cv;
using namespace std;

std::string g_stream_url;

/**
 * Function to validate and parse arguments.
 */
int ParseArgs(int argc, char **argv)
{
   int status_code;
   int arg_index = 1;

    if(argc == EXPECTED_NUM_OF_ARGS)
    {
        g_stream_url.assign(argv[arg_index]);
        status_code = SUCCESS;
    }
    else
    {
        status_code = FAILURE;
    }
    return status_code;
}

int main(int argc, char** argv)
{
    int status_code;
    VideoCapture cap; //Capture source
    Mat frame;        //Output to store the frame
    int counter = 0;

    //Validate command line arguments
    status_code = ParseArgs(argc, argv);
    if(SUCCESS == status_code)
    {
        cout<<"Capturing from: "<<g_stream_url<<endl;
        cap.open(g_stream_url);
        if(cap.isOpened())
        {
            cout<<"Capture opened" <<endl;
            //--- GRAB AND WRITE LOOP
            cout << "Start grabbing" << endl
                << "Press any key to terminate" << endl;
            for (;;)
            {
		++counter;
	        cout<<"counter: "<<counter<<endl;

                // wait for a new frame from camera and store it into 'frame'

                 cap.read(frame);
                // check if we succeeded
                if (frame.empty()) {
                    cerr << "ERROR! blank frame grabbed\n";
                    break;
                }
                // show live and wait for a key with timeout long enough to show images
                imshow("Live", frame);
                if (waitKey(5) >= 0)
                break;
            }
        }        
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return status_code;
}

