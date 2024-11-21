#include <stdint.h>
#include <iostream>
#include <string>
#include <vector>
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
};
//regular constructor - data passed by API server
image::image(const unsigned char* Data, long long unsigned int length, string ext):width(0),height(0),channels(0),filetype(ext),original_image(nullptr), modified_image(nullptr){
    original_image=stbi_load_from_memory(Data,static_cast<int>(length),&width,&height,&channels,0);
    if (original_image==nullptr){
        throw std::invalid_argument("Image could not be opened - "+string(stbi_failure_reason()));
    }
};

//destructor
image::~image(){
    if (original_image==modified_image){
        modified_image=nullptr;
    }
    if (original_image != nullptr){
        stbi_image_free(original_image);
    }
    if (modified_image != nullptr){
        delete [] modified_image;
    }
}

bool image::valid_image(){
    if (original_image==nullptr){
        return false;
    }
    return true;
}
//load an image from a specified location
void image::load_image(string filepath) {
    filetype=filepath.substr(filepath.find_last_of(".")+1);
    int ioWidth, ioHeight, ioChannels;
    unsigned char* image_ptr = stbi_load(filepath.c_str(), &ioWidth, &ioHeight, &ioChannels, 0);
    if (image_ptr==nullptr){
        throw std::invalid_argument("Image could not be opened - "+string(stbi_failure_reason()));
    }
    width=ioWidth;
    height=ioHeight;
    channels=ioChannels;
    original_image=image_ptr;
    return;
}

void image::modify_image(int n, string payload)
{
    if (original_image==nullptr){
        throw std::invalid_argument("Original Image we are trying to modify is null");
    }
    modified_image=new unsigned char[channels*width*height];
    memcpy(modified_image,original_image, channels*width*height);
    vector <char> vec=bitStringCompressor(channels,payload);
    if (vec.size() > channels*width*height){
        throw std::invalid_argument("payload is too large for image size");
    }
    int k=0;//index for the vector will increment by 2 every time the loop executes
    for (int i=0; i < height; i++){
        for (int j=0; j < width; j+=n,k+=2){
            int index=(i*width+j)*channels;
            //we will land on only the pixel's we need to change
            //here we clean the pixel and change the LSB of the channel
            //case that we have a sequence of 1's
            if(vec[k+1]=='1'){
                //need to modify channel 1
                if (vec[k]=='1')
                {
                    modified_image[index] |= 1;
                    modified_image[index+1]&= ~1;
                    modified_image[index+2]&= ~1;
                    if (channels==4){
                        modified_image[index+3]&= ~1;
                    }
                }
                //need to modify channel 2
                else if (vec[k]=='2')
                {
                    modified_image[index]&= ~1;
                    modified_image[index+1]|= 1;
                    modified_image[index+2]&= ~1;
                    if (channels==4){
                        modified_image[index+3]&= ~1;
                    }
                }
                //need to modify channel 3
                else if (vec[k]=='3')
                {
                    modified_image[index]&= ~1;
                    modified_image[index+1]&= ~1;
                    modified_image[index+2]|= 1;
                    if (channels==4){
                        modified_image[index+3]&= ~1;
                    }
                }
                //need to modify channel 4
                else if (vec[k]=='4'){
                modified_image[index]&= ~1;
                modified_image[index+1]&= ~1;
                modified_image[index+2]&= ~1;
                modified_image[index+3]|= 1;
                }
            }
            //we have a sequence of 0's
            else{
                if(vec[k]=='1'){
                    modified_image[index] &= ~1;
                    modified_image[index+1]|= 1;
                    modified_image[index+2]|= 1;
                    if (channels==4){
                        modified_image[index+3]|= 1;
                    }
                }
                //need to modify channel 2
                else if(vec[k]=='2')
                {
                    modified_image[index]|= 1;
                    modified_image[index+1]&= ~1;
                    modified_image[index+2]|= 1;
                    if (channels==4){
                        modified_image[index+3]|= 1;
                    }
                }
                //need to modify channel 3
                else if (vec[k]=='3')
                {
                    modified_image[index]|= 1;
                    modified_image[index+1]|= 1;
                    modified_image[index+2]&= ~1;
                    if (channels==4){
                        modified_image[index+3]|= 1;
                    }
                }
                //need to modify channel 4
                else if (vec[k]=='4'){
                modified_image[index]|= 1;
                modified_image[index+1]|= 1;
                modified_image[index+2]|= 1;
                modified_image[index+3]&= ~1;
                }
            }
            //write a stop pixel and return when we are done encoding
            if (k >= vec.size()-2){
                j+=n;
                int index=(i*width+j)*channels;
                modified_image[index] &= ~1;
                modified_image[index+1]&= ~1;
                modified_image[index+2]&= ~1;
                if (channels==4){
                    modified_image[index+3]&= ~1;
                }
                return;
            }
        }
    }
}

string image::retrieve_payload(int n)
{
    if (original_image==nullptr){
        throw std::runtime_error("cannot retrive image is null");
    }
    string result;
    int k=0;
    for (int i=0; i < height; i++){
        for (int j=0; j < width; j+=n,k+=2){
            int index=(i*width+j)*channels;
                int redLSB=original_image[index]&1;
                int greenLSB=original_image[index+1]&1;
                int blueLSB=original_image[index+2]&1;
                int combined=(redLSB << 2) | (greenLSB << 1) | blueLSB;
                if (channels==4){
                    int alphaLSB=original_image[index+3]&1;
                    combined=(redLSB << 3) | (greenLSB << 2) | (blueLSB << 1) | alphaLSB;   
                }
                switch (channels){
                    case 3:
                        switch (combined){
                            //LSB's are 000
                            case 0:
                                return result;

                            //LSB's are 001
                            case 1:
                                result=result+"111";
                                break;

                            //LSB's are 010
                            case 2:
                                result=result+"11";
                                break;

                            //LSB's are 011
                            case 3:
                                result=result+"0";
                                break;

                            //LSB's are 100
                            case 4:
                                result=result+"1";
                                break;

                            //LSB's are 101
                            case 5:
                                result=result+"00";
                                break;

                            //LSB's are 110
                            case 6:
                                result=result+"000";
                                break;

                            //LSB's are 111
                            case 7:
                                return result;
                            
                        }
                    break;
                    case 4:
                        switch (combined){                                 
                            //LSB's are 0000
                            case 0:
                                return result;

                            //LSB's are 0001
                            case 1:
                                result=result+"1111";
                                break;

                            //LSB's are 0010
                            case 2:
                                result=result+"111";
                                break;

                            //LSB's are 0011
                            case 3:
                                return result;

                            //LSB's are 0100
                            case 4:
                                result=result+"11";
                                break;

                            //LSB's are 0101
                            case 5:
                                return result;

                            //LSB's are 0110
                            case 6:
                                return result;

                            //LSB's are 0111
                            case 7:
                                result=result+"0";
                                break;

                            //LSB's are 1000
                            case 8:
                                result=result+"1";
                                break;

                            //LSB's are 1001
                            case 9:
                                return result;

                            //LSB's are 1010
                            case 10:
                                return result;

                            //LSB's are 1011
                            case 11:
                                result=result+"00";
                                break;

                            //LSB's are 1100
                            case 12:
                                return result;

                            //LSB's are 1101
                            case 13:
                                result=result+"000";
                                break;

                            //LSB's are 1110
                            case 14:
                                result=result+"0000";
                                break;
                            //LSB's are 1111
                            case 15:
                                return result;   
                        }
                    break;
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

vector<char> image::bitStringCompressor(int channels, string toCompress){
    vector <char> vec;
    int count=1;
    for(int i=0; i < toCompress.length(); i+=count){
        count=1;
        char value=toCompress[i];
        while ( count < channels && toCompress[i+count]==value){
            count++;
        }
        vec.push_back(static_cast<char>(count+'0'));
        vec.push_back(value);
    }
    vec.shrink_to_fit();
    return vec;
}

/**
 * @brief   Finds the multiplicative inverse of any odd number between 1 and n.
 * @param   a any number such that 1 <= a < n.
 * @return  Returns the multiplicative inverse of a.
 */
long long image::findInverse(long long a, int n) {
    long long aInverse = 1;
    if(n%2 == 0) {
        while((a*aInverse)%n != 1) {
            aInverse += 2;
        }
    } else {
        while((a*aInverse)%n != 1) {
            aInverse ++;
        }
    }
    return aInverse;
}

/**
 * @brief   Given a number k in the range [1,n] and a known number a in the range [1,256], determines an integer b such that a*b%n = k.
 * @param   k the number which we are trying to generate.
 * @param   aInverse a number between 1 and n-1 that is the multiplicative inverse of a known number a in the range [1,n].
 * @return  Returns b such that a*b%n = k.
 */
long long image::findB(long long idealSkipSize, int n, int aInverse) {
    long long b = (idealSkipSize*aInverse) % n;
    return b;
}

/**
 * @brief   Given two positive integers n and b where 1<=b<n, computes the gcd(n,b).
 * @param   n The larger of the two integers whose gcd will be computed.
 * @param   b The lesser of the two integers whose gcd will be computed.
 * @return  The integer value of gcd(n,b).
 */
int image::euclideanAlgorithm(int n, int b) {
    while (b != 0) {
        int temp = b;
        b = n % b;
        n = temp;
    }
    return n;
}

/**
 * @brief   Builds an array and stores numbers that are coprime to n, that is, any integers k such that
 *          gcd(n,k)=1.
 * @param   n The integer value that is being checked for values that are coprime to it.
 * @param   coprimes An array to store integer values coprime to n.
 * @param   count The size of the coprimes array.
 * @return  No return type for a void function.
 */
void image::coprime_numbers(int n, int coprimes[], int &count) {
    for (int i = 2; i < n; ++i) {
        if (euclideanAlgorithm(i, n) == 1) {
            if (count < MAX_SIZE) {
                coprimes[count] = i; // Store coprime number in array
                count++; // Increment the count
            } else {
                //cout << "Array size exceeded!" << std::endl;
                break; // Stop if the array is full
            }
        }
    }
}

/**
 * @brief   Searches the coprimes array for a skip size that is just less than an even division of data pixels into the total pixels.
 * @param   coprimes The array storing values coprime to n.
 * @param   size The size of the coprimes array.
 * @param   idealSkipSize An even division of the characters into the image's pixel count that is not a generator of the total pixels.
 * @return  No return type for a void function.
 */
int image::binarySearch(int coprimes[], int size, const int idealSkipSize) {
    int start = 0;
    int end = size-1;
    int mid = (start + end)/2;
    while(start+1 != end && coprimes[mid] != idealSkipSize) {
        if(coprimes[mid] < idealSkipSize) {
            start = mid;
        } else {
            end = mid;
        }
        mid = (start + end)/2;
    }
    if(mid == idealSkipSize) {
        return coprimes[mid];
    } else {
        return coprimes[start];
    }
}

/**
 * @brief   Generates a key for an embedded and decoding a message to/from an image.
 * @param   imageSize The number of pixels in the image as an integer.
 * @param   messageSize The number of pixels required to contain the message (including the stopping pixel).
 * @param   channels The number of channels in the image.
 * @return  A string the contains an image key in the format (a_1,b_1,a_2,b_2,e,f) where each pair a*b mod imageSize = idealSkipSize, e is the hex length
 *          of each a, b, and f is the number of channels in the image.
 */
string image::generateKey(int imageSize, int messageSize, int channels) {
    if (messageSize <= 1 || messageSize > 1024) {
        return "Invalid message size, exiting.";
    }
    int coprimes[MAX_SIZE];
    int size = 0;
    coprime_numbers(imageSize, coprimes, size);
    int idealSkipSize = imageSize / messageSize;
    idealSkipSize = binarySearch(coprimes, size, idealSkipSize);
    string abArray[4];
    for(int i = 0; i < 4; i+=2) {
        long long randomA = coprimes[rand() % size];
        while (randomA == idealSkipSize) {
            randomA = coprimes[rand() % size];
        }
        cout << "a chosen is " << randomA << endl;
        int inverse = findInverse(randomA, imageSize);
        long long b = findB(idealSkipSize, imageSize, inverse);
        cout << "b is " << b << endl;
        cout << "The skip size should be " << randomA * b % imageSize << endl;
        abArray[i] = intToHex(randomA);
        abArray[i+1] = intToHex(b);
    }
    int lengths[4];
    int maxLength = 0;
    for(int i = 0; i < 4; i++) {
        if(abArray[i].length() > maxLength) {
            maxLength = abArray[i].length();
        }
    }
    for(int i = 0; i < 4; i++) {
        while(abArray[i].length() < maxLength) {
            abArray[i] = '0' + abArray[i];
        }
    }
    string key = "";
    for(int i = 0; i < 4; i++) {
        key = key + abArray[i];
    }
    key = key + to_string(maxLength) + to_string(channels);
    cout << "The key is " << key << endl;
    return key;
}

/**
 * @brief   Determines if a key is valid. If valid, calculates the skip size of pixels to find data in a payload.
 * @param   key The string key that is created at encoding to decode the message within the image.
 * @param   imageSize The number of pixels in the image.
 * @return  The interger value of the skip size between pixels containing payload data.
 */
int image::decodeKey(string key, int imageSize) {
    if(isValidHexCharacter(key) == false || key.length() == 0) {
        cout << "The key contains invalid characters or is empty." << endl;
        return -1;
    }
    int size = key.length();
    int channels = key[size - 1] - '0';
    int length = key[size - 2] - '0';
    std::stringstream ss;
    long long abPairArray[4];
    for(int i = 0; i < 4; i++) {
        string ab = key.substr(i*length, length);
        ss << std::hex << ab;
        ss >> abPairArray[i];
        ss.str("");
        ss.clear();
    }
    long long skipSize1 = abPairArray[0] * abPairArray[1] % imageSize;
    long long skipSize2 = abPairArray[2] * abPairArray[3] % imageSize;
    if(skipSize1 == skipSize2) {
        cout << "The skip size is of the given key is " << skipSize1 << endl;
        return skipSize1;
    } else {
        cout << "The key is not a valid, and a known payload is not present." << endl;
        return -1;
    }
}

/**
 * @brief   Generates a dummy key to be used for images without a payload.
 * @param   imageSize The size of the image for which a dummyKey is being generated. Required to check that the key couldn't be valid.
 * @return  Returns a dummy string that does NOT satisfy the key model.
 */
string image::generateDummyKey(int imageSize) {
    int randHexLength[] = {4, 5, 6, 7, 8};
    int randomLength = randHexLength[rand() % 5];
    const char hexChars[] = "0123456789ABCDEF";
    string dummyKey = "";
    while(decodeKey(dummyKey, imageSize) != -1 || dummyKey == "") {
        dummyKey = "";
        for(int i = 0; i < 4*randomLength; i++) {
            int randomHex = rand() % 16;
            dummyKey = dummyKey + hexChars[randomHex];
        }
        //To add the randomLength (between 5 and 8 inclusive) and a dummy channel value to the end of the string (between 1 and 4).
        dummyKey = dummyKey + to_string(randomLength) + to_string((rand() % 4) + 1);
    }
    cout << "The dummy key is " << dummyKey << endl;
    return dummyKey;
}

