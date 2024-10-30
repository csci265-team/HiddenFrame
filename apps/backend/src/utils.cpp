#include <hiddenframe_headers.h>
#include <iostream>


using namespace std;

string reverse(string other){
    int length=other.length();
    string revstr;
    int i=0;
    int j=length-1;
    do{
       revstr[i]=other[j];
       i++;
       j--;
    } while ( i < length); 
    return revstr; 
}

string strToBinary(string s)
{
    int n = s.length();
    string bin = "";
    for (int i = 0; i <= n; i++)
    {
        // convert each char to
        // ASCII value
        int val = int(s[i]);
        // Convert ASCII value to binary
        while (val > 0)
        {
            (val % 2)? bin.push_back('1') :
                       bin.push_back('0');
            val /= 2;
        }
        reverse(bin);
    }
    return bin;
}
