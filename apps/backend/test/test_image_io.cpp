#include <hiddenframe_headers.h>
#include <iostream>
#include <vector>
#include <utils.h>
#include <fstream>//for testing data streaming capability
#include <sstream>
#include <cstring>//for testing data streaming capability

vector<unsigned char> readFileToBuffer(const char* filepath);

int main(){
    try{
        //Simulates images on the FS
        image* test1=new image("../../resources/images/test/input/test_image_1.jpg");
        if (test1==nullptr){
            throw std::runtime_error("Test 1 - Loading Image from File System - failed.");
        }
        else{
            cout << "Test 1 - Loading Image from File System - was sucessful." << endl;
            //test1->displayImageProperties();
        }
        test1->write_image("../../resources/images/test/output/test_image_1.png");
        image* test2=new image("../../resources/images/test/output/test_image_1.png");
        if (test2==nullptr){
            throw std::runtime_error("Test 3 - writing Image to File System - failed.");
        }
        else{
            cout << "Test 2 - writing Image to File System - was sucessful." << endl;
            //test2->displayImageProperties();
            if (test1->filetype == test2->filetype){
                throw std::runtime_error("Test 3 - Changing image format - failed.");
            }
            else{
                cout << "Test 3 - Changing image format - was sucessful." << endl;
            }
        }

        //Simulate image passed by API
        vector<unsigned char> imageData = readFileToBuffer("../../resources/images/test/input/test_image_6.bmp");
        //cout << "Read " << imageData.size() << " bytes" << endl;
        image* test4=new image(imageData.data(), static_cast<int>(imageData.size()), "bmp");
        if (test4 != nullptr){
            cout << "Test 4 - image reading from simulated live stream - was successful." << endl;
            //test4->displayImageProperties();
            //test4->write_image("../../resources/images/test/output/test_image_6.bmp");
        }
        else{
            throw std::runtime_error("Test 4 - image reading from simulated live stream - failed.");
        }

        //tests the encoding of images
        image* test5=new image("../../resources/images/test/input/test_image_7.png");
        int n=2;//pixel spacing
        //string teststr="111000110010";
        //string teststr="01101000";
        //string teststr="010010000110010101101100011011000110111100100000010101110110111101110010011011000110010000100001";
        ifstream file("../../resources/lorumBN.txt");
        if (!file.is_open()){
            throw ("error opening lorum file");
        }
        stringstream buffer;
        buffer <<file.rdbuf();
        string teststr=buffer.str();
        test5->modify_image(n,teststr);
        test5->write_image("../../resources/images/test/output/test_image_7.png");
        test5->displayImageProperties();
        image* payloadTest=new image("../../resources/images/test/output/test_image_7.png");
        string payload=payloadTest->retrieve_payload(n);
        cout << binaryToString(payload) << endl;
        //cout << "Original Message is " << teststr << endl;
        //cout <<"Hidden Message is " <<payload << endl;
        if (binaryToString(teststr)==binaryToString(payload)){
            cout << "Test 5 - image embedding and retrieval - was sucessful." << endl;   
        }
        else{
            throw std::runtime_error("Test 5 - image embedding and retrieval - failed.");
        }

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


//helper function for spoofing API provisioned data 
vector<unsigned char> readFileToBuffer(const char* filepath) {
    ifstream file(filepath, ios::binary);
    if (!file) {
        throw std::runtime_error("Error opening file");
    }
    vector<unsigned char> buffer((istreambuf_iterator<char>(file)),(istreambuf_iterator<char>()));
    return buffer;
}