#include <HiddenFrame_Headers.h>
#include <stdint.h>
#include <iostream>
#include <stb_image_write.h>
#include <stb_image.h>

using namespace std;

int main(){
    try{
        image* test=new image("../../resources/images/test/input/test_image_5.jpg");
        test->displayImageProperties();
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