#include <string>
#ifndef HiddenFrame_Headers 
#define HiddenFrame_Headers

using namespace std;

struct pixel{
    int red=-1;
    int green=-1;
    int blue=-1;
    int alpha=-1;
    bool operator == (const pixel& rhs) const;
};

class image{
    public:
    image();
    image(string filepath);
    ~image();
    pixel* pixel_array();
    int width;
    int height;
    int channels;
    void displayImageProperties();
    private:
    unsigned char* load_image(string filepath);
    unsigned char* original_image;
};

#endif
