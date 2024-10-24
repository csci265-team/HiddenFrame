#include <stdint.h>
#include <iostream>
#include <string>
#include <hiddenframe_headers.h>


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

using namespace std;

//default consturctor
image::image():width(0),height(0),channels(0),filetype(),original_image(nullptr),modified_image(nullptr){};

//regular constructor - image is already in the file system
image::image(string filepath):width(0),height(0),channels(0),filetype(),original_image(nullptr), modified_image(nullptr){
    load_image(filepath);
    if (original_image==nullptr){
        throw std::invalid_argument("Image could not be opened");
    }
};
//regular constructor - data bassed by API server
image::image(unsigned char* Data, long long unsigned int length):width(0),height(0),channels(0),filetype(),original_image(nullptr), modified_image(nullptr){
    original_image=stbi_load_from_memory(Data,static_cast<int>(length),&width,&height,&channels,0);
    if (original_image==nullptr){
        throw std::invalid_argument("Image could not be opened");
    }
};

//destructor
image::~image(){
    if (original_image != nullptr){
        stbi_image_free(original_image);
    }
    if (modified_image != nullptr){
        stbi_image_free(modified_image);
    }
}

//load an image from a specified location
void image::load_image(string filepath) {
    filetype=filepath.substr(filepath.find_last_of(".")+1);
    int ioWidth, ioHeight, ioChannels;
    unsigned char* image_ptr = stbi_load(filepath.c_str(), &ioWidth, &ioHeight, &ioChannels, 0);
    if (image_ptr==nullptr){
        throw std::invalid_argument("Image could not be opened");
    }
    width=ioWidth;
    height=ioHeight;
    channels=ioChannels;
    original_image=image_ptr;
    return;
}

void image::modify_image(int n, int arr[], int arrSize)
{
    if (original_image==nullptr){
        throw "Original Image we are trying to modify is null";
    }
    modified_image=new unsigned char[channels*width*height];
    memcpy(modified_image,original_image, channels*width*height);
    int k=0;
    for (int i=0; i < height; i++){
        for (int j=0; j < width; j+=n,k+=2){
            int index=(i*width+j)*channels;
            //we will land on only the pixel's we need to change
            //here we clean the pixel and change the LSB of the channel
            //case that we have a sequence of 1's
            if(arr[k+1]==1){
                //need to modify channel 1
                if (arr[k]==1)
                {
                    modified_image[index] |= 1;
                    modified_image[index+1]&= ~1;
                    modified_image[index+2]&= ~1;
                    if (channels==4){
                        modified_image[index+3]&= ~1;
                    }
                }
                //need to modify channel 2
                else if (arr[k]==2)
                {
                    modified_image[index]&= ~1;
                    modified_image[index+1]|= 1;
                    modified_image[index+2]&= ~1;
                    if (channels==4){
                        modified_image[index+3]&= ~1;
                    }
                }
                //need to modify channel 3
                else if (arr[k]==3)
                {
                    modified_image[index]&= ~1;
                    modified_image[index+1]&= ~1;
                    modified_image[index+2]|= 1;
                    if (channels==4){
                        modified_image[index+3]&= ~1;
                    }
                }
                //need to modify channel 4
                else{
                modified_image[index]&= ~1;
                modified_image[index+1]&= ~1;
                modified_image[index+2]&= ~1;
                modified_image[index+3]|= 1;
                }
            }
            //we have a sequence of 0's
            else{
                if(arr[k]==1){
                    modified_image[index] &= ~1;
                    modified_image[index+1]|= 1;
                    modified_image[index+2]|= 1;
                    if (channels==4){
                        modified_image[index+3]|= 1;
                    }
                }
                //need to modify channel 2
                else if(arr[k]==2)
                {
                    modified_image[index]|= 1;
                    modified_image[index+1]&= ~1;
                    modified_image[index+2]|= 1;
                    if (channels==4){
                        modified_image[index+3]|= 1;
                    }
                }
                //need to modify channel 3
                else if (arr[k]==3)
                {
                    modified_image[index]|= 1;
                    modified_image[index+1]|= 1;
                    modified_image[index+2]&= ~1;
                    if (channels==4){
                        modified_image[index+3]|= 1;
                    }
                }
                //need to modify channel 4
                else{
                modified_image[index]|= 1;
                modified_image[index+1]|= 1;
                modified_image[index+2]|= 1;
                modified_image[index+3]&= ~1;
                }
            }
            if (k >= (arrSize-2)){
                return;
            }
        }
    }
}

string image::retrieve_payload(int n)
{
    if (original_image==nullptr){
        throw "cannot retrive image is null";
    }
    string result;
    int k=0;
    for (int i=0; i < height; i++){
        for (int j=0; j < width; j+=n,k+=2){
            int index=(i*width+j)*channels;
            //check channel 1 and 1's
            if((original_image[index] & 1) && !(original_image[index+1] & 1) && !(original_image[index+2] & 1)){
                result=result+"1";
            }
              //check channel 1 and 0's
            else if(!(original_image[index] & 1) && (original_image[index+1] & 1) && (original_image[index+2] & 1)){
                result=result+"0";
            }
            //check channel 2 and 1's
            else if(!(original_image[index] & 1) && (original_image[index+1] & 1) && !(original_image[index+2] & 1)){
                result=result+"11";
            }
            //check channel 2 and 0's
            else if((original_image[index] & 1) && !(original_image[index+1] & 1) && (original_image[index+2] & 1)){
                result=result+"00";
            }
            //check channel 3 and 1's
            else if(!(original_image[index] & 1) && !(original_image[index+1] & 1) && (original_image[index+2] & 1)){
                result=result+"111";
            }
            //check channel 3 and 0's
            else if((original_image[index] & 1) && (original_image[index+1] & 1) && !(original_image[index+2] & 1)){
                result=result+"000";
            }
            //if we got here then we are no longer reading the hidden message
            //WenMay wish to add an escape sequence
            else{
                return result;
            }
        }
    }
    return result;
}

//prints out the image properties
void image::displayImageProperties(){
    cout << "The loaded image has width: " << width << endl;
    cout << "The loaded image has height: " << height << endl;
    cout << "The loaded image has no channels: " << channels << endl;
    cout << "The total number of pixels in the image is: "<< width * height <<endl;
    cout << "The loaded image has file type: " << filetype << endl;
}

void image::write_image(string filename)
{
    if (original_image==nullptr){
        throw "cannot retrive image is null";
    }
    if (modified_image==nullptr){
        modified_image=original_image;
    }
    int length=filename.length();
    char convertedFilename[length+1];
    strcpy(convertedFilename, filename.c_str());
    if (filetype=="png" || filetype=="jpg"){
        stbi_write_png(convertedFilename, width, height, channels, modified_image,width*channels);
    }
    else if (filetype=="bmp"){
        stbi_write_bmp(convertedFilename, width, height, channels, modified_image);
    }
    else if (filetype=="tga"){
        stbi_write_tga(convertedFilename, width, height, channels, modified_image);
    }
    else{
        throw std::invalid_argument("Invalid file type");        
    }
}

