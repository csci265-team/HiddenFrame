#include <string>
#include <vector>
#include <sqlite3.h>
#ifndef hiddenframe_headers 
#define hiddenframe_headers

using namespace std;

const int MAX_SIZE_COPRIMES = 10000;

class image{
    public:
        image();
        image(string filepath);
        image(const unsigned char* Data, long long unsigned int length, string ext);
        ~image();
        int width;
        int height;
        int channels;
        string filetype;
        void displayImageProperties();
        void modify_image(int n, string payload);
        string retrieve_payload(int n);
        void write_image(string filename);
        //unsigned char* original_image;
    private:
        void load_image(string filepath);
        unsigned char* original_image;
        unsigned char* modified_image;
        //To find the multiplicative inverse of an element a from an Z_n group.
        long long findInverse(long long a, int n);
        //To find a number b, such that, g=ab mod n, where g is a generator of a Z_n group and
        //the ideal skip size of when encoding or decoding an image, a is also a generator
        //of the same Z_n group, an a inverse is a^-1 such that a*a^-1 mod n = 1.
        long long findB(long long idealSkipSize, int n, int aInverse);
        //Performs the Euclidean Algorithm to find gcd(n,b), by recursivly using the property
        //of the division algorithm that is, for n>b, n=qb + r for some q and r in Z where
        //0<=r<b and gcd(n,b)=gcd(b,r)
        int euclideanAlgorithm(int n, int b);
        //Iteratively uses the Euclidean Algorithm on a value n to find value in
        //{0,1,2,3,...,n-1} that are coprime to n and store them in an array, and keeps
        //track of the count of the number of values it finds.
        void coprime_numbers(int n, int coprimes[], int &count);

        //Compresses a string of binary bits into an array of integers with the format:
        //[3,1,2,0,4,1,...] that is to be read, "Three 1's, two 0's, four 1's..."
        vector<char> bitStringCompressor(int channels, string toCompress);
    };

sqlite3* createDB();
void createNewAdmin(sqlite3 *database,const string& username, const string& password);
void createNewUser(sqlite3 *database,const string& username, const string& password, const int InviteID);
bool authenticateUser(sqlite3 *database, const string& username, const string& password);
int createInvite(sqlite3 *database, const string &username);
pair<int, string> verifyTokenWithDb(sqlite3 *database, const string &tokenId);
void saveToken(sqlite3 *database, const string &username, const string &tokenId);

#endif