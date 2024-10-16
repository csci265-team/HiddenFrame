#include <stdint.h>
#include <iostream>
#include <string>
#include <functional>
#include <unordered_map>
#include <HiddenFrame_Headers.h>


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace std;
//default consturctor
image::image():width(0),height(0),channels(0),original_image(nullptr), pArr(nullptr){};

//regular constructor
image::image(string filepath):width(0),height(0),channels(0),original_image(nullptr), pArr(nullptr){
    load_image(filepath);
};

//move consturctor

//copy constructor

//overloaded [] operator

//destructor
image::~image(){
    stbi_image_free(this->original_image);
}

//load an image from a specified location
void image::load_image(string filepath) {
    int ioWidth, ioHeight, ioChannels;
    unsigned char* image_ptr = stbi_load(filepath.c_str(), &ioWidth, &ioHeight, &ioChannels, 0);
    if (image_ptr==nullptr){
        throw std::invalid_argument("Image could not be opened");
    }
    this->width=ioWidth;
    this->height=ioHeight;
    this->channels=ioChannels;
    this->original_image=image_ptr;
    return;
}
//create and fill an array of pixel structs from an image:
void image::pixel_array(){
    if (this->original_image==nullptr){
        throw std::invalid_argument("No Image loaded");
    }
    pixel* pixel_arr=new pixel[height*width];
    for (int i=0; i < height; i++){
        for (int j=0; j < width; j++){
            int index=i*width+j;
            if (channels==1){
                pixel_arr[index].red=this->original_image[i];
            }
            if (channels==2){
                pixel_arr[index].red=this->original_image[i];
                pixel_arr[index].alpha=this->original_image[i+1];
            }
            if (channels==3){
                pixel_arr[index].red=this->original_image[i];
                pixel_arr[index].green=this->original_image[i+1];
                pixel_arr[index].blue=this->original_image[i+2];
            }
            if (channels==4){
                pixel_arr[index].red=this->original_image[i];
                pixel_arr[index].green=this->original_image[i+1];
                pixel_arr[index].blue=this->original_image[i+2];
                pixel_arr[index].alpha=this->original_image[i+3]; 
            }
        }
    }
    this->pArr=pixel_arr;
}


//image analysis
void image::image_analysis(pixel* pArr)
{
    unordered_map<size_t, pixel> pMap;
    for (int i=0; i < (width*height); i++){
        size_t key=combined_hash(pArr[i].red,pArr[i].green, pArr[i].blue, pArr[i].alpha); // do some hashing here to get a unique key for each pixel 
        //key was not in the map
        if (pMap.find(key)== pMap.end()){
            pMap[key]=pArr[i];
        }
        //found pixel, iterate the count
        else{
            pMap.at(key).count++;
        }
    }
    //print the number of each pixel there is:
    for(const auto& key_value: pMap) {
        cout << "The colour " << static_cast<int>(key_value.second.red) << "/" 
        << static_cast<int>(key_value.second.green) << "/" 
        << static_cast<int>(key_value.second.blue) << "/" 
        << static_cast<int>(key_value.second.alpha) 
        << " Occurs " << key_value.second.count+1 << " times" << endl;
    }
}



//prints out the image properties
void image::displayImageProperties(){
    cout << "The loaded image has width: " << width << endl;
    cout << "The loaded image has height: " << height << endl;
    cout << "The loaded image has no channels: " << channels << endl;
    cout << "The total number of pixels in the image is: "<< width * height <<endl;
}

size_t image::combined_hash(unsigned char r, unsigned char g, unsigned char b, unsigned char alpha)
{
    hash<unsigned char> hash_fn;
    size_t hash= 17;
    hash=hash*31+hash_fn(r);
    hash=hash*31+hash_fn(g);
    hash=hash*31+hash_fn(b);
    hash=hash*31+hash_fn(alpha);
    return hash;
}

bool pixel::operator==(const pixel& rhs) const{
    if (rhs.red==this->red && rhs.green==this->green && rhs.blue==this->blue && rhs.alpha==this->alpha){
        return true;
    }
    return false;
}
