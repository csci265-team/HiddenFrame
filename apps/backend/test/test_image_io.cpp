#include <boost/test/unit_test.hpp>
#include <hiddenframe_headers.h>
#include <iostream>
#include <vector>
#include <utils.h>
#include <fstream>
#include <sstream>
#include <cstring>

using namespace std;

vector<unsigned char> readFileToBuffer(const char* filepath);

BOOST_AUTO_TEST_SUITE(ImageIOTestSuite)

BOOST_AUTO_TEST_CASE(TestLoadImageFromFileSystem)
{
    image* test1 = new image("../../resources/images/test/input/test_image_1.jpg");
    BOOST_REQUIRE(test1 != nullptr);
    BOOST_TEST_MESSAGE("Test 1 - Loading Image from File System - was successful.");
    test1->write_image("../../resources/images/test/output/test_image_1.png");
}

BOOST_AUTO_TEST_CASE(TestWriteImageToFileSystem)
{
    image* test2 = new image("../../resources/images/test/output/test_image_1.png");
    BOOST_REQUIRE(test2 != nullptr);
    BOOST_TEST_MESSAGE("Test 2 - Writing Image to File System - was successful.");
    image* test1 = new image("../../resources/images/test/input/test_image_1.jpg");
    BOOST_REQUIRE(test1 != nullptr);
    BOOST_CHECK(test1->filetype != test2->filetype);
    BOOST_TEST_MESSAGE("Test 3 - Changing image format - was successful.");
}

BOOST_AUTO_TEST_CASE(TestImageReadingFromSimulatedLiveStream)
{
    vector<unsigned char> imageData = readFileToBuffer("../../resources/images/test/input/test_image_6.bmp");
    image* test4 = new image(imageData.data(), static_cast<int>(imageData.size()), "bmp");
    BOOST_REQUIRE(test4 != nullptr);
    BOOST_TEST_MESSAGE("Test 4 - Image reading from simulated live stream - was successful.");
}

BOOST_AUTO_TEST_CASE(TestImageEmbeddingAndRetrieval)
{
    image* test5 = new image("../../resources/images/test/output/test_image_7.png");
    int n = 2; // pixel spacing
    string teststr = "010010000110010101101100011011000110111100100000010101110110111101110010011011000110010000100001";
    test5->modify_image(n, teststr);
    test5->write_image("../../resources/images/test/output/test_image_7.png");
    test5->displayImageProperties();
    image* payloadTest = new image("../../resources/images/test/output/test_image_7.png");
    string payload = payloadTest->retrieve_payload(n);
    BOOST_CHECK_EQUAL(binaryToString(teststr), binaryToString(payload));
    BOOST_TEST_MESSAGE("Test 5 - Image embedding and retrieval - was successful.");
}

BOOST_AUTO_TEST_SUITE_END()

vector<unsigned char> readFileToBuffer(const char* filepath) {
    ifstream file(filepath, ios::binary);
    if (!file) {
        throw std::runtime_error("Error opening file");
    }
    vector<unsigned char> buffer((istreambuf_iterator<char>(file)), (istreambuf_iterator<char>()));
    return buffer;
}