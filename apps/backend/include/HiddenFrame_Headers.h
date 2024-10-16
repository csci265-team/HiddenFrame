#include <string>
#include <unordered_map>
#ifndef HiddenFrame_Headers 
#define HiddenFrame_Headers

using namespace std;

struct pixel{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    unsigned char alpha;
    unsigned long int count=0;
    bool operator == (const pixel& rhs) const;
};

class image{
    public:
    image();
    image(string filepath);
    ~image();
    int width;
    int height;
    int channels;
    void displayImageProperties();
    void image_analysis(pixel*);
    private:
    void pixel_array();
    void load_image(string filepath);
    size_t combined_hash(unsigned char r, unsigned char g, unsigned char b, unsigned char alpha);
    unsigned char* original_image;
    pixel* pArr;
};

#endif
