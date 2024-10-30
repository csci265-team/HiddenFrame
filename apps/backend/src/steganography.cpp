#include <hiddenframe_headers.h>
#include <iostream>
#include <fstream>//for testing data streaming capability
#include <cstring>//for testing data streaming capability

using namespace std;

int notmain(){
    try{
        //Simulates images on the FS
        /*
        image* test=new image("../../resources/images/test/input/test_image_1.jpg");
        test->displayImageProperties();
        int n=2;//pixel spacing
        int arrSize=12;
        int arr[12]={3,1,3,0,2,1,2,0,1,1,1,0};
        test->modify_image(n,arr,arrSize);
        test->write_image("../../resources/images/test/output/test_image_1.png");
        image* payloadTest=new image("../../resources/images/test/output/test_image_1.png");
        string payload=payloadTest->retrieve_payload(n);
        cout <<"Hidden Message is " <<payload << endl;*/
        
        //Simulate image passed by API
        // string imageData;
        // ifstream file("../../resources/images/test/input/test_image_6.bmp");
        // if (!file.is_open()){
        //     cerr << "String Not read" << endl;
        //     return 1;
        // }
        // string line;
        // while (getline(file, line)){
        //     imageData+=line;
        // }
        // file.close();
        // unsigned char* imgptr=new unsigned char[imageData.length()];
        // for (long long unsigned int i=0; i < (imageData.length()-1); i++){
        //     imgptr[i]=static_cast<unsigned char>(imageData[i]);
        // }
        // image* test2=new image(imgptr,imageData.length());
        // test2->displayImageProperties();
        // test2->filetype="bmp";
        // test2->write_image("../../resources/images/test/output/test_image_6.bmp");
        // delete [] imgptr;
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