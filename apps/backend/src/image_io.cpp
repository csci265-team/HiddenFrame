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

//prints out the image properties
void image::displayImageProperties(){
    cout << "The loaded image has width: " << width << endl;
    cout << "The loaded image has height: " << height << endl;
    cout << "The loaded image has no channels: " << channels << endl;
}