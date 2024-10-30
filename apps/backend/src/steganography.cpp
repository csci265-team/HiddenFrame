#include <hiddenframe_headers.h>
#include <iostream>
#include <fstream>//for testing data streaming capability
#include <cstring>//for testing data streaming capability

using namespace std;

int notmain(){
    try{
        //do stuff
    }
    catch (const std::invalid_argument& e1){
        cerr << "Encountered an exception: " << e1.what() << endl;
    }
    return 0;
}
//sample image filepaths:
//"../../resources/images/test/input/test_image_1.jpg"
//"../../resources/images/test/input/test_image_2.png"
//"../../resources/images/test/input/test_image_3.png"