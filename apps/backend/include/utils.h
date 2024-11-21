#include <string>

std::string stringToBinary(const std::string &str);
std::string binaryToString(const std::string &binaryStr);
//Converts an integer value into the corresponding Hex string.
std::string intToHex(int num);
//Checks whether a character is a valid Hex character.
bool isValidHexCharacter(const std::string& key);
bool isValidEmailFormat(const std::string& possibleEmail);