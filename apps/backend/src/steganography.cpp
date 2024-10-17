#include <HiddenFrame_Headers.h>
#include <stdint.h>
#include <iostream>
#include <stb_image_write.h>
#include <stb_image.h>

using namespace std;

int main(){
    try{
        image* test=new image("../../resources/images/test/input/test_image_1.jpg");
        test->displayImageProperties();
        //test->image_analysis(test->pArr);
        int n=2;//pixel spacing
        int arrSize=4;
        int arr[4]={2,1,3,0};//should give 11000
        test->modify_image(n,arr,arrSize);
        test->write_image("../../resources/images/test/output/test_image_1.jpg");
        image* payloadTest=new image("../../resources/images/test/output/test_image_1.jpg");
        string payload=payloadTest->retrieve_payload(n);
        cout << payload;
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