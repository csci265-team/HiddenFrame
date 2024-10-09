#include <string>
#ifndef HiddenFrame_Headers 
#define HiddenFrame_Headers

using namespace std;

class image{
    public:
    image();
    image(string filepath);
    ~image();
    int width;
    int height;
    int channels;
    void displayImageProperties();
    private:
    unsigned char* load_image(string filepath);
    unsigned char* original_image;
};

//not sure if we will need this
class pixel{
    public:
    private:
};

#endif
