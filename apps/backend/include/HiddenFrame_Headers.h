#include <string>
#include <unordered_map>
#include <vector>
#ifndef HiddenFrame_Headers 
#define HiddenFrame_Headers

using namespace std;

struct pixel{
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    unsigned char alpha;
    unsigned long int count=1;
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
    pixel* pArr;
    string filetype;
    void displayImageProperties();
    //vector<pixel> image_analysis(pixel*);
    void modify_image(int n, int arr[], int arrSize);
    string retrieve_payload(int n);
    void write_image(string filename);
    private:
    void pixel_array();
    void load_image(string filepath);
    size_t combined_hash(unsigned char r, unsigned char g, unsigned char b, unsigned char alpha);
    unsigned char* original_image;
    unsigned char* modified_image;
};
#endif
