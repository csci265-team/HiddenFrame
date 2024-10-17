#include <HiddenFrame_Headers.h>
#include <stdint.h>
#include <iostream>
#include <stb_image_write.h>
#include <stb_image.h>

using namespace std;

int main(){
    try{
        image* test=new image("../../resources/images/test/input/test_image_4.png");
        test->displayImageProperties();
        test->image_analysis(test->pArr);
        test->modify_image();
        test->write_image("../../resources/images/test/output/test_image_4.png");
        //test->image_analysis(test->pArr);
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