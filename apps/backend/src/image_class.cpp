#include <stdint.h>
#include <iostream>
#include <string>
#include <HiddenFrame_Headers.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace std;
//default consturctor
image::image():width(0),height(0),channels(0),original_image(nullptr){};

//regular constructor
image::image(string filepath):width(0),height(0),channels(0),original_image(nullptr){
    load_image(filepath);
};

//move consturctor

//copy constructor

//overloaded [] operator

//destructor
image::~image(){
    stbi_image_free(this);
}

//load an image from a specified location
unsigned char* image::load_image(string filepath) {
    int ioWidth, ioHeight, ioChannels;
    unsigned char* image_ptr = stbi_load(filepath.c_str(), &ioWidth, &ioHeight, &ioChannels, 0);
    if (image_ptr==nullptr){
        throw std::invalid_argument("Image could not be opened");
    }
    this->width=ioWidth;
    this->height=ioHeight;
    this->channels=ioChannels;
    return image_ptr;
}
//create and fill an array of pixel structs from an image:
pixel* image::pixel_array(){
    if (this==nullptr){
        throw std::invalid_argument("No Image loaded");
    }
    pixel* pixel_arr=new pixel[height*width];
    for (int i=0; i < height; i++){
        for (int j=0; j < width; j++){
            int index=i*width+j;
            if (channels==1){
                pixel_arr[index].red=static_cast<unsigned int>(this->original_image[i]);
            }
            if (channels==2){
                pixel_arr[index].red=static_cast<unsigned int>(this->original_image[i]);
                pixel_arr[index].alpha=static_cast<unsigned int>(this->original_image[i+1]);
            }
            if (channels==3){
                pixel_arr[index].red=static_cast<unsigned int>(this->original_image[i]);
                pixel_arr[index].green=static_cast<unsigned int>(this->original_image[i+1]);
                pixel_arr[index].blue=static_cast<unsigned int>(this->original_image[i+2]);
            }
            if (channels==4){
                pixel_arr[index].red=static_cast<unsigned int>(this->original_image[i]);
                pixel_arr[index].green=static_cast<unsigned int>(this->original_image[i+1]);
                pixel_arr[index].blue=static_cast<unsigned int>(this->original_image[i+2]);
                pixel_arr[index].alpha=static_cast<unsigned int>(this->original_image[i+3]); 
            }
        }
    }
    return pixel_arr;
}


//prints out the image properties
void image::displayImageProperties(){
    cout << "The loaded image has width: " << width << endl;
    cout << "The loaded image has height: " << height << endl;
    cout << "The loaded image has no channels: " << channels << endl;
    cout << "The total number of pixels in the image is: "<< width * height <<endl;
}

bool pixel::operator==(const pixel& rhs) const{
    if (rhs.red==this->red && rhs.green==this->green && rhs.blue==this->blue && rhs.alpha==this->alpha){
        return true;
    }
    return false;
}
