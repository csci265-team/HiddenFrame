#include <stdint.h>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace std;

int main() {
    int width, height, channels;

    unsigned char* image = stbi_load("../../resources/images/test/test_image_1.jpg", &width, &height, &channels, 0);
    if (image==nullptr){
        cout << "error opening image " << stbi_failure_reason << endl;
        return -1;
    }

    //TESTING BELOW HERE
    cout << "width " << width << endl;
    cout << "height " << height << endl;
    cout << "channels " << channels << endl;

    // Loop through each pixel
    //each time we iterate y we need to add width to the index to get the start of the next line. 
    //Channels lets us pick the first index of the next pixel. 
    for (int y = 0; y < height; ++y){
        for (int x = 0; x < width; ++x) {
            //grey scale images
            int index=(y * width + x) * channels;
            if (channels==1){
                unsigned char gr = image[index];
                cout << static_cast<int>(gr) <<endl;
            }
            //greyscale with transparency
            else if (channels==2){
                unsigned char gr = image[index];
                unsigned char alpha = image[index+1];
                cout << static_cast<int>(gr) <<endl;
            }
            //standard RGB
            else if (channels==3){
            unsigned char r = image[index];
            unsigned char g = image[index+1];
            unsigned char b = image[index+2];
            cout << static_cast<int>(r) << "/"
                 << static_cast<int>(g) << "/"
                 << static_cast<int>(b) << endl;
            }
            //RGB with transparency
            else if (channels==4){
            unsigned char r = image[index];
            unsigned char g = image[index+1];
            unsigned char b = image[index+2];
            unsigned char alpha=image[index+3];
            cout << static_cast<int>(r) << "/"
                 << static_cast<int>(g) << "/"
                 << static_cast<int>(b) << "/"
                 << static_cast<int>(alpha) << endl;
            }
        }
    }

    stbi_image_free(image);

    return 0;
}