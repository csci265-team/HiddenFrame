#include <iostream>
#include <bitset>
#include <string>

std::string stringToBinary(const std::string &str)
{
    std::string binaryString;
    for (char c : str)
    {
        binaryString += std::bitset<8>(c).to_string(); // Each character to 8-bit binary
    }
    return binaryString;
}

std::string binaryToString(const std::string &binaryStr)
{
    std::string text;
    for (size_t i = 0; i < binaryStr.size(); i += 8)
    {
        std::bitset<8> byte(binaryStr.substr(i, 8)); // Take 8 bits at a time
        text += static_cast<char>(byte.to_ulong());  // Convert binary to char
    }
    return text;
}
