#include <string>
#ifndef HiddenFrame_Headers 
#define HiddenFrame_Headers

using namespace std;

class image{
    public:
        image();
        image(string filepath);
        image(unsigned char* Data, long long unsigned int);
        ~image();
        int width;
        int height;
        int channels;
        string filetype;
        void displayImageProperties();
        void modify_image(int n, int arr[], int arrSize);
        string retrieve_payload(int n);
        void write_image(string filename);
    private:
        void load_image(string filepath);
        unsigned char* original_image;
        unsigned char* modified_image;
};
#endif
