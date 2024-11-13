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

/**
 * @brief   Converts an integer into a hex value.
 * @param   num The integer value to be converted to hex.
 * @return  Returns the hex value as a string.
 */
std::string intToHex(int num) {
    std::stringstream ss;
    // Set the output format to hex and use uppercase letters for A-F
    ss << std::hex << std::uppercase << num;
    return ss.str();
}

/**
 * @brief   Loops through characters in a key.  Returns false if any character is not a valid hex char.
 * @param   key The key to be checked for valid chars.
 * @return  True if all the characters in the key are valid characters; false otherwise.
 */
bool isValidHexCharacter(const string& key) {
    for (char c : key) {
        if (!((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f'))) {
            return false;
        }
    }
    return true;
}
